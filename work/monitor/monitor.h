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

SC_MODULE (monitor)
{
public:

  /* port declarations */
  fa_rtl_port port_in_a;
  sc_in<sc_logic> cy_in;

  sc_out<sc_uint <BITWIDTH> > port_out;
  sc_out<bool> cy_out;

  sc_signal<packet_fulladdr> rtl2sw_trans_monitor;

  SC_CTOR(monitor)
  {
    SC_METHOD(monitor_method);
      sensitive << port_in_a.fa_value_changed_event();
      dont_initialize();

    SC_METHOD(monitor_debouncing_method);
      sensitive << rtl2sw_trans_monitor.value_changed_event();
      dont_initialize();
  }

  void monitor_method();
  void monitor_debouncing_method();
};

#endif
