// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo_buffer.h for the primary calling header

#include "Vfifo_buffer__pch.h"
#include "Vfifo_buffer___024root.h"

void Vfifo_buffer___024root___ico_sequent__TOP__0(Vfifo_buffer___024root* vlSelf);

void Vfifo_buffer___024root___eval_ico(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_ico\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vfifo_buffer___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vfifo_buffer___024root___ico_sequent__TOP__0(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___ico_sequent__TOP__0\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.fifo_buffer__DOT__load_output_reg = (1U 
                                                   & (((IData)(vlSelfRef.fifo_buffer__DOT__out_valid_reg) 
                                                       & (IData)(vlSelfRef.output_ready)) 
                                                      | ((~ (IData)(vlSelfRef.fifo_buffer__DOT__out_valid_reg)) 
                                                         & (~ (IData)(vlSelfRef.fifo_buffer__DOT__buffer_empty)))));
}

void Vfifo_buffer___024root___eval_triggers__ico(Vfifo_buffer___024root* vlSelf);

bool Vfifo_buffer___024root___eval_phase__ico(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_phase__ico\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vfifo_buffer___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vfifo_buffer___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vfifo_buffer___024root___eval_act(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_act\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vfifo_buffer___024root___nba_sequent__TOP__0(Vfifo_buffer___024root* vlSelf);

void Vfifo_buffer___024root___eval_nba(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_nba\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vfifo_buffer___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

VL_INLINE_OPT void Vfifo_buffer___024root___nba_sequent__TOP__0(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___nba_sequent__TOP__0\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*1:0*/ __Vdly__fifo_buffer__DOT__wr_addr;
    __Vdly__fifo_buffer__DOT__wr_addr = 0;
    CData/*0:0*/ __Vdly__fifo_buffer__DOT__wr_wrap;
    __Vdly__fifo_buffer__DOT__wr_wrap = 0;
    CData/*1:0*/ __Vdly__fifo_buffer__DOT__rd_addr;
    __Vdly__fifo_buffer__DOT__rd_addr = 0;
    CData/*0:0*/ __Vdly__fifo_buffer__DOT__rd_wrap;
    __Vdly__fifo_buffer__DOT__rd_wrap = 0;
    SData/*15:0*/ __VdlyVal__fifo_buffer__DOT__buffer__v0;
    __VdlyVal__fifo_buffer__DOT__buffer__v0 = 0;
    CData/*1:0*/ __VdlyDim0__fifo_buffer__DOT__buffer__v0;
    __VdlyDim0__fifo_buffer__DOT__buffer__v0 = 0;
    CData/*0:0*/ __VdlySet__fifo_buffer__DOT__buffer__v0;
    __VdlySet__fifo_buffer__DOT__buffer__v0 = 0;
    // Body
    __VdlySet__fifo_buffer__DOT__buffer__v0 = 0U;
    __Vdly__fifo_buffer__DOT__rd_wrap = vlSelfRef.fifo_buffer__DOT__rd_wrap;
    __Vdly__fifo_buffer__DOT__wr_wrap = vlSelfRef.fifo_buffer__DOT__wr_wrap;
    __Vdly__fifo_buffer__DOT__rd_addr = vlSelfRef.fifo_buffer__DOT__rd_addr;
    __Vdly__fifo_buffer__DOT__wr_addr = vlSelfRef.fifo_buffer__DOT__wr_addr;
    if (vlSelfRef.rst) {
        __Vdly__fifo_buffer__DOT__rd_addr = 0U;
        __Vdly__fifo_buffer__DOT__rd_wrap = 0U;
        __Vdly__fifo_buffer__DOT__wr_addr = 0U;
        __Vdly__fifo_buffer__DOT__wr_wrap = 0U;
        vlSelfRef.fifo_buffer__DOT__out_valid_reg = 0U;
        vlSelfRef.fifo_buffer__DOT__out_reg = 0U;
    } else {
        if (((~ (IData)(vlSelfRef.fifo_buffer__DOT__buffer_empty)) 
             & (IData)(vlSelfRef.fifo_buffer__DOT__load_output_reg))) {
            if ((3U == (IData)(vlSelfRef.fifo_buffer__DOT__rd_addr))) {
                __Vdly__fifo_buffer__DOT__rd_wrap = 
                    (1U & (~ (IData)(vlSelfRef.fifo_buffer__DOT__rd_wrap)));
                __Vdly__fifo_buffer__DOT__rd_addr = 0U;
            } else {
                __Vdly__fifo_buffer__DOT__rd_addr = 
                    (3U & ((IData)(1U) + (IData)(vlSelfRef.fifo_buffer__DOT__rd_addr)));
            }
        }
        if (((IData)(vlSelfRef.input_ready) & (IData)(vlSelfRef.input_valid))) {
            __VdlyVal__fifo_buffer__DOT__buffer__v0 
                = vlSelfRef.input_data;
            __VdlyDim0__fifo_buffer__DOT__buffer__v0 
                = vlSelfRef.fifo_buffer__DOT__wr_addr;
            __VdlySet__fifo_buffer__DOT__buffer__v0 = 1U;
            if ((3U == (IData)(vlSelfRef.fifo_buffer__DOT__wr_addr))) {
                __Vdly__fifo_buffer__DOT__wr_wrap = 
                    (1U & (~ (IData)(vlSelfRef.fifo_buffer__DOT__wr_wrap)));
                __Vdly__fifo_buffer__DOT__wr_addr = 0U;
            } else {
                __Vdly__fifo_buffer__DOT__wr_addr = 
                    (3U & ((IData)(1U) + (IData)(vlSelfRef.fifo_buffer__DOT__wr_addr)));
            }
        }
        if (vlSelfRef.fifo_buffer__DOT__load_output_reg) {
            if ((1U & (~ (IData)(vlSelfRef.fifo_buffer__DOT__buffer_empty)))) {
                vlSelfRef.fifo_buffer__DOT__out_valid_reg = 1U;
                vlSelfRef.fifo_buffer__DOT__out_reg 
                    = vlSelfRef.fifo_buffer__DOT__buffer
                    [vlSelfRef.fifo_buffer__DOT__rd_addr];
            } else {
                vlSelfRef.fifo_buffer__DOT__out_valid_reg = 0U;
            }
        }
    }
    vlSelfRef.fifo_buffer__DOT__rd_wrap = __Vdly__fifo_buffer__DOT__rd_wrap;
    vlSelfRef.fifo_buffer__DOT__wr_wrap = __Vdly__fifo_buffer__DOT__wr_wrap;
    vlSelfRef.fifo_buffer__DOT__wr_addr = __Vdly__fifo_buffer__DOT__wr_addr;
    if (__VdlySet__fifo_buffer__DOT__buffer__v0) {
        vlSelfRef.fifo_buffer__DOT__buffer[__VdlyDim0__fifo_buffer__DOT__buffer__v0] 
            = __VdlyVal__fifo_buffer__DOT__buffer__v0;
    }
    vlSelfRef.fifo_buffer__DOT__rd_addr = __Vdly__fifo_buffer__DOT__rd_addr;
    vlSelfRef.output_valid = vlSelfRef.fifo_buffer__DOT__out_valid_reg;
    vlSelfRef.output_data = vlSelfRef.fifo_buffer__DOT__out_reg;
    vlSelfRef.fifo_buffer__DOT____VdfgRegularize_hc69a2164_0_1 
        = ((IData)(vlSelfRef.fifo_buffer__DOT__rd_addr) 
           == (IData)(vlSelfRef.fifo_buffer__DOT__wr_addr));
    vlSelfRef.input_ready = (1U & (~ ((IData)(vlSelfRef.fifo_buffer__DOT____VdfgRegularize_hc69a2164_0_1) 
                                      & ((IData)(vlSelfRef.fifo_buffer__DOT__wr_wrap) 
                                         != (IData)(vlSelfRef.fifo_buffer__DOT__rd_wrap)))));
    vlSelfRef.fifo_buffer__DOT__buffer_empty = ((IData)(vlSelfRef.fifo_buffer__DOT____VdfgRegularize_hc69a2164_0_1) 
                                                & ((IData)(vlSelfRef.fifo_buffer__DOT__rd_wrap) 
                                                   == (IData)(vlSelfRef.fifo_buffer__DOT__wr_wrap)));
    vlSelfRef.fifo_buffer__DOT__load_output_reg = (1U 
                                                   & (((IData)(vlSelfRef.fifo_buffer__DOT__out_valid_reg) 
                                                       & (IData)(vlSelfRef.output_ready)) 
                                                      | ((~ (IData)(vlSelfRef.fifo_buffer__DOT__out_valid_reg)) 
                                                         & (~ (IData)(vlSelfRef.fifo_buffer__DOT__buffer_empty)))));
}

void Vfifo_buffer___024root___eval_triggers__act(Vfifo_buffer___024root* vlSelf);

bool Vfifo_buffer___024root___eval_phase__act(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_phase__act\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vfifo_buffer___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vfifo_buffer___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vfifo_buffer___024root___eval_phase__nba(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_phase__nba\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vfifo_buffer___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_buffer___024root___dump_triggers__ico(Vfifo_buffer___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_buffer___024root___dump_triggers__nba(Vfifo_buffer___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_buffer___024root___dump_triggers__act(Vfifo_buffer___024root* vlSelf);
#endif  // VL_DEBUG

void Vfifo_buffer___024root___eval(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vfifo_buffer___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("../hdl/../hdl/fifo_buffer.sv", 5, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vfifo_buffer___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vfifo_buffer___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("../hdl/../hdl/fifo_buffer.sv", 5, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vfifo_buffer___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("../hdl/../hdl/fifo_buffer.sv", 5, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vfifo_buffer___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vfifo_buffer___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vfifo_buffer___024root___eval_debug_assertions(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_debug_assertions\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.rst & 0xfeU)))) {
        Verilated::overWidthError("rst");}
    if (VL_UNLIKELY(((vlSelfRef.input_valid & 0xfeU)))) {
        Verilated::overWidthError("input_valid");}
    if (VL_UNLIKELY(((vlSelfRef.output_ready & 0xfeU)))) {
        Verilated::overWidthError("output_ready");}
}
#endif  // VL_DEBUG
