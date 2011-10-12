//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/processors/mips/mips_debugger.tpp"

namespace simsoc {

  template class MIPS_Debugger<BUS32>;
  template class MIPS_Debugger<BUS64>;
  
}
