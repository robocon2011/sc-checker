/*
 * scoreboard_config.h
 *
 *  Created on: 27.11.2011
 *      Author: ew08b033
 */

#ifndef SCOREBOARD_CONFIG_H_
#define SCOREBOARD_CONFIG_H_

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc>
using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include <fstream>
#include <iostream>

#include <tlm.h>
/*std convinience sockets, which encapsulate the explicite inheritance of interfaces*/
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include "../global.h"
#include "../reference_model/UART_TLM/common.hpp"

enum compareResult { eOK = 0, eMISMATCH, eTIMEOUT_OK, eTIMEOUT_MISMATCH};

struct scoreboard_uart:sc_module
{
public:
	sc_in < sc_uint <DATABITS> > rx_data_stim;
	sc_in < sc_uint <DATABITS> > tx_data_stim;
	sc_in < double > timeout_reference;
	sc_in < unsigned int > testcase_id_reference;
	sc_in < unsigned int > testsequence_id_reference;

	sc_in<bool> tx_empty_out;
	sc_in<bool> rx_empty_out;
	sc_in<sc_uint< DATABITS> > rx_data_out;
	sc_in<sc_uint< DATABITS> > tx_data_out;

	sc_port < handshake_event_if > data_written;

	sc_inout < bool > reference_received;
	sc_inout < bool > testcase_finished;

	std::ofstream outputFile;
	tlm_utils::simple_target_socket< scoreboard_uart > scoreboard_target_socket;

	void store_reference_uart_method ();
	void compare_uart_method ();
	void write_to_file_uart_method ();

private:
	sc_time end_time_buffer;
	sc_time start_time_buffer;
	sc_uint <DATABITS> rx_data_stim_buffer, tx_data_stim_buffer,
					 rx_data_out_buffer, tx_data_out_buffer,
					 rx_data_stim_buffer_old, tx_data_stim_buffer_old;
	sc_time timeout_buffer;
	sc_event event_timeout;

	unsigned int testsequence_id;
	unsigned int testcase_id;


	enum compareResult result;
	packet_uart_data_to_reference data_from_ref;
	sc_event receive_event;

	void my_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);

public:
	SC_HAS_PROCESS(scoreboard_uart);
	scoreboard_uart(sc_module_name nm)
	  : sc_module (nm),
	    rx_data_stim_buffer(0),
	    tx_data_stim_buffer(0),
	    rx_data_out_buffer(0),
	    tx_data_out_buffer(0),
	    timeout_buffer(0, SC_NS),

	    testsequence_id(0),
	    testcase_id(0),
	    start_time_buffer(0, SC_NS),
	    end_time_buffer(0, SC_NS),
	    scoreboard_target_socket("scoreboard_target_socket")
	{
	  SC_METHOD (store_reference_uart_method);
	    sensitive   << receive_event;
	//    			<< rx_data_stim.value_changed()
	//                << tx_data_stim.value_changed()
	//                << testcase_id_reference.value_changed()
	//                << testsequence_id_reference.value_changed();
	  dont_initialize();

	  SC_METHOD (compare_uart_method);
	    sensitive   << data_written
	                << event_timeout;
	  dont_initialize();

	  scoreboard_target_socket.register_b_transport(this, &scoreboard_uart::my_b_transport);

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


#endif /* SCOREBOARD_CONFIG_H_ */
