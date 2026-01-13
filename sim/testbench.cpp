#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <random>
#include <unordered_map>

#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vternary_decoder.h"
#include "Vtmatmul.h"

using namespace std;

#ifndef TILE_SIZE
    #define TILE_SIZE 4
#endif

#ifndef TRIT_PACK
    #define TRIT_PACK 5
#endif

#define NUM_TILES ((TILE_SIZE + TRIT_PACK - 1) / TRIT_PACK)

// Calculate bit widths
constexpr int ACTIVATION_BITS = TILE_SIZE * 8;
constexpr int WEIGHT_BITS = TILE_SIZE * NUM_TILES * 8;
constexpr int DOT_OUT_BITS = TILE_SIZE * 8;

// Pipeline latency: decode(1) + multiply(1) + reduction(log2(TILE_SIZE))
constexpr int PIPELINE_LATENCY = 2 + 3;

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

    // Encode a row of trits into NUM_TILES bytes
    bool encode_row(int* trits, int num_trits, uint8_t* output) {
        int num_tiles = (num_trits + TRIT_PACK - 1) / TRIT_PACK;
        
        for (int tile = 0; tile < num_tiles; tile++) {
            int start = tile * TRIT_PACK;
            int end = std::min(start + TRIT_PACK, num_trits);
            
            uint16_t packed = 0;
            for (int i = start; i < end; ++i) {
                packed |= trit_to_bits(trits[i]) << (2 * (i - start));
            }
            
            auto it = trit_to_byte.find(packed);
            if (it == trit_to_byte.end()) {
                printf("Failed to encode tile %d, packed=%x\n", tile, packed);
                return false;
            }
            
            output[tile] = it->second;
        }
        return true;
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
void tick(Vtmatmul* top, VerilatedVcdC* tfp) {
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
        printf("activations[%d] = %d, trits[%d] = %d\n", i, activations[i], i, trits[i]);
        sum += sw_tmul(activations[i], trits[i]);
    }
    return (int8_t)sum;
}

// Pack activations into the appropriate type based on TILE_SIZE
// For TILE_SIZE <= 4: 32-bit, for TILE_SIZE <= 8: 64-bit
#if TILE_SIZE <= 4
typedef uint32_t activation_t;
typedef uint32_t weight_t;
typedef uint32_t dot_out_t;
#else
typedef uint64_t activation_t;
typedef uint32_t weight_t[4];  // 128-bit as 4 words
typedef uint64_t dot_out_t;
#endif

activation_t pack_activations(uint8_t* activations) {
#if TILE_SIZE <= 4
    uint32_t packed = 0;
    for (int i = 0; i < TILE_SIZE; i++) {
        packed |= ((uint32_t)activations[i]) << (8 * i);
    }
    return packed;
#else
    uint64_t packed = 0;
    for (int i = 0; i < TILE_SIZE; i++) {
        packed |= ((uint64_t)activations[i]) << (8 * i);
    }
    return packed;
#endif
}

void unpack_dot_out(dot_out_t packed, int8_t* results) {
    for (int i = 0; i < TILE_SIZE; i++) {
        results[i] = (int8_t)((packed >> (8 * i)) & 0xFF);
    }
}

// Pack weight_fifo_in
// Layout: row 0 tiles in lowest bits, then row 1, etc.
#if TILE_SIZE <= 4
weight_t pack_weights(uint8_t encoded_weights[TILE_SIZE][NUM_TILES]) {
    uint32_t packed = 0;
    for (int row = 0; row < TILE_SIZE; row++) {
        for (int tile = 0; tile < NUM_TILES; tile++) {
            int bit_pos = (row * NUM_TILES + tile) * 8;
            packed |= ((uint32_t)encoded_weights[row][tile]) << bit_pos;
        }
    }
    return packed;
}
#else
void pack_weights(uint8_t encoded_weights[TILE_SIZE][NUM_TILES], uint32_t* weight_words) {
    for (int w = 0; w < 4; w++) {
        weight_words[w] = 0;
    }
    for (int row = 0; row < TILE_SIZE; row++) {
        for (int tile = 0; tile < NUM_TILES; tile++) {
            int bit_pos = (row * NUM_TILES + tile) * 8;
            int word_idx = bit_pos / 32;
            int bit_in_word = bit_pos % 32;
            weight_words[word_idx] |= ((uint32_t)encoded_weights[row][tile]) << bit_in_word;
        }
    }
}
#endif

int main() {
    mt19937 gen(42);  // Fixed seed for reproducibility
    uniform_int_distribution<> trit_dist(-1, 1);
    uniform_int_distribution<> act_dist(0, 255);

    // Initialize Verilator
    Verilated::traceEverOn(true);

    TernaryEncoder encoder;
    Vtmatmul* top = new Vtmatmul;

    // Setup VCD tracing
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace(tfp, 99);
    tfp->open("tmatmul_waveform.vcd");

    int num_tests = 3;
    int errors = 0;

    printf("Testing tmatmul: %dx%d matrix-vector multiplication\n", TILE_SIZE, TILE_SIZE);
    printf("Running %d tests with TILE_SIZE=%d, NUM_TILES=%d, pipeline latency=%d cycles\n\n", 
           num_tests, TILE_SIZE, NUM_TILES, PIPELINE_LATENCY);

    // Reset the design
    top->clk = 0;
    top->rst = 1;
    top->weight_fifo_valid = 0;
    top->activations_valid = 0;
    top->activations_in = 0;
    top->weight_fifo_in = 0;
    
    // Hold reset for a few cycles
    for (int i = 0; i < 5; i++) {
        tick(top, tfp);
    }
    top->rst = 0;
    tick(top, tfp);

    for (int test = 0; test < num_tests; test++) {
        // Generate random weight matrix and activation vector
        int weight_matrix[TILE_SIZE][TILE_SIZE];
        uint8_t activations[TILE_SIZE];
        int8_t expected_results[TILE_SIZE];
        
        for (int row = 0; row < TILE_SIZE; row++) {
            for (int col = 0; col < TILE_SIZE; col++) {
                weight_matrix[row][col] = trit_dist(gen);
            }
        }
        printf("weight_matrix:\n");
        for(int i = 0; i < TILE_SIZE; i++) {
            for(int j = 0; j < TILE_SIZE; j++) {
                printf("%d ", weight_matrix[i][j]);
            }
            printf("\n");
        }
        printf("activations:\n");
        for (int i = 0; i < TILE_SIZE; i++) {
            activations[i] = act_dist(gen);
        }
        for(int i = 0; i < TILE_SIZE; i++) {
            printf("%d ", activations[i]);
        }
        printf("\n");

        // Compute expected results in software
        for (int row = 0; row < TILE_SIZE; row++) {
            expected_results[row] = sw_dot_product(weight_matrix[row], activations, TILE_SIZE);
        }
        printf("expected_results:\n");
        for(int i = 0; i < TILE_SIZE; i++) {
            printf("%d ", expected_results[i]);
        }
        printf("\n");

        // Encode weight matrix rows
        uint8_t encoded_weights[TILE_SIZE][NUM_TILES];
        bool encode_ok = true;
        for (int row = 0; row < TILE_SIZE; row++) {
            if (!encoder.encode_row(weight_matrix[row], TILE_SIZE, encoded_weights[row])) {
                printf("Test %d: ERROR - Failed to encode weight row %d\n", test, row);
                encode_ok = false;
                break;
            }
        }
        if (!encode_ok) {
            errors++;
            continue;
        }

        // Pack and apply inputs to hardware
#if TILE_SIZE <= 4
        top->weight_fifo_in = pack_weights(encoded_weights);
#else
        uint32_t weight_words[4];
        pack_weights(encoded_weights, weight_words);
        for (int w = 0; w < 4; w++) {
            top->weight_fifo_in[w] = weight_words[w];
        }
#endif
        
        top->activations_in = pack_activations(activations);
        top->weight_fifo_valid = 1;
        top->activations_valid = 1;
        tick(top, tfp);
        
        // Deassert valid after one cycle
        top->weight_fifo_valid = 0;
        top->activations_valid = 0;

        // Wait for pipeline to produce result
        int cycles = 0;
        while (!top->dot_out_valid && cycles < PIPELINE_LATENCY + 5) {
            tick(top, tfp);
            cycles++;
        }

        if (!top->dot_out_valid) {
            printf("Test %d: ERROR - dot_out_valid never asserted after %d cycles\n", test, cycles);
            errors++;
            continue;
        }

        // Unpack and check all results
        int8_t hw_results[TILE_SIZE];
        printf("top->dot_out = %x\n", top->dot_out);
        unpack_dot_out(top->dot_out, hw_results);

        printf("hw_results:\n");
        for(int i = 0; i < TILE_SIZE; i++) {
            printf("%d ", hw_results[i]);
        }
        printf("\n");
        bool test_pass = true;
        for (int row = 0; row < TILE_SIZE; row++) {
            if (hw_results[row] != expected_results[row]) {
                if (test_pass) {
                    printf("Test %d: MISMATCH (after %d cycles)\n", test, cycles);
                }
                printf("  Row %d: Expected=%d, Got=%d\n", row, expected_results[row], hw_results[row]);
                printf("    Weights: [");
                for (int col = 0; col < TILE_SIZE; col++) printf("%d ", weight_matrix[row][col]);
                printf("]\n");
                test_pass = false;
            }
        }
        
        if (!test_pass) {
            printf("  Activations: [");
            for (int i = 0; i < TILE_SIZE; i++) printf("%d ", (int)activations[i]);
            printf("]\n");
            errors++;
        } else {
            printf("Test %d: PASS - all %d dot products correct (after %d cycles)\n", 
                   test, TILE_SIZE, cycles);
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
