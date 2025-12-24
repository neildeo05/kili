/*
Pipelines combinational path between producer (memory) and consumer (tensor core)
 inspired from https://fpgacpu.ca/fpga/Pipeline_FIFO_Buffer.html
Producer -> FIFO -> Consumer

If there is no data in the output register, and the buffer has data, we preload the output register with the next valid data from the buffer
If there is data in the output register, and the consumer is ready to consume, we remove the data from the output register
If there is 
*/
module fifo_buffer #(
    parameter int WIDTH = 128,
    parameter int DEPTH = 4
) (
    input  logic              clk,
    input  logic              rst,

    input  logic              input_valid, // incoming data is valid from producer
    output logic              input_ready, // fifo is ready to get incoming data from producer
    input  logic [WIDTH-1:0]  input_data, // incoming data from producer

    output logic              output_valid, // outgoing data is valid to consumer
    input  logic              output_ready, // consumer is ready to consume outgoing data
    output logic [WIDTH-1:0]  output_data // outgoing data to consumer
);

    localparam PTR_W = $clog2(DEPTH);
    localparam ADDR_LAST = DEPTH - 1;

    // Buffer storage, switch to SRAM if needed
    logic [WIDTH-1:0] buffer [DEPTH];

    // Read and Write Pointers
    logic [PTR_W-1:0] wr_addr, rd_addr;
    logic             wr_wrap, rd_wrap; // Wrap bits

    logic buffer_empty, buffer_full; // State of the buffer
    // Buffer is empty when the write and read pointers are the same, and the write pointer/read pointer haven't wrapped around
    assign buffer_empty = (wr_addr == rd_addr) && (wr_wrap == rd_wrap);
    // Buffer is full when the write and read pointers are the same, and the write pointer/read pointer HAVE wrapped around
    assign buffer_full  = (wr_addr == rd_addr) && (wr_wrap != rd_wrap);

    // FIFO is ready to get incoming data from producer if buffer is not full
    assign input_ready = ~buffer_full;

    // We can insert data into the buffer if the incoming data is valid, and the buffer can accept said data
    logic insert;
    assign insert = input_valid && input_ready;

    // Output Register holds data for consumer
    logic [WIDTH-1:0] out_reg;
    logic             out_valid_reg;

    assign output_data  = out_reg;
    assign output_valid = out_valid_reg;

    // Control signals for the output register
    logic remove, load_output_reg, buffer_read;

    // Since the output register holds valid data, and the consumer is ready to consume, we can remove it from the output register
    assign remove = out_valid_reg && output_ready;

    // We load the output register EITHER:
    // - The consumer is ready to consume the current data in the output register
    // - The output register is empty, and the buffer has data
    // This way we know to load the output register with the next valid data from the buffer
    assign load_output_reg = remove || (~out_valid_reg && ~buffer_empty);

    // Buffer -> Output Register when we should load the output register and the buffer has data
    assign buffer_read = load_output_reg && ~buffer_empty;

    // Writes
    always_ff @(posedge clk) begin
        if (rst) begin
            wr_addr <= '0;
            wr_wrap <= 1'b0;
        // Insert data into the buffer if the incoming data is valid, and the buffer can accept said data
        end else if (insert) begin
            buffer[wr_addr] <= input_data;
            if (wr_addr == PTR_W'(ADDR_LAST)) begin
              // wrap around logic
                wr_addr <= '0;
                wr_wrap <= ~wr_wrap;
            end else begin
                wr_addr <= wr_addr + 1'b1;
            end
        end
    end

    // Reads
    always_ff @(posedge clk) begin
        if (rst) begin
            rd_addr <= '0;
            rd_wrap <= 1'b0;
        end else if (buffer_read) begin
            if (rd_addr == PTR_W'(ADDR_LAST)) begin
              // wrap around logic
                rd_addr <= '0;
                rd_wrap <= ~rd_wrap;
            end else begin
                rd_addr <= rd_addr + 1'b1;
            end
        end
    end

    // Output register: loads from buffer, holds data until consumed
    always_ff @(posedge clk) begin
        if (rst) begin
            out_reg       <= '0;
            out_valid_reg <= 1'b0;
        end else if (load_output_reg) begin
            // Set valid based on whether buffer has data to provide
            out_valid_reg <= ~buffer_empty;
            if (~buffer_empty) begin
                out_reg <= buffer[rd_addr];
            end
        end
    end

endmodule
