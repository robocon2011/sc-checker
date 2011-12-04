/*
 * develop_main.cpp
 *
 *  Created on: 06.11.2011
 *      Author: ew08b033
 */

#include <systemc>
#include <scv.h>
#include "stimulator/stimulator_config.h"
#include "scoreboard/scoreboard_config.h"
//#include "dut/fulladder/fulladder_rtl.h"

SC_MODULE (testcontroller)
{
public:
	sc_inout < bool > next_sample_to_reference;
	sc_in < bool > reference_received;
	sc_inout <bool > next_sample_to_dut;
	sc_in < bool > testcase_finished;
	sc_in < bool > all_sequences_finished;

	SC_CTOR(testcontroller)
	{
		SC_THREAD(testcontroller_thread);
	}

	void testcontroller_thread ()
	{
		while ( !all_sequences_finished.read() )
		{
			next_sample_to_reference.write(true);

			wait(reference_received.posedge_event());

			next_sample_to_reference.write(false);
			next_sample_to_dut.write(true);

			wait(testcase_finished.posedge_event());
			next_sample_to_dut.write(false);
		}
	}
};

SC_MODULE (reference_model)
{
public:
	sc_in < sc_uint<BITWIDTH> > input_A_stimulator;
	sc_in < sc_uint<BITWIDTH> > input_B_stimulator;
	sc_in < bool > carry_in_stimulator;
	sc_in < double > timeout;
	sc_in < unsigned int > testsequence_id;
	sc_in < unsigned int > testcase_id;

	sc_inout < sc_uint <BITWIDTH> > output_scoreboard;
	sc_inout < bool > output_carry_scoreboard;
	sc_inout < double > timeout_scoreboard;
	sc_inout < unsigned int > testcase_id_scoreboard;
	sc_inout < unsigned int > testsequence_id_scoreboard;

	SC_CTOR(reference_model)
	{
		SC_METHOD(reference_method);
		sensitive << input_A_stimulator.value_changed() << input_B_stimulator.value_changed();
	}

	void reference_method ()
	{
		input_A = input_A_stimulator.read();
		input_B = input_B_stimulator.read();
		carry_in = carry_in_stimulator.read();

		output = input_A + input_B + (carry_in ? 1 : 0) ;
		carry_out = ( output < input_A ) || ( output < input_B) ;

		output_scoreboard.write(output);
		output_carry_scoreboard.write(carry_out);
		timeout_scoreboard.write(timeout);
		testsequence_id_scoreboard.write(testsequence_id.read());
		testcase_id_scoreboard.write(testcase_id.read());
	}

private:
	sc_uint <BITWIDTH> input_A;
	sc_uint <BITWIDTH> input_B;
	bool carry_in;

	sc_uint <BITWIDTH> output;
	bool carry_out;
};

SC_MODULE(dut_dummy)
{
	sc_in < sc_uint<BITWIDTH> > output_ref;
	sc_in < bool > carry_out_ref;
	sc_inout < sc_uint<BITWIDTH> > output_mon;
	sc_inout < bool > carry_out_mon;

	SC_CTOR(dut_dummy)
	{
		SC_THREAD(dut_delay);
	}

	void dut_delay (void)
	{
		while(1)
		{
			wait(output_ref.value_changed_event());
			wait(1,SC_NS);
			output_mon.write(output_ref.read());
			carry_out_mon.write(carry_out_ref.read());
		}
	}
};

int sc_main (int argc, char *argv[])
{
	//fulladder_cascade i_fulladder("i_fulladder");

	stimulator_m i_stimulator("i_stimulator");
	testcontroller i_testcontroller("i_testcontroller");
	reference_model i_reference_model ("i_reference_model");
	dut_dummy i_dut_dummy ("i_dut_dummy");
	scoreboard_m i_scoreboard ("i_scoreboard");

	sc_signal <sc_uint<BITWIDTH> > signal_A_reference;
	sc_signal <sc_uint<BITWIDTH> > signal_B_reference;
	sc_signal <bool> signal_carry_in_reference;
	sc_signal < double > signal_timeout;
	sc_signal < unsigned int > signal_testcase_id;
	sc_signal < unsigned int > signal_testsequence_id;

	sc_signal <sc_uint<BITWIDTH> > signal_A_dut;
	sc_signal <sc_uint<BITWIDTH> > signal_B_dut;
	sc_signal <bool> signal_carry_in_dut;

	sc_signal <sc_uint<BITWIDTH> > signal_output_reference;
	sc_signal <bool> signal_carry_out_reference;
	sc_signal < double > signal_timeout_scoreboard;
	sc_signal < unsigned int > signal_testcase_id_scoreboard;
	sc_signal < unsigned int > signal_testsequence_id_scoreboard;

	sc_signal <sc_uint<BITWIDTH> > signal_output;
	sc_signal <bool> signal_carry_out;


	sc_signal <bool> signal_next_sample_to_reference;
	sc_signal <bool> signal_next_sample_to_dut;
	sc_signal <bool> signal_reference_received;
	sc_signal <bool> signal_testcase_finished;
	sc_signal <bool> signal_all_testsequences_finished;

	i_testcontroller.next_sample_to_reference(signal_next_sample_to_reference);
	i_testcontroller.reference_received(signal_reference_received);
	i_testcontroller.next_sample_to_dut(signal_next_sample_to_dut);
	i_testcontroller.testcase_finished(signal_testcase_finished);
	i_testcontroller.all_sequences_finished(signal_all_testsequences_finished);


	i_stimulator.input_A_reference(signal_A_reference);
	i_stimulator.input_B_reference(signal_B_reference);
	i_stimulator.carry_in_reference(signal_carry_in_reference);
	i_stimulator.timeout(signal_timeout);
	i_stimulator.testsequence_id(signal_testsequence_id);
	i_stimulator.testcase_id(signal_testcase_id);
	i_stimulator.input_A(signal_A_dut);
	i_stimulator.input_B(signal_B_dut);
	i_stimulator.carry_in(signal_carry_in_dut);
	i_stimulator.next_sample_to_reference(signal_next_sample_to_reference);
	i_stimulator.next_sample_to_dut(signal_next_sample_to_dut);
	i_stimulator.testsequences_finished(signal_all_testsequences_finished);

	i_reference_model.input_A_stimulator(signal_A_reference);
	i_reference_model.input_B_stimulator(signal_B_reference);
	i_reference_model.carry_in_stimulator (signal_carry_in_reference);
	i_reference_model.timeout(signal_timeout);
	i_reference_model.testcase_id(signal_testcase_id);
	i_reference_model.testsequence_id(signal_testsequence_id);
	i_reference_model.output_scoreboard(signal_output_reference);
	i_reference_model.output_carry_scoreboard(signal_carry_out_reference);
	i_reference_model.timeout_scoreboard(signal_timeout_scoreboard);
	i_reference_model.testcase_id_scoreboard(signal_testcase_id_scoreboard);
	i_reference_model.testsequence_id_scoreboard(signal_testsequence_id_scoreboard);

	i_dut_dummy.output_ref(signal_output_reference);
	i_dut_dummy.carry_out_ref(signal_carry_out_reference);
	i_dut_dummy.output_mon(signal_output);
	i_dut_dummy.carry_out_mon(signal_carry_out);

	i_scoreboard.output_reference(signal_output_reference);
	i_scoreboard.output_carry_reference(signal_carry_out_reference);
	i_scoreboard.timeout_reference(signal_timeout_scoreboard);
	i_scoreboard.testcase_id_reference(signal_testcase_id_scoreboard);
	i_scoreboard.testsequence_id_reference(signal_testsequence_id_scoreboard);
	i_scoreboard.output_monitor(signal_output);
	i_scoreboard.output_carry_monitor(signal_carry_out);
	i_scoreboard.reference_received(signal_reference_received);
	i_scoreboard.testcase_finished(signal_testcase_finished);


	sc_start();

	return 0;
}
