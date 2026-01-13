module bus_arbiter (
  input logic [7:0] ui_in,
  input logic activation_byte_valid,
  output logic [7:0] activation_byte,
  input logic weight_byte_valid,
  output logic [7:0] weight_byte
);

  always_comb begin
    activation_byte = '0;
    weight_byte = '0;
    if (activation_byte_valid) begin
      activation_byte = ui_in;
    end else if (weight_byte_valid) begin
      weight_byte = ui_in;
    end
  end

endmodule