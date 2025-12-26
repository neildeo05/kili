// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*5:0*/ __Vdly__top__DOT__curr_burst_addr_reg;
    __Vdly__top__DOT__curr_burst_addr_reg = 0;
    CData/*1:0*/ __Vdly__top__DOT__burst_fifo_inst__DOT__wr_addr;
    __Vdly__top__DOT__burst_fifo_inst__DOT__wr_addr = 0;
    CData/*0:0*/ __Vdly__top__DOT__burst_fifo_inst__DOT__wr_wrap;
    __Vdly__top__DOT__burst_fifo_inst__DOT__wr_wrap = 0;
    CData/*1:0*/ __Vdly__top__DOT__burst_fifo_inst__DOT__rd_addr;
    __Vdly__top__DOT__burst_fifo_inst__DOT__rd_addr = 0;
    CData/*0:0*/ __Vdly__top__DOT__burst_fifo_inst__DOT__rd_wrap;
    __Vdly__top__DOT__burst_fifo_inst__DOT__rd_wrap = 0;
    CData/*1:0*/ __Vdly__top__DOT__weight_fifo_inst__DOT__wr_addr;
    __Vdly__top__DOT__weight_fifo_inst__DOT__wr_addr = 0;
    CData/*0:0*/ __Vdly__top__DOT__weight_fifo_inst__DOT__wr_wrap;
    __Vdly__top__DOT__weight_fifo_inst__DOT__wr_wrap = 0;
    CData/*1:0*/ __Vdly__top__DOT__weight_fifo_inst__DOT__rd_addr;
    __Vdly__top__DOT__weight_fifo_inst__DOT__rd_addr = 0;
    CData/*0:0*/ __Vdly__top__DOT__weight_fifo_inst__DOT__rd_wrap;
    __Vdly__top__DOT__weight_fifo_inst__DOT__rd_wrap = 0;
    SData/*11:0*/ __VdlyVal__top__DOT__burst_fifo_inst__DOT__buffer__v0;
    __VdlyVal__top__DOT__burst_fifo_inst__DOT__buffer__v0 = 0;
    CData/*1:0*/ __VdlyDim0__top__DOT__burst_fifo_inst__DOT__buffer__v0;
    __VdlyDim0__top__DOT__burst_fifo_inst__DOT__buffer__v0 = 0;
    CData/*0:0*/ __VdlySet__top__DOT__burst_fifo_inst__DOT__buffer__v0;
    __VdlySet__top__DOT__burst_fifo_inst__DOT__buffer__v0 = 0;
    VlWide<4>/*127:0*/ __VdlyVal__top__DOT__weight_memory_inst__DOT__mem__v0;
    VL_ZERO_W(128, __VdlyVal__top__DOT__weight_memory_inst__DOT__mem__v0);
    CData/*5:0*/ __VdlyDim0__top__DOT__weight_memory_inst__DOT__mem__v0;
    __VdlyDim0__top__DOT__weight_memory_inst__DOT__mem__v0 = 0;
    CData/*0:0*/ __VdlySet__top__DOT__weight_memory_inst__DOT__mem__v0;
    __VdlySet__top__DOT__weight_memory_inst__DOT__mem__v0 = 0;
    VlWide<4>/*127:0*/ __VdlyVal__top__DOT__weight_fifo_inst__DOT__buffer__v0;
    VL_ZERO_W(128, __VdlyVal__top__DOT__weight_fifo_inst__DOT__buffer__v0);
    CData/*1:0*/ __VdlyDim0__top__DOT__weight_fifo_inst__DOT__buffer__v0;
    __VdlyDim0__top__DOT__weight_fifo_inst__DOT__buffer__v0 = 0;
    CData/*0:0*/ __VdlySet__top__DOT__weight_fifo_inst__DOT__buffer__v0;
    __VdlySet__top__DOT__weight_fifo_inst__DOT__buffer__v0 = 0;
    // Body
    __VdlySet__top__DOT__burst_fifo_inst__DOT__buffer__v0 = 0U;
    __VdlySet__top__DOT__weight_fifo_inst__DOT__buffer__v0 = 0U;
    __Vdly__top__DOT__weight_fifo_inst__DOT__rd_wrap 
        = vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap;
    __Vdly__top__DOT__burst_fifo_inst__DOT__rd_wrap 
        = vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_wrap;
    __Vdly__top__DOT__weight_fifo_inst__DOT__rd_addr 
        = vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr;
    __Vdly__top__DOT__burst_fifo_inst__DOT__rd_addr 
        = vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_addr;
    __Vdly__top__DOT__burst_fifo_inst__DOT__wr_wrap 
        = vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_wrap;
    __Vdly__top__DOT__weight_fifo_inst__DOT__wr_wrap 
        = vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap;
    __Vdly__top__DOT__burst_fifo_inst__DOT__wr_addr 
        = vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_addr;
    __Vdly__top__DOT__weight_fifo_inst__DOT__wr_addr 
        = vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_addr;
    __Vdly__top__DOT__curr_burst_addr_reg = vlSelfRef.top__DOT__curr_burst_addr_reg;
    __VdlySet__top__DOT__weight_memory_inst__DOT__mem__v0 = 0U;
    if ((1U & (~ (IData)(vlSelfRef.top__DOT__weight_memory_inst__DOT__web1_reg)))) {
        __VdlyVal__top__DOT__weight_memory_inst__DOT__mem__v0[0U] 
            = vlSelfRef.top__DOT__weight_memory_inst__DOT__din1_reg[0U];
        __VdlyVal__top__DOT__weight_memory_inst__DOT__mem__v0[1U] 
            = vlSelfRef.top__DOT__weight_memory_inst__DOT__din1_reg[1U];
        __VdlyVal__top__DOT__weight_memory_inst__DOT__mem__v0[2U] 
            = vlSelfRef.top__DOT__weight_memory_inst__DOT__din1_reg[2U];
        __VdlyVal__top__DOT__weight_memory_inst__DOT__mem__v0[3U] 
            = vlSelfRef.top__DOT__weight_memory_inst__DOT__din1_reg[3U];
        __VdlyDim0__top__DOT__weight_memory_inst__DOT__mem__v0 
            = vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg;
        __VdlySet__top__DOT__weight_memory_inst__DOT__mem__v0 = 1U;
    }
    if ((1U & (~ (IData)(vlSelfRef.rst)))) {
        if (((0U == (IData)(vlSelfRef.top__DOT__state)) 
             & (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg))) {
            vlSelfRef.top__DOT__curr_burst_boundary 
                = (0x3fU & ((((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_reg) 
                              >> 6U) + (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_reg)) 
                            - (IData)(1U)));
        }
    }
    if (vlSelfRef.rst) {
        __Vdly__top__DOT__weight_fifo_inst__DOT__rd_addr = 0U;
        __Vdly__top__DOT__weight_fifo_inst__DOT__rd_wrap = 0U;
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap 
            = __Vdly__top__DOT__weight_fifo_inst__DOT__rd_wrap;
        __Vdly__top__DOT__burst_fifo_inst__DOT__rd_addr = 0U;
        __Vdly__top__DOT__burst_fifo_inst__DOT__rd_wrap = 0U;
        vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_wrap 
            = __Vdly__top__DOT__burst_fifo_inst__DOT__rd_wrap;
        __Vdly__top__DOT__burst_fifo_inst__DOT__wr_addr = 0U;
        __Vdly__top__DOT__burst_fifo_inst__DOT__wr_wrap = 0U;
        vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_wrap 
            = __Vdly__top__DOT__burst_fifo_inst__DOT__wr_wrap;
        vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_addr 
            = __Vdly__top__DOT__burst_fifo_inst__DOT__wr_addr;
        __Vdly__top__DOT__weight_fifo_inst__DOT__wr_addr = 0U;
        __Vdly__top__DOT__weight_fifo_inst__DOT__wr_wrap = 0U;
    } else {
        if (((~ (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer_empty)) 
             & (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__load_output_reg))) {
            if ((3U == (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr))) {
                __Vdly__top__DOT__weight_fifo_inst__DOT__rd_wrap 
                    = (1U & (~ (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap)));
                __Vdly__top__DOT__weight_fifo_inst__DOT__rd_addr = 0U;
            } else {
                __Vdly__top__DOT__weight_fifo_inst__DOT__rd_addr 
                    = (3U & ((IData)(1U) + (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr)));
            }
        }
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap 
            = __Vdly__top__DOT__weight_fifo_inst__DOT__rd_wrap;
        if (((~ (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer_empty)) 
             & (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__load_output_reg))) {
            if ((3U == (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_addr))) {
                __Vdly__top__DOT__burst_fifo_inst__DOT__rd_wrap 
                    = (1U & (~ (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_wrap)));
                __Vdly__top__DOT__burst_fifo_inst__DOT__rd_addr = 0U;
            } else {
                __Vdly__top__DOT__burst_fifo_inst__DOT__rd_addr 
                    = (3U & ((IData)(1U) + (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_addr)));
            }
        }
        vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_wrap 
            = __Vdly__top__DOT__burst_fifo_inst__DOT__rd_wrap;
        if (((IData)(vlSelfRef.in_burst_ready) & (IData)(vlSelfRef.in_burst_valid))) {
            __VdlyVal__top__DOT__burst_fifo_inst__DOT__buffer__v0 
                = (((IData)(vlSelfRef.in_burst_addr) 
                    << 6U) | (IData)(vlSelfRef.in_burst_len));
            __VdlyDim0__top__DOT__burst_fifo_inst__DOT__buffer__v0 
                = vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_addr;
            __VdlySet__top__DOT__burst_fifo_inst__DOT__buffer__v0 = 1U;
            if ((3U == (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_addr))) {
                __Vdly__top__DOT__burst_fifo_inst__DOT__wr_wrap 
                    = (1U & (~ (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_wrap)));
                __Vdly__top__DOT__burst_fifo_inst__DOT__wr_addr = 0U;
            } else {
                __Vdly__top__DOT__burst_fifo_inst__DOT__wr_addr 
                    = (3U & ((IData)(1U) + (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_addr)));
            }
        }
        vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_wrap 
            = __Vdly__top__DOT__burst_fifo_inst__DOT__wr_wrap;
        vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_addr 
            = __Vdly__top__DOT__burst_fifo_inst__DOT__wr_addr;
        if (vlSelfRef.top__DOT__weight_fifo_inst__DOT__insert) {
            __VdlyVal__top__DOT__weight_fifo_inst__DOT__buffer__v0[0U] 
                = vlSelfRef.weight_data[0U];
            __VdlyVal__top__DOT__weight_fifo_inst__DOT__buffer__v0[1U] 
                = vlSelfRef.weight_data[1U];
            __VdlyVal__top__DOT__weight_fifo_inst__DOT__buffer__v0[2U] 
                = vlSelfRef.weight_data[2U];
            __VdlyVal__top__DOT__weight_fifo_inst__DOT__buffer__v0[3U] 
                = vlSelfRef.weight_data[3U];
            __VdlyDim0__top__DOT__weight_fifo_inst__DOT__buffer__v0 
                = vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_addr;
            __VdlySet__top__DOT__weight_fifo_inst__DOT__buffer__v0 = 1U;
            if ((3U == (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_addr))) {
                __Vdly__top__DOT__weight_fifo_inst__DOT__wr_wrap 
                    = (1U & (~ (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap)));
                __Vdly__top__DOT__weight_fifo_inst__DOT__wr_addr = 0U;
            } else {
                __Vdly__top__DOT__weight_fifo_inst__DOT__wr_addr 
                    = (3U & ((IData)(1U) + (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_addr)));
            }
        }
    }
    vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap 
        = __Vdly__top__DOT__weight_fifo_inst__DOT__wr_wrap;
    vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_addr 
        = __Vdly__top__DOT__weight_fifo_inst__DOT__wr_addr;
    if (__VdlySet__top__DOT__weight_memory_inst__DOT__mem__v0) {
        vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[__VdlyDim0__top__DOT__weight_memory_inst__DOT__mem__v0][0U] 
            = __VdlyVal__top__DOT__weight_memory_inst__DOT__mem__v0[0U];
        vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[__VdlyDim0__top__DOT__weight_memory_inst__DOT__mem__v0][1U] 
            = __VdlyVal__top__DOT__weight_memory_inst__DOT__mem__v0[1U];
        vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[__VdlyDim0__top__DOT__weight_memory_inst__DOT__mem__v0][2U] 
            = __VdlyVal__top__DOT__weight_memory_inst__DOT__mem__v0[2U];
        vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[__VdlyDim0__top__DOT__weight_memory_inst__DOT__mem__v0][3U] 
            = __VdlyVal__top__DOT__weight_memory_inst__DOT__mem__v0[3U];
    }
    if (vlSelfRef.rst) {
        __Vdly__top__DOT__curr_burst_addr_reg = 0U;
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_valid_reg = 0U;
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_reg[0U] = 0U;
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_reg[1U] = 0U;
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_reg[2U] = 0U;
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_reg[3U] = 0U;
    } else {
        if (((0U == (IData)(vlSelfRef.top__DOT__state)) 
             & (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg))) {
            __Vdly__top__DOT__curr_burst_addr_reg = 
                (0x3fU & ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_reg) 
                          >> 6U));
        } else if ((1U == (IData)(vlSelfRef.top__DOT__state))) {
            __Vdly__top__DOT__curr_burst_addr_reg = 
                (0x3fU & ((IData)(1U) + (IData)(vlSelfRef.top__DOT__curr_burst_addr_reg)));
        }
        if (vlSelfRef.top__DOT__weight_fifo_inst__DOT__load_output_reg) {
            if ((1U & (~ (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer_empty)))) {
                vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_valid_reg = 1U;
                vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_reg[0U] 
                    = vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer
                    [vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr][0U];
                vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_reg[1U] 
                    = vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer
                    [vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr][1U];
                vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_reg[2U] 
                    = vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer
                    [vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr][2U];
                vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_reg[3U] 
                    = vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer
                    [vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr][3U];
            } else {
                vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_valid_reg = 0U;
            }
        }
    }
    if (__VdlySet__top__DOT__weight_fifo_inst__DOT__buffer__v0) {
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer[__VdlyDim0__top__DOT__weight_fifo_inst__DOT__buffer__v0][0U] 
            = __VdlyVal__top__DOT__weight_fifo_inst__DOT__buffer__v0[0U];
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer[__VdlyDim0__top__DOT__weight_fifo_inst__DOT__buffer__v0][1U] 
            = __VdlyVal__top__DOT__weight_fifo_inst__DOT__buffer__v0[1U];
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer[__VdlyDim0__top__DOT__weight_fifo_inst__DOT__buffer__v0][2U] 
            = __VdlyVal__top__DOT__weight_fifo_inst__DOT__buffer__v0[2U];
        vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer[__VdlyDim0__top__DOT__weight_fifo_inst__DOT__buffer__v0][3U] 
            = __VdlyVal__top__DOT__weight_fifo_inst__DOT__buffer__v0[3U];
    }
    vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr 
        = __Vdly__top__DOT__weight_fifo_inst__DOT__rd_addr;
    if ((1U == (IData)(vlSelfRef.top__DOT__state))) {
        vlSelfRef.top__DOT__weight_memory_inst__DOT__web1_reg = 1U;
        vlSelfRef.top__DOT__weight_memory_inst__DOT__din1_reg[0U] = 0U;
        vlSelfRef.top__DOT__weight_memory_inst__DOT__din1_reg[1U] = 0U;
        vlSelfRef.top__DOT__weight_memory_inst__DOT__din1_reg[2U] = 0U;
        vlSelfRef.top__DOT__weight_memory_inst__DOT__din1_reg[3U] = 0U;
        vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg 
            = vlSelfRef.top__DOT__curr_burst_addr_reg;
    }
    if (vlSelfRef.rst) {
        vlSelfRef.top__DOT__weight_valid = 0U;
        vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg = 0U;
        vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_reg = 0U;
        vlSelfRef.top__DOT__state = 0U;
    } else {
        if (((0U == (IData)(vlSelfRef.top__DOT__state)) 
             & (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg))) {
            vlSelfRef.top__DOT__weight_valid = 0U;
        } else if ((1U == (IData)(vlSelfRef.top__DOT__state))) {
            vlSelfRef.top__DOT__weight_valid = 1U;
        } else if ((2U == (IData)(vlSelfRef.top__DOT__state))) {
            vlSelfRef.top__DOT__weight_valid = 0U;
        }
        if (vlSelfRef.top__DOT__burst_fifo_inst__DOT__load_output_reg) {
            if ((1U & (~ (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer_empty)))) {
                vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg = 1U;
                vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_reg 
                    = vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer
                    [vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_addr];
            } else {
                vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg = 0U;
            }
        }
        vlSelfRef.top__DOT__state = vlSelfRef.top__DOT__next_state;
    }
    vlSelfRef.top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1 
        = ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr) 
           == (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_addr));
    vlSelfRef.top__DOT__curr_burst_addr_reg = __Vdly__top__DOT__curr_burst_addr_reg;
    vlSelfRef.top__DOT__weight_fifo_inst__DOT__insert 
        = ((~ ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1) 
               & ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap) 
                  != (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap)))) 
           & (IData)(vlSelfRef.top__DOT__weight_valid));
    vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer_empty 
        = ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1) 
           & ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap) 
              == (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap)));
    if (__VdlySet__top__DOT__burst_fifo_inst__DOT__buffer__v0) {
        vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer[__VdlyDim0__top__DOT__burst_fifo_inst__DOT__buffer__v0] 
            = __VdlyVal__top__DOT__burst_fifo_inst__DOT__buffer__v0;
    }
    vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_addr 
        = __Vdly__top__DOT__burst_fifo_inst__DOT__rd_addr;
    vlSelfRef.weight_data[0U] = vlSelfRef.top__DOT__weight_memory_inst__DOT__mem
        [vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg][0U];
    vlSelfRef.weight_data[1U] = vlSelfRef.top__DOT__weight_memory_inst__DOT__mem
        [vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg][1U];
    vlSelfRef.weight_data[2U] = vlSelfRef.top__DOT__weight_memory_inst__DOT__mem
        [vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg][2U];
    vlSelfRef.weight_data[3U] = vlSelfRef.top__DOT__weight_memory_inst__DOT__mem
        [vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg][3U];
    vlSelfRef.top__DOT__weight_fifo_inst__DOT__load_output_reg 
        = (1U & ((~ (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer_empty)) 
                 | (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_valid_reg)));
    vlSelfRef.top__DOT__burst_fifo_inst__DOT____VdfgRegularize_h869595dc_0_1 
        = ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_addr) 
           == (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_addr));
    vlSelfRef.in_burst_ready = (1U & (~ ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT____VdfgRegularize_h869595dc_0_1) 
                                         & ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_wrap) 
                                            != (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_wrap)))));
    vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer_empty 
        = ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT____VdfgRegularize_h869595dc_0_1) 
           & ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_wrap) 
              == (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_wrap)));
    vlSelfRef.top__DOT__next_state = vlSelfRef.top__DOT__state;
    if ((0U == (IData)(vlSelfRef.top__DOT__state))) {
        if (vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg) {
            vlSelfRef.top__DOT__next_state = 1U;
        }
    } else if ((1U == (IData)(vlSelfRef.top__DOT__state))) {
        if (((IData)(vlSelfRef.top__DOT__curr_burst_addr_reg) 
             == (IData)(vlSelfRef.top__DOT__curr_burst_boundary))) {
            vlSelfRef.top__DOT__next_state = 2U;
        }
    } else {
        vlSelfRef.top__DOT__next_state = 0U;
    }
    vlSelfRef.top__DOT__burst_fifo_inst__DOT__load_output_reg 
        = (1U & (((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg) 
                  & (0U == (IData)(vlSelfRef.top__DOT__state))) 
                 | ((~ (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg)) 
                    & (~ (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer_empty)))));
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("../hdl/../hdl/top.sv", 6, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("../hdl/../hdl/top.sv", 6, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY(((vlSelfRef.in_burst_addr & 0xc0U)))) {
        Verilated::overWidthError("in_burst_addr");}
    if (VL_UNLIKELY(((vlSelfRef.in_burst_len & 0xc0U)))) {
        Verilated::overWidthError("in_burst_len");}
    if (VL_UNLIKELY(((vlSelfRef.in_burst_valid & 0xfeU)))) {
        Verilated::overWidthError("in_burst_valid");}
}
#endif  // VL_DEBUG
