module out_chan_skid_buffer #(parameter WIDTH=32) (
  input logic clk,
  input logic rst,
  input logic in_producer_valid,
  input logic [WIDTH-1:0] in_producer_data,
  input logic in_consumer_ready,
  output logic out_buf_valid,
  output logic out_buf_ready,
  output logic [WIDTH-1:0] out_buf_data
);
  logic [WIDTH-1:0] buffer_data;
  logic buffer_valid;


  assign out_buf_ready = ~buffer_valid;

  always_ff @(posedge clk) begin : buffer_valid_logic
    if(rst) begin
      buffer_valid <= '0;
    end else if (in_producer_valid & out_buf_ready & out_buf_valid & ~in_consumer_ready) begin // valid incoming data, and we are ready
        buffer_valid <= '1;
    end else if (in_consumer_ready) begin
        buffer_valid <= '0;
    end
  end

  always_ff @(posedge clk) begin : buffer_data_logic
    if(rst) begin
      buffer_data <= '0;
    end else if (in_producer_valid & out_buf_ready) begin
      buffer_data <= in_producer_data;
    end else if (~out_buf_valid | in_consumer_ready) begin
      // We only set it to zero if the buffer is valid and the consumer is ready (cause it will handshake next cycle)
      buffer_data <= '0;
    end
  end


  logic will_handshake;
  assign will_handshake = ~out_buf_valid | (out_buf_valid & in_consumer_ready);
  always_ff @(posedge clk) begin : output_valid_logic
    if(rst) begin
      out_buf_valid <= '0;
    end else if (will_handshake) begin
      // Can populate by the next cycle
      out_buf_valid <= buffer_valid | in_producer_valid;
    end
  end
  always_ff @(posedge clk) begin : output_data_logic
    if(rst) begin
      out_buf_data <= '0;
    end else if (will_handshake) begin
      if(buffer_valid) begin
        out_buf_data <= buffer_data;
      end else if (in_producer_valid) begin
        out_buf_data <= in_producer_data;
      end else out_buf_data <= '0;
    end
  end

endmodule