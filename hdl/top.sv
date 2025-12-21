module top #(
  parameter TILE_SIZE = 8,
  parameter TRIT_PACK = 5,
  parameter NUM_TILES = (TILE_SIZE + TRIT_PACK-1)/TRIT_PACK
) (
  input logic [NUM_TILES-1:0][7:0] weights_in,
  input logic [7:0] activations [TILE_SIZE],
  output logic [TILE_SIZE-1:0][1:0] trit_decoded_weights,
  output logic [7:0] products [TILE_SIZE]
);

  logic [NUM_TILES-1:0][9:0] decoded_weights;
  
  logic [NUM_TILES*10-1:0] all_decoded;
  
  generate
    for (genvar k = 0; k < NUM_TILES; k++) begin
      assign all_decoded[k*10 +: 10] = decoded_weights[k];
    end
  endgenerate
  assign trit_decoded_weights = all_decoded[TILE_SIZE*2-1:0];
  always_comb begin
    $display("input_weights = %b, %b, decoded_weights: %b, %b, trit_decoded_weights: %b", weights_in[1], weights_in[0], decoded_weights[1], decoded_weights[0], trit_decoded_weights);
  end


  generate 
    for(genvar i = 0; i < NUM_TILES; i++) begin
      ternary_decoder td (
        .encoded_vals(weights_in[i]),
        .decoded_vals(decoded_weights[i])
      );
    end
  endgenerate
  generate
    for(genvar j = 0; j < TILE_SIZE; ++j) begin
      tmul tm (
        .a(activations[j]),
        .b(trit_decoded_weights[j]),
        .c(products[j])
      );
    end
  endgenerate


  // Reduction tree to sum up all 4 of the values


endmodule