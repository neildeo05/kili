module tmatmul #(
  parameter TILE_SIZE = 8,
  parameter TRIT_PACK = 5,
  parameter NUM_TILES = (TILE_SIZE + TRIT_PACK-1)/TRIT_PACK
) (
  input logic clk,
  input logic rst,
  input logic [7:0] activations_in [TILE_SIZE], // these activations get broadcasted to all the dot product units
  input logic activations_valid,
  input logic weight_fifo_valid, // we don't want the units to operate separately, so they share a valid signal
  input logic [TILE_SIZE-1:0][NUM_TILES-1:0][7:0] weight_fifo_in,
  output logic [TILE_SIZE-1:0][7:0] dot_out,
  output logic dot_out_valid
);

  // FIFO between local memory and tensor core

  generate
    for(genvar i = 0; i < TILE_SIZE; i++) begin : dot_units
      tdot #(.TILE_SIZE(TILE_SIZE), .TRIT_PACK(TRIT_PACK), .NUM_TILES(NUM_TILES)) tdot_inst (
        .clk(clk),
        .rst(rst),
        .weights_valid(weight_fifo_valid),
        .weights_in(weight_fifo_in[i]),
        .activations_in(activations_in),
        .activations_valid(activations_valid),
        .sum_out(dot_out[i]),
        .sum_out_valid(dot_out_valid)
      );
    end
  endgenerate

endmodule