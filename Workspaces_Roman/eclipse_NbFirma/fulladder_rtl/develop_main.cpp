/*
 * develop_main.cpp
 *
 *  Created on: 06.11.2011
 *      Author: ew08b033
 */

#include <systemc>
#include <scv.h>
#include "stimulator/stimulator_config.h"
#include "dut/fulladder/fulladder_rtl.h"

#define _DEBUG


SC_MODULE (tb_stimulator)
{
public:
	sc_in < sc_uint<BITWIDTH> > stim_input_A;
	sc_in < sc_uint<BITWIDTH> > stim_input_B;
	sc_inout < bool > nextSample;
	sc_in < bool > testsequences_finished;

	SC_CTOR (tb_stimulator)
	{
		SC_METHOD (tb_stimulator_print_method)
				sensitive << stim_input_A.value_changed() << stim_input_B.value_changed();
		dont_initialize();

		SC_THREAD(tb_nextSample_thread);
	}

	void tb_nextSample_thread()
	{
		while (testsequences_finished.read() != true)
		{
			nextSample.write(!nextSample);
			wait(stim_input_A.value_changed_event() | stim_input_B.value_changed_event());
		}
	}

	void tb_stimulator_print_method ()
	{
		cout << "input_A: " << stim_input_A << endl;
		cout << "input_B: " << stim_input_B << endl;
	}
};

int sc_main (int argc, char *argv[])
{
	//fulladder_cascade i_fulladder("i_fulladder");
	stimulator_m i_stimulator("i_stimulator");
	tb_stimulator i_tb_stimulator("i_tb_stimulator");

	sc_signal <sc_uint<BITWIDTH> > signal_A;
	sc_signal <sc_uint<BITWIDTH> > signal_B;
	sc_signal <bool> signal_nextSample;
	sc_signal <bool> signal_test_finished;


	i_tb_stimulator.stim_input_A(signal_A);
	i_tb_stimulator.stim_input_B(signal_B);
	i_tb_stimulator.nextSample(signal_nextSample);
	i_tb_stimulator.testsequences_finished(signal_test_finished);

	i_stimulator.input_A(signal_A);
	i_stimulator.input_B(signal_B);
	i_stimulator.nextSample(signal_nextSample);
	i_stimulator.testsequences_finished(signal_test_finished);


	sc_start();

	return 0;
}
