# This serves as the tapeout branch -> the branch that is used for the tapeout of a subsection of this chip


- It ONLY has a (5,5) * (5,1) -> ternary GEMV


Simplest possible routine:
- Load the weight tile in -> weight_data + weigh_valid
- Activation In + Activation Valid -> Stores it in the activation buffer
- Start bit is set -> matmul_valid should go high when the buffer is not ready anymore
- each register in the FIFO feeds into a TDot unit
- TDot out populates a result fifo buffer.
- The done signal gets asserted by the unit
- To read out the data from the fifo, we assert a read signal from the input interface, and it serially reads out the outputs from the FIFO