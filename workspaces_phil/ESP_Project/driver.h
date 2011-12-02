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

/* driver method */
SC_MODULE(driver)
{
public:

  /* port declarations */
  fulladr_port port_in;
  fa_rtl_port port_out_a;
  fa_rtl_port port_out_b;

  /*channel declarations */
  sc_signal<packet_fulladdr> rtl2sw_trans_driver;
  sc_fifo<packet_fulladdr> rtl2sw_trans_driver_fifo;

  SC_CTOR(driver)
  {
    SC_METHOD(driver_method);
      sensitive << port_in.fa_value_changed_event();
  }

  void driver_method();
};

#endif
