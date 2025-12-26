// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst,0,0);
    VL_IN8(in_burst_addr,5,0);
    VL_IN8(in_burst_len,5,0);
    VL_IN8(in_burst_valid,0,0);
    VL_OUT8(in_burst_ready,0,0);
    CData/*5:0*/ top__DOT__curr_burst_addr_reg;
    CData/*1:0*/ top__DOT__state;
    CData/*1:0*/ top__DOT__next_state;
    CData/*5:0*/ top__DOT__curr_burst_boundary;
    CData/*0:0*/ top__DOT__weight_valid;
    CData/*1:0*/ top__DOT__burst_fifo_inst__DOT__wr_addr;
    CData/*1:0*/ top__DOT__burst_fifo_inst__DOT__rd_addr;
    CData/*0:0*/ top__DOT__burst_fifo_inst__DOT__wr_wrap;
    CData/*0:0*/ top__DOT__burst_fifo_inst__DOT__rd_wrap;
    CData/*0:0*/ top__DOT__burst_fifo_inst__DOT__buffer_empty;
    CData/*0:0*/ top__DOT__burst_fifo_inst__DOT__out_valid_reg;
    CData/*0:0*/ top__DOT__burst_fifo_inst__DOT__load_output_reg;
    CData/*0:0*/ top__DOT__burst_fifo_inst__DOT____VdfgRegularize_h869595dc_0_1;
    CData/*5:0*/ top__DOT__weight_memory_inst__DOT__addr0_reg;
    CData/*0:0*/ top__DOT__weight_memory_inst__DOT__web1_reg;
    CData/*5:0*/ top__DOT__weight_memory_inst__DOT__addr1_reg;
    CData/*1:0*/ top__DOT__weight_fifo_inst__DOT__wr_addr;
    CData/*1:0*/ top__DOT__weight_fifo_inst__DOT__rd_addr;
    CData/*0:0*/ top__DOT__weight_fifo_inst__DOT__wr_wrap;
    CData/*0:0*/ top__DOT__weight_fifo_inst__DOT__rd_wrap;
    CData/*0:0*/ top__DOT__weight_fifo_inst__DOT__buffer_empty;
    CData/*0:0*/ top__DOT__weight_fifo_inst__DOT__insert;
    CData/*0:0*/ top__DOT__weight_fifo_inst__DOT__out_valid_reg;
    CData/*0:0*/ top__DOT__weight_fifo_inst__DOT__load_output_reg;
    CData/*0:0*/ top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __VactContinue;
    SData/*11:0*/ top__DOT__burst_fifo_inst__DOT__out_reg;
    VL_OUTW(weight_data,127,0,4);
    VlWide<4>/*127:0*/ top__DOT__weight_memory_inst__DOT__din0_reg;
    VlWide<4>/*127:0*/ top__DOT__weight_memory_inst__DOT__din1_reg;
    IData/*31:0*/ top__DOT__weight_memory_inst__DOT__unnamedblk1__DOT__i;
    VlWide<4>/*127:0*/ top__DOT__weight_fifo_inst__DOT__out_reg;
    IData/*31:0*/ __VactIterCount;
    VlUnpacked<SData/*11:0*/, 4> top__DOT__burst_fifo_inst__DOT__buffer;
    VlUnpacked<VlWide<4>/*127:0*/, 64> top__DOT__weight_memory_inst__DOT__mem;
    VlUnpacked<VlWide<4>/*127:0*/, 4> top__DOT__weight_fifo_inst__DOT__buffer;
    VlUnpacked<CData/*0:0*/, 2> __Vm_traceActivity;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
