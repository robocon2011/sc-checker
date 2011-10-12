//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_UTILS_HPP
#define PPC_UTILS_HPP

#include "ppc_processor.hpp"

namespace simsoc {

  static const uint32_t ppc_cmp_and_mask[8] = {
    0x0fffffff,
    0xf0ffffff,
    0xff0fffff,
    0xfff0ffff,
    0xffff0fff,
    0xfffff0ff,
    0xffffff0f,
    0xfffffff0
  };

  static inline void ppc_update_cr0(PPC_Processor &proc, const uint8_t rt) {
    proc.cpu.cr &= 0x0fffffff;
    if (!proc.cpu.gpr[rt]) {
      proc.cpu.cr |= CR_CR0_EQ;
    } else if (proc.cpu.gpr[rt] & 0x80000000) {
      proc.cpu.cr |= CR_CR0_LT;
    } else {
      proc.cpu.cr |= CR_CR0_GT;
    }
    if (proc.cpu.xer & XER_SO)
      proc.cpu.cr |= CR_CR0_SO;
  }

  static inline bool ppc_carry(const uint32_t a,
                               const uint32_t b,
                               const uint32_t c) {
    return (((a+b) < a) || ((a+b+c) < c));
  }

  static inline uint32_t ppc_word_rotl(uint32_t data, int n) {
    n &= 0x1f; // n = n%32
    return (data << n) | (data >> (32-n));
  }

  static inline uint32_t ppc_mask(int MB, int ME) {
    uint32_t mask;
    if (MB <= ME) {
      if (ME-MB == 31)
        mask = 0xffffffff;
      else
        mask = ((1<<(ME-MB+1))-1)<<(31-ME);
    }
    else
      mask = ppc_word_rotl((1<<(32-MB+ME+1))-1, 31-ME);
    return mask;
  }

} // namespace simsoc

#endif //PPC_UTILS_HPP
