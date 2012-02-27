#define SC_INCLUDE_DYNAMIC_PROCESSES
#include <systemc.h>


using namespace sc_core;
using namespace sc_dt;
using namespace std;

#include <tlm.h>
/*std convinience sockets, which encapsulate the explicite inheritance of interfaces*/
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

#include "../../global.h"

#include "common.hpp"

/*This is a usual SystemC module*/
struct uart_tlm:sc_module {
	
public:
	/*instanciate the initiator socket as "init_socket"*/	
	tlm_utils::simple_initiator_socket<uart_tlm> uart_initiator_socket;
	/*instanciate the target socket as "init_socket"*/
	tlm_utils::simple_target_socket<uart_tlm> uart_target_socket;

private:	
	/*implemented in initiator.cpp*/
	sc_event receive_event;
	packet_uart_data_to_scoreboard data;
	packet_uart_data_to_scoreboard data_to_scbd;
	sc_uint<DATABITS> rx_reg_new, tx_new;
	uint32_t ctrl_old, ctrl_new;
	uint32_t mem[MEMSIZE_UART];
	void uart_method(void);
	void uart_tlm_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t);


public:
/*register process to be called when module is scheduled to simulator*/
SC_HAS_PROCESS(uart_tlm);
	
/*A usual SystemC constructor*/
uart_tlm(sc_module_name name_) :sc_module(name_),
		uart_initiator_socket("uart_initiator_socket"),
		uart_target_socket("uart_target_socket") {
	/*register module behavorial description*/
	SC_METHOD(uart_method);
	sensitive << receive_event;
	dont_initialize();

	for (unsigned int i = 0; i < MEMSIZE_UART; i++)
	{
		mem[i] = 0;
	}

	uart_target_socket.register_b_transport(this, &uart_tlm::uart_tlm_b_transport);
	/*do the usual initialization stuff here*/
	
}	
		
	
~uart_tlm() {}
	
};
