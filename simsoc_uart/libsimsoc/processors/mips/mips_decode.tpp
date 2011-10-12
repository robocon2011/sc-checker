//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Implementation of "mips_decode.hpp"
// This file is included only by "mips_decode.cpp"
#include "mips_decode.hpp"
#include "mips_decode_macros.hpp"
#include "mipsis.hpp"
#include "mipsis_branch.hpp"
#include "mipsis_arithmetic.hpp"
#include "mipsis_coprocessor.hpp"
#include "mipsis_loadstore.hpp"
#include <libsimsoc/display.hpp>

namespace simsoc {

  template <typename word_t>
  struct MIPS_DecodeTable {
    typedef MIPS_Instruction<word_t> * (* decode_func)(uint32_t);
    static const decode_func main_table[64];
  };

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_invalid(uint32_t instr) {
    return new MIPS_Undefined<word_t>("Undefined MIPS instruction!");
  }

  // main opcode 000 000

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_group0(uint32_t instr) {
    uint32_t ext = instr & 0x3f;

    switch (ext) {
    case   0 :
      switch ((instr>>6)&0xfffff){
      case  0 : return new MIPS_nop<word_t>();
      case  1 : return new MIPS_ssnop<word_t>();
      default : {
        uint8_t s,t,d,a;
        MIPS_R_FORMAT(instr,s,t,d,a);
        return new MIPS_sll<word_t>(t,d,a);
      }
      }
    case  1 : {
      uint8_t s,c,d;
      MIPS_FP_FORMAT(instr,s,c,d);
      return new MIPS_movf<word_t>(s,c,d);
    }
    case  2 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_srl<word_t>(t,d,a);
    }
    case   3 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_sra<word_t>(t,d,a);
    }
    case   4 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_sllv<word_t>(s,t,d);
    }

    case  6 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_srlv<word_t>(s,t,d);
    }
    case   7 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_srav<word_t>(s,t,d);
    }
    case   8 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_jr<word_t>(s,a);
    }
    case   9 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_jalr<word_t>(s,d,a);
    }
    case  10 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_movz<word_t>(s,t,d);
    }
    case  11 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_movn<word_t>(s,t,d);
    }
    case   12 : {
      uint32_t c;
      MIPS_BREAK_FORMAT(instr,c);
      return new MIPS_syscall<word_t>(c);
    }
    case   13 : {
      uint32_t c;
      MIPS_BREAK_FORMAT(instr,c);
      return new MIPS_break<word_t>(c);
    }
    case  15 : return new MIPS_sync<word_t>();
    case  16 : {
      uint8_t  s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_mfhi<word_t>(d);
    }
    case  17 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_mthi<word_t>(s);
    }
    case  18 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_mflo<word_t>(d);
    }
    case  19 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_mtlo<word_t>(s);
    }
    case  20 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dsllv<word_t>(s,t,d);
    }
    case  22: {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dsrlv<word_t>(s,t,d);
    }

    case  23: {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dsrav<word_t>(s,t,d);
    }
    case  24 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_mult<word_t>(s,t);
    }
    case  25 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_multu<word_t>(s,t);
    }
    case  26 :{
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_div<word_t>(s,t);
    }
    case  27 :{
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_divu<word_t>(s,t);
    }
    case  28: {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dmult<word_t>(s,t);
    }
    case  29: {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dmultu<word_t>(s,t);
    }
    case  30: {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_ddiv<word_t>(s,t);
    }
    case  31: {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_ddivu<word_t>(s,t);
    }
    case  32 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_add<word_t>(s,t,d);
    }
    case  33 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr, s,t,d,a);
      return new MIPS_addu<word_t>(s,t,d);
    }
    case  34  : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_sub<word_t>(s,t,d);
    }

    case  35 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_subu<word_t>(s,t,d);
    }
    case  36 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_and<word_t>(s,t,d);
    }
    case  37 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_or<word_t>(s,t,d);
    }
    case  38 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_xor<word_t>(s,t,d);
    }
    case  39 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_nor<word_t>(s,t,d);
    }
    case  42 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_slt<word_t>(s,t,d);
    }
    case  43 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_sltu<word_t>(s,t,d);
    }
    case  44: {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dadd<word_t>(s,t,d);
    }
    case  45: {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_daddu<word_t>(s,t,d);
    }
    case  46: {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dsub<word_t>(s,t,d);
    }
    case  47: {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dsubu<word_t>(s,t,d);
    }
    case  48 : {
      uint8_t s, t;
      int32_t c;
      MIPS_TEQ_FORMAT(instr,s,t,c);
      return new MIPS_tge<word_t>(s,t);
    }
    case  49 : {
      uint8_t s, t;
      int32_t c;
      MIPS_TEQ_FORMAT(instr,s,t,c);
      return new MIPS_tgeu<word_t>(s,t);
    }
    case  50 : {
      uint8_t s, t;
      int32_t c;
      MIPS_TEQ_FORMAT(instr,s,t,c);
      return new MIPS_tlt<word_t>(s,t);
    }
    case  51 : {
      uint8_t s, t;
      int32_t c;
      MIPS_TEQ_FORMAT(instr,s,t,c);
      return new MIPS_tltu<word_t>(s,t);
    }
    case  52 : {
      uint8_t s, t;
      int32_t c;
      MIPS_TEQ_FORMAT(instr,s,t,c);
      return new MIPS_teq<word_t>(s,t);
    }
    case  54 : {
      uint8_t s, t;
      int32_t c;
      MIPS_TEQ_FORMAT(instr,s,t,c);
      return new MIPS_tne<word_t>(s,t);
    }
    case  56 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dsll<word_t>(t,d,a);
    }
    case  58 : {
      switch ((instr>>21)&0x1){
      case  0 : {
        uint8_t s,t,d,a;
        MIPS_R_FORMAT(instr,s,t,d,a);
        return new MIPS_dsrl<word_t>(t,d,a);
      }
      case  1 : {
        uint8_t s,t,d,a;
        MIPS_R_FORMAT(instr,s,t,d,a);
        return new MIPS_drotr<word_t>(t,d,a);
      }
      }
    }
    case  59 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dsra<word_t>(t,d,a);
    }
    case  60 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dsll32<word_t>(t,d,a);
    }
    case  62 : {
      switch((instr>>21)&0x1){
      case 0 :  {
        uint8_t s,t,d,a;
        MIPS_R_FORMAT(instr,s,t,d,a);
        return new MIPS_dsrl32<word_t>(t,d,a);
      }
      case 1 :  {
        uint8_t s,t,d,a;
        MIPS_R_FORMAT(instr,s,t,d,a);
        return new MIPS_drotr32<word_t>(t,d,a);
      }
      }
    }
    case  63 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dsra32<word_t>(t,d,a);
    }
    }
    return mips_invalid<word_t>(instr);
  }
  //group 1  000 001

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_group1(uint32_t instr) {
    uint32_t ext = (instr >> 16) & 0x1f;

    switch (ext) {
    case   0 :  {
      uint8_t s,t;
      uint32_t o;
      MIPS_I_FORMAT(instr,s,t,o);
      int32_t offset = (int32_t) o << 2;
      return new MIPS_bltz<word_t>(s,offset);
    }
    case   1 : {
      uint8_t s,t;
      uint32_t o;
      MIPS_I_FORMAT(instr,s,t,o);
      int32_t offset = (int32_t) o << 2;
      return new MIPS_bgez<word_t>(s,offset);
    }
    case   2 : {
      uint8_t s,t;
      uint32_t o;
      MIPS_I_FORMAT(instr,s,t,o);
      int32_t offset = (int32_t) o << 2;
      return new MIPS_bltzl<word_t>(s,offset);
    }
    case   3 : {
      uint8_t s,t;
      uint32_t o;
      MIPS_I_FORMAT(instr,s,t,o);
      int32_t offset = (int32_t) o << 2;
      return new MIPS_bgezl<word_t>(s,offset);
    }
    case   8 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      int32_t imme = (int32_t) i;
      return new MIPS_tgei<word_t>(s,imme);
    }
    case   9 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      return new MIPS_tgeiu<word_t>(s,i);
    }
    case  10 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      int32_t imme = (int32_t)i;
      return new MIPS_tlti<word_t>(s,imme);
    }
    case  11 : {
      uint8_t s,t;
      uint32_t imme;
      MIPS_I_FORMAT(instr,s,t,imme);
      return new MIPS_tltiu<word_t>(s,imme);
    }
    case  12 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      int32_t imme = (int32_t) i;
      return new MIPS_teqi<word_t>(s,imme);
    }
    case  14 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      int32_t imme = (int32_t)i;
      return new MIPS_tnei<word_t>(s,imme);
    }
    case  16 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      uint32_t f = i<<2;
      return new MIPS_bltzl<word_t>(s,f);
    }
    case  17 :
      switch(instr >> 21){
      case 0 : {
        uint8_t s,t;
        uint32_t o;
        MIPS_I_FORMAT(instr,s,t,o);
        int32_t offset = (int32_t) o << 2;
        return new MIPS_bal<word_t>(s,offset);
      }
      default: {
        uint8_t s,t;
        uint32_t o;
        MIPS_I_FORMAT(instr, s,t,o);
        int32_t offset = (int32_t) o << 2;
        return new MIPS_bgezal<word_t>(s, offset);
      }
      }
    case  18 : {
      uint8_t s,t;
      uint32_t o;
      MIPS_I_FORMAT(instr,s,t,o);
      int32_t offset = (int32_t) o << 2;
      return new MIPS_bltzall<word_t>(s,offset);
    }
    case  19 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      uint32_t f = i<<2;
      return new MIPS_bgezall<word_t>(s,f);
    }
    }
    return mips_invalid<word_t>(instr);
  }

  //group2 000100
  template <typename word_t>
  MIPS_Instruction<word_t>*  mips_group2(uint32_t instr){
    uint32_t ext = (instr >> 16) & 0x3ff;
    switch (ext){
    case   0 : {
      uint8_t s, t;
      uint32_t o;
      MIPS_I_FORMAT(instr, s, t, o);
      int32_t offset = (int32_t) o << 2;
      return new MIPS_b<word_t>(offset);
    }
    default : {
      uint8_t s, t;
      uint32_t o;
      MIPS_I_FORMAT(instr,s,t,o);
      int32_t offset = (int32_t) o <<2;
      return new MIPS_beq<word_t>(s,t,offset);
    }
    }
    return mips_invalid<word_t>(instr);
  }

  //group3 010000
  template <typename word_t>
  MIPS_Instruction<word_t> * mips_group3(uint32_t instr) {
    uint32_t ext = instr & 0x3f;

    switch (ext) {
    case   1 : return new MIPS_tlbr<word_t>();
    case   2 : return new MIPS_tlbwi<word_t>();
    case   6 : return new MIPS_tlbwr<word_t>();
    case   8 : return new MIPS_tlbp<word_t>();
    case  24 : return new MIPS_eret<word_t>();
    case  31 : return new MIPS_deret<word_t>();
    case  32 : {
      uint32_t p;
      MIPS_WAIT_FORMAT(instr,p);
      return new MIPS_wait<word_t>(p);
    }
    default  : switch ((instr>>21)&0x1f) {
      case 0  : {
        uint8_t t,d;
        uint16_t s;
        MIPS_MFC_FORMAT(instr,t,d,s);
        return new MIPS_mfc0<word_t>(t,d,s);
      }
      case 1 : {
        uint8_t t,d;
        uint16_t s;
        MIPS_MFC_FORMAT(instr,t,d,s);
        return new MIPS_dmfc0<word_t>(t,d,s);
      }
      case 4  : {
        uint8_t t,d;
        uint16_t s;
        MIPS_MFC_FORMAT(instr,t,d,s);
        return new MIPS_mtc0<word_t>(t,d,s);
      }
      case 5 : {
        uint8_t t,d;
        uint16_t s;
        MIPS_MFC_FORMAT(instr,t,d,s);
        return new MIPS_dmtc0<word_t>(t,d,s);
      }
      }
    }
    return mips_invalid<word_t>(instr);
  }

  //group4 010001
  template <typename word_t>
  MIPS_Instruction<word_t> * mips_group4(uint32_t instr) {
    uint32_t ext = (instr >> 21) & 0x1f;

    switch (ext) {
    case   1 : return mips_invalid<word_t>(instr);
    case   3 : return mips_invalid<word_t>(instr);
    case   6 : return mips_invalid<word_t>(instr);
    case   8 : return mips_invalid<word_t>(instr);
    }
    return mips_invalid<word_t>(instr);
  }

  //group 5 010 010

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_group5(uint32_t instr) {
    uint32_t ext = (instr >> 21) & 0x1f;

    switch (ext) {
    case   0 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      return new MIPS_mfc2<word_t>(s,t,i);
    }

    case   1 :{
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      return new MIPS_dmfc2<word_t>(s,t,i);
    }

    case   2 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      return new MIPS_cfc2<word_t>(t,i);
    }
    case   3 : return mips_invalid<word_t>(instr);
    case   4 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      return new MIPS_mtc2<word_t>(s,t,i);
    }

    case   5 :{
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      return new MIPS_dmtc2<word_t>(s,t,i);
    }

    case   6 : {
      uint8_t s,t;
      uint32_t i;
      MIPS_I_FORMAT(instr,s,t,i);
      return new MIPS_ctc2<word_t>(t,i);
    }
    case   8 : {
      switch ((instr>>17)&0x1){
      case  0 :{
        switch ((instr>>16)&0x1){
        case  0 : {
          uint8_t c;
          uint16_t f;
          MIPS_BC_FORMAT(instr,c,f);
          return new MIPS_bc2f<word_t>(c,f);
        }
        case  1 : {
          uint8_t c;
          uint16_t f;
          MIPS_BC_FORMAT(instr,c,f);
          return new MIPS_bc2t<word_t>(c,f);
        }
        }
      }
      case  1 : {
        switch ((instr>>16)&0x1){
        case  0 :{
          uint8_t c;
          uint16_t f;
          MIPS_BC_FORMAT(instr,c,f);
          return new MIPS_bc2fl<word_t>(c,f);
        }
        case  1 : {
          uint8_t c;
          uint16_t f;
          MIPS_BC_FORMAT(instr,c,f);
          return new MIPS_bc2tl<word_t>(c,f);
        }
        }
      }
      }
    }
    }
    return mips_invalid<word_t>(instr);
  }
  //group 6 010 011

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_group6(uint32_t instr) {
    uint32_t ext = instr & 0x3f;

    switch (ext) {
    case   1 : return mips_invalid<word_t>(instr);
    case   5 : return mips_invalid<word_t>(instr);
    case   9 : return mips_invalid<word_t>(instr);
    case  13 : return mips_invalid<word_t>(instr);
    case  15 : return mips_invalid<word_t>(instr);

    }

    return mips_invalid<word_t>(instr);
  }

  //group 7 011 100


  template <typename word_t>
  MIPS_Instruction<word_t> * mips_group7(uint32_t instr) {
    uint32_t ext = instr & 0x3f;

    switch (ext) {
    case   0 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_madd<word_t>(s,t);
    }
    case   1 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_maddu<word_t>(s,t);
    }
    case   2 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_mul<word_t>(s,t,d);
    }

    case  4  : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_msub<word_t>(s,t);
    }
    case  5  : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_msubu<word_t>(s,t);
    }
    case  32 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_clz<word_t>(s,d);
    }
    case  33 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_clo<word_t>(s,d);
    }
    case  36 : return mips_dclz<word_t>(instr);

    case  37 : {
      uint8_t s,t,d,a;
      MIPS_R_FORMAT(instr,s,t,d,a);
      return new MIPS_dclo<word_t>(s,t,d);
    }                               //MIPS64

    case  63 : {
      uint32_t c;
      MIPS_SDBBP_FORMAT(instr,c);
      return new MIPS_sdbbp<word_t>(c);
    }
    }
    return mips_invalid<word_t>(instr);
  }

  //group 8 011 111

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_group8(uint32_t instr){
    // uint32_t ext = instr & 0x3f;

    // switch (ext) {
    // case   0 : return mips_invalid<word_t>(instr);
    // case   1 : return mips_invalid<word_t>(instr);
    // case   2 : return mips_invalid<word_t>(instr);
    // case   3 : return mips_invalid<word_t>(instr);
    // case   5 : return mips_invalid<word_t>(instr);
    // case   6 : return mips_invalid<word_t>(instr);
    // case   7 : return mips_invalid<word_t>(instr);
    // case  32 : {
    //   uint32_t ext = (instr >> 6) & 0x1f;

    //   switch (ext) {
    //   case   2 : return mips_invalid<word_t>(instr);
    //   case   5 : return mips_invalid<word_t>(instr);
    //   case   16 : return mips_invalid<word_t>(instr);
    //   case   24 : return mips_invalid<word_t>(instr);
    //   }
    // }
    // case  36 : {
    //   uint32_t ext = (instr >> 6) & 0x1f;
    //   switch (ext) {
    //   case   2 : return mips_invalid<word_t>(instr);
    //   case   5 : return mips_invalid<word_t>(instr);
    //   }
    // }
    // case   59 : return mips_invalid<word_t>(instr);
    // }{
    //   uint32_t ext = (instr >> 6) & 0x1f;

    //   switch (ext) {
    //   case   2 : return mips_invalid<word_t>(instr);
    //   case   5 : return mips_invalid<word_t>(instr);
    //   case   16 : return mips_invalid<word_t>(instr);
    //   case   24 : return mips_invalid<word_t>(instr);
    //   }
    // }
    return mips_invalid<word_t>(instr);
  }

  template <typename word_t>
  const typename MIPS_DecodeTable<word_t>::decode_func MIPS_DecodeTable<word_t>::main_table[64] =
    {
      mips_group0,      // 000000
      mips_group1,      // 000001
      mips_j,           // 000010
      mips_jal,         // 000011
      mips_group2,      // 000100
      mips_bne,         // 000101
      mips_blez,        // 000110
      mips_bgtz,        // 000111
      mips_addi,        // 001000
      mips_addiu,       // 001001
      mips_slti,        // 001010
      mips_sltiu,       // 001011
      mips_andi,        // 001100
      mips_ori,         // 001101
      mips_xori,        // 001110
      mips_lui,         // 001111
      mips_group3,      // 010000
      mips_group4,      // 010001
      mips_group5,      // 010010
      mips_group6,      // 010011
      mips_beql,        // 010100
      mips_bnel,        // 010101
      mips_blezl,       // 010110
      mips_bgtzl,       // 010111
      mips_daddi,       // 011000  MIPS64
      mips_daddiu,      // 011001  MIPS64
      mips_ldl,         // 011010  MIPS64
      mips_ldr,         // 011011  MIPS64
      mips_group7,      // 011100
      mips_invalid,     // 011101
      mips_invalid,     // 011110
      mips_group8,      // 011111
      mips_lb,          // 100000
      mips_lh,          // 100001
      mips_lwl,         // 100010
      mips_lw,          // 100011
      mips_lbu,         // 100100
      mips_lhu,         // 100101
      mips_lwr,         // 100110
      mips_lwu,         // 100111
      mips_sb,          // 101000
      mips_sh,          // 101001
      mips_swl,         // 101010
      mips_sw,          // 101011
      mips_sdl,         // 101100
      mips_sdr,         // 101101  MIPS64
      mips_swr,         // 101110
      mips_cache,       // 101111
      mips_ll,          // 110000
      mips_invalid,     // 110001
      mips_lwc2,        // 110010
      mips_pref,        // 110011
      mips_lld,         // 110100  MIPS64
      mips_invalid,     // 110101
      mips_ldc2,        // 110110
      mips_ld,          // 110111
      mips_sc,          // 111000
      mips_invalid,     // 111001
      mips_swc2,        // 111010
      mips_invalid,     // 111011
      mips_scd,         // 111100  MIPS64
      mips_invalid,     // 111101
      mips_sdc2,        // 111110
      mips_sd           // 111111  MIPS64
    };

  template <typename word_t>
  MIPS_Instruction<word_t>* mipsDecode(uint32_t instr) {
    uint32_t mainopc = (instr >> 26) & 0x3f;
    return MIPS_DecodeTable<word_t>::main_table[mainopc](instr);
  }

} // namespace simsoc
