.PHONY: test_decoder testbench clean

# Test just the decoder
test_decoder:
	verilator -I../hdl -Wall -Wno-fatal --trace --cc --exe --build \
		test_decoder.cpp ../hdl/ternary_decoder.sv
	./obj_dir/Vternary_decoder

# Build and run testbench (needs both decoder and top models)
testbench:
	# Build decoder model
	verilator -I../hdl -Wall -Wno-fatal --cc ../hdl/ternary_decoder.sv \
		--Mdir obj_decoder
	$(MAKE) -C obj_decoder -f Vternary_decoder.mk
	# Build top model
	verilator -I../hdl -Wall -Wno-fatal --cc \
		../hdl/top.sv ../hdl/ternary_decoder.sv ../hdl/tmul.sv \
		--Mdir obj_top
	$(MAKE) -C obj_top -f Vtop.mk
	# Link testbench
	g++ -std=c++17 -I obj_decoder -I obj_top \
		-I$$(verilator --getenv VERILATOR_ROOT)/include \
		testbench.cpp \
		obj_decoder/Vternary_decoder__ALL.a \
		obj_top/Vtop__ALL.a \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated.cpp \
		$$(verilator --getenv VERILATOR_ROOT)/include/verilated_threads.cpp \
		-pthread \
		-o testbench
	./testbench

clean:
	rm -rf obj_dir obj_decoder obj_top testbench
