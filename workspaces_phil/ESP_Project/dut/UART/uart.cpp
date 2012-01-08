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

  cout << "UART: receive_data-process" << endl;

  /* store inputs to local values */
  sc_logic s_reset, s_rx_in, s_uld_data, s_rx_enable;

    s_reset = '0';
    //s_reset = reset.read();

  s_rx_in = rx_in.read();
  s_uld_data = uld_rx_data.read();
  s_rx_enable = rx_enable.read();

  /* asynchronous reset */
  if(s_reset == '1'){
      rx_d1 = '1';
      rx_d2 = '1';
      rx_is_empty = '1';
      rx_busy = '0';
      rx_over_run = '0';
      rx_frame_err = '0';
      for(unsigned i = 0; i < DATABITS;i++){
          rx_loc_data[i] = '0';
      }
      rx_cnt = 0;
      rx_sample_count = 0;
  }
  else{
    /* synchr. the asynchr. signal */
    rx_d2 = rx_d1;
    rx_d1 = s_rx_in;

    /* unload the rx data */
    if(s_uld_data == '1'){
        for(unsigned i = 0; i < DATABITS;i++){
            rx_loc_data[i] = '0';
        }
        rx_is_empty = '1';
    }

    /* receive data when rx is enabled */
    if((s_rx_enable == '1') && (rxclk.read() == '1')){

        /* check if start of frame received */
        if((rx_busy == '0') && (rx_d2 == '0')){
            rx_busy = '1';
            rx_sample_count = 1;
            rx_cnt = 0;
        }

        /* SOF detected, get data */
        if(rx_busy == '1'){
            rx_sample_count++;

            /* data read */
            if(rx_sample_count == (DATABITS-1)){
                if((rx_d2 == '1') && (rx_cnt == 0)){
                    rx_busy = '0';
                }
                else{
                    rx_cnt++;

                    /* start storing data */
                    if((rx_cnt > 0) && (rx_cnt < (DATABITS+1))){
                        rx_loc_data[rx_cnt - 1] = rx_d2;
                    }
                    else if(rx_cnt == 9){
                        rx_busy = '0';

                        /* Check for end of the frame */
                        if(rx_d2 == '0'){
                            rx_frame_err = '1';
                        }
                        else{
                            rx_is_empty = '0';
                            rx_frame_err = '0';

                            /* Check if last data was not unloaded */
                            if(rx_is_empty == '1'){
                                rx_over_run = '0';
                            }
                            else{
                                rx_over_run = '1';
                            }
                        }
                    }
                }
            }
        }
    }
    if(s_rx_enable == '0') rx_busy = '0';
    rx_empty.write(rx_is_empty);
    for(unsigned i = 0; i < DATABITS; i++) rx_data[i].write(rx_loc_data[i]);
  }

}

void uart::send_data(){
  /* store inputs to local values */
  sc_logic s_reset, s_ld_data, s_tx_enable;

  cout << "UART: send_data-process" << endl;

  s_reset = reset.read();

  s_ld_data = ld_tx_data.read();
  s_tx_enable = tx_enable.read();

  /* asynchronous reset */
  if(s_reset == '1'){
      for(unsigned i = 0; i < DATABITS; i++){
        tx_loc_data[i] = '0';
      }
      tx_loc_out = '0';
      tx_is_empty = '0';
      tx_over_run = '0';
      tx_cnt = 0;
  }
  else{

      /* load data */
      if(s_ld_data == '1'){

          /* check for overrun */
          if(tx_is_empty == '0'){
              tx_over_run = '0';
          }
          else{
              for(unsigned i = 0; i < DATABITS; i++) tx_loc_data[i] = tx_data[i].read();
              tx_is_empty = '0';
          }
      }

      /* start transmit frame */
      if((s_tx_enable == '1') && (tx_is_empty == '0')){
          if(tx_cnt == 0){
              tx_loc_out = '0';
          }
          else if ((tx_cnt > 0) && (tx_cnt < 9)){
              tx_loc_out = tx_loc_data[tx_cnt-1];
          }
          else if (tx_cnt == (DATABITS + 1)){
              tx_loc_out = '1';
              tx_cnt = 0;
              tx_is_empty = '1';
          }
          tx_cnt++;
      }
      else if (s_tx_enable == '0'){
          tx_cnt = 0;
      }
  }
  tx_empty.write(tx_is_empty);
  tx_out.write(tx_loc_out);
}
