module top (
  input logic [7:0] weights,
  input logic [7:0] activations [5],
  output logic [9:0] decoded_weights,
  output logic [7:0] products [5]
);

  ternary_decoder ternary_decoder_inst (
    .encoded_vals(weights),
    .decoded_vals(decoded_weights)
  );

    generate
      for (genvar i = 0; i < 5; i++) begin
        tmul tmul_inst (
          .a(activations[i]),
          .b(decoded_weights[(i<<1) +: 2]),
          .c(products[i])
        );
      end
    endgenerate

endmodule