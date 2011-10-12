//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPSIS_BRANCH_HPP
#define MIPSIS_BRANCH_HP

#include "libsimsoc/processors/mips/mipsis_visitor.hpp"

#include "libsimsoc/processors/mips/mips_base.hpp"
#include "libsimsoc/processors/mips/mips_processor.hpp"
#include "libsimsoc/processors/mips/mips_decode_macros.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/bitwise_operator.hpp"

namespace simsoc {

template <typename word_t>
class MIPS_b: public MIPS_Instruction<word_t>{
public:
  uint32_t branch_offset;
  MIPS_b(int32_t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bal: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bal(uint8_t,int32_t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_beq: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t branch_offset;
  MIPS_beq(uint8_t s,uint8_t t, int32_t f);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_beql: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t branch_offset;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_beql(uint8_t s, uint8_t t, int32_t offset);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bgez: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bgez(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bgezal: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bgezal(uint8_t,int32_t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bgtz: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bgtz(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_blez: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_blez(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bltz: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bltz<word_t>(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};


template <typename word_t>
class MIPS_bltzal: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bltzal(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bne: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t branch_offset;
  MIPS_bne(uint8_t s, uint8_t t, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_j: public MIPS_Instruction<word_t>{
public:
  uint32_t target_addr;
  MIPS_j(uint32_t ta);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_jal: public MIPS_Instruction<word_t>{
public:
  uint32_t target_addr;
  MIPS_jal(uint32_t ta);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_jalr: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rd;
  uint8_t hint;
  MIPS_jalr(uint8_t s, uint8_t d, uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_jr: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t hint;
  MIPS_jr(uint8_t s, uint8_t a);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_ssnop: public MIPS_Instruction<word_t>{
public:
  MIPS_ssnop();
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_nop: public MIPS_Instruction<word_t>{
public:
  MIPS_nop();
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_break: public MIPS_Instruction<word_t>{
public:
  uint32_t code;
  MIPS_break(uint32_t c);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_syscall: public MIPS_Instruction<word_t>{
public:
  uint32_t code;
  MIPS_syscall(uint32_t c);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_teq: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_teq(uint8_t s, uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_teqi: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t immed;
  MIPS_teqi(uint8_t s,int32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tge: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_tge(uint8_t s, uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tgei: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t immed;
  MIPS_tgei(uint8_t s,int32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tgeiu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t immed;
  MIPS_tgeiu(uint8_t s, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tgeu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_tgeu(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tlt: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_tlt(uint8_t s, uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tlti: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t immed;
  MIPS_tlti(uint8_t s,int32_t imme);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tltiu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t immed;
  MIPS_tltiu(uint8_t s,uint32_t imme);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tltu: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_tltu(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tne: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  MIPS_tne(uint8_t s,uint8_t t);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tnei: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t immed;
  MIPS_tnei(uint8_t s,int32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bgezall: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bgezall(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bgezl: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bgezl(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bgtzl: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bgtzl(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_blezl: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_blezl(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bltzall: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bltzall(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bltzl: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint32_t branch_offset;
  MIPS_bltzl(uint8_t s, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bnel: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t branch_offset;
  MIPS_bnel(uint8_t s, uint8_t t, int32_t offset);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_cache: public MIPS_Instruction<word_t>{
public:
  uint8_t base;
  uint8_t op;
  uint32_t offset;
  MIPS_cache(uint8_t s, uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_deret: public MIPS_Instruction<word_t>{
public:
  MIPS_deret();
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};


template <typename word_t>
class MIPS_eret: public MIPS_Instruction<word_t>{
public:
  MIPS_eret();
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_mfc0: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sel;
  MIPS_mfc0(uint8_t t,uint8_t d,uint8_t s);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_mtc0: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sel;
  MIPS_mtc0(uint8_t t,uint8_t d,uint8_t s);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_sdbbp: public MIPS_Instruction<word_t>{
public:
  uint32_t code;
  MIPS_sdbbp(uint32_t c);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_tlbp: public MIPS_Instruction<word_t>{
public:
  MIPS_tlbp();
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_tlbr: public MIPS_Instruction<word_t>{
public:
  MIPS_tlbr();
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_tlbwi: public MIPS_Instruction<word_t>{
public:
  MIPS_tlbwi();
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_tlbwr: public MIPS_Instruction<word_t>{
public:
  MIPS_tlbwr();
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_wait: public MIPS_Instruction<word_t>{
public:
  uint32_t implement;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_wait(uint32_t p);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_dmfc0: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sel;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_dmfc0(uint8_t t,uint8_t d,uint8_t s);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dmtc0: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint8_t rd;
  uint8_t sel;
  void exec(MIPS_Processor<word_t> &proc);
  MIPS_dmtc0(uint8_t t,uint8_t d,uint8_t s);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

} // namespace simsoc

#include "mipsis_branch.tpp"

#endif
