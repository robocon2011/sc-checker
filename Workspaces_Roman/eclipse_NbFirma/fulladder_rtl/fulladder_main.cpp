///////////////////////////////////////////////////////////////////////////////
//
// SystemC class example: fulladder
// 
// Filename:   fulladder_main.cpp
//
// Author:     Roland Höller
//
// Tools:      Compiles with SystemC 2.1.v1 and Modelsim 6.1e
//
//
///////////////////////////////////////////////////////////////////////////////

#include <systemc>
#include "dut/fulladder/fulladder_rtl.h"

///////////////////////////////////////////////////////////////////////////////
//
// Describe a testbench for the full adder design example.
SC_MODULE(tb_fulladder_cascade) {

	int i;

	sc_out< sc_logic >  a_o[BITWIDTH];
	sc_out< sc_logic >  b_o[BITWIDTH];
	sc_out< sc_logic >  cy_o;

	void stim_fulladder_cascade() {
		for (i=0; i<(BITWIDTH); i++){
			a_o[i]->write(SC_LOGIC_0);
			b_o[i]->write(SC_LOGIC_0);
		}
		cy_o->write(SC_LOGIC_0);

		wait(100, SC_NS);

		for (i=0; i<(BITWIDTH); i++){
			a_o[i]->write(SC_LOGIC_1);
			b_o[i]->write(SC_LOGIC_0);
		}
		cy_o->write(SC_LOGIC_1);
		wait(100, SC_NS);
		for (i=0; i<(BITWIDTH); i++){
			a_o[i]->write(SC_LOGIC_0);
			b_o[i]->write(SC_LOGIC_1);
		}
		cy_o->write(SC_LOGIC_0);
	};

	SC_CTOR(tb_fulladder_cascade) {
		SC_THREAD(stim_fulladder_cascade);
	}

};
///////////////////////////////////////////////////////////////////////////////

#ifdef MTI_SYSTEMC

SC_MODULE(fulladder_top) {

  fulladder    i_fulladder;
  tb_fulladder i_tb_fulladder;

  // declare interconnecting signals
  sc_signal<sc_logic> s_a, s_b, s_cy, s_sumout, s_cyout;

  SC_CTOR(fulladder_top) :
    i_fulladder("i_fulladder"),
    i_tb_fulladder("i_tb_fulladder")
  {
    // connect the fulladder design
    i_fulladder.a_i(s_a);
    i_fulladder.b_i(s_b);
    i_fulladder.cy_i(s_cy);
    i_fulladder.sum_o(s_sumout);
    i_fulladder.cy_o(s_cyout);
    // and the fulladder testbench
    i_tb_fulladder.a_o(s_a);
    i_tb_fulladder.b_o(s_b);
    i_tb_fulladder.cy_o(s_cy);
  }
};

// export the toplevel SystemC design with a macro.
SC_MODULE_EXPORT(fulladder_top);

#else

int sc_main(int argc, char* argv[]) {

	int i;
	char name[64];

	// set up trace file
	sc_trace_file* Tf;
	Tf = sc_create_vcd_trace_file("fulladder_traces");
	((vcd_trace_file*)Tf)->sc_set_vcd_time_unit(-9);

	// declare interconnecting signals
	sc_signal<sc_logic> s_cy, s_cyout;
	sc_signal< sc_logic > s_a[BITWIDTH], s_b[BITWIDTH], s_sumout[BITWIDTH];

	// trace signals to vcd file
	for (i=0; i<(BITWIDTH); i++){
		sprintf(name, "in_a_%d",i);
		sc_trace(Tf, s_a[i],  name);
		sprintf(name, "in_b_%d",i);
		sc_trace(Tf, s_b[i],  name);
		sprintf(name, "out_sum__%d",i);
		sc_trace(Tf, s_sumout[i], name);
	}

	sc_trace(Tf, s_cy, "in_cy");
	sc_trace(Tf, s_cyout, "out_cy");

	// create instances of fulladder and tb_fulladder
	fulladder_cascade i_fulladder("i_fulladder");
	tb_fulladder_cascade i_tb_fulladder("i_tb_fulladder");

	// connect the fulladder design
	for (i=0; i<(BITWIDTH); i++){
		i_fulladder.a_in[i](s_a[i]);
		i_fulladder.b_in[i](s_b[i]);
		i_fulladder.sum_out[i](s_sumout[i]);
		i_tb_fulladder.a_o[i](s_a[i]);
		i_tb_fulladder.b_o[i](s_b[i]);
	}

	i_fulladder.cy_in(s_cy);
	i_fulladder.cy_out(s_cyout);

	// and the fulladder testbench
	i_tb_fulladder.cy_o(s_cy);

	// invoke the simulator
	sc_start(300,SC_NS ) ;
	// close trace file
	sc_close_vcd_trace_file(Tf);
	return 0;
}

#endif
