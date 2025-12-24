// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo_buffer.h for the primary calling header

#include "Vfifo_buffer__pch.h"
#include "Vfifo_buffer___024root.h"

VL_ATTR_COLD void Vfifo_buffer___024root___eval_static(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_static\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vfifo_buffer___024root___eval_initial(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_initial\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vfifo_buffer___024root___eval_final(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_final\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_buffer___024root___dump_triggers__stl(Vfifo_buffer___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vfifo_buffer___024root___eval_phase__stl(Vfifo_buffer___024root* vlSelf);

VL_ATTR_COLD void Vfifo_buffer___024root___eval_settle(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_settle\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VstlIterCount;
    CData/*0:0*/ __VstlContinue;
    // Body
    __VstlIterCount = 0U;
    vlSelfRef.__VstlFirstIteration = 1U;
    __VstlContinue = 1U;
    while (__VstlContinue) {
        if (VL_UNLIKELY(((0x64U < __VstlIterCount)))) {
#ifdef VL_DEBUG
            Vfifo_buffer___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("../hdl/../hdl/fifo_buffer.sv", 5, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vfifo_buffer___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_buffer___024root___dump_triggers__stl(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___dump_triggers__stl\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VstlTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        VL_DBG_MSGF("         'stl' region trigger index 0 is active: Internal 'stl' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vfifo_buffer___024root___stl_sequent__TOP__0(Vfifo_buffer___024root* vlSelf);
VL_ATTR_COLD void Vfifo_buffer___024root____Vm_traceActivitySetAll(Vfifo_buffer___024root* vlSelf);

VL_ATTR_COLD void Vfifo_buffer___024root___eval_stl(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_stl\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vfifo_buffer___024root___stl_sequent__TOP__0(vlSelf);
        Vfifo_buffer___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD void Vfifo_buffer___024root___stl_sequent__TOP__0(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___stl_sequent__TOP__0\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
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

VL_ATTR_COLD void Vfifo_buffer___024root___eval_triggers__stl(Vfifo_buffer___024root* vlSelf);

VL_ATTR_COLD bool Vfifo_buffer___024root___eval_phase__stl(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_phase__stl\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vfifo_buffer___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vfifo_buffer___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_buffer___024root___dump_triggers__ico(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___dump_triggers__ico\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VicoTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        VL_DBG_MSGF("         'ico' region trigger index 0 is active: Internal 'ico' trigger - first iteration\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_buffer___024root___dump_triggers__act(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___dump_triggers__act\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VactTriggered.word(0U))) {
        VL_DBG_MSGF("         'act' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_buffer___024root___dump_triggers__nba(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___dump_triggers__nba\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VL_DBG_MSGF("         'nba' region trigger index 0 is active: @(posedge clk)\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vfifo_buffer___024root____Vm_traceActivitySetAll(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root____Vm_traceActivitySetAll\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vfifo_buffer___024root___ctor_var_reset(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___ctor_var_reset\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->input_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 4270309033785105452ull);
    vlSelf->input_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5031374033172706937ull);
    vlSelf->input_data = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 1923588759227995539ull);
    vlSelf->output_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14078276386344907199ull);
    vlSelf->output_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15744654871367209719ull);
    vlSelf->output_data = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 7032170951333504304ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->fifo_buffer__DOT__buffer[__Vi0] = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 836420934150588922ull);
    }
    vlSelf->fifo_buffer__DOT__wr_addr = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 15288164902780009342ull);
    vlSelf->fifo_buffer__DOT__rd_addr = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 13131192656316084040ull);
    vlSelf->fifo_buffer__DOT__wr_wrap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 15903423345328041009ull);
    vlSelf->fifo_buffer__DOT__rd_wrap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8280509421465267299ull);
    vlSelf->fifo_buffer__DOT__buffer_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 1534262369242930653ull);
    vlSelf->fifo_buffer__DOT__out_reg = VL_SCOPED_RAND_RESET_I(16, __VscopeHash, 14298207469024948671ull);
    vlSelf->fifo_buffer__DOT__out_valid_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 3052518765322549776ull);
    vlSelf->fifo_buffer__DOT__load_output_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6411796228888084000ull);
    vlSelf->fifo_buffer__DOT____VdfgRegularize_hc69a2164_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 11544136408822625590ull);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9526919608049418986ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
