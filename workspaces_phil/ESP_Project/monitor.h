/******************************************************************************/
/*                                                                            */
/* Filename:   monitor.h                                                      */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#ifndef MONITOR_H
#define MONITOR_

#include "config.h"
#include <systemc.h>
#include <scv.h>

/* rtl to software interface */
class rw_rtl2sw_task_if : virtual public sc_interface{
public:
  struct read_t{
    sc_logic sign_a[INSTANCES_FULLADDER];
    sc_logic sign_b[INSTANCES_FULLADDER];
  };
  struct write_t{
    int a_i;
    int b_i;
  };
  virtual read_t read () = 0;
  virtual void write(const write_t*) = 0;
};


SC_MODULE(monitor)
{
public:

  /* port declarations */
  sc_inout <int> po_mon_A;
  sc_inout <int> po_mon_B;
  sc_in <sc_logic> pi_mon_A[INSTANCES_FULLADDER];
  sc_in <sc_logic> pi_mon_B[INSTANCES_FULLADDER];

  SC_CTOR(monitor)
  : po_mon_A("po_mon_A"),
    po_mon_B("po_mon_B")/*,
    po_mon_A("po_mon_A"),
    po_mon_B[INSTANCES_FULLADDER]("po_mon_B") */
    {}
};

SC_MODULE(monitor_rtl2sw)
{
public:

  sc_port<rw_rtl2sw_task_if> monitor_driver;

  SC_HAS_PROCESS(monitor_rtl2sw);
  monitor_rtl2sw (sc_module_name nm){
    SC_METHOD(monitor_thread)
        sensitive << monitor_driver;
  }

  void monitor_thread();
};

/* prepare transaction recording, software to rtl */
class pipelined_monitor_rtl2sw
  : public rw_rtl2sw_task_if,
    public monitor {

    scv_tr_stream pipelined_stream;
    scv_tr_stream data_stream;

    scv_tr_generator<sc_logic[INSTANCES_FULLADDER]> read_gen;
    scv_tr_generator<int> write_gen;


public:
    pipelined_monitor_rtl2sw (sc_module_name nm) :
      monitor(nm),

      pipelined_stream("pipelined_stream", "driver"),
      data_stream("data_stream", "driver"),
      read_gen("read", pipelined_stream, "data"),
      write_gen("write", pipelined_stream, "data")

    {}
    virtual read_t read();
    virtual void write(const write_t* p_req);
  };

#endif
