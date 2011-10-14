/*
 * filename: main.cpp
 *
 * Main routine for test of SIMSOC uart_16550
 */

#include <systemc.h>
#include "libsimsoc/components/uart_16550.hpp"

using namespace simsoc;

int sc_main (int argc, char *argv[])
{
	// channels

	// variables

	// module instances
	Uart16550 i_uart = Uart16550("uart", false);
	// module port bindings


	// Time/resulution setup

	// Start simulation
	sc_start();

	if (! sc_end_of_simulation_invoked()) sc_stop(); //< invoke end_of_simulation

	return 0;
}
