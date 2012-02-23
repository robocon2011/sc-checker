/******************************************************************************/
/*                                                                            */
/* Filename:    driver.h                                                      */
/*                                                                            */
/* Author:      Philipp Maroschek                                             */
/*                                                                            */
/* Tools:       Compiles with SystemC 2.2.v0                                  */
/*                                                                            */
/* Project:     SystemC Checker                                               */
/*                                                                            */
/* Topmodule:   Driver                                                        */
/* Submodules:  ------                                                        */
/*                                                                            */
/******************************************************************************/

#ifndef DRIVER_H
#define DRIVER_H

#include "../global.h"
#include <systemc.h>
#include <scv.h>

#include "clock_gen.h"

SC_MODULE(driver_fulladdr)
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

  /* constructor and initialization of streams */
  SC_CTOR(driver_fulladdr)
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

SC_MODULE(driver_uart)
{
public:

  /* port declarations */

  sc_in<sc_uint< DATABITS> > rx_data_in;
  sc_in<sc_uint< DATABITS> > tx_data_in;
  sc_in<bool> reset_in;
  sc_in<bool> tx_enable_in;
  sc_in<bool> rx_enable_in;

  sc_out<sc_logic> reset;
  sc_out<sc_logic> ld_tx_data;
  sc_out<sc_logic> tx_enable;
  sc_out<sc_logic> uld_rx_data;
  sc_out<sc_logic> rx_enable;
  sc_out<sc_logic> rx_in;
  uart_data_port   tx_data_port;

  sc_export<sc_signal_inout_if<sc_logic> > rxclk;
  sc_export<sc_signal_inout_if<sc_logic> > txclk;

  sc_signal<packet_uart_rx_data> packet_uart_rx;
  sc_signal<packet_uart_tx_data> packet_uart_tx;

  sc_port < handshake_event_if > data_written;
  sc_port < handshake_generation_if > data_written_uart;
  sc_signal<sc_logic> s_clk;

#if (ESP_DL == DRIVER)
  /* create tracefile */
  sc_trace_file* tracefile_driver;
#endif

  /* submodule instantiation */
  clock_gen clock_gen_i;

  /*transaction streams */
  scv_tr_stream input_stream;
  scv_tr_stream output_stream;
  scv_tr_generator<sc_uint<DATABITS>, bool > input_gen;
  scv_tr_generator<sc_logic, sc_logic> output_gen;

  /* constructor and initialization of streams */
  SC_CTOR(driver_uart)
  : clock_gen_i("clock_gen_i"),
    input_stream("input_stream", "driver"),
    output_stream("output_stream_a", "driver"),
    input_gen("reading",input_stream,"I_driver","reset"),
    output_gen("writing_a", output_stream, "O_driver_A")
  {

    SC_METHOD(driver_get_data);
      dont_initialize();
      sensitive << data_written;

    SC_METHOD(driver_send_rx_data);
      dont_initialize();
      sensitive << packet_uart_rx.default_event();

    SC_METHOD(driver_send_tx_data);
      dont_initialize();
      sensitive << packet_uart_tx.default_event();

    clock_gen_i.clkout_log(s_clk);
    txclk(s_clk);
    rxclk(s_clk);
  }
  ~driver_uart(){
#if (ESP_DL == DRIVER)
  sc_close_vcd_trace_file(tracefile_driver);
  cout << "DRIVER: tracefile closed" << endl;
#endif
  }

  void driver_get_data();
  void driver_send_rx_data();
  void driver_send_tx_data();

};

#endif
