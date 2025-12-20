// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vternary_decoder.h for the primary calling header

#ifndef VERILATED_VTERNARY_DECODER___024ROOT_H_
#define VERILATED_VTERNARY_DECODER___024ROOT_H_  // guard

#include "verilated.h"


class Vternary_decoder__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vternary_decoder___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(encoded_vals,7,0);
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __VactContinue;
    VL_OUT16(decoded_vals,9,0);
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<0> __VactTriggered;
    VlTriggerVec<0> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vternary_decoder__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vternary_decoder___024root(Vternary_decoder__Syms* symsp, const char* v__name);
    ~Vternary_decoder___024root();
    VL_UNCOPYABLE(Vternary_decoder___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
