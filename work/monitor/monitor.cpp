/******************************************************************************/
/*                                                                            */
/* Filename:   monitor.cpp                                                    */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/* Project:     SystemC Checker                                               */
/*                                                                            */
/* Topmodule:   Monitor                                                       */
/* Submodules:  ------                                                        */
/*                                                                            */
/******************************************************************************/


#include "monitor.h"

void monitor::monitor_method(){
  int i=0;
  packet_fulladdr packet_temp;
  bitset<BITWIDTH> b_set[1];


  for(i=0; i<BITWIDTH;i++){
    packet_temp.rtl_a[i] = port_in_a[i]->read();

    if(packet_temp.rtl_a[i] == 1){
        b_set[0].set(i);
    }
    else{
        b_set[0].reset(i);
    }
  }

  /* read data from dut */
  packet_temp.rtl_cy = cy_in->read();
  packet_temp.sw_a = b_set[0].to_ulong();
  packet_temp.b_set[0] = b_set[0];

  rtl2sw_trans_monitor.write(packet_temp);
}

void monitor::monitor_debouncing_method(){
  packet_fulladdr packet_temp;
  static packet_fulladdr packet_temp_old;
  static bool first_call = true;

  /* read packet from channel */
  packet_temp = rtl2sw_trans_monitor.read();

  if(packet_temp.sw_a == packet_temp_old.sw_a){

      /* check for first call */
      if(!first_call){

        /* begin with transaction recording on inputs */
        scv_tr_handle tr_h = mon_in_gen.begin_transaction(packet_temp.rtl_a[0]);

        /* add attributes to transaction recording */
        tr_h.record_attribute("I_monitor", packet_temp.b_set[0].to_string());
        tr_h.record_attribute("I_monitor_carry", packet_temp.rtl_cy);

        /* end transaction recording on inputs */
        mon_in_gen.end_transaction(tr_h, packet_temp.rtl_a[BITWIDTH]);

        packet_temp.sw_cy = (packet_temp.rtl_cy == '1') ? true : false;

        cout << "packet monitor: " << packet_temp << endl;

        /* begin with transaction recording on outputs */
        scv_tr_handle tr_h1 = mon_out_gen.begin_transaction(packet_temp.sw_a);

        /* add attributes to transaction recording */
        tr_h1.record_attribute("O_monitor", packet_temp.sw_a);
        tr_h1.record_attribute("O_monitor_carry", packet_temp.sw_cy);
        port_out->write(packet_temp.sw_a);
        cy_out->write(packet_temp.sw_cy);

        /* end transaction recording on outputs */
        mon_out_gen.end_transaction(tr_h1, cy_out);

        /* notify the scoreboard, that the data had been written */
        data_written->notify(SC_ZERO_TIME);
      }
      else first_call = false;
  }
  else{
      /* values from dut are not stable */
      packet_temp_old = packet_temp;
      next_trigger(1, SC_PS);
  }
}
