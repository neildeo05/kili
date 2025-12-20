// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vternary_decoder.h for the primary calling header

#include "Vternary_decoder__pch.h"
#include "Vternary_decoder__Syms.h"
#include "Vternary_decoder___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vternary_decoder___024root___dump_triggers__stl(Vternary_decoder___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vternary_decoder___024root___eval_triggers__stl(Vternary_decoder___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vternary_decoder___024root___eval_triggers__stl\n"); );
    Vternary_decoder__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.setBit(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vternary_decoder___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
