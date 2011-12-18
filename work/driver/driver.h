/******************************************************************************/
/*                                                                            */
/* Filename:   driver.h                                                   */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#ifndef DRIVER_H
#define DRIVER_H

#include "../global.h"
#include <systemc.h>
#include <scv.h>

/* driver method */
SC_MODULE(driver)
{
public:

  /* port declarations */
  fulladr_port port_in;
  sc_in<bool> cy_in;

  fa_rtl_port port_out_a;
  fa_rtl_port port_out_b;
  sc_inout<sc_logic> cy_out;

  /*transaction streams */
  scv_tr_stream input_stream;
  scv_tr_stream output_stream_a;
  scv_tr_stream output_stream_b;
  scv_tr_generator<sc_uint<BITWIDTH>, bool > input_gen;
  scv_tr_generator<sc_logic, sc_logic> output_gen_a;
  scv_tr_generator<sc_logic, sc_logic> output_gen_b;

  SC_CTOR(driver)
  : input_stream("input_stream", "driver"),
    output_stream_a("output_stream_a", "driver"),
    output_stream_b("output_stream_b", "driver"),
    input_gen("reading",input_stream,"I_driver_A","I_driver_B"),
    output_gen_a("writing_a", output_stream_a, "O_driver_A"),
    output_gen_b("writing_b", output_stream_b, "O_driver_B")
  {

    SC_METHOD(driver_method);
      sensitive << port_in.fa_value_changed_event()
                << cy_in.value_changed();
      dont_initialize();
  }
  void driver_method();
};

#endif
