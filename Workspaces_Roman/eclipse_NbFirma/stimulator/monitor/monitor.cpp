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

/* transaction recorded read function */
rw_rtl2sw_task_if::read_t pipelined_driver_rtl2sw::read(){
  int i;
  read_t data;

  scv_tr_handle h = read_gen.begin_transaction();

  for(i=0; i< INSTANCES_FULLADDER; i++){
  data.sign_a[i]= pi_A[i].read();
  data.sign_b[i] = pi_B[i].read();
  }

  read_gen.end_transaction(h);

  /* print out results */
  for(i=0; i< INSTANCES_FULLADDER; i++){
      cout << "Signal A " << i << ": " << data.sign_a[i] << endl;
  }
  for(i=0; i< INSTANCES_FULLADDER; i++){
      cout << "Signal B " << i << ": " << data.sign_b[i] << endl;
  }

  return data;
}

/* transaction recorded write function */
void pipelined_driver_rtl2sw::write(const write_t* p_req){

  cout << "write process: \n"<<endl;

  scv_tr_handle h = write_gen.begin_transaction();

  po_A.write(p_req->a_i);
  po_B.write(p_req->b_i);

  write_gen.end_transaction(h);

  cout << "write process: \n A = " << po_A << "\n B = "<< po_B << endl;

}

void monitor_rtl2sw::monitor_thread(){
  int i;

  bitset<INSTANCES_FULLADDER> b_set[2];

  rw_rtl2sw_task_if::write_t data_w;

  /* read data in */
  rw_rtl2sw_task_if::read_t data_r = monitor_driver->read();

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
