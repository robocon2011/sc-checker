//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mipsis_visitor.tpp"
#include <libsimsoc/processors/common.hpp>

namespace simsoc {

  template class MIPS_InstructionVisitor<BUS32>;

  template class MIPS_InstructionVisitor<BUS64>;

} // namespace simsoc
