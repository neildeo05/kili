#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <random>
#include <unordered_map>

#include "verilated.h"
#include "Vternary_decoder.h"
#include "Vtop.h"

using namespace std;

// Required by Verilator
double sc_time_stamp() { return 0; }

// Trit encoding: -1 → 0b11, 0 → 0b00, +1 → 0b01
constexpr uint8_t TRIT_NEG  = 0b11;
constexpr uint8_t TRIT_ZERO = 0b00;
constexpr uint8_t TRIT_POS  = 0b01;

// Encoder: uses hardware decoder to build reverse lookup table
class TernaryEncoder {
private:
    unordered_map<uint16_t, uint8_t> trit_to_byte;
    Vternary_decoder* decoder;

public:
    TernaryEncoder() {
        decoder = new Vternary_decoder;
        // Build reverse lookup from all 243 valid encoded values
        for (int i = 0; i < 257; i++) {
            decoder->encoded_vals = i;
            decoder->eval();
            auto d = decoder->decoded_vals;
            trit_to_byte[d] = i;
        }
    }

    ~TernaryEncoder() { delete decoder; }

    static uint8_t trit_to_bits(int t) {
        return (t == -1) ? TRIT_NEG : (t == 1) ? TRIT_POS : TRIT_ZERO;
    }

    static int bits_to_trit(uint8_t b) {
        return (b == TRIT_NEG) ? -1 : (b == TRIT_POS) ? 1 : 0;
    }

    int64_t encode(int* t, int num_trits) {
        // Encode takes the number of trits and encodes it into a 64-bit integer.
        // There are NUM_TILE trits in a tile, so if the number of trits goes past the TRIT_PACK boundary, we need to encode the next tile.
        const int TRIT_PACK = 5;
        int num_tiles = (num_trits + TRIT_PACK - 1) / TRIT_PACK;
        int64_t result = 0;
        
        for (int tile = 0; tile < num_tiles; tile++) {
            int start = tile * TRIT_PACK;
            int end = std::min(start + TRIT_PACK, num_trits);
            
            uint16_t packed = 0;
            for (int i = start; i < end; ++i) {
                packed |= trit_to_bits(t[i]) << (2 * (i - start));
            }
            
            auto it = trit_to_byte.find(packed);
            if (it == trit_to_byte.end()) {
                printf("Failed to decode tile %d, packed=%x\n", tile, packed);
                decoder->encoded_vals = packed;
                decoder->eval();
                printf("Decoded: %x\n", decoder->decoded_vals);
                return -1;
            }
            
            result |= ((int64_t)it->second) << (8 * tile);
        }
        return result;
    }

};

// Software reference: multiply activation by trit
int8_t sw_tmul(uint8_t activation, int trit) {
    int8_t a = (int8_t)activation;
    if (trit == 1)  return a;
    if (trit == -1) return -a;
    return 0;
}

int main() {
    mt19937 gen(time(NULL));  // Fixed seed for reproducibility
    uniform_int_distribution<> trit_dist(-1, 1);
    uniform_int_distribution<> act_dist(0, 255);

    TernaryEncoder encoder;
    Vtop* top = new Vtop;

    int num_tests = 100;
    int errors = 0;
#ifndef TILE_SIZE
    #define TILE_SIZE 8
#endif

    printf("Running %d tests...\n\n", num_tests);

    for (int test = 0; test < num_tests; test++) {
        // Generate random trits and activations
        int trits[TILE_SIZE];
        uint8_t activations[TILE_SIZE];
        for (int i = 0; i < TILE_SIZE; i++) {
            trits[i] = trit_dist(gen);
            activations[i] = act_dist(gen);
        }
        std::cout << std::endl;

        // Encode trits to packed bytes (one byte per tile)
        int64_t encoded = encoder.encode(trits, TILE_SIZE);
        printf("Encoded: 0x%llx\n", (unsigned long long)encoded);
        if (encoded < 0) {
            printf("ERROR: Failed to encode trits\n");
            num_tests += 1;
            continue;
        }

        // Run hardware
        top->weights_in = encoded;
        for (int i = 0; i < TILE_SIZE; i++) {
            top->activations[i] = activations[i];
        }
        top->eval();

        // Compute expected in software
        int8_t expected[TILE_SIZE];
        for (int i = 0; i < TILE_SIZE; i++) {
            expected[i] = sw_tmul(activations[i], trits[i]);
        }

        // // Compare
        bool pass = true;
        for (int i = 0; i < TILE_SIZE; i++) {
            int8_t pr = (int8_t) top->products[i];
            if (pr != expected[i]) {
                printf("MISMATCH!: ");
                pass = false;
            }
            printf("Weight %d:, Activation %d: Expected: %d, Got: %d\n", trits[i], (int8_t) activations[i], expected[i], pr);
        }
        if(pass == false) {
            errors += 1;
        }
    }
    // printf("Ran %d tests\n", num_tests);

    printf("\n%d/%d tests passed\n", num_tests - errors, num_tests);

    delete top;
    return errors;
}
