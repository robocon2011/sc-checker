/******************************************************************************/
/*                                                                            */
/* Filename:   monitor_uart.cpp                                                    */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/


#include "monitor.h"

void monitor_uart::monitor_get_data(){
  packet_uart_tx_data packet_temp_tx;
  packet_uart_rx_data packet_temp_rx;
  //sc_logic s_clk;

  cout << "MONITOR: get_data-process" << endl;

  packet_temp_rx.rtl_rx_empty = rx_empty->read();
  for(unsigned i=0;i<DATABITS;i++){
    packet_temp_rx.rtl_rx_data[i] = rx_data_port[i]->read();
  }
  packet_temp_tx.rtl_tx_empty = tx_empty->read();
  //s_clk = rxclk.read();

  packet_uart_rx.write(packet_temp_rx);
  packet_uart_tx.write(packet_temp_tx);
}

void monitor_uart::monitor_calc(){
  packet_uart_tx_data packet_temp_tx;
  packet_uart_rx_data packet_temp_rx;
  bitset<BITWIDTH> b_set;

  cout << "MONITOR: calc-process" << endl;

  packet_temp_rx = packet_uart_rx.read();
  packet_temp_tx = packet_uart_tx.read();

  /* check if notifiying bit is correct on received data */
  if(packet_temp_rx.rtl_rx_empty == '1'){
    for(unsigned i = 0; i < DATABITS; i++){
      if(packet_temp_rx.rtl_rx_data[i] == '1'){
          b_set.set(i);
      }
      else{
          b_set.reset(i);
      }
    }

    packet_temp_rx.sw_data_rx = b_set.to_ulong();
    if(packet_temp_rx.sw_data_rx != 0) cout << "ERROR: rx_empty is false" << endl;
    else rx_empty_out.write(((packet_temp_rx.rtl_rx_empty == '1') ? true : false));
  }
  else rx_data_out.write(packet_temp_rx.sw_data_rx);


  /* check if notifiying bit is correct on transmitted data */
  if(packet_temp_tx.rtl_ld_tx_data == '1'){
    if(packet_temp_tx.rtl_tx_empty == '1'){
      if(packet_temp_tx.sw_data_tx != 0) cout << "ERROR: rx_empty is false" << endl;
      else tx_empty_out.write(((packet_temp_tx.rtl_tx_empty == '1') ? true : false));
    }
  }
  else tx_data_out.write(packet_temp_tx.sw_data_tx);

}

void monitor_uart::monitor_catch_tx(){
  packet_uart_tx_data packet_temp_tx;
  bitset<DATABITS> b_set;
  sc_logic tx_data_in;
  sc_logic tx_finished;
  static bool sof = true;
  static int count = 0;

  tx_finished = '0';
  tx_data_in = tx_out->read();

  cout << "MONITOR: catch-tx-process" << endl;

  /* start of frame detected */
  if((tx_data_in == '0') && (sof == true)){
      cout<<"SOF detected" << endl;
      sof = false;
  }
  else{

    /* catch transmitted data */
    if(count < DATABITS){
      if(tx_data_in == '1'){
          b_set.set(count);
      }
      else{
          b_set.reset(count);
      }
      count++;
    }

    /*end of frame detected */
    else if(count == (DATABITS+1)){
      if(tx_data_in == '0') cout << "ERROR: overrun on databits" << endl;
      else{
        sof = true;
        packet_temp_tx.sw_data_tx = b_set.to_ulong();
        tx_finished = '1';
      }
    }
  }
  packet_temp_tx.rtl_ld_tx_data = tx_finished;
  packet_uart_tx.write(packet_temp_tx);
}
