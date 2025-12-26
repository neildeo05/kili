// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

VL_ATTR_COLD void Vtop___024root___eval_static(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_static\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf);
VL_ATTR_COLD void Vtop___024root____Vm_traceActivitySetAll(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_initial(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vtop___024root___eval_initial__TOP(vlSelf);
    Vtop___024root____Vm_traceActivitySetAll(vlSelf);
}

VL_ATTR_COLD void Vtop___024root___eval_initial__TOP(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_initial__TOP\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.top__DOT__weight_memory_inst__DOT__web1_reg = 1U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0U][0U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[1U][0U] = 1U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[1U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[1U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[1U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[2U][0U] = 2U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[2U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[2U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[2U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[3U][0U] = 3U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[3U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[3U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[3U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[4U][0U] = 4U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[4U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[4U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[4U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[5U][0U] = 5U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[5U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[5U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[5U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[6U][0U] = 6U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[6U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[6U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[6U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[7U][0U] = 7U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[7U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[7U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[7U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[8U][0U] = 8U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[8U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[8U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[8U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[9U][0U] = 9U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[9U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[9U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[9U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xaU][0U] = 0xaU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xaU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xaU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xaU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xbU][0U] = 0xbU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xbU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xbU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xbU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xcU][0U] = 0xcU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xcU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xcU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xcU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xdU][0U] = 0xdU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xdU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xdU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xdU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xeU][0U] = 0xeU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xeU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xeU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xeU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xfU][0U] = 0xfU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xfU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xfU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0xfU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x10U][0U] = 0x10U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x10U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x10U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x10U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x11U][0U] = 0x11U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x11U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x11U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x11U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x12U][0U] = 0x12U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x12U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x12U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x12U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x13U][0U] = 0x13U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x13U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x13U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x13U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x14U][0U] = 0x14U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x14U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x14U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x14U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x15U][0U] = 0x15U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x15U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x15U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x15U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x16U][0U] = 0x16U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x16U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x16U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x16U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x17U][0U] = 0x17U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x17U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x17U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x17U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x18U][0U] = 0x18U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x18U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x18U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x18U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x19U][0U] = 0x19U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x19U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x19U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x19U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1aU][0U] = 0x1aU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1aU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1aU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1aU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1bU][0U] = 0x1bU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1bU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1bU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1bU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1cU][0U] = 0x1cU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1cU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1cU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1cU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1dU][0U] = 0x1dU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1dU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1dU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1dU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1eU][0U] = 0x1eU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1eU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1eU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1eU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1fU][0U] = 0x1fU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1fU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1fU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x1fU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x20U][0U] = 0x20U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x20U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x20U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x20U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x21U][0U] = 0x21U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x21U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x21U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x21U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x22U][0U] = 0x22U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x22U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x22U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x22U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x23U][0U] = 0x23U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x23U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x23U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x23U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x24U][0U] = 0x24U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x24U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x24U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x24U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x25U][0U] = 0x25U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x25U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x25U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x25U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x26U][0U] = 0x26U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x26U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x26U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x26U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x27U][0U] = 0x27U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x27U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x27U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x27U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x28U][0U] = 0x28U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x28U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x28U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x28U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x29U][0U] = 0x29U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x29U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x29U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x29U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2aU][0U] = 0x2aU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2aU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2aU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2aU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2bU][0U] = 0x2bU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2bU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2bU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2bU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2cU][0U] = 0x2cU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2cU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2cU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2cU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2dU][0U] = 0x2dU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2dU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2dU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2dU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2eU][0U] = 0x2eU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2eU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2eU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2eU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2fU][0U] = 0x2fU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2fU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2fU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x2fU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x30U][0U] = 0x30U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x30U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x30U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x30U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x31U][0U] = 0x31U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x31U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x31U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x31U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x32U][0U] = 0x32U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x32U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x32U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x32U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x33U][0U] = 0x33U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x33U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x33U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x33U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x34U][0U] = 0x34U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x34U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x34U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x34U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x35U][0U] = 0x35U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x35U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x35U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x35U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x36U][0U] = 0x36U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x36U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x36U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x36U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x37U][0U] = 0x37U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x37U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x37U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x37U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x38U][0U] = 0x38U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x38U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x38U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x38U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x39U][0U] = 0x39U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x39U][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x39U][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x39U][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3aU][0U] = 0x3aU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3aU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3aU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3aU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3bU][0U] = 0x3bU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3bU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3bU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3bU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3cU][0U] = 0x3cU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3cU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3cU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3cU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3dU][0U] = 0x3dU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3dU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3dU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3dU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3eU][0U] = 0x3eU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3eU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3eU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3eU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3fU][0U] = 0x3fU;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3fU][1U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3fU][2U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__mem[0x3fU][3U] = 0U;
    vlSelfRef.top__DOT__weight_memory_inst__DOT__unnamedblk1__DOT__i = 0x40U;
}

VL_ATTR_COLD void Vtop___024root___eval_final(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_final\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_settle(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_settle\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
            Vtop___024root___dump_triggers__stl(vlSelf);
#endif
            VL_FATAL_MT("../hdl/../hdl/top.sv", 6, "", "Settle region did not converge.");
        }
        __VstlIterCount = ((IData)(1U) + __VstlIterCount);
        __VstlContinue = 0U;
        if (Vtop___024root___eval_phase__stl(vlSelf)) {
            __VstlContinue = 1U;
        }
        vlSelfRef.__VstlFirstIteration = 0U;
    }
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf);

VL_ATTR_COLD void Vtop___024root___eval_stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vtop___024root___stl_sequent__TOP__0(vlSelf);
        Vtop___024root____Vm_traceActivitySetAll(vlSelf);
    }
}

VL_ATTR_COLD void Vtop___024root___stl_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___stl_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.weight_data[0U] = vlSelfRef.top__DOT__weight_memory_inst__DOT__mem
        [vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg][0U];
    vlSelfRef.weight_data[1U] = vlSelfRef.top__DOT__weight_memory_inst__DOT__mem
        [vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg][1U];
    vlSelfRef.weight_data[2U] = vlSelfRef.top__DOT__weight_memory_inst__DOT__mem
        [vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg][2U];
    vlSelfRef.weight_data[3U] = vlSelfRef.top__DOT__weight_memory_inst__DOT__mem
        [vlSelfRef.top__DOT__weight_memory_inst__DOT__addr1_reg][3U];
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
    vlSelfRef.top__DOT__burst_fifo_inst__DOT____VdfgRegularize_h869595dc_0_1 
        = ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_addr) 
           == (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_addr));
    vlSelfRef.top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1 
        = ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_addr) 
           == (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_addr));
    vlSelfRef.in_burst_ready = (1U & (~ ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT____VdfgRegularize_h869595dc_0_1) 
                                         & ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_wrap) 
                                            != (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_wrap)))));
    vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer_empty 
        = ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT____VdfgRegularize_h869595dc_0_1) 
           & ((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__rd_wrap) 
              == (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__wr_wrap)));
    vlSelfRef.top__DOT__weight_fifo_inst__DOT__insert 
        = ((~ ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1) 
               & ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap) 
                  != (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap)))) 
           & (IData)(vlSelfRef.top__DOT__weight_valid));
    vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer_empty 
        = ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1) 
           & ((IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__rd_wrap) 
              == (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__wr_wrap)));
    vlSelfRef.top__DOT__burst_fifo_inst__DOT__load_output_reg 
        = (1U & (((IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg) 
                  & (0U == (IData)(vlSelfRef.top__DOT__state))) 
                 | ((~ (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__out_valid_reg)) 
                    & (~ (IData)(vlSelfRef.top__DOT__burst_fifo_inst__DOT__buffer_empty)))));
    vlSelfRef.top__DOT__weight_fifo_inst__DOT__load_output_reg 
        = (1U & ((~ (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__buffer_empty)) 
                 | (IData)(vlSelfRef.top__DOT__weight_fifo_inst__DOT__out_valid_reg)));
}

VL_ATTR_COLD void Vtop___024root___eval_triggers__stl(Vtop___024root* vlSelf);

VL_ATTR_COLD bool Vtop___024root___eval_phase__stl(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__stl\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VstlExecute;
    // Body
    Vtop___024root___eval_triggers__stl(vlSelf);
    __VstlExecute = vlSelfRef.__VstlTriggered.any();
    if (__VstlExecute) {
        Vtop___024root___eval_stl(vlSelf);
    }
    return (__VstlExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___dump_triggers__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
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

VL_ATTR_COLD void Vtop___024root____Vm_traceActivitySetAll(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root____Vm_traceActivitySetAll\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vm_traceActivity[0U] = 1U;
    vlSelfRef.__Vm_traceActivity[1U] = 1U;
}

VL_ATTR_COLD void Vtop___024root___ctor_var_reset(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ctor_var_reset\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    const uint64_t __VscopeHash = VL_MURMUR64_HASH(vlSelf->name());
    vlSelf->clk = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16707436170211756652ull);
    vlSelf->rst = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 18209466448985614591ull);
    vlSelf->in_burst_addr = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 5502113323528510855ull);
    vlSelf->in_burst_len = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 5524839208257555720ull);
    vlSelf->in_burst_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5844739301862290038ull);
    vlSelf->in_burst_ready = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14717993335939252466ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->weight_data, __VscopeHash, 9000556573228251116ull);
    vlSelf->top__DOT__curr_burst_addr_reg = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 18043684107442418231ull);
    vlSelf->top__DOT__state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 9904540416334528851ull);
    vlSelf->top__DOT__next_state = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 14234869201619147039ull);
    vlSelf->top__DOT__curr_burst_boundary = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 11404522110661055877ull);
    vlSelf->top__DOT__weight_valid = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 8814711740459645179ull);
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        vlSelf->top__DOT__burst_fifo_inst__DOT__buffer[__Vi0] = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 18199541262947914570ull);
    }
    vlSelf->top__DOT__burst_fifo_inst__DOT__wr_addr = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 11950173861551087562ull);
    vlSelf->top__DOT__burst_fifo_inst__DOT__rd_addr = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 5722332405978895476ull);
    vlSelf->top__DOT__burst_fifo_inst__DOT__wr_wrap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9326105007742362433ull);
    vlSelf->top__DOT__burst_fifo_inst__DOT__rd_wrap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 6226458108460527215ull);
    vlSelf->top__DOT__burst_fifo_inst__DOT__buffer_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7557293043910387819ull);
    vlSelf->top__DOT__burst_fifo_inst__DOT__out_reg = VL_SCOPED_RAND_RESET_I(12, __VscopeHash, 223704849039248931ull);
    vlSelf->top__DOT__burst_fifo_inst__DOT__out_valid_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 5912835269154682136ull);
    vlSelf->top__DOT__burst_fifo_inst__DOT__load_output_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7145905662910670054ull);
    vlSelf->top__DOT__burst_fifo_inst__DOT____VdfgRegularize_h869595dc_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 16791731355316238058ull);
    for (int __Vi0 = 0; __Vi0 < 64; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(128, vlSelf->top__DOT__weight_memory_inst__DOT__mem[__Vi0], __VscopeHash, 11729163073987584129ull);
    }
    vlSelf->top__DOT__weight_memory_inst__DOT__addr0_reg = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 15786172838458411068ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->top__DOT__weight_memory_inst__DOT__din0_reg, __VscopeHash, 4697295593797913248ull);
    vlSelf->top__DOT__weight_memory_inst__DOT__web1_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 14673741696546447629ull);
    vlSelf->top__DOT__weight_memory_inst__DOT__addr1_reg = VL_SCOPED_RAND_RESET_I(6, __VscopeHash, 13960470932490297404ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->top__DOT__weight_memory_inst__DOT__din1_reg, __VscopeHash, 4289253641505413835ull);
    vlSelf->top__DOT__weight_memory_inst__DOT__unnamedblk1__DOT__i = 0;
    for (int __Vi0 = 0; __Vi0 < 4; ++__Vi0) {
        VL_SCOPED_RAND_RESET_W(128, vlSelf->top__DOT__weight_fifo_inst__DOT__buffer[__Vi0], __VscopeHash, 15440005766498684248ull);
    }
    vlSelf->top__DOT__weight_fifo_inst__DOT__wr_addr = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 8140576077476068219ull);
    vlSelf->top__DOT__weight_fifo_inst__DOT__rd_addr = VL_SCOPED_RAND_RESET_I(2, __VscopeHash, 12722191669402185070ull);
    vlSelf->top__DOT__weight_fifo_inst__DOT__wr_wrap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 10468886021674103032ull);
    vlSelf->top__DOT__weight_fifo_inst__DOT__rd_wrap = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12648476907016419885ull);
    vlSelf->top__DOT__weight_fifo_inst__DOT__buffer_empty = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12559791552038972060ull);
    vlSelf->top__DOT__weight_fifo_inst__DOT__insert = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 7952922124782216177ull);
    VL_SCOPED_RAND_RESET_W(128, vlSelf->top__DOT__weight_fifo_inst__DOT__out_reg, __VscopeHash, 14606285930051347556ull);
    vlSelf->top__DOT__weight_fifo_inst__DOT__out_valid_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 12005910079742769861ull);
    vlSelf->top__DOT__weight_fifo_inst__DOT__load_output_reg = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 2688557304831899674ull);
    vlSelf->top__DOT__weight_fifo_inst__DOT____VdfgRegularize_hc69a2164_0_1 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9652600874654450887ull);
    vlSelf->__Vtrigprevexpr___TOP__clk__0 = VL_SCOPED_RAND_RESET_I(1, __VscopeHash, 9526919608049418986ull);
    for (int __Vi0 = 0; __Vi0 < 2; ++__Vi0) {
        vlSelf->__Vm_traceActivity[__Vi0] = 0;
    }
}
