/*
 * 	Filename:	scoreboard_uart.cpp
 *
 * 	Version:	---
 *
 *  Created on:	2012/02/28
 *
 *  Author: 	Roman SOLLBOECK
 *
 *  Project:	SystemC Checker
 *  Submodule:	Scoreboard
 *
 *  purpose:	Scoreboard configuration for testing of UART RTL Design
 *
 *  History:	2012/02/28: first executable version implemented
 *  			2012/03/01: comments added
 */

/*	define needed for TLM Simulation */
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <scv.h>
#include <systemc>
#include "scoreboard_config_uart.h"

/*
 * **************************************************************
 *
 * functionname:	store_reference_uart_method
 * purpose:			Method for storage of Reference values and
 * 					signaling to testcontroller
 * parameters:		none
 * returnvalue:		none
 *
 * **************************************************************
 */
void scoreboard_uart::store_reference_uart_method()
{
	/*	read RX-data from UART memory */
	rx_data_ref_buffer = data_from_ref[UART_BYTE_OFFS_RX_REG / sizeof(uint32_t)];

	/*	read TX-data from UART memory */
	tx_data_ref_buffer = data_from_ref[UART_BYTE_OFFS_TX_REG / sizeof(uint32_t)];

	timeout_buffer = data_from_stim.p_values->timeout;
	testcase_id = data_from_stim.cnt_testcases;
	testsequence_id = data_from_stim.testsequence_id;

	/*	reset of final testcase signal */
	testcase_finished.write(false);
	/*	signal to testcontroller */
	reference_received.write(true);

	/*	start timeout based on received timeout data */
	event_timeout.notify(timeout_buffer);
	start_time_buffer = sc_time_stamp();
}

/*
 * **************************************************************
 *
 * functionname:	compare_uart_method
 * purpose:			Method for comparison of Reference values and
 * 					received results from monitor module
 * parameters:		none
 * returnvalue:		none
 *
 * **************************************************************
 */
void scoreboard_uart::compare_uart_method()
{
	/*	reset timeout */
	event_timeout.cancel();

	rx_data_out_buffer = rx_data_out.read();
	tx_data_out_buffer = tx_data_out.read();
	end_time_buffer = sc_time_stamp();

	/*	Evaluation of data and comparison to Reference values */
	if (  rx_data_ref_buffer == rx_data_out_buffer &&
		tx_data_ref_buffer == tx_data_out_buffer)
	{
		if ( (end_time_buffer - start_time_buffer) < timeout_buffer )
		{
			result = eOK;
		}
		else
		{
			result = eTIMEOUT_OK;
		}
	}
	else if ( (end_time_buffer - start_time_buffer) < timeout_buffer )
	{
		result = eMISMATCH;
	}
	else result = eTIMEOUT_MISMATCH;

	write_to_file_uart_method();

	rx_data_ref_buffer_old = rx_data_ref_buffer;
	tx_data_ref_buffer_old = tx_data_ref_buffer;

	reference_received.write(false);
	testcase_finished.write(true);
}

/*
 * **************************************************************
 *
 * functionname:	write_to_file_uart_method
 * purpose:			Function for saving testcase results to textfile
 * parameters:		none
 * returnvalue:		none
 *
 * **************************************************************
 */
void scoreboard_uart::write_to_file_uart_method()
{
	outputFile.open("scoreboard.txt", fstream::ate | fstream::app);
	if (outputFile.is_open())
	{
	/*	indicate, if result data haven't changed */
	// TODO: compare input data, not result data !
	if (rx_data_ref_buffer == rx_data_ref_buffer_old &&
		tx_data_ref_buffer == tx_data_ref_buffer_old )
	{
	  outputFile << "---;---;---;no input change;no input change;no input change;---;---;---;---;---;---;---;" << endl;
	}
	outputFile << testsequence_id      << "; "
			   << testcase_id          << "; "
			   << result               << "; "
			   << rx_data_ref_buffer  << "; "
			   << tx_data_ref_buffer  << "; "
			   << rx_data_out_buffer   << "; "
			   << tx_data_out_buffer   << "; "
			   << timeout_buffer       << "; "
			   << start_time_buffer    << "; "
			   << end_time_buffer
			   << endl;
	}
	else cout << "file open error" << endl;

	outputFile.close();
}

/*
 * **************************************************************
 *
 * functionname:	ReferenceToScoreboard_b_transport
 * purpose:			Blocking transport function for TLM target socket connected to Reference model
 * 					Implementation required for TLM simple socket
 * parameters:		pointer to generic payload container
 * 					value for transport time delay
 * returnvalue:		none
 *
 * **************************************************************
 */
void scoreboard_uart::ReferenceToScoreboard_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
	/*	extract transaction data from payload container */
	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64    adr = trans.get_address();
	unsigned char*   ptr = trans.get_data_ptr();
	size_t     len = trans.get_data_length();
	unsigned char*   byt = trans.get_byte_enable_ptr();
	unsigned int     wid = trans.get_streaming_width();

	/*	Failure handling */
	if (byt != NULL) {
    trans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
    return;
	}

	if (wid != 0 && wid < len) {
		trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE );
		return;
	}

	switch(cmd) {
		case tlm::TLM_WRITE_COMMAND:
			adr = adr - BASE_ADDR;
			/*	copy payload data to defined data structure of Reference model data */
			memcpy(&data_from_ref[0],ptr,len);
			trans.set_response_status(tlm::TLM_OK_RESPONSE );
			break;
		case tlm::TLM_READ_COMMAND:
			/* not supported */
			cout << "Read Command not supported" << endl;
			break;
		default:
		cout << "ERROR\n";
		trans.set_response_status( tlm::TLM_COMMAND_ERROR_RESPONSE);
		break;
	}
}

/*
 * **************************************************************
 *
 * functionname:	StimulatorToScoreboard_b_transport
 * purpose:			Blocking transport function for TLM target socket connected to Stimulator module
 * 					Implementation required for TLM simple socket
 * parameters:		pointer to generic payload container
 * 					value for transport time delay
 * returnvalue:		none
 *
 * **************************************************************
 */
void scoreboard_uart::StimulatorToScoreboard_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
	/*	extract transaction data from payload container */
	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64    adr = trans.get_address(); // unused
	unsigned char*   ptr = trans.get_data_ptr();
	size_t     len = trans.get_data_length();
	unsigned char*   byt = trans.get_byte_enable_ptr();
	unsigned int     wid = trans.get_streaming_width();

	/*	Failure handling */
	if (byt != NULL) {
    trans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
    return;
	}

	if (wid != 0 && wid < len) {
		trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE );
		return;
	}

	switch(cmd) {
		case tlm::TLM_WRITE_COMMAND:
			/*	copy payload data to defined data structure of Stimulator's testcase data */
			memcpy(&data_from_stim,ptr,sizeof(struct data_to_scoreboard_t));
			trans.set_response_status(tlm::TLM_OK_RESPONSE );
			receive_event.notify();
			break;
		case tlm::TLM_READ_COMMAND:
			/* not supported */
			cout << "Read Command not supported" << endl;
			break;
		default:
		cout << "ERROR\n";
		trans.set_response_status( tlm::TLM_COMMAND_ERROR_RESPONSE);
		break;
	}
}
/*///////////////////////////////////////////////////////////////////////////////////////
 * scoreboard_uart.cpp
 */
