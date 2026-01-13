/**
 * test_top_system.cpp - Comprehensive testbench for ternary matrix-vector multiply
 * 
 * Architecture Overview:
 * ----------------------
 * The top module implements a ternary dot product accelerator with:
 *   - 4 activation inputs (8-bit unsigned each, 32 bits total)
 *   - 4 weight bytes (each byte = 4 x 2-bit trits, one per dot product unit)
 *   - 4 parallel dot product units, each computing: sum(activation[i] * trit[i])
 *   - Result: 4 x 8-bit outputs streamed byte-by-byte while result_valid is HIGH
 * 
 * Trit Encoding (2 bits per trit, 4 trits per byte):
 *   0b00 = 0
 *   0b01 = +1
 *   0b10 = 0 (treated as 0)
 *   0b11 = -1
 * 
 * Result Output Protocol:
 *   - When dot_out_valid goes HIGH, result_byte_valid follows (1 cycle later)
 *   - While result_byte_valid is HIGH, uo_out outputs one byte per cycle
 *   - Byte order: dot_out[7:0], dot_out[15:8], dot_out[23:16], dot_out[31:24]
 *   - Each byte is the result of one dot product unit
 * 
 * Interface (Tiny Tapeout style):
 *   ui_in[7:0]   - Data input (shared for activation/weight bytes)
 *   uo_out[7:0]  - Result output (streamed byte-by-byte)
 *   uio_in[7:0]  - Control: [0]=activation_valid, [1]=weight_valid
 *   uio_out[7:0] - Status: [2]=act_ready, [3]=wgt_ready, [4]=result_valid, [5]=matmul_valid
 */

#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <random>
#include <cmath>

#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

using namespace std;

vluint64_t sim_time = 0;
double sc_time_stamp() { return sim_time; }

int test_num = 0;
int total_errors = 0;

// ============================================================================
// Trit Encoding Constants
// ============================================================================
const uint8_t TRIT_ZERO = 0b00;
const uint8_t TRIT_POS  = 0b01;
const uint8_t TRIT_NEG  = 0b11;

// ============================================================================
// Testbench Infrastructure
// ============================================================================

void tick(Vtop* dut, VerilatedVcdC* tfp) {
    dut->clk = 0;
    dut->eval();
    if (tfp) tfp->dump(sim_time++);
    
    dut->clk = 1;
    dut->eval();
    if (tfp) tfp->dump(sim_time++);
}

void reset(Vtop* dut, VerilatedVcdC* tfp) {
    dut->rst_n = 0;
    dut->ena = 1;
    dut->ui_in = 0;
    dut->uio_in = 0;
    for (int i = 0; i < 10; i++) tick(dut, tfp);
    dut->rst_n = 1;
    tick(dut, tfp);
}

bool check(bool condition, const string& msg) {
    if (!condition) {
        cout << "  [FAIL] " << msg << endl;
        total_errors++;
        return false;
    }
    cout << "  [PASS] " << msg << endl;
    return true;
}

void start_test(const string& name) {
    test_num++;
    cout << "\n========== Test " << test_num << ": " << name << " ==========" << endl;
}

// ============================================================================
// Signal Accessors
// ============================================================================

void set_activation_valid(Vtop* dut, bool valid) {
    if (valid) dut->uio_in |= 0x01;
    else dut->uio_in &= ~0x01;
}

void set_weight_valid(Vtop* dut, bool valid) {
    if (valid) dut->uio_in |= 0x02;
    else dut->uio_in &= ~0x02;
}

bool get_activation_ready(Vtop* dut) { return (dut->uio_out >> 2) & 0x01; }
bool get_weight_ready(Vtop* dut) { return (dut->uio_out >> 3) & 0x01; }
bool get_result_valid(Vtop* dut) { return (dut->uio_out >> 4) & 0x01; }
bool get_matmul_valid(Vtop* dut) { return (dut->uio_out >> 5) & 0x01; }
uint8_t get_result(Vtop* dut) { return dut->uo_out; }

// ============================================================================
// Helper Functions
// ============================================================================

/**
 * Convert integer trit (-1, 0, +1) to 2-bit encoding
 */
uint8_t trit_to_bits(int t) {
    if (t == 1) return TRIT_POS;
    if (t == -1) return TRIT_NEG;
    return TRIT_ZERO;
}

/**
 * Pack 4 trits into a single byte
 * Layout: [trit3:trit2:trit1:trit0] where each trit is 2 bits
 */
uint8_t pack_trits(int t0, int t1, int t2, int t3) {
    return trit_to_bits(t0) | 
           (trit_to_bits(t1) << 2) | 
           (trit_to_bits(t2) << 4) | 
           (trit_to_bits(t3) << 6);
}

/**
 * Unpack 4 trits from a byte
 */
void unpack_trits(uint8_t byte, int trits[4]) {
    for (int i = 0; i < 4; i++) {
        uint8_t bits = (byte >> (2*i)) & 0x03;
        if (bits == TRIT_POS) trits[i] = 1;
        else if (bits == TRIT_NEG) trits[i] = -1;
        else trits[i] = 0;
    }
}

/**
 * Software reference: compute dot product of activations with trits
 * Returns signed 8-bit result (matching hardware behavior)
 */
int8_t sw_dot_product(uint8_t acts[4], int trits[4]) {
    int32_t sum = 0;
    for (int i = 0; i < 4; i++) {
        if (trits[i] == 1) sum += acts[i];
        else if (trits[i] == -1) sum -= acts[i];
    }
    return (int8_t)(sum & 0xFF);  // Truncate to 8 bits
}

/**
 * Send a byte to the activation buffer
 */
void send_activation_byte(Vtop* dut, VerilatedVcdC* tfp, uint8_t byte) {
    dut->ui_in = byte;
    set_activation_valid(dut, true);
    set_weight_valid(dut, false);
    tick(dut, tfp);
    set_activation_valid(dut, false);
}

/**
 * Send a byte to the weight buffer
 */
void send_weight_byte(Vtop* dut, VerilatedVcdC* tfp, uint8_t byte) {
    dut->ui_in = byte;
    set_activation_valid(dut, false);
    set_weight_valid(dut, true);
    tick(dut, tfp);
    set_weight_valid(dut, false);
}

/**
 * Collect all result bytes while result_valid is HIGH
 * Returns number of bytes collected (should be 4 for a complete operation)
 */
int collect_results(Vtop* dut, VerilatedVcdC* tfp, uint8_t results[4], int max_wait = 100) {
    // Wait for result_valid to go HIGH
    int wait = 0;
    while (!get_result_valid(dut) && wait < max_wait) {
        tick(dut, tfp);
        wait++;
    }
    
    if (!get_result_valid(dut)) {
        return 0;  // Timeout
    }
    
    // Collect bytes while result_valid is HIGH
    int count = 0;
    while (get_result_valid(dut) && count < 4) {
        results[count++] = get_result(dut);
        tick(dut, tfp);
    }
    
    return count;
}

/**
 * Perform a complete matrix-vector multiply operation:
 * 1. Send 4 activation bytes
 * 2. Send 4 weight bytes  
 * 3. Wait for and collect all 4 result bytes
 * Returns the number of result bytes collected
 */
int do_matmul(Vtop* dut, VerilatedVcdC* tfp,
              uint8_t acts[4], uint8_t weights[4],
              uint8_t results[4], int max_wait = 100) {
    // Send activations
    for (int i = 0; i < 4; i++) {
        send_activation_byte(dut, tfp, acts[i]);
    }
    tick(dut, tfp);
    
    // Send weights
    for (int i = 0; i < 4; i++) {
        send_weight_byte(dut, tfp, weights[i]);
    }
    tick(dut, tfp);
    
    // Wait for matmul_valid (both buffers full)
    int wait = 0;
    while (!get_matmul_valid(dut) && wait < max_wait) {
        tick(dut, tfp);
        wait++;
    }
    
    // Collect all result bytes
    int num_results = collect_results(dut, tfp, results, max_wait);
    
    // Let system settle
    tick(dut, tfp);
    
    return num_results;
}

/**
 * Compute expected results for all 4 dot product units
 * Each weight byte (weights[i]) contains the 4 trits for dot unit i
 */
void compute_expected_results(uint8_t acts[4], uint8_t weights[4], int8_t expected[4]) {
    for (int unit = 0; unit < 4; unit++) {
        int trits[4];
        unpack_trits(weights[unit], trits);
        expected[unit] = sw_dot_product(acts, trits);
    }
}

// ============================================================================
// TEST 1: Initial State After Reset
// ============================================================================
void test_initial_state(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Initial state after reset");
    reset(dut, tfp);
    
    check(get_activation_ready(dut) == true, 
          "activation_buffer_ready should be HIGH");
    check(get_weight_ready(dut) == true, 
          "weight_buffer_ready should be HIGH");
    check(get_matmul_valid(dut) == false, 
          "matmul_valid should be LOW (no data)");
    check(get_result_valid(dut) == false, 
          "result_byte_valid should be LOW");
    check(dut->uio_oe == 0b00111100, 
          "uio_oe should be 0b00111100");
}

// ============================================================================
// TEST 2: Simple Dot Product - All Positive Trits
// ============================================================================
void test_simple_all_positive(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Simple dot product - all positive trits");
    reset(dut, tfp);
    
    uint8_t acts[4] = {1, 2, 3, 4};
    // All 4 dot units get same trits: [+1, +1, +1, +1]
    uint8_t weights[4] = {
        pack_trits(1, 1, 1, 1),
        pack_trits(1, 1, 1, 1),
        pack_trits(1, 1, 1, 1),
        pack_trits(1, 1, 1, 1)
    };
    
    uint8_t results[4];
    int8_t expected[4];
    compute_expected_results(acts, weights, expected);
    
    int num_results = do_matmul(dut, tfp, acts, weights, results);
    
    cout << "  Activations: [1, 2, 3, 4], Trits: [+1,+1,+1,+1]" << endl;
    cout << "  Received " << num_results << " result bytes" << endl;
    
    check(num_results == 4, "Should receive 4 result bytes");
    
    bool all_correct = true;
    for (int i = 0; i < num_results; i++) {
        cout << "    Result[" << i << "]: expected=" << (int)expected[i] 
             << ", got=" << (int)(int8_t)results[i] << endl;
        if (results[i] != (uint8_t)expected[i]) all_correct = false;
    }
    
    check(all_correct, "All results should match expected (sum = 10)");
}

// ============================================================================
// TEST 3: Different Weights Per Dot Unit
// ============================================================================
void test_different_weights_per_unit(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Different weights per dot unit");
    reset(dut, tfp);
    
    uint8_t acts[4] = {10, 20, 30, 40};
    // Each dot unit gets different trits
    uint8_t weights[4] = {
        pack_trits(1, 1, 1, 1),    // Unit 0: all +1 -> 10+20+30+40 = 100
        pack_trits(-1, -1, -1, -1),// Unit 1: all -1 -> -(10+20+30+40) = -100
        pack_trits(1, 0, -1, 0),   // Unit 2: 10 - 30 = -20
        pack_trits(0, 0, 0, 0)     // Unit 3: all 0 -> 0
    };
    
    uint8_t results[4];
    int8_t expected[4];
    compute_expected_results(acts, weights, expected);
    
    int num_results = do_matmul(dut, tfp, acts, weights, results);
    
    cout << "  Activations: [10, 20, 30, 40]" << endl;
    cout << "  Weight[0]: [+1,+1,+1,+1] -> 100" << endl;
    cout << "  Weight[1]: [-1,-1,-1,-1] -> -100" << endl;
    cout << "  Weight[2]: [+1,0,-1,0] -> -20" << endl;
    cout << "  Weight[3]: [0,0,0,0] -> 0" << endl;
    
    check(num_results == 4, "Should receive 4 result bytes");
    
    bool all_correct = true;
    for (int i = 0; i < num_results; i++) {
        cout << "    Result[" << i << "]: expected=" << (int)expected[i] 
             << ", got=" << (int)(int8_t)results[i] << endl;
        if (results[i] != (uint8_t)expected[i]) all_correct = false;
    }
    
    check(all_correct, "All 4 dot products should be correct");
}

// ============================================================================
// TEST 4: Zero Activations
// ============================================================================
void test_zero_activations(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Zero activations");
    reset(dut, tfp);
    
    uint8_t acts[4] = {0, 0, 0, 0};
    uint8_t weights[4] = {
        pack_trits(1, -1, 1, -1),
        pack_trits(-1, 1, -1, 1),
        pack_trits(1, 1, 1, 1),
        pack_trits(-1, -1, -1, -1)
    };
    
    uint8_t results[4];
    int num_results = do_matmul(dut, tfp, acts, weights, results);
    
    check(num_results == 4, "Should receive 4 result bytes");
    
    bool all_zero = true;
    for (int i = 0; i < num_results; i++) {
        if (results[i] != 0) all_zero = false;
    }
    
    check(all_zero, "Zero activations should produce all zero results");
}

// ============================================================================
// TEST 5: Maximum Values (Overflow Test)
// ============================================================================
void test_overflow(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Maximum values (overflow behavior)");
    reset(dut, tfp);
    
    uint8_t acts[4] = {255, 255, 255, 255};
    uint8_t weights[4] = {
        pack_trits(1, 1, 1, 1),    // +1020, truncated to 8 bits = 0xFC
        pack_trits(-1, -1, -1, -1),// -1020, truncated = 0x04
        pack_trits(1, 1, 0, 0),    // +510, truncated = 0xFE
        pack_trits(-1, 0, 0, -1)   // -510, truncated = 0x02
    };
    
    uint8_t results[4];
    int8_t expected[4];
    compute_expected_results(acts, weights, expected);
    
    int num_results = do_matmul(dut, tfp, acts, weights, results);
    
    cout << "  Activations: [255, 255, 255, 255]" << endl;
    
    check(num_results == 4, "Should receive 4 result bytes");
    
    bool all_correct = true;
    for (int i = 0; i < num_results; i++) {
        cout << "    Result[" << i << "]: expected=0x" << hex << (int)(uint8_t)expected[i] 
             << ", got=0x" << (int)results[i] << dec << endl;
        if (results[i] != (uint8_t)expected[i]) all_correct = false;
    }
    
    check(all_correct, "Overflow should truncate to 8 bits correctly");
}

// ============================================================================
// TEST 6: Back-to-Back Operations
// ============================================================================
void test_back_to_back(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Back-to-back operations (3 sequential)");
    reset(dut, tfp);
    
    bool all_passed = true;
    
    for (int round = 0; round < 3; round++) {
        uint8_t acts[4] = {
            (uint8_t)(10 + round*10),
            (uint8_t)(20 + round*10),
            (uint8_t)(30 + round*10),
            (uint8_t)(40 + round*10)
        };
        uint8_t weights[4] = {
            pack_trits(1, 1, 1, 1),
            pack_trits(-1, -1, -1, -1),
            pack_trits(1, -1, 1, -1),
            pack_trits(0, 1, 0, -1)
        };
        
        uint8_t results[4];
        int8_t expected[4];
        compute_expected_results(acts, weights, expected);
        
        int num_results = do_matmul(dut, tfp, acts, weights, results);
        
        cout << "  Round " << (round+1) << ": ";
        if (num_results != 4) {
            cout << "Only got " << num_results << " results!" << endl;
            all_passed = false;
            continue;
        }
        
        bool round_ok = true;
        for (int i = 0; i < 4; i++) {
            if (results[i] != (uint8_t)expected[i]) round_ok = false;
        }
        cout << (round_ok ? "OK" : "MISMATCH") << endl;
        if (!round_ok) all_passed = false;
        
        // Check buffers ready for next operation
        if (!get_activation_ready(dut) || !get_weight_ready(dut)) {
            cout << "    WARNING: Buffers not ready!" << endl;
            all_passed = false;
        }
    }
    
    check(all_passed, "All back-to-back operations should pass");
}

// ============================================================================
// TEST 7: Randomized Stress Test
// ============================================================================
void test_random_stress(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Randomized stress test (20 operations)");
    reset(dut, tfp);
    
    mt19937 gen(42);
    uniform_int_distribution<> act_dist(0, 255);
    uniform_int_distribution<> trit_dist(-1, 1);
    
    int total_mismatches = 0;
    const int NUM_TESTS = 20;
    
    for (int test = 0; test < NUM_TESTS; test++) {
        uint8_t acts[4];
        uint8_t weights[4];
        
        for (int i = 0; i < 4; i++) {
            acts[i] = act_dist(gen);
            int trits[4];
            for (int j = 0; j < 4; j++) trits[j] = trit_dist(gen);
            weights[i] = pack_trits(trits[0], trits[1], trits[2], trits[3]);
        }
        
        uint8_t results[4];
        int8_t expected[4];
        compute_expected_results(acts, weights, expected);
        
        int num_results = do_matmul(dut, tfp, acts, weights, results);
        
        if (num_results != 4) {
            total_mismatches += 4;
            continue;
        }
        
        for (int i = 0; i < 4; i++) {
            if (results[i] != (uint8_t)expected[i]) {
                total_mismatches++;
            }
        }
    }
    
    cout << "  Mismatches: " << total_mismatches << " / " << (NUM_TESTS * 4) << endl;
    check(total_mismatches == 0, "All random tests should pass");
}

// ============================================================================
// TEST 8: Interleaved Activation/Weight Fill
// ============================================================================
void test_interleaved_fill(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Interleaved activation/weight byte fill");
    reset(dut, tfp);
    
    uint8_t acts[4] = {5, 10, 15, 20};
    uint8_t weights[4] = {
        pack_trits(1, 1, 1, 1),  // Sum = 50
        pack_trits(-1, -1, -1, -1),
        pack_trits(1, 0, 0, 0),
        pack_trits(0, 0, 0, 1)
    };
    
    // Send interleaved: A0, W0, A1, W1, A2, W2, A3, W3
    for (int i = 0; i < 4; i++) {
        send_activation_byte(dut, tfp, acts[i]);
        send_weight_byte(dut, tfp, weights[i]);
    }
    tick(dut, tfp);
    
    // Wait for matmul_valid
    int wait = 0;
    while (!get_matmul_valid(dut) && wait < 50) {
        tick(dut, tfp);
        wait++;
    }
    
    // Collect results
    uint8_t results[4];
    int num_results = collect_results(dut, tfp, results);
    
    int8_t expected[4];
    compute_expected_results(acts, weights, expected);
    
    cout << "  Activations: [5, 10, 15, 20]" << endl;
    cout << "  Received " << num_results << " result bytes" << endl;
    
    check(num_results == 4, "Should receive 4 result bytes");
    
    bool all_correct = true;
    for (int i = 0; i < num_results; i++) {
        cout << "    Result[" << i << "]: expected=" << (int)expected[i] 
             << ", got=" << (int)(int8_t)results[i] << endl;
        if (results[i] != (uint8_t)expected[i]) all_correct = false;
    }
    
    check(all_correct, "Interleaved fill should produce correct results");
}

// ============================================================================
// TEST 9: Cancellation Test
// ============================================================================
void test_cancellation(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Cancellation (+1 and -1 on equal values)");
    reset(dut, tfp);
    
    // Pairs of equal values with opposite trits should cancel
    uint8_t acts[4] = {50, 50, 100, 100};
    uint8_t weights[4] = {
        pack_trits(1, -1, 1, -1),  // 50-50+100-100 = 0
        pack_trits(1, -1, 0, 0),   // 50-50 = 0
        pack_trits(0, 0, 1, -1),   // 100-100 = 0
        pack_trits(1, 1, -1, -1)   // 50+50-100-100 = -100
    };
    
    uint8_t results[4];
    int8_t expected[4];
    compute_expected_results(acts, weights, expected);
    
    int num_results = do_matmul(dut, tfp, acts, weights, results);
    
    check(num_results == 4, "Should receive 4 result bytes");
    
    bool all_correct = true;
    for (int i = 0; i < num_results; i++) {
        cout << "    Result[" << i << "]: expected=" << (int)expected[i] 
             << ", got=" << (int)(int8_t)results[i] << endl;
        if (results[i] != (uint8_t)expected[i]) all_correct = false;
    }
    
    check(all_correct, "Cancellation should work correctly");
}

// ============================================================================
// TEST 10: Single Activation Position
// ============================================================================
void test_single_activation_position(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Single activation position (verify indexing)");
    reset(dut, tfp);
    
    bool all_passed = true;
    
    for (int pos = 0; pos < 4; pos++) {
        reset(dut, tfp);
        
        uint8_t acts[4] = {0, 0, 0, 0};
        acts[pos] = 100;
        
        // All units have +1 at the tested position, 0 elsewhere
        int trits[4] = {0, 0, 0, 0};
        trits[pos] = 1;
        uint8_t packed = pack_trits(trits[0], trits[1], trits[2], trits[3]);
        uint8_t weights[4] = {packed, packed, packed, packed};
        
        uint8_t results[4];
        int num_results = do_matmul(dut, tfp, acts, weights, results);
        
        if (num_results != 4) {
            cout << "  Position " << pos << ": Only got " << num_results << " results!" << endl;
            all_passed = false;
            continue;
        }
        
        bool pos_ok = true;
        for (int i = 0; i < 4; i++) {
            if (results[i] != 100) pos_ok = false;
        }
        
        cout << "  Position " << pos << ": " << (pos_ok ? "OK" : "FAIL") 
             << " (results: " << (int)results[0] << "," << (int)results[1] 
             << "," << (int)results[2] << "," << (int)results[3] << ")" << endl;
        
        if (!pos_ok) all_passed = false;
    }
    
    check(all_passed, "Each activation position should contribute correctly");
}

// ============================================================================
// MAIN
// ============================================================================
int main() {
    Verilated::traceEverOn(true);
    
    Vtop* dut = new Vtop;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("top_system_waveform.vcd");

    cout << "====================================================" << endl;
    cout << "   Ternary Matrix-Vector Multiply Test Suite        " << endl;
    cout << "====================================================" << endl;

    // Run all tests
    test_initial_state(dut, tfp);
    test_simple_all_positive(dut, tfp);
    test_different_weights_per_unit(dut, tfp);
    test_zero_activations(dut, tfp);
    test_overflow(dut, tfp);
    test_back_to_back(dut, tfp);
    test_random_stress(dut, tfp);
    test_interleaved_fill(dut, tfp);
    test_cancellation(dut, tfp);
    test_single_activation_position(dut, tfp);

    cout << "\n====================================================" << endl;
    cout << "                    SUMMARY                         " << endl;
    cout << "====================================================" << endl;
    cout << "Total tests: " << test_num << endl;
    if (total_errors == 0) {
        cout << "\033[32mAll tests PASSED!\033[0m" << endl;
    } else {
        cout << "\033[31mFailed assertions: " << total_errors << "\033[0m" << endl;
    }
    cout << "====================================================" << endl;

    tfp->close();
    delete tfp;
    delete dut;
    return total_errors;
}
