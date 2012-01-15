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

  SC_CTOR(uart){
    SC_METHOD(receive_data);
    dont_initialize();
    sensitive << rx_in.neg()
              << reset.value_changed(); // TODO: eigene method für reset schreiben...

    SC_METHOD(send_data);
    dont_initialize();
    sensitive << ld_tx_data.value_changed()
              << tx_data[0].value_changed()
              << tx_data[1].value_changed()
              << tx_data[2].value_changed()
              << tx_data[3].value_changed()
              << tx_data[4].value_changed()
              << tx_data[5].value_changed()
              << tx_data[6].value_changed()
              << tx_data[7].value_changed()
              << tx_enable.value_changed()
              << reset.value_changed();
  }

  void receive_data();
  void send_data();

};

#endif
