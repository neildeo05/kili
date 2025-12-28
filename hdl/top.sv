module top #(
  parameter NUM_TILES = 8,
  parameter TILE_SIZE = 8
) (
  input logic clk,
  input logic rst,
  // input logic activations_valid,
  // input logic [7:0] activations_in [TILE_SIZE],
  input logic [NUM_TILES-1:0][TILE_SIZE-1:0][7:0] activations_in,
  input logic activations_valid,
  output logic activations_ready,

  // Burst transfer from local memory to tensor core
  input logic [5:0] in_burst_addr,
  input logic [5:0] in_burst_len,
  input logic in_burst_valid,
  output logic in_burst_ready,
  output logic [127:0] weight_data,
  output logic [TILE_SIZE-1:0][7:0] dot_out,
  output logic dot_out_valid
);

  logic local_memory_active;
  logic [5:0] weight_addr;

  local_memory weight_memory (
    // Port 0: Unused, tie off
    .clk0(clk),
    .csb0(1'b1),  // active-low chip select: 1 = disabled
    .web0(1'b1),  // active-low write enable: 1 = read mode (no write)
    .addr0(6'b0),
    .din0(128'b0),
    .dout0(),     // unused
    // Port 1: Burst read port
    .clk1(clk),
    .csb1(~local_memory_active),  // active-low chip select: 0 = enabled
    .web1(1'b1),  // active-low write enable: 1 = read mode
    .addr1(weight_addr),
    .din1(128'b0),
    .dout1(weight_data)
  );

tensor_core #(.NUM_TILES(NUM_TILES), .TILE_SIZE(TILE_SIZE)) tensor_core_inst (
  .clk(clk),
  .rst(rst),
  .activations_in(activations_in),
  .activations_valid(activations_valid),
  .activations_ready(activations_ready),
  .in_burst_addr(in_burst_addr),
  .in_burst_len(in_burst_len),
  .in_burst_valid(in_burst_valid),
  .in_burst_ready(in_burst_ready),
  .bursting_active(local_memory_active),
  .weight_addr(weight_addr),
  .weight_data(weight_data),
  .dot_out(dot_out),
  .dot_out_valid(dot_out_valid)
);
endmodule