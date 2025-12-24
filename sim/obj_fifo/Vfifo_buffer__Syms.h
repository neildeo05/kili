// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table internal header
//
// Internal details; most calling programs do not need this header,
// unless using verilator public meta comments.

#ifndef VERILATED_VFIFO_BUFFER__SYMS_H_
#define VERILATED_VFIFO_BUFFER__SYMS_H_  // guard

#include "verilated.h"

// INCLUDE MODEL CLASS

#include "Vfifo_buffer.h"

// INCLUDE MODULE CLASSES
#include "Vfifo_buffer___024root.h"

// SYMS CLASS (contains all model state)
class alignas(VL_CACHE_LINE_BYTES)Vfifo_buffer__Syms final : public VerilatedSyms {
  public:
    // INTERNAL STATE
    Vfifo_buffer* const __Vm_modelp;
    bool __Vm_activity = false;  ///< Used by trace routines to determine change occurred
    uint32_t __Vm_baseCode = 0;  ///< Used by trace routines when tracing multiple models
    VlDeleter __Vm_deleter;
    bool __Vm_didInit = false;

    // MODULE INSTANCE STATE
    Vfifo_buffer___024root         TOP;

    // CONSTRUCTORS
    Vfifo_buffer__Syms(VerilatedContext* contextp, const char* namep, Vfifo_buffer* modelp);
    ~Vfifo_buffer__Syms();

    // METHODS
    const char* name() { return TOP.name(); }
};

#endif  // guard
