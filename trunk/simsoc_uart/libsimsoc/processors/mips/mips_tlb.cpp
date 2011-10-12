//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mips_tlb.tpp"

namespace simsoc {

template class MIPS_TLBEntry<BUS32>;

template class MIPS_TLB<BUS32>;

template class MIPS_TLBEntry<BUS64>;

template class MIPS_TLB<BUS64>;

}
