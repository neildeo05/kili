module tmul (
  input logic [7:0] a,
  input logic [1:0] b,
  output logic [7:0] c
);
  always_comb begin
    c = '0;
    case (b)
      2'b00, 2'b10: c = '0;
      2'b01: c = a;
      2'b11: c = ~a+8'b1;
    endcase
  end
endmodule
