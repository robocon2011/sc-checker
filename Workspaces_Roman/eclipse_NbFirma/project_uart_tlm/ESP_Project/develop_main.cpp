/******************************************************************************/
/*                                                                            */
/* Filename:    develop_main.cpp                                              */
/*                                                                            */
/* Author:      Roman Sollböck, Philipp Maroschek                             */
/*                                                                            */
/* Tools:       Compiles with SystemC 2.2.v0                                  */
/*                                                                            */
/* Project:     SystemC Checker                                               */
/*                                                                            */
/* Topmodule:   ------                                                        */
/* Submodules:  ------                                                        */
/*                                                                            */
/******************************************************************************/


#define BITWIDTH 32

#define SC_INCLUDE_DYNAMIC_PROCESSES


#include "database/database.h"
#include "driver/driver.h"
//#include "dut/fulladder/fulladder_rtl.h"
#include "monitor/monitor.h"
#include "reference_model/UART_TLM/uart_tlm.hpp"
#include "scoreboard/scoreboard_config_uart.h"
#include "stimulator/stimulator_config_uart_tlm.h"
#include "testcontroller/testcontroller.h"
#include "dut/uart/uart.h"

#include "global.h"

int sc_main (int argc, char *argv[])
{

  scv_startup();

  scv_tr_text_init();
  scv_tr_db db("ESP_DB");
  scv_tr_db::set_default_db(&db);

  /* create tracefile */
  sc_trace_file* tracefile_uart;

  tracefile_uart = sc_create_vcd_trace_file("uart_trace");

  if (!tracefile_uart){
      cout << "Error creating tracefile." << endl;
  }


  stimulator_m i_stimulator("i_stimulator");
  testcontroller i_testcontroller("i_testcontroller");
  uart_tlm i_reference_uart ("i_reference_uart");

  //reference_model i_reference_model ("i_reference_model"); TODO: implement TLM-Reference model
  scoreboard_uart i_scoreboard("i_scoreboard");
  driver_uart driver_i("driver_i");
  monitor_uart monitor_i("monitor_i");
  uart uart_i("uart_i");



  /* signals stimulator to driver */
  sc_signal<sc_uint< DATABITS> > rx_data_in;
  sc_signal<sc_uint< DATABITS> > tx_data_in;
  sc_signal<bool> reset_in;
  sc_signal<bool> tx_enable_in;
  sc_signal<bool> rx_enable_in;

  /* signals driver to dut */
  sc_signal<sc_logic> txclk;
  sc_signal<sc_logic> reset;
  sc_signal<sc_logic> ld_tx_data;
  sc_signal<sc_logic> tx_enable;
  sc_signal<sc_logic> rxclk;
  sc_signal<sc_logic> uld_rx_data;
  sc_signal<sc_logic> rx_enable;
  sc_signal<sc_logic> rx_in;
  sc_signal<sc_logic> tx_data_port[DATABITS];

  /* signals dut to monitor */
  sc_signal<sc_logic> rx_data_port[DATABITS];
  sc_signal<sc_logic> tx_out;
  sc_signal<sc_logic> tx_empty;
  sc_signal<sc_logic> rx_empty;
  handshake stimulator_data_written;
  handshake uart_data_written;
  handshake driver_data_written;

  /* signals monitor to scoreboard */
  sc_signal<sc_uint< DATABITS> > rx_data_out;
  sc_signal<sc_uint< DATABITS> > tx_data_out;
  sc_signal<bool> tx_empty_out;
  sc_signal<bool> rx_empty_out;
  handshake monitor_data_written;

  /* signals testcontroller to stimulator */
  sc_signal <bool> signal_next_sample_to_reference;
  sc_signal <bool> signal_next_sample_to_dut;
  sc_signal <bool> signal_reference_received;
  sc_signal <bool> signal_testcase_finished;
  sc_signal <bool> signal_all_testsequences_finished;

  sc_signal <unsigned int> signal_testcase_id;
  sc_signal <unsigned int> signal_testsequence_id;
  sc_signal <double> signal_timeout;

  /* assignment of testcontroller ports */
  i_testcontroller.next_sample_to_reference(signal_next_sample_to_reference);
  i_testcontroller.reference_received(signal_reference_received);
  i_testcontroller.next_sample_to_dut(signal_next_sample_to_dut);
  i_testcontroller.testcase_finished(signal_testcase_finished);
  i_testcontroller.all_sequences_finished(signal_all_testsequences_finished);

  /* assignment of stimulator ports */
  i_stimulator.port_inputs_rx(rx_data_in);
  i_stimulator.port_inputs_tx(tx_data_in);
  i_stimulator.rx_enable_in(rx_enable_in);
  i_stimulator.tx_enable_in(tx_enable_in);
  i_stimulator.reset_in(reset_in);

  i_stimulator.next_sample_to_reference(signal_next_sample_to_reference);
  i_stimulator.next_sample_to_dut(signal_next_sample_to_dut);
  i_stimulator.testsequences_finished(signal_all_testsequences_finished);
  i_stimulator.testcase_id(signal_testcase_id);
  i_stimulator.testsequence_id(signal_testsequence_id);
  i_stimulator.timeout(signal_timeout);
  i_stimulator.data_written(stimulator_data_written);

  /*connect them using the TLM interfaces*/
  i_stimulator.reference_initiator_socket.bind(i_reference_uart.uart_target_socket);
  i_stimulator.scoreboard_initiator_socket.bind(i_scoreboard.StimulatorToScoreboard_target_socket);
  i_reference_uart.uart_initiator_socket.bind(i_scoreboard.ReferenceToScoreboard_target_socket);

  /* assignment of driver ports */
  driver_i.rx_data_in(rx_data_in);
  driver_i.tx_data_in(tx_data_in);
  driver_i.reset_in(reset_in);
  driver_i.rx_enable_in(rx_enable_in);
  driver_i.tx_enable_in(tx_enable_in);

  driver_i.reset(reset);
  driver_i.ld_tx_data(ld_tx_data);
  driver_i.tx_enable(tx_enable);
  driver_i.uld_rx_data(uld_rx_data);
  driver_i.rx_enable(rx_enable);
  driver_i.rx_in(rx_in);
  driver_i.data_written(stimulator_data_written);
  driver_i.data_written_uart(driver_data_written);

  for(unsigned i = 0; i < DATABITS;i++){
    driver_i.tx_data_port(tx_data_port[i]);
  }

  /* assignment of monitor ports */
  monitor_i.tx_out(tx_out);
  monitor_i.tx_empty(tx_empty);
  monitor_i.rx_empty(rx_empty);
  monitor_i.rxclk(driver_i.rxclk);
  monitor_i.txclk(driver_i.txclk);
  for(unsigned i = 0; i < DATABITS; i++){
    monitor_i.rx_data_port(rx_data_port[i]);
  }

  monitor_i.rx_data_out(rx_data_out);
  monitor_i.tx_data_out(tx_data_out);
  monitor_i.tx_empty_out(tx_empty_out);
  monitor_i.rx_empty_out(rx_empty_out);
  monitor_i.data_written(monitor_data_written);
  monitor_i.data_written_rx(uart_data_written);

  /* assignment for dut-uart ports */
  uart_i.reset(reset);
  uart_i.txclk(driver_i.txclk);
  uart_i.ld_tx_data(ld_tx_data);
  for(unsigned i = 0; i < DATABITS;i++){
    uart_i.tx_data[i](tx_data_port[i]);
  }
  uart_i.tx_enable(tx_enable);
  uart_i.rxclk(driver_i.rxclk);
  uart_i.uld_rx_data(uld_rx_data);
  uart_i.rx_enable(rx_enable);
  uart_i.rx_in(rx_in);

  for(unsigned i = 0; i < DATABITS;i++){
    uart_i.rx_data[i](rx_data_port[i]);
  }
  uart_i.rx_empty(rx_empty);
  uart_i.tx_out(tx_out);
  uart_i.tx_empty(tx_empty);
  uart_i.data_written_rx(uart_data_written);
  uart_i.data_written_driver(driver_data_written);

  /* assignment of scoreboard ports */

  i_scoreboard.data_written(monitor_data_written);
  i_scoreboard.testcase_finished(signal_testcase_finished);
  i_scoreboard.reference_received(signal_reference_received);
  i_scoreboard.testcase_id_reference(signal_testcase_id);
  i_scoreboard.testsequence_id_reference(signal_testsequence_id);
  i_scoreboard.timeout_reference(signal_timeout);
  i_scoreboard.tx_data_stim(tx_data_in);
  i_scoreboard.rx_data_stim(rx_data_in);
  i_scoreboard.tx_data_out(tx_data_out);
  i_scoreboard.rx_data_out(rx_data_out);
  i_scoreboard.tx_empty_out(tx_empty_out);
  i_scoreboard.rx_empty_out(rx_empty_out);

  /* transaction recording - create value change dumps*/
  sc_trace(tracefile_uart, reset, "reset");
  sc_trace(tracefile_uart, tx_enable, "tx_enable");
  sc_trace(tracefile_uart, rx_enable, "rx_enable");
  sc_trace(tracefile_uart, ld_tx_data, "ld_tx_data");
  sc_trace(tracefile_uart, uld_rx_data, "uld_rx_data");
  sc_trace(tracefile_uart, tx_empty, "tx_empty");
  sc_trace(tracefile_uart, rx_empty, "rx_empty");
  sc_trace(tracefile_uart, rx_in, "rx_in");
  sc_trace(tracefile_uart, tx_out, "tx_out");


  cout << "START OF SIMULATION" << endl;

  sc_start();
  if (! sc_end_of_simulation_invoked()) sc_stop();

  sc_close_vcd_trace_file(tracefile_uart);

  cout << "END OF SIMULATION" << endl;


  return 0;
}
