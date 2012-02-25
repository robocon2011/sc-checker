/*********************************************************************************/
#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <scv.h>
#include <systemc>
#include "scoreboard_config_uart.h"
#include "../reference_model/UART_TLM/common.hpp"



void scoreboard_uart::store_reference_uart_method()
{
//  rx_data_stim_buffer = rx_data_stim.read();
//  tx_data_stim_buffer = tx_data_stim.read();
//
//  timeout_buffer = sc_time(timeout_reference.read(),SC_SEC);
//  testcase_id = testcase_id_reference.read();
//  testsequence_id = testsequence_id_reference.read();

	rx_data_stim_buffer = data_from_ref.packet.sw_data_rx;
	tx_data_stim_buffer = data_from_ref.packet.sw_data_tx;

	timeout_buffer = sc_time(data_from_ref.timeout, SC_SEC);
	testcase_id = data_from_ref.cnt_testcases;
	testsequence_id = data_from_ref.testsequ_id;

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

  if (  rx_data_stim_buffer == rx_data_out_buffer &&
        tx_data_stim_buffer == tx_data_out_buffer)
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

  rx_data_stim_buffer_old = rx_data_stim_buffer;
  tx_data_stim_buffer_old = tx_data_stim_buffer;

  reference_received.write(false);
  testcase_finished.write(true);
}

void scoreboard_uart::write_to_file_uart_method()
{

  outputFile.open("scoreboard.txt", fstream::ate | fstream::app);
  if (outputFile.is_open())
  {
    if (rx_data_stim_buffer == rx_data_stim_buffer_old &&
        tx_data_stim_buffer == tx_data_stim_buffer_old )
    {
      outputFile << "---;---;---;no input change;no input change;no input change;---;---;---;---;---;---;---;" << endl;
    }
    outputFile << testsequence_id      << "; "
               << testcase_id          << "; "
               << result               << "; "
               << rx_data_stim_buffer  << "; "
               << tx_data_stim_buffer  << "; "
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

/*required implementation of the b_transport method. this method is called by the initiator eventually*/
void scoreboard_uart::my_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t) {


	tlm::tlm_command cmd = trans.get_command();
	sc_dt::uint64    adr = trans.get_address();
	/*pointer to the payload*/
	unsigned char*   ptr = trans.get_data_ptr();
	/*how many bytes expected?*/
	size_t     len = trans.get_data_length();
	/*get range of valid bytes in payload*/
	unsigned char*   byt = trans.get_byte_enable_ptr();
	/*in case streaming is supported*/
	unsigned int     wid = trans.get_streaming_width();

	/*we do not support a lot*/

//	/*1st memory boundary check*/
//	if (adr+len > BASE_ADDR+LENGTH) {
//    trans.set_response_status( tlm::TLM_ADDRESS_ERROR_RESPONSE );
//    return;
//	}

	/*2nd byte enable check, we do not support that*/
	if (byt != NULL) {
    trans.set_response_status(tlm::TLM_BYTE_ENABLE_ERROR_RESPONSE );
    return;
	}

	/*3rd check for streaming endeavor, we do not support that*/
	if (wid != 0 && wid < len) {
		trans.set_response_status(tlm::TLM_BURST_ERROR_RESPONSE );
		return;
	}


	/*4th process command*/
	switch(cmd) {
		case tlm::TLM_WRITE_COMMAND:
			adr = adr - BASE_ADDR;
			//memcpy((char *)&mem[adr],ptr,len);
			memcpy((char *)&data_from_ref,ptr,len);
			trans.set_response_status(tlm::TLM_OK_RESPONSE );
			receive_event.notify();
			break;
//		TLM_READ_COMMAND not supported
//		case tlm::TLM_READ_COMMAND:
//			adr = adr - BASE_ADDR;
//			memcpy(ptr,(char *)&data_from_ref[adr],len);
//			trans.set_response_status(tlm::TLM_OK_RESPONSE );
//			break;
		default:
		cout << "ERROR\n";
		trans.set_response_status( tlm::TLM_COMMAND_ERROR_RESPONSE);
		break;

	}

}
