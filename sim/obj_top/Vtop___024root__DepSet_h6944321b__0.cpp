// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

extern const VlUnpacked<CData/*7:0*/, 1024> Vtop__ConstPool__TABLE_h17d98b51_0;

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*7:0*/ top__DOT____Vcellout__genblk1__BRA__0__KET____DOT__tmul_inst__c;
    top__DOT____Vcellout__genblk1__BRA__0__KET____DOT__tmul_inst__c = 0;
    CData/*1:0*/ top__DOT____Vcellinp__genblk1__BRA__0__KET____DOT__tmul_inst__b;
    top__DOT____Vcellinp__genblk1__BRA__0__KET____DOT__tmul_inst__b = 0;
    CData/*7:0*/ top__DOT____Vcellout__genblk1__BRA__1__KET____DOT__tmul_inst__c;
    top__DOT____Vcellout__genblk1__BRA__1__KET____DOT__tmul_inst__c = 0;
    CData/*7:0*/ top__DOT____Vcellout__genblk1__BRA__2__KET____DOT__tmul_inst__c;
    top__DOT____Vcellout__genblk1__BRA__2__KET____DOT__tmul_inst__c = 0;
    CData/*7:0*/ top__DOT____Vcellout__genblk1__BRA__3__KET____DOT__tmul_inst__c;
    top__DOT____Vcellout__genblk1__BRA__3__KET____DOT__tmul_inst__c = 0;
    CData/*7:0*/ top__DOT____Vcellout__genblk1__BRA__4__KET____DOT__tmul_inst__c;
    top__DOT____Vcellout__genblk1__BRA__4__KET____DOT__tmul_inst__c = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__y0;
    top__DOT__ternary_decoder_inst__DOT__y0 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__y1;
    top__DOT__ternary_decoder_inst__DOT__y1 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__y2;
    top__DOT__ternary_decoder_inst__DOT__y2 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__y3;
    top__DOT__ternary_decoder_inst__DOT__y3 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__y5;
    top__DOT__ternary_decoder_inst__DOT__y5 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__y6;
    top__DOT__ternary_decoder_inst__DOT__y6 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__y7;
    top__DOT__ternary_decoder_inst__DOT__y7 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__y8;
    top__DOT__ternary_decoder_inst__DOT__y8 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__z0;
    top__DOT__ternary_decoder_inst__DOT__z0 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__z1;
    top__DOT__ternary_decoder_inst__DOT__z1 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__z2;
    top__DOT__ternary_decoder_inst__DOT__z2 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__x0;
    top__DOT__ternary_decoder_inst__DOT__x0 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__x1;
    top__DOT__ternary_decoder_inst__DOT__x1 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__x2;
    top__DOT__ternary_decoder_inst__DOT__x2 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__x3;
    top__DOT__ternary_decoder_inst__DOT__x3 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__x4;
    top__DOT__ternary_decoder_inst__DOT__x4 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__x5;
    top__DOT__ternary_decoder_inst__DOT__x5 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__x6;
    top__DOT__ternary_decoder_inst__DOT__x6 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__x7;
    top__DOT__ternary_decoder_inst__DOT__x7 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__x8;
    top__DOT__ternary_decoder_inst__DOT__x8 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT__x9;
    top__DOT__ternary_decoder_inst__DOT__x9 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_6;
    top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_6 = 0;
    CData/*0:0*/ top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_9;
    top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_9 = 0;
    CData/*3:0*/ __VdfgRegularize_h7cd686f0_0_0;
    __VdfgRegularize_h7cd686f0_0_0 = 0;
    CData/*5:0*/ __VdfgRegularize_h7cd686f0_0_1;
    __VdfgRegularize_h7cd686f0_0_1 = 0;
    CData/*7:0*/ __VdfgRegularize_h7cd686f0_0_2;
    __VdfgRegularize_h7cd686f0_0_2 = 0;
    SData/*9:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    SData/*9:0*/ __Vtableidx2;
    __Vtableidx2 = 0;
    SData/*9:0*/ __Vtableidx3;
    __Vtableidx3 = 0;
    SData/*9:0*/ __Vtableidx4;
    __Vtableidx4 = 0;
    SData/*9:0*/ __Vtableidx5;
    __Vtableidx5 = 0;
    // Body
    top__DOT__ternary_decoder_inst__DOT__y8 = (IData)(
                                                      (0xc1U 
                                                       == 
                                                       (0xc1U 
                                                        & (IData)(vlSelfRef.weights))));
    top__DOT__ternary_decoder_inst__DOT__z1 = (IData)(
                                                      (4U 
                                                       == 
                                                       (0xcU 
                                                        & (IData)(vlSelfRef.weights))));
    top__DOT__ternary_decoder_inst__DOT__z0 = (IData)(
                                                      (0x20U 
                                                       == 
                                                       (0x62U 
                                                        & (IData)(vlSelfRef.weights))));
    top__DOT__ternary_decoder_inst__DOT__y3 = (IData)(
                                                      (9U 
                                                       == 
                                                       (0xbU 
                                                        & (IData)(vlSelfRef.weights))));
    top__DOT__ternary_decoder_inst__DOT__y6 = (IData)(
                                                      (8U 
                                                       == 
                                                       (9U 
                                                        & (IData)(vlSelfRef.weights))));
    top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_9 
        = (IData)((0x10U != (0x11U & (IData)(vlSelfRef.weights))));
    top__DOT__ternary_decoder_inst__DOT__y5 = (IData)(
                                                      (0U 
                                                       == 
                                                       (3U 
                                                        & (IData)(vlSelfRef.weights))));
    top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_6 
        = (IData)((8U != (0xcU & (IData)(vlSelfRef.weights))));
    top__DOT__ternary_decoder_inst__DOT__z2 = (IData)(
                                                      (2U 
                                                       == 
                                                       (3U 
                                                        & (IData)(vlSelfRef.weights))));
    top__DOT__ternary_decoder_inst__DOT__y1 = (IData)(
                                                      (3U 
                                                       == 
                                                       (3U 
                                                        & (IData)(vlSelfRef.weights))));
    top__DOT__ternary_decoder_inst__DOT__y2 = ((IData)(top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_9) 
                                               & (((IData)(vlSelfRef.weights) 
                                                   ^ 
                                                   ((IData)(vlSelfRef.weights) 
                                                    >> 1U)) 
                                                  & (IData)(
                                                            (0U 
                                                             == 
                                                             (0xcU 
                                                              & (IData)(vlSelfRef.weights))))));
    top__DOT__ternary_decoder_inst__DOT__x5 = (((IData)(top__DOT__ternary_decoder_inst__DOT__y3) 
                                                & (IData)(
                                                          (0U 
                                                           == 
                                                           (0x60U 
                                                            & (IData)(vlSelfRef.weights))))) 
                                               | (((IData)(top__DOT__ternary_decoder_inst__DOT__y6) 
                                                   & (IData)(
                                                             (0x44U 
                                                              == 
                                                              (0x44U 
                                                               & (IData)(vlSelfRef.weights))))) 
                                                  | ((~ (IData)(top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_6)) 
                                                     & (IData)(top__DOT__ternary_decoder_inst__DOT__y5))));
    top__DOT__ternary_decoder_inst__DOT__y0 = (1U & 
                                               (((~ 
                                                  ((IData)(vlSelfRef.weights) 
                                                   >> 1U)) 
                                                 & (IData)(top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_6)) 
                                                | ((((IData)(vlSelfRef.weights) 
                                                     >> 7U) 
                                                    & (IData)(top__DOT__ternary_decoder_inst__DOT__z0)) 
                                                   ^ 
                                                   ((IData)(top__DOT__ternary_decoder_inst__DOT__y5) 
                                                    ^ (IData)(
                                                              ((0x82U 
                                                                == 
                                                                (0x82U 
                                                                 & (IData)(vlSelfRef.weights))) 
                                                               & (~ (IData)(top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_6))))))));
    top__DOT__ternary_decoder_inst__DOT__x3 = ((((IData)(vlSelfRef.weights) 
                                                 & (IData)(top__DOT__ternary_decoder_inst__DOT__z0)) 
                                                | (IData)(top__DOT__ternary_decoder_inst__DOT__z2)) 
                                               & ((~ 
                                                   ((IData)(vlSelfRef.weights) 
                                                    >> 7U)) 
                                                  & (~ (IData)(top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_6))));
    top__DOT__ternary_decoder_inst__DOT__x2 = ((IData)(top__DOT__ternary_decoder_inst__DOT__z2) 
                                               & (IData)(
                                                         (0xcU 
                                                          == 
                                                          (0xcU 
                                                           & (IData)(vlSelfRef.weights)))));
    top__DOT__ternary_decoder_inst__DOT__x0 = ((IData)(top__DOT__ternary_decoder_inst__DOT__y1) 
                                               & ((IData)(vlSelfRef.weights) 
                                                  >> 2U));
    top__DOT__ternary_decoder_inst__DOT__x4 = (((~ 
                                                 ((IData)(vlSelfRef.weights) 
                                                  >> 5U)) 
                                                & (IData)(top__DOT__ternary_decoder_inst__DOT__y2)) 
                                               | ((IData)(top__DOT__ternary_decoder_inst__DOT__z1) 
                                                  | (IData)(top__DOT__ternary_decoder_inst__DOT__y1)));
    top__DOT__ternary_decoder_inst__DOT__x7 = (1U & 
                                               ((IData)(
                                                        ((0U 
                                                          == 
                                                          (5U 
                                                           & (IData)(vlSelfRef.weights))) 
                                                         & (2U 
                                                            != 
                                                            (0xaU 
                                                             & (IData)(vlSelfRef.weights))))) 
                                                | ((IData)(top__DOT__ternary_decoder_inst__DOT__y2) 
                                                   & ((IData)(vlSelfRef.weights) 
                                                      >> 5U))));
    top__DOT__ternary_decoder_inst__DOT__x9 = (1U & 
                                               (((~ 
                                                  ((IData)(vlSelfRef.weights) 
                                                   >> 2U)) 
                                                 & (IData)(top__DOT__ternary_decoder_inst__DOT__y6)) 
                                                | (((~ (IData)(top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_9)) 
                                                    & (~ 
                                                       ((IData)(vlSelfRef.weights) 
                                                        >> 3U))) 
                                                   ^ 
                                                   (((IData)(top__DOT__ternary_decoder_inst__DOT__x2) 
                                                     & (IData)(
                                                               (0x50U 
                                                                == 
                                                                (0x50U 
                                                                 & (IData)(vlSelfRef.weights))))) 
                                                    ^ 
                                                    ((IData)(top__DOT__ternary_decoder_inst__DOT__y5) 
                                                     ^ 
                                                     ((IData)(top__DOT__ternary_decoder_inst__DOT__y3) 
                                                      & (IData)(
                                                                (0x40U 
                                                                 == 
                                                                 (0xc0U 
                                                                  & (IData)(vlSelfRef.weights))))))))));
    top__DOT__ternary_decoder_inst__DOT__y7 = ((~ ((IData)(vlSelfRef.weights) 
                                                   >> 6U)) 
                                               & (IData)(top__DOT__ternary_decoder_inst__DOT__x2));
    top__DOT__ternary_decoder_inst__DOT__x1 = (1U & 
                                               ((IData)(
                                                        ((4U 
                                                          == 
                                                          (0x46U 
                                                           & (IData)(vlSelfRef.weights))) 
                                                         & (1U 
                                                            != 
                                                            (0x21U 
                                                             & (IData)(vlSelfRef.weights))))) 
                                                | ((~ 
                                                    ((IData)(vlSelfRef.weights) 
                                                     >> 3U)) 
                                                   | (IData)(top__DOT__ternary_decoder_inst__DOT__x0))));
    top__DOT____Vcellinp__genblk1__BRA__0__KET____DOT__tmul_inst__b 
        = (((0x1ffffffeU & (((IData)(vlSelfRef.weights) 
                             >> 3U) & ((IData)(top__DOT__ternary_decoder_inst__DOT__y0) 
                                       << 1U))) | (0x3ffffffeU 
                                                   & (((IData)(vlSelfRef.weights) 
                                                       >> 2U) 
                                                      & ((IData)(top__DOT__ternary_decoder_inst__DOT__x0) 
                                                         << 1U)))) 
           | ((IData)(top__DOT__ternary_decoder_inst__DOT__x0) 
              | (IData)(top__DOT__ternary_decoder_inst__DOT__y0)));
    top__DOT__ternary_decoder_inst__DOT__x6 = (1U & 
                                               ((((IData)(top__DOT__ternary_decoder_inst__DOT__y8) 
                                                  | (IData)(
                                                            (2U 
                                                             == 
                                                             (0x12U 
                                                              & (IData)(vlSelfRef.weights))))) 
                                                 & ((IData)(vlSelfRef.weights) 
                                                    >> 2U)) 
                                                | (((IData)(top__DOT__ternary_decoder_inst__DOT__y8) 
                                                    & (IData)(
                                                              (8U 
                                                               == 
                                                               (0x18U 
                                                                & (IData)(vlSelfRef.weights))))) 
                                                   | ((IData)(top__DOT__ternary_decoder_inst__DOT__y7) 
                                                      | (((IData)(vlSelfRef.weights) 
                                                          & (IData)(top__DOT__ternary_decoder_inst__DOT__z1)) 
                                                         | (IData)(top__DOT__ternary_decoder_inst__DOT__y1))))));
    top__DOT__ternary_decoder_inst__DOT__x8 = ((((~ 
                                                  ((IData)(vlSelfRef.weights) 
                                                   >> 7U)) 
                                                 | (IData)(top__DOT__ternary_decoder_inst__DOT____VdfgRegularize_hb0db941f_0_6)) 
                                                & (IData)(top__DOT__ternary_decoder_inst__DOT__y1)) 
                                               | (IData)(top__DOT__ternary_decoder_inst__DOT__y7));
    __Vtableidx1 = ((vlSelfRef.activations[0U] << 2U) 
                    | (IData)(top__DOT____Vcellinp__genblk1__BRA__0__KET____DOT__tmul_inst__b));
    top__DOT____Vcellout__genblk1__BRA__0__KET____DOT__tmul_inst__c 
        = Vtop__ConstPool__TABLE_h17d98b51_0[__Vtableidx1];
    __VdfgRegularize_h7cd686f0_0_0 = (((0x3ffffff8U 
                                        & (((IData)(vlSelfRef.weights) 
                                            >> 2U) 
                                           & ((IData)(top__DOT__ternary_decoder_inst__DOT__x9) 
                                              << 3U))) 
                                       | (0x7ffffff8U 
                                          & (((IData)(vlSelfRef.weights) 
                                              >> 1U) 
                                             & ((IData)(top__DOT__ternary_decoder_inst__DOT__x8) 
                                                << 3U)))) 
                                      | ((((IData)(top__DOT__ternary_decoder_inst__DOT__x8) 
                                           | (IData)(top__DOT__ternary_decoder_inst__DOT__x9)) 
                                          << 2U) | (IData)(top__DOT____Vcellinp__genblk1__BRA__0__KET____DOT__tmul_inst__b)));
    vlSelfRef.products[0U] = top__DOT____Vcellout__genblk1__BRA__0__KET____DOT__tmul_inst__c;
    __Vtableidx2 = ((vlSelfRef.activations[1U] << 2U) 
                    | (3U & ((IData)(__VdfgRegularize_h7cd686f0_0_0) 
                             >> 2U)));
    top__DOT____Vcellout__genblk1__BRA__1__KET____DOT__tmul_inst__c 
        = Vtop__ConstPool__TABLE_h17d98b51_0[__Vtableidx2];
    __VdfgRegularize_h7cd686f0_0_1 = (((0x7fffffe0U 
                                        & (((IData)(vlSelfRef.weights) 
                                            >> 1U) 
                                           & ((IData)(top__DOT__ternary_decoder_inst__DOT__x7) 
                                              << 5U))) 
                                       | (0xffffffe0U 
                                          & ((IData)(vlSelfRef.weights) 
                                             & ((IData)(top__DOT__ternary_decoder_inst__DOT__x6) 
                                                << 5U)))) 
                                      | ((((IData)(top__DOT__ternary_decoder_inst__DOT__x6) 
                                           | (IData)(top__DOT__ternary_decoder_inst__DOT__x7)) 
                                          << 4U) | (IData)(__VdfgRegularize_h7cd686f0_0_0)));
    vlSelfRef.products[1U] = top__DOT____Vcellout__genblk1__BRA__1__KET____DOT__tmul_inst__c;
    __Vtableidx3 = ((vlSelfRef.activations[2U] << 2U) 
                    | (3U & ((IData)(__VdfgRegularize_h7cd686f0_0_1) 
                             >> 4U)));
    top__DOT____Vcellout__genblk1__BRA__2__KET____DOT__tmul_inst__c 
        = Vtop__ConstPool__TABLE_h17d98b51_0[__Vtableidx3];
    __VdfgRegularize_h7cd686f0_0_2 = ((0xffffff80U 
                                       & (((IData)(vlSelfRef.weights) 
                                           & ((IData)(top__DOT__ternary_decoder_inst__DOT__x5) 
                                              << 7U)) 
                                          | (((IData)(vlSelfRef.weights) 
                                              << 1U) 
                                             & ((IData)(top__DOT__ternary_decoder_inst__DOT__x4) 
                                                << 7U)))) 
                                      | ((((IData)(top__DOT__ternary_decoder_inst__DOT__x4) 
                                           | (IData)(top__DOT__ternary_decoder_inst__DOT__x5)) 
                                          << 6U) | (IData)(__VdfgRegularize_h7cd686f0_0_1)));
    vlSelfRef.products[2U] = top__DOT____Vcellout__genblk1__BRA__2__KET____DOT__tmul_inst__c;
    __Vtableidx4 = ((vlSelfRef.activations[3U] << 2U) 
                    | (3U & ((IData)(__VdfgRegularize_h7cd686f0_0_2) 
                             >> 6U)));
    top__DOT____Vcellout__genblk1__BRA__3__KET____DOT__tmul_inst__c 
        = Vtop__ConstPool__TABLE_h17d98b51_0[__Vtableidx4];
    vlSelfRef.decoded_weights = ((0xfffffe00U & ((((IData)(vlSelfRef.weights) 
                                                   << 5U) 
                                                  & ((IData)(top__DOT__ternary_decoder_inst__DOT__x3) 
                                                     << 9U)) 
                                                 | (((IData)(vlSelfRef.weights) 
                                                     << 2U) 
                                                    & ((IData)(top__DOT__ternary_decoder_inst__DOT__x1) 
                                                       << 9U)))) 
                                 | ((((IData)(top__DOT__ternary_decoder_inst__DOT__x1) 
                                      | (IData)(top__DOT__ternary_decoder_inst__DOT__x3)) 
                                     << 8U) | (IData)(__VdfgRegularize_h7cd686f0_0_2)));
    vlSelfRef.products[3U] = top__DOT____Vcellout__genblk1__BRA__3__KET____DOT__tmul_inst__c;
    __Vtableidx5 = ((vlSelfRef.activations[4U] << 2U) 
                    | (3U & ((IData)(vlSelfRef.decoded_weights) 
                             >> 8U)));
    top__DOT____Vcellout__genblk1__BRA__4__KET____DOT__tmul_inst__c 
        = Vtop__ConstPool__TABLE_h17d98b51_0[__Vtableidx5];
    vlSelfRef.products[4U] = top__DOT____Vcellout__genblk1__BRA__4__KET____DOT__tmul_inst__c;
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<0> __VpreTriggered;
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
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
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
            Vtop___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("../hdl/../hdl/top.sv", 1, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtop___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("../hdl/../hdl/top.sv", 1, "", "NBA region did not converge.");
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
                VL_FATAL_MT("../hdl/../hdl/top.sv", 1, "", "Active region did not converge.");
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
}
#endif  // VL_DEBUG
