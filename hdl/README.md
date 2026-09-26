# Kili (temporary name) ternary AI accelerator

# Some instructions
```
GEMV:
Instruction[31:27] = rs3 (burst length)
Instruction[26:25] = 2'b0
Instruction[24:20] = rs2 (weight addr)
Instruction[19:15] = rs1 (acivation addr)
Instruction[14:12] = 3'b0
Instruction[11:7] = rd (result buffer addr)
Instruction[6:0] = 0b0101011 (opcode)
```
### Skid Buffers
There are two types of skid buffers in use in this design, the in_chan skid buffer and the out_chan skid buffer. The in_chan buffer is used specifically for channels where the master/slave is getting data from the other one, like the read data channel from the perspective of the master. It specifically does not have buffered outputs -> this means that the input will appear on the output in the same clock cycle. This means that it should not be used as a flip flop, but can be used as a buffer in between two flip-flops, say between the slave output and the master input. The out_chan buffer is used specifically for channels where the master/slave is giving data to the other one, like the read address channel. The outputs appear on the next rising edge after the input, which means they act as a buffer/pipeline stage. The output from the master can go into this buffer, and can then feed into the slave, mitigating large slack issues with a pure combinational path


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