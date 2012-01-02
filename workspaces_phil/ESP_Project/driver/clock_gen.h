/******************************************************************************/
/*                                                                            */
/* Filename:   clock_gen.cpp                                                  */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#ifndef CLOCK_GEN_H
#define CLOCK_GEN_H

#include "../global.h"
#include <systemc.h>
#include <scv.h>

SC_MODULE(clock_gen){
  sc_export<sc_signal_inout_if<bool> > clkout;
  sc_port<sc_signal_inout_if<bool> >  clkdiv_half;

  sc_clock clk;

  SC_CTOR(clock_gen)
  : clk("clk", sc_time(10, SC_NS)){
    SC_METHOD(clk_method);
    sensitive << clk.posedge_event();
    clkout(clk);
  }
  void clk_method(){
    clkdiv_half->write(!clkdiv_half->read());
  }
};

#endif
