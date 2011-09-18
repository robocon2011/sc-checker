#ifndef EA_INTERRUPT_H
#define EA_INTERRUPT_H
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// DESCRIPTION
//   This is a custom primitive channel that supports the notion of
//   sending events between modules. To send an event, simply invoke
//   notify with the appropriate arguments. The receiving modules should
//   wait on the default event.
//
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <systemc.h>
using namespace sc_core;

#include "ea_interrupt_evt_if.h"
#include "ea_interrupt_gen_if.h"

struct ea_interrupt
: public sc_prim_channel
, public sc_signal<bool>
//, public sc_signal_inout_if<bool>
//, public ea_interrupt_evt_if
, public ea_interrupt_gen_if
{
	sc_signal<bool> m_signal;

		explicit ea_interrupt() 
  : sc_prim_channel(sc_gen_unique_name("ea_interrupt")),m_signal() {}
  
  explicit ea_interrupt(sc_module_name nm) 
  : sc_prim_channel(nm),m_signal() {}
  
  void notify()
	{ 
		//m_interrupt.notify(); 
		m_signal.write(true);
	}
  void notify(sc_time t) 
	{ 
		//m_interrupt.notify(t);
		m_signal.write(true);

	}
	void clear()
	{
		m_signal.write(false);
	}
  const sc_event& default_event() const
	{ 
		//return m_interrupt;
		return m_signal.posedge_event();
	}

private:
  sc_event m_interrupt;

  // Copy constructor so compiler won't create one
  ea_interrupt( const ea_interrupt& );
};

#endif