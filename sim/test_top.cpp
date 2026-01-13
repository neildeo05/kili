#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <iomanip>
#include <string>

#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vtop.h"

using namespace std;

vluint64_t sim_time = 0;
double sc_time_stamp() { return sim_time; }

int test_num = 0;
int total_errors = 0;

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
    dut->activation_byte_valid = 0;
    dut->activation_byte = 0;
    dut->weight_byte_valid = 0;
    dut->weight_byte = 0;
    dut->result_byte_valid = 0;
    for (int i = 0; i < 5; i++) tick(dut, tfp);
    dut->rst = 0;
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

// Helper to build expected buffer value from an array of 4 bytes
uint32_t build_expected_buffer(uint8_t bytes[4]) {
    uint32_t expected = 0;
    for (int i = 0; i < 4; i++) {
        expected |= ((uint32_t)bytes[i]) << (i * 8);
    }
    return expected;
}

// Helper to check buffer contents
bool check_buffer(Vtop* dut, uint8_t expected_bytes[4], const string& context) {
    uint32_t expected = build_expected_buffer(expected_bytes);
    uint32_t actual = dut->activation_buffer;
    if (actual != expected) {
        cout << "  [FAIL] Buffer mismatch " << context << endl;
        cout << "         Expected: 0x" << hex << setfill('0') << setw(8) << expected << endl;
        cout << "         Actual:   0x" << hex << setfill('0') << setw(8) << actual << dec << endl;
        total_errors++;
        return false;
    }
    cout << "  [PASS] Buffer contents correct " << context << endl;
    return true;
}

// Helper to fill buffer with bytes and return expected pattern
void fill_buffer(Vtop* dut, VerilatedVcdC* tfp, uint8_t bytes[4]) {
    for (int i = 0; i < 4; i++) {
        dut->activation_byte_valid = 1;
        dut->activation_byte = bytes[i];
        tick(dut, tfp);
    }
    dut->activation_byte_valid = 0;
    tick(dut, tfp);
}

void start_test(const string& name) {
    test_num++;
    cout << "\n========== Test " << test_num << ": " << name << " ==========" << endl;
}

// ============================================================================
// TEST 1: Initial state after reset
// ============================================================================
void test_initial_state(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Initial state after reset");
    reset(dut, tfp);
    
    check(dut->activation_ready == 1, "activation_ready should be HIGH after reset");
    check(dut->result_byte_valid == 0, "result_byte_valid should be LOW after reset");
    check(dut->activation_buffer == 0, "activation_buffer should be zero after reset");
}

// ============================================================================
// TEST 2: Basic 4-byte fill and verify buffer contents
// ============================================================================
void test_basic_fill(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Basic 4-byte fill");
    reset(dut, tfp);
    
    uint8_t bytes[4] = {0x00, 0x01, 0x02, 0x03};
    
    // Fill with bytes 0x00 through 0x03
    for (int i = 0; i < 4; i++) {
        check(dut->activation_ready == 1, "activation_ready should be HIGH during fill (byte " + to_string(i) + ")");
        dut->activation_byte_valid = 1;
        dut->activation_byte = bytes[i];
        tick(dut, tfp);
    }
    
    dut->activation_byte_valid = 0;
    tick(dut, tfp);
    
    // After 4 bytes, should be in DONE state
    check(dut->activation_ready == 0, "activation_ready should be LOW after buffer full");
    check_buffer(dut, bytes, "(sequential 0x00-0x03)");
}

// ============================================================================
// TEST 3: Valid signal gating - bytes only accepted when valid is HIGH
// ============================================================================
void test_valid_gating(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Valid signal gating");
    reset(dut, tfp);
    
    // Send garbage with valid LOW - should be ignored
    for (int i = 0; i < 5; i++) {
        dut->activation_byte_valid = 0;
        dut->activation_byte = 0xFF;  // Garbage
        tick(dut, tfp);
    }
    
    // Should still be in EMPTY state (ready HIGH)
    check(dut->activation_ready == 1, "activation_ready should still be HIGH (no valid bytes sent)");
    check(dut->activation_buffer == 0, "buffer should still be zero (garbage ignored)");
    
    // Now send 1 valid byte
    dut->activation_byte_valid = 1;
    dut->activation_byte = 0xAA;
    tick(dut, tfp);
    
    // Should now be in FILLING state
    check(dut->activation_ready == 1, "activation_ready should be HIGH during FILLING");
    
    // Check that first byte is written
    check((dut->activation_buffer & 0xFF) == 0xAA, "first byte should be 0xAA");
    
    // Send more garbage with valid LOW
    dut->activation_byte_valid = 0;
    dut->activation_byte = 0xFF;
    for (int i = 0; i < 5; i++) tick(dut, tfp);
    
    // Should still be in FILLING state (only 1 byte received)
    check(dut->activation_ready == 1, "activation_ready should remain HIGH (only 1 valid byte received)");
    check((dut->activation_buffer & 0xFF) == 0xAA, "first byte should still be 0xAA (garbage ignored)");
}

// ============================================================================
// TEST 4: Intermittent valid signal - gaps between valid bytes
// ============================================================================
void test_intermittent_valid(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Intermittent valid signal");
    reset(dut, tfp);
    
    uint8_t bytes[4];
    
    // Send 4 bytes with gaps
    for (int i = 0; i < 4; i++) {
        bytes[i] = (uint8_t)(0x10 + i);
        
        // Valid byte
        dut->activation_byte_valid = 1;
        dut->activation_byte = bytes[i];
        tick(dut, tfp);
        
        // Gap (2 cycles of invalid)
        dut->activation_byte_valid = 0;
        dut->activation_byte = 0xFF;  // Garbage
        tick(dut, tfp);
        tick(dut, tfp);
    }
    
    check(dut->activation_ready == 0, "activation_ready should be LOW after 4 valid bytes (with gaps)");
    check_buffer(dut, bytes, "(0x10-0x13 with gaps)");
}

void test_back_to_back_operations(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Back-to-back operations");
    reset(dut, tfp);
    
    for (int round = 0; round < 3; round++) {
        cout << "  Round " << (round + 1) << ":" << endl;
        
        uint8_t bytes[4];
        for (int i = 0; i < 4; i++) {
            bytes[i] = (uint8_t)(round * 0x10 + i);
        }
        
        // Fill buffer
        fill_buffer(dut, tfp, bytes);
        
        check(dut->activation_ready == 0, "  activation_ready should be LOW in DONE state");
        check_buffer(dut, bytes, "(round " + to_string(round + 1) + ")");
        
        // Trigger transition back to EMPTY
        dut->result_byte_valid = 1;
        tick(dut, tfp);
        dut->result_byte_valid = 0;
        tick(dut, tfp);
        
        check(dut->activation_ready == 1, "  activation_ready should be HIGH after transition");
    }
}

void test_ignore_bytes_when_done(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Ignore bytes when buffer is full (DONE state)");
    reset(dut, tfp);
    
    // Fill buffer
    uint8_t bytes[4] = {0x00, 0x01, 0x02, 0x03};
    fill_buffer(dut, tfp, bytes);
    
    check(dut->activation_ready == 0, "activation_ready should be LOW in DONE state");
    uint32_t buffer_before = dut->activation_buffer;
    
    // Try to send more bytes - should be ignored (ready is LOW)
    for (int i = 0; i < 5; i++) {
        dut->activation_byte_valid = 1;
        dut->activation_byte = 0xFF;
        tick(dut, tfp);
        
        check(dut->activation_ready == 0, "activation_ready should remain LOW (byte " + to_string(i) + ")");
    }
    
    // Verify buffer wasn't modified
    check(dut->activation_buffer == buffer_before, "buffer should be unchanged after ignored bytes");
    check_buffer(dut, bytes, "(unchanged)");
}

void test_boundary_fourth_byte(Vtop* dut, VerilatedVcdC* tfp) {
    start_test("Boundary condition - 3 bytes then 4th byte");
    reset(dut, tfp);
    
    uint8_t bytes[4] = {0xA0, 0xA1, 0xA2, 0xA3};
    
    // Send 3 bytes
    for (int i = 0; i < 3; i++) {
        dut->activation_byte_valid = 1;
        dut->activation_byte = bytes[i];
        tick(dut, tfp);
    }
    
    dut->activation_byte_valid = 0;
    tick(dut, tfp);
    
    check(dut->activation_ready == 1, "activation_ready should still be HIGH after 3 bytes");
    
    // Wait some cycles
    for (int i = 0; i < 5; i++) tick(dut, tfp);
    
    check(dut->activation_ready == 1, "activation_ready should still be HIGH (waiting)");
    
    // Send the 4th byte
    dut->activation_byte_valid = 1;
    dut->activation_byte = bytes[3];
    tick(dut, tfp);
    
    dut->activation_byte_valid = 0;
    tick(dut, tfp);
    
    check(dut->activation_ready == 0, "activation_ready should be LOW after 4th byte");
    check_buffer(dut, bytes, "(after delayed 4th byte)");
}

int main() {
    Verilated::traceEverOn(true);
    
    Vtop* dut = new Vtop;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("top_waveform.vcd");

    cout << "====================================================" << endl;
    cout << "      Activation Buffer Test Suite                  " << endl;
    cout << "====================================================" << endl;

    // Run all tests
    test_initial_state(dut, tfp);
    test_basic_fill(dut, tfp);
    test_valid_gating(dut, tfp);
    test_intermittent_valid(dut, tfp);
    test_back_to_back_operations(dut, tfp);
    test_ignore_bytes_when_done(dut, tfp);
    test_boundary_fourth_byte(dut, tfp);

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
