//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mipsis_dyntrans.tpp"

namespace simsoc {

  template class MIPS_ExecuteBlock<BUS32>;
  template class MIPS_ExecuteBlock<BUS64>;
  template class MIPS_TranslateBlock<BUS32>;
  template class MIPS_TranslateBlock<BUS64>;

} // namespace simsoc
