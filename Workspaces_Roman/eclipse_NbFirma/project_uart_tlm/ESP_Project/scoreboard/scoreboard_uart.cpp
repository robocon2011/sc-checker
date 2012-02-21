/*********************************************************************************/

#include <scv.h>
#include <systemc>
#include "scoreboard_config.h"

SC_HAS_PROCESS(scoreboard_uart);
scoreboard_uart::scoreboard_uart(sc_module_name nm)
  : sc_module (nm),
    rx_data_stim_buffer(0),
    tx_data_stim_buffer(0),
    rx_data_out_buffer(0),
    tx_data_out_buffer(0),
    timeout_buffer(0, SC_NS),

    testsequence_id(0),
    testcase_id(0),
    start_time_buffer(0, SC_NS),
    end_time_buffer(0, SC_NS)
{
  SC_METHOD (store_reference_uart_method);
    sensitive   << rx_data_stim.value_changed()
                << tx_data_stim.value_changed()
                << testcase_id_reference.value_changed()
                << testsequence_id_reference.value_changed();
  dont_initialize();

  SC_METHOD (compare_uart_method);
    sensitive   << data_written
                << event_timeout;
  dont_initialize();

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

void scoreboard_uart::store_reference_uart_method()
{
  rx_data_stim_buffer = rx_data_stim.read();
  tx_data_stim_buffer = tx_data_stim.read();

  timeout_buffer = sc_time(timeout_reference.read(),SC_SEC);
  testcase_id = testcase_id_reference.read();
  testsequence_id = testsequence_id_reference.read();

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

