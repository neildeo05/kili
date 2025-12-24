// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Tracing implementation internals
#include "verilated_vcd_c.h"
#include "Vfifo_buffer__Syms.h"


VL_ATTR_COLD void Vfifo_buffer___024root__trace_init_sub__TOP__0(Vfifo_buffer___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root__trace_init_sub__TOP__0\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    const int c = vlSymsp->__Vm_baseCode;
    // Body
    tracep->pushPrefix("$rootio", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBit(c+13,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+15,0,"input_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+16,0,"input_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+17,0,"input_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+18,0,"output_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+19,0,"output_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+20,0,"output_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->popPrefix();
    tracep->pushPrefix("fifo_buffer", VerilatedTracePrefixType::SCOPE_MODULE);
    tracep->declBus(c+25,0,"WIDTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBus(c+26,0,"DEPTH",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::INT, false,-1, 31,0);
    tracep->declBit(c+13,0,"clk",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+14,0,"rst",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+15,0,"input_valid",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+16,0,"input_ready",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+17,0,"input_data",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+18,0,"output_valid",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+19,0,"output_ready",-1, VerilatedTraceSigDirection::INPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+20,0,"output_data",-1, VerilatedTraceSigDirection::OUTPUT, VerilatedTraceSigKind::WIRE, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBus(c+27,0,"PTR_W",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->declBus(c+28,0,"ADDR_LAST",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::PARAMETER, VerilatedTraceSigType::LOGIC, false,-1, 31,0);
    tracep->pushPrefix("buffer", VerilatedTracePrefixType::ARRAY_UNPACKED);
    for (int i = 0; i < 4; ++i) {
        tracep->declBus(c+1+i*1,0,"",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, true,(i+0), 15,0);
    }
    tracep->popPrefix();
    tracep->declBus(c+5,0,"wr_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBus(c+6,0,"rd_addr",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 1,0);
    tracep->declBit(c+7,0,"wr_wrap",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+8,0,"rd_wrap",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+9,0,"buffer_empty",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+10,0,"buffer_full",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+21,0,"insert",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBus(c+11,0,"out_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1, 15,0);
    tracep->declBit(c+12,0,"out_valid_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+22,0,"remove",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+23,0,"load_output_reg",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->declBit(c+24,0,"buffer_read",-1, VerilatedTraceSigDirection::NONE, VerilatedTraceSigKind::VAR, VerilatedTraceSigType::LOGIC, false,-1);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vfifo_buffer___024root__trace_init_top(Vfifo_buffer___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root__trace_init_top\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vfifo_buffer___024root__trace_init_sub__TOP__0(vlSelf, tracep);
}

VL_ATTR_COLD void Vfifo_buffer___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
VL_ATTR_COLD void Vfifo_buffer___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vfifo_buffer___024root__trace_chg_0(void* voidSelf, VerilatedVcd::Buffer* bufp);
void Vfifo_buffer___024root__trace_cleanup(void* voidSelf, VerilatedVcd* /*unused*/);

VL_ATTR_COLD void Vfifo_buffer___024root__trace_register(Vfifo_buffer___024root* vlSelf, VerilatedVcd* tracep) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root__trace_register\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    tracep->addConstCb(&Vfifo_buffer___024root__trace_const_0, 0U, vlSelf);
    tracep->addFullCb(&Vfifo_buffer___024root__trace_full_0, 0U, vlSelf);
    tracep->addChgCb(&Vfifo_buffer___024root__trace_chg_0, 0U, vlSelf);
    tracep->addCleanupCb(&Vfifo_buffer___024root__trace_cleanup, vlSelf);
}

VL_ATTR_COLD void Vfifo_buffer___024root__trace_const_0_sub_0(Vfifo_buffer___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vfifo_buffer___024root__trace_const_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root__trace_const_0\n"); );
    // Init
    Vfifo_buffer___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vfifo_buffer___024root*>(voidSelf);
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vfifo_buffer___024root__trace_const_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vfifo_buffer___024root__trace_const_0_sub_0(Vfifo_buffer___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root__trace_const_0_sub_0\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullIData(oldp+25,(0x10U),32);
    bufp->fullIData(oldp+26,(4U),32);
    bufp->fullIData(oldp+27,(2U),32);
    bufp->fullIData(oldp+28,(3U),32);
}

VL_ATTR_COLD void Vfifo_buffer___024root__trace_full_0_sub_0(Vfifo_buffer___024root* vlSelf, VerilatedVcd::Buffer* bufp);

VL_ATTR_COLD void Vfifo_buffer___024root__trace_full_0(void* voidSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root__trace_full_0\n"); );
    // Init
    Vfifo_buffer___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vfifo_buffer___024root*>(voidSelf);
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    // Body
    Vfifo_buffer___024root__trace_full_0_sub_0((&vlSymsp->TOP), bufp);
}

VL_ATTR_COLD void Vfifo_buffer___024root__trace_full_0_sub_0(Vfifo_buffer___024root* vlSelf, VerilatedVcd::Buffer* bufp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vfifo_buffer___024root__trace_full_0_sub_0\n"); );
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    uint32_t* const oldp VL_ATTR_UNUSED = bufp->oldp(vlSymsp->__Vm_baseCode);
    // Body
    bufp->fullSData(oldp+1,(vlSelfRef.fifo_buffer__DOT__buffer[0]),16);
    bufp->fullSData(oldp+2,(vlSelfRef.fifo_buffer__DOT__buffer[1]),16);
    bufp->fullSData(oldp+3,(vlSelfRef.fifo_buffer__DOT__buffer[2]),16);
    bufp->fullSData(oldp+4,(vlSelfRef.fifo_buffer__DOT__buffer[3]),16);
    bufp->fullCData(oldp+5,(vlSelfRef.fifo_buffer__DOT__wr_addr),2);
    bufp->fullCData(oldp+6,(vlSelfRef.fifo_buffer__DOT__rd_addr),2);
    bufp->fullBit(oldp+7,(vlSelfRef.fifo_buffer__DOT__wr_wrap));
    bufp->fullBit(oldp+8,(vlSelfRef.fifo_buffer__DOT__rd_wrap));
    bufp->fullBit(oldp+9,(vlSelfRef.fifo_buffer__DOT__buffer_empty));
    bufp->fullBit(oldp+10,(((IData)(vlSelfRef.fifo_buffer__DOT____VdfgRegularize_hc69a2164_0_1) 
                            & ((IData)(vlSelfRef.fifo_buffer__DOT__wr_wrap) 
                               != (IData)(vlSelfRef.fifo_buffer__DOT__rd_wrap)))));
    bufp->fullSData(oldp+11,(vlSelfRef.fifo_buffer__DOT__out_reg),16);
    bufp->fullBit(oldp+12,(vlSelfRef.fifo_buffer__DOT__out_valid_reg));
    bufp->fullBit(oldp+13,(vlSelfRef.clk));
    bufp->fullBit(oldp+14,(vlSelfRef.rst));
    bufp->fullBit(oldp+15,(vlSelfRef.input_valid));
    bufp->fullBit(oldp+16,(vlSelfRef.input_ready));
    bufp->fullSData(oldp+17,(vlSelfRef.input_data),16);
    bufp->fullBit(oldp+18,(vlSelfRef.output_valid));
    bufp->fullBit(oldp+19,(vlSelfRef.output_ready));
    bufp->fullSData(oldp+20,(vlSelfRef.output_data),16);
    bufp->fullBit(oldp+21,(((IData)(vlSelfRef.input_ready) 
                            & (IData)(vlSelfRef.input_valid))));
    bufp->fullBit(oldp+22,(((IData)(vlSelfRef.fifo_buffer__DOT__out_valid_reg) 
                            & (IData)(vlSelfRef.output_ready))));
    bufp->fullBit(oldp+23,(vlSelfRef.fifo_buffer__DOT__load_output_reg));
    bufp->fullBit(oldp+24,(((~ (IData)(vlSelfRef.fifo_buffer__DOT__buffer_empty)) 
                            & (IData)(vlSelfRef.fifo_buffer__DOT__load_output_reg))));
}
