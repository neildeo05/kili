# Kili (temporary name) ternary AI accelerator

# Accelerator Architecutre:
## Nomenclature
 - Core: a single computational system that operates on activations as vectors and weights as tiles
 - Tensor Unit: A unit that computes a GEMV (operates on vectors and matrices)
 - Vector Unit: A unit that solely operates on vectors
 - Scalar Unit: A unit that operates on scalar values, similar to an ALU
 - Weight Buffers: Per-core SRAM buffer that contains weight tiles
 - Activation Buffers: Per-core SRAM buffer that contains vectors for use before activation and after matrix computation
 - Cluster: A set of 8 cores, a large second-level SRAM buffer, and a AXI Network Interface/ROB/Router for use with the AXI NoC
 - NoC: a on-chip interconnection network that connects clusters up. Communication is done via the second level SRAM buffer. Memory <-> Memory is the main endpoint structure


# Core
# Second Level SRAM -> Core Interface:
There is an AXI4 bus that interconnects each core and the second level SRAM. This is done due to the necessity for bursts and the non-uniformity of data sizes. 
### Skid Buffers
There are two types of skid buffers in use in this design, the in_chan skid buffer and the out_chan skid buffer. The in_chan buffer is used specifically for channels where the master/slave is getting data from the other one, like the read data channel from the perspective of the master. It specifically does not have buffered outputs -> this means that the input will appear on the output in the same clock cycle. This means that it should not be used as a flip flop, but can be used as a buffer in between two flip-flops, say between the slave output and the master input. The out_chan buffer is used specifically for channels where the master/slave is giving data to the other one, like the read address channel. The outputs appear on the next rising edge after the input, which means they act as a buffer/pipeline stage. The output from the master can go into this buffer, and can then feed into the slave, mitigating large slack issues with a pure combinational path



# Units
There are three units (Tensor, Vector, and Scalar), and 2 memories/buffers (Activation & Weight Buffers). The tensor unit reads from the weight buffer and writes to the activation buffer. The vector and scalar units read/write from the activation buffers (vector & scalar use a shared bus w/ arbiter)

## Tensor Unit:
The tensor unit computes a GEMV with inputs of a 8x8 weight tile and a 1x8 activation input


### Latencies:

Cycles before operation starts:
- Burst Transfer Core Input to Memory Input: 2 cycles
- Memory Input to Weight FIFO: 1 cycle
- Weight FIFO input to Weight FIFO output (best case): 2 cycles (note that in-flight data due to the burst request will only appear one cycle after the previous data being processed)
- Tensor Core Unit: 5 cycles between input and output

Example Latencies (64x64) matrix with (8x8) tiles


Total 10 cycles between input and output, which is kinda a lot (but it is hyper pipelined so the clock frequency can be higher)

### Interfaces/Handshakes:
- Input Burst -> Burst FIFO: if Burst FIFO isn't full, it will always accept
- Memory Request -> Weight FIFO: If weight FIFO isn't full it will always accept
- Weight FIFO -> Ternary Core: Since the ternary core doesn't stall for anything, it will ALWAYS accept
- Activation Input -> Activation Buffer: If the activation input isn't buffered (hasn't been operated on) or isn't activating (currently being operate on) it will accept a new input to the activation buffer
- Activation Chunk -> Tensor Core: When we get a valid activation input and we aren't using the current value in the activation buffer, we overwrite it with the activation value. When the weight FIFO starts sending values to the tensor core, we designate the activation buffer to be "activating", and we start sending chunks to the tensor core. When the weight FIFO is done sending tiles to the tensor core, we designate the buffer "empty", and it is ready to accept a new input



## Vector Unit (TODO)


## Scalar Unit (TODO)

