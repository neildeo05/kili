// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vfifo_buffer__Syms.h"


void Vfifo_buffer___024root__trace_chg_0_sub_0(Vfifo_buffer___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vfifo_buffer___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root__trace_chg_0\n"); );
    // Init
    Vfifo_buffer___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vfifo_buffer___024root*>(voidSelf);
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vfifo_buffer___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vfifo_buffer___024root__trace_chg_0_sub_0(Vfifo_buffer___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root__trace_chg_0_sub_0\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgSData(oldp+0,(vlSelfRef.fifo_buffer__DOT__buffer[0]),16);
        bufp->chgSData(oldp+1,(vlSelfRef.fifo_buffer__DOT__buffer[1]),16);
        bufp->chgSData(oldp+2,(vlSelfRef.fifo_buffer__DOT__buffer[2]),16);
        bufp->chgSData(oldp+3,(vlSelfRef.fifo_buffer__DOT__buffer[3]),16);
        bufp->chgCData(oldp+4,(vlSelfRef.fifo_buffer__DOT__wr_addr),2);
        bufp->chgCData(oldp+5,(vlSelfRef.fifo_buffer__DOT__rd_addr),2);
        bufp->chgBit(oldp+6,(vlSelfRef.fifo_buffer__DOT__wr_wrap));
        bufp->chgBit(oldp+7,(vlSelfRef.fifo_buffer__DOT__rd_wrap));
        bufp->chgBit(oldp+8,(vlSelfRef.fifo_buffer__DOT__buffer_empty));
        bufp->chgBit(oldp+9,(((IData)(vlSelfRef.fifo_buffer__DOT____VdfgRegularize_hc69a2164_0_1) 
                              & ((IData)(vlSelfRef.fifo_buffer__DOT__wr_wrap) 
                                 != (IData)(vlSelfRef.fifo_buffer__DOT__rd_wrap)))));
        bufp->chgSData(oldp+10,(vlSelfRef.fifo_buffer__DOT__out_reg),16);
        bufp->chgBit(oldp+11,(vlSelfRef.fifo_buffer__DOT__out_valid_reg));
    }
    bufp->chgBit(oldp+12,(vlSelfRef.clk));
    bufp->chgBit(oldp+13,(vlSelfRef.rst));
    bufp->chgBit(oldp+14,(vlSelfRef.input_valid));
    bufp->chgBit(oldp+15,(vlSelfRef.input_ready));
    bufp->chgSData(oldp+16,(vlSelfRef.input_data),16);
    bufp->chgBit(oldp+17,(vlSelfRef.output_valid));
    bufp->chgBit(oldp+18,(vlSelfRef.output_ready));
    bufp->chgSData(oldp+19,(vlSelfRef.output_data),16);
    bufp->chgBit(oldp+20,(((IData)(vlSelfRef.input_ready) 
                           & (IData)(vlSelfRef.input_valid))));
    bufp->chgBit(oldp+21,(((IData)(vlSelfRef.fifo_buffer__DOT__out_valid_reg) 
                           & (IData)(vlSelfRef.output_ready))));
    bufp->chgBit(oldp+22,(vlSelfRef.fifo_buffer__DOT__load_output_reg));
    bufp->chgBit(oldp+23,(((~ (IData)(vlSelfRef.fifo_buffer__DOT__buffer_empty)) 
                           & (IData)(vlSelfRef.fifo_buffer__DOT__load_output_reg))));
}

void Vfifo_buffer___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root__trace_cleanup\n"); );
    // Init
    Vfifo_buffer___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vfifo_buffer___024root*>(voidSelf);
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
