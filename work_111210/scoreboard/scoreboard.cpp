/*
 * scoreboard.cpp
 *
 *  Created on: 27.11.2011
 *      Author: ew08b033
 */

#include <scv.h>
#include <systemc>
#include "scoreboard_config.h"


SC_HAS_PROCESS(scoreboard_m);
scoreboard_m::scoreboard_m(sc_module_name nm)
	: sc_module (nm),
	  output_reference_buffer(0),
	  output_carry_reference_buffer(false),
	  timeout_buffer(0, SC_NS),
	  output_monitor_buffer(0),
	  output_carry_monitor_buffer(false),
	  testsequence_id(0),
	  testcase_id(0),
	  start_time_buffer(0, SC_NS),
	  end_time_buffer(0, SC_NS)
{
	SC_METHOD (store_reference_method);
		sensitive 	<< output_reference.value_changed() << output_carry_reference.value_changed();
	dont_initialize();

	SC_METHOD (compare_method);
		sensitive 	<< output_monitor.value_changed() << output_carry_monitor.value_changed();
	dont_initialize();

	outputFile.open("scoreboard.txt");
	if (outputFile.is_open())
	{
		cout << "file successfully opened" << endl;
		outputFile << "testsequence_id; "
				"testcase_id; "
				"result; "
				"output_reference; "
				"output_carry_reference; "
				"output_monitor; "
				"output_carry_monitor; "
				"timeout; "
				"start_time; "
				"end_time" << endl;
	}
	else cout << "file open error" << endl;

	outputFile.close();

}

void scoreboard_m::store_reference_method()
{
	output_reference_buffer = output_reference.read();
	output_carry_reference_buffer = output_carry_reference.read();
	timeout_buffer = sc_time(timeout_reference.read(),SC_SEC);
	testcase_id = testcase_id_reference.read();
	testsequence_id = testsequence_id_reference.read();

	testcase_finished.write(false);
	reference_received.write(true);

	start_time_buffer = sc_time_stamp();
}

void scoreboard_m::compare_method()
{
	output_monitor_buffer = output_monitor.read();
	output_carry_monitor_buffer = output_carry_monitor.read();
	end_time_buffer = sc_time_stamp();

	if (	output_monitor_buffer == output_reference_buffer &&
			output_carry_monitor_buffer == output_carry_reference_buffer)
	{
		if ( (end_time_buffer - start_time_buffer) < timeout_buffer	)
		{
			result = eOK;
		}
		else
		{
			result = eTIMEOUT;
		}
	}
	else
	{
		result = eMISMATCH;
	}

	write_to_file();

	reference_received.write(false);
	testcase_finished.write(true);
}

void scoreboard_m::write_to_file()
{

	outputFile.open("scoreboard.txt", fstream::ate | fstream::app);
	if (outputFile.is_open())
	{
		cout << "file successfully opened" << endl;

		outputFile << testsequence_id 			<< "; " <<
				testcase_id 					<< "; "	<<
				result							<< "; " <<
				output_reference_buffer  		<< "; "	<<
				output_carry_reference_buffer  	<< "; "	<<
				output_monitor_buffer 			<< "; "	<<
				output_carry_monitor_buffer  	<< "; "	<<
				timeout_buffer					<< "; " <<
				start_time_buffer  				<< "; "	<<
				end_time_buffer 				<< endl;
	}
	else cout << "file open error" << endl;

	outputFile.close();
}
