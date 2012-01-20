/******************************************************************************/
/*                                                                            */
/* Filename:   uart.cpp                                                       */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#include "uart.h"

void uart::receive_data(){

  /* store inputs to local values */
  static sc_logic s_rx_is_empty, s_rx_busy,
           s_rx_over_run, s_rx_frame_err, s_rx_loc_data[DATABITS];
  static sc_uint<DATABITS> s_rx_cnt;
  sc_logic s_reset, s_rx_in, s_uld_data, s_rx_enable;
  static bool delay = true;

  /* delay it for a small amount of time */
  if(delay == true){
      next_trigger(5, SC_PS);
      delay = false;
  }
  else{
    delay = true;

    s_reset = reset.read();
    s_rx_in = rx_in.read();
    s_uld_data = uld_rx_data.read();
    s_rx_enable = rx_enable.read();

    /* asynchronous reset */
    if(s_reset == '1'){
        s_rx_is_empty = '1';
        s_rx_busy = '0';
        s_rx_over_run = '0';
        s_rx_frame_err = '0';
        for(unsigned i = 0; i < DATABITS;i++){
            s_rx_loc_data[i] = '0';
        }
        s_rx_cnt = 0;

#if (ESP_DL & DUT_DETAIL)
        cout << "UART: uart reseted" << endl;
#endif

    }
    else{

      /* unload the rx data */
      if(s_uld_data == '1'){
          for(unsigned i = 0; i < DATABITS;i++){
              s_rx_loc_data[i] = '0';
          }
          s_rx_is_empty = '1';

#if (ESP_DL & DUT_DETAIL)
          cout << "UART: unloading data...." << endl;
#endif

          next_trigger(rxclk.posedge_event());
      }
      else s_rx_is_empty = '0';
      rx_empty.write(s_rx_is_empty);

      /* receive data when rx is enabled */
      if(s_rx_enable == '1'){

          /* check if start of frame received */
          if((s_rx_busy == '0') && (s_rx_in == '0')){
              s_rx_busy = '1';
              s_rx_cnt = 0;

#if (ESP_DL & DUT_DETAIL)
              cout<<"UART: SOF detected" << endl;
#endif

              next_trigger(rxclk.posedge_event());
          }

          /* SOF detected, get data */
          else if(s_rx_busy == '1'){

              /* data read */
              if(s_rx_cnt <= DATABITS){

                /* start storing data */
                if(s_rx_cnt < DATABITS){
                    s_rx_loc_data[s_rx_cnt] = s_rx_in;

#if (ESP_DL & DUT_DETAIL)
                    cout << "UART: received data bit" << s_rx_cnt << ": " << s_rx_in << endl;
#endif
                    next_trigger(rxclk.posedge_event());
                }
                else if(s_rx_cnt == DATABITS){
                    s_rx_busy = '0';

                    /* Check for end of the frame */
                    if(s_rx_in == '0'){
                        s_rx_frame_err = '1';
#if (ESP_DL & DUT_DETAIL)
                        cout << "UART: uart-rx frame error" << endl;
#endif
                    }
                    else{
                        s_rx_is_empty = '0';
                        s_rx_frame_err = '0';

                        /* Check if last data was not unloaded */
                        if(s_rx_is_empty == '1'){
                            s_rx_over_run = '0';
                        }
                        else{
                            s_rx_over_run = '1';
#if (ESP_DL & DUT_DETAIL)
                            cout << "UART: uart-rx overrun" << endl;
#endif
                        }
                        for(unsigned i = 0; i < DATABITS; i++) rx_data[i].write(s_rx_loc_data[i]);
                        data_written_rx->notify(SC_ZERO_TIME);
#if (ESP_DL & DUT_DETAIL)
                        cout << "UART: rx-data reg written to monitor" << endl;
#endif
                    }
#if (ESP_DL & DUT_DETAIL)
                    cout << "UART: uart-rx transmission finished" << endl;
#endif
                    next_trigger(rxclk.posedge_event());
                }
                s_rx_cnt++;
            }
        }
      }else s_rx_busy = '0';
    }
  }
}

void uart::send_data(){
  /* store inputs to local values */
  static sc_logic s_tx_is_empty, s_tx_loc_out, s_tx_over_run, s_tx_loc_data[DATABITS];
  static sc_uint<DATABITS> s_tx_cnt;
  static sc_logic s_reset, s_ld_data, s_tx_enable, s_tx_sof;

  s_reset = reset.read();
  s_ld_data = ld_tx_data.read();
  s_tx_enable = tx_enable.read();


  /* asynchronous reset */
  if(s_reset == '1'){
      for(unsigned i = 0; i < DATABITS; i++){
        s_tx_loc_data[i] = '0';
      }
      s_tx_loc_out = '1';
      s_tx_is_empty = '1';
      s_tx_over_run = '0';
      s_tx_cnt = 0;
      s_tx_sof = '1';
#if (ESP_DL & DUT_DETAIL)
      cout << "UART: uart reseted (tx)" << endl;
#endif
  }
  else{

      /* load data */
      if(s_ld_data == '1'){

          /* check for overrun */
          if((s_tx_is_empty == '0') && (s_tx_cnt > DATABITS)){
              s_tx_over_run = '0';
#if (ESP_DL & DUT_DETAIL)
              cout << "UART: uart-tx overrun" << endl;
#endif
          }
          else if(s_tx_is_empty == '1'){
              for(unsigned i = 0; i < DATABITS; i++) s_tx_loc_data[i] = tx_data[i]->read();
              s_tx_is_empty = '0';
              s_tx_sof = '1';
#if (ESP_DL & DUT_DETAIL)
              cout << "UART: tx-data loaded" << endl;
#endif
          }
      }

      /* start transmit frame */
      if((s_tx_enable == '1') && (s_tx_is_empty == '0')){
          if((s_tx_cnt == 0) && (s_tx_sof == '1')){
              s_tx_loc_out = '0';
              s_tx_sof = '0';
#if (ESP_DL & DUT_DETAIL)
              cout << "UART: SOF sent";
#endif
              next_trigger(txclk.posedge_event());
          }
          else if (s_tx_cnt < DATABITS){
              s_tx_loc_out = s_tx_loc_data[s_tx_cnt];
              s_tx_cnt++;
#if (ESP_DL & DUT_DETAIL)
              cout << "UART: sent data bit " << s_tx_cnt << ": " << s_tx_loc_out << endl;
#endif
              next_trigger(txclk.posedge_event());
          }
          else if (s_tx_cnt == DATABITS){
              s_tx_loc_out = '1';
              s_tx_cnt = 0;
              s_tx_is_empty = '1';
              s_tx_sof = '1';

//#if (ESP_DL & UART_DETAIL)
              cout << "UART: uart-tx transmission finished" << endl;
//#endif
          }
      }
      else if (s_tx_enable == '0'){
          s_tx_cnt = 0;
          s_tx_loc_out = '1';
      }

      tx_empty.write(s_tx_is_empty);
      tx_out.write(s_tx_loc_out);
  }
}
