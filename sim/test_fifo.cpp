#include <stdlib.h>
#include <stdint.h>
#include <iostream>
#include <queue>
#include <random>

#include "verilated.h"
#include "verilated_vcd_c.h"
#include "Vfifo_buffer.h"

using namespace std;

vluint64_t sim_time = 0;
double sc_time_stamp() { return sim_time; }

void tick(Vfifo_buffer* dut, VerilatedVcdC* tfp) {
    dut->clk = 0;
    dut->eval();
    if (tfp) tfp->dump(sim_time++);
    
    dut->clk = 1;
    dut->eval();
    if (tfp) tfp->dump(sim_time++);
}

void reset(Vfifo_buffer* dut, VerilatedVcdC* tfp) {
    dut->rst = 1;
    dut->input_valid = 0;
    dut->input_data = 0;
    dut->output_ready = 0;
    for (int i = 0; i < 5; i++) tick(dut, tfp);
    dut->rst = 0;
    tick(dut, tfp);
}

int main() {
    Verilated::traceEverOn(true);
    
    Vfifo_buffer* dut = new Vfifo_buffer;
    VerilatedVcdC* tfp = new VerilatedVcdC;
    dut->trace(tfp, 99);
    tfp->open("fifo_waveform.vcd");

    int errors = 0;
    queue<uint16_t> ref_fifo;
    mt19937 gen(42);
    uniform_int_distribution<> data_dist(0, 0xFFFF);

    // Pipeline FIFO has 2-cycle latency from input to output
    // Effective capacity = DEPTH (buffer) + 1 (output register) = 5 for DEPTH=4

    // ========== Test 1: Basic push then pop (with latency) ==========
    printf("Test 1: Basic push then pop (2-cycle latency)\n");
    reset(dut, tfp);
    
    // Push one value
    dut->input_valid = 1;
    dut->input_data = 0xABCD;
    tick(dut, tfp);  // Cycle 1: data written to buffer
    dut->input_valid = 0;
    tick(dut, tfp);  // Cycle 2: data loads into output register
    
    // Now output should be valid
    if (!dut->output_valid) {
        printf("  FAIL: output_valid should be 1 after 2 cycles\n");
        errors++;
    } else if (dut->output_data != 0xABCD) {
        printf("  FAIL: Expected 0xABCD, got 0x%04X\n", dut->output_data);
        errors++;
    } else {
        printf("  PASS: Data 0x%04X available after 2-cycle latency\n", dut->output_data);
    }
    
    // Pop it - sample data BEFORE tick (valid/ready handshake)
    dut->output_ready = 1;
    uint16_t sampled = dut->output_data;
    tick(dut, tfp);  // Handshake completes
    dut->output_ready = 0;
    
    if (sampled == 0xABCD) {
        printf("  PASS: Sampled 0x%04X on handshake\n", sampled);
    } else {
        printf("  FAIL: Expected to sample 0xABCD, got 0x%04X\n", sampled);
        errors++;
    }
    
    // After pop, should be empty
    tick(dut, tfp);
    if (dut->output_valid) {
        printf("  FAIL: output_valid should be 0 after draining\n");
        errors++;
    } else {
        printf("  PASS: FIFO empty after pop\n");
    }

    // ========== Test 2: Fill FIFO to capacity ==========
    printf("\nTest 2: Fill FIFO to capacity (DEPTH=4 buffer + 1 output reg = 5 total)\n");
    reset(dut, tfp);
    
    uint16_t test_vals[] = {0x1111, 0x2222, 0x3333, 0x4444, 0x5555};
    
    // Insert 5 values (should fill buffer + output register)
    for (int i = 0; i < 5; i++) {
        if (!dut->input_ready) {
            printf("  FAIL: FIFO not ready at entry %d\n", i);
            errors++;
            break;
        }
        dut->input_valid = 1;
        dut->input_data = test_vals[i];
        tick(dut, tfp);
    }
    dut->input_valid = 0;
    tick(dut, tfp);
    
    // Should be full now (buffer full, output register also has data)
    if (dut->input_ready) {
        printf("  FAIL: FIFO should be full but input_ready=1\n");
        errors++;
    } else {
        printf("  PASS: FIFO full after 5 inserts, input_ready=0\n");
    }
    
    // Read all values back - sample BEFORE tick
    dut->output_ready = 1;
    for (int i = 0; i < 5; i++) {
        if (!dut->output_valid) {
            printf("  FAIL: output_valid=0 at read %d\n", i);
            errors++;
            tick(dut, tfp);
            continue;
        }
        uint16_t got = dut->output_data;
        if (got == test_vals[i]) {
            printf("  PASS: Read[%d] = 0x%04X\n", i, got);
        } else {
            printf("  FAIL: Read[%d] expected 0x%04X, got 0x%04X\n", i, test_vals[i], got);
            errors++;
        }
        tick(dut, tfp);  // Complete handshake, load next
    }
    dut->output_ready = 0;
    
    // Should be empty
    if (dut->output_valid) {
        printf("  FAIL: FIFO should be empty\n");
        errors++;
    } else {
        printf("  PASS: FIFO empty after reading all\n");
    }

    // ========== Test 3: Simultaneous read/write (steady state) ==========
    printf("\nTest 3: Simultaneous read/write (steady-state throughput)\n");
    reset(dut, tfp);
    
    // Prime the pipeline: insert 2 values
    dut->input_valid = 1;
    dut->input_data = 0xAAAA;
    tick(dut, tfp);
    dut->input_data = 0xBBBB;
    tick(dut, tfp);
    dut->input_valid = 0;
    
    // Wait for output to be valid
    while (!dut->output_valid) tick(dut, tfp);
    
    // Now do simultaneous read/write
    dut->input_valid = 1;
    dut->output_ready = 1;
    
    // Insert 0xCCCC while reading 0xAAAA
    dut->input_data = 0xCCCC;
    uint16_t read_val = dut->output_data;
    if (read_val == 0xAAAA) {
        printf("  PASS: Read 0xAAAA while inserting 0xCCCC\n");
    } else {
        printf("  FAIL: Expected 0xAAAA, got 0x%04X\n", read_val);
        errors++;
    }
    tick(dut, tfp);
    
    // Insert 0xDDDD while reading 0xBBBB
    dut->input_data = 0xDDDD;
    read_val = dut->output_data;
    if (read_val == 0xBBBB) {
        printf("  PASS: Read 0xBBBB while inserting 0xDDDD\n");
    } else {
        printf("  FAIL: Expected 0xBBBB, got 0x%04X\n", read_val);
        errors++;
    }
    tick(dut, tfp);
    
    dut->input_valid = 0;
    
    // Read 0xCCCC
    read_val = dut->output_data;
    if (read_val == 0xCCCC) {
        printf("  PASS: Read 0xCCCC\n");
    } else {
        printf("  FAIL: Expected 0xCCCC, got 0x%04X\n", read_val);
        errors++;
    }
    tick(dut, tfp);
    
    // Read 0xDDDD
    read_val = dut->output_data;
    if (read_val == 0xDDDD) {
        printf("  PASS: Read 0xDDDD\n");
    } else {
        printf("  FAIL: Expected 0xDDDD, got 0x%04X\n", read_val);
        errors++;
    }
    tick(dut, tfp);
    dut->output_ready = 0;

    // ========== Test 4: Random stress test ==========
    printf("\nTest 4: Random stress test (1000 transactions)\n");
    reset(dut, tfp);
    ref_fifo = queue<uint16_t>();
    
    int pushed = 0, popped = 0;
    uniform_int_distribution<> op_dist(0, 2);
    
    // Account for pipeline latency - items in flight
    queue<uint16_t> in_flight;  // Items written but not yet at output
    
    for (int cycle = 0; cycle < 2000; cycle++) {
        int op = op_dist(gen);
        bool want_push = (op == 0 || op == 2);
        bool want_pop = (op == 1 || op == 2);
        
        // Check output handshake BEFORE tick
        if (want_pop && dut->output_valid) {
            uint16_t expected = ref_fifo.front();
            uint16_t got = dut->output_data;
            if (got != expected) {
                printf("  FAIL at cycle %d: Expected 0x%04X, got 0x%04X\n",
                       cycle, expected, got);
                errors++;
                if (errors > 10) {
                    printf("  Too many errors, stopping stress test\n");
                    break;
                }
            }
            ref_fifo.pop();
            popped++;
            dut->output_ready = 1;
        } else {
            dut->output_ready = 0;
        }
        
        // Setup input
        if (want_push && dut->input_ready) {
            uint16_t val = data_dist(gen);
            dut->input_valid = 1;
            dut->input_data = val;
            in_flight.push(val);
            pushed++;
        } else {
            dut->input_valid = 0;
        }
        
        tick(dut, tfp);
        
        // After 2 cycles, items move from in_flight to ref_fifo (simulating latency)
        // Simplified: just move items when output becomes valid
        while (!in_flight.empty() && ref_fifo.size() < 10) {
            ref_fifo.push(in_flight.front());
            in_flight.pop();
        }
    }
    
    // Drain remaining
    dut->input_valid = 0;
    dut->output_ready = 1;
    
    // Move all in-flight to ref
    while (!in_flight.empty()) {
        ref_fifo.push(in_flight.front());
        in_flight.pop();
    }
    
    int drain_cycles = 0;
    while (!ref_fifo.empty() && drain_cycles < 100) {
        if (dut->output_valid) {
            uint16_t expected = ref_fifo.front();
            uint16_t got = dut->output_data;
            if (got != expected) {
                printf("  FAIL drain: Expected 0x%04X, got 0x%04X\n", expected, got);
                errors++;
            }
            ref_fifo.pop();
            popped++;
        }
        tick(dut, tfp);
        drain_cycles++;
    }
    
    // Wait for output to go invalid
    for (int i = 0; i < 5 && dut->output_valid; i++) {
        tick(dut, tfp);
    }
    
    printf("  Pushed %d, Popped %d\n", pushed, popped);
    if (!dut->output_valid) {
        printf("  PASS: Stress test complete, FIFO drained\n");
    } else {
        printf("  FAIL: FIFO not empty after stress test\n");
        errors++;
    }

    // ========== Test 5: Back-to-back writes then reads ==========
    printf("\nTest 5: Back-to-back writes then reads\n");
    reset(dut, tfp);
    
    // Rapid-fire writes
    dut->input_valid = 1;
    for (int i = 0; i < 4; i++) {
        dut->input_data = 0x100 + i;
        tick(dut, tfp);
    }
    dut->input_valid = 0;
    
    // Wait for pipeline
    tick(dut, tfp);
    tick(dut, tfp);
    
    // Rapid-fire reads
    dut->output_ready = 1;
    for (int i = 0; i < 4; i++) {
        if (dut->output_valid && dut->output_data == (0x100 + i)) {
            printf("  PASS: Back-to-back read[%d] = 0x%04X\n", i, dut->output_data);
        } else {
            printf("  FAIL: Back-to-back read[%d] expected 0x%04X, got 0x%04X (valid=%d)\n",
                   i, 0x100 + i, dut->output_data, dut->output_valid);
            errors++;
        }
        tick(dut, tfp);
    }
    dut->output_ready = 0;

    // ========== Summary ==========
    printf("\n========================================\n");
    if (errors == 0) {
        printf("All tests PASSED!\n");
    } else {
        printf("%d error(s) in tests\n", errors);
    }

    tfp->close();
    delete tfp;
    delete dut;
    return errors;
}
