// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vternary_decoder__pch.h"

//============================================================
// Constructors

Vternary_decoder::Vternary_decoder(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vternary_decoder__Syms(contextp(), _vcname__, this)}
    , encoded_vals{vlSymsp->TOP.encoded_vals}
    , decoded_vals{vlSymsp->TOP.decoded_vals}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
}

Vternary_decoder::Vternary_decoder(const char* _vcname__)
    : Vternary_decoder(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vternary_decoder::~Vternary_decoder() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vternary_decoder___024root___eval_debug_assertions(Vternary_decoder___024root* vlSelf);
#endif  // VL_DEBUG
void Vternary_decoder___024root___eval_static(Vternary_decoder___024root* vlSelf);
void Vternary_decoder___024root___eval_initial(Vternary_decoder___024root* vlSelf);
void Vternary_decoder___024root___eval_settle(Vternary_decoder___024root* vlSelf);
void Vternary_decoder___024root___eval(Vternary_decoder___024root* vlSelf);

void Vternary_decoder::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vternary_decoder::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vternary_decoder___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vternary_decoder___024root___eval_static(&(vlSymsp->TOP));
        Vternary_decoder___024root___eval_initial(&(vlSymsp->TOP));
        Vternary_decoder___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vternary_decoder___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vternary_decoder::eventsPending() { return false; }

uint64_t Vternary_decoder::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vternary_decoder::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vternary_decoder___024root___eval_final(Vternary_decoder___024root* vlSelf);

VL_ATTR_COLD void Vternary_decoder::final() {
    Vternary_decoder___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vternary_decoder::hierName() const { return vlSymsp->name(); }
const char* Vternary_decoder::modelName() const { return "Vternary_decoder"; }
unsigned Vternary_decoder::threads() const { return 1; }
void Vternary_decoder::prepareClone() const { contextp()->prepareClone(); }
void Vternary_decoder::atClone() const {
    contextp()->threadPoolpOnClone();
}
