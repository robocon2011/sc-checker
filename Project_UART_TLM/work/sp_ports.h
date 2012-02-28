/******************************************************************************/
/*                                                                            */
/* Filename:    sp_ports.h                                                    */
/*                                                                            */
/* Author:      Philipp Maroschek                                             */
/*                                                                            */
/* Tools:       Compiles with SystemC 2.2.v0                                  */
/*                                                                            */
/* Project:     SystemC Checker                                               */
/*                                                                            */
/* Topmodule:   ------                                                        */
/* Submodules:  ------                                                        */
/*                                                                            */
/******************************************************************************/

#ifndef SP_PORTS_H
#define SP_PORTS_H

#include <systemc>
#include <scv.h>

#include "global.h"

class fulladr_port
  : public sc_port<sc_signal_inout_if< sc_uint<BITWIDTH> >
    ,2
    ,SC_ONE_OR_MORE_BOUND
    > {
public:
    typedef sc_signal_inout_if< sc_uint<BITWIDTH> > if_type;

    sc_event_finder& fa_value_changed_event() const{
      return *new sc_event_finder_t <if_type> (
          *this,
          &if_type::value_changed_event);
    }
  };

/******************************************************************/

class fa_rtl_port
  : public sc_port<sc_signal_inout_if<sc_logic>
    ,BITWIDTH
    ,SC_ONE_OR_MORE_BOUND
    > {
public:
    typedef sc_signal_inout_if<sc_logic> if_type;

    sc_event_finder& fa_value_changed_event() const{
      return *new sc_event_finder_t <if_type> (
          *this,
          &if_type::value_changed_event);
    }
  };

/******************************************************************/

class fa_rtl_lv_single_port
  : public sc_port<sc_signal_inout_if<sc_lv <BITWIDTH> >
    ,1
    ,SC_ONE_OR_MORE_BOUND
    > {
public:
    typedef sc_signal_inout_if<sc_lv <BITWIDTH> > if_type;

    sc_event_finder& fa_value_changed_event() const{
      return *new sc_event_finder_t <if_type> (
          *this,
          &if_type::value_changed_event);
    }
  };



/******************************************************************/
  class uart_data_port
    : public sc_port<sc_signal_inout_if<sc_logic>
      ,DATABITS
      ,SC_ONE_OR_MORE_BOUND
      > {
  public:
      typedef sc_signal_inout_if<sc_logic> if_type;

      sc_event_finder& fa_value_changed_event() const{
        return *new sc_event_finder_t <if_type> (
            *this,
            &if_type::value_changed_event);
      }
    };

#endif
