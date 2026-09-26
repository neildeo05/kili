# Kili C / QEMU device

This local experimental PCIe device exposes the same functional datapath as
`kili.py`. It models computation, DMA queues and interrupts, without accelerator
cycle timing. The device is named `kili`, with experimental PCI ID `1234:1111`.
`kili-core.c` is also a standalone C library, independent of QEMU.

The [Linux driver and guest walkthrough](driver/README.md) provides a blocking
`/dev/kili0` ioctl interface, a two-layer C neural-network example, and instructions to restart
the existing Ubuntu ARM64 VM with this device and load the module.

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

This works with the AArch64 `virt` machine or an x86 `q35` machine. The installed
system QEMU binary does not contain this device. The model advertises a PCI
Express capability at configuration offset `0x80`. ABI version 2 supports only
TMatmul. Rebuild QEMU, the driver, and guest programs together: version 1 queue
entries and ioctl payloads are incompatible.

Run the tests from this directory:

```sh
python3 -B tests/test_core.py --model ../../kili.py
python3 -B tests/test_device.py --qemu /tmp/kili-qemu-build/qemu-system-aarch64 --model ../../kili.py
```

The first test compiles the actual C core and compares it with Python, including
all 65,536 encoded row-byte pairs. The second starts an AArch64 QEMU under qtest
and verifies the PCIe endpoint capability behind a root port, matrix
multiplication, ring wraparound/full handling, MSI-X message delivery, pending-bit masking/unmasking, late interrupt
enable, errors, and reset. MSI-X messages target test RAM so their data writes
can be verified without a guest interrupt handler. No guest disk is used.

For standalone C use:

```c
#include "kili-core.h"

uint8_t weights[16];     /* Same encoded tile bytes as Python. */
uint8_t activations[8];  /* Eight signed or unsigned byte bit patterns. */
uint8_t result[8];
/* Fill weights and activations first. */
kili_tmatmul(weights, activations, result);
```

Compile your program with `cc -DKILI_STANDALONE program.c kili-core.c`.
Inputs and output must not overlap. All arithmetic wraps modulo 256. No heap
allocation or external libraries are needed by the standalone core.

## BAR0 registers

BAR0 is a 16 KiB memory BAR. Device registers accept aligned, little-endian
32-bit accesses only. Use the two halves when programming a 64-bit address.
Reserved registers read zero and ignore writes. Read-only registers ignore writes.

| Offset | Register | Access / meaning |
|---|---|---|
| `0x00` | MAGIC | RO: `0x69696969` |
| `0x04` | VERSION | RO: ABI version 2 |
| `0x08` | CONTROL | RW: bit 0 enables processing; bit 1 resets queues |
| `0x0c` | STATUS | RO: bit 0 ready, bit 1 fatal error, bit 2 CQ full |
| `0x10/14` | SQ_BASE_LO/HI | RW: submission ring DMA address |
| `0x18/1c` | CQ_BASE_LO/HI | RW: completion ring DMA address |
| `0x20` | SQ_SIZE | RW: number of submission slots |
| `0x24` | CQ_SIZE | RW: number of completion slots |
| `0x28` | SQ_HEAD | RO: device submission consumer counter |
| `0x2c` | CQ_TAIL | RO: device completion producer counter |
| `0x30` | SQ_TAIL | RW: guest submission producer / doorbell |
| `0x34` | CQ_HEAD | RW: guest completion consumer / doorbell |
| `0x38` | ERROR | RO: sticky fatal error code |
| `0x2000` | MSI-X table | One standard 16-byte vector entry |
| `0x3000` | MSI-X PBA | Standard pending-bit array |

Both queue sizes must be powers of two from 2 to 256 and their bases must be
64-byte aligned. Queue configuration is writable only before the first enable
or after queue reset. Queue addresses, buffers, and completions must reference
DMA-accessible guest RAM and must not overlap queue storage. The PCI bus-master
bit must be enabled. DMA uses the PCI address space, including IOMMU translation;
these are DMA addresses, not host pointers or guest virtual addresses. Accesses
to MMIO and overflowing DMA ranges are rejected.

`CONTROL=0` pauses consumption, preserving pending requests and completions;
`CONTROL=1` resumes. `CONTROL=2` cancels pending processing, resets configuration,
counters and error status, and clears the MSI-X pending bit without writing guest
memory. It preserves PCI/MSI-X configuration. Reset takes precedence over enable.
A PCI/device reset additionally resets MSI-X. Queue processing runs directly
inside the MMIO write handler when enabling the device or ringing a doorbell.
It stops when the SQ is empty or the CQ is full; at most 256 requests can be
pending. There is no deferred callback or artificial compute delay.
Doorbells written while disabled/paused are ignored; resume before publishing
submissions or acknowledging completions.

## Submission and completion format

Every submission performs one TMatmul: read 16 packed weight bytes and 8
activation bytes, then write 8 output bytes. There is no opcode or tile count.
Each submission is 32 bytes. All multi-byte fields are little-endian.

| Offset | Type | Meaning |
|---|---|---|
| `0` | u32 | Guest request tag, echoed in the completion |
| `4` | u32 | Reserved, zero |
| `8` | u64 | Packed weights DMA address |
| `16` | u64 | Activations DMA address |
| `24` | u64 | Output DMA address |

To multiply two 8x8 matrices, enqueue eight requests sharing the weight address,
with one eight-byte activation column per request. The eight results are output
columns.

Weights retain the HDL packing: two encoded bytes per row; the first decodes to
five trits, the second to three used trits and two ignored padding trits. Row
zero comes first. The encoding is the exact Boolean decoder, not base 3.

Each completion is 8 bytes:

| Offset | Type | Meaning |
|---|---|---|
| `0` | u32 | Request tag |
| `4` | u32 | Status: 0 success, 1 bad descriptor, 2 DMA error |

Success means all eight output bytes are valid. There is no variable output
length or separate submission sequence; the tag identifies the request.

An operand/output DMA failure produces an error completion and does not stop
later requests. Output memory may be partially written on a DMA error; ignore
it unless the completion reports success. An unreadable SQE or unwritable CQE
sets a fatal error and stops processing, since a reliable completion cannot be
posted. Fatal codes are: 1 invalid configuration, 2 invalid doorbell advance,
3 SQ DMA failure, 4 CQ DMA failure, 5 PCI bus mastering disabled. A fatal error
also notifies MSI-X vector 0 when enabled. Reset is required to recover.

## Guest submission sequence

1. Enable PCI memory decoding and bus mastering. Map BAR0 and configure MSI-X
   vector 0 through the standard PCI capability, table and mask controls.
2. Allocate non-overlapping DMA-coherent rings and operand/output buffers.
   Program ring bases and sizes, then write `CONTROL=1` and check STATUS.
3. Write each SQE at `SQ_BASE + (producer & (SQ_SIZE - 1)) * 32`.
   Execute a DMA write barrier, advance the producer counter and write its
   value to `SQ_TAIL`. One doorbell may publish multiple requests.
4. On interrupt (or while polling), read `CQ_TAIL`, execute a DMA read barrier,
   and read CQEs at `CQ_BASE + (consumer & (CQ_SIZE - 1)) * 8`. A successful
   CQE means its output bytes are already written. Check ERROR as well.
5. After consuming CQEs/output, advance `CQ_HEAD`. This frees slots and resumes
   processing if the device stopped because the completion ring was full.

All four counters are monotonically increasing **32-bit counters**, wrapping
modulo 2^32, not slot indexes. Occupancy is unsigned producer-minus-consumer;
every allocated slot is usable. Never publish more than `SQ_SIZE` outstanding
SQEs or acknowledge CQEs not yet produced. Invalid advances halt the device.
The device never overwrites an unconsumed completion. Software owns submission
entries until the doorbell and must not modify them until SQ_HEAD passes them.

Each posted completion requests MSI-X vector 0, after writing output, CQE and
publishing counters. Masked interrupts use the standard PBA; multiple masked
events may coalesce. Enabling MSI-X after polling notifies any outstanding
completion/error. A driver must drain the CQ rather than assume one entry per
interrupt. No legacy INTx fallback is provided. Snapshot/live migration is
explicitly blocked for this initial model.
