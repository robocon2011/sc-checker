/******************************************************************************/
/*                                                                            */
/* Filename:    clock_gen.cpp                                                 */
/*                                                                            */
/* Author:      Philipp Maroschek                                             */
/*                                                                            */
/* Tools:       Compiles with SystemC 2.2.v0                                  */
/*                                                                            */
/* Project:     SystemC Checker                                               */
/*                                                                            */
/* Topmodule:   Driver                                                        */
/* Submodules:  Clock_gen                                                     */
/*                                                                            */
/******************************************************************************/

#ifndef CLOCK_GEN_H
#define CLOCK_GEN_H

#include "../global.h"
#include <systemc.h>
#include <scv.h>

SC_MODULE(clock_gen){

  /* port decalartions */
  sc_out<sc_logic> clkout_log;

  sc_clock clk;

  SC_CTOR(clock_gen)
  : clk("clk", sc_time(100, SC_PS))
  {
    SC_METHOD(clk_method);
    sensitive << clk.posedge_event()
              << clk.negedge_event();
  }

  /* method to derive a sc_logic clock from sc_clock */
  void clk_method(){
    sc_logic dummy;
    dummy = ((clk.read() == true) ? '1' : '0');
    clkout_log->write(dummy);
  }

  /* further clocks could be derived with this kind of method */
};

#endif
