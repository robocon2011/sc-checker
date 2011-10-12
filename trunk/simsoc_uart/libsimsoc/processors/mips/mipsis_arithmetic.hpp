//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPSIS_ARITHMETIC_HPP
#define MIPSIS_ARITHMETIC_HPP

#include "libsimsoc/processors/mips/mips_base.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/processors/mips/mips_processor.hpp"
#include "libsimsoc/processors/mips/mips_decode_macros.hpp"

namespace simsoc {

template <typename word_t>
class MIPS_add: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_add(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_addi: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t immed;
  MIPS_addi(uint8_t s, uint8_t t, int32_t imme);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_addiu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t immed;
  MIPS_addiu(uint8_t s,uint8_t t,int32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_addu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_addu(uint8_t s,uint8_t t,uint8_t d);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_clo: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rd;
  MIPS_clo(uint8_t s, uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_clz: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rd;
  MIPS_clz(uint8_t s,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_div: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_div(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_divu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_divu(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_madd: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_madd(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_maddu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_maddu(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_msub: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_msub(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_msubu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_msubu(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_mul: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_mul(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_mult: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_mult(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_multu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_multu(uint8_t s,uint8_t t);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_slt: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_slt(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_slti: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t immed;
  MIPS_slti(uint8_t s,uint8_t t,uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_sltiu: public MIPS_Instruction<word_t> {
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t immed;
  MIPS_sltiu(uint8_t s,uint8_t t,uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_sltu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_sltu(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_sub: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_sub(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_subu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_subu(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_and: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_and(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_andi: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t immed;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_andi(uint8_t s,uint8_t t,uint32_t i);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_lui: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint32_t immed;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_lui(uint8_t t,uint32_t f);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_nor: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_nor(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_xor: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_xor(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_xori: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t immed;
  MIPS_xori(uint8_t s,uint8_t t,uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_or: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_or(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_ori: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t immed;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_ori(uint8_t s,uint8_t t,uint32_t i);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_mfhi: public MIPS_Instruction<word_t>{
public:
  uint8_t rd;
  MIPS_mfhi(uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_mflo: public MIPS_Instruction<word_t>{
public:
  uint8_t rd;;
  MIPS_mflo(uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_movf: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t cc;
  uint8_t rd;
  MIPS_movf(uint8_t s,uint8_t c,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_movz: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_movz(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_movn: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_movn(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_mthi: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  MIPS_mthi(uint8_t s);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_mtlo: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  MIPS_mtlo(uint8_t s);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_sll: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_sll(uint8_t t,uint8_t d,uint8_t a);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_sllv: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_sllv(uint8_t s,uint8_t t,uint8_t d);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_sra: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_sra(uint8_t t,uint8_t d,uint8_t a);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_srav: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_srav(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_srl: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_srl(uint8_t t,uint8_t d,uint8_t a);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_srlv: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_srlv(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

/***********************************************///mips64 command
template <typename word_t>
class MIPS_dsll: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  MIPS_dsll(uint8_t t,uint8_t d,uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsllv: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_dsllv(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsrlv: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_dsrlv(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsrav: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_dsrav(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dmult: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_dmult(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dmultu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_dmultu(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_ddiv: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_ddiv(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_ddivu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_ddivu(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dadd: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_dadd(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_daddu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_daddu(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsub: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_dsub(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsubu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_dsubu(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsrl: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  MIPS_dsrl(uint8_t t,uint8_t d,uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_drotr: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  MIPS_drotr(uint8_t t,uint8_t d,uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsra: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  MIPS_dsra(uint8_t t,uint8_t d,uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsll32: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  MIPS_dsll32(uint8_t t,uint8_t d,uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsrl32: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  MIPS_dsrl32(uint8_t t,uint8_t d,uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsra32: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  MIPS_dsra32(uint8_t t,uint8_t d,uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_daddi: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t immed;
  MIPS_daddi(uint8_t s,uint8_t t,uint64_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_daddiu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t immed;
  MIPS_daddiu(uint8_t s,uint8_t t,uint64_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dclo: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint8_t rd;
  MIPS_dclo(uint8_t s,uint8_t t,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dsbh: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  MIPS_dsbh(uint8_t t,uint8_t d,uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_drotr32: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sa;
  MIPS_drotr32(uint8_t t,uint8_t d,uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dclz: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rd;
  MIPS_dclz(uint8_t s,uint8_t d);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

} // namespace simsoc

#include "mipsis_arithmetic.tpp"

#endif
