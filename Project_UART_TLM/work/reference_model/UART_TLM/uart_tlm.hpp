/*
 * 	Filename:	uart_tlm.hpp
 *
 * 	Version:	---
 *
 *  Created on:	2012/02/28
 *
 *  Author: 	Roman SOLLBOECK
 *
 *  Project:	SystemC Checker
 *  Submodule:	UART_TLM
 *
 *  purpose:	TLM Reference Model for UART RTL Design
 *
 *  History:	2012/02/28: first executable version implemented
 *  			2012/03/01: comments added
 */


#ifndef UART_TLM_HPP_
#define UART_TLM_HPP_

#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc.h>


using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include "../../global.h"

/*
 *	structname:	uart_tlm
 *	purpose:	UART module incorporating TLM sockets
 *				for TLM-based communication
 *
 */
struct uart_tlm:sc_module
{
public:
	/* TLM initiator socket for module output */
	tlm_utils::simple_initiator_socket<uart_tlm> uart_initiator_socket;
	/* TLM target socket for input data */
	tlm_utils::simple_target_socket<uart_tlm> uart_target_socket;

private:
	/*	internal receive event for triggering behavioral functions */
	sc_event receive_event;
	packet_uart_data_to_scoreboard data;
	packet_uart_data_to_scoreboard data_to_scbd;
	uint32_t rx_reg_new, tx_new, ctrl_old, ctrl_new;
	uint32_t mem[MEMSIZE_UART];
	void uart_method(void);
	void uart_tlm_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);


public:
	SC_HAS_PROCESS(uart_tlm);
	uart_tlm(sc_module_name name_);
		
	
	~uart_tlm() {}
	
};

#endif /* UART_TLM_HPP_ */

/*///////////////////////////////////////////////////////////////////////////////////////
 * uart_tlm.hpp
 */

