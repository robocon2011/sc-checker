//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See stim.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#include <systemc>
using namespace sc_core;
using std::cout;
using std::endl;
#include "stim.h"

void stim::stim_thread(void) 
{
  wait(2,SC_NS);  // Get off zero
  for (unsigned i=0; i!=5; i++) 
  {
    cout << "INFO: " << name() << " Sending event at " << sc_time_stamp() << endl;
    irq_op->notify(SC_ZERO_TIME);
		wait(5,SC_NS);
		irq_op->clear();
		wait(SC_ZERO_TIME);
  }//endfor
  
}//end stim::stim_thread