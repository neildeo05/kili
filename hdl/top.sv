// Tensor Core Implementation

// 4 cycle latency from burst transfer to entering the weight FIFO
// 2 cycle latency from entering the weight FIFO to the weight being used in the tensor core

module top #(
  parameter NUM_TILES = 64,
  parameter TILE_SIZE = 8
) (
  input logic clk,
  input logic rst,
  // input logic activations_valid,
  // input logic [7:0] activations_in [TILE_SIZE],
  input logic [TILE_SIZE-1:0][7:0] activations_in [NUM_TILES],

  // Burst transfer from local memory to tensor core
  input logic [5:0] in_burst_addr,
  input logic [5:0] in_burst_len,
  input logic in_burst_valid,
  output logic in_burst_ready,
  output logic [127:0] weight_data,
  output logic [TILE_SIZE-1:0][7:0] dot_out,
  output logic dot_out_valid
);
  parameter BURST_WIDTH = 6+6;

  /*
  State Machine to handle the burst transfer
  - Idle: Ready to accept a burst
  - Bursting: Burst is in progress
  - Done: Burst complete

  curr_burst_ready = 1'b1 when in Idle state, 1'b0 when in Bursting/Done state

  Transitiosn:
  - Idle -> Bursting: curr_burst_valid is high
  - Bursting -> Done: burst_addr = curr_burst_addr + curr_burst_len - 1
  - Done -> Idle: always
  */
  // burst fifo stores the burst address and length before sending it to the memory unit
  typedef enum logic [1:0] {
    IDLE = 2'b00,
    BURSTING = 2'b01,
    DONE = 2'b10
  } state_t;

  logic [5:0] curr_burst_addr, curr_burst_addr_reg, curr_burst_len;
  logic curr_burst_valid, curr_burst_done, curr_burst_ready;
  logic [BURST_WIDTH-1:0] curr_burst_data;

  assign curr_burst_len = curr_burst_data[5:0];
  assign curr_burst_addr = curr_burst_data[11:6];

  state_t state, next_state;
  always_ff @(posedge clk) begin : burst_state_machine_ff
    if (rst) begin
      state <= IDLE;
    end else begin
      state <= next_state;
    end
  end

  always_comb begin : burst_state_machine
    next_state = state;
    case (state)
      IDLE: begin
        if (curr_burst_valid) begin
          next_state = BURSTING;
        end
      end
      BURSTING: begin
        if (curr_burst_done) begin
          next_state = DONE;
        end
      end
      default: begin
        next_state = IDLE;
      end
    endcase
  end

  logic [5:0] curr_burst_boundary;
  assign curr_burst_ready = (state == IDLE);
  assign curr_burst_done = (curr_burst_addr_reg == curr_burst_boundary);
  logic weight_valid, weight_ready;
  always_ff @(posedge clk) begin : update_curr_burst_address
    if (rst) begin
      curr_burst_addr_reg <= '0;
      weight_valid <= 1'b0;
    end else begin
      if (state == IDLE & curr_burst_valid) begin
        weight_valid <= 1'b0;
        curr_burst_addr_reg <= curr_burst_addr;
        curr_burst_boundary <= curr_burst_addr + curr_burst_len - 1;
      end else if (state == BURSTING) begin
        curr_burst_addr_reg <= curr_burst_addr_reg + 1'b1;
        weight_valid <= 1'b1;
      end else if (state == DONE) begin
        weight_valid <= 1'b0;
      end
    end
  end


  fifo_buffer #(.WIDTH(BURST_WIDTH), .DEPTH(4)) burst_fifo_inst (
    .clk(clk),
    .rst(rst),
    .input_valid(in_burst_valid),
    .input_ready(in_burst_ready),
    .input_data({in_burst_addr, in_burst_len}),
    .output_valid(curr_burst_valid),
    .output_ready(curr_burst_ready),
    .output_data(curr_burst_data)
  );


  // local memory stores 64 8x8 tiles
  // that means it can do a 64x64 matrix multiplication, using the 8x8 tiles
  local_memory weight_memory_inst (
    // Port 0: Unused, tie off
    .clk0(clk),
    .csb0(1'b1),  // active-low chip select: 1 = disabled
    .web0(1'b1),  // active-low write enable: 1 = read mode (no write)
    .addr0(6'b0),
    .din0(128'b0),
    .dout0(),     // unused
    // Port 1: Burst read port
    .clk1(clk),
    .csb1(~(state == BURSTING)),  // active-low chip select: 0 = enabled
    .web1(1'b1),  // active-low write enable: 1 = read mode
    .addr1(curr_burst_addr_reg),
    .din1(128'b0),
    .dout1(weight_data)
  );

  logic weight_fifo_valid, weight_fifo_ready;
  assign weight_fifo_ready = '1;
  logic [127:0] weight_fifo_data;
  fifo_buffer #(.WIDTH(128), .DEPTH(4)) weight_fifo_inst (
    .clk(clk),
    .rst(rst),
    .input_valid(weight_valid),
    .input_ready(weight_ready),
    .input_data(weight_data),
    .output_valid(weight_fifo_valid),
    .output_ready(weight_fifo_ready),
    .output_data(weight_fifo_data)
  );

  tmatmul #(.TILE_SIZE(TILE_SIZE)) tmatmul_inst (
    .clk(clk),
    .rst(rst),
    .activations_in(),
    .activations_valid(),
    .weight_fifo_valid(weight_fifo_valid),
    .weight_fifo_in(weight_fifo_data),
    .dot_out(dot_out),
    .dot_out_valid(dot_out_valid)
  );


endmodule
