/*********************************************************************************/
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <scv.h>
#include <systemc>
#include "scoreboard_config_uart.h"

void scoreboard_uart::store_reference_uart_method()
{
	rx_data_ref_buffer = data_from_ref[UART_BYTE_OFFS_RX_REG / sizeof(uint32_t)];

	tx_data_ref_buffer = data_from_ref[UART_BYTE_OFFS_TX_REG / sizeof(uint32_t)];

	timeout_buffer = data_from_stim.p_values->timeout;
	testcase_id = data_from_stim.cnt_testcases;
	testsequence_id = data_from_stim.testsequence_id;

	testcase_finished.write(false);
	reference_received.write(true);

	event_timeout.notify(timeout_buffer);
	start_time_buffer = sc_time_stamp();
}

void scoreboard_uart::compare_uart_method()
{
	event_timeout.cancel();

	rx_data_out_buffer = rx_data_out.read();
	tx_data_out_buffer = tx_data_out.read();
	end_time_buffer = sc_time_stamp();

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

void scoreboard_uart::write_to_file_uart_method()
{
	outputFile.open("scoreboard.txt", fstream::ate | fstream::app);
	if (outputFile.is_open())
	{
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

void scoreboard_uart::ReferenceToScoreboard_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64    adr = trans.get_address();
	unsigned char*   ptr = trans.get_data_ptr();
	size_t     len = trans.get_data_length();
	unsigned char*   byt = trans.get_byte_enable_ptr();
	unsigned int     wid = trans.get_streaming_width();

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
			//memcpy((char *)&mem[adr],ptr,len);
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

void scoreboard_uart::StimulatorToScoreboard_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
{
	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64    adr = trans.get_address();
	unsigned char*   ptr = trans.get_data_ptr();
	size_t     len = trans.get_data_length();
	unsigned char*   byt = trans.get_byte_enable_ptr();
	unsigned int     wid = trans.get_streaming_width();

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

