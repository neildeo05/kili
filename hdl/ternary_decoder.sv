// 8-bit to 5-trit decoder based on:
// "Efficient Decompression of Binary Encoded Balanced Ternary Sequences"
// Muller et al., IEEE TVLSI 2019
//
// Notation from paper: × = AND, + = OR, overline = NOT, ⊕ = XOR
//
// Encoding: μ: [-1, 0, 1] → [11, 00, 01]

module ternary_decoder (
  input  logic [7:0] encoded_vals,
  output logic [9:0] decoded_vals
);
  logic [7:0] b;
  logic [9:0] t;
  assign b = encoded_vals;
  assign decoded_vals = t;

  logic b0,b1,b2,b3,b4,b5,b6,b7;
  assign {b7,b6,b5,b4,b3,b2,b1,b0} = b;
  logic y0,y1,y2,y3,y4,y5,y6,y7,y8,y9;
  logic z0,z1,z2;
  logic x0,x1,x2,x3,x4,x5,x6,x7,x8,x9;
  assign z0 = (~b6) & (~b1) &  b5;
  assign z1 = (~b3) &  b2;
  assign z2 = (~b0) &  b1;
  assign y1 = b0 & b1;
  assign y4 = ~(b0 | (~b4));
  assign y2 = (~y4) & (b0 ^ b1) & (~b3) & (~b2);
  assign y3 = b0 & (~b1) & b3;
  assign y5 = (~b0) & (~b1);
  assign y6 = (~b0) & b3;
  assign y9 = ~((~b3) | b2);
  assign x2 = z2 & b3 & b2;
  assign y7 = x2 & (~b6);
  assign y8 = b0 & b7 & b6;
  assign y0 = (~b1) & (~y9) |  b7  &  z0 | y5 | b1 & y9 & b7;
  assign x0 = y1 & b2;
  assign x1 = (~b0 | b5) & (~b6) & (~b1) & b2 | (~b3) | x0;

  assign x3 = ((b0 & z0 | z2) & (~b7) & y9 );

  assign x4 = y2 & (~b5) | z1 | y1;
  assign x5 = y3 & (~b6) & (~b5) | y6 &  b2  &  b6  | y5 &  y9;

  assign x6 = (y8 | b1 & (~b4)) & b2 | y8 & (~b4) & b3 | y7 | b0 & z1 | y1;

  assign x7 = ( (~b0) & (~b2) & ((~b1) | b3) ) |
              ( y2 & b5 );

  assign x8 = ( ((~b7) | (~y9)) & y1 ) | y7;

  assign x9 = y6 & (~b2) | y4 & (~b3) | x2 &  b6  &  b4 | y5 | y3 & ~b7 & b6;

  assign t[0] = x0 | y0;
  assign t[1] = (b4 & y0) | (b3 & x0);
  assign t[2] = x8 | x9;
  assign t[3] = (b5 & x9) | (b4 & x8);
  assign t[4] = x6 | x7;
  assign t[5] = (b6 & x7) | (b5 & x6);
  assign t[6] = x4 | x5;
  assign t[7] = (b7 & x5) | (b6 & x4);
  assign t[8] = x1 | x3;
  assign t[9] = (b4 & x3) | (b7 & x1);

endmodule