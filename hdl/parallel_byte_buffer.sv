module parallel_byte_buffer #(
  parameter NUM_BYTES = 4
) (
  input logic clk,
  input logic rst,
  input logic clear,
  input logic [7:0] data_in,
  input logic valid_in,
  output logic [(NUM_BYTES * 8)-1:0] buffer_out,
  output logic buffer_valid,
  output logic buffer_ready
);

typedef enum logic [1:0] {
  EMPTY = 2'b00,
  FILLING = 2'b01,
  DONE = 2'b10
} state_t;
state_t state, state_next;
assign buffer_ready = (state == EMPTY | state == FILLING);
assign buffer_valid = (state == DONE);

logic [$clog2(NUM_BYTES):0] buffer_index;
always_comb begin
  state_next = state;
  case (state)
    EMPTY: begin
      if (valid_in) begin
        state_next = FILLING;
      end
    end
    FILLING: begin
      if (buffer_index[$clog2(NUM_BYTES)-1:0] == '0 & buffer_index[$clog2(NUM_BYTES)] == 1'b1) begin
        state_next = DONE;
      end
    end
    DONE: begin
      if (clear) begin
        state_next = EMPTY;
      end
    end
    default: begin
      state_next = EMPTY;
    end
  endcase
end

always_ff @(posedge clk) begin
  if (rst) begin
    state <= EMPTY;
  end else begin
    state <= state_next;
  end
end
always_ff @(posedge clk) begin
  if (rst) begin
    buffer_out <= '0;
    buffer_index <= '0;
  end else begin
    if ((state == DONE) & clear) begin
      buffer_index <= '0;
    end
    if (valid_in & buffer_ready) begin
      buffer_out[(buffer_index[$clog2(NUM_BYTES)-1:0] * 8) +: 8] <= data_in;
      buffer_index <= buffer_index + 1'b1;
    end
  end
end
endmodule