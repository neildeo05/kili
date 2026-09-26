/* SPDX-License-Identifier: GPL-2.0 WITH Linux-syscall-note */
#ifndef KILI_UAPI_H
#define KILI_UAPI_H

#include <linux/ioctl.h>
#include <linux/types.h>

/* Fixed layout, no pointers: identical for 32-bit and 64-bit applications.
 * One TMatmul: 16 packed weight bytes, 8 activation bytes, 8 output bytes.
 * Packing matches the hardware and kili.py; arithmetic wraps modulo 256.
 * ioctl returns 0 on success or -1/errno. Only read output on success.
 */
struct kili_job {
	__u8 weights[16];
	__u8 activations[8];
	__u8 output[8];
};

#define KILI_IOCTL_RUN _IOWR('K', 1, struct kili_job)

#endif
