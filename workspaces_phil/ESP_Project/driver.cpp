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
  int i=0;

  packet_fulladdr packet;

  cout << "Driver method" << endl;

  packet.sw_a = port_in[0]->read();
  packet.sw_b = port_in[1]->read();
  packet.sw_cy = cy_in->read();

  /* translate to bit stream */
  for(i=0; i<BITWIDTH;i++){

      if(packet.sw_a&(1<<i)){
            packet.rtl_a[i] = '1';
        }
        else{
            packet.rtl_a[i] = '0';
        }

        if(packet.sw_b&(1<<i)){
            packet.rtl_b[i] = '1';
        }else{
            packet.rtl_b[i] = '0';
        }

        port_out_a[i]->write(packet.rtl_a[i]);
        port_out_b[i]->write(packet.rtl_b[i]);
    }

  cy_out->write(packet.rtl_cy);
  packet.rtl_cy = packet.sw_cy;

  cout << "packet driver: " << packet << endl;

}


