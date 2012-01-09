#ifndef DUMMY_H
#define DUMMY_H

#include "global.h"
#include <systemc.h>
#include <scv.h>
#include <bitset>

/* driver method */
SC_MODULE(dummy)
{
public:

  /* port declarations */
/*  sc_in<sc_uint< DATABITS> > rx_data_out;
  sc_in<sc_uint< DATABITS> > tx_data_out;
  sc_in<bool> tx_empty_out;
  sc_in<bool> rx_empty_out;
  sc_in<bool> reset_in;
  */

  sc_inout<bool> reference_received;
  sc_inout<bool> testcase_finished;

  sc_in<sc_logic>   rxclk;
  sc_in<sc_logic>   txclk;
  sc_in<sc_logic>   reset;
  sc_in<sc_logic>   ld_tx_data;
  sc_in<sc_logic>   tx_enable;

  sc_in<sc_logic>   uld_rx_data;
  sc_in<sc_logic>   rx_enable;
  sc_in<sc_logic>   rx_in;
  sc_in<bool>       clk_dr;
  sc_in<sc_logic>   tx_data[DATABITS];


  SC_CTOR(dummy)
  {

      SC_METHOD(dummy_method);
        dont_initialize();
        sensitive << rx_in.value_changed();
  }

  void dummy_method();
};

#endif
