.PHONY: test_decoder test_fifo test_skid_buffer test_top test_top_system testbench matvec_sw clean

# Configurable tile size (default 4)
TILE_SIZE ?= 4

# Test just the decoder
test_decoder:
	verilator -I../hdl -Wall -Wno-fatal --trace --cc --exe --build \
		test_decoder.cpp ../hdl/ternary_decoder.sv
	./obj_dir/Vternary_decoder

# Test the FIFO buffer
test_fifo:
	verilator -I../hdl -Wall -Wno-fatal --trace --cc --exe --build \
		test_fifo.cpp ../hdl/fifo_buffer.sv \
		--Mdir obj_fifo
	./obj_fifo/Vfifo_buffer

# Test the skid buffers
test_skid_buffer:
	# Build in-channel skid buffer model
	verilator -I../hdl -Wall -Wno-fatal --trace --cc \
		../hdl/in_chan_skid_buffer.sv \
		--Mdir obj_in_skid
	$(MAKE) -C obj_in_skid -f Vin_chan_skid_buffer.mk
	# Build out-channel skid buffer model
	verilator -I../hdl -Wall -Wno-fatal --trace --cc \
		../hdl/out_chan_skid_buffer.sv \
		--Mdir obj_out_skid
	$(MAKE) -C obj_out_skid -f Vout_chan_skid_buffer.mk
	# Link testbench with both skid buffer models
	g++ -std=c++17 -I obj_in_skid -I obj_out_skid \
		-I$$(verilator --getenv VERILATOR_ROOT)/include \
		test_skid_buffer.cpp \
		obj_in_skid/Vin_chan_skid_buffer__ALL.a \
		obj_out_skid/Vout_chan_skid_buffer__ALL.a \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated.cpp \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated_threads.cpp \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated_vcd_c.cpp \
		-pthread \
		-o test_skid_buffer_exe
	./test_skid_buffer_exe

# Test the top module (legacy test for parallel_byte_buffer)
test_top:
	verilator -I../hdl -Wall -Wno-fatal --trace --cc \
		../hdl/top.sv \
		../hdl/parallel_byte_buffer.sv \
		../hdl/bus_arbiter.sv \
		--Mdir obj_top
	$(MAKE) -C obj_top -f Vtop.mk
	g++ -std=c++17 -I obj_top \
		-I$$(verilator --getenv VERILATOR_ROOT)/include \
		test_top.cpp \
		obj_top/Vtop__ALL.a \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated.cpp \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated_threads.cpp \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated_vcd_c.cpp \
		-pthread \
		-o test_top_exe
	./test_top_exe

# Test the top module system (full ternary matmul with bus arbiter + buffers)
test_top_system:
	verilator -I../hdl -Wall -Wno-fatal --trace --cc \
		../hdl/top.sv \
		../hdl/parallel_byte_buffer.sv \
		../hdl/bus_arbiter.sv \
		../hdl/tmatmul.sv \
		../hdl/tdot.sv \
		../hdl/tmul.sv \
		../hdl/reduction_tree.sv \
		../hdl/reduction_stage.sv \
		../hdl/adder_stage.sv \
		--Mdir obj_top_system
	$(MAKE) -C obj_top_system -f Vtop.mk
	g++ -std=c++17 -I obj_top_system \
		-I$$(verilator --getenv VERILATOR_ROOT)/include \
		test_top_system.cpp \
		obj_top_system/Vtop__ALL.a \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated.cpp \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated_threads.cpp \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated_vcd_c.cpp \
		-pthread \
		-o test_top_system_exe
	./test_top_system_exe

# Build and run testbench (tests tmatmul matrix-vector multiplication)
testbench:
	# Build decoder model (needed for weight encoding in testbench)
	verilator -I../hdl -Wall -Wno-fatal --cc ../hdl/ternary_decoder.sv \
		--Mdir obj_decoder
	$(MAKE) -C obj_decoder -f Vternary_decoder.mk
	# Build tmatmul model with TILE_SIZE parameter and tracing
	verilator -I../hdl -Wall -Wno-fatal --trace --cc \
		-GTILE_SIZE=$(TILE_SIZE) \
		../hdl/tmatmul.sv ../hdl/tdot.sv ../hdl/ternary_decoder.sv \
		../hdl/tmul.sv ../hdl/reduction_tree.sv ../hdl/reduction_stage.sv \
		../hdl/adder_stage.sv \
		--Mdir obj_tmatmul
	$(MAKE) -C obj_tmatmul -f Vtmatmul.mk
	# Link testbench with TILE_SIZE define and VCD support
	g++ -std=c++17 -I obj_decoder -I obj_tmatmul \
		-I$$(verilator --getenv VERILATOR_ROOT)/include \
		-DTILE_SIZE=$(TILE_SIZE) \
		testbench.cpp \
		obj_decoder/Vternary_decoder__ALL.a \
		obj_tmatmul/Vtmatmul__ALL.a \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated.cpp \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated_threads.cpp \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated_vcd_c.cpp \
		-pthread \
		-o testbench
	./testbench

# Pure software 64x64 matrix-vector product (no Verilator needed)
matvec_sw:
	g++ -std=c++17 -O2 -o matvec_sw matvec_sw.cpp
	./matvec_sw

clean:
	rm -rf obj_dir obj_decoder obj_fifo obj_in_skid obj_out_skid obj_top obj_top_system \
		obj_top_test obj_tmatmul testbench matvec_sw test_skid_buffer_exe test_top_exe \
		test_top_system_exe
