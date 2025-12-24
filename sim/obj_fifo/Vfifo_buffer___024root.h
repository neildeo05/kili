// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vfifo_buffer.h for the primary calling header

#ifndef VERILATED_VFIFO_BUFFER___024ROOT_H_
#define VERILATED_VFIFO_BUFFER___024ROOT_H_  // guard

#include "verilated.h"


class Vfifo_buffer__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vfifo_buffer___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(input_valid,0,0);
    VL_OUT8(input_ready,0,0);
    VL_OUT8(output_valid,0,0);
    VL_IN8(output_ready,0,0);
    CData/*1:0*/ fifo_buffer__DOT__wr_addr;
    CData/*1:0*/ fifo_buffer__DOT__rd_addr;
    CData/*0:0*/ fifo_buffer__DOT__wr_wrap;
    CData/*0:0*/ fifo_buffer__DOT__rd_wrap;
    CData/*0:0*/ fifo_buffer__DOT__buffer_empty;
    CData/*0:0*/ fifo_buffer__DOT__out_valid_reg;
    CData/*0:0*/ fifo_buffer__DOT__load_output_reg;
    CData/*0:0*/ fifo_buffer__DOT____VdfgRegularize_hc69a2164_0_1;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    VL_IN16(input_data,15,0);
    VL_OUT16(output_data,15,0);
    SData/*15:0*/ fifo_buffer__DOT__out_reg;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<SData/*15:0*/, 4> fifo_buffer__DOT__buffer;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vfifo_buffer__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vfifo_buffer___024root(Vfifo_buffer__Syms* symsp, const char* v__name);
    ~Vfifo_buffer___024root();
    VL_UNCOPYABLE(Vfifo_buffer___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
