module reduction_stage #(STAGE_SIZE = 8)(
  input logic clk,
  input logic rst,
  input logic [STAGE_SIZE-1:0][7:0] sum_in,
  input logic sum_in_valid,
  output logic [(STAGE_SIZE/2)-1:0][7:0] sum,
  output logic sum_valid
);


  logic [STAGE_SIZE/2-1:0] sum_valid_internal;
  assign sum_valid = |sum_valid_internal;
  generate
    for(genvar i = 0; i < STAGE_SIZE-1; i+=2) begin
      adder_stage adder_stage_i (
        .clk(clk),
        .rst(rst),
        .a_valid(sum_in_valid),
        .b_valid(sum_in_valid),
        .a(sum_in[i]),
        .b(sum_in[i+1]),
        .out(sum[i/2]),
        .out_valid(sum_valid_internal[i/2])
      );
    end
  endgenerate
endmodule