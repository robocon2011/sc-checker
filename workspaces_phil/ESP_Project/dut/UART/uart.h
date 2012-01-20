/******************************************************************************/
/*                                                                            */
/* Filename:   uart.h                                                         */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#ifndef UART_H
#define UART_H

#include "../../global.h"
#include <systemc.h>
#include <scv.h>


SC_MODULE(uart){

  /*declaration of ports */
  sc_in<sc_logic>   txclk;
  sc_in<sc_logic>   reset;
  sc_in<sc_logic>   ld_tx_data;
  sc_in<sc_logic>   tx_enable;
  sc_in<sc_logic>   rxclk;
  sc_in<sc_logic>   uld_rx_data;
  sc_in<sc_logic>   rx_enable;
  sc_in<sc_logic>   rx_in;
  sc_in<sc_logic>   tx_data[DATABITS];

  sc_out<sc_logic>  rx_data[DATABITS];
  sc_out<sc_logic>  tx_empty;
  sc_out<sc_logic>  rx_empty;
  sc_out<sc_logic>  tx_out;

  sc_port < handshake_generation_if > data_written_rx;
  sc_port < handshake_event_if > data_written_driver;

  SC_CTOR(uart){
    SC_METHOD(receive_data);
    dont_initialize();
    sensitive << rx_in.neg()
              << reset.value_changed();

    SC_METHOD(send_data);
    dont_initialize();
    sensitive << data_written_driver;
  }

  void receive_data();
  void send_data();

};

#endif
