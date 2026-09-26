/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Guest-visible ABI. Multi-byte fields are little-endian, including DMA. */
#ifndef KILI_REGS_H
#define KILI_REGS_H

#define KILI_PCI_VENDOR_ID       0x1234
#define KILI_PCI_DEVICE_ID       0x1111 /* Local experimental ID. */
#define KILI_MAGIC               0x69696969
#define KILI_ABI_VERSION         2
#define KILI_BAR_SIZE            0x4000
#define KILI_MSIX_TABLE          0x2000
#define KILI_MSIX_PBA            0x3000
#define KILI_MAX_QUEUE_SIZE      256
#define KILI_SQE_SIZE            32
#define KILI_CQE_SIZE            8

#define KILI_REG_MAGIC           0x00
#define KILI_REG_VERSION         0x04
#define KILI_REG_CONTROL         0x08
#define KILI_REG_STATUS          0x0c
#define KILI_REG_SQ_BASE_LO      0x10
#define KILI_REG_SQ_BASE_HI      0x14
#define KILI_REG_CQ_BASE_LO      0x18
#define KILI_REG_CQ_BASE_HI      0x1c
#define KILI_REG_SQ_SIZE         0x20
#define KILI_REG_CQ_SIZE         0x24
#define KILI_REG_SQ_HEAD         0x28
#define KILI_REG_CQ_TAIL         0x2c
#define KILI_REG_SQ_TAIL         0x30
#define KILI_REG_CQ_HEAD         0x34
#define KILI_REG_ERROR           0x38

#define KILI_CTRL_ENABLE         1
#define KILI_CTRL_RESET          2
#define KILI_STATUS_READY        1
#define KILI_STATUS_FATAL        2
#define KILI_STATUS_CQ_FULL      4

/* Every SQE performs one TMatmul: 16 weight, 8 activation, 8 output bytes. */
#define KILI_SQE_TAG             0  /* u32: echoed in the completion */
#define KILI_SQE_RESERVED        4  /* u32: must be zero */
#define KILI_SQE_WEIGHTS         8  /* u64 DMA address */
#define KILI_SQE_ACTIVATIONS     16 /* u64 DMA address */
#define KILI_SQE_OUTPUT          24 /* u64 DMA address */

/* CQE: u32 tag, u32 status. Success means all eight output bytes are valid. */
#define KILI_CQE_OK              0
#define KILI_CQE_BAD_DESCRIPTOR  1
#define KILI_CQE_DMA_ERROR       2

/* Fatal queue errors: device stops until CTRL_RESET. */
#define KILI_ERR_NONE            0
#define KILI_ERR_CONFIG          1
#define KILI_ERR_DOORBELL        2
#define KILI_ERR_SQ_DMA          3
#define KILI_ERR_CQ_DMA          4
#define KILI_ERR_BUS_MASTER      5

#endif
