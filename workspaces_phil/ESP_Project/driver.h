/******************************************************************************/
/*                                                                            */
/* Filename:   driver.h                                                   */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#ifndef DRIVER_H
#define DRIVER_

#include "config.h"

/* software to rtl interface */
class rw_sw2rtl_task_if : virtual public sc_interface{
public:
  struct read_t{
    int a_i;
    int b_i;
  };
  struct write_t{
    sc_logic sign_a[INSTANCES_FULLADDER];
    sc_logic sign_b[INSTANCES_FULLADDER];
  };
  virtual read_t read () = 0;
  virtual void write(const write_t*) = 0;
};

SC_MODULE(driver)
{
public:

  /* port declarations */
  sc_in <int> pi_A;
  sc_in <int> pi_B;
  sc_inout <sc_logic> po_A[INSTANCES_FULLADDER];
  sc_inout <sc_logic> po_B[INSTANCES_FULLADDER];

  SC_CTOR(driver)
  /*: pi_A("pi_A"),
    pi_B("pi_B"),
    po_A[0]("po_A_0"),
    po_B[INSTANCES_FULLADDER]("po_B") */
     {}
};

/* driver method */
SC_MODULE(driver_sw2rtl)
{
public:

  sc_port<rw_sw2rtl_task_if> port_driver;

  SC_HAS_PROCESS(driver_sw2rtl);
  driver_sw2rtl (sc_module_name nm){
    SC_METHOD(driversw2rtl_thread)
      sensitive << port_driver;
  }

  void driversw2rtl_thread();
};

/* prepare transaction recording, software to rtl */
class pipelined_driver_sw2rtl
  : public rw_sw2rtl_task_if,
    public driver {

    scv_tr_stream pipelined_stream;
    scv_tr_stream data_stream;

    scv_tr_generator<int> read_gen;
    scv_tr_generator<sc_logic> write_gen;

    //driver_sw2rtl* driver_sub_iptr;

public:
    pipelined_driver_sw2rtl (sc_module_name nm)
    : driver(nm),
      pipelined_stream("pipelined_stream", "driver"),
      data_stream("data_stream", "driver"),
      read_gen("read", pipelined_stream, "data"),
      write_gen("write", pipelined_stream, "data")
    {

    }

    virtual read_t read();
    virtual void write(const write_t* p_req);
  };
#endif
