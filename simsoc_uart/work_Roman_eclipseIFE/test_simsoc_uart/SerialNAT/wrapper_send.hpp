//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef WRAPPER_SEND_HPP
#define WRAPPER_SEND_HPP

#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/interfaces/tlm_signal.hpp"
#include "libsimsoc/module.hpp"

class WrapperSend: public simsoc::Module,
                   public simsoc::SignalTarget<bool> {
public:

  SC_HAS_PROCESS(WrapperSend);
  WrapperSend(sc_core::sc_module_name name,
              uint32_t start, uint32_t size);

  void signal(bool);
  void compute();

  const uint32_t START;
  const uint32_t SIZE;

  sc_core::sc_event it_event;

  simsoc::RW_InitiatorPort rw_port;
  simsoc::SignalTargetPort<bool> it_signal;
};

#endif // WRAPPER_SEND_HPP
