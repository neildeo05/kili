module top #(
  parameter TILE_SIZE = 8,
  parameter TRIT_PACK = 5,
  parameter NUM_TILES = (TILE_SIZE + TRIT_PACK-1)/TRIT_PACK
) (
  input logic clk,
  input logic rst,
  input logic weight_fifo_valid,
  input logic [NUM_TILES-1:0][7:0] weight_fifo_in,
  input logic [7:0] activations_in [TILE_SIZE],
  input logic activations_valid,
  // output logic [TILE_SIZE-1:0][1:0] trit_decoded_weights,
  output logic [7:0] sum_out,
  output logic sum_out_valid,

  // SRAM interface
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

  weight_array weight_array_inst (
    .clk0  (clk),
    .csb0  (sram_csb),
    .web0  (sram_web),
    .addr0 (sram_addr),
    .din0  (sram_din),
    .dout0 (sram_dout)
  );


  tdot #(.TILE_SIZE(TILE_SIZE), .TRIT_PACK(TRIT_PACK), .NUM_TILES(NUM_TILES)) tdot_inst (
    .*
  );
endmodule
