/*
 * 	Filename:	uart_tlm.cpp
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

#include "uart_tlm.hpp"

/*
 * **************************************************************
 *
 * functionname:	uart_tlm (constructor)
 * purpose:			Constructor for sc_module uart_tlm
 * parameters:		none
 * returnvalue:		none
 *
 * **************************************************************
 */
SC_HAS_PROCESS(uart_tlm);
uart_tlm::uart_tlm(sc_module_name name_) :sc_module(name_),
		uart_initiator_socket("uart_initiator_socket"),
		uart_target_socket("uart_target_socket")
{
	SC_METHOD(uart_method);
	sensitive << receive_event;
	dont_initialize();
	
	/*	initialize UART memory */
	for (unsigned int i = 0; i < MEMSIZE_UART; i++)
	{
		mem[i] = 0;
	}
	
	/*	register blocking transport method for receiving transactions */
	uart_target_socket.register_b_transport(this, &uart_tlm::uart_tlm_b_transport);
}

/*
 * **************************************************************
 *
 * functionname:	uart_method
 * purpose:			Function for actual behavior of UART model
 * parameters:		none
 * returnvalue:		none
 *
 * **************************************************************
 */
void uart_tlm::uart_method(void) {
	/*	Generic Payload container for storage of transaction data */
	tlm::tlm_generic_payload trans;

	sc_time delay = SC_ZERO_TIME;
	uint64_t addr;
	int response = 0;

	/*	perform only when CTRL data were changed
	 * 	TODO: Sollte anders gelöst werden */

	// DEBUG
	cout << this->name() << ", ctrl_old = " << ctrl_old << ", ctrl_new = " << ctrl_new << endl;

//	if (ctrl_old != ctrl_new)
	{
		/*	highest priority for reset signal */
		if (ctrl_new & UART_CTRL_RESET)
		{
			mem[(UART_BYTE_OFFS_RX_REG/sizeof(uint32_t))] = 0u;
			mem[(UART_BYTE_OFFS_TX_REG/sizeof(uint32_t))] = 0u;
		}
		/*	Unload of RX-Register */
		else if (	( ctrl_new & UART_CTRL_ULD_RX_DATA ) &&
					( ctrl_new & UART_CTRL_RX_ENABLE ) )
		{
			mem[(UART_BYTE_OFFS_RX_REG/sizeof(uint32_t))] = 0u;
		}
		/*	RX-Enable, store received data to UART RX-register */
		else if ( ctrl_new & UART_CTRL_RX_ENABLE )
		{

			// DEBUG
			cout << this->name() << ", else if ( ctrl_new & UART_CTRL_RX_ENABLE ) entered" << endl;

			mem[(UART_BYTE_OFFS_RX_REG/sizeof(uint32_t))] = rx_reg_new;
		}
		/*	Load of TX-Register */
		else if (	( ctrl_new & UART_CTRL_TX_ENABLE ) &&
					( ctrl_new & UART_CTRL_LD_TX_DATA) )
		{
			mem[(UART_BYTE_OFFS_TX_REG/sizeof(uint32_t))] = tx_new;
		}
		else
		{
			cout << "error: no valid control configuration or NULL: " << ctrl_new << endl;
		}
	}

	/*	prepare payload container for transaction */
	trans.set_command(tlm::TLM_WRITE_COMMAND);/*There exist TLM_WRITE_COMMAND, TLM_READ_COMMAND and TLM_IGNORE_COMMAND which can be used to point to extensions*/
	addr = SCOREBOARD_BASE_ADDR;
	trans.set_address(addr);
	trans.set_data_length(sizeof(uint32_t) * MEMSIZE_UART);
	/*	provide Memory content of UART to target */
	trans.set_data_ptr((unsigned char *)&mem[0]);
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
	uart_initiator_socket->b_transport(trans, delay);

	/*	evaluate call response */
	response = trans.get_response_status();
	switch(response) {
			case tlm::TLM_OK_RESPONSE:
				break;
			default:
				cout <<"Initiator WRITE: TLM_RESPONSE:"<<dec<<response<<"\n";
				break;
	}
}


/*
 * **************************************************************
 *
 * functionname:	uart_tlm_b_transport
 * purpose:			Blocking transport function for TLM target socket connected to Stimulator
 * 					Implementation required for TLM simple socket
 * parameters:		pointer to generic payload container
 * 					value for transport time delay
 * returnvalue:		none
 *
 * **************************************************************
 */
void uart_tlm::uart_tlm_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t)
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
			adr = ( adr - UART_BASE_ADDR ) >> 3; // Address in Bytes
			/*	Transaction points directly to certain UART registers */
			switch(adr)
			{
				/*	Random RX-value received, store in buffer and evaluate RX-enable afterwards */
				case UART_BYTE_OFFS_RX_REG:
					rx_reg_new = (uint32_t)*ptr;

					// DEBUG
					cout << this->name() << ", b_transport: rx_reg_new = " << rx_reg_new << endl;

					trans.set_response_status(tlm::TLM_OK_RESPONSE );
					break;
				/*	Random TX-value received, store in TX-register */
				case UART_BYTE_OFFS_TX_REG:
					tx_new = (uint32_t)*ptr;
					trans.set_response_status(tlm::TLM_OK_RESPONSE );
					break;
				/*	UART control bits received, store in CTRL register
				 * 	and keep old value in buffer */
				case UART_BYTE_OFFS_CTRL:
					ctrl_old = mem[(UART_BYTE_OFFS_CTRL/sizeof(uint32_t))];
					memcpy((uint32_t *)&mem[(UART_BYTE_OFFS_CTRL/sizeof(uint32_t))], ptr, len);
					ctrl_new = mem[(UART_BYTE_OFFS_CTRL/sizeof(uint32_t))];
					trans.set_response_status(tlm::TLM_OK_RESPONSE );
					receive_event.notify();
					break;
				default:
					cout << "addr ERROR\n";
					trans.set_response_status( tlm::TLM_COMMAND_ERROR_RESPONSE);
					break;

			}
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
 * uart_tlm.cpp
 */

