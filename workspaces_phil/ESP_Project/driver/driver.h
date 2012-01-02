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
#define DRIVER_H

#include "../global.h"
#include <systemc.h>
#include <scv.h>

#include "clock_gen.h"

/* driver for the fulladder design */
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

/* driver method */
SC_MODULE(driver_uart)
{
public:

  /* port declarations */

  sc_in<sc_uint< DATABITS> > rx_data_in;
  sc_in<sc_uint< DATABITS> > tx_data_in;
  sc_in<bool> reset_in;
  sc_in<bool> tx_enable_in;
  sc_in<bool> rx_enable_in;
  sc_in<bool> ld_tx_data_in;
  sc_in<bool> uld_rx_data_in;

  sc_out<sc_logic> txclk;
  sc_out<sc_logic> reset;
  sc_out<sc_logic> ld_tx_data;
  sc_out<sc_logic> tx_enable;
  sc_out<sc_logic> rxclk;
  sc_out<sc_logic> uld_rx_data;
  sc_out<sc_logic> rx_enable;
  sc_out<sc_logic> rx_in;
  uart_data_port   rx_data_port;
  uart_data_port   tx_data_port;

  sc_signal<packet_uart_rx_data> packet_uart_rx;
  sc_signal<packet_uart_tx_data> packet_uart_tx;

  sc_signal<bool>  clk;
  sc_signal<bool>  clk_half;

  //sc_out<sc_logic>  tx_out;
  //sc_out<sc_logic>   tx_empty;
  //sc_out<sc_logic>  rx_empty;

  /*transaction streams */
  scv_tr_stream input_stream;
  scv_tr_stream output_stream;
  scv_tr_generator<sc_uint<DATABITS>, bool > input_gen;
  scv_tr_generator<sc_logic, sc_logic> output_gen;

  SC_CTOR(driver_uart)
  : input_stream("input_stream", "driver"),
    output_stream("output_stream_a", "driver"),
    input_gen("reading",input_stream,"I_driver","reset"),
    output_gen("writing_a", output_stream, "O_driver_A")
  {

    SC_METHOD(driver_get_data);
      dont_initialize();
      sensitive << reset.value_changed_event()
                << rx_data_port.fa_value_changed_event()
                << tx_data_port.fa_value_changed_event();

    SC_METHOD(driver_send_rx_data);
      dont_initialize();
      sensitive << packet_uart_rx.value_changed_event();

    SC_METHOD(driver_send_tx_data);
      dont_initialize();
      sensitive << packet_uart_tx.value_changed_event();

    clock_gen clock_gen_i("clock_gen_i");
    clock_gen_i.clkout(clk);
    clock_gen_i.clkdiv_half(clk_half);
  }

  void driver_get_data();
  void driver_send_rx_data();
  void driver_send_tx_data();

};

#endif
