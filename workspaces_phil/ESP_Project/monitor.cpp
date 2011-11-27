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

/* constructor declarations */
//monitor_rtl2sw::monitor_rtl2sw(){}

/* transaction recorded read function */
rw_rtl2sw_task_if::read_t pipelined_monitor_rtl2sw::read(){
  int i;
  read_t data;

  scv_tr_handle h = read_gen.begin_transaction();

  for(i=0; i< INSTANCES_FULLADDER; i++){
  data.sign_a[i] = pi_mon_A[i].read();
  data.sign_b[i] = pi_mon_B[i].read();
  }

  cout << "\nMonitor reads...!!!\n " << endl;

  read_gen.end_transaction(h);

  /* print out results */
  for(i=0; i< INSTANCES_FULLADDER; i++){
      cout << "Input A " << i << ": " << data.sign_a[i] << endl;
  }
  for(i=0; i< INSTANCES_FULLADDER; i++){
      cout << "Input B " << i << ": " << data.sign_b[i] << endl;
  }

  return data;
}

/* transaction recorded write function */
void pipelined_monitor_rtl2sw::write(const write_t* p_req){

  cout << "monitor writes: \n"<<endl;

  scv_tr_handle h = write_gen.begin_transaction();

  po_mon_A.write(p_req->a_i);
  po_mon_B.write(12);

  write_gen.end_transaction(h);

  cout << "write process: \n A = " << po_mon_A << "\n B = "<< po_mon_B << endl;

}

void monitor_rtl2sw::monitor_thread(){
  int i;

  bitset<INSTANCES_FULLADDER> b_set[2];

  rw_rtl2sw_task_if::write_t data_w;

  /* read data in */
  rw_rtl2sw_task_if::read_t data_r = monitor_driver->read();

  cout << "Monitor output:" << data_r.sign_a[0] << endl;

  /* translate to bit stream */
  for(i=0; i<INSTANCES_FULLADDER;i++){
      if(data_r.sign_a[i] == 1){
          b_set[0].set(i);
      }
      if(data_r.sign_b[i] == 1){
          b_set[1].set(i);
      }
  }

  /* convert to unsigned long */
  data_w.a_i = b_set[0].to_ulong();
  data_w.b_i = b_set[1].to_ulong();

  /* write data to channel */
  monitor_driver->write(&data_w);
}
