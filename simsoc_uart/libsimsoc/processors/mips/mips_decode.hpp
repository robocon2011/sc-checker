//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_DECODE_HPP
#define MIPS_DECODE_HPP

#include "mips_base.hpp"

namespace simsoc {

  template <typename word_t>
  MIPS_Instruction<word_t>* mipsDecode(uint32_t instr);
  // all MIPS instructions are 32 bits
  // therefore this function is not parameterized by template S
  // However the decoder returns an instruction whose data can be 32 or 64 bits.

  // We do not include "mips_decoder.tpp" here,
  // because the user can only use a restricted number of parameter values.
  // Code for these parameter values is created in "mips_decoder.cpp".

} // namespace simsoc

#endif // MIPS_DECODE_HPP
