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
  sc_in<sc_logic>   tx_data[DATABITS];
  sc_in<sc_logic>   tx_enable;
  sc_in<sc_logic>   rxclk;
  sc_in<sc_logic>   uld_rx_data;
  sc_in<sc_logic>   rx_enable;
  sc_in<sc_logic>   rx_in;

  sc_out<sc_logic>  rx_data[DATABITS];
  sc_out<sc_logic>  tx_empty;
  sc_out<sc_logic>  rx_empty;
  sc_out<sc_logic>  tx_out;
  //sc_mutex uart_mutex;

  SC_CTOR(uart){
    SC_METHOD(receive_data);
    dont_initialize();
    sensitive << rxclk.posedge_event()
              << reset.value_changed(); // TODO: eigene method für reset schreiben...

    SC_METHOD(send_data);
    dont_initialize();
    sensitive << txclk.posedge_event()
              << reset.value_changed();
  }

  void receive_data();
  void send_data();

private:
  sc_logic rx_d1, rx_d2;
  sc_logic rx_is_empty, rx_busy,
           rx_over_run, rx_frame_err;
  sc_logic rx_loc_data[DATABITS];
  sc_uint<8>  rx_sample_count, rx_cnt;
  sc_logic tx_is_empty, tx_loc_out, tx_over_run, tx_loc_data[DATABITS];
  sc_uint<8> tx_cnt;
};

#endif
