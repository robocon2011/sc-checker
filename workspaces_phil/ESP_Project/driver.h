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
#define DRIVER_

#ifndef PACKETS_
  #include "packets.h"
#endif
#ifndef SP_PORTS__
  #include "sp_ports.h"
#endif
#include "global.h"

/* driver method */
SC_MODULE(driver)
{
public:

  /* port declarations */
  fulladr_port port_in;
  sc_in<bool> cy_in;

  fa_rtl_lv_single_port port_out_a;
  fa_rtl_lv_single_port port_out_b;
  sc_inout<sc_logic> cy_out;

  /*channel declarations */
  sc_signal<packet_fulladdr_lv> rtl2sw_trans_driver;
  //sc_fifo<packet_fulladdr> rtl2sw_trans_driver_fifo;

  SC_CTOR(driver)
  {
    SC_METHOD(driver_method);
      sensitive << port_in.fa_value_changed_event()
                << cy_in.value_changed();
      dont_initialize();

  }

  void driver_method();
};

#endif
