/*
 * scoreboard_config_uart.h
 *
 *  Created on: 27.11.2011
 *      Author: ew08b033
 */

#ifndef SCOREBOARD_CONFIG_UART_H_
#define SCOREBOARD_CONFIG_UART_H_

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc>
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include <fstream>
#include <iostream>

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include "../global.h"
#include "../stimulator/stimulator_config_uart_tlm.h"

enum compareResult { eOK = 0, eMISMATCH, eTIMEOUT_OK, eTIMEOUT_MISMATCH};

struct scoreboard_uart:sc_module
{
public:
	tlm_utils::simple_target_socket< scoreboard_uart > ReferenceToScoreboard_target_socket;
	tlm_utils::simple_target_socket< scoreboard_uart > StimulatorToScoreboard_target_socket;

	sc_in<bool> tx_empty_out;
	sc_in<bool> rx_empty_out;
	sc_in<sc_uint< DATABITS> > rx_data_out;
	sc_in<sc_uint< DATABITS> > tx_data_out;

	sc_port < handshake_event_if > data_written;

	sc_inout < bool > reference_received;
	sc_inout < bool > testcase_finished;

	std::ofstream outputFile;

	void store_reference_uart_method ();
	void compare_uart_method ();
	void write_to_file_uart_method ();

private:
	sc_uint <DATABITS> rx_data_ref_buffer, tx_data_ref_buffer,
					 rx_data_out_buffer, tx_data_out_buffer,
					 rx_data_ref_buffer_old, tx_data_ref_buffer_old;
	sc_time timeout_buffer;
	sc_event event_timeout;

	unsigned int testcase_id, testsequence_id;
	sc_time end_time_buffer, start_time_buffer;


	enum compareResult result;
	uint32_t data_from_ref[MEMSIZE_UART];
	struct data_to_scoreboard_t data_from_stim;
	sc_event receive_event;

	void ReferenceToScoreboard_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);
	void StimulatorToScoreboard_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);

public:
	SC_HAS_PROCESS(scoreboard_uart);
	scoreboard_uart(sc_module_name nm)
	  : sc_module (nm),
	    ReferenceToScoreboard_target_socket("ReferenceToScoreboard_target_socket"),
	    StimulatorToScoreboard_target_socket("StimulatorToScoreboard_target_socket"),
	    rx_data_ref_buffer(0),
	    tx_data_ref_buffer(0),
	    rx_data_out_buffer(0),
	    tx_data_out_buffer(0),
	    timeout_buffer(0, SC_NS),
	    testcase_id(0),
	    testsequence_id(0),
	    end_time_buffer(0, SC_NS),
	    start_time_buffer(0, SC_NS)
	{
	  SC_METHOD (store_reference_uart_method);
	    sensitive   << receive_event;

	  dont_initialize();

	  SC_METHOD (compare_uart_method);
	    sensitive   << data_written
	                << event_timeout;
	  dont_initialize();

	  ReferenceToScoreboard_target_socket.register_b_transport(this, &scoreboard_uart::ReferenceToScoreboard_b_transport);
	  StimulatorToScoreboard_target_socket.register_b_transport(this, &scoreboard_uart::StimulatorToScoreboard_b_transport);

	  outputFile.open("scoreboard.txt");
	  if (outputFile.is_open())
	  {
	    outputFile << "testsequence_id; "
	        "testcase_id; "
	        "result; "
	        "rx_data_stim; "
	        "tx_data_stim; "
	        "rx_data_out; "
	        "tx_data_out; "
	        "timeout; "
	        "start_time; "
	        "end_time" << endl;
	  }
	  else cout << "file open error" << endl;

	  outputFile.close();
	}
};


#endif /* SCOREBOARD_CONFIG_UART_H_ */
