/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Local experimental Kili PCIe accelerator. See README.md for the guest ABI. */
#include "qemu/osdep.h"
#include "qemu/module.h"
#include "hw/pci/pci.h"
#include "hw/pci/pci_device.h"
#include "hw/pci/pcie.h"
#include "qapi/error.h"
#include "hw/pci/msix.h"
#include "migration/vmstate.h"
#include "qom/object.h"
#include "kili-core.h"
#include "kili-regs.h"

#define TYPE_KILI "kili"
OBJECT_DECLARE_SIMPLE_TYPE(KiliState, KILI)

// qemu/hw/misc/edu.c
struct KiliState {
    PCIDevice pdev;
    MemoryRegion bar0;
    // backend state for the registers
    uint64_t sq_base;
    uint64_t cq_base;
    uint32_t sq_size;
    uint32_t cq_size;
    uint32_t sq_head;
    uint32_t sq_tail;
    uint32_t cq_head;
    uint32_t cq_tail;
    uint32_t error;
    bool enabled;
    bool configured;
};

static void kili_raise_irq(KiliState *s) {
    // Interrupt the guest using an MSI-X interrupt
    if (msix_enabled(PCI_DEVICE(s))) {
        msix_notify(PCI_DEVICE(s), 0);
    }
}

static void kili_fail(KiliState *s, uint32_t error) {
    // Backend-side failure, relay to driver
    if (!s->error) {
        s->error = error;
        kili_raise_irq(s);
    }
}

static bool kili_range_valid(uint64_t addr, size_t len) {
    return len && addr <= UINT64_MAX - (len - 1);
}

static bool kili_dma(KiliState *s, uint64_t addr, void *buf, size_t len, DMADirection direction) {
    const MemTxAttrs attrs = {.memory = true}; // restrict bus transactions to normal memories
    // this probably not needed when i switch to iommu
    // QEMU PCI DMA_RW will do a DMA request to a specific address, with buf.
    if(kili_range_valid(addr, len)) {
        return pci_dma_rw(PCI_DEVICE(s), addr, buf, len, direction, attrs) == MEMTX_OK;
    }
    return false;
}

static uint32_t kili_execute(KiliState *s, const uint8_t sqe[KILI_SQE_SIZE])
{
    uint64_t weights_addr = ldq_le_p(&sqe[KILI_SQE_WEIGHTS]);
    uint64_t acts_addr = ldq_le_p(&sqe[KILI_SQE_ACTIVATIONS]);
    uint64_t output_addr = ldq_le_p(&sqe[KILI_SQE_OUTPUT]);

    uint8_t weights[KILI_WEIGHT_BYTES];
    uint8_t activations[KILI_TILE_SIZE];
    uint8_t output[KILI_TILE_SIZE];

    if (ldl_le_p(sqe + KILI_SQE_RESERVED)) {
        return KILI_CQE_BAD_DESCRIPTOR;
    }
    if(!kili_range_valid(output_addr, sizeof(output))) return KILI_CQE_DMA_ERROR;
    bool weight_dma = kili_dma(s, weights_addr, weights, sizeof(weights), DMA_DIRECTION_TO_DEVICE);
    bool act_dma = kili_dma(s, acts_addr, activations, sizeof(activations), DMA_DIRECTION_TO_DEVICE);
    if(!weight_dma || !act_dma) return KILI_CQE_DMA_ERROR;

    // call backend ternary matmul
    kili_tmatmul(weights, activations, output);

    bool output_dma = kili_dma(s, output_addr, output, sizeof(output), DMA_DIRECTION_FROM_DEVICE);
    if(!output_dma) return KILI_CQE_DMA_ERROR;

    return KILI_CQE_OK;
}

static void kili_process(KiliState *s)
{
    PCIDevice *pdev = PCI_DEVICE(s);

    if (!s->enabled || s->error) {
        return;
    }
    if (!(pci_get_word(pdev->config + PCI_COMMAND) & PCI_COMMAND_MASTER)) {
        kili_fail(s, KILI_ERR_BUS_MASTER);
        return;
    }
    // driver writes to tail we read from head, we have to keep consuming from head until 
    // we finish everything driver wants us to finish
    while (s->sq_head != s->sq_tail &&
           (uint32_t)(s->cq_tail - s->cq_head) < s->cq_size) {
        uint8_t sqe[KILI_SQE_SIZE];
        uint8_t cqe[KILI_CQE_SIZE] = { 0 };
        uint64_t sq_addr = s->sq_base +
            (s->sq_head & (s->sq_size - 1)) * KILI_SQE_SIZE;
        uint64_t cq_addr = s->cq_base +
            (s->cq_tail & (s->cq_size - 1)) * KILI_CQE_SIZE;
        uint32_t status;
        // grab the head submission queue entry from memory
        if (!kili_dma(s, sq_addr, sqe, sizeof(sqe), DMA_DIRECTION_TO_DEVICE)) {
            kili_fail(s, KILI_ERR_SQ_DMA);
            return;
        }
        // execute the submission queue entry
        status = kili_execute(s, sqe);
        // write to the completion queue the same tag that was provided with the submission queue, and the status
        stl_le_p(cqe, ldl_le_p(sqe + KILI_SQE_TAG));
        stl_le_p(cqe + 4, status);
        // write the completion queue descriptor to the tail of the completion queue
        if (!kili_dma(s, cq_addr, cqe, sizeof(cqe),
                      DMA_DIRECTION_FROM_DEVICE)) {
            kili_fail(s, KILI_ERR_CQ_DMA);
            return;
        }
        // we have monotonically increasing counters, we can use head & (size-1) to find the slot
        s->sq_head++;
        s->cq_tail++;
        // once CQ is finished we interrupt the driver
        kili_raise_irq(s);
    }
}

static void kili_queue_reset(KiliState *s)
{
    s->enabled = false;
    s->configured = false;
    s->error = KILI_ERR_NONE;
    s->sq_base = s->cq_base = 0;
    s->sq_size = s->cq_size = 0;
    s->sq_head = s->sq_tail = s->cq_head = s->cq_tail = 0;
    msix_clr_pending(PCI_DEVICE(s), 0);
}

static bool kili_queue_valid(uint64_t base, uint32_t size, unsigned entry_size)
{
    return size >= 2 && size <= KILI_MAX_QUEUE_SIZE && !(size & (size - 1)) &&
           !(base & 63) && kili_range_valid(base, size * entry_size);
}

static uint64_t kili_read(void *opaque, hwaddr addr, unsigned size)
{
    // MMIO access to registers
    KiliState *s = opaque;

    switch (addr) {
    case KILI_REG_MAGIC:
        return KILI_MAGIC;
    case KILI_REG_VERSION:
        return KILI_ABI_VERSION;
    case KILI_REG_CONTROL:
        return s->enabled ? KILI_CTRL_ENABLE : 0;
    case KILI_REG_STATUS:
        return (s->enabled && !s->error ? KILI_STATUS_READY : 0) |
               (s->error ? KILI_STATUS_FATAL : 0) |
               (s->enabled && s->cq_size &&
                (uint32_t)(s->cq_tail - s->cq_head) == s->cq_size ?
                KILI_STATUS_CQ_FULL : 0);
    case KILI_REG_SQ_BASE_LO:
        return (uint32_t)s->sq_base;
    case KILI_REG_SQ_BASE_HI:
        return s->sq_base >> 32;
    case KILI_REG_CQ_BASE_LO:
        return (uint32_t)s->cq_base;
    case KILI_REG_CQ_BASE_HI:
        return s->cq_base >> 32;
    case KILI_REG_SQ_SIZE:
        return s->sq_size;
    case KILI_REG_CQ_SIZE:
        return s->cq_size;
    case KILI_REG_SQ_HEAD:
        return s->sq_head;
    case KILI_REG_SQ_TAIL:
        return s->sq_tail;
    case KILI_REG_CQ_HEAD:
        return s->cq_head;
    case KILI_REG_CQ_TAIL:
        return s->cq_tail;
    case KILI_REG_ERROR:
        return s->error;
    default:
        return 0;
    }
}

static void kili_write(void *opaque, hwaddr addr, uint64_t val, unsigned size)
{
    KiliState *s = opaque;
    uint32_t value = val;

    if (addr == KILI_REG_CONTROL) {
        if (value & KILI_CTRL_RESET) {
            kili_queue_reset(s);
        } else if (value == 0) {
            s->enabled = false;
        } else if (value == KILI_CTRL_ENABLE && !s->error) {
            if (!kili_queue_valid(s->sq_base, s->sq_size, KILI_SQE_SIZE) ||
                !kili_queue_valid(s->cq_base, s->cq_size, KILI_CQE_SIZE)) {
                kili_fail(s, KILI_ERR_CONFIG);
                return;
            }
            s->enabled = true;
            s->configured = true;
            kili_process(s);
        }
        return;
    }
    if (s->error) {
        return;
    }
    if (addr == KILI_REG_SQ_TAIL || addr == KILI_REG_CQ_HEAD) {
        // Writing to the tail means driver have submitted some work
        // Writing to head means the driver has finished some work
        // The interface is the driver writes the updated tail index/head index

        if (!s->enabled) {
            return;
        }
        if (addr == KILI_REG_SQ_TAIL) {
            // updated tail index minus previous tail tells us how many inflight requests there are
            uint32_t added = value - s->sq_tail;
            // we have to ensure that the driver isn't updating the tail past the amount of free queue entries (overwrite their own descriptors)
            uint32_t used = s->sq_tail - s->sq_head;
            if (added > s->sq_size - used) {
                kili_fail(s, KILI_ERR_DOORBELL);
                return;
            }
            s->sq_tail = value;
        } else {
            if ((uint32_t)(value - s->cq_head) >
                (uint32_t)(s->cq_tail - s->cq_head)) {
                kili_fail(s, KILI_ERR_DOORBELL);
                return;
            }
            s->cq_head = value;
        }
        kili_process(s);
        return;
    }
    /* Queue configuration is immutable until reset, even after pausing. */
    if (s->configured) {
        return;
    }
    switch (addr) {
    case KILI_REG_SQ_BASE_LO:
        s->sq_base = (s->sq_base & ~UINT64_C(0xffffffff)) | value;
        break;
    case KILI_REG_SQ_BASE_HI:
        s->sq_base = (s->sq_base & UINT32_MAX) | ((uint64_t)value << 32);
        break;
    case KILI_REG_CQ_BASE_LO:
        s->cq_base = (s->cq_base & ~UINT64_C(0xffffffff)) | value;
        break;
    case KILI_REG_CQ_BASE_HI:
        s->cq_base = (s->cq_base & UINT32_MAX) | ((uint64_t)value << 32);
        break;
    case KILI_REG_SQ_SIZE:
        s->sq_size = value;
        break;
    case KILI_REG_CQ_SIZE:
        s->cq_size = value;
        break;
    }
}

static const MemoryRegionOps kili_ops = {
    .read = kili_read,
    .write = kili_write,
    .endianness = DEVICE_LITTLE_ENDIAN,
    .valid = { .min_access_size = 4, .max_access_size = 4 },
    .impl = { .min_access_size = 4, .max_access_size = 4 },
};

static void kili_write_config(PCIDevice *pdev, uint32_t addr,
                              uint32_t val, int len)
{
    KiliState *s = KILI(pdev);
    bool was_enabled = msix_enabled(pdev);

    pci_default_write_config(pdev, addr, val, len);
    if (!was_enabled && msix_enabled(pdev) &&
        (s->cq_head != s->cq_tail || s->error)) {
        kili_raise_irq(s);
    }
}

static void kili_reset(DeviceState *dev)
{
    KiliState *s = KILI(dev);

    kili_queue_reset(s);
    msix_reset(PCI_DEVICE(s));
}

static void kili_realize(PCIDevice *pdev, Error **errp)
{
    KiliState *s = KILI(pdev);

    if (pcie_endpoint_cap_init(pdev, 0x80) < 0) {
        error_setg(errp, "Failed to initialize Kili PCIe capability");
        return;
    }

    memory_region_init_io(&s->bar0, OBJECT(s), &kili_ops, s,
                          "kili-bar0", KILI_BAR_SIZE);
    if (msix_init(pdev, 1, &s->bar0, 0, KILI_MSIX_TABLE,
                  &s->bar0, 0, KILI_MSIX_PBA, 0, errp)) {
        pcie_cap_exit(pdev);
        return;
    }
    msix_vector_use(pdev, 0);
    pci_register_bar(pdev, 0, PCI_BASE_ADDRESS_SPACE_MEMORY, &s->bar0);
}

static void kili_exit(PCIDevice *pdev)
{
    KiliState *s = KILI(pdev);

    msix_uninit(pdev, &s->bar0, &s->bar0);
    pcie_cap_exit(pdev);
}

/* No silent loss of queue state on migration/snapshot in this first model. */
static const VMStateDescription kili_vmstate = {
    .name = TYPE_KILI,
    .unmigratable = true,
};

static void kili_class_init(ObjectClass *klass, const void *data)
{
    DeviceClass *dc = DEVICE_CLASS(klass);
    PCIDeviceClass *pc = PCI_DEVICE_CLASS(klass);

    pc->realize = kili_realize;
    pc->exit = kili_exit;
    pc->config_write = kili_write_config;
    pc->vendor_id = KILI_PCI_VENDOR_ID;
    pc->device_id = KILI_PCI_DEVICE_ID;
    pc->revision = KILI_ABI_VERSION;
    pc->class_id = PCI_CLASS_OTHERS;
    dc->desc = "Kili ternary tile accelerator";
    dc->vmsd = &kili_vmstate;
    device_class_set_legacy_reset(dc, kili_reset);
    set_bit(DEVICE_CATEGORY_MISC, dc->categories);
}

static const TypeInfo kili_info = {
    .name = TYPE_KILI,
    .parent = TYPE_PCI_DEVICE,
    .instance_size = sizeof(KiliState),
    .class_init = kili_class_init,
    .interfaces = (const InterfaceInfo[]) {
        { INTERFACE_PCIE_DEVICE },
        { },
    },
};

static void kili_register_types(void)
{
    type_register_static(&kili_info);
}

type_init(kili_register_types)
