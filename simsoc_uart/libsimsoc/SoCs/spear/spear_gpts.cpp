//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "spear_gpts.hpp"
#include "libsimsoc/display.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

/*
 * Constructor and destructor
 */

GPTimers::GPTimers(sc_module_name name) :
  Module(name)
{
  rw_port(*this); //bind the target port

  SC_METHOD(compute0);
  dont_initialize();
  sensitive<<channels[0].timeout_event;

  SC_METHOD(compute1);
  dont_initialize();
  sensitive<<channels[1].timeout_event;

  debug() <<"General Purpose Timers constructor"<<endl;
}

GPTimers::~GPTimers() {
  debug() <<"General Purpose Timers destructed"<<endl;
}

uint16_t GPTimers::read_half(uint32_t addr) {
	uint32_t select=(addr & CHANNEL_SELECT)?1:0;
	uint32_t offset_addr = addr & CHANNEL_OFFSET_MASK;
	switch (offset_addr) {
	  case CONTROL_OFFSET:
	    return channels[select].control;
	  case STATUS_INT_ACK_OFFSET:
	    return channels[select].status_int_ack;
	  case COMPARE_OFFSET:
	    return channels[select].compare;
	  case COUNT_OFFSET:
		  timer_update(&channels[select],elapse_time);	//for speed now. used for the delay check
		  return channels[select].count;
	  case REDG_CAPT_OFFSET:
	    return channels[select].redg_capt;
	  case FEDG_CAPT_OFFSET:
	    return channels[select].fedg_capt;
	  default:
	     error() <<"read half at address " <<hex <<addr <<endl;
	      exit(1);
	   }
}

void GPTimers::write_half(uint32_t addr, uint16_t data) {
	uint32_t select=(addr & CHANNEL_SELECT)?1:0;
	uint32_t offset_addr = addr & CHANNEL_OFFSET_MASK;
	switch (offset_addr) {
	  case CONTROL_OFFSET:
		  channels[select].control=data;
	    if (channels[select].control & CONTROL_ENABLE) {
	    	channels[select].redg_capt=0;
	    	channels[select].fedg_capt=0;
	    	channels[select].count=0;

    		proc_timeout(&channels[select]);
	    }
	    break;
	  case STATUS_INT_ACK_OFFSET:
		  channels[select].status_int_ack=data & 0x7;	// write: bits[15:3] should be zero
	     clean_interrupt_source(&channels[select]);
	    break;
	  case COMPARE_OFFSET:
		  channels[select].compare=data;
		  if (channels[select].control & CONTROL_ENABLE) {
			  	    		proc_timeout(&channels[select]);
		  }
	    break;
	  case COUNT_OFFSET:
	    error()<<"write to read only count1 register"<<endl;
	    exit(1);
	  case REDG_CAPT_OFFSET:
	    error()<<"write to read only capture re1 register"<<endl;
	    exit(1);
	  case FEDG_CAPT_OFFSET:
	    error()<<"write to read only capture fe1 register"<<endl;
	    exit(1);
	  default:
	    error() <<"write word at address " <<hex <<addr <<endl;
	    exit(1);
	  }
}

void GPTimers::rasing_edge_capture(timer_channel *timer)
{
	timer->redg_capt=timer->count;
	timer->status_int_ack |=  STATUS_REDGE;
	if(timer->control & CONTROL_REDGE_INT )
	{
		timer->it_port=true;
	}
}

void GPTimers::failing_edge_capture(timer_channel *timer)
{
	timer->fedg_capt=timer->count;
	timer->status_int_ack |=  STATUS_FEDGE;
	if(timer->control & CONTROL_FEDGE_INT )
	{
		timer->it_port=true;
	}
}

void GPTimers::timer_reload(timer_channel *timer)
{
	  //todo:counter clear and restarts
	  timer->count=0;
}

void GPTimers::timer_stop(timer_channel *timer)
{
	//count stopped and GPT is disabled
	timer->control &= ~CONTROL_ENABLE; //GPT is disabled
}

void GPTimers::timer_update(timer_channel *timer,uint32_t elapse_time)
{
	//Ignore disabled timer
	if(timer->control & CONTROL_ENABLE==0)
		return;

	timer->count+=elapse_time;	//the timeout will be controled by sc_event so just add the count here
}

void GPTimers::clean_interrupt_source(timer_channel* timer)
{
	if(timer->status_int_ack & STATUS_REDGE || timer->status_int_ack & STATUS_FEDGE || timer->status_int_ack & STATUS_MATCH)
	{
		timer->it_port=false;
	}
}

void GPTimers::setup_interrupt_source(timer_channel *timer)
{
	if (timer->control & CONTROL_MATCH_INT) {
			//an interrupt source is activated
			timer->it_port=true;
			timer->status_int_ack |=STATUS_MATCH; //set MATCH bit

			switch (timer->control & CONTROL_MODE) {
			case SINGLE_SHOT_MODE:
				//the counter is stopped and the GPT is disabled
				timer_stop(timer);
				break;

			case AUTO_RELOAD_MODE:
				//the counter is automatically clear and then it restarts incrementing
				timer_reload(timer);
				break;
			}
		} else {
			timer_update(timer, elapse_time);
		}
	proc_timeout(timer);
}

void GPTimers::compute0()
{
	info()<<"timer0 interrupt at time "<<sc_time_stamp()<<endl;
	setup_interrupt_source(&channels[0]);
}

void GPTimers::compute1()
{
	info()<<"timer1 interrupt at time "<<sc_time_stamp()<<endl;
	setup_interrupt_source(&channels[1]);
}

void GPTimers::proc_timeout(timer_channel *timer)
{
	timer->timeout_event.cancel();
	if (timer->control & CONTROL_MATCH_INT) {
		timer->timeout_event.notify(timer->compare*10,SC_NS);
	}
}

} // namespace simsoc
