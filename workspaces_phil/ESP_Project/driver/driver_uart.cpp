/******************************************************************************/
/*                                                                            */
/* Filename:   driver.cpp                                                     */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#include <bitset>
#include "driver.h"

void driver_uart::driver_get_data(){

  packet_uart_rx_data packet_temp_rx;
  packet_uart_tx_data packet_temp_tx;

  scv_tr_handle tr_h = input_gen.begin_transaction(packet_temp_rx.sw_data_rx);

  /* read data from stimulator */
  packet_temp_rx.sw_data_rx = rx_data_in->read();
  packet_temp_tx.sw_data_tx = tx_data_in->read();
  packet_temp_rx.sw_reset = packet_temp_tx.sw_reset = reset_in->read();
  packet_temp_tx.sw_ld_tx_data = ld_tx_data_in->read();
  packet_temp_rx.sw_uld_rx_data = uld_rx_data_in->read();
  packet_temp_rx.sw_rx_enable = rx_enable_in->read();
  packet_temp_tx.sw_tx_enable = tx_enable_in->read();

  tr_h.record_attribute("I_driver_data_rx", packet_temp_rx.sw_data_rx);
  tr_h.record_attribute("I_driver_data_tx", packet_temp_tx.sw_data_tx);
  tr_h.record_attribute("I_driver_reset", packet_temp_rx.sw_reset);

  input_gen.end_transaction(tr_h, packet_temp_rx.sw_reset);

  packet_uart_rx.write(packet_temp_rx);
  cout << "packet driver: " << packet_temp_rx << endl;
}

void driver_uart::driver_send_rx_data(){
  packet_uart_rx_data packet_temp;
  string a = "";

  /* read packet data */
  packet_temp = packet_uart_rx.read();

  /* send asynchronous reset */
  if(packet_temp.sw_reset == true){
      packet_temp.rtl_reset = '1';
      reset->write(packet_temp.rtl_reset);
  }
  else{

    /* check control signals */
    packet_temp.rtl_uld_rx_data = (packet_temp.sw_uld_rx_data ? '1' : '0');

    /* unload rx buffer, if requested */
    uld_rx_data.write(packet_temp.rtl_uld_rx_data);
    next_trigger(clk.posedge_event());

    /* translate data to bit stream */
    for(unsigned i=0; i<DATABITS;i++){
      if(packet_temp.sw_data_rx&(1<<i)){
          packet_temp.rtl_rx_data[i] = '1';
          a+="1";
      }
      else{
          packet_temp.rtl_rx_data[i] = '0';
          a+="0";
      }
    }

    /* rx enabled, start of transaction */
    if(packet_temp.rtl_rx_enable == '1'){
      /* send enable rx to DUT */
      rx_enable->write(packet_temp.rtl_rx_enable);

      /* send start of frame */
      packet_temp.rtl_rx_in = '0';
      next_trigger(clk.posedge_event());

      /* send data of frame */
      for(unsigned i = 0; i < DATABITS; i++){
        packet_temp.rtl_rx_in = packet_temp.rtl_rx_data[i];
        next_trigger(clk.posedge_event());
      }
      /* end of frame, end of transaction */
      packet_temp.rtl_rx_in = '1';
      next_trigger(clk.posedge_event());
    }
  } /* end else */
}


void driver_uart::driver_send_tx_data(){
  packet_uart_tx_data packet_temp;
  string a = "";

  /* read packet data */
  packet_temp = packet_uart_tx.read();

  /* send asynchronous reset */
  if(packet_temp.sw_reset == true){
      packet_temp.rtl_reset = '1';
      reset->write(packet_temp.rtl_reset);
  }
  else{

    /* check control signals */
    packet_temp.rtl_ld_tx_data = (packet_temp.sw_ld_tx_data ? '1' : '0');

    /* load tx buffer, if requested */
    ld_tx_data.write(packet_temp.rtl_ld_tx_data);
    next_trigger(clk.posedge_event());

    /* translate data to bit stream */
    for(unsigned i=0; i<DATABITS;i++){
      if(packet_temp.sw_data_tx&(1<<i)){
          packet_temp.rtl_tx_data[i] = '1';
          a+="1";
      }
      else{
          packet_temp.rtl_tx_data[i] = '0';
          a+="0";
      }
    }

    /* rx enabled, start of transaction */
    if(packet_temp.rtl_tx_enable == '1'){
      /* send enable rx to DUT */
      rx_enable->write(packet_temp.rtl_tx_enable);

      /* send start of frame */
      packet_temp.rtl_tx_out = '0';
      next_trigger(clk.posedge_event());

      /* send data of frame */
      for(unsigned i = 0; i < DATABITS; i++){
        packet_temp.rtl_tx_out = packet_temp.rtl_tx_data[i];
        next_trigger(clk.posedge_event());
      }
      /* end of frame, end of transaction */
      packet_temp.rtl_tx_out = '1';
      next_trigger(clk.posedge_event());
    }

  } /* end else */
}
