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
  output logic sum_out_valid
);

  logic [TILE_SIZE-1:0][7:0] products, products_next;
  logic products_valid;
  logic [NUM_TILES*10-1:0] all_decoded;

  logic [TILE_SIZE-1:0][1:0] trit_decoded_weights;
  logic trit_decoded_weights_valid;
  logic [TILE_SIZE-1:0][7:0] activations;
  // assign trit_decoded_weights = all_decoded[(TILE_SIZE*2)-1:0];
  logic [7:0] new_data;
  logic sum_valid;


  // Stage 0: Decode the incoming weights
  generate 
    for(genvar i = 0; i < NUM_TILES; i++) begin : decode_weights
      ternary_decoder td (
        .encoded_vals(weight_fifo_in[i]),
        .decoded_vals(all_decoded[i*(TRIT_PACK*2) +: (TRIT_PACK*2)])
      );
    end
  endgenerate

  integer k;
  always_ff @(posedge clk) begin
    if(rst) begin
      trit_decoded_weights <= '0;
      trit_decoded_weights_valid <= '0;
      activations <= '0;
    end else begin
      trit_decoded_weights_valid <= weight_fifo_valid;
      if(weight_fifo_valid) begin
        trit_decoded_weights <= all_decoded[(TILE_SIZE*2)-1:0];
      end
      if(activations_valid) begin
        for(k = 0; k < TILE_SIZE; k++) begin
          activations[k] <= activations_in[k];
        end
      end
    end
  end

  // Stage 1: Multiply stage
  generate
    for(genvar j = 0; j < TILE_SIZE; ++j) begin : multiply_weights
      tmul tm (
        .a(activations[j]),
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
      products_valid <= trit_decoded_weights_valid;
      if(trit_decoded_weights_valid) begin
        products <= products_next;
      end else begin
        products <= '0;
        products_valid <= '0;
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