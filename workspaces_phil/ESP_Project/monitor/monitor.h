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
#include <systemc.h>
#include <scv.h>
#include <bitset>

#ifndef BITWIDTH
#define BITWIDTH 32
#endif


SC_MODULE (monitor_fulladdr)
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

  SC_CTOR(monitor_fulladdr)
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

/***************************************************************************************/

SC_MODULE (monitor_uart)
{
public:

  /* port declarations */
  sc_in<sc_logic> tx_out;
  sc_in<sc_logic> tx_empty;
  sc_in<sc_logic> rx_empty;
  sc_in<sc_logic> rxclk;
  sc_in<sc_logic> txclk;
  uart_data_port  rx_data_port;

  sc_out<sc_uint< DATABITS> > rx_data_out;
  sc_out<sc_uint< DATABITS> > tx_data_out;
  sc_out<bool> tx_empty_out;
  sc_out<bool> rx_empty_out;

  sc_port < handshake_generation_if > data_written;
  sc_port < handshake_event_if > data_written_rx;

  sc_signal<packet_uart_tx_data> packet_uart_tx;
  sc_signal<packet_uart_rx_data> packet_uart_rx;

  /*transaction streams */
  scv_tr_stream input_stream;
  scv_tr_stream output_stream;
  scv_tr_generator<sc_logic, sc_logic> mon_in_gen;
  scv_tr_generator<sc_uint<BITWIDTH>, bool> mon_out_gen;

  SC_CTOR(monitor_uart)
  : input_stream("input_stream", "monitor"),
    output_stream("output_stream", "monitor"),
    mon_in_gen("mon_input", input_stream, "I_monitor"),
    mon_out_gen("mon_output",output_stream,"O_monitor"),
    s_rx_ok(false),
    s_tx_ok(false),
    initialization(true)
  {
    SC_METHOD(monitor_get_data);
      sensitive << data_written_rx;
      dont_initialize();

    SC_METHOD(monitor_calc);
      sensitive << packet_uart_rx.value_changed_event()
                << packet_uart_tx.value_changed_event();
      dont_initialize();

    SC_METHOD(monitor_catch_tx);
      sensitive << tx_out.neg();
      dont_initialize();
  }

  void monitor_get_data();
  void monitor_catch_tx();
  void monitor_calc();

private:
  bool s_rx_ok, s_tx_ok, initialization;
};

#endif
