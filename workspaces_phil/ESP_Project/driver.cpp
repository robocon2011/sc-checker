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
  data.a_i = pi_A.read();
  data.b_i = pi_B.read();
  read_gen.end_transaction(h);

  cout << "read process: \n A = " << data.a_i << "\n B = "<< data.b_i << endl;
  return data;
}

/* transaction recorded write function */
void pipelined_driver_sw2rtl::write(const write_t* p_req){
  int i;

  cout << "\nwrite process: \n"<<endl;

  scv_tr_handle h = write_gen.begin_transaction();

  for(i=0; i< INSTANCES_FULLADDER; i++){
    po_A[i].write(p_req->sign_a[i]);
    po_B[i].write(p_req->sign_b[i]);
  }
  write_gen.end_transaction(h);
}

void driver_sw2rtl::driversw2rtl_thread(){
  int size_a, size_b, size, i;

  bitset<INSTANCES_FULLADDER> b_set[2];

  rw_sw2rtl_task_if::write_t data_w;
  rw_sw2rtl_task_if::write_t* data_ptr;


  /* read data in */
  rw_sw2rtl_task_if::read_t data_r = port_driver->read();

  /* calculate the size of the inputs (bit length) */
  size_a = CHAR_BIT*sizeof(data_r.a_i);
  size_b = CHAR_BIT*sizeof(data_r.b_i);

  size = ((size_a > size_b) ? size_a : size_b);

  /* translate to bit stream */
  for(i=0; i<size;i++){
      if(data_r.a_i&(1<<i)){
          data_w.sign_a[i] = '1';
          b_set[0].set(i);
      }
      else{
          data_w.sign_a[i] = 'Z';
          b_set[0].reset(i);
      }
      if(data_r.b_i&(1<<i)){
          data_w.sign_b[i] = '1';
          b_set[1].set(i);
      }else{
          data_w.sign_b[i] = '0';
          b_set[1].reset(i);
      }

  }

  /* print out results */
  cout << "Bitset 1: " << b_set[0] << endl;
  cout << "Bitset 2: " << b_set[1] << endl;

  /*for(i=0; i< INSTANCES_FULLADDER; i++){
      cout << "Output A " << i << ": " << data_w.sign_a[i] << endl;
  }
  for(i=0; i< INSTANCES_FULLADDER; i++){
      cout << "Output B " << i << ": " << data_w.sign_b[i] << endl;
  }*/
  //*data = data_w;
  /* write data to channel */
  data_ptr = &data_w;

  port_driver->write(data_ptr);
}


