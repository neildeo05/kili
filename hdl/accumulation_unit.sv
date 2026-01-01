// Accumulates the Tile Partial Products into a single output
module accumulation_unit #(
  parameter TILE_SIZE = 8
) (
  input logic clk,
  input logic rst,
  input logic [TILE_SIZE-1:0][7:0] dot_out,
  input logic dot_out_valid,
  output logic [TILE_SIZE-1:0][7:0] accumulation_out,
  output logic accumulation_valid
);

  // Accumulates the dot products for a given tile

  logic [$clog2(TILE_SIZE)-1:0] accumulation_counter;
  logic [TILE_SIZE-1:0][7:0] accumulation_reg;
  logic tile_size_boundary;
  assign tile_size_boundary = (accumulation_counter == $clog2(TILE_SIZE)'(TILE_SIZE-1));

  always_ff @(posedge clk) begin : accumulation_reg_ff
    if(rst) begin
      accumulation_reg <= '0;
    end else begin
      if (dot_out_valid & ~tile_size_boundary) begin
        accumulation_valid <= 1'b0;
        for(int i = 0; i < TILE_SIZE; i++) begin
          accumulation_reg[i] <= accumulation_reg[i] + dot_out[i];
        end
        accumulation_out <= '0;
      end else if (tile_size_boundary) begin
        accumulation_valid <= 1'b1;
        accumulation_reg <= '0;
        for(int i = 0; i < TILE_SIZE; i++) begin
          accumulation_out[i] <= accumulation_reg[i] + dot_out[i];
        end
      end
      else if (~dot_out_valid) begin
        accumulation_valid <= 1'b0;
        accumulation_reg <= '0;
        accumulation_out <= '0;
      end
    end
  end

  always_ff @(posedge clk) begin : accumulation_counter_ff
    if(rst) begin
      accumulation_counter <= '0;
    end else begin
      if (dot_out_valid) begin
        accumulation_counter <= accumulation_counter + 1'b1;
      end
    end
  end





endmodule