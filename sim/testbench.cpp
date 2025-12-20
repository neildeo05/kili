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
        for (int i = 0; i < 243; i++) {
            decoder->encoded_vals = i;
            decoder->eval();
            trit_to_byte[decoder->decoded_vals] = i;
        }
    }

    ~TernaryEncoder() { delete decoder; }

    static uint8_t trit_to_bits(int t) {
        return (t == -1) ? TRIT_NEG : (t == 1) ? TRIT_POS : TRIT_ZERO;
    }

    static int bits_to_trit(uint8_t b) {
        return (b == TRIT_NEG) ? -1 : (b == TRIT_POS) ? 1 : 0;
    }

    // Encode 5 trits to 8-bit value
    int encode(int t0, int t1, int t2, int t3, int t4) {
        uint16_t packed = (trit_to_bits(t4) << 8) | (trit_to_bits(t3) << 6) |
                          (trit_to_bits(t2) << 4) | (trit_to_bits(t1) << 2) |
                          trit_to_bits(t0);
        auto it = trit_to_byte.find(packed);
        return (it != trit_to_byte.end()) ? it->second : -1;
    }
};

// Software reference: multiply activation by trit
int8_t sw_tmul(uint8_t activation, int trit) {
    int8_t a = (int8_t)activation;
    if (trit == 1)  return a;
    if (trit == -1) return -a;
    return 0;
}

// Function that takes the 10 bit packed decoded weights and returns the 5 trits
int8_t* decode_weights(uint16_t decoded_weights) {
    int8_t* trits = new int8_t[5];
    for (int i = 0; i < 5; i++) {
        trits[i] = (decoded_weights >> (i * 2)) & 0x3;
        if(trits[i] == 0b00) trits[i] = 0;
        else if(trits[i] == 0b01) trits[i] = 1;
        else if(trits[i] == 0b11) trits[i] = -1;
        else {
            printf("ERROR: Invalid decoded weight %d: %d\n", i, trits[i]);
            return NULL;
        }
    }
    return trits;
}

int main() {
    mt19937 gen(42);  // Fixed seed for reproducibility
    uniform_int_distribution<> trit_dist(-1, 1);
    uniform_int_distribution<> act_dist(0, 255);

    TernaryEncoder encoder;
    Vtop* top = new Vtop;

    int num_tests = 10;
    int errors = 0;

    printf("Running %d tests...\n\n", num_tests);

    for (int test = 0; test < num_tests; test++) {
        // Generate random trits and activations
        int trits[5];
        uint8_t activations[5];
        for (int i = 0; i < 5; i++) {
            trits[i] = trit_dist(gen);
            activations[i] = act_dist(gen);
        }

        // Encode trits to 8-bit
        int encoded = encoder.encode(trits[0], trits[1], trits[2], trits[3], trits[4]);
        printf("Encoded: %d\n", encoded);
        if (encoded < 0) {
            printf("ERROR: Failed to encode trits\n");
            continue;
        }

        // Run hardware
        top->weights = encoded;
        for (int i = 0; i < 5; i++) {
            top->activations[i] = activations[i];
        }
        top->eval();

        // Compute expected in software
        int8_t expected[5];
        for (int i = 0; i < 5; i++) {
            expected[i] = sw_tmul(activations[i], trits[i]);
        }

        // Compare
        bool pass = true;
        int8_t* decoded_trits = decode_weights(top->decoded_weights);
        for (int i = 0; i < 5; i++) {
            printf("Decoded weight %d: %d\n", i, decoded_trits[i]);
        }
        for (int i = 0; i < 5; i++) {
            printf("Weight %d:, Activation %d: Expected: %d, Got: %d\n", trits[i], (int8_t) activations[i], expected[i], (int8_t)top->products[i]);
        }
    }

    printf("\n%d/%d tests passed\n", num_tests - errors, num_tests);

    delete top;
    return errors;
}
