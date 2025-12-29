# Kili (temporary name) ternary AI accelerator
<!-- 
## Operation
Each core contains three units, a tensor unit for GEMVs, a vector unit mostly for activations and elementwise operations, and a scalar unit for operations on reduced outputs. The core-complex is a set of 8x8 cores

There are three local memories inside a core:
 - Weight memory (64 x 16 bytes): contains 64 8x8 weight tiles
 - Activation buffer (64 x 8 bytes): contains a scratchpad buffer where activations reside before they get operated on.
 - Accumulation/Output Buffer (64 x 8 bytes): contans a accumulation buffer for the output of the tensor core

Activation Buffer Interfaces:
 - (WRITE) Burst/single transfer from the core complex to the a core
 - (WRITE) Single transfer from core to core
 - (READ) Each unit is ready to accept an activation input from the buffer

Output Buffer Interfaces:
  - (WRITE) Output of tensor/vector/scalar unit
  - (READ): Core complex/other core wants to read in a speicifc output

Weight Memory Interface:
  - (WRITE) AXI DMA transfers from the core complex to the core
  - (READ) Burst transfers from weight memory to weight FIFO preceding the tensor unit


-->
# Tensor Unit:
The tensor unit computes a GEMV with inputs of a 8x8 weight tile and a 1x8 activation input


Here are the latencies:
- Burst Transfer Core Input to Memory Input: 2 cycles
- Memory Input to Weight FIFO: 1 cycle
- Weight FIFO input to Weight FIFO output (best case): 2 cycles (note that in-flight data due to the burst request will only appear one cycle after the previous data being processed)
- Tensor Core Unit: 5 cycles between input and output

Total 10 cycles between input and output, which is kinda a lot (but it is hyper pipelined so the clock frequency can be higher)

Interfaces/Handshakes:
- Input Burst -> Burst FIFO: if Burst FIFO isn't full, it will always accept
- Memory Request -> Weight FIFO: If weight FIFO isn't full it will always accept
- Weight FIFO -> Ternary Core: Since the ternary core doesn't stall for anything, it will ALWAYS accept
- Activation Input -> Activation Buffer: If the activation input isn't buffered (hasn't been operated on) or isn't activating (currently being operate on) it will accept a new input to the activation buffer
- Activation Chunk -> Tensor Core: When we get a valid activation input and we aren't using the current value in the activation buffer, we overwrite it with the activation value. When the weight FIFO starts sending values to the tensor core, we designate the activation buffer to be "activating", and we start sending chunks to the tensor core. When the weight FIFO is done sending tiles to the tensor core, we designate the buffer "empty", and it is ready to accept a new input

