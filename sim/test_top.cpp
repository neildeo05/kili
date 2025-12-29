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
    printf("Test 1: Simple burst read (addr=0, len=4)\n");
    reset(dut, tfp);
    dut->activations_valid = 1;
    for (int i = 0; i < 16; i++) {
        dut->activations_in[i] = i * 16;
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
