// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VTERNARY_DECODER__SYMS_H_
#define VERILATED_VTERNARY_DECODER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vternary_decoder.h"

// INCLUDE MODULE CLASSES
#include "Vternary_decoder___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vternary_decoder__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vternary_decoder* const __Vm_modelp;
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vternary_decoder___024root     TOP;

    // CONSTRUCTORS
    Vternary_decoder__Syms(VerilatedContext* contextp, const char* namep, Vternary_decoder* modelp);
    ~Vternary_decoder__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
