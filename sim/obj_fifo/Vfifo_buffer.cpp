// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Model implementation (design independent parts)

#include "Vfifo_buffer__pch.h"
#include "verilated_vcd_c.h"

//============================================================
// Constructors

Vfifo_buffer::Vfifo_buffer(VerilatedContext* _vcontextp__, const char* _vcname__)
    : VerilatedModel{*_vcontextp__}
    , vlSymsp{new Vfifo_buffer__Syms(contextp(), _vcname__, this)}
    , clk{vlSymsp->TOP.clk}
    , rst{vlSymsp->TOP.rst}
    , input_valid{vlSymsp->TOP.input_valid}
    , input_ready{vlSymsp->TOP.input_ready}
    , output_valid{vlSymsp->TOP.output_valid}
    , output_ready{vlSymsp->TOP.output_ready}
    , input_data{vlSymsp->TOP.input_data}
    , output_data{vlSymsp->TOP.output_data}
    , rootp{&(vlSymsp->TOP)}
{
    // Register model with the context
    contextp()->addModel(this);
    contextp()->traceBaseModelCbAdd(
        [this](VerilatedTraceBaseC* tfp, int levels, int options) { traceBaseModel(tfp, levels, options); });
}

Vfifo_buffer::Vfifo_buffer(const char* _vcname__)
    : Vfifo_buffer(Verilated::threadContextp(), _vcname__)
{
}

//============================================================
// Destructor

Vfifo_buffer::~Vfifo_buffer() {
    delete vlSymsp;
}

//============================================================
// Evaluation function

#ifdef VL_DEBUG
void Vfifo_buffer___024root___eval_debug_assertions(Vfifo_buffer___024root* vlSelf);
#endif  // VL_DEBUG
void Vfifo_buffer___024root___eval_static(Vfifo_buffer___024root* vlSelf);
void Vfifo_buffer___024root___eval_initial(Vfifo_buffer___024root* vlSelf);
void Vfifo_buffer___024root___eval_settle(Vfifo_buffer___024root* vlSelf);
void Vfifo_buffer___024root___eval(Vfifo_buffer___024root* vlSelf);

void Vfifo_buffer::eval_step() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vfifo_buffer::eval_step\n"); );
#ifdef VL_DEBUG
    // Debug assertions
    Vfifo_buffer___024root___eval_debug_assertions(&(vlSymsp->TOP));
#endif  // VL_DEBUG
    vlSymsp->__Vm_activity = true;
    vlSymsp->__Vm_deleter.deleteAll();
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) {
        vlSymsp->__Vm_didInit = true;
        VL_DEBUG_IF(VL_DBG_MSGF("+ Initial\n"););
        Vfifo_buffer___024root___eval_static(&(vlSymsp->TOP));
        Vfifo_buffer___024root___eval_initial(&(vlSymsp->TOP));
        Vfifo_buffer___024root___eval_settle(&(vlSymsp->TOP));
    }
    VL_DEBUG_IF(VL_DBG_MSGF("+ Eval\n"););
    Vfifo_buffer___024root___eval(&(vlSymsp->TOP));
    // Evaluate cleanup
    Verilated::endOfEval(vlSymsp->__Vm_evalMsgQp);
}

//============================================================
// Events and timing
bool Vfifo_buffer::eventsPending() { return false; }

uint64_t Vfifo_buffer::nextTimeSlot() {
    VL_FATAL_MT(__FILE__, __LINE__, "", "No delays in the design");
    return 0;
}

//============================================================
// Utilities

const char* Vfifo_buffer::name() const {
    return vlSymsp->name();
}

//============================================================
// Invoke final blocks

void Vfifo_buffer___024root___eval_final(Vfifo_buffer___024root* vlSelf);

VL_ATTR_COLD void Vfifo_buffer::final() {
    Vfifo_buffer___024root___eval_final(&(vlSymsp->TOP));
}

//============================================================
// Implementations of abstract methods from VerilatedModel

const char* Vfifo_buffer::hierName() const { return vlSymsp->name(); }
const char* Vfifo_buffer::modelName() const { return "Vfifo_buffer"; }
unsigned Vfifo_buffer::threads() const { return 1; }
void Vfifo_buffer::prepareClone() const { contextp()->prepareClone(); }
void Vfifo_buffer::atClone() const {
    contextp()->threadPoolpOnClone();
}
std::unique_ptr<VerilatedTraceConfig> Vfifo_buffer::traceConfig() const {
    return std::unique_ptr<VerilatedTraceConfig>{new VerilatedTraceConfig{false, false, false}};
};

//============================================================
// Trace configuration

void Vfifo_buffer___024root__trace_decl_types(VerilatedVcd* tracep);

void Vfifo_buffer___024root__trace_init_top(Vfifo_buffer___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD static void trace_init(void* voidSelf, VerilatedVcd* tracep, uint32_t code) {
    // Callback from tracep->open()
    Vfifo_buffer___024root* const __restrict vlSelf VL_ATTR_UNUSED = static_cast<Vfifo_buffer___024root*>(voidSelf);
    Vfifo_buffer__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    if (!vlSymsp->_vm_contextp__->calcUnusedSigs()) {
        VL_FATAL_MT(__FILE__, __LINE__, __FILE__,
            "Turning on wave traces requires Verilated::traceEverOn(true) call before time 0.");
    }
    vlSymsp->__Vm_baseCode = code;
    tracep->pushPrefix(std::string{vlSymsp->name()}, VerilatedTracePrefixType::SCOPE_MODULE);
    Vfifo_buffer___024root__trace_decl_types(tracep);
    Vfifo_buffer___024root__trace_init_top(vlSelf, tracep);
    tracep->popPrefix();
}

VL_ATTR_COLD void Vfifo_buffer___024root__trace_register(Vfifo_buffer___024root* vlSelf, VerilatedVcd* tracep);

VL_ATTR_COLD void Vfifo_buffer::traceBaseModel(VerilatedTraceBaseC* tfp, int levels, int options) {
    (void)levels; (void)options;
    VerilatedVcdC* const stfp = dynamic_cast<VerilatedVcdC*>(tfp);
    if (VL_UNLIKELY(!stfp)) {
        vl_fatal(__FILE__, __LINE__, __FILE__,"'Vfifo_buffer::trace()' called on non-VerilatedVcdC object;"
            " use --trace-fst with VerilatedFst object, and --trace-vcd with VerilatedVcd object");
    }
    stfp->spTrace()->addModel(this);
    stfp->spTrace()->addInitCb(&trace_init, &(vlSymsp->TOP));
    Vfifo_buffer___024root__trace_register(&(vlSymsp->TOP), stfp->spTrace());
}
