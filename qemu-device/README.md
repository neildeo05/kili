# Kili C / QEMU device

Implementation of QEMU backend for `kili` ternary AI accelerator, and linux kernel module for it
in `./qemu-device`

# Description

Like standard NVMe, there are two descriptor rings, the submission ring and the completion ring. The basic driver initiation operation is the driver writes a descriptor to the submission queue, notifies the device through an MMIO write (write the updated submisison queue tail pointer into the device register), sleeps. Here is the submission descriptor
```c
struct kili_sqe {
	// submission queue descriptor, tag and reserved are for validation
	// weights, activations, output contains the pointers for all of the buffers
	__le32 tag, reserved;
	__le64 weights, activations, output;
};
```

Since many threads can contend for a spot in the queue, we serialize publishing to the queue using a simple spinlock. The submission, completion, and buffers queue all are of size QUEUE_SIZE. If there is empty space in the buffers queue, the thread submit its job to the the submission and the buffers queue. If there isn't any space, we wait until the number of inflight jobs is less than the buffers queue size, meaning that we can publish our job to the buffers queue.

We sleep until the ISR/IRQ, which wakes us up. Given more time, I would've made it event driven.

After the MMIO doorbell, the device iterates through all of the descriptors that have been placed in the queue since it's previous observation of shared state. It does a DMA read request to obtain these descriptors. It then issues DMA read requests for the activations/weight matrices, performs the ternary matmul, then issues a DMA write. The QEMU config doesn't include an IOMMU, which should be enabled so the device doesn't overwrite sensitive data.

Here is the completion queue data structure:
```c

struct kili_cqe {
	// completion queue descriptor, ensure that tag is the same, status has to be OK for us to count it as completed
	__le32 tag, status;
};
```
We write the same tag into the completion descriptor, and increment it. In order to notify the device, we interrupt using an MSI-X interrupt. The driver will then verify all of the new entries on the completion queue (in the ISR itself).

To call the driver function, we call

```c
kili_tmatmul(job->weights, job->activations, job->output);
```


## Build and run

From this directory, install into the adjacent QEMU source checkout:

```sh
python3 install.py ../../../qemu
mkdir -p /tmp/kili-qemu-build
cd /tmp/kili-qemu-build
/absolute/path/to/qemu/configure --target-list=aarch64-softmmu --disable-docs --disable-rust
make -j8
```

Use the newly built binary and attach Kili through a PCIe root port:

```sh
-device pcie-root-port,id=kili_port,chassis=1 -device kili,bus=kili_port
```

Run the tests from this directory:

```sh
python3 -B tests/test_core.py --model ../../kili.py
python3 -B tests/test_device.py --qemu /tmp/kili-qemu-build/qemu-system-aarch64 --model ../../kili.py
```
