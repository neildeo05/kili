#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

using namespace std;

vluint64_t sim_time = 0;
double sc_time_stamp() { return sim_time; }

void tick(Vtop* dut, VerilatedVcdC* tfp) {
    dut->clk = 0;
    dut->eval();
    if (tfp) tfp->dump(sim_time++);
    
    dut->clk = 1;
    dut->eval();
    if (tfp) tfp->dump(sim_time++);
}

void reset(Vtop* dut, VerilatedVcdC* tfp) {
    dut->rst = 1;
    dut->in_burst_valid = 0;
    dut->in_burst_addr = 0;
    dut->in_burst_len = 0;
    for (int i = 0; i < 5; i++) tick(dut, tfp);
    dut->rst = 0;
    tick(dut, tfp);
}

int main() {
    Verilated::traceEverOn(true);
    
    Vtop* dut = new Vtop;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("top_waveform.vcd");

    int errors = 0;

    // ========== Test 1: Simple burst read ==========
    reset(dut, tfp);
    dut->activations_valid = 1;
    for (int i = 0; i < 16; i++) {
        dut->activations_in[i] = 0x02020202;
    }
    tick(dut, tfp);

    dut->activations_valid = 0;
    dut->in_burst_valid = 1;
    dut->in_burst_addr = 0;
    dut->in_burst_len = 63;
    tick(dut, tfp);
    dut->in_burst_valid = 0;
    tick(dut, tfp);
    // dut->in_burst_addr = 0;
    // dut->in_burst_len = 63;
    // dut->in_burst_valid = 1;
    // tick(dut, tfp);
    // dut->in_burst_valid = 0;
    // tick(dut, tfp);


    printf("  Running burst...\n");
    for (int i = 0; i < 100; i++) {
        tick(dut, tfp);
    }

    tfp->close();
    delete tfp;
    delete dut;
    return errors;
}
// #include <stdlib.h>
// #include <stdint.h>
// #include <iostream>
// #include <random>
// #include <unordered_map>

// #include "verilated.h"
// #include "verilated_vcd_c.h"
// #include "Vtop.h"
// #include "Vternary_decoder.h"

// using namespace std;

// #ifndef TILE_SIZE
//     #define TILE_SIZE 8
// #endif

// #ifndef NUM_TILES
//     #define NUM_TILES 8
// #endif

// // Trit packing: 5 trits per byte
// constexpr int TRIT_PACK = 5;
// // Number of bytes needed to encode TILE_SIZE trits
// constexpr int ENCODED_BYTES = (TILE_SIZE + TRIT_PACK - 1) / TRIT_PACK;

// // Global simulation time for VCD
// vluint64_t sim_time = 0;
// double sc_time_stamp() { return sim_time; }

// // Trit encoding: -1 → 0b11, 0 → 0b00, +1 → 0b01
// constexpr uint8_t TRIT_NEG  = 0b11;
// constexpr uint8_t TRIT_ZERO = 0b00;
// constexpr uint8_t TRIT_POS  = 0b01;

// // Decoder class to convert encoded bytes back to trits
// class TernaryDecoder {
// private:
//     Vternary_decoder* decoder;

// public:
//     TernaryDecoder() {
//         decoder = new Vternary_decoder;
//     }

//     ~TernaryDecoder() { delete decoder; }

//     static int bits_to_trit(uint8_t b) {
//         return (b == TRIT_NEG) ? -1 : (b == TRIT_POS) ? 1 : 0;
//     }

//     // Decode a single byte to up to 5 trits
//     void decode_byte(uint8_t encoded, int* trits, int num_trits) {
//         decoder->encoded_vals = encoded;
//         decoder->eval();
//         uint16_t decoded = decoder->decoded_vals;
        
//         for (int i = 0; i < num_trits && i < TRIT_PACK; i++) {
//             uint8_t trit_bits = (decoded >> (2 * i)) & 0x3;
//             trits[i] = bits_to_trit(trit_bits);
//         }
//     }

//     // Decode multiple bytes to TILE_SIZE trits
//     void decode(uint8_t* encoded_bytes, int* trits) {
//         int trit_idx = 0;
//         for (int byte_idx = 0; byte_idx < ENCODED_BYTES && trit_idx < TILE_SIZE; byte_idx++) {
//             int remaining = TILE_SIZE - trit_idx;
//             int to_decode = (remaining < TRIT_PACK) ? remaining : TRIT_PACK;
//             decode_byte(encoded_bytes[byte_idx], &trits[trit_idx], to_decode);
//             trit_idx += to_decode;
//         }
//     }
// };

// // Software reference: multiply activation by trit
// int sw_tmul(int8_t activation, int trit) {
//     if (trit == 1)  return activation;
//     if (trit == -1) return -activation;
//     return 0;
// }

// // Compute expected dot product in software
// int sw_dot_product(int* trits, int8_t* activations) {
//     int sum = 0;
//     for (int i = 0; i < TILE_SIZE; i++) {
//         sum += sw_tmul(activations[i], trits[i]);
//     }
//     return sum;
// }

// // Clock the design with VCD tracing
// void tick(Vtop* dut, VerilatedVcdC* tfp) {
//     dut->clk = 0;
//     dut->eval();
//     if (tfp) tfp->dump(sim_time++);
    
//     dut->clk = 1;
//     dut->eval();
//     if (tfp) tfp->dump(sim_time++);
// }

// // Pack activations into the 512-bit wide input
// // Layout: activations_in[NUM_TILES-1:0][TILE_SIZE-1:0][7:0]
// // This is 8 tiles × 8 elements × 8 bits = 512 bits = 16 × 32-bit words
// void pack_activations(Vtop* dut, int8_t activations[NUM_TILES][TILE_SIZE]) {
//     // Clear all words first
//     for (int i = 0; i < 16; i++) {
//         dut->activations_in[i] = 0;
//     }
    
//     // Pack: bit position = tile * TILE_SIZE * 8 + elem * 8
//     // Each 32-bit word holds 4 bytes
//     for (int tile = 0; tile < NUM_TILES; tile++) {
//         for (int elem = 0; elem < TILE_SIZE; elem++) {
//             int bit_pos = tile * TILE_SIZE * 8 + elem * 8;
//             int word_idx = bit_pos / 32;
//             int bit_offset = bit_pos % 32;
//             dut->activations_in[word_idx] |= ((uint32_t)(uint8_t)activations[tile][elem]) << bit_offset;
//         }
//     }
// }

// // Unpack dot_out from 64-bit value to 8 × 8-bit signed results
// void unpack_dot_out(uint64_t dot_out, int8_t* results) {
//     for (int i = 0; i < TILE_SIZE; i++) {
//         results[i] = (int8_t)((dot_out >> (i * 8)) & 0xFF);
//     }
// }

// // Extract weight bytes for a specific dot unit from a 128-bit memory word
// // Memory layout: weight_fifo_in[TILE_SIZE-1:0][ENCODED_BYTES-1:0][7:0]
// // Total: 8 dot units × 2 bytes = 16 bytes = 128 bits
// void extract_weights_for_dot_unit(uint64_t mem_lo, uint64_t mem_hi, int dot_unit, uint8_t* weights) {
//     __uint128_t mem_word = ((__uint128_t)mem_hi << 64) | mem_lo;
//     int bit_offset = dot_unit * ENCODED_BYTES * 8;
    
//     for (int i = 0; i < ENCODED_BYTES; i++) {
//         weights[i] = (mem_word >> (bit_offset + i * 8)) & 0xFF;
//     }
// }

// void reset(Vtop* dut, VerilatedVcdC* tfp) {
//     dut->rst = 1;
//     dut->activations_valid = 0;
//     dut->in_burst_valid = 0;
//     dut->in_burst_addr = 0;
//     dut->in_burst_len = 0;
    
//     // Clear activations
//     for (int i = 0; i < 16; i++) {
//         dut->activations_in[i] = 0;
//     }
    
//     for (int i = 0; i < 5; i++) tick(dut, tfp);
//     dut->rst = 0;
//     tick(dut, tfp);
// }

// int main() {
//     mt19937 gen(42);  // Fixed seed for reproducibility
//     uniform_int_distribution<> act_dist(-128, 127);
    
//     Verilated::traceEverOn(true);
    
//     TernaryDecoder decoder;
//     Vtop* dut = new Vtop;
//     VerilatedVcdC* tfp = new VerilatedVcdC;
//     dut->trace(tfp, 99);
//     tfp->open("top_waveform.vcd");

//     int errors = 0;
//     int num_tests = 10;

//     printf("Testing dot product outputs (pre-accumulation)\n");
//     printf("TILE_SIZE=%d, NUM_TILES=%d, ENCODED_BYTES=%d\n\n", TILE_SIZE, NUM_TILES, ENCODED_BYTES);

//     for (int test = 0; test < num_tests; test++) {
//         printf("=== Test %d ===\n", test);
//         reset(dut, tfp);

//         // Generate random activations (8x8 matrix, signed 8-bit)
//         int8_t activations[NUM_TILES][TILE_SIZE];
//         for (int tile = 0; tile < NUM_TILES; tile++) {
//             for (int elem = 0; elem < TILE_SIZE; elem++) {
//                 activations[tile][elem] = act_dist(gen);
//             }
//         }
//         // Pack and load activations
//         pack_activations(dut, activations);
//         dut->activations_valid = 1;
//         tick(dut, tfp);
//         dut->activations_valid = 0;
//         tick(dut, tfp);

//         // Use a single memory row for this test (row = test % 64)
//         int mem_row = test % 64;
        
//         // Initiate burst read (single row)
//         dut->in_burst_addr = mem_row;
//         dut->in_burst_len = 0;  // len=0 means 1 word
//         dut->in_burst_valid = 1;
//         tick(dut, tfp);
//         dut->in_burst_valid = 0;

//         // Memory is initialized with mem[i] = 128'(i)
//         // So mem[row] = row as a 128-bit value
//         uint64_t mem_lo = mem_row;
//         uint64_t mem_hi = 0;

//         // Compute expected dot products
//         // The activations used are from chunk 0 (first tile of activations)
//         // Based on tensor_unit.sv, chunk_index starts at 0 and increments
//         int expected_dots[TILE_SIZE];
//         for (int dot_unit = 0; dot_unit < TILE_SIZE; dot_unit++) {
//             uint8_t weight_bytes[ENCODED_BYTES];
//             extract_weights_for_dot_unit(mem_lo, mem_hi, dot_unit, weight_bytes);
            
//             int trits[TILE_SIZE];
//             decoder.decode(weight_bytes, trits);
            
//             expected_dots[dot_unit] = sw_dot_product(trits, activations[0]);
//         }


//         // Wait for dot_out_valid
//         int cycles = 0;
//         int max_cycles = 50;
//         while (!dut->dot_out_valid && cycles < max_cycles) {
//             tick(dut, tfp);
//             cycles++;
//         }

//         if (!dut->dot_out_valid) {
//             printf("  ERROR: dot_out_valid never asserted after %d cycles\n", cycles);
//             errors++;
//             continue;
//         }

//         printf("  dot_out_valid after %d cycles\n", cycles);

//         // Unpack and check results
//         int8_t hw_results[TILE_SIZE];
//         unpack_dot_out(dut->dot_out, hw_results);

//         int test_errors = 0;
//         for (int i = 0; i < TILE_SIZE; i++) {
//             int8_t expected = (int8_t)expected_dots[i];
            
//             if (hw_results[i] != expected) {
//                 printf("  MISMATCH dot_out[%d]: expected=%d, got=%d\n", i, expected, hw_results[i]);
//                 test_errors++;
//             }
//         }

//         if (test_errors == 0) {
//             printf("  PASS: all %d dot products match\n", TILE_SIZE);
//         } else {
//             printf("  FAIL: %d/%d mismatches\n", test_errors, TILE_SIZE);
//             errors++;
//         }

//         // Let pipeline drain
//         for (int i = 0; i < 10; i++) {
//             tick(dut, tfp);
//         }
//     }

//     printf("\n%d/%d tests passed\n", num_tests - errors, num_tests);

//     tfp->close();
//     delete tfp;
//     delete dut;
//     return errors;
// }
