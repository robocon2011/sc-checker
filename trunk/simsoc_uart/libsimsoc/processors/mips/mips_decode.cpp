//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mips_decode.tpp"

namespace simsoc {

  template MIPS_Instruction<BUS32>* mipsDecode<BUS32>(uint32_t instr);

  template MIPS_Instruction<BUS64>* mipsDecode<BUS64>(uint32_t instr);

} // namespace simsoc
