//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef SPEAR_GPTS_HPP_
#define SPEAR_GPTS_HPP_

/*
 * TLM Model for SPEAR Plus General Pourpose Timers
 * This module is incomplete
 * */
#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/interfaces/tlm_signal.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

const uint32_t elapse_time=100;		//for the fake couter increasement

class GPTimers:public Module,public RW_Target{
public:
  //register offset
  static const uint32_t CONTROL_OFFSET =0x0;
  static const uint32_t STATUS_INT_ACK_OFFSET = 0x4;
  static const uint32_t COMPARE_OFFSET =0x8;
  static const uint32_t COUNT_OFFSET = 0xC;
  static const uint32_t REDG_CAPT_OFFSET = 0x10;
  static const uint32_t FEDG_CAPT_OFFSET = 0x14;

  //channel register
  struct timer_channel{
    uint16_t control;				//Control Register of 1st timer in the couple
    uint16_t status_int_ack;		//Status Register of 1st timer
    uint16_t compare;				//Compare Register of 1st timer
    uint16_t count;					//Count Register of 1st timer
    uint16_t redg_capt;				//Rising Edge Capture Register of 1st timer
    uint16_t fedg_capt;				//Falling Edge Capture Register of 1st timer
    SignalInitiatorPort<bool> it_port;	//iterrupt port
    sc_core::sc_event timeout_event;

    timer_channel():
      control(0)
      , status_int_ack(0)
      , compare(0xffff)
      , count(0)
      , redg_capt(0)
      , fedg_capt(0)
    {}
    void channel_reset()
    {
      control=0;
      status_int_ack=0;
      compare=0xffff;
      count=0;
      redg_capt=0;
      fedg_capt=0;
    };
  }channels[2];

  //mask for the channels
  static const uint16_t CHANNEL_SELECT	= 0x100;
  static const uint16_t CHANNEL_OFFSET_MASK = 0x1f;

  //mask for TIMER_CONTROL Register
  static const uint16_t CONTROL_REDGE_INT= 1<<10;		//bit[10] enables interruption on a rising edge capture
  static const uint16_t CONTROL_FEDGE_INT= 1<<9;		//bit[9] enables interruption on a falling edge capture
  static const uint16_t CONTROL_MATCH_INT = 1<<8;		//bit[8] enables interruption when comparator matches
  static const uint16_t CONTROL_CAPTURE = 0xC0;		//bits[7:6]
  static const uint16_t CONTROL_ENABLE = 1<<5; 		//bit[5]
  static const uint16_t CONTROL_MODE = 1<<4;			//bit[4]
  static const uint16_t CONTROL_PRESCALER =0xf;		//bit[3:0]
  //values
  enum timer_mode
    {
      AUTO_RELOAD_MODE=0,
      SINGLE_SHOT_MODE
    };
  enum capture_mode{
    NO_CAPTURE=0,
    CAPTURE_IN_RISING_EDGE,
    CAPTURE_IN_FALLING_EDGE,
    CAPTURE_IN_BITH_EDGE
  };
  enum prescaler_div{
    TIMER_DIV1 = 0,
    TIMER_DIV2,
    TIMER_DIV4,
    TIMER_DIV8,
    TIMER_DIV16,
    TIMER_DIV32,
    TIMER_DIV64,
    TIMER_DIV128,
    TIMER_DIV256
  };

  //mask for TIMER_STATUS_INT_ACK
  static const uint16_t STATUS_REDGE = 1<<2;	//reading as 1 means a rising edge has been detected and a interrupt is raised
  //writing as 1 means the interrupt source is cleared
  static const uint16_t STATUS_FEDGE = 1<<1; 	//failing edge capture, as above
  static const uint16_t STATUS_MATCH = 1<<0; 		//match status,as above

  //ports
  RW_TargetPort rw_port;
  SC_HAS_PROCESS(GPTimers);


  GPTimers(sc_core::sc_module_name name);
  ~GPTimers();

  // TLM read writes
  uint16_t read_half(uint32_t addr);
  void write_half(uint32_t addr, uint16_t data);

  void trans_read_data(PayLoad &pl)
  {
    uint32_t addr = pl.get_address();
    switch (pl.get_data_length()) {
    case 4:
      //warning() <<"read access of size 4 converted to size 1" <<std::endl;
    case 2: {
      uint16_t data = read_half(addr);
      *(uint16_t*)(pl.get_data_ptr()) = data;
    } break;
    default:
      error() <<": read data method is not implemented for data_length = "
              <<pl.get_data_length() <<std::endl;
      exit(1);
    }
  };

  void trans_write_data(PayLoad &pl)
  {
    uint32_t addr = pl.get_address();

    switch (pl.get_data_length()) {
    case 4:
      //warning() <<"write access of size 4 converted to size 1" <<std::endl;
    case 2: {
      uint16_t data = *(uint16_t*)(pl.get_data_ptr());
      write_half(addr,data);
    } break;
    default:
      error() <<": write data  method is not implemented for data_length = "
              <<pl.get_data_length() <<std::endl;
      exit(1);
    }
  };



  void rasing_edge_capture(timer_channel *timer);
  void failing_edge_capture(timer_channel *timer);

  void timer_reload(timer_channel *timer);
  void timer_stop(timer_channel *timer);
  void timer_update(timer_channel *timer,uint32_t elapse_time);

  void setup_interrupt_source(timer_channel *timer);
  void clean_interrupt_source(timer_channel *timer);

  void compute0();
  void compute1();
  void proc_timeout(timer_channel *timer);
};

} // namespace simsoc

#endif /*SPEAR_GPTS_HPP_*/
