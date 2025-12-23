#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <random>
#include <unordered_map>

#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vternary_decoder.h"
#include "Vtop.h"

using namespace std;

#ifndef TILE_SIZE
    #define TILE_SIZE 8
#endif

// Pipeline latency: decode(1) + multiply(1) + reduction(log2(TILE_SIZE))
constexpr int PIPELINE_LATENCY = 2 + 3; // For TILE_SIZE=8: 2 + log2(8) = 5

// Global simulation time for VCD
vluint64_t sim_time = 0;

// Required by Verilator
double sc_time_stamp() { return sim_time; }

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
        // Build reverse lookup from all 256 possible encoded values
        for (int i = 0; i < 256; i++) {
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
                printf("Failed to encode tile %d, packed=%x\n", tile, packed);
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

// Clock the design with VCD tracing
void tick(Vtop* top, VerilatedVcdC* tfp) {
    top->clk = 0;
    top->eval();
    if (tfp) tfp->dump(sim_time++);
    
    top->clk = 1;
    top->eval();
    if (tfp) tfp->dump(sim_time++);
}

// Compute expected dot product in software
int8_t sw_dot_product(int* trits, uint8_t* activations, int size) {
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += sw_tmul(activations[i], trits[i]);
    }
    return (int8_t)sum;
}

int main() {
    mt19937 gen(42);  // Fixed seed for reproducibility
    uniform_int_distribution<> trit_dist(-1, 1);
    uniform_int_distribution<> act_dist(0, 255);

    // Initialize Verilator
    Verilated::traceEverOn(true);

    TernaryEncoder encoder;
    Vtop* top = new Vtop;

    // Setup VCD tracing
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);  // Trace 99 levels of hierarchy
    tfp->open("waveform.vcd");

    int num_tests = 10;
    int errors = 0;

    printf("Running %d tests with TILE_SIZE=%d, pipeline latency=%d cycles\n\n", 
           num_tests, TILE_SIZE, PIPELINE_LATENCY);

    // Reset the design
    top->clk = 0;
    top->rst = 1;
    top->weight_fifo_valid = 0;
    top->weight_fifo_in = 0;
    for (int i = 0; i < TILE_SIZE; i++) {
        top->activations_in[i] = 0;
    }
    
    // Hold reset for a few cycles
    for (int i = 0; i < 5; i++) {
        tick(top, tfp);
    }
    top->rst = 0;
    tick(top, tfp);

    for (int test = 0; test < num_tests; test++) {
        // Generate random trits and activations
        int trits[TILE_SIZE];
        uint8_t activations[TILE_SIZE];
        for (int i = 0; i < TILE_SIZE; i++) {
            trits[i] = trit_dist(gen);
            activations[i] = act_dist(gen);
        }

        // Encode trits to packed bytes
        int64_t encoded = encoder.encode(trits, TILE_SIZE);
        if (encoded < 0) {
            printf("Test %d: ERROR - Failed to encode trits\n", test);
            continue;
        }

        // Compute expected result in software
        int8_t expected_sum = sw_dot_product(trits, activations, TILE_SIZE);

        // Apply inputs
        top->weight_fifo_in = encoded;
        for (int i = 0; i < TILE_SIZE; i++) {
            top->activations_in[i] = activations[i];
        }
        top->weight_fifo_valid = 1;
        top->activations_valid = 1;
        tick(top, tfp);
        
        // Deassert valid after one cycle
        top->weight_fifo_valid = 0;

        // Wait for pipeline to produce result
        int cycles = 0;
        while (!top->sum_out_valid && cycles < PIPELINE_LATENCY + 5) {
            tick(top, tfp);
            cycles++;
        }

        if (!top->sum_out_valid) {
            printf("Test %d: ERROR - sum_out_valid never asserted after %d cycles\n", test, cycles);
            errors++;
            continue;
        }

        // Check result
        int8_t hw_sum = (int8_t)top->sum_out;
        
        if (hw_sum != expected_sum) {
            printf("Test %d: MISMATCH - Expected sum=%d, Got sum=%d (after %d cycles)\n", 
                   test, expected_sum, hw_sum, cycles);
            printf("  Trits: [");
            for (int i = 0; i < TILE_SIZE; i++) printf("%d ", trits[i]);
            printf("]\n  Activations: [");
            for (int i = 0; i < TILE_SIZE; i++) printf("%d ", (int8_t)activations[i]);
            printf("]\n");
            errors++;
        } else {
            printf("Test %d: PASS - sum=%d (after %d cycles)\n", test, hw_sum, cycles);
        }

        // Let the pipeline drain
        for (int i = 0; i < 2; i++) {
            tick(top, tfp);
        }
    }

    printf("\n%d/%d tests passed\n", num_tests - errors, num_tests);

    // Cleanup
    tfp->close();
    delete tfp;
    delete top;
    return errors;
}
