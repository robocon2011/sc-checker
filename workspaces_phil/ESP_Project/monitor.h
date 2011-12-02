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

SC_MODULE(monitor)
{
public:

  /* port declarations */
  fa_rtl_port port_in_a;
  fa_rtl_port port_in_b;
  fulladr_port port_out;

  sc_signal<packet_fulladdr> rtl2sw_trans_monitor;
  sc_fifo<packet_fulladdr> rtl2sw_trans_fifo;

  SC_CTOR(monitor)
  {
    SC_METHOD(monitor_method);
      sensitive << port_in_a.fa_value_changed_event()
                << port_in_b.fa_value_changed_event();
  }

  void monitor_method();
};

#endif
