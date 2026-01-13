module tdot #(
  parameter TILE_SIZE = 4,
  parameter TRIT_PACK = 5,
  parameter NUM_TILES = (TILE_SIZE + TRIT_PACK-1)/TRIT_PACK
) (
  input logic clk,
  input logic rst,
  input logic weights_valid,
  input logic [NUM_TILES-1:0][7:0] weights_in,
  input logic [TILE_SIZE-1:0][7:0] activations_in,
  input logic activations_valid,
  // output logic [TILE_SIZE-1:0][1:0] trit_decoded_weights,
  output logic [7:0] sum_out,
  output logic sum_out_valid
);

  logic [TILE_SIZE-1:0][7:0] products, products_next;
  logic products_valid;

  logic [TILE_SIZE-1:0][1:0] trit_decoded_weights;
  assign trit_decoded_weights = weights_in;


  // Stage 1: Multiply stage
  generate
    for(genvar j = 0; j < TILE_SIZE; ++j) begin : multiply_weights
      tmul tm (
        .a(activations_in[j]),
        .b(trit_decoded_weights[j]),
        .c(products_next[j])
      );
    end
  endgenerate


  // Pipeline
  always_ff @(posedge clk) begin
    if(rst) begin
      products <= '0;
      products_valid <= '0;
    end else begin
      products_valid <= weights_valid & activations_valid;
      if(weights_valid & activations_valid) begin
        products <= products_next;
      end else begin
        products <= '0;
      end
    end
  end

  // Stage 3-(3+log_2(TILE_SIZE)):Reduction tree to sum up all 4 of the values


  reduction_tree rt (
    .clk(clk),
    .rst(rst),
    .products(products),
    .product_valid(products_valid),
    .sum(sum_out),
    .sum_valid(sum_out_valid)
  );






endmodule
