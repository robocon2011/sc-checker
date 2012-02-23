#include "uart_tlm.hpp"

/*usually this functin will model the hardware behaviour*/
void uart_tlm::uart_method(void) {
		
	/*usually you would add som hw behaviour here*/
	while(1)
	{
		wait(receive_event);

		cout <<"uart_tlm::uart_method called at" <<sc_time_stamp() << "\n";

		cout << "data.cnt_testcases = " << data.cnt_testcases << endl;
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

