/******************************************************************************/
/*                                                                            */
/* Filename:   monitor.cpp                                                    */
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
  packet_fulladdr packet_temp;
  bitset<BITWIDTH> b_set[1];

  cout << "monitor method started" << endl;

  for(i=0; i<BITWIDTH;i++){
    packet_temp.rtl_a[i] = port_in_a[i]->read();

    if(packet_temp.rtl_a[i] == 1){
        b_set[0].set(i);
    }
    else{
        b_set[0].reset(i);
    }
  }

  packet_temp.rtl_cy = cy_in->read();
  packet_temp.sw_a = b_set[0].to_ulong();

  rtl2sw_trans_monitor.write(packet_temp);
}

void monitor::monitor_debouncing_method(){
  packet_fulladdr packet_temp;
  static packet_fulladdr packet_temp_old;

  packet_temp = rtl2sw_trans_monitor.read();

  if(packet_temp.sw_a == packet_temp_old.sw_a){
      cout << "packet monitor: " << packet_temp << endl;
      port_out->write(packet_temp.sw_a);
      cy_out->write( cy_in.read()==1 ? true:false );

  }
  else{
      packet_temp_old = packet_temp;
      next_trigger(1, SC_PS);
  }
}
