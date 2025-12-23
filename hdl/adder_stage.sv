module adder_stage (
  input logic clk,
  input logic rst,
  input logic a_valid,
  input logic b_valid,
  input logic [7:0] a,
  input logic [7:0] b,
  output logic [7:0] out,
  output logic out_valid
);
  logic [7:0] sum;
  always_comb begin
    sum = a + b;
  end
  always_ff @(posedge clk) begin
    if(rst) begin
      out <= '0;
      out_valid <= '0;
    end else begin
      if(a_valid && b_valid) begin
        out <= sum;
        out_valid <= '1;
      end else begin
        out <= '0;
        out_valid <= '0;
      end
    end
  end
endmodule