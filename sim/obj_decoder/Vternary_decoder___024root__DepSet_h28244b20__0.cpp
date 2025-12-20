// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vternary_decoder.h for the primary calling header

#include "Vternary_decoder__pch.h"
#include "Vternary_decoder___024root.h"

void Vternary_decoder___024root___ico_sequent__TOP__0(Vternary_decoder___024root* vlSelf);

void Vternary_decoder___024root___eval_ico(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_ico\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vternary_decoder___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vternary_decoder___024root___ico_sequent__TOP__0(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___ico_sequent__TOP__0\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ ternary_decoder__DOT__y0;
    ternary_decoder__DOT__y0 = 0;
    CData/*0:0*/ ternary_decoder__DOT__y1;
    ternary_decoder__DOT__y1 = 0;
    CData/*0:0*/ ternary_decoder__DOT__y2;
    ternary_decoder__DOT__y2 = 0;
    CData/*0:0*/ ternary_decoder__DOT__y3;
    ternary_decoder__DOT__y3 = 0;
    CData/*0:0*/ ternary_decoder__DOT__y5;
    ternary_decoder__DOT__y5 = 0;
    CData/*0:0*/ ternary_decoder__DOT__y6;
    ternary_decoder__DOT__y6 = 0;
    CData/*0:0*/ ternary_decoder__DOT__y7;
    ternary_decoder__DOT__y7 = 0;
    CData/*0:0*/ ternary_decoder__DOT__y8;
    ternary_decoder__DOT__y8 = 0;
    CData/*0:0*/ ternary_decoder__DOT__z0;
    ternary_decoder__DOT__z0 = 0;
    CData/*0:0*/ ternary_decoder__DOT__z1;
    ternary_decoder__DOT__z1 = 0;
    CData/*0:0*/ ternary_decoder__DOT__z2;
    ternary_decoder__DOT__z2 = 0;
    CData/*0:0*/ ternary_decoder__DOT__x0;
    ternary_decoder__DOT__x0 = 0;
    CData/*0:0*/ ternary_decoder__DOT__x1;
    ternary_decoder__DOT__x1 = 0;
    CData/*0:0*/ ternary_decoder__DOT__x2;
    ternary_decoder__DOT__x2 = 0;
    CData/*0:0*/ ternary_decoder__DOT__x3;
    ternary_decoder__DOT__x3 = 0;
    CData/*0:0*/ ternary_decoder__DOT__x4;
    ternary_decoder__DOT__x4 = 0;
    CData/*0:0*/ ternary_decoder__DOT__x5;
    ternary_decoder__DOT__x5 = 0;
    CData/*0:0*/ ternary_decoder__DOT__x6;
    ternary_decoder__DOT__x6 = 0;
    CData/*0:0*/ ternary_decoder__DOT__x7;
    ternary_decoder__DOT__x7 = 0;
    CData/*0:0*/ ternary_decoder__DOT__x8;
    ternary_decoder__DOT__x8 = 0;
    CData/*0:0*/ ternary_decoder__DOT__x9;
    ternary_decoder__DOT__x9 = 0;
    CData/*0:0*/ ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_6;
    ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_6 = 0;
    CData/*0:0*/ ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_9;
    ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_9 = 0;
    // Body
    ternary_decoder__DOT__y8 = (IData)((0xc1U == (0xc1U 
                                                  & (IData)(vlSelfRef.encoded_vals))));
    ternary_decoder__DOT__z0 = (IData)((0x20U == (0x62U 
                                                  & (IData)(vlSelfRef.encoded_vals))));
    ternary_decoder__DOT__z1 = (IData)((4U == (0xcU 
                                               & (IData)(vlSelfRef.encoded_vals))));
    ternary_decoder__DOT__y3 = (IData)((9U == (0xbU 
                                               & (IData)(vlSelfRef.encoded_vals))));
    ternary_decoder__DOT__y6 = (IData)((8U == (9U & (IData)(vlSelfRef.encoded_vals))));
    ternary_decoder__DOT__y5 = (IData)((0U == (3U & (IData)(vlSelfRef.encoded_vals))));
    ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_9 
        = (IData)((0x10U != (0x11U & (IData)(vlSelfRef.encoded_vals))));
    ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_6 
        = (IData)((8U != (0xcU & (IData)(vlSelfRef.encoded_vals))));
    ternary_decoder__DOT__z2 = (IData)((2U == (3U & (IData)(vlSelfRef.encoded_vals))));
    ternary_decoder__DOT__y1 = (IData)((3U == (3U & (IData)(vlSelfRef.encoded_vals))));
    ternary_decoder__DOT__y2 = ((IData)(ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_9) 
                                & (((IData)(vlSelfRef.encoded_vals) 
                                    ^ ((IData)(vlSelfRef.encoded_vals) 
                                       >> 1U)) & (IData)(
                                                         (0U 
                                                          == 
                                                          (0xcU 
                                                           & (IData)(vlSelfRef.encoded_vals))))));
    ternary_decoder__DOT__y0 = (1U & (((~ ((IData)(vlSelfRef.encoded_vals) 
                                           >> 1U)) 
                                       & (IData)(ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_6)) 
                                      | ((((IData)(vlSelfRef.encoded_vals) 
                                           >> 7U) & (IData)(ternary_decoder__DOT__z0)) 
                                         ^ ((IData)(ternary_decoder__DOT__y5) 
                                            ^ (IData)(
                                                      ((0x82U 
                                                        == 
                                                        (0x82U 
                                                         & (IData)(vlSelfRef.encoded_vals))) 
                                                       & (~ (IData)(ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_6))))))));
    ternary_decoder__DOT__x5 = (((IData)(ternary_decoder__DOT__y3) 
                                 & (IData)((0U == (0x60U 
                                                   & (IData)(vlSelfRef.encoded_vals))))) 
                                | (((IData)(ternary_decoder__DOT__y6) 
                                    & (IData)((0x44U 
                                               == (0x44U 
                                                   & (IData)(vlSelfRef.encoded_vals))))) 
                                   | ((~ (IData)(ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_6)) 
                                      & (IData)(ternary_decoder__DOT__y5))));
    ternary_decoder__DOT__x3 = ((((IData)(vlSelfRef.encoded_vals) 
                                  & (IData)(ternary_decoder__DOT__z0)) 
                                 | (IData)(ternary_decoder__DOT__z2)) 
                                & ((~ ((IData)(vlSelfRef.encoded_vals) 
                                       >> 7U)) & (~ (IData)(ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_6))));
    ternary_decoder__DOT__x2 = ((IData)(ternary_decoder__DOT__z2) 
                                & (IData)((0xcU == 
                                           (0xcU & (IData)(vlSelfRef.encoded_vals)))));
    ternary_decoder__DOT__x0 = ((IData)(ternary_decoder__DOT__y1) 
                                & ((IData)(vlSelfRef.encoded_vals) 
                                   >> 2U));
    ternary_decoder__DOT__x7 = (1U & ((IData)(((0U 
                                                == 
                                                (5U 
                                                 & (IData)(vlSelfRef.encoded_vals))) 
                                               & (2U 
                                                  != 
                                                  (0xaU 
                                                   & (IData)(vlSelfRef.encoded_vals))))) 
                                      | ((IData)(ternary_decoder__DOT__y2) 
                                         & ((IData)(vlSelfRef.encoded_vals) 
                                            >> 5U))));
    ternary_decoder__DOT__x4 = (((~ ((IData)(vlSelfRef.encoded_vals) 
                                     >> 5U)) & (IData)(ternary_decoder__DOT__y2)) 
                                | ((IData)(ternary_decoder__DOT__z1) 
                                   | (IData)(ternary_decoder__DOT__y1)));
    ternary_decoder__DOT__x9 = (1U & (((~ ((IData)(vlSelfRef.encoded_vals) 
                                           >> 2U)) 
                                       & (IData)(ternary_decoder__DOT__y6)) 
                                      | (((~ (IData)(ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_9)) 
                                          & (~ ((IData)(vlSelfRef.encoded_vals) 
                                                >> 3U))) 
                                         ^ (((IData)(ternary_decoder__DOT__x2) 
                                             & (IData)(
                                                       (0x50U 
                                                        == 
                                                        (0x50U 
                                                         & (IData)(vlSelfRef.encoded_vals))))) 
                                            ^ ((IData)(ternary_decoder__DOT__y5) 
                                               ^ ((IData)(ternary_decoder__DOT__y3) 
                                                  & (IData)(
                                                            (0x40U 
                                                             == 
                                                             (0xc0U 
                                                              & (IData)(vlSelfRef.encoded_vals))))))))));
    ternary_decoder__DOT__y7 = ((~ ((IData)(vlSelfRef.encoded_vals) 
                                    >> 6U)) & (IData)(ternary_decoder__DOT__x2));
    ternary_decoder__DOT__x1 = (1U & ((IData)(((4U 
                                                == 
                                                (0x46U 
                                                 & (IData)(vlSelfRef.encoded_vals))) 
                                               & (1U 
                                                  != 
                                                  (0x21U 
                                                   & (IData)(vlSelfRef.encoded_vals))))) 
                                      | ((~ ((IData)(vlSelfRef.encoded_vals) 
                                             >> 3U)) 
                                         | (IData)(ternary_decoder__DOT__x0))));
    ternary_decoder__DOT__x8 = ((((~ ((IData)(vlSelfRef.encoded_vals) 
                                      >> 7U)) | (IData)(ternary_decoder__DOT____VdfgRegularize_hb0db941f_0_6)) 
                                 & (IData)(ternary_decoder__DOT__y1)) 
                                | (IData)(ternary_decoder__DOT__y7));
    ternary_decoder__DOT__x6 = (1U & ((((IData)(ternary_decoder__DOT__y8) 
                                        | (IData)((2U 
                                                   == 
                                                   (0x12U 
                                                    & (IData)(vlSelfRef.encoded_vals))))) 
                                       & ((IData)(vlSelfRef.encoded_vals) 
                                          >> 2U)) | 
                                      (((IData)(ternary_decoder__DOT__y8) 
                                        & (IData)((8U 
                                                   == 
                                                   (0x18U 
                                                    & (IData)(vlSelfRef.encoded_vals))))) 
                                       | ((IData)(ternary_decoder__DOT__y7) 
                                          | (((IData)(vlSelfRef.encoded_vals) 
                                              & (IData)(ternary_decoder__DOT__z1)) 
                                             | (IData)(ternary_decoder__DOT__y1))))));
    vlSelfRef.decoded_vals = ((((0xfffffe00U & ((((IData)(vlSelfRef.encoded_vals) 
                                                  << 5U) 
                                                 & ((IData)(ternary_decoder__DOT__x3) 
                                                    << 9U)) 
                                                | (((IData)(vlSelfRef.encoded_vals) 
                                                    << 2U) 
                                                   & ((IData)(ternary_decoder__DOT__x1) 
                                                      << 9U)))) 
                                | ((((IData)(ternary_decoder__DOT__x1) 
                                     | (IData)(ternary_decoder__DOT__x3)) 
                                    << 8U) | (0xffffff80U 
                                              & (((IData)(vlSelfRef.encoded_vals) 
                                                  & ((IData)(ternary_decoder__DOT__x5) 
                                                     << 7U)) 
                                                 | (((IData)(vlSelfRef.encoded_vals) 
                                                     << 1U) 
                                                    & ((IData)(ternary_decoder__DOT__x4) 
                                                       << 7U)))))) 
                               | ((((IData)(ternary_decoder__DOT__x4) 
                                    | (IData)(ternary_decoder__DOT__x5)) 
                                   << 6U) | ((0x7fffffe0U 
                                              & (((IData)(vlSelfRef.encoded_vals) 
                                                  >> 1U) 
                                                 & ((IData)(ternary_decoder__DOT__x7) 
                                                    << 5U))) 
                                             | (0xffffffe0U 
                                                & ((IData)(vlSelfRef.encoded_vals) 
                                                   & ((IData)(ternary_decoder__DOT__x6) 
                                                      << 5U)))))) 
                              | (((((IData)(ternary_decoder__DOT__x6) 
                                    | (IData)(ternary_decoder__DOT__x7)) 
                                   << 4U) | (((0x3ffffff8U 
                                               & (((IData)(vlSelfRef.encoded_vals) 
                                                   >> 2U) 
                                                  & ((IData)(ternary_decoder__DOT__x9) 
                                                     << 3U))) 
                                              | (0x7ffffff8U 
                                                 & (((IData)(vlSelfRef.encoded_vals) 
                                                     >> 1U) 
                                                    & ((IData)(ternary_decoder__DOT__x8) 
                                                       << 3U)))) 
                                             | (((IData)(ternary_decoder__DOT__x8) 
                                                 | (IData)(ternary_decoder__DOT__x9)) 
                                                << 2U))) 
                                 | (((0x1ffffffeU & 
                                      (((IData)(vlSelfRef.encoded_vals) 
                                        >> 3U) & ((IData)(ternary_decoder__DOT__y0) 
                                                  << 1U))) 
                                     | (0x3ffffffeU 
                                        & (((IData)(vlSelfRef.encoded_vals) 
                                            >> 2U) 
                                           & ((IData)(ternary_decoder__DOT__x0) 
                                              << 1U)))) 
                                    | ((IData)(ternary_decoder__DOT__x0) 
                                       | (IData)(ternary_decoder__DOT__y0)))));
}

void Vternary_decoder___024root___eval_triggers__ico(Vternary_decoder___024root* vlSelf);

bool Vternary_decoder___024root___eval_phase__ico(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_phase__ico\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vternary_decoder___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vternary_decoder___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vternary_decoder___024root___eval_act(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_act\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vternary_decoder___024root___eval_nba(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_nba\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vternary_decoder___024root___eval_triggers__act(Vternary_decoder___024root* vlSelf);

bool Vternary_decoder___024root___eval_phase__act(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_phase__act\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<0> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vternary_decoder___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vternary_decoder___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vternary_decoder___024root___eval_phase__nba(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_phase__nba\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vternary_decoder___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vternary_decoder___024root___dump_triggers__ico(Vternary_decoder___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vternary_decoder___024root___dump_triggers__nba(Vternary_decoder___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vternary_decoder___024root___dump_triggers__act(Vternary_decoder___024root* vlSelf);
#endif  // VL_DEBUG

void Vternary_decoder___024root___eval(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
            Vternary_decoder___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("../hdl/../hdl/ternary_decoder.sv", 9, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vternary_decoder___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vternary_decoder___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("../hdl/../hdl/ternary_decoder.sv", 9, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vternary_decoder___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("../hdl/../hdl/ternary_decoder.sv", 9, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vternary_decoder___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vternary_decoder___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vternary_decoder___024root___eval_debug_assertions(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_debug_assertions\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}
#endif  // VL_DEBUG
