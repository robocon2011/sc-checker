#include "uart_tlm.hpp"

/*usually this functin will model the hardware behaviour*/
void uart_tlm::uart_method(void) {
		
	/*usually you would add som hw behaviour here*/
	while(1)
	{
		tlm::tlm_generic_payload trans;
		struct packet_uart_data_to_reference data;

		/*time delay simulated by each transaction*/
		sc_time delay = sc_time(5, SC_PS);

		uint64_t addr;

		int response = 0;

		wait(receive_event);

		cout <<"uart_tlm::uart_method called at" <<sc_time_stamp() << "\n";
		/*create a new payload data structure*/


		/*1st, set the command type*/
		trans.set_command(tlm::TLM_WRITE_COMMAND);/*There exist TLM_WRITE_COMMAND, TLM_READ_COMMAND and TLM_IGNORE_COMMAND which can be used to point to extensions*/
		/*2nd which device to call?*/
		addr = BASE_ADDR;
		trans.set_address(addr);
		/*3rd the data length*/
		trans.set_data_length(sizeof(struct packet_uart_data_to_reference));
		/*4th the data itself*/
		memcpy(&data_to_scbd,&data,sizeof(packet_uart_data_to_reference));

		/*info*/
		//cout << "Writing data:" << dec << data <<"@address:"<< hex <<addr<<"\n";

		trans.set_data_ptr((unsigned char *)&data_to_scbd);
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
		uart_initiator_socket->b_transport(trans, delay);

		/*evaluate call response*/
		response = trans.get_response_status();
		switch(response) {
				case tlm::TLM_OK_RESPONSE:
					break;
				default:
					cout <<"Initiator WRITE: TLM_RESPONSE:"<<dec<<response<<"\n";
					break;

		};
	}


}


/*required implementation of the b_transport method. this method is called by the initiator eventually*/
void uart_tlm::my_b_transport(tlm::tlm_generic_payload& trans, sc_core::sc_time& t) {
	
	
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
			memcpy((char *)&data,ptr,len);
			trans.set_response_status(tlm::TLM_OK_RESPONSE );
			receive_event.notify();
			break;
		case tlm::TLM_READ_COMMAND:
			adr = adr - BASE_ADDR;
			memcpy(ptr,(char *)&mem[adr],len);
			trans.set_response_status(tlm::TLM_OK_RESPONSE );
			break;
		default:
		cout << "ERROR\n";
		trans.set_response_status( tlm::TLM_COMMAND_ERROR_RESPONSE);
		break;
			
	}
	
}

