/* SPDX-License-Identifier: GPL-2.0-or-later */
#ifndef KILI_CORE_H
#define KILI_CORE_H

#include <stdint.h>

#define KILI_TILE_SIZE 8
#define KILI_WEIGHT_BYTES 16

uint16_t kili_decode_byte(uint8_t encoded);

void kili_tmatmul(const uint8_t weights[16], const uint8_t activations[8],
                  uint8_t output[8]);

#endif
