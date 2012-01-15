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
#if (ESP_DL & DRIVER_DETAIL)
  cout << "DRIVER: get_data-process" << endl;
#endif

  /* read data from stimulator */
  packet_temp_rx.sw_data_rx = rx_data_in->read();
  packet_temp_tx.sw_data_tx = tx_data_in->read();
  packet_temp_rx.sw_reset = reset_in->read();

  packet_temp_tx.sw_reset = packet_temp_rx.sw_reset;
  packet_temp_rx.sw_rx_enable = rx_enable_in->read();
  packet_temp_tx.sw_tx_enable = tx_enable_in->read();

  tr_h.record_attribute("I_driver_data_rx", packet_temp_rx.sw_data_rx);
  tr_h.record_attribute("I_driver_data_tx", packet_temp_tx.sw_data_tx);
  tr_h.record_attribute("I_driver_reset", packet_temp_rx.sw_reset);

  input_gen.end_transaction(tr_h, packet_temp_rx.sw_reset);

  /* workaround for loading and unloading data */
  packet_temp_rx.sw_uld_rx_data = packet_temp_rx.sw_rx_enable;
  packet_temp_tx.sw_ld_tx_data = packet_temp_tx.sw_tx_enable;

  packet_uart_tx.write(packet_temp_tx);
  packet_uart_rx.write(packet_temp_rx);

}

void driver_uart::driver_send_rx_data(){
  packet_uart_rx_data packet_temp;
  static int count = 0;
  static bool eof = false, data_uld = false, initialization = true;

  /* check debug level */
#if (ESP_DL & DRIVER_DETAIL)
  cout << "DRIVER: rx-process" << endl;
#endif

#if (ESP_DL & DRIVER)

  tracefile_driver = sc_create_vcd_trace_file("driver_trace");

  if (!tracefile_driver){
      cout << "Error creating driver tracefile." << endl;
  }

  /* transaction recording */
  sc_trace(tracefile_driver, packet_temp.rtl_rx_in, "rx_in");
  sc_trace(tracefile_driver, packet_temp.rtl_reset, "reset");
  sc_trace(tracefile_driver, packet_temp.rtl_rx_enable, "rx_enable");
  sc_trace(tracefile_driver, packet_temp.rtl_uld_rx_data, "uld_rx_data");

  sc_trace(tracefile_driver, s_clk2, "s_clk");


#endif

  /* read packet data */
  packet_temp = packet_uart_rx.read();

    /* send asynchronous reset */
    if((packet_temp.sw_reset == true) || (initialization == true)){
      packet_temp.rtl_reset = '1';
      initialization = false;
#if (ESP_DL & DRIVER_DETAIL)
      cout << "DRIVER: rx catched sw-reset" << endl;
#endif
    }
    else{
      /* clear reset */
      packet_temp.rtl_reset = '0';

      /* check control signals and sent them correct */
      if((packet_temp.sw_uld_rx_data ==  '1') && (data_uld == false)){
        packet_temp.rtl_uld_rx_data = '1';
        data_uld = true;
      }
      else if (packet_temp.sw_uld_rx_data ==  '0'){
        packet_temp.rtl_uld_rx_data = '0';
        data_uld = false;
      }
      else{
        packet_temp.rtl_uld_rx_data = '0';
      }

      packet_temp.rtl_rx_enable = (packet_temp.sw_rx_enable ? '1' : '0');

      /* translate data to bit stream */
      for(unsigned i=0; i<DATABITS;i++){
        if(packet_temp.sw_data_rx&(1<<i)){
            packet_temp.rtl_rx_data[i] = '1';
        }
        else{
            packet_temp.rtl_rx_data[i] = '0';
        }
      }

      /* rx enabled, start of transaction */
      if(packet_temp.rtl_rx_enable == '1'){

        if(count == 0){
          /* send start of frame */
          packet_temp.rtl_rx_in = '0';
          rx_in.write(packet_temp.rtl_rx_in);

#if (ESP_DL & DRIVER_DETAIL)
          cout << "DRIVER: SOF sent" << endl;
#endif

          count++;
          next_trigger(s_clk.posedge_event());
        }
        else if(count <= DATABITS){
          /* send data of frame */
          packet_temp.rtl_rx_in = packet_temp.rtl_rx_data[count-1];
          rx_in.write(packet_temp.rtl_rx_in);

#if (ESP_DL & DRIVER_DETAIL)
          cout << "DRIVER: Bit " << count << "sent" << endl;
#endif

          count++;
          next_trigger(s_clk.posedge_event());
        }
        else{
          /* end of frame, end of transaction */
          if(eof == false){
            packet_temp.rtl_rx_in = '1';
            rx_in.write(packet_temp.rtl_rx_in);

#if (ESP_DL & DRIVER_DETAIL)
            cout << "DRIVER: EOF sent" << endl;
            cout << "DRIVER: packet rx sent: " << packet_temp << endl;
#endif
            cout << "DRIVER: rx-data sent: " << packet_temp.sw_data_rx << endl;

            next_trigger(s_clk.posedge_event());
            eof = true;
          }else{
              eof = false;
              count = 0;
          }
        }
      }

    } /* end else */

    /* send control signals to dut */
    reset->write(packet_temp.rtl_reset);
    rx_enable->write(packet_temp.rtl_rx_enable);
    uld_rx_data->write(packet_temp.rtl_uld_rx_data);    /* unload rx buffer, if requested */

}

void driver_uart::driver_send_tx_data(){
  packet_uart_tx_data packet_temp;
  static bool initialization = true;

#if (ESP_DL & DRIVER_DETAIL)
  cout << "DRIVER: tx-process" << endl;
#endif

  /* read packet data */
  packet_temp = packet_uart_tx.read();
#if (ESP_DL & DRIVER_DETAIL)
  cout << "DRIVER: got tx-packet: " << packet_temp.sw_data_tx << endl;
#endif
  /* send asynchronous reset */
  if((packet_temp.sw_reset == true) || (initialization == true)){
      packet_temp.rtl_reset = '1';
      initialization = false;
#if (ESP_DL & DRIVER_DETAIL)
      cout << "DRIVER: catched sw-reset" << endl;
#endif
  }
  else{

    /* check control signals */
    packet_temp.rtl_reset = '0';
    packet_temp.rtl_ld_tx_data = '1';
    packet_temp.rtl_tx_enable = (packet_temp.sw_tx_enable ? '1' : '0');

    /* translate data to bit stream */
    for(unsigned i=0; i<DATABITS;i++){
      if(packet_temp.sw_data_tx&(1<<i)){
          packet_temp.rtl_tx_data[i] = '1';
      }
      else{
          packet_temp.rtl_tx_data[i] = '0';
      }

      /* send tx data to dut */
      tx_data_port[i]->write(packet_temp.rtl_tx_data[i]);
#if (ESP_DL & DRIVER_DETAIL)
      cout << "DRIVER: sent package to DUT: " << packet_temp.rtl_tx_data[i] << endl;
#endif
    }
  } /* end else */
  cout << "DRIVER: tx-data sent: " << packet_temp.sw_data_tx << endl;
  reset->write(packet_temp.rtl_reset);
  tx_enable->write(SC_LOGIC_1);
  ld_tx_data->write(packet_temp.rtl_ld_tx_data); /* load tx buffer, if requested */
}
