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

void usart::receive_data(){

  /* asynchronous reset */
  if(reset == '1'){
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
    rx_d1 = rx_in;

    /* unload the rx data */
    if(uld_rx_data == '1'){
        for(unsigned i = 0; i < DATABITS;i++){
            rx_loc_data[i] = '0';
        }
        rx_is_empty = '1';
    }

    /* receive data when rx is enabled */
    if(rx_enable == '1'){

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
    if(rx_enable == '0') rx_busy = '0';
    rx_empty = rx_is_empty;
    for(unsigned i = 0; i < DATABITS; i++) rx_data[i] = rx_loc_data[i];
  }

}

void usart::send_data(){

  /* asynchronous reset */
  if(reset == '1'){
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
      if(ld_tx_data == '1'){

          /* check for overrun */
          if(tx_is_empty == '0'){
              tx_over_run = '0';
          }
          else{
              for(unsigned i = 0; i < DATABITS; i++) tx_loc_data[i] = tx_data[i];
              tx_is_empty = '0';
          }
      }

      /* start transmit frame */
      if((tx_enable == '1') && (tx_is_empty == '0')){
          if(tx_cnt == 0){
              tx_loc_out = '0';
          }
          else if ((tx_cnt > 0) && (tx_cnt < 9)){
              tx_out = tx_data[tx_cnt-1];
          }
          else if (tx_cnt == (DATABITS + 1)){
              tx_loc_out = '1';
              tx_cnt = 0;
              tx_is_empty = '1';
          }
          tx_cnt++;
      }
      else if (tx_enable == '0'){
          tx_cnt = 0;
      }
  }
  tx_empty = tx_is_empty;
  tx_out = tx_loc_out;
}
