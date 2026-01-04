#include <stdlib.h>
#include <stdint.h>
#include <iostream>

#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vin_chan_skid_buffer.h"
#include "Vout_chan_skid_buffer.h"

using namespace std;

vluint64_t sim_time = 0;
double sc_time_stamp() { return sim_time; }

// ============================================================================
// In-channel skid buffer helpers
// ============================================================================

void tick_in(Vin_chan_skid_buffer* dut, VerilatedVcdC* tfp) {
    dut->clk = 0;
    dut->eval();
    if (tfp) tfp->dump(sim_time++);
    
    dut->clk = 1;
    dut->eval();
    if (tfp) tfp->dump(sim_time++);
}

void reset_in(Vin_chan_skid_buffer* dut, VerilatedVcdC* tfp) {
    dut->rst = 1;
    dut->in_producer_valid = 0;
    dut->in_producer_data = 0;
    dut->in_consumer_ready = 0;
    for (int i = 0; i < 5; i++) tick_in(dut, tfp);
    dut->rst = 0;
    tick_in(dut, tfp);
}

// ============================================================================
// Out-channel skid buffer helpers
// ============================================================================

void tick_out(Vout_chan_skid_buffer* dut, VerilatedVcdC* tfp) {
    dut->clk = 0;
    dut->eval();
    if (tfp) tfp->dump(sim_time++);
    
    dut->clk = 1;
    dut->eval();
    if (tfp) tfp->dump(sim_time++);
}

void reset_out(Vout_chan_skid_buffer* dut, VerilatedVcdC* tfp) {
    dut->rst = 1;
    dut->in_producer_valid = 0;
    dut->in_producer_data = 0;
    dut->in_consumer_ready = 0;
    for (int i = 0; i < 5; i++) tick_out(dut, tfp);
    dut->rst = 0;
    tick_out(dut, tfp);
}

// ============================================================================
// In-channel skid buffer tests
// ============================================================================

int test_in_chan_skid_buffer() {
    printf("\n");
    printf("========================================\n");
    printf("Testing in_chan_skid_buffer\n");
    printf("========================================\n");

    Vin_chan_skid_buffer* dut = new Vin_chan_skid_buffer;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("in_chan_skid_waveform.vcd");

    int errors = 0;

    // ========== Test 1  ==========
    printf("\nTest 1: Basic passthrough when consumer ready\n");
    reset_in(dut, tfp);
    dut->in_producer_valid = 1;
    dut->in_producer_data = 0x1234;
    dut->in_consumer_ready = 1;
    tick_in(dut, tfp);
    dut->in_producer_valid = 0;
    tick_in(dut, tfp);

    // ========== Test 2 ==========
    printf("\nTest 2: Buffer holds data when consumer stalls\n");
    reset_in(dut, tfp);
    dut->in_producer_valid = 1;
    dut->in_producer_data = 0x1234;
    // dut->in_consumer_ready = 1;
    tick_in(dut, tfp);
    dut->in_producer_valid = 0;
    dut->in_producer_data = 0;
    tick_in(dut, tfp);
    dut->in_consumer_ready = 1;
    tick_in(dut, tfp);
    dut->in_consumer_ready = 0;
    tick_in(dut, tfp);
    tick_in(dut, tfp);
    tick_in(dut, tfp);
    tick_in(dut, tfp);

    // ========== Test 3 ==========
    printf("\nTest 3: Backpressure propagation\n");
    reset_in(dut, tfp);
    
    // Consumer not ready, send first data - should pass through combinationally
    dut->in_producer_valid = 1;
    dut->in_producer_data = 0xAAAA;
    dut->in_consumer_ready = 0;
    dut->eval();
    
    // out_buf_ready should still be high (buffer empty)
    if (!dut->out_buf_ready) {
        printf("  FAIL: out_buf_ready should be 1 before buffering\n");
        errors++;
    } else {
        printf("  PASS: out_buf_ready=1 initially\n");
    }
    
    tick_in(dut, tfp);  // Buffer captures data since consumer not ready
    
    // Now buffer is valid, out_buf_ready should be LOW (backpressure!)
    if (dut->out_buf_ready) {
        printf("  FAIL: out_buf_ready should be 0 after buffering (backpressure)\n");
        errors++;
    } else {
        printf("  PASS: out_buf_ready=0, backpressure propagated\n");
    }
    tick_in(dut, tfp);
    
    // Try to send more data - producer should see we're not ready
    dut->in_producer_valid = 1;
    dut->in_producer_data = 0xBBBB;
    tick_in(dut, tfp);
    tick_in(dut, tfp);
    
    // Consumer becomes ready, should drain buffer
    dut->in_consumer_ready = 1;
    dut->in_producer_valid = 0;
    
    // out_buf_data should be the buffered value
    if (dut->out_buf_data != 0xAAAA) {
        printf("  FAIL: Expected buffered data 0xAAAA, got 0x%X\n", dut->out_buf_data);
        errors++;
    } else {
        printf("  PASS: Buffered data 0xAAAA available\n");
    }
    
    tick_in(dut, tfp);  // Handshake completes
    tick_in(dut, tfp);
    
    // out_buf_ready should be back HIGH
    if (!dut->out_buf_ready) {
        printf("  FAIL: out_buf_ready should be 1 after drain\n");
        errors++;
    } else {
        printf("  PASS: out_buf_ready=1 after drain\n");
    }
    
    tick_in(dut, tfp);
    tick_in(dut, tfp);

    // ========== Summary ==========
    printf("\n----------------------------------------\n");
    if (errors == 0) {
        printf("in_chan_skid_buffer: All tests PASSED!\n");
    } else {
        printf("in_chan_skid_buffer: %d error(s)\n", errors);
    }

    tfp->close();
    delete tfp;
    delete dut;
    return errors;
}

// ============================================================================
// Out-channel skid buffer tests
// ============================================================================

int test_out_chan_skid_buffer() {
    printf("\n");
    printf("========================================\n");
    printf("Testing out_chan_skid_buffer\n");
    printf("========================================\n");

    Vout_chan_skid_buffer* dut = new Vout_chan_skid_buffer;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("out_chan_skid_waveform.vcd");

    int errors = 0;

    // ========== Test 1 ==========
    printf("\nTest 1: Basic passthrough with 1-cycle latency\n");
    reset_out(dut, tfp);
    
    // Output is registered, so 1-cycle latency from input to output
    dut->in_producer_valid = 1;
    dut->in_producer_data = 0x1234;
    dut->in_consumer_ready = 1;
    
    // Before clock, output should not be valid yet
    if (dut->out_buf_valid) {
        printf("  FAIL: out_buf_valid should be 0 before first clock\n");
        errors++;
    } else {
        printf("  PASS: out_buf_valid=0 before clock (registered output)\n");
    }
    
    tick_out(dut, tfp);  // Data appears on output after 1 cycle
    
    if (!dut->out_buf_valid) {
        printf("  FAIL: out_buf_valid should be 1 after clock\n");
        errors++;
    } else if (dut->out_buf_data != 0x1234) {
        printf("  FAIL: Expected 0x1234, got 0x%X\n", dut->out_buf_data);
        errors++;
    } else {
        printf("  PASS: Data 0x1234 available after 1-cycle latency\n");
    }
    
    dut->in_producer_valid = 0;
    tick_out(dut, tfp);  // Consumer handshakes
    
    // After handshake, output should go invalid (no new data)
    if (dut->out_buf_valid) {
        printf("  FAIL: out_buf_valid should be 0 after drain\n");
        errors++;
    } else {
        printf("  PASS: out_buf_valid=0 after consumer handshake\n");
    }

    // ========== Test 2 ==========
    printf("\nTest 2: Buffer holds data when consumer stalls\n");
    reset_out(dut, tfp);
    
    // Send data, consumer not ready
    dut->in_producer_valid = 1;
    dut->in_producer_data = 0xABCD;
    dut->in_consumer_ready = 0;
    tick_out(dut, tfp);  // Data goes to output register
    
    if (!dut->out_buf_valid) {
        printf("  FAIL: out_buf_valid should be 1\n");
        errors++;
    } else if (dut->out_buf_data != 0xABCD) {
        printf("  FAIL: Expected 0xABCD, got 0x%X\n", dut->out_buf_data);
        errors++;
    } else {
        printf("  PASS: Data 0xABCD latched in output register\n");
    }
    
    // Send more data while output stalled - should go to internal buffer
    dut->in_producer_data = 0x5678;
    tick_out(dut, tfp);
    
    // Output should still hold original value
    if (dut->out_buf_data != 0xABCD) {
        printf("  FAIL: Output should still be 0xABCD, got 0x%X\n", dut->out_buf_data);
        errors++;
    } else {
        printf("  PASS: Output holds 0xABCD while stalled\n");
    }
    
    dut->in_producer_valid = 0;
    
    // Consumer becomes ready, first value consumed
    dut->in_consumer_ready = 1;
    tick_out(dut, tfp);
    
    // Buffered value should now appear on output
    if (!dut->out_buf_valid) {
        printf("  FAIL: out_buf_valid should be 1 (buffered data)\n");
        errors++;
    } else if (dut->out_buf_data != 0x5678) {
        printf("  FAIL: Expected buffered 0x5678, got 0x%X\n", dut->out_buf_data);
        errors++;
    } else {
        printf("  PASS: Buffered data 0x5678 now on output\n");
    }
    
    tick_out(dut, tfp);  // Drain
    tick_out(dut, tfp);

    // ========== Test 3 ==========
    printf("\nTest 3: Backpressure propagation\n");
    reset_out(dut, tfp);
    
    // out_buf_ready should be high initially (buffer empty)
    if (!dut->out_buf_ready) {
        printf("  FAIL: out_buf_ready should be 1 initially\n");
        errors++;
    } else {
        printf("  PASS: out_buf_ready=1 initially\n");
    }
    
    // Fill output register
    dut->in_producer_valid = 1;
    dut->in_producer_data = 0x1111;
    dut->in_consumer_ready = 0;
    tick_out(dut, tfp);
    
    // Still ready (output reg full, but internal buffer empty)
    if (!dut->out_buf_ready) {
        printf("  FAIL: out_buf_ready should still be 1 (buffer empty)\n");
        errors++;
    } else {
        printf("  PASS: out_buf_ready=1 (buffer still empty)\n");
    }
    
    // Fill internal buffer
    dut->in_producer_data = 0x2222;
    tick_out(dut, tfp);
    
    // Now backpressure should kick in (buffer full)
    if (dut->out_buf_ready) {
        printf("  FAIL: out_buf_ready should be 0 (backpressure)\n");
        errors++;
    } else {
        printf("  PASS: out_buf_ready=0, backpressure propagated\n");
    }
    
    // Consumer drains first value
    dut->in_producer_valid = 0;
    dut->in_consumer_ready = 1;
    tick_out(dut, tfp);
    
    // Buffer should drain, ready goes high
    if (!dut->out_buf_ready) {
        printf("  FAIL: out_buf_ready should be 1 after drain\n");
        errors++;
    } else {
        printf("  PASS: out_buf_ready=1 after drain\n");
    }
    
    // Verify second value is now on output
    if (dut->out_buf_data != 0x2222) {
        printf("  FAIL: Expected 0x2222, got 0x%X\n", dut->out_buf_data);
        errors++;
    } else {
        printf("  PASS: Buffered data 0x2222 now on output\n");
    }
    
    tick_out(dut, tfp);
    tick_out(dut, tfp);

    // ========== Summary ==========
    printf("\n----------------------------------------\n");
    if (errors == 0) {
        printf("out_chan_skid_buffer: All tests PASSED!\n");
    } else {
        printf("out_chan_skid_buffer: %d error(s)\n", errors);
    }

    tfp->close();
    delete tfp;
    delete dut;
    return errors;
}

// ============================================================================
// Main
// ============================================================================

int main() {
    Verilated::traceEverOn(true);

    int total_errors = 0;
    // total_errors += test_in_chan_skid_buffer();
    total_errors += test_out_chan_skid_buffer();

    printf("\n========================================\n");
    if (total_errors == 0) {
        printf("All skid buffer tests PASSED!\n");
    } else {
        printf("Total: %d error(s)\n", total_errors);
    }
    printf("========================================\n");

    return total_errors;
}

