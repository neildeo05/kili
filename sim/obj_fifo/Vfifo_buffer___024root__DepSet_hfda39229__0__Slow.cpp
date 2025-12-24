// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vfifo_buffer.h for the primary calling header

#include "Vfifo_buffer__pch.h"
#include "Vfifo_buffer__Syms.h"
#include "Vfifo_buffer___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void Vfifo_buffer___024root___dump_triggers__stl(Vfifo_buffer___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vfifo_buffer___024root___eval_triggers__stl(Vfifo_buffer___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root___eval_triggers__stl\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.setBit(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vfifo_buffer___024root___dump_triggers__stl(vlSelf);
    }
#endif
}
