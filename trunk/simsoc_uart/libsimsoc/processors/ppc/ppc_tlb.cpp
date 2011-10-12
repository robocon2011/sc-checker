//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <cassert>
#include "libsimsoc/processors/ppc/ppc_tlb.hpp"
#include "libsimsoc/processors/ppc/ppc_mmu.hpp"

namespace simsoc {

//------------------------------------------------------------------
PPC_TLB::PPC_TLB():
  TLB<BUS32>("PPC_TLB", 0){}


} // namespace simsoc
