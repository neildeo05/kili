module in_chan_skid_buffer #(parameter WIDTH=32) (
  input logic clk,
  input logic rst,
  input logic in_producer_valid,
  input logic [WIDTH-1:0] in_producer_data,
  input logic in_consumer_ready,
  output logic out_buf_valid,
  output logic out_buf_ready,
  output logic [WIDTH-1:0] out_buf_data
);
  /*
  A skid buffer is designed to hold data until the consumer is ready to consume it, allowing us to pipeline a combinational path between producer and consumer
  This is an in channel skid buffer -> the ouutput registers aren't registered, but the input signals are assumed to come from registers

  Here is a description of the skid buffer:
   - If the producer produces valid input, and the consumer can consume said input (in_producer_valid & in_consumer_ready) we can just send the data through
   - However, we can have the data appear on the bus even if the consumer isn't ready to consume it, we just have to buffer it and hold it until the consumer can consume it
   We use a buffer valid signal to see if the buffer contains valid data. It will hold valid data if the producer produces valid data and the buffer is ready to inherit the data:
     - If either the buffer is presently valid or the incoming data is valid, and the consumer isn't ready, the buffer becomes/stays valid
     - Otherwise, if the buffer is presently valid and the incoming data is valid and the consumer isn't ready, the buffer becomes invalid
   We populate the buffer if the buffer is ready to accept data, and the incoming value is valid. We set it to zero if ~out_buffer_valid | (out_buffer_valid & consumer_ready)

   The output signals are set as so:
    - We know that the buffer is ready to accept data if it is not currently containing valid data
    - We set the output valid signal if the buffer is currently valid or the incomign data is valid
    - If the buffer is valid, we put the buffered data on the output data bus
    - Otherwise, if the buffer is not valid, and the incoming data is valid, we put the incoming data on the output data bus
    - Otherwise, we put zero on the output data bus

    Let's say we have the following scenario:
    Producer -> Buffer -> Consumer
    - Producer produces valid data
    - Consumer is stalled/not ready
    1. The producer sends the data to the buffer.
    2. The buffer will become valid on the next cycle. The buffer will also start holding the data.
    3. The buffer tells the producer that it is NOT ready to accept new data since it is currently holding valid data
    4. Now let's say the consumer becomes ready after some cycles, and the producer doesn't produce any new data when the consumer is ready. The consumer will consume the data in the buffer, and a handshake will occur
    5. In the same cycle: The buffer will become invalid on the next cycle. The buffer will become ready. The buffer will get zeroed out. 


  */
  logic [WIDTH-1:0] buffer_data;
  logic buffer_valid;


  always_comb begin : output_logic
    out_buf_ready = ~buffer_valid;
    out_buf_valid = buffer_valid | in_producer_valid;
    if(buffer_valid) begin
      out_buf_data = buffer_data;
    end else if (in_producer_valid) begin
      out_buf_data = in_producer_data;
    end else out_buf_data = '0;
  end


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
    end else if (~out_buf_valid | (out_buf_valid & in_consumer_ready)) begin
      // We only set it to zero if the buffer is valid and the consumer is ready (cause it will handshake next cycle)
      buffer_data <= '0;
    end
  end


endmodule