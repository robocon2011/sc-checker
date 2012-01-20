/*
 * scoreboard_config.h
 *
 *  Created on: 27.11.2011
 *      Author: ew08b033
 */

#ifndef SCOREBOARD_CONFIG_H_
#define SCOREBOARD_CONFIG_H_

#include <systemc>
#include <scv.h>
#include <fstream>
#include <iostream>
#include "scoreboard.h"
#include "../global.h"

enum compareResult { eOK = 0, eMISMATCH, eTIMEOUT_OK, eTIMEOUT_MISMATCH};


SC_MODULE (scoreboard_fulladdr)
{
public:
	sc_in < sc_uint <BITWIDTH> > input_a_reference;
	sc_in < sc_uint <BITWIDTH> > input_b_reference;
	sc_in < bool > input_carry_reference;

	sc_in < sc_uint <BITWIDTH> > output_reference;
	sc_in < bool > output_carry_reference;
	sc_in < double > timeout_reference;
	sc_in < unsigned int > testcase_id_reference;
	sc_in < unsigned int > testsequence_id_reference;

	sc_in < sc_uint <BITWIDTH> > output_monitor;
	sc_in < bool > output_carry_monitor;
	sc_port < handshake_event_if > data_written;

	sc_inout < bool > reference_received;
	sc_inout < bool > testcase_finished;

	std::ofstream outputFile;

	scoreboard_fulladdr (sc_module_name nm);

	void store_reference_method ();
	void compare_method ();

	void write_to_file ();

private:
	sc_uint <BITWIDTH> input_a_reference_buffer, input_a_reference_old;
	sc_uint <BITWIDTH> input_b_reference_buffer, input_b_reference_old;
	bool input_carry_reference_buffer, input_carry_reference_old;
	sc_uint <BITWIDTH> output_reference_buffer;
	bool output_carry_reference_buffer;
	sc_time timeout_buffer;
	sc_event event_timeout;

	sc_uint <BITWIDTH> output_monitor_buffer;
	bool output_carry_monitor_buffer;

	unsigned int testsequence_id;
	unsigned int testcase_id;
	sc_time start_time_buffer;
	sc_time end_time_buffer;

	enum compareResult result;
};


SC_MODULE (scoreboard_uart)
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

  scoreboard_uart (sc_module_name nm);

  void store_reference_uart_method ();
  void compare_uart_method ();
  void write_to_file_uart_method ();

private:
  sc_uint <DATABITS> rx_data_stim_buffer, tx_data_stim_buffer,
                     rx_data_out_buffer, tx_data_out_buffer,
                     rx_data_stim_buffer_old, tx_data_stim_buffer_old;
  sc_time timeout_buffer;
  sc_event event_timeout;

  unsigned int testsequence_id;
  unsigned int testcase_id;
  sc_time start_time_buffer;
  sc_time end_time_buffer;

  enum compareResult result;
};


#endif /* SCOREBOARD_CONFIG_H_ */
