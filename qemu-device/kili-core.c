/* SPDX-License-Identifier: GPL-2.0-or-later */
/* Standalone functional datapath, also compiled into the QEMU device. */
#ifdef KILI_STANDALONE
#include <stdbool.h>
#else
#include "qemu/osdep.h"
#endif
#include "kili-core.h"

uint16_t kili_decode_byte(uint8_t encoded)
{
    bool b0 = (encoded >> 0) & 1;
    bool b1 = (encoded >> 1) & 1;
    bool b2 = (encoded >> 2) & 1;
    bool b3 = (encoded >> 3) & 1;
    bool b4 = (encoded >> 4) & 1;
    bool b5 = (encoded >> 5) & 1;
    bool b6 = (encoded >> 6) & 1;
    bool b7 = (encoded >> 7) & 1;
    bool z0 = !b6 && !b1 && b5;
    bool z1 = !b3 && b2;
    bool z2 = !b0 && b1;
    bool y1 = b0 && b1;
    bool y4 = !(b0 || !b4);
    bool y2 = !y4 && (b0 ^ b1) && !b3 && !b2;
    bool y3 = b0 && !b1 && b3;
    bool y5 = !b0 && !b1;
    bool y6 = !b0 && b3;
    bool y9 = !(!b3 || b2);
    bool x2 = z2 && b3 && b2;
    bool y7 = x2 && !b6;
    bool y8 = b0 && b7 && b6;
    bool y0 = (!b1 && !y9) || (b7 && z0) || y5 || (b1 && y9 && b7);
    bool x0 = y1 && b2;
    bool x1 = ((!b0 || b5) && !b6 && !b1 && b2) || !b3 || x0;
    bool x3 = ((b0 && z0) || z2) && !b7 && y9;
    bool x4 = (y2 && !b5) || z1 || y1;
    bool x5 = (y3 && !b6 && !b5) || (y6 && b2 && b6) || (y5 && y9);
    bool x6 = ((y8 || (b1 && !b4)) && b2) || (y8 && !b4 && b3) ||
              y7 || (b0 && z1) || y1;
    bool x7 = (!b0 && !b2 && (!b1 || b3)) || (y2 && b5);
    bool x8 = ((!b7 || !y9) && y1) || y7;
    bool x9 = (y6 && !b2) || (y4 && !b3) || (x2 && b6 && b4) ||
              y5 || (y3 && !b7 && b6);
    bool bits[10] = {
        x0 || y0, (b4 && y0) || (b3 && x0),
        x8 || x9, (b5 && x9) || (b4 && x8),
        x6 || x7, (b6 && x7) || (b5 && x6),
        x4 || x5, (b7 && x5) || (b6 && x4),
        x1 || x3, (b4 && x3) || (b7 && x1),
    };
    uint16_t decoded = 0;
    unsigned i;

    for (i = 0; i < 10; i++) {
        decoded |= (uint16_t)bits[i] << i;
    }
    return decoded;
}

void kili_tmatmul(const uint8_t weights[16], const uint8_t activations[8],
                  uint8_t output[8])
{
    // Performs the KILI matmul
    // 16 bytes is an 8x8 matrix, since they are all trit-packed
    unsigned row, col;

    for (row = 0; row < KILI_TILE_SIZE; row++) {
        // 2 bytes are required for 8 values, since we do 8 bits for 5 trits, we have to round up to 16 bits for 8 trits (lmao)
        uint32_t trits = kili_decode_byte(weights[2 * row]);
        trits |= (uint32_t)kili_decode_byte(weights[2 * row + 1]) << 10;
        int sum = 0;

        for (col = 0; col < KILI_TILE_SIZE; col++) {
            unsigned trit = (trits >> (2 * col)) & 3; // extract the trit
            if (trit == 1) { // if it is 1, we add
                sum += activations[col];
            } else if (trit == 3) { // if it is -1, we subtract
                sum -= activations[col];
            }
            // 0 is passthrough
        }
        output[row] = (uint8_t)sum; // 8x8 @ (8,1) -> (8,1)
    }
}