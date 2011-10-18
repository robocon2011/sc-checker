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

#include <systemc.h>

///////////////////////////////////////////////////////////////////////////////
//
// Describe a gate-level like model of a half adder.
SC_MODULE(halfadder) {
  sc_in<sc_logic>  a_i;
  sc_in<sc_logic>  b_i;
  sc_out<sc_logic> sum_o;
  sc_out<sc_logic> cy_o;

  void proc_halfadder();

  SC_CTOR(halfadder) {
    SC_METHOD(proc_halfadder);
    sensitive << a_i << b_i;
  }

};

void halfadder::proc_halfadder() {
  sum_o = a_i ^ b_i;
  cy_o  = a_i & b_i;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Describe a gate-level like model of an or gate.
SC_MODULE(orgate) {
  sc_in<sc_logic>  a_i;
  sc_in<sc_logic>  b_i;
  sc_out<sc_logic> or_o;

  void proc_orgate();

  SC_CTOR(orgate) {
    SC_METHOD(proc_orgate);
    sensitive << a_i << b_i;
  }

};

void orgate::proc_orgate() {
  or_o = a_i | b_i;
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Describe a gate-level like model of a full adder by instantiating two half
// adders and an or gate submodule.
SC_MODULE(fulladder) {
  sc_in<sc_logic>  a_i;
  sc_in<sc_logic>  b_i;
  sc_in<sc_logic>  cy_i;
  sc_out<sc_logic> sum_o;
  sc_out<sc_logic> cy_o;

  halfadder i_halfadder1;
  halfadder i_halfadder2;
  orgate    i_orgate;

  sc_signal<sc_logic> s_sum1, s_cy1, s_cy2;

  SC_CTOR(fulladder) : 
    i_halfadder1("i_halfadder1"),
    i_halfadder2("i_halfadder2"),
    i_orgate("i_orgate")
  {
    // hook up half adder one.
    i_halfadder1.a_i(a_i);
    i_halfadder1.b_i(b_i);
    i_halfadder1.sum_o(s_sum1);
    i_halfadder1.cy_o(s_cy1);
    // hook up half adder two.
    i_halfadder2.a_i(s_sum1);
    i_halfadder2.b_i(cy_i);
    i_halfadder2.sum_o(sum_o);
    i_halfadder2.cy_o(s_cy2);
    // hook up the or gate.
    i_orgate.a_i(s_cy1);
    i_orgate.b_i(s_cy2);
    i_orgate.or_o(cy_o);
  }

};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Describe a testbench for the full adder design example.
SC_MODULE(tb_fulladder) {

  sc_out<sc_logic>  a_o;
  sc_out<sc_logic>  b_o;
  sc_out<sc_logic>  cy_o;

  void stim_fulladder() {
    a_o  = SC_LOGIC_0;
    b_o  = SC_LOGIC_0;
    cy_o = SC_LOGIC_0;
    wait(100, SC_NS);
    a_o  = SC_LOGIC_1;
    b_o  = SC_LOGIC_1;
    cy_o = SC_LOGIC_1;
    wait(100, SC_NS);
    a_o  = SC_LOGIC_1;
    b_o  = SC_LOGIC_1;
    cy_o = SC_LOGIC_0;
    wait(100, SC_NS);  };

  SC_CTOR(tb_fulladder) {
    SC_THREAD(stim_fulladder);
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

  // set up trace file
  sc_trace_file* Tf;
  Tf = sc_create_vcd_trace_file("fulladder_traces");
  ((vcd_trace_file*)Tf)->sc_set_vcd_time_unit(-9);

  // declare interconnecting signals
  sc_signal<sc_logic> s_a, s_b, s_cy, s_sumout, s_cyout;

  // trace signals to vcd file
  sc_trace(Tf, s_a,  "in_a");
  sc_trace(Tf, s_b,  "in_b");
  sc_trace(Tf, s_cy, "in_cy");
  sc_trace(Tf, s_sumout, "out_sum");
  sc_trace(Tf, s_cyout, "out_cy");

  // create instances of fulladder and tb_fulladder
  fulladder i_fulladder("i_fulladder");
  tb_fulladder i_tb_fulladder("i_tb_fulladder");

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

  // invoke the simulator
  sc_start(300,SC_NS ) ;
  // close trace file
  sc_close_vcd_trace_file(Tf);
  return 0;
}

#endif
