/*-------------------------------------
 * Project: Fulladder
 * ------------------------------------
 * file: main.cpp
 * ------------------------------------
 * 23.09.2o11: Sollböck, initial version
 *
 *
 * ------------------------------------
*/

#include <systemc.h>
#include "fulladder.h"
#include "testbench.h"

int sc_main (int argc, char *argv[])
{
	// channels
	sc_signal<sc_uint<8>> sig_A;
	sc_signal<sc_uint<8>> sig_B;
	sc_signal<sc_uint<8>> sig_C;
	sc_signal<bool> sig_carry;
	// variables

	// module instances
	testbench testbench_i("testbench_i");
	fulladder fulladder_i("fulladder_i");
	// module port bindings

	testbench_i.po_A(sig_A);
	testbench_i.po_B(sig_B);
	testbench_i.pi_C(sig_C);
	testbench_i.pi_carry(sig_carry);

	fulladder_i.pi_A(sig_A);
	fulladder_i.pi_B(sig_B);
	fulladder_i.po_C(sig_C);
	fulladder_i.po_carry(sig_carry);

	// Time/resulution setup

	// Start simulation
	sc_start();

	if (! sc_end_of_simulation_invoked()) sc_stop(); //< invoke end_of_simulation

	return 0;
}