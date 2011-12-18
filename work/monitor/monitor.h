/******************************************************************************/
/*                                                                            */
/* Filename:   monitor.h                                                      */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#ifndef MONITOR_H
#define MONITOR_H

#include "../global.h"
#include <bitset>

SC_MODULE (monitor)
{
public:

  /* port declarations */
  fa_rtl_port port_in_a;
  sc_in<sc_logic> cy_in;

  sc_out<sc_uint <BITWIDTH> > port_out;
  sc_out<bool> cy_out;
  sc_port < handshake_generation_if > data_written;

  sc_signal<packet_fulladdr> rtl2sw_trans_monitor;

  /*transaction streams */
  scv_tr_stream input_stream;
  scv_tr_stream output_stream;
  scv_tr_generator<sc_logic, sc_logic> mon_in_gen;
  scv_tr_generator<sc_uint<BITWIDTH>, bool> mon_out_gen;

  SC_CTOR(monitor)
  : input_stream("input_stream", "monitor"),
    output_stream("output_stream", "monitor"),
    mon_in_gen("mon_input", input_stream, "I_monitor"),
    mon_out_gen("mon_output",output_stream,"O_monitor")
  {
    SC_METHOD(monitor_method);
      sensitive << port_in_a.fa_value_changed_event()
                << cy_in;
      dont_initialize();

    SC_METHOD(monitor_debouncing_method);
      sensitive << rtl2sw_trans_monitor.value_changed_event();
      dont_initialize();
  }

  void monitor_method();
  void monitor_debouncing_method();
};

#endif
