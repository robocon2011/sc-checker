//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_DECODE_HPP
#define PPC_DECODE_HPP

#include "libsimsoc/processors/ppc/ppcis.hpp"

namespace simsoc {

  typedef PPC_Instruction * (*ppc_func) (uint32_t instr);

  PPC_Instruction * ppcDecode(uint32_t instr);

  //-----------------------------------------------------

  inline void PPC_I_FORM(const uint32_t &instr, uint32_t &li) {
    li = instr & 0x3fffffc;
    if (li&0x02000000)
      li |= 0xfc000000;

  }

  inline void PPC_B_FORM(const uint32_t &instr, uint8_t &bo, uint8_t &bi, uint32_t &bd) {
    bo = (instr >> 21) & 0x1f;
    bi = (instr >> 16) & 0x1f;
    bd = (instr) & 0x0fffc;
    if (bd & 0x8000)
      bd |= 0xffff0000;
  }

  inline void PPC_SC_FORM(const uint32_t &instr, uint8_t &lev) {
    lev = (instr >> 5) & 0x3f;
  }

  /*inline void PPC_D_FORM(const uint32_t &instr, uint8_t &rt, uint8_t &ra, uint32_t &d) {
    rt = (instr >> 21) & 0x1f;
    ra = (instr >> 16) & 0x1f;
    d = instr & 0x0ffff;
    }*/

  inline void PPC_D_FORM_SI(const uint32_t &instr, uint8_t &rt, uint8_t &ra, uint32_t &d) {
    rt = (instr >> 21) & 0x1f;
    ra = (instr >> 16) & 0x1f;
    d = instr & 0x0ffff;
    if (d & 0x8000)
      d |= 0xffff0000;
  }

  inline void PPC_D_FORM_UI(const uint32_t &instr, uint8_t &rt, uint8_t &ra, uint32_t &d) {
    rt = (instr >> 21) & 0x1f;
    ra = (instr >> 16) & 0x1f;
    d = instr & 0x0ffff;
  }

  inline void PPC_DS_FORM(const uint32_t &instr, uint8_t &rt, uint8_t &ra, uint32_t &ds) {
    rt = (instr >> 21) & 0x1f;
    ra = (instr >> 16) & 0x1f;
    ds = (instr) & 0x00fffc;
    if (ds & 0x8000)
      ds |= 0xffff0000;
  }

  inline void  PPC_X_FORM(const uint32_t &instr, uint8_t &rt, uint8_t &ra, uint8_t &rb) {
    rt = (instr >> 21) & 0x1f;
    ra = (instr >> 16) & 0x1f;
    rb = (instr >> 11) & 0x1f;
  }


  inline void PPC_XL_FORM(const uint32_t &instr, uint8_t &bt, uint8_t &ba, uint8_t &bb) {
    bt = (instr >> 21) & 0x1f;
    ba = (instr >> 16) & 0x1f;
    bb= (instr >> 11) & 0x1f;
  }inline void PPC_XFX_FORM(const uint32_t &instr, uint8_t &rt, uint16_t &spr) {
    rt = (instr >> 21) & 0x1f;
    spr = (instr >> 11) & 0x3ff;
  }


  inline void PPC_XFL_FORM(const uint32_t &instr, uint8_t &flm, uint8_t &frb) {
    flm = (instr >> 17) & 0x0ff;
    frb = (instr >> 11) & 0x1f;
  }


  inline void PPC_XS_FORM(const uint32_t &instr, uint8_t &rs, uint8_t &ra, uint8_t &sh) {
    rs = (instr >> 21) & 0x1f;
    ra = (instr >> 16) & 0x1f;
    sh = (instr >> 11) & 0x1f;

  }


  inline void PPC_XO_FORM(const uint32_t &instr, uint8_t &rt, uint8_t &ra, uint8_t &rb) {
    rt= (instr >> 21) & 0x1f;
    ra = (instr >> 16) & 0x1f;
    rb = (instr >> 11) & 0x1f;
  }


  inline void PPC_A_FORM(const uint32_t &instr, uint8_t &frt, uint8_t &fra, uint8_t &frb, uint8_t &frc) {
    frt = (instr>>21)&0x1f;
    fra = (instr>>16)&0x1f;
    frb = (instr>>11)&0x1f;
    frc = (instr>>6)&0x1f;
  }


  inline void PPC_M_FORM(const uint32_t &instr, uint8_t &rs, uint8_t &ra, uint8_t &rb, uint8_t &mb, uint8_t &me) {
    rs = (instr >> 21) & 0x1f;
    ra = (instr >> 16) & 0x1f;
    rb = (instr >> 11) & 0x1f;
    mb = (instr >> 6) & 0x1f;
    me = (instr >> 1) & 0x1f;
  }


  inline void PPC_MD_FORM(const uint32_t &instr, uint8_t &rs, uint8_t &ra, uint8_t &sh, uint8_t &mb) {
    rs = (instr >>21) & 0x1f;
    ra = (instr >>16) & 0x1f;
    sh = (instr >>11) & 0x1f;
    mb = (instr >>5) & 0x3f;
  }


  inline void PPC_MDS_FORM(const uint32_t &instr, uint8_t &rs, uint8_t &ra, uint8_t &rb, uint8_t &mb) {
    rs = (instr >> 21) & 0x1f;
    ra = (instr >> 16) & 0x1f;
    rb = (instr >> 11) & 0x1f;
    mb = (instr>> 5) & 0x3f;
  }

  //big endia and little endia translate function
  static inline  uint16_t half_be_le_translate(const uint16_t data) {
    return (data>>8) | (data<<8);
  }

  static inline  uint32_t word_be_le_translate(const uint32_t data) {//be : big endian, le : little endian

    return (data<<24) | ((data&0xff00) << 8)
      | ((data&0xff0000) >> 8)
      | (data>>24);
  }

  static inline uint64_t dword_be_le_translate(const uint64_t data){
    return (((uint64_t)word_be_le_translate(data)) << 32) | (uint64_t)word_be_le_translate(data >> 32);
  }

} // namespace simsoc

#endif //PPC_DECODE_HPP
