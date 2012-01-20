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
  packet_uart_rx_data packet_temp_rx;
  static packet_uart_rx_data packet_old_rx;
  bitset<DATABITS> b_set;
  static bool delay = true;

  if(delay == true){
      next_trigger(5, SC_PS);
      delay = false;
  }
  else{
#if (ESP_DL & MONITOR_DETAIL)
    cout << "MONITOR: get_data-process" << endl;
#endif
    delay = true;

    packet_temp_rx.rtl_rx_empty = rx_empty->read();
    for(unsigned i=0;i<DATABITS;i++){
      packet_temp_rx.rtl_rx_data[i] = rx_data_port[i]->read();

      /* decode rx-data */
      if(packet_temp_rx.rtl_rx_data[i] == '1'){
          b_set.set(i);
      }
      else{
          b_set.reset(i);
      }
    }
    packet_temp_rx.sw_data_rx = b_set.to_ulong();

    if(packet_old_rx.sw_data_rx != packet_temp_rx.sw_data_rx){
        s_rx_ok = true;
        packet_old_rx.sw_data_rx = packet_temp_rx.sw_data_rx;
    }

    packet_uart_rx.write(packet_temp_rx);
  }
}

void monitor_uart::monitor_calc(){
  packet_uart_tx_data packet_temp_tx;
  packet_uart_rx_data packet_temp_rx;
  static int data_offset = 0;

#if (ESP_DL & MONITOR_DETAIL)
  cout << "MONITOR: calc-process" << endl;
#endif

  packet_temp_rx = packet_uart_rx.read();
  packet_temp_tx = packet_uart_tx.read();


  /* check if notifiying bit is correct on received data */
  if(packet_temp_rx.rtl_rx_empty == '1'){

    if(packet_temp_rx.sw_data_rx != 0) cout << "ERROR: rx_empty is false" << endl;
    else rx_empty_out.write(((packet_temp_rx.rtl_rx_empty == '1') ? true : false));
  }
  /* if data reg is not empty send data to scoreboard
  if(packet_old_rx.sw_data_rx != packet_temp_rx.sw_data_rx){
     s_rx_ok = true;
     packet_old_rx.sw_data_rx = packet_temp_rx.sw_data_rx;
#if (ESP_DL & MONITOR_DETAIL)
      cout << "MONITOR: rx-packet received: " << packet_temp_rx << endl;
#endif
 }
 else{
     s_rx_ok = false;
 }


  if(packet_old_tx.sw_data_tx != packet_temp_tx.sw_data_tx){
     s_tx_ok = true;
     packet_old_tx.sw_data_tx = packet_temp_tx.sw_data_tx;
#if (ESP_DL & MONITOR_DETAIL)
      cout << "MONITOR: tx-packet received: " << packet_temp_tx << endl;
#endif
 }
 else{
     s_tx_ok = false;
 }*/

    if(initialization == true){
      cout << "~~~ INITIALIZATION ~~~" <<endl;
      initialization = false;
      data_offset = 0;

      next_trigger(txclk.posedge_event());
    }


    if((s_rx_ok == true) && (s_tx_ok == true) && (data_offset < 1000)){

      rx_data_out.write(packet_temp_rx.sw_data_rx);
      tx_data_out.write(packet_temp_tx.sw_data_tx);
      data_written->notify(SC_ZERO_TIME);

      s_rx_ok = false;
      s_tx_ok = false;
      data_offset = 0;

      cout << "MONITOR: ok" <<endl;
    }
    else if((s_rx_ok == true) && (data_offset >= 1000)){
        rx_data_out.write(packet_temp_rx.sw_data_rx);
        tx_data_out.write(0);
        data_written->notify(SC_ZERO_TIME);

        s_rx_ok = false;
        s_tx_ok = false;
        data_offset = 0;

        cout << "TIMEOUT: rx-ok" <<endl;
    }
    else if((s_tx_ok == true) && (data_offset >= 1000)){
        rx_data_out.write(0);
        tx_data_out.write(packet_temp_tx.sw_data_tx);
        data_written->notify(SC_ZERO_TIME);

        s_rx_ok = false;
        s_tx_ok = false;
        data_offset = 0;

        cout << "TIMEOUT: tx-ok" <<endl;
    }
    else{
        data_offset++;
        next_trigger(txclk.posedge_event());
    }
}

void monitor_uart::monitor_catch_tx(){
  packet_uart_tx_data packet_temp_tx;
  static bitset<DATABITS> b_set;
  sc_logic tx_data_in;
  sc_logic tx_finished;

  static bool sof = true, delay = true;
  static int count = 0;

  if(delay == true){
      next_trigger(5, SC_PS);
      delay = false;
  }
  else{
    delay = true;

    tx_finished = '0';
    tx_data_in = tx_out->read();

    /* start of frame detected */
    if((tx_data_in == '0') && (sof == true)){
#if (ESP_DL & MONITOR_DETAIL)
        cout<<"MONITOR: SOF detected" << endl;
#endif
        count = 0;
        b_set = 0;
        sof = false;

        next_trigger(txclk.posedge_event());
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
#if (ESP_DL & MONITOR_DETAIL)
        cout << "MONITOR: catched bit: " << count <<  endl;
#endif
        next_trigger(txclk.posedge_event());
      }

      /*end of frame detected */
      else if(count == DATABITS){
        if(tx_data_in == '0') cout << "MONITOR ERROR: overrun on databits" << endl;
        else{
          sof = true;
          packet_temp_tx.sw_data_tx = b_set.to_ulong();
#if (ESP_DL & MONITOR_DETAIL)
          cout << "MONITOR: monitor received data: " << packet_temp_tx.sw_data_tx << " bin: " << b_set << endl;
#endif
          tx_finished = '1';
          s_tx_ok = true;

          cout << "MONITOR: monitor received data: " << packet_temp_tx.sw_data_tx << " bin: " << b_set << endl;

          /* transmission finished */
          packet_temp_tx.rtl_ld_tx_data = tx_finished;
          packet_uart_tx.write(packet_temp_tx);
        }
      }
    }
  }
}
