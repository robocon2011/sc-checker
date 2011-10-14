//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "wrapper_receive.hpp"
#include "uart_constants.hpp"
#include "libsimsoc/display.hpp"

using namespace std;
using namespace sc_core;
using namespace simsoc;

WrapperReceive::WrapperReceive(sc_core::sc_module_name name,
                               uint32_t dest):
  Module(name),
  DEST(dest),
  it_signal(false)
{
  info() <<"constructor called.\n";
  it_signal(*this);
  SC_THREAD(compute);
}

void WrapperReceive::signal(bool b) {
  info() <<"it = " <<dec <<b <<endl;
  if (b)
    it_event.notify();
}

void WrapperReceive::compute() {
  info() <<"start compute SC_THREAD.\n";

  // enable IRQ from UART
  PayLoad pl;
  pl.set_streaming_width(4);

  uint8_t value=0;

  value=UART_IER_DATA_AVAILABLE;
  pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
  pl.set_payload(UART_BASE+UART_IER,(unsigned char*)(&value),1);
  rw_port->trans_write_data(pl);

  // enable fifo, set trigger level to 14
  value=7|(3<<6);
  pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
  pl.set_payload(UART_BASE+UART_FCR,(unsigned char*)(&value),1);
  rw_port->trans_write_data(pl);

  char c = 0;
  size_t n = 0;
  while (c!=EOT) {

    // set RTS to 1
    value=0;
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(UART_BASE+UART_MCR,(unsigned char*)(&value),1);
    rw_port->trans_read_data(pl);

    value|=UART_MCR_RTS;
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(UART_BASE+UART_MCR,(unsigned char*)(&value),1);
    rw_port->trans_write_data(pl);

    // wait data
    value=0;
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(UART_BASE+UART_LSR,(unsigned char*)(&value),1);
    rw_port->trans_read_data(pl);

    while (!(value & UART_LSR_DATA_AVAILABLE)) {
      while(!it_signal)
        wait(it_event);
      value=0;
      pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
      pl.set_payload(UART_BASE+UART_LSR,(unsigned char*)(&value),1);
      rw_port->trans_read_data(pl);
    }

    //  set RTS to 0
    value=0;
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(UART_BASE+UART_MCR,(unsigned char*)(&value),1);
    rw_port->trans_read_data(pl);

    value &=~UART_MCR_RTS;
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(UART_BASE+UART_MCR,(unsigned char*)(&value),1);
    rw_port->trans_write_data(pl);


    // get the characters from the fifo
    value=0;
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_payload(UART_BASE+UART_LSR,(unsigned char*)(&value),1);
    rw_port->trans_read_data(pl);

    while (value & UART_LSR_DATA_AVAILABLE) {
      pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
      pl.set_payload(UART_BASE+UART_RBR,(unsigned char*)(&c),1);
      rw_port->trans_read_data(pl);
      if(c==EOT)
        break;
      pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
      pl.set_payload(DEST+n,(unsigned char*)(&c),1);
      rw_port->trans_write_data(pl);
      ++n;

      value=0;
      pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
      pl.set_payload(UART_BASE+UART_LSR,(unsigned char*)(&value),1);
      rw_port->trans_read_data(pl);
    }
  }
}
