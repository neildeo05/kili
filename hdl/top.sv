module top(

  input logic clk,
  input logic rst,
  input  logic        sram_csb,   // active low chip select
  input  logic        sram_web,   // active low write enable
  input  logic [5:0]  sram_addr,
  input  logic [15:0] sram_din,
  output logic [15:0] sram_dout
);

/*
Memory System:
Local Core Memory: (1kB local buffer)
  - 16-bit words
  - 64 "sets"

*/

  // Local Core Memory
  // FIFO between local memory and tensor core


  local_memory local_memory_inst (
    .clk0  (clk),
    .csb0  (sram_csb),
    .web0  (sram_web),
    .addr0 (sram_addr),
    .din0  (sram_din),
    .dout0 (sram_dout)
  );


endmodule
