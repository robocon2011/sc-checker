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
#define MONITOR_

#ifndef SP_PORTS_
  #include "sp_ports.h"
#endif
#ifndef PACKETS_
  #include "packets.h"
#endif

#include "global.h"

SC_MODULE(monitor)
{
public:

  /* port declarations */
  fa_rtl_lv_single_port port_in_a;
  sc_in<sc_logic> cy_in;

  sc_out<sc_uint <BITWIDTH> > port_out;
  sc_out<bool> cy_out;

  sc_signal<packet_fulladdr_lv> rtl2sw_trans_monitor;
  sc_fifo<packet_fulladdr_lv> rtl2sw_trans_fifo;

  SC_CTOR(monitor)
  {
    SC_METHOD(monitor_method);
      sensitive << port_in_a.fa_value_changed_event();
      dont_initialize();

    SC_THREAD(monitor_thread);
      sensitive << rtl2sw_trans_monitor;
      dont_initialize();
  }

  void monitor_method();
  void monitor_thread();
};

#endif
