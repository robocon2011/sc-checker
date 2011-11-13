/******************************************************************************/
/*                                                                            */
/* Filename:   driver.cpp                                                     */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#include <scv.h>
#include <bitset>

#include "driver.h"

/* transaction recorded read function */
rw_sw2rtl_task_if::read_t pipelined_driver_sw2rtl::read(){
  read_t data;

  scv_tr_handle h = read_gen.begin_transaction();
  data.a_i= pi_A.read();
  data.b_i = pi_B.read();
  read_gen.end_transaction(h);

  cout << "read process: \n A = " << data.a_i << "\n B = "<< data.b_i << endl;
  return data;
}

/* transaction recorded write function */
void pipelined_driver_sw2rtl::write(const write_t* p_req){
  int i;

  cout << "write process: \n"<<endl;

  scv_tr_handle h = write_gen.begin_transaction();

  for(i=0; i< INSTANCES_FULLADDER; i++){
  po_A[i].write(p_req->sign_a[i]);
  po_B[i].write(p_req->sign_b[i]);
  }
  write_gen.end_transaction(h);

  /* print out results */
  for(i=0; i< INSTANCES_FULLADDER; i++){
      cout << "Signal A " << i << ": " << po_A[i] << endl;
  }
  for(i=0; i< INSTANCES_FULLADDER; i++){
      cout << "Signal B " << i << ": " << po_B[i] << endl;
  }

}

void driver_sw2rtl::driver_thread(){
  int size_a, size_b, size, i;

  bitset<INSTANCES_FULLADDER> b_set[2];

  rw_sw2rtl_task_if::write_t data_w;

  /* read data in */
  rw_sw2rtl_task_if::read_t data_r = port_driver->read();

  /* calculate the size of the inputs (bit length) */
  size_a = CHAR_BIT*sizeof(data_r.a_i);
  size_b = CHAR_BIT*sizeof(data_r.b_i);

  size = ((size_a > size_b) ? size_a : size_b);

  /* translate to bit stream */
  for(i=0; i<size;i++){
      if(data_r.a_i&(1<<i)){
          data_w.sign_a[i] = 1;
          b_set[0].set(i);
      }
      if(data_r.b_i&(1<<i)){
          data_w.sign_a[i] = 1;
          b_set[1].set(i);
      }
  }

  /* write data to channel */
  port_driver->write(&data_w);
}


