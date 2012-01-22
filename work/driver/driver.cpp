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
  string a = "",
         b = "";
  packet_fulladdr packet;

  /* begin with transaction recording on ports (esl) */
  scv_tr_handle tr_h = input_gen.begin_transaction(packet.sw_a);



  /* read ports, write values to packet */
  packet.sw_a = port_in[0]->read();
  packet.sw_b = port_in[1]->read();
  packet.sw_cy = cy_in->read();

  /* add attributes to transaction recording */
  tr_h.record_attribute("I_driver_A", packet.sw_a);
  tr_h.record_attribute("I_driver_B", packet.sw_b);
  tr_h.record_attribute("I_driver_carry", packet.sw_cy);

  /* end transaction recording on ports (esl) */
  input_gen.end_transaction(tr_h, packet.sw_cy);

  /* begin with transaction recording on packets (rtl) */
  scv_tr_handle tr_h1 = output_gen_a.begin_transaction(packet.rtl_a[0]);
  scv_tr_handle tr_h2 = output_gen_b.begin_transaction(packet.rtl_b[0]);

  /* translate to bit stream */
  for(i=0; i<BITWIDTH;i++){

      if(packet.sw_a&(1<<i)){
            packet.rtl_a[i] = '1';
            a+="1";
        }
        else{
            packet.rtl_a[i] = '0';
            a+="0";
        }

        if(packet.sw_b&(1<<i)){
            packet.rtl_b[i] = '1';
            b+="1";
        }else{
            packet.rtl_b[i] = '0';
            b+="0";
        }

        port_out_a[i]->write(packet.rtl_a[i]);
        port_out_b[i]->write(packet.rtl_b[i]);
    }

  cy_out->write(packet.rtl_cy);
  packet.rtl_cy = packet.sw_cy;

  /* add attributes to transaction recording*/
  tr_h1.record_attribute("O_driver_A", a);
  tr_h2.record_attribute("O_driver_B", b);
  tr_h2.record_attribute("O_driver_carry", packet.rtl_cy);

  /* end transaction recording on packets (rtl) */
  output_gen_a.end_transaction(tr_h1, packet.rtl_a[BITWIDTH]);
  output_gen_b.end_transaction(tr_h2, packet.rtl_b[BITWIDTH]);

  cout << "packet driver: " << packet << endl;
}


