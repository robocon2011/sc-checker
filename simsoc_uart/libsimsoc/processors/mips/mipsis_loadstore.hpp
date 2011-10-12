//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_LOADSTORE_HPP
#define MIPS_LOADSTORE_HPP

#include "libsimsoc/processors/mips/mipsis_visitor.hpp"
#include "libsimsoc/processors/mips/mips_base.hpp"
#include "libsimsoc/display.hpp"
#include "libsimsoc/processors/mips/mips_processor.hpp"
#include "libsimsoc/processors/mips/mips_decode_macros.hpp"

namespace simsoc {

  template <typename word_t>
  class MIPS_lb: public MIPS_Instruction<word_t> {
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    void exec(MIPS_Processor<word_t> &proc);
    MIPS_lb(uint8_t s,uint8_t t,uint32_t i);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_lbu: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_lbu(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_lh: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    void exec(MIPS_Processor<word_t> &proc);
    MIPS_lh(uint8_t s,uint8_t t,uint32_t i);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_lhu: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_lhu(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_ll: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_ll(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_lw: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_lw(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_lwl: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_lwl(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_lwr: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_lwr(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_pref: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t hint;
    uint32_t offset;
    MIPS_pref(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_sb: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_sb(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_sc: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_sc(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_sh: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_sh(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_sw: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_sw(uint8_t s,uint8_t t,int32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_swl: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_swl(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_swr: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_swr(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_sync: public MIPS_Instruction<word_t>{
  public:
    MIPS_sync();
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  /*****************************///mips64 commands

  template <typename word_t>
  class MIPS_dmfc1: public MIPS_Instruction<word_t>{
  public:
    uint8_t rt;
    uint8_t rd;
    MIPS_dmfc1(uint8_t t,uint8_t d);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_dmtc1: public MIPS_Instruction<word_t>{
  public:
    uint8_t rt;
    uint8_t rd;
    MIPS_dmtc1(uint8_t t,uint8_t d);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_ldl: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_ldl(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };


  template <typename word_t>
  class MIPS_ldr: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_ldr(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_lwu: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_lwu(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_sdl: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_sdl(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_sdr: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_sdr(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_lld: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    void exec(MIPS_Processor<word_t> &proc);
    MIPS_lld(uint8_t s,uint8_t t,uint32_t i);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_ld: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_ld(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_scd: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_scd(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

  template <typename word_t>
  class MIPS_sd: public MIPS_Instruction<word_t>{
  public:
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
    MIPS_sd(uint8_t s,uint8_t t,uint32_t i);
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
    bool may_branch() const {return false;}
  };

} // namespace simsoc

#include "mipsis_loadstore.tpp"

#endif
