// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vternary_decoder.h for the primary calling header

#include "Vternary_decoder__pch.h"
#include "Vternary_decoder___024root.h"

VL_ATTR_COLD void Vternary_decoder___024root___eval_static(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_static\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vternary_decoder___024root___eval_initial(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_initial\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

VL_ATTR_COLD void Vternary_decoder___024root___eval_final(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_final\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vternary_decoder___024root___dump_triggers__stl(Vternary_decoder___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vternary_decoder___024root___eval_phase__stl(Vternary_decoder___024root* vlSelf);

VL_ATTR_COLD void Vternary_decoder___024root___eval_settle(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_settle\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
            Vternary_decoder___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("../hdl/../hdl/ternary_decoder.sv", 9, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vternary_decoder___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vternary_decoder___024root___dump_triggers__stl(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___dump_triggers__stl\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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

void Vternary_decoder___024root___ico_sequent__TOP__0(Vternary_decoder___024root* vlSelf);

VL_ATTR_COLD void Vternary_decoder___024root___eval_stl(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_stl\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vternary_decoder___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_ATTR_COLD void Vternary_decoder___024root___eval_triggers__stl(Vternary_decoder___024root* vlSelf);

VL_ATTR_COLD bool Vternary_decoder___024root___eval_phase__stl(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_phase__stl\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vternary_decoder___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vternary_decoder___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vternary_decoder___024root___dump_triggers__ico(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___dump_triggers__ico\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
VL_ATTR_COLD void Vternary_decoder___024root___dump_triggers__act(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___dump_triggers__act\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VactTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

#ifdef VL_DEBUG
VL_ATTR_COLD void Vternary_decoder___024root___dump_triggers__nba(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___dump_triggers__nba\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1U & (~ vlSelfRef.__VnbaTriggered.any()))) {
        VL_DBG_MSGF("         No triggers active\n");
    }
}
#endif  // VL_DEBUG

VL_ATTR_COLD void Vternary_decoder___024root___ctor_var_reset(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___ctor_var_reset\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->encoded_vals = VL_SCOPED_RAND_RESET_I(8, __VscopeHash, 5610962712071728453ull);
    vlSelf->decoded_vals = VL_SCOPED_RAND_RESET_I(10, __VscopeHash, 6989915838517532898ull);
}
