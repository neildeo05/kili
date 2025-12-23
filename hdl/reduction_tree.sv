module reduction_tree #(TILE_SIZE = 8) (
  input logic clk,
  input logic rst,
  input logic [TILE_SIZE-1:0][7:0] products,
  input logic product_valid,
  output logic [7:0] sum,
  output logic sum_valid
);
  localparam NUM_STAGES = $clog2(TILE_SIZE);

  logic [NUM_STAGES:0][TILE_SIZE-1:0][7:0] level_data; //TODO: Explore if there is a way to avoid the extra space per dimension
  logic [NUM_STAGES:0] level_valid;

  assign level_data[0] = products;
  assign level_valid[0] = product_valid; //{TILE_SIZE{product_valid}};

  generate
    for (genvar s = 0; s < NUM_STAGES; s++) begin
      localparam STAGE_WIDTH = TILE_SIZE >> s; // Width of the stage, since we are halving the size each stage
      localparam OUT_WIDTH = STAGE_WIDTH / 2; // Each stage outputs half the number of values as the previous stage

      reduction_stage #(.STAGE_SIZE(STAGE_WIDTH)) stage_inst (
        .clk(clk),
        .rst(rst),
        .sum_in(level_data[s][STAGE_WIDTH-1:0]),
        .sum_in_valid(level_valid[s]),
        .sum(level_data[s+1][OUT_WIDTH-1:0]),
        .sum_valid(level_valid[s+1])
      );
    end
  endgenerate

  // Final output is the single element from the last stage
  assign sum = level_data[NUM_STAGES][0];
  assign sum_valid = level_valid[NUM_STAGES];

endmodule