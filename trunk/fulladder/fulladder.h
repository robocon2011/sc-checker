#ifndef FULLADDER_H
#define FULLADDER_

/*-------------------------------------
 * Project: Fulladder
 * ------------------------------------
 * file: fulladder.h
 * ------------------------------------
 * 23.09.2o11: Sollböck, initial version
 *
 *
 * ------------------------------------
*/


#include <systemc.h>

SC_MODULE(fulladder)
{
	sc_port< sc_signal_in_if < sc_uint<8> > > pi_A;
	sc_port< sc_signal_in_if < sc_uint<8> > > pi_B;
	sc_port< sc_signal_inout_if < sc_uint<8> > > po_C;
	sc_port<sc_signal_inout_if<bool> > po_carry;

	void fulladder_method ();

	fulladder(sc_module_name nm);
};

#endif
