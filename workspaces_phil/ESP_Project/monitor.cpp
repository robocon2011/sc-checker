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
  packet_fulladdr packet;
  bitset<INSTANCES_FULLADDER> b_set[2];

  cout << "Monitor method dude: " << endl;

  for(i=0; i<INSTANCES_FULLADDER;i++){
      packet.rtl_a[i] = port_in_a[i]->read();
      packet.rtl_b[i] = port_in_b[i]->read();

      if(packet.rtl_a[i] == 1){
          b_set[0].set(i);
      }
      else{
          b_set[0].reset(i);
      }

      if(packet.rtl_b[i] == 1){
          b_set[1].set(i);
      }
      else{
          b_set[0].reset(i);
      }
  }

  packet.sw_a = b_set[0].to_ulong();
  packet.sw_b = b_set[1].to_ulong();

  cout << "packet monitor: " << packet << endl;

  rtl2sw_trans_fifo.write(packet);
  rtl2sw_trans_monitor.write(packet);
}
