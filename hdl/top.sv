module top (
  input logic [7:0] ui_in,
  output logic [7:0] uo_out,

  input logic [7:0] uio_in,
  output wire [7:0] uio_out,
  output wire [7:0] uio_oe,

  input logic ena,
  input logic clk,
  input logic rst_n
);

// We start off with both activation and weight ready
// From the Raspi, an activation byte is sent, with activation_valid
// Activation ready is high until the entire activation buffer is filled, then it goes low. It goes high again when done
// From the Raspi, a weight byte is sent, with weight_valid
// Weight ready is high until the entire weight buffer is filled, then it goes low. It goes high again when done
// When both activation and activation_buffer weight are NOT ready -> we start the operation

// Bus Arbiter:
// uio_in[0] -> activation_byte_valid (input)
// uio_in[1] -> weight_byte_valid (input)
// uio_in[2] -> activation_buffer_ready (output)
// uio_in[3] -> weight_buffer_ready (output)
// uio_in[4] -> result_byte_valid (output)
// uio_in[5] -> matmul_valid (output)


logic activation_byte_valid, weight_byte_valid;
assign activation_byte_valid = uio_in[0];
assign weight_byte_valid = uio_in[1];

logic activation_buffer_ready, weight_buffer_ready;
assign uio_out[2] = activation_buffer_ready;
assign uio_out[3] = weight_buffer_ready;

logic result_byte_valid, matmul_valid;
assign matmul_valid = activation_buffer_valid & weight_buffer_valid;
assign uio_out[4] = result_byte_valid;
assign uio_out[5] = matmul_valid;
assign uio_oe = 8'b00111100; // 1 for output, 0 for input


logic [7:0] activation_byte, weight_byte;
bus_arbiter bus_arbiter_inst (
  .ui_in(ui_in),
  .activation_byte_valid(activation_byte_valid),
  .weight_byte_valid(weight_byte_valid),
  .activation_byte(activation_byte),
  .weight_byte(weight_byte)
);

logic activation_buffer_valid, weight_buffer_valid;
logic [31:0] activation_buffer, weight_buffer;
parallel_byte_buffer #(.NUM_BYTES(4)) activation_byte_buffer_inst (
  .clk(clk),
  .rst(~rst_n),
  .clear(dot_out_valid),
  .data_in(activation_byte),
  .valid_in(activation_byte_valid),
  .buffer_out(activation_buffer),
  .buffer_valid(activation_buffer_valid),
  .buffer_ready(activation_buffer_ready)
);
parallel_byte_buffer #(.NUM_BYTES(4)) weight_byte_buffer_inst (
  .clk(clk),
  .rst(~rst_n),
  .clear(dot_out_valid),
  .data_in(weight_byte),
  .valid_in(weight_byte_valid),
  .buffer_out(weight_buffer),
  .buffer_valid(weight_buffer_valid),
  .buffer_ready(weight_buffer_ready)
);

logic [31:0] dot_out;
logic dot_out_valid;
logic [7:0] result_byte;
logic [1:0] result_byte_index;
assign uo_out = result_byte;
always_ff @(posedge clk) begin
  if(~rst_n) begin
    result_byte <= '0;
    result_byte_index <= '0;
  end else begin
    result_byte_valid <= dot_out_valid;
    if (dot_out_valid) begin
      result_byte_index <= result_byte_index + 1'b1;
      result_byte <= dot_out[8*result_byte_index +: 8];
    end
  end
end
tmatmul tmatmul_inst (
  .clk(clk),
  .rst(~rst_n),
  .activations_in(activation_buffer),
  .activations_valid(activation_buffer_valid),
  .weight_fifo_in(weight_buffer),
  .weight_fifo_valid(weight_buffer_valid),
  .dot_out(dot_out),
  .dot_out_valid(dot_out_valid)
);



endmodule
