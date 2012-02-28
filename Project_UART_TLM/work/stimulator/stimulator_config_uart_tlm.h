/*
 * 	Filename:	stimulator_config_uart_tlm.h
 *
 * 	Version:	---
 *
 *  Created on:	2012/02/22
 *
 *  Author: 	Roman SOLLBOECK
 *
 *  Project:	SystemC Checker
 *  Submodule:	Stimulator
 *
 *  purpose:	user-specific configuration for stimulator module
 *  			config file for UART, interface to TLM model
 *
 *  History:	2012/02/22: first executable version implemented
 *
 */

#ifndef STIMULATOR_CONFIG_UART_TLM_H_
#define STIMULATOR_CONFIG_UART_TLM_H_

#define SC_INCLUDE_DYNAMIC_PROCESSES

#include <systemc>
using namespace sc_core;
using namespace sc_dt;
using namespace std;
#include <scv.h>
/*	patch for dealing with issue from OSCI forum
 * 	http://www.systemc.org/Discussion_Forums/systemc-forum/archive/msg?list_name=systemc-forum&monthdir=201005&msg=msg00010.html
 */
void _scv_pop_constraint();	/*	patch	*/

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include "../global.h"
#include "stimulator.h"

#define GLOBAL_TIMEOUT (sc_time(50, SC_NS))

SCV_EXTENSIONS(uart_data_t) {
public:
	scv_extensions < sc_uint<DATABITS> > sw_data_rx;
	scv_extensions < bool > sw_reset;
	scv_extensions < bool > sw_rx_enable;
	scv_extensions < sc_uint<DATABITS> > sw_data_tx;
	scv_extensions < bool > sw_tx_enable;
	scv_extensions < bool > sw_uld_rx_data;
	scv_extensions < bool > sw_ld_tx_data;

	SCV_EXTENSIONS_CTOR(uart_data_t) {
		SCV_FIELD (sw_data_rx);
		SCV_FIELD (sw_rx_enable);
		SCV_FIELD (sw_data_tx);
		SCV_FIELD (sw_reset);
		SCV_FIELD (sw_tx_enable);
		SCV_FIELD (sw_uld_rx_data);
		SCV_FIELD (sw_ld_tx_data);
	}
};


class packet_uart_constraint_base_t;

struct data_to_scoreboard_t
{
	packet_uart_constraint_base_t* p_values;
	unsigned int cnt_testcases;
	unsigned int testsequence_id;
};

/*	<ENTER BELOW>	------------------------------------------------
 *
 *	classname:	[user-defined constraint classes]
 *	purpose:	specialized base constraint class according SCV-guidelines
 *				no limit for user-specific amount of specialized classes
 *				testsequences are templated by these classes
 *
 *	Important:	use SCV_CONSTRAINT_CTOR,
 *				specialize from dutInput_constraint_base_t,
 *				redeclaration of scv_smart_ptr not necessary
 */
class packet_uart_constraint_t_01
	: public packet_uart_constraint_base_t
{
public:
	SCV_CONSTRAINT_CTOR(packet_uart_constraint_t_01)
	{
		SCV_CONSTRAINT (pInput->sw_data_rx() < 255);
		pInput->sw_reset.disable_randomization();
		pInput->sw_reset.write(false);
		pInput->sw_rx_enable.disable_randomization();
		pInput->sw_rx_enable.write(true);

		SCV_CONSTRAINT (pInput->sw_data_tx() < 255);
		pInput->sw_tx_enable.disable_randomization();
		pInput->sw_tx_enable.write(true);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_uart_constraint_t_02
	: public packet_uart_constraint_base_t
{
public:
	SCV_CONSTRAINT_CTOR(packet_uart_constraint_t_02)
	{
		SCV_CONSTRAINT (pInput->sw_data_rx() < 50);
		pInput->sw_reset.disable_randomization();
		pInput->sw_reset.write(false);
		pInput->sw_rx_enable.disable_randomization();
		pInput->sw_rx_enable.write(true);

		SCV_CONSTRAINT (pInput->sw_data_tx() < 100);
		pInput->sw_tx_enable.disable_randomization();
		pInput->sw_tx_enable.write(true);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_uart_constraint_t_03
	: public packet_uart_constraint_base_t
{
public:
	SCV_CONSTRAINT_CTOR(packet_uart_constraint_t_03)
	{
		SCV_CONSTRAINT (pInput->sw_data_rx() > 200);
		pInput->sw_reset.disable_randomization();
		pInput->sw_reset.write(false);
		pInput->sw_rx_enable.disable_randomization();
		pInput->sw_rx_enable.write(true);

		pInput->sw_data_tx.disable_randomization();
		pInput->sw_tx_enable.disable_randomization();
		pInput->sw_tx_enable.write(false);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_uart_constraint_t_04
	: public packet_uart_constraint_base_t
{
public:
	SCV_CONSTRAINT_CTOR(packet_uart_constraint_t_04)
	{
		pInput->sw_data_rx.keep_only(30, 60);
		pInput->sw_data_rx.keep_out(130, 160);
		pInput->sw_data_tx.keep_only(0, 10);
		pInput->sw_data_tx.keep_out(240, 255);

		pInput->sw_reset.disable_randomization();
		pInput->sw_reset.write(false);
		pInput->sw_rx_enable.disable_randomization();
		pInput->sw_rx_enable.write(true);
		pInput->sw_tx_enable.disable_randomization();
		pInput->sw_tx_enable.write(false);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_uart_constraint_t_05
	: public packet_uart_constraint_base_t
{
public:
	list < sc_uint <DATABITS> > legal_values;
	SCV_CONSTRAINT_CTOR(packet_uart_constraint_t_05)
	{
		for (int i = 0; i < 255; i += 25)
		{
			legal_values.push_back(i);
		}

		pInput->sw_data_rx.keep_only(legal_values);
		pInput->sw_data_tx.keep_only(legal_values);

		pInput->sw_reset.disable_randomization();
		pInput->sw_reset.write(false);
		pInput->sw_rx_enable.disable_randomization();
		pInput->sw_rx_enable.write(true);
		pInput->sw_tx_enable.disable_randomization();
		pInput->sw_tx_enable.write(true);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_uart_constraint_t_06
	: public packet_uart_constraint_base_t
{
public:
	typedef pair< sc_uint<DATABITS>, sc_uint<DATABITS> > data_range;
	scv_bag < data_range > distribution_sw_data_rx;
	scv_bag < data_range > distribution_sw_data_tx;

	SCV_CONSTRAINT_CTOR(packet_uart_constraint_t_06)
	{
		distribution_sw_data_rx.add( data_range (0, 50),			20);
		distribution_sw_data_rx.add( data_range (100, 150),			20);
		distribution_sw_data_rx.add( data_range (200, 250),			20);
		distribution_sw_data_tx.add( data_range (51, 100),			30);
		distribution_sw_data_tx.add( data_range (151, 200),			30);

		pInput->sw_data_rx.set_mode(distribution_sw_data_rx);
		pInput->sw_data_tx.set_mode(distribution_sw_data_tx);

		pInput->sw_reset.disable_randomization();
		pInput->sw_reset.write(false);
		pInput->sw_rx_enable.disable_randomization();
		pInput->sw_rx_enable.write(true);
		pInput->sw_tx_enable.disable_randomization();
		pInput->sw_tx_enable.write(true);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_uart_constraint_t_07
	: public packet_uart_constraint_base_t
{
public:
	typedef sc_uint<DATABITS> data_single;
	scv_bag < data_single > distribution_sw_data_rx;
	scv_bag < data_single > distribution_sw_data_tx;

	SCV_CONSTRAINT_CTOR(packet_uart_constraint_t_07)
	{
		distribution_sw_data_rx.add( (data_single) 20, 20);
		distribution_sw_data_rx.add( (data_single) 40, 40);
		distribution_sw_data_rx.add( (data_single) 60, 40);
		distribution_sw_data_tx.add( (data_single) 77, 40);
		distribution_sw_data_tx.add( (data_single) 88, 20);
		distribution_sw_data_tx.add( (data_single) 99, 40);

		pInput->sw_data_rx.set_mode(distribution_sw_data_rx);
		pInput->sw_data_tx.set_mode(distribution_sw_data_tx);

		pInput->sw_reset.disable_randomization();
		pInput->sw_reset.write(false);
		pInput->sw_rx_enable.disable_randomization();
		pInput->sw_rx_enable.write(true);
		pInput->sw_tx_enable.disable_randomization();
		pInput->sw_tx_enable.write(true);

		timeout = GLOBAL_TIMEOUT;
	}
};

/*	<ENTER BELOW>	------------------------------------------------
 *
 *	classname:	project_testsequences
 *	purpose:	class consisting of user-specific test sequences
 *				one class inside stimulator module, which holds
 *				all testsequences
 *				testsequences are processed in the order of instantiation
 *				new testsequences are added the same as the samples
 *				using user-defined constraint classes
 */
class project_testsequences
{
public:
	/*	functionname:	project_testsequences (inline Constructor)
	 *  purpose:		instantiation and registration of testsequences
	 *  parameters:		p_testsequences...pointer to collection of all user-defined testsequences
	 *  returnvalues:	none
	 */
	project_testsequences(testseq_collectionentry_c *p_testsequences)
	{
		/*			|	templated classes for testsequence 						|	pointer to collection		|	specific number of
		 * 			|							< specialized constraint class >|	of testsequences (only one)	|	testcases (randoms)	*/
		addSequence	(new testsequence_specialized_c < packet_uart_constraint_t_01 > 	(p_testsequences, 				10));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < packet_uart_constraint_t_02 > 	(p_testsequences, 				10));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < packet_uart_constraint_t_03 > 	(p_testsequences, 				10));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < packet_uart_constraint_t_04 > 	(p_testsequences, 				10));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < packet_uart_constraint_t_05 > 	(p_testsequences, 				10));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < packet_uart_constraint_t_06 > 	(p_testsequences, 				10));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < packet_uart_constraint_t_07 > 	(p_testsequences, 				10));
		/*			|															|								|						*/
		/*	<ENTER> new testsequences	*/
	}

	/*	dummy function for catching return pointer of "new" operator	*/
	void addSequence(void * dummy) {}
};

/*	<ENTER BELOW>	------------------------------------------------
 *
 *	structname:	stimulator_m
 *	purpose:	Stimulator SystemC Module for propagation of
 *				constraint randomized values to DUT
 *				needs partly to be adapted to DUT
 *
 */
SC_MODULE (stimulator_m)
{
public:
	tlm_utils::simple_initiator_socket<stimulator_m> reference_initiator_socket;
	tlm_utils::simple_initiator_socket<stimulator_m> scoreboard_initiator_socket;

	sc_inout <sc_uint <DATABITS> > port_inputs_rx;
	sc_inout <sc_uint <DATABITS> > port_inputs_tx;
	sc_inout < bool > rx_enable_in;
	sc_inout < bool > tx_enable_in;
	sc_inout < bool > reset_in;

	sc_port < handshake_generation_if > data_written;

	/*	helper variables for port assignment	*/
	sc_uint<DATABITS> s_input_rx;
	sc_uint<DATABITS> s_input_tx;
	bool s_reset_in;
	bool s_tx_enable_in;
	bool s_rx_enable_in;

	/*	-> DO NOT MODIFY <-
	 * 	control signal ports for stimulator */
	sc_in < bool > next_sample_to_reference;
	sc_in < bool > next_sample_to_dut;
	sc_inout < bool > testsequences_finished;

	/*	Constructor declaration	*/
	stimulator_m (sc_module_name nm);

	/*	module function declarations	*/
	void create_testsequences ( );

	/*	<ENTER BELOW> --------------------------------------------------
	 * 	user-defined function for assigning the created values to
	 * 	the module ports of dut
	 */

	void write_values_to_dut(packet_uart_constraint_base_t *p_values)
	{
		cout << "STIMULATOR: write values to dut" << endl;

		s_input_rx = p_values->pInput->sw_data_rx;
		s_input_tx = p_values->pInput->sw_data_tx;
		s_reset_in = false;
		s_tx_enable_in = p_values->pInput->sw_tx_enable;
		s_rx_enable_in = p_values->pInput->sw_rx_enable;

		port_inputs_rx ->write(s_input_rx);
		port_inputs_tx ->write(s_input_tx);
		reset_in.write(s_reset_in);
		tx_enable_in.write(s_tx_enable_in);
		rx_enable_in.write(s_rx_enable_in);

		data_written->notify(SC_ZERO_TIME);

		if(s_reset_in == true) cout << "STIMULATOR: RESET SENT" << endl;
	}

	/*	<ENTER BELOW> --------------------------------------------------
	 * 	user-defined function for assigning the created values to
	 * 	the module ports of reference model
	 */

	void write_values_to_reference(packet_uart_constraint_base_t *p_values , unsigned int _cnt_testcases, unsigned int _testsequence_id )
	{
		tlm::tlm_generic_payload trans;

		uint32_t data;
		sc_time delay = SC_ZERO_TIME;
		uint64_t addr;

		struct data_to_scoreboard_t data_to_scoreboard;
		data_to_scoreboard.p_values = p_values;
		data_to_scoreboard.cnt_testcases = _cnt_testcases;
		data_to_scoreboard.testsequence_id = _testsequence_id;

		data = p_values->pInput->sw_data_rx.to_int();
		trans.set_command(tlm::TLM_WRITE_COMMAND);/*There exist TLM_WRITE_COMMAND, TLM_READ_COMMAND and TLM_IGNORE_COMMAND which can be used to point to extensions*/
		addr = UART_BASE_ADDR + ( UART_BYTE_OFFS_RX_REG << 3);
		trans.set_address(addr);
		trans.set_data_length(sizeof(data));
		trans.set_data_ptr((unsigned char *)&data);
		trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
		/*the following responses are available eventually
					TLM_OK_RESPONSE                Successful
					TLM_INCOMPLETE_RESPONSE        Transaction not delivered to target. (Default)
					TLM_ADDRESS_ERROR_RESPONSE     Unable to act on address
					TLM_COMMAND_ERROR_RESPONSE     Unable to execute command
					TLM_BURST_ERROR_RESPONSE       Unable to act on data length or streaming width
					TLM_BYTE_ENABLE_ERROR_RESPONSE Unable to act on byte enable
					TLM_GENERIC_ERROR_RESPONSE     Any other error
		*/
		process_tlm_transmission(eREFERENCE, &trans, delay);

		data = p_values->pInput->sw_data_tx.to_int();
		trans.set_command(tlm::TLM_WRITE_COMMAND);/*There exist TLM_WRITE_COMMAND, TLM_READ_COMMAND and TLM_IGNORE_COMMAND which can be used to point to extensions*/
		addr = UART_BASE_ADDR + ( UART_BYTE_OFFS_TX_REG << 3);
		trans.set_address(addr);
		trans.set_data_length(sizeof(data));
		trans.set_data_ptr((unsigned char *)&data);
		trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
		process_tlm_transmission(eREFERENCE, &trans, delay);

		data = 	( p_values->pInput->sw_reset ? UART_CTRL_RESET : 0x00 ) |
				( p_values->pInput->sw_rx_enable ? UART_CTRL_RX_ENABLE : 0x00 ) |
				( p_values->pInput->sw_tx_enable ? UART_CTRL_TX_ENABLE : 0x00 ) |
				( p_values->pInput->sw_uld_rx_data ? UART_CTRL_ULD_RX_DATA : 0x00 ) |
				( p_values->pInput->sw_ld_tx_data ? UART_CTRL_LD_TX_DATA : 0x00 );
		trans.set_command(tlm::TLM_WRITE_COMMAND);/*There exist TLM_WRITE_COMMAND, TLM_READ_COMMAND and TLM_IGNORE_COMMAND which can be used to point to extensions*/
		addr = UART_BASE_ADDR + ( UART_BYTE_OFFS_CTRL << 3);
		trans.set_address(addr);
		trans.set_data_length(sizeof(uint32_t));
		trans.set_data_ptr((unsigned char *)&data);
		trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
		process_tlm_transmission(eREFERENCE, &trans, delay);

		delay = sc_time(10, SC_NS);

		// provide pointer to input values to scoreboard
		addr = SCOREBOARD_BASE_ADDR;
		trans.set_address(addr);
		trans.set_data_length(sizeof(struct data_to_scoreboard_t));
		trans.set_data_ptr((unsigned char *)&data_to_scoreboard);
		trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
		process_tlm_transmission(eSCOREBOARD, &trans, delay);

	}

	/*	SystemC module thread for stimulator	*/
	void stimulator_thread (void);

	void process_tlm_transmission(tlm_direction_t dir, tlm::tlm_generic_payload* trans, sc_time delay);


private:
	/*	extracted number of testsequences	*/
	unsigned int numOfTestsequences;
	/*	modules root element for list of testsequences	*/
	testseq_collectionentry_c testsequences;
};

#endif /* STIMULATOR_CONFIG_H_ */

/*///////////////////////////////////////////////////////////////////////////////////////
 * stimulator_config_uart_tlm.h
 */

