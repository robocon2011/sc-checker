//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mipsis_arithmetic.hpp"

namespace simsoc {

  template <>
  void MIPS_slt<uint32_t>::exec(MIPS_Processor<uint32_t> &proc){
    if (((int32_t)proc.regs[rs]) < ((int32_t)proc.regs[rt]))
      proc.regs[rd] = 1;
    else
      proc.regs[rd] = 0;
    proc.pc += 4;
  }

  template <>
  void MIPS_slt<uint64_t>::exec(MIPS_Processor<uint64_t> &proc){
    if (((int64_t)proc.regs[rs]) < ((int64_t)proc.regs[rt]))
      proc.regs[rd] = 1;
    else
      proc.regs[rd] = 0;
    proc.pc += 4;
  }

  template <>
  void MIPS_slti<uint32_t>::exec(MIPS_Processor<uint32_t> &proc){
    if ( (int32_t)proc.regs[rs] < (int32_t)immed)
      proc.regs[rt] = 1;
    else
      proc.regs[rt] = 0;
    proc.pc += 4;
  }

  template <>
  void MIPS_slti<uint64_t>::exec(MIPS_Processor<uint64_t> &proc){
    if ((int64_t)proc.regs[rs] < (int64_t)sign_ext<uint64_t>(immed))
      proc.regs[rt] = 1;
    else
      proc.regs[rt] = 0;
    proc.pc += 4;
  }

} // namespace simsoc
