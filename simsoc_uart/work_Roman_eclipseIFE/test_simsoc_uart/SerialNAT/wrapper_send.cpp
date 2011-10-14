//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "wrapper_send.hpp"
#include "uart_constants.hpp"
#include "libsimsoc/display.hpp"

using namespace std;
using namespace sc_core;
using namespace simsoc;

WrapperSend::WrapperSend(sc_core::sc_module_name name,
                         uint32_t start, uint32_t size):
  Module(name),
  START(start), SIZE(size),
  it_signal(false)
{
  info() <<"constructor called.\n";
  it_signal(*this);
  SC_THREAD(compute);
}

void WrapperSend::signal(bool b) {
  info() <<"it = " <<dec <<b <<endl;
  if (b)
    it_event.notify();
}

void WrapperSend::compute() {
  info() <<"start compute SC_THREAD.\n";

  PayLoad pl;
  pl.set_streaming_width(4);

  uint8_t value=0;

  // enable IRQ from UART
  value=UART_IER_MSR_CHANGE;
  pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
  pl.set_payload(UART_BASE+UART_IER,(unsigned char*)(&value),1);
  rw_port->trans_write_data(pl);

  // send the alphabet N times
  for (size_t i = 0; i<SIZE; ++i) {
    value=0;
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(UART_BASE+UART_MSR,(unsigned char*)(&value),1);
    rw_port->trans_read_data(pl);

    while(!(value & UART_MSR_CTS))
    {
      while(!it_signal)
        wait(it_event);
      value=0;
      pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
      pl.set_payload(UART_BASE+UART_MSR,(unsigned char*)(&value),1);
      rw_port->trans_read_data(pl);
    }

    value=0;
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(START+i,(unsigned char*)(&value),1);
    rw_port->trans_read_data(pl);

    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(UART_BASE+UART_THR,(unsigned char*)(&value),1);
    rw_port->trans_write_data(pl);
  }

 // wait for CTS==1
  value=0;
  pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
  pl.set_payload(UART_BASE+UART_MSR,(unsigned char*)(&value),1);
  rw_port->trans_read_data(pl);

  while(!(value & UART_MSR_CTS))
  {
    while(!it_signal)
      wait(it_event);
    value=0;
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(UART_BASE+UART_MSR,(unsigned char*)(&value),1);
    rw_port->trans_read_data(pl);
  }

  // send "End of Transmission" character (sixteen times)
  for (size_t i = 0; i<16; ++i)
  {
    value=EOT;
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(UART_BASE+UART_THR,(unsigned char*)(&value),1);
    rw_port->trans_write_data(pl);
  }
}
