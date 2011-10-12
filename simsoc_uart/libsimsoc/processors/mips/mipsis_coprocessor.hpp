//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPSIS_COPROCESSOR_HPP
#define MIPSIS_COPROCESSOR_HPP
#include "libsimsoc/processors/mips/mipsis_visitor.hpp"

#include "libsimsoc/processors/mips/mips_base.hpp"
#include "libsimsoc/processors/mips/mips_base.hpp"
#include "libsimsoc/processors/mips/mips_decode_macros.hpp"

namespace simsoc {

template <typename word_t>
class MIPS_bc2f: public MIPS_Instruction<word_t>{
public:
  uint8_t cc;
  uint16_t offset;
  MIPS_bc2f(uint8_t c,uint16_t f);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bc2t: public MIPS_Instruction<word_t>{
public:
  uint8_t cc;
  uint16_t offset;
  MIPS_bc2t(uint8_t c,uint16_t f);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bc2fl: public MIPS_Instruction<word_t>{
public:
  uint8_t cc;
  uint16_t offset;
  MIPS_bc2fl(uint8_t c,uint16_t f);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_bc2tl: public MIPS_Instruction<word_t>{
public:
  uint8_t cc;
  uint16_t offset;
  MIPS_bc2tl(uint8_t c,uint16_t f);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
};

template <typename word_t>
class MIPS_cfc2: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint32_t immed;
  MIPS_cfc2(uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_ctc2: public MIPS_Instruction<word_t>{
public:
  uint8_t rt;
  uint32_t immed;
  MIPS_ctc2(uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_ldc2: public MIPS_Instruction<word_t>{
public:
  uint8_t base;
  uint8_t rt;
  uint32_t offset;
  MIPS_ldc2(uint8_t s,uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_lwc2: public MIPS_Instruction<word_t>{
public:
  uint8_t base;
  uint8_t rt;
  uint32_t offset;
  MIPS_lwc2(uint8_t s,uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_mfc2: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
   uint32_t sel;
  MIPS_mfc2(uint8_t s,uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_mtc2: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t sel;
  MIPS_mtc2(uint8_t s,uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_sdc2: public MIPS_Instruction<word_t>{
public:
  uint8_t base;
  uint8_t rt;
  uint32_t offset;
  MIPS_sdc2(uint8_t s,uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_swc2: public MIPS_Instruction<word_t>{
public:
  uint8_t base;
  uint8_t rt;
  uint32_t offset;
  MIPS_swc2(uint8_t s,uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dmfc2: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t sel;
  MIPS_dmfc2(uint8_t s,uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

template <typename word_t>
class MIPS_dmtc2: public MIPS_Instruction<word_t>{
public:
  uint8_t rs;
  uint8_t rt;
  uint32_t sel;
  MIPS_dmtc2(uint8_t s,uint8_t t, uint32_t i);
  void exec(MIPS_Processor<word_t> &proc);
  virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
  std::ostream& display(std::ostream& os) const;
  bool may_branch() const {return false;}
};

} // namespace simsoc

#include "mipsis_coprocessor.tpp"

#endif // MIPSIS_COPROCESSOR_HPP
