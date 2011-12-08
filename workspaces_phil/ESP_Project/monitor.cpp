/******************************************************************************/
/*                                                                            */
/* Filename:   monitor.cpp                                                     */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/


#include "monitor.h"
#include <bitset>

void monitor::monitor_method(){
  int i=0;
  packet_fulladdr_lv packet_temp;
  bitset<BITWIDTH> b_set[1];

  for(i=0; i<BITWIDTH;i++){
    packet_temp.rtl_a[i] = port_in_a->read().bit(i);

    if(packet_temp.rtl_a[i] == 1){
        b_set[0].set(i);
    }
    else{
        b_set[0].reset(i);
    }
  }

  cout << "Monitor method: " << endl;

  packet_temp.rtl_cy = cy_in->read();
  packet_temp.sw_a = b_set[0].to_ulong();

  rtl2sw_trans_fifo.write(packet_temp);
  rtl2sw_trans_monitor.write(packet_temp);
}

void monitor::monitor_thread(){
  packet_fulladdr_lv packet_temp, packet_temp_old;

  while(1){
    packet_temp = rtl2sw_trans_fifo.read();

    if(packet_temp == packet_temp_old){}
    else
    {
      cout << "packet monitor: " << packet_temp << endl;
      port_out->write(packet_temp.sw_a);
      cy_out->write(0);
      packet_temp = packet_temp_old;
    }
  }
}
