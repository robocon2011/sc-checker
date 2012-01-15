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

  sc_inout<bool> reference_received;
  sc_inout<bool> testcase_finished;

  sc_in<bool> tx_empty_out;
  sc_in<bool> rx_empty_out;
  sc_in<sc_uint< DATABITS> > rx_data_out;
  sc_in<sc_uint< DATABITS> > tx_data_out;

  sc_port < handshake_generation_if > data_written;

  SC_CTOR(dummy)
  {

      SC_METHOD(dummy_method);
        dont_initialize();
        sensitive << data_written;
  }

  void dummy_method();
};

#endif
