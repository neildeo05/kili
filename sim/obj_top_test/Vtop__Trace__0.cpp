// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vtop__Syms.h"


void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp);

void Vtop___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (VL_UNLIKELY(!vlSymsp->__Vm_activity)) return;
    // Body
    Vtop___024root__trace_chg_0_sub_0((&vlSymsp->TOP), bufp);
}

void Vtop___024root__trace_chg_0_sub_0(Vtop___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_chg_0_sub_0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode + 1);
    // Body
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[0U]))) {
        bufp->chgIData(oldp+0,(vlSelfRef.top__DOT__weight_memory_inst__DOT__unnamedblk1__DOT__i),32);
    }
    if (VL_UNLIKELY((vlSelfRef.__Vm_traceActivity[1U]))) {
        bufp->chgCData(oldp+1,((0x3fU & ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_reg) 
                                         >> 6U))),6);
        bufp->chgCData(oldp+2,(vlSelfRef.top__DOT__curr_burst_addr_reg),6);
        bufp->chgCData(oldp+3,((0x3fU & (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_reg))),6);
        bufp->chgBit(oldp+4,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg));
        bufp->chgBit(oldp+5,(((IData)(vlSelfRef.top__DOT__curr_burst_addr_reg) 
                              == (IData)(vlSelfRef.top__DOT__curr_burst_boundary))));
        bufp->chgBit(oldp+6,((0U == (IData)(vlSelfRef.top__DOT__state))));
        bufp->chgSData(oldp+7,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_reg),12);
        bufp->chgCData(oldp+8,(vlSelfRef.top__DOT__state),2);
        bufp->chgCData(oldp+9,(vlSelfRef.top__DOT__next_state),2);
        bufp->chgCData(oldp+10,(vlSelfRef.top__DOT__curr_burst_boundary),6);
        bufp->chgBit(oldp+11,(vlSelfRef.top__DOT__weight_valid));
        bufp->chgBit(oldp+12,((1U & (~ ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1) 
                                        & ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap) 
                                           != (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap)))))));
        bufp->chgBit(oldp+13,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_valid_reg));
        bufp->chgWData(oldp+14,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_reg),128);
        bufp->chgSData(oldp+18,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer[0]),12);
        bufp->chgSData(oldp+19,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer[1]),12);
        bufp->chgSData(oldp+20,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer[2]),12);
        bufp->chgSData(oldp+21,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer[3]),12);
        bufp->chgCData(oldp+22,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_addr),2);
        bufp->chgCData(oldp+23,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_addr),2);
        bufp->chgBit(oldp+24,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_wrap));
        bufp->chgBit(oldp+25,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_wrap));
        bufp->chgBit(oldp+26,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer_empty));
        bufp->chgBit(oldp+27,(((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT____VdfgRegularize_h869595dc_0_1) 
                               & ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_wrap) 
                                  != (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_wrap)))));
        bufp->chgBit(oldp+28,(((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg) 
                               & (0U == (IData)(vlSelfRef.top__DOT__state)))));
        bufp->chgBit(oldp+29,(vlSelfRef.top__DOT__burst_fifo_inst__DOT__load_output_reg));
        bufp->chgBit(oldp+30,(((~ (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer_empty)) 
                               & (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__load_output_reg))));
        bufp->chgWData(oldp+31,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer[0]),128);
        bufp->chgWData(oldp+35,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer[1]),128);
        bufp->chgWData(oldp+39,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer[2]),128);
        bufp->chgWData(oldp+43,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer[3]),128);
        bufp->chgCData(oldp+47,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_addr),2);
        bufp->chgCData(oldp+48,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr),2);
        bufp->chgBit(oldp+49,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap));
        bufp->chgBit(oldp+50,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap));
        bufp->chgBit(oldp+51,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer_empty));
        bufp->chgBit(oldp+52,(((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1) 
                               & ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap) 
                                  != (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap)))));
        bufp->chgBit(oldp+53,(((~ ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1) 
                                   & ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap) 
                                      != (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap)))) 
                               & (IData)(vlSelfRef.top__DOT__weight_valid))));
        bufp->chgBit(oldp+54,(vlSelfRef.top__DOT__weight_fifo_inst__DOT__load_output_reg));
        bufp->chgBit(oldp+55,(((~ (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer_empty)) 
                               & (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__load_output_reg))));
        bufp->chgWData(oldp+56,(vlSelfRef.top__DOT__weight_memory_inst__DOT__mem
                                [vlSelfRef.top__DOT__weight_memory_inst__DOT__addr0_reg]),128);
        bufp->chgBit(oldp+60,((1U != (IData)(vlSelfRef.top__DOT__state))));
        bufp->chgBit(oldp+61,(vlSelfRef.top__DOT__weight_memory_inst__DOT__web1_reg));
        bufp->chgCData(oldp+62,(vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg),6);
        bufp->chgWData(oldp+63,(vlSelfRef.top__DOT__weight_memory_inst__DOT__din1_reg),128);
    }
    bufp->chgBit(oldp+67,(vlSelfRef.clk));
    bufp->chgBit(oldp+68,(vlSelfRef.rst));
    bufp->chgCData(oldp+69,(vlSelfRef.in_burst_addr),6);
    bufp->chgCData(oldp+70,(vlSelfRef.in_burst_len),6);
    bufp->chgBit(oldp+71,(vlSelfRef.in_burst_valid));
    bufp->chgBit(oldp+72,(vlSelfRef.in_burst_ready));
    bufp->chgWData(oldp+73,(vlSelfRef.weight_data),128);
    bufp->chgSData(oldp+77,((((IData)(vlSelfRef.in_burst_addr) 
                              << 6U) | (IData)(vlSelfRef.in_burst_len))),12);
    bufp->chgBit(oldp+78,(((IData)(vlSelfRef.in_burst_ready) 
                           & (IData)(vlSelfRef.in_burst_valid))));
}

void Vtop___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root__trace_cleanup\n"); );
    // Init
    Vtop___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vtop___024root*>(voidSelf);
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    vlSymsp->__Vm_activity = false;
    vlSymsp->TOP.__Vm_traceActivity[0U] = 0U;
    vlSymsp->TOP.__Vm_traceActivity[1U] = 0U;
}
