#ifndef TESTBENCH_H
#define TESTBENCH_H

/*-------------------------------------
 * Project: Fulladder
 * ------------------------------------
 * file: testbench.h
 * ------------------------------------
 * 23.09.2o11: Sollböck, initial version
 *
 *
 * ------------------------------------
*/
#include <systemc.h>
#include <scv.h>
#include "testvalues_ext.h"
#include "testvalues_constraint.h"

SC_MODULE(testbench)
{

	sc_port<sc_signal_inout_if<sc_uint<8>> > po_A;
	sc_port<sc_signal_inout_if<sc_uint<8>> >	po_B;
	sc_port<sc_signal_in_if<sc_uint<8>> > pi_C;
	sc_port<sc_signal_in_if<bool> > pi_carry;
		
	scv_smart_ptr<testvalues> pTest;
	testvalues_constraint constrValues;

	testbench(sc_module_name nm);

	void testbench_thread ();
	
};

#endif
