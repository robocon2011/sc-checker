//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef WRAPPER_RECEIVE_HPP
#define WRAPPER_RECEIVE_HPP

#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/interfaces/tlm_signal.hpp"
#include "libsimsoc/module.hpp"

class WrapperReceive: public simsoc::Module,
                      public simsoc::SignalTarget<bool> {
public:

  SC_HAS_PROCESS(WrapperReceive);
  WrapperReceive(sc_core::sc_module_name name,
                 uint32_t dest);

  void check(char prev, char current);
  void signal(bool);
  void compute();

  const uint32_t DEST;

  sc_core::sc_event it_event;

  simsoc::RW_InitiatorPort rw_port;
  simsoc::SignalTargetPort<bool> it_signal;
};

#endif // WRAPPER_RECEIVE_HPP
