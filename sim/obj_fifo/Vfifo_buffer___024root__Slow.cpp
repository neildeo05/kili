// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo_buffer.h for the primary calling header

#include "Vfifo_buffer__pch.h"
#include "Vfifo_buffer__Syms.h"
#include "Vfifo_buffer___024root.h"

void Vfifo_buffer___024root___ctor_var_reset(Vfifo_buffer___024root* vlSelf);

Vfifo_buffer___024root::Vfifo_buffer___024root(Vfifo_buffer__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vfifo_buffer___024root___ctor_var_reset(this);
}

void Vfifo_buffer___024root::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vfifo_buffer___024root::~Vfifo_buffer___024root() {
}
