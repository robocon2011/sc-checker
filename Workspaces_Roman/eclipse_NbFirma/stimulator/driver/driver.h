/******************************************************************************/
/*                                                                            */
/* Filename:   driver.h                                                   */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#ifndef driver_H
#define driver_

#include "config.h"

SC_MODULE(driver)
{
  /* port declarations */


#warning "modified code by Roman"
//  sc_inout <int> pi_A;
//  sc_inout <int> pi_B;
	sc_inout < sc_uint <BITWIDTH> > pi_A;
	sc_inout < sc_uint <BITWIDTH> > pi_B;
/*	end of modification */

  sc_out <sc_logic> po_A[INSTANCES_FULLADDER];
  sc_out<sc_logic> po_B[INSTANCES_FULLADDER];
  driver(sc_module_name nm);
};

/* software to rtl interface */
class rw_sw2rtl_task_if : virtual public sc_interface{
public:
  struct read_t{
#warning "modified code by Roman"
//	  int a_i;
//	  int b_i;
	  sc_uint<BITWIDTH> a_i;
	  sc_uint<BITWIDTH> b_i;
/*	end of modification */
  };
  struct write_t{
    sc_logic sign_a[INSTANCES_FULLADDER];
    sc_logic sign_b[INSTANCES_FULLADDER];
  };
  virtual read_t read () = 0;
  virtual void write(const write_t*) = 0;
};

class driver_sw2rtl{
  sc_port<rw_sw2rtl_task_if> port_driver;
  void driver_thread();
};


/* prepare transaction recording, software to rtl */
class pipelined_driver_sw2rtl
  : public rw_sw2rtl_task_if,
    public driver {

    scv_tr_stream pipelined_stream;
    scv_tr_stream data_stream;

#warning "modified code by Roman"
//    scv_tr_generator<int> read_gen;
    scv_tr_generator<sc_uint<BITWIDTH>> read_gen;
/*	end of modification */

    scv_tr_generator<sc_logic, sc_logic> write_gen;

public:
    pipelined_driver_sw2rtl (sc_module_name nm) :
      driver(nm),

      pipelined_stream("pipelined_stream", "driver"),
      data_stream("data_stream", "driver"),
      read_gen("read", pipelined_stream, "data"),
      write_gen("write", pipelined_stream, "data")

    {}
    virtual read_t read();
    virtual void write(const write_t* p_req);
  };

#endif
