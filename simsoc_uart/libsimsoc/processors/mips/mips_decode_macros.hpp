//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_DECODE_MACROS_HPP
#define MIPS_DECODE_MACROS_HPP
#include <stdint.h>

namespace simsoc {

  inline void MIPS_I_FORMAT(const uint32_t instr, uint8_t &s, uint8_t &t, uint32_t &i)
  {
    i = instr & 0xffff;
    if (i & 0x8000)
      i|= 0xffff0000;
    t = (instr >> 16) & 0x1f;
    s = (instr >> 21) & 0x1f;
  }

  inline void MIPS_IU_FORMAT(const uint32_t instr, uint8_t &s, uint8_t &t, uint32_t &i)
  {
    i = instr & 0xffff;
    t = (instr >> 16) & 0x1f;
    s = (instr >> 21) & 0x1f;

  }

  inline void MIPS_R_FORMAT(const uint32_t instr, uint8_t &s, uint8_t &t, uint8_t &d, uint8_t &a)
  {
    s = (instr >> 21) & 0x1f;
    t = (instr >> 16) & 0x1f;
    d = (instr >> 11) & 0x1f;
    a = (instr >> 6)  & 0x1f;

  }

  inline void MIPS_FP_FORMAT(const uint32_t instr, uint8_t &s, uint8_t &c, uint8_t &d)
  {
    s = (instr >> 21) & 0x1f;
    c = (instr >> 18) & 0x7;
    d = (instr >> 11) & 0x1f;
  }

  inline void MIPS_BC_FORMAT(const uint32_t instr, uint8_t &c, uint16_t &f){
    c = (instr >> 18) & 0x7;
    f = instr & 0xffff;
  }


  inline void MIPS_J_FORMAT(const uint32_t instr, uint32_t &i)
  {
    i = instr & 0x3ffffff;
  }

  inline void MIPS_BREAK_FORMAT(const uint32_t instr, uint32_t &c)
  {
    c = (instr >> 6)&0xfffff;
  }

  inline void MIPS_TEQ_FORMAT(const uint32_t instr, uint8_t &s, uint8_t &t, int32_t &c)
  {
    s = (instr >> 21) & 0x1f;
    t = (instr >> 16) & 0x1f;
    c = (instr >> 6) & 0x3ff;
  }

  inline void MIPS_SDBBP_FORMAT(const uint32_t instr, uint32_t &code)
  {
    code = (instr >> 5) & 0xfffff;
  }

  inline void MIPS_MFC_FORMAT(const uint32_t instr, uint8_t &t, uint8_t &d, uint16_t &s)
  {
    t = (instr >> 16)&0x1f;
    d = (instr >> 11)&0x1f;
    s = instr & 0x7;
  }

  inline void MIPS_WAIT_FORMAT(const uint32_t instr, uint32_t &p)
  {
    p = (instr >> 6)& 0x7ffff;
  }

} // namespace simsoc

#endif // MIPS_DECODE_MACROS_HPP
