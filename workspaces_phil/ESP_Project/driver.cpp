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

void driver::driver_method(){
  int size_a, size_b, size, i;
  packet_fulladdr packet;
  bitset<INSTANCES_FULLADDER> b_set[2];
  sc_logic asdf;

  cout << "Driver method" << endl;

  packet.sw_a = port_in[0]->read();
  packet.sw_b = port_in[1]->read();

  /* calculate the size of the inputs (bit length) */
  size_a = CHAR_BIT*sizeof(packet.sw_a);
  size_b = CHAR_BIT*sizeof(packet.sw_b);

  size = ((size_a > size_b) ? size_a : size_b);

  /* translate to bit stream */
  for(i=0; i<INSTANCES_FULLADDER;i++){
      if(packet.sw_a&(1<<i)){
          packet.rtl_a[i] = '1';
          b_set[0].set(i);
      }
      else{
          packet.rtl_a[i] = '0';
          b_set[0].reset(i);
      }
      if(packet.sw_b&(1<<i)){
          packet.rtl_b[i] = '1';
          b_set[1].set(i);
      }else{
          packet.rtl_b[i] = '0';
          b_set[1].reset(i);
      }

      asdf = packet.rtl_a[i];
      cout << "asdf " << i << " : " << asdf << endl;

      port_out_a[i]->write(packet.rtl_a[i]);
      port_out_b[i]->write(packet.rtl_b[1]);
  }

  cout << "packet driver: " << packet << endl;
  cout << "bitset A: " << b_set[0] << endl;
  cout << "bitset B: " << b_set[1] << "\n" << endl;

  rtl2sw_trans_driver_fifo.write(packet);
  rtl2sw_trans_driver.write(packet);
}


