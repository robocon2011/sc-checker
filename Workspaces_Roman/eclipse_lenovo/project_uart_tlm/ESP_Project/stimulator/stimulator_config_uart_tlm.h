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
#include <scv.h>
/*	patch for dealing with issue from OSCI forum
 * 	http://www.systemc.org/Discussion_Forums/systemc-forum/archive/msg?list_name=systemc-forum&monthdir=201005&msg=msg00010.html
 */
void _scv_pop_constraint();	/*	patch	*/

#include <tlm.h>
/*std convinience sockets, which encapsulate the explicite inheritance of interfaces*/
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include "../global.h"
#include "../reference_model/UART_TLM/common.hpp"
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


class packet_fulladdr_constraint_base_t;

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
		pInput->sw_reset.disable_randomization();
		pInput->sw_reset.write(false);
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
		pInput->sw_reset.disable_randomization();
		pInput->sw_reset.write(false);
		pInput->sw_tx_enable.disable_randomization();
		pInput->sw_tx_enable.write(true);

		timeout = GLOBAL_TIMEOUT;
	}
};

/*
class packet_fulladdr_constraint_t_02
	: public packet_fulladdr_constraint_base_t
{
	SCV_CONSTRAINT_CTOR(packet_fulladdr_constraint_t_02)
	{
		SCV_CONSTRAINT (pInput->sw_a() > 100000);
		SCV_CONSTRAINT (pInput->sw_b() > 100000);
		pInput->sw_cy.disable_randomization();
		pInput->sw_cy.write(false);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_fulladdr_constraint_t_03
	: public packet_fulladdr_constraint_base_t
{
	SCV_CONSTRAINT_CTOR(packet_fulladdr_constraint_t_03)
	{
		SCV_CONSTRAINT (pInput->sw_b() < 50000);
		pInput->sw_a.disable_randomization();
		pInput->sw_cy.disable_randomization();
		pInput->sw_cy.write(false);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_fulladdr_constraint_t_04
	: public packet_fulladdr_constraint_base_t
{
	SCV_CONSTRAINT_CTOR(packet_fulladdr_constraint_t_04)
	{
		pInput->sw_a.keep_only(500, 1000);
		pInput->sw_b.keep_out(550, 950);
		pInput->sw_b.keep_only(0, 500);
		pInput->sw_b.keep_out(50, 450);
		pInput->sw_cy.disable_randomization();
		pInput->sw_cy.write(false);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_fulladdr_constraint_t_05
	: public packet_fulladdr_constraint_base_t
{
public:
	list < sc_uint <BITWIDTH> > legal_values;

	SCV_CONSTRAINT_CTOR(packet_fulladdr_constraint_t_05)
	{
		for (int i = 0; i < 100; i++)
		{
			legal_values.push_back(i*1000);
		}
		pInput->sw_a.keep_only(legal_values);
		pInput->sw_b.keep_only(legal_values);
		pInput->sw_cy.disable_randomization();
		pInput->sw_cy.write(false);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_fulladdr_constraint_t_06
	: public packet_fulladdr_constraint_base_t
{
public:
	typedef pair< sc_uint<BITWIDTH>, sc_uint<BITWIDTH> > data_range;
	scv_bag < data_range > distribution_input_A;
	scv_bag < data_range > distribution_input_B;

	SCV_CONSTRAINT_CTOR(packet_fulladdr_constraint_t_06)
	{
		distribution_input_A.add( data_range (1000, 2000),			500);
		distribution_input_A.add( data_range (2000, 10000),			500);
		distribution_input_A.add( data_range (30000, 3000000),		500);
		distribution_input_B.add( data_range (2000, 5000),			500);
		distribution_input_B.add( data_range (5000, 20000),			500);
		distribution_input_B.add( data_range (3000000, 5000000),	500);

		pInput->sw_a.set_mode(distribution_input_A);
		pInput->sw_b.set_mode(distribution_input_B);
		pInput->sw_cy.disable_randomization();
		pInput->sw_cy.write(false);

		timeout = GLOBAL_TIMEOUT;
	}
};

class packet_fulladdr_constraint_t_07
	: public packet_fulladdr_constraint_base_t
{
public:
	typedef sc_uint<BITWIDTH> data_single;
	scv_bag < data_single > distribution_input_A;
	scv_bag < data_single > distribution_input_B;

	SCV_CONSTRAINT_CTOR(packet_fulladdr_constraint_t_07)
	{
		distribution_input_A.add( (data_single) 1000, 20);
		distribution_input_A.add( (data_single) 5000, 40);
		distribution_input_A.add( (data_single) 5555, 40);
		distribution_input_A.add( (data_single) 6666, 40);
		distribution_input_B.add( (data_single) 1000, 20);
		distribution_input_B.add( (data_single) 4444, 40);
		distribution_input_B.add( (data_single) 7777, 40);
		distribution_input_B.add( (data_single) 9999, 40);

		pInput->sw_a.set_mode(distribution_input_A);
		pInput->sw_b.set_mode(distribution_input_B);
		pInput->sw_cy.disable_randomization();
		pInput->sw_cy.write(false);

		timeout = GLOBAL_TIMEOUT;
	}
};*/

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
		addSequence	(new testsequence_specialized_c < packet_uart_constraint_t_01 > 	(p_testsequences, 				5));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < packet_uart_constraint_t_02 > 	(p_testsequences, 				5));
		/*			|															|								|						*/
		//addSequence	(new testsequence_specialized_c < packet_fulladdr_constraint_t_03 > 	(p_testsequences, 				500));
		/*			|															|								|						*/
		//addSequence	(new testsequence_specialized_c < packet_fulladdr_constraint_t_04 > 	(p_testsequences, 				250));
		/*			|															|								|						*/
		//addSequence	(new testsequence_specialized_c < packet_fulladdr_constraint_t_05 > 	(p_testsequences, 				250));
		/*			|															|								|						*/
		//addSequence	(new testsequence_specialized_c < packet_fulladdr_constraint_t_06 > 	(p_testsequences, 				100));
		/*			|															|								|						*/
		//addSequence	(new testsequence_specialized_c < packet_fulladdr_constraint_t_07 > 	(p_testsequences, 				100));
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
	/*	user defined ports for DUT - connected to Driver-module	*/
	/*uart_data_port port_inputs_reference;
	sc_inout < bool > carry_in_reference;
	  */

	/*instanciate the initiator socket as "init_socket"*/
	tlm_utils::simple_initiator_socket<stimulator_m> reference_initiator_socket;

	sc_inout < double > timeout;
	sc_inout < unsigned int > testsequence_id;
	sc_inout < unsigned int > testcase_id;


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
	//scv_smart_ptr <dutInput_t> stim_value;

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

	void write_values_to_reference(packet_uart_constraint_base_t *p_values, unsigned int _cnt_testcases, unsigned int _testsequence_id)
	{
		/*create a new payload data structure*/
		tlm::tlm_generic_payload trans;
		struct packet_uart_data_to_reference data;

		/*time delay simulated by each transaction*/
		sc_time delay = sc_time(5, SC_PS);

		uint64_t addr;

		int response = 0;

		/*1st, set the command type*/
		trans.set_command(tlm::TLM_WRITE_COMMAND);/*There exist TLM_WRITE_COMMAND, TLM_READ_COMMAND and TLM_IGNORE_COMMAND which can be used to point to extensions*/
		/*2nd which device to call?*/
		addr = BASE_ADDR;
		trans.set_address(addr);
		/*3rd the data length*/
		trans.set_data_length(sizeof(struct packet_uart_data_to_reference));
		/*4th the data itself*/
		data.packet.sw_data_rx = p_values->pInput->sw_data_rx;
		data.packet.sw_data_tx = p_values->pInput->sw_data_tx;
		data.packet.sw_reset = p_values->pInput->sw_data_tx;
		data.packet.sw_rx_enable = p_values->pInput->sw_rx_enable;
		data.packet.sw_tx_enable = p_values->pInput->sw_tx_enable;
		data.packet.sw_ld_tx_data = p_values->pInput->sw_ld_tx_data;
		data.packet.sw_uld_rx_data = p_values->pInput->sw_uld_rx_data;

		data.cnt_testcases = _cnt_testcases;
		data.testsequ_id = _testsequence_id;
		data.timeout = p_values->timeout.to_seconds();

		/*info*/
		//cout << "Writing data:" << dec << data <<"@address:"<< hex <<addr<<"\n";

		trans.set_data_ptr((unsigned char *)&data);
		/*5th set the response value to incomplete*/
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

		/*6th call blocking transport*/
		reference_initiator_socket->b_transport(trans, delay);

		/*evaluate call response*/
		response = trans.get_response_status();
		switch(response) {
				case tlm::TLM_OK_RESPONSE:
					break;
				default:
					cout <<"Initiator WRITE: TLM_RESPONSE:"<<dec<<response<<"\n";
					break;

		};

		// for compatibility reasons
		timeout.write( p_values->timeout.to_seconds() );
		testcase_id.write(_cnt_testcases);
		testsequence_id.write(_testsequence_id);

		/*done*/

	}

	/*	SystemC module thread for stimulator	*/
	void stimulator_thread (void);


private:
	/*	extracted number of testsequences	*/
	unsigned int numOfTestsequences;
	/*	modules root element for list of testsequences	*/
	testseq_collectionentry_c testsequences;
};

#endif /* STIMULATOR_CONFIG_H_ */

/*///////////////////////////////////////////////////////////////////////////////////////
 * stimulator_config.h
 */
