// SPDX-License-Identifier: GPL-2.0-or-later
#include <linux/module.h>
#include <linux/pci.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <linux/completion.h>
#include <linux/miscdevice.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/spinlock.h>
#include <linux/wait.h>
#include <linux/kref.h>
#include <linux/idr.h>
#include <linux/compat.h>

#include "kili-regs.h"
#include "kili-uapi.h"

#define KILI_QUEUE_SIZE 16
#define KILI_TIMEOUT_MS 5000

struct kili_sqe {
	// submission queue descriptor, tag and reserved are for validation
	// weights, activations, output contains the pointers for all of the buffers
	__le32 tag, reserved;
	__le64 weights, activations, output;
};

struct kili_cqe {
	// completion queue descriptor, ensure that tag is the same, status has to be OK for us to count it as completed
	__le32 tag, status;
};

// DMA will happen to this region
struct kili_dma_area {
	struct kili_sqe sq[KILI_QUEUE_SIZE];
	struct kili_cqe cq[KILI_QUEUE_SIZE];
	// a ring buffer of buffers that we DMA with
	struct kili_job buffers[KILI_QUEUE_SIZE];
};

struct kili_request {
	struct completion done;
	struct kili_job job;
	u32 tag;
	int result;
	bool pending;
};

struct kili_dev {
	// taken from dma kernel module example
	struct pci_dev *pdev;
	void __iomem *bar;
	struct kili_dma_area *dma;
	dma_addr_t dma_addr;
	struct miscdevice misc;
	spinlock_t lock;
	wait_queue_head_t space;
	struct kili_request *pending[KILI_QUEUE_SIZE];
	unsigned int inflight;
	struct kref refs;
	u32 sq_tail, cq_head;
	int irq, instance;
	bool removed, failed;
};

static DEFINE_IDA(kili_ids);

static void kili_release_dev(struct kref *ref)
{
	struct kili_dev *k = container_of(ref, struct kili_dev, refs);

	ida_free(&kili_ids, k->instance);
	kfree(k->misc.name);
	kfree(k);
}

static void kili_stop(struct kili_dev *k)
{
	iowrite32(KILI_CTRL_RESET, k->bar + KILI_REG_CONTROL);
	/* Flush the posted reset before DMA memory can be reused or freed. */
	ioread32(k->bar + KILI_REG_CONTROL);
}

static void kili_set_address(struct kili_dev *k, unsigned int reg,
			     dma_addr_t address)
{
	iowrite32(lower_32_bits(address), k->bar + reg);
	iowrite32(upper_32_bits(address), k->bar + reg + 4);
}

static void kili_abort_locked(struct kili_dev *k, int error)
{
	unsigned int i;

	k->failed = true;
	kili_stop(k);
	for (i = 0; i < KILI_QUEUE_SIZE; i++) {
		struct kili_request *req = k->pending[i];

		if (!req)
			continue;
		k->pending[i] = NULL;
		req->result = error;
		req->pending = false;
		complete(&req->done);
	}
	k->inflight = 0;
	wake_up_all(&k->space);
}

static irqreturn_t kili_irq(int irq, void *opaque)
{
	struct kili_dev *k = opaque;
	unsigned long flags;
	u32 tail;

	spin_lock_irqsave(&k->lock, flags);
	if (k->removed || k->failed)
		goto unlock;
	if (ioread32(k->bar + KILI_REG_ERROR))
		goto fail;
	tail = ioread32(k->bar + KILI_REG_CQ_TAIL);
	if ((u32)(tail - k->cq_head) > k->inflight)
		goto fail;
	dma_rmb(); // make sure the device has finished writing
	while (k->cq_head != tail) {
		// write to the completion queue and update the head to show we have processed the transactions
		unsigned int slot = k->cq_head & (KILI_QUEUE_SIZE - 1);
		struct kili_cqe *cqe = &k->dma->cq[slot];
		struct kili_request *req = k->pending[slot];
		u32 status = le32_to_cpu(cqe->status);

		if (!req || le32_to_cpu(cqe->tag) != req->tag ||
		    status > KILI_CQE_DMA_ERROR)
			goto fail;
		if (!status)
			memcpy(req->job.output, k->dma->buffers[slot].output,
			       sizeof(req->job.output));
		req->result = status == KILI_CQE_DMA_ERROR ? -EIO :
			      (status ? -EINVAL : 0);
		/* Copy results before freeing a slot for another caller. */
		k->pending[slot] = NULL;
		k->cq_head++;
		k->inflight--; // we can consume a buffer in the dma space
		req->pending = false;
		complete(&req->done);
	}
	dma_mb(); // memory barrier before we "doorbell"
	iowrite32(k->cq_head, k->bar + KILI_REG_CQ_HEAD);
	wake_up_all(&k->space);
	goto unlock;
fail:
	kili_abort_locked(k, -EIO);
unlock:
	spin_unlock_irqrestore(&k->lock, flags);
	return IRQ_HANDLED;
}

static int kili_open(struct inode *inode, struct file *file)
{
	struct miscdevice *misc = file->private_data;
	struct kili_dev *k = container_of(misc, struct kili_dev, misc);
	unsigned long flags;
	int ret = 0;

	spin_lock_irqsave(&k->lock, flags);
	if (k->removed) {
		ret = -ENODEV;
	} else {
		kref_get(&k->refs);
		file->private_data = k;
	}
	spin_unlock_irqrestore(&k->lock, flags);
	return ret;
}

static int kili_release(struct inode *inode, struct file *file)
{
	struct kili_dev *k = file->private_data;

	kref_put(&k->refs, kili_release_dev);
	return 0;
}

static long kili_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
	struct kili_dev *k = file->private_data;
	struct kili_request req;
	struct kili_sqe *sqe;
	dma_addr_t buffers;
	unsigned long flags;
	unsigned int slot;
	long ret;

	if (cmd != KILI_IOCTL_RUN)
		return -ENOTTY;
	if (copy_from_user(&req.job, (void __user *)arg, sizeof(req.job)))
		return -EFAULT;
	init_completion(&req.done);
	for (;;) {
		// in a crit section see if we have space
		spin_lock_irqsave(&k->lock, flags);
		if (k->removed || k->failed) {
			ret = k->removed ? -ENODEV : -EIO;
			goto unlock;
		}
		if (k->inflight < KILI_QUEUE_SIZE) // keep holding the lock throughout
			break;
		spin_unlock_irqrestore(&k->lock, flags);
		// wait until there is space
		ret = wait_event_interruptible(k->space, READ_ONCE(k->removed) || READ_ONCE(k->failed) || READ_ONCE(k->inflight) < KILI_QUEUE_SIZE);
		if (ret)
			return ret;
	}

	// find the slot, w wrap around
	slot = k->sq_tail & (KILI_QUEUE_SIZE - 1);
	// move the job buffers to the slot that we have
	memcpy(&k->dma->buffers[slot], &req.job, sizeof(req.job));
	buffers = k->dma_addr + offsetof(struct kili_dma_area, buffers) +
		  slot * sizeof(struct kili_job);
	req.tag = k->sq_tail + 1;
	req.pending = true;
	k->pending[slot] = &req;
	k->inflight++;
	sqe = &k->dma->sq[slot];
	memset(sqe, 0, sizeof(*sqe));
	sqe->tag = cpu_to_le32(req.tag);
	sqe->weights = cpu_to_le64(buffers + offsetof(struct kili_job, weights));
	sqe->activations = cpu_to_le64(buffers +
				      offsetof(struct kili_job, activations));
	sqe->output = cpu_to_le64(buffers + offsetof(struct kili_job, output));
	dma_wmb();
	k->sq_tail++;
	iowrite32(k->sq_tail, k->bar + KILI_REG_SQ_TAIL);
	spin_unlock_irqrestore(&k->lock, flags);

	/* Other callers may submit while this one sleeps for its own result. */
	if (!wait_for_completion_timeout(&req.done,
					msecs_to_jiffies(KILI_TIMEOUT_MS))) {
		spin_lock_irqsave(&k->lock, flags);
		/* Completion can race with the expiry of the wait. */
		if (req.pending) {
			kili_abort_locked(k, -EIO);
			req.result = -ETIMEDOUT;
			dev_err(&k->pdev->dev,
				"request timed out; reload kili_drv to recover\n");
		}
		spin_unlock_irqrestore(&k->lock, flags);
	}
	ret = req.result;
	if (!ret && copy_to_user((void __user *)arg, &req.job, sizeof(req.job)))
		ret = -EFAULT;
	return ret;

unlock:
	spin_unlock_irqrestore(&k->lock, flags);
	return ret;
}

static const struct file_operations kili_fops = {
	.owner = THIS_MODULE,
	.open = kili_open,
	.release = kili_release,
	.unlocked_ioctl = kili_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl = compat_ptr_ioctl,
#endif
	.llseek = no_llseek,
};

static int kili_probe(struct pci_dev *pdev, const struct pci_device_id *id)
{
	struct kili_dev *k;
	int ret;

	static_assert(KILI_QUEUE_SIZE >= 2 && KILI_QUEUE_SIZE <= KILI_MAX_QUEUE_SIZE);
	static_assert((KILI_QUEUE_SIZE & (KILI_QUEUE_SIZE - 1)) == 0);
	static_assert(sizeof(struct kili_sqe) == KILI_SQE_SIZE);
	static_assert(sizeof(struct kili_cqe) == KILI_CQE_SIZE);
	static_assert(offsetof(struct kili_dma_area, cq) % 64 == 0);
	static_assert(sizeof(struct kili_job) == 32);
	k = kzalloc(sizeof(*k), GFP_KERNEL);
	if (!k)
		return -ENOMEM;
	ret = ida_alloc(&kili_ids, GFP_KERNEL);
	if (ret < 0) {
		kfree(k);
		return ret;
	}
	k->instance = ret;
	kref_init(&k->refs);
	k->pdev = pdev;
	spin_lock_init(&k->lock);
	init_waitqueue_head(&k->space);
	k->misc.name = kasprintf(GFP_KERNEL, "kili%d", k->instance);
	if (!k->misc.name) {
		ret = -ENOMEM;
		goto put;
	}
	ret = pci_enable_device_mem(pdev);
	if (ret)
		goto put;
	ret = pci_request_region(pdev, 0, "kili_drv");
	if (ret)
		goto disable;
	if (!(pci_resource_flags(pdev, 0) & IORESOURCE_MEM) ||
	    pci_resource_len(pdev, 0) < KILI_BAR_SIZE) {
		ret = -ENODEV;
		goto region;
	}
	ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64));
	if (ret)
		ret = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
	if (ret)
		goto region;
	k->bar = pci_iomap(pdev, 0, KILI_BAR_SIZE);
	if (!k->bar) {
		ret = -ENOMEM;
		goto region;
	}
	if (ioread32(k->bar + KILI_REG_MAGIC) != KILI_MAGIC ||
	    ioread32(k->bar + KILI_REG_VERSION) != KILI_ABI_VERSION) {
		ret = -ENODEV;
		goto unmap;
	}
	kili_stop(k);
	k->dma = dma_alloc_coherent(&pdev->dev, sizeof(*k->dma),
				    &k->dma_addr, GFP_KERNEL);
	if (!k->dma) {
		ret = -ENOMEM;
		goto unmap;
	}
	memset(k->dma, 0, sizeof(*k->dma));
	ret = pci_alloc_irq_vectors(pdev, 1, 1, PCI_IRQ_MSIX);
	if (ret < 0)
		goto dma;
	k->irq = pci_irq_vector(pdev, 0);
	ret = request_irq(k->irq, kili_irq, 0, k->misc.name, k);
	if (ret)
		goto vectors;
	pci_set_master(pdev);
	kili_set_address(k, KILI_REG_SQ_BASE_LO, k->dma_addr);
	kili_set_address(k, KILI_REG_CQ_BASE_LO, k->dma_addr +
			 offsetof(struct kili_dma_area, cq));
	iowrite32(KILI_QUEUE_SIZE, k->bar + KILI_REG_SQ_SIZE);
	iowrite32(KILI_QUEUE_SIZE, k->bar + KILI_REG_CQ_SIZE);
	iowrite32(KILI_CTRL_ENABLE, k->bar + KILI_REG_CONTROL);
	if (ioread32(k->bar + KILI_REG_STATUS) != KILI_STATUS_READY) {
		ret = -EIO;
		goto irq;
	}
	k->misc.minor = MISC_DYNAMIC_MINOR;
	k->misc.fops = &kili_fops;
	k->misc.parent = &pdev->dev;
	k->misc.mode = 0600;
	ret = misc_register(&k->misc);
	if (ret)
		goto irq;
	pci_set_drvdata(pdev, k);
	dev_info(&pdev->dev, "/dev/%s ready, MSI-X IRQ %d\n", k->misc.name, k->irq);
	return 0;

irq:
	kili_stop(k);
	pci_clear_master(pdev);
	free_irq(k->irq, k);
vectors:
	pci_free_irq_vectors(pdev);
dma:
	dma_free_coherent(&pdev->dev, sizeof(*k->dma), k->dma, k->dma_addr);
unmap:
	pci_iounmap(pdev, k->bar);
region:
	pci_release_region(pdev, 0);
disable:
	pci_disable_device(pdev);
put:
	kref_put(&k->refs, kili_release_dev);
	return ret;
}

static void kili_remove(struct pci_dev *pdev)
{
	struct kili_dev *k = pci_get_drvdata(pdev);
	unsigned long flags;

	misc_deregister(&k->misc);
	spin_lock_irqsave(&k->lock, flags);
	k->removed = true;
	kili_abort_locked(k, -ENODEV);
	spin_unlock_irqrestore(&k->lock, flags);
	pci_clear_master(pdev);
	/* Synchronize with any ISR before releasing BAR0 and DMA storage. */
	free_irq(k->irq, k);
	pci_free_irq_vectors(pdev);
	dma_free_coherent(&pdev->dev, sizeof(*k->dma), k->dma, k->dma_addr);
	pci_iounmap(pdev, k->bar);
	pci_release_region(pdev, 0);
	pci_disable_device(pdev);
	kref_put(&k->refs, kili_release_dev);
}

static void kili_shutdown(struct pci_dev *pdev)
{
	struct kili_dev *k = pci_get_drvdata(pdev);
	unsigned long flags;

	spin_lock_irqsave(&k->lock, flags);
	kili_abort_locked(k, -EIO);
	spin_unlock_irqrestore(&k->lock, flags);
	pci_clear_master(pdev);
}

static const struct pci_device_id kili_pci_ids[] = {
	{ PCI_DEVICE(KILI_PCI_VENDOR_ID, KILI_PCI_DEVICE_ID) },
	{ }
};
MODULE_DEVICE_TABLE(pci, kili_pci_ids);

static struct pci_driver kili_driver = {
	.name = "kili_drv",
	.id_table = kili_pci_ids,
	.probe = kili_probe,
	.remove = kili_remove,
	.shutdown = kili_shutdown,
};
module_pci_driver(kili_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Blocking PCI/MSI-X driver for the Kili ternary accelerator");
