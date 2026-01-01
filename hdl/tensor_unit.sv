// Tensor Unit Implementation

// 4 cycle latency from burst transfer to entering the weight FIFO
   // to be completely honest, the burst fifo could be overkill. at worst it adds an extra cycle of buffering, but at best it allows for a decopuling of the processing of control and data
// 2 cycle latency from entering the weight FIFO to the weight being used in the tensor core

module tensor_unit #(
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

  // Memory Interface
  output logic local_mem_en, // memory enable
  output logic [5:0] local_mem_addr, // memory address
  input logic [127:0] local_mem_data, // memory output data -> assumes 1 cycle latency from address to data, which is prolly fine hopefully

  // Full Matrix Product Output
  output logic [TILE_SIZE-1:0][7:0] accumulation_out,
  output logic accumulation_valid
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
  assign local_mem_addr = curr_burst_addr_reg;

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
  logic burst_active;
  assign burst_active = (state == BURSTING);
  assign local_mem_en = burst_active;
  always_ff @(posedge clk) begin : update_curr_burst_address
    if (rst) begin
      curr_burst_addr_reg <= '0;
      weight_valid <= 1'b0;
    end else begin
      if (state == IDLE & curr_burst_valid) begin
        weight_valid <= 1'b0;
        curr_burst_addr_reg <= curr_burst_addr;
        curr_burst_boundary <= curr_burst_addr + curr_burst_len;
      end else if (burst_active) begin
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
  // local_memory weight_memory_inst (
  //   // Port 0: Unused, tie off
  //   .clk0(clk),
  //   .csb0(1'b1),  // active-low chip select: 1 = disabled
  //   .web0(1'b1),  // active-low write enable: 1 = read mode (no write)
  //   .addr0(6'b0),
  //   .din0(128'b0),
  //   .dout0(),     // unused
  //   // Port 1: Burst read port
  //   .clk1(clk),
  //   .csb1(~(state == BURSTING)),  // active-low chip select: 0 = enabled
  //   .web1(1'b1),  // active-low write enable: 1 = read mode
  //   .addr1(curr_burst_addr_reg),
  //   .din1(128'b0),
  //   .dout1(weight_data)
  // );

  logic weight_fifo_valid, weight_fifo_ready;
  assign weight_fifo_ready = '1;
  logic [127:0] weight_fifo_data;
  fifo_buffer #(.WIDTH(128), .DEPTH(4)) weight_fifo_inst (
    .clk(clk),
    .rst(rst),
    .input_valid(weight_valid),
    .input_ready(weight_ready),
    .input_data(local_mem_data),
    .output_valid(weight_fifo_valid),
    .output_ready(weight_fifo_ready),
    .output_data(weight_fifo_data)
  );

  logic [NUM_TILES-1:0][TILE_SIZE-1:0][7:0] activation_buffer_data;
  logic [TILE_SIZE-1:0][7:0] activation_buffer_chunk;

  // We don't want the activation buffer to be a FIFO:
  // specifically, the issuer of activations is the core complex. If the activations are not ready, 
  // that means that we are currently doing a dot product. That means the core complex itself should look at a different core, this one is busy
  // The issuing fifo shouldn't be a part of the tensor core, but a level above it

  // Activation FSM
  // States:
  // - Empty: have an empty activation buffer, ready to be loaded
  // - Buffered: buffered is filled, but we are not ready to be activating
  // - Activating: Currently being used for a MVP
  // - Done: MVP is done

  // Transitions: 
  // Empty -> Buffered (on activation valid)
  // Buffered -> Activating (on weight_valid, because the weight has been fetched, and has been sent to the fifo)
  // Activating -> Done (on ~weight_valid, because no weights have been fetched (MVP routine is done))
  // This correlates the activation accesses to the bursts being issued from the burst fifo. This also kinda ensures that we can do ANY matvp size

  typedef enum logic [1:0] {
    EMPTY = 2'b00,
    BUFFERED = 2'b01,
    ACTIVATING = 2'b10,
    ACT_DONE = 2'b11
  } activation_state_t;

  activation_state_t activation_state, next_activation_state;
  assign activations_ready = (activation_state == EMPTY);

  always_comb begin : update_activation_state
    next_activation_state = activation_state;
    unique case (activation_state)
      EMPTY: begin
        if(activations_valid) next_activation_state = BUFFERED;
      end
      BUFFERED: begin
        if (weight_valid) next_activation_state = ACTIVATING;
      end
      ACTIVATING: begin
        if (~weight_valid) next_activation_state = ACT_DONE;
      end
      ACT_DONE: begin
        next_activation_state = EMPTY;
      end
      default: begin
        next_activation_state = EMPTY;
      end
    endcase
  end


  always_ff @(posedge clk) begin : update_activation_state_ff
    if (rst) begin
      activation_state <= EMPTY;
    end else begin
      activation_state <= next_activation_state;
    end
  end

  logic activation_chunk_valid, activation_chunk_valid_reg;
  assign activation_chunk_valid = (activation_state == ACTIVATING);
  logic [$clog2(TILE_SIZE)-1:0] chunk_index, next_chunk_index;
  always_comb begin
    next_chunk_index = '0;
    if (activation_state == EMPTY | activation_state == BUFFERED) next_chunk_index = '0;
    else next_chunk_index = chunk_index + 1'b1;
  end
  always_ff @(posedge clk) begin : update_activation_buffer
    if(rst) begin
      activation_buffer_data <= '0;
    end else if (activation_state == BUFFERED) begin
      activation_buffer_data <= activations_in;
    end
  end
  always_ff @(posedge clk) begin : update_activation_buffer_chunk
    if(rst) begin
      activation_buffer_chunk <= '0;
      chunk_index <= '0;
      activation_chunk_valid_reg <= 1'b0;
    end else if (activation_chunk_valid) begin
      activation_buffer_chunk <= activation_buffer_data[chunk_index];
      chunk_index <= next_chunk_index;
    end
    activation_chunk_valid_reg <= activation_chunk_valid;
  end





  logic [TILE_SIZE-1:0][7:0] dot_out;
  logic dot_out_valid;
  tmatmul #(.TILE_SIZE(TILE_SIZE)) tmatmul_inst (
    .clk(clk),
    .rst(rst),
    .activations_in(activation_buffer_chunk),
    .activations_valid(activation_chunk_valid_reg),
    .weight_fifo_in(weight_fifo_data),
    .weight_fifo_valid(weight_fifo_valid),
    .dot_out(dot_out),
    .dot_out_valid(dot_out_valid)
  );

  accumulation_unit #(.TILE_SIZE(TILE_SIZE)) accumulation_unit_inst (
    .clk(clk),
    .rst(rst),
    .dot_out(dot_out),
    .dot_out_valid(dot_out_valid),
    .accumulation_out(accumulation_out),
    .accumulation_valid(accumulation_valid)
  );


endmodule
