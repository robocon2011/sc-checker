//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPCIS_ALU_HPP
#define PPCIS_ALU_HPP

#include "libsimsoc/processors/ppc/ppcis.hpp"
#include "libsimsoc/processors/ppc/ppc_decode.hpp"

namespace simsoc {

  /*--------------------------------------------------------------------------*/
  struct PPC_add : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_add(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_add_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_add_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };


  /*--------------------------------------------------------------------------*/
  struct PPC_addo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addc : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addc(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addc_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addc_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addco : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addco(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addco_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addco_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_adde : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_adde(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_adde_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_adde_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addeo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addeo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addeo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addeo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addi : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_addi(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addic : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_addic(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addic_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_addic_(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addis : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_addis(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addme : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addme(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addme_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addme_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addmeo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addmeo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addmeo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addmeo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addze : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addze(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addze_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addze_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addzeo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addzeo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_addzeo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_addzeo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_and : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_and(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_and_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_and_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_andc : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_andc(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_andc_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_andc_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_andi_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_andi_(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_andis_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_andis_(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_cmp : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_cmp(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_cmpi : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_cmpi(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_cmpl : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_cmpl(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_cmpli : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_cmpli(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_cntlzd : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_cntlzd(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_cntlzd_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_cntlzd_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_cntlzw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_cntlzw(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_cntlzw_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_cntlzw_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_crand : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_crand(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_crandc : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_crandc(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_creqv : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_creqv(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_crnand : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_crnand(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_crnor : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_crnor(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_cror : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_cror(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_crorc : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_crorc(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_crxor : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_crxor(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divd : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divd(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divd_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divd_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divdo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divdo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divdo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divdo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divdu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divdu(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divdu_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divdu_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divduo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divduo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divduo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divduo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divw(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divw_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divw_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divwo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divwo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divwo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divwo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divwu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divwu(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divwu_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divwu_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divwuo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divwuo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_divwuo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_divwuo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_eqv : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_eqv(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_eqv_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_eqv_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_extsb : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_extsb(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_extsb_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_extsb_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_extsh : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_extsh(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_extsh_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_extsh_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_extsw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_extsw(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_extsw_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_extsw_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulhd : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulhd(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulhd_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulhd_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulhdu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulhdu(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulhdu_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulhdu_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulhw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulhw(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulhw_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulhw_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulhwu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulhwu(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulhwu_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulhwu_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulld : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulld(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulld_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulld_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulldo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulldo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulldo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mulldo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mulli : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_mulli(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mullw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mullw(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mullw_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mullw_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mullwo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mullwo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mullwo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mullwo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_nand : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_nand(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_nand_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_nand_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_neg : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_neg(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_neg_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_neg_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_nego : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_nego(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_nego_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_nego_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_nor : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_nor(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_nor_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_nor_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_or : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_or(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_or_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_or_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_orc : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_orc(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_orc_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_orc_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_ori : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_ori(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_oris : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_oris(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldcl : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    PPC_rldcl(uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldcl_ : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    PPC_rldcl_(uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldcr : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    PPC_rldcr(uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldcr_ : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    PPC_rldcr_(uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldic : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    uint8_t mb;
    PPC_rldic(uint8_t rs, uint8_t ra, uint8_t sh, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldic_ : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    uint8_t mb;
    PPC_rldic_(uint8_t rs, uint8_t ra, uint8_t sh, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldicl_ : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    uint8_t mb;
    PPC_rldicl_(uint8_t rs, uint8_t ra, uint8_t sh, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldicl : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    uint8_t mb;
    PPC_rldicl(uint8_t rs, uint8_t ra, uint8_t sh, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldicr : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    uint8_t mb;
    PPC_rldicr(uint8_t rs, uint8_t ra, uint8_t sh, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldicr_ : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    uint8_t mb;
    PPC_rldicr_(uint8_t rs, uint8_t ra, uint8_t sh, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldimi : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    uint8_t mb;
    PPC_rldimi(uint8_t rs, uint8_t ra, uint8_t sh, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rldimi_ : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    uint8_t mb;
    PPC_rldimi_(uint8_t rs, uint8_t ra, uint8_t sh, uint8_t mb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rlwimi : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    uint8_t me;
    PPC_rlwimi(uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb,uint8_t me);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rlwimi_ : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    uint8_t me;
    PPC_rlwimi_(uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb,uint8_t me);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rlwinm : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    uint8_t me;
    PPC_rlwinm(uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb,uint8_t me);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rlwinm_ : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    uint8_t me;
    PPC_rlwinm_(uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb,uint8_t me);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rlwnm : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    uint8_t me;
    PPC_rlwnm(uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb,uint8_t me);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rlwnm_ : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    uint8_t me;
    PPC_rlwnm_(uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb,uint8_t me);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sld : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_sld(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sld_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_sld_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_slw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_slw(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_slw_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_slw_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_srad : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_srad(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_srad_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_srad_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sradi : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    PPC_sradi(uint8_t rs, uint8_t ra, uint8_t sh);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sradi_ : public PPC_Instruction {
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    PPC_sradi_(uint8_t rs, uint8_t ra, uint8_t sh);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sraw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_sraw(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sraw_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_sraw_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_srawi : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_srawi(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_srawi_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_srawi_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_srd : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_srd(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_srd_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_srd_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_srw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_srw(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_srw_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_srw_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subf : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subf(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subf_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subf_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfc : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfc(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfc_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfc_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfco : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfco(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfco_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfco_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfe : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfe(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfe_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfe_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfeo: public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfeo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfeo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfeo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfic : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_subfic(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfme : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfme(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfme_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfme_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfmeo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfmeo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfmeo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfmeo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfze : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfze(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfze_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfze_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfzeo : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfzeo(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_subfzeo_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_subfzeo_(uint8_t rt, uint8_t ra, uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_xor : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_xor(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_xor_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_xor_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_xori : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_xori(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_xoris : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_xoris(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  //---------------------------------------------------
  //
  static inline PPC_Instruction* ppc_add(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_add(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_add_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_add_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addc(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addc(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addc_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addc_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addco(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addco(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addco_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addco_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_adde(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_adde(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_adde_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_adde_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addeo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addeo(rt, ra, rb);
  }
  static inline PPC_Instruction* ppc_addeo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addeo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addi(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_addi(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_addic(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_addic(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_addic_(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_addic_(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_addis(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_addis(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_addme(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addme(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addme_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addme_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addmeo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addmeo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addmeo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addmeo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addze(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addze(rt, ra, rb);
  }
  static inline PPC_Instruction* ppc_addze_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addze_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addzeo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addzeo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_addzeo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_addzeo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_and(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_and(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_and_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_and_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_andc(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_andc(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_andc_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_andc_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_andi_(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_UI(instr, rt, ra, d);
    return new PPC_andi_(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_andis_(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_UI(instr, rt, ra, d);
    return new PPC_andis_(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_cmp(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_cmp(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_cmpi(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_cmpi(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_cmpl(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_cmpl(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_cmpli(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_UI(instr, rt, ra, d);
    return new PPC_cmpli(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_cntlzd(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_cntlzd(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_cntlzd_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_cntlzd_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_cntlzw(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_cntlzw(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_cntlzw_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_cntlzw_(rt, ra, rb);
  }
  static inline PPC_Instruction* ppc_crand(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_crand(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_crandc(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_crandc(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_creqv(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_creqv(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_crnand(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_crnand(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_crnor(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_crnor(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_cror(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_cror(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_crorc(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_crorc(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_crxor(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_crxor(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_divd(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divd(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divd_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divd_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divdo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divdo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divdo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divdo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divdu(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divdu(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divdu_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divdu_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divduo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divduo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divduo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divduo_(rt, ra, rb);
  }
  static inline PPC_Instruction* ppc_divw(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divw(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divw_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divw_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divwo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divwo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divwo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divwo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divwu(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divwu(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divwu_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divwu_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divwuo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divwuo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_divwuo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_divwuo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_eqv(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_eqv(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_eqv_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_eqv_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_extsb(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_extsb(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_extsb_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_extsb_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_extsh(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_extsh(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_extsh_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_extsh_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_extsw(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_extsw(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_extsw_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_extsw_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulhd(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulhd(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulhd_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulhd_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulhdu(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulhdu(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulhdu_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulhdu_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulhw(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulhw(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulhw_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulhw_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulhwu_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulhwu_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulhwu(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulhwu(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulld(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulld(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulld_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulld_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulldo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulldo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulldo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mulldo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mulli(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_mulli(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_mullw(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mullw(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mullw_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mullw_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mullwo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mullwo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mullwo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_mullwo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_nand(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_nand(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_nand_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_nand_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_neg(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_neg(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_neg_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_neg_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_nego(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_nego(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_nego_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_nego_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_nor(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_nor(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_nor_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_nor_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_or(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_or(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_or_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_or_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_orc(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_orc(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_orc_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_orc_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_ori(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_UI(instr, rt, ra, d);
    return new PPC_ori(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_oris(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_UI(instr, rt, ra, d);
    return new PPC_oris(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_rldcl(uint32_t instr) {
    uint8_t rt, ra, rb, mb;
    PPC_MDS_FORM(instr,rt, ra, rb, mb);
    return new PPC_rldcl(rt, ra, rb, mb);
  }

  static inline PPC_Instruction* ppc_rldcl_(uint32_t instr) {
    uint8_t rt, ra, rb, mb;
    PPC_MDS_FORM(instr,rt, ra, rb, mb);
    return new PPC_rldcl_(rt, ra, rb, mb);
  }

  static inline PPC_Instruction* ppc_rldcr(uint32_t instr) {
    uint8_t rt, ra, rb, mb;
    PPC_MDS_FORM(instr,rt, ra, rb, mb);
    return new PPC_rldcr(rt, ra, rb, mb);
  }

  static inline PPC_Instruction* ppc_rldcr_(uint32_t instr) {
    uint8_t rt, ra, rb, mb;
    PPC_MDS_FORM(instr,rt, ra, rb, mb);
    return new PPC_rldcr_(rt, ra, rb, mb);
  }

  static inline PPC_Instruction* ppc_rldic(uint32_t instr) {
    uint8_t rt, ra, sh, mb;
    PPC_MD_FORM(instr, rt, ra, sh, mb);
    return new PPC_rldic(rt, ra, sh, mb);
  }

  static inline PPC_Instruction* ppc_rldic_(uint32_t instr) {
    uint8_t rt, ra, sh, mb;
    PPC_MD_FORM(instr, rt, ra, sh, mb);
    return new PPC_rldic_(rt, ra, sh, mb);
  }

  static inline PPC_Instruction* ppc_rldicl(uint32_t instr) {
    uint8_t rt, ra, sh, mb;
    PPC_MD_FORM(instr, rt, ra, sh, mb);
    return new PPC_rldicl(rt, ra, sh, mb);
  }

  static inline PPC_Instruction* ppc_rldicl_(uint32_t instr) {
    uint8_t rt, ra, sh, mb;
    PPC_MD_FORM(instr, rt, ra, sh, mb);
    return new PPC_rldicl_(rt, ra, sh, mb);
  }

  static inline PPC_Instruction* ppc_rldicr(uint32_t instr) {
    uint8_t rt, ra, sh, mb;
    PPC_MD_FORM(instr, rt, ra, sh, mb);
    return new PPC_rldicr(rt, ra, sh, mb);
  }

  static inline PPC_Instruction* ppc_rldicr_(uint32_t instr) {
    uint8_t rt, ra, sh, mb;
    PPC_MD_FORM(instr, rt, ra, sh, mb);
    return new PPC_rldicr_(rt, ra, sh, mb);
  }

  static inline PPC_Instruction* ppc_rldimi(uint32_t instr) {
    uint8_t rt, ra, sh, mb;
    PPC_MD_FORM(instr, rt, ra, sh, mb);
    return new PPC_rldimi(rt, ra, sh, mb);
  }

  static inline PPC_Instruction* ppc_rldimi_(uint32_t instr) {
    uint8_t rt, ra, sh, mb;
    PPC_MD_FORM(instr, rt, ra, sh, mb);
    return new PPC_rldimi_(rt, ra, sh, mb);
  }

  static inline PPC_Instruction* ppc_rlwimi(uint32_t instr) {
    uint8_t rt, ra, rb, mb, me;
    PPC_M_FORM(instr, rt, ra, rb, mb, me);
    return new PPC_rlwimi(rt, ra, rb, mb, me);
  }

  static inline PPC_Instruction* ppc_rlwimi_(uint32_t instr) {
    uint8_t rt, ra, rb, mb, me;
    PPC_M_FORM(instr, rt, ra, rb, mb, me);
    return new PPC_rlwimi_(rt, ra, rb, mb, me);
  }

  static inline PPC_Instruction* ppc_rlwinm(uint32_t instr) {
    uint8_t rt, ra, rb, mb, me;
    PPC_M_FORM(instr, rt, ra, rb, mb, me);
    return new PPC_rlwinm(rt, ra, rb, mb, me);
  }

  static inline PPC_Instruction* ppc_rlwinm_(uint32_t instr) {
    uint8_t rt, ra, rb, mb, me;
    PPC_M_FORM(instr, rt, ra, rb, mb, me);
    return new PPC_rlwinm_(rt, ra, rb, mb, me);
  }

  static inline PPC_Instruction* ppc_rlwnm(uint32_t instr) {
    uint8_t rt, ra, rb, mb, me;
    PPC_M_FORM(instr, rt, ra, rb, mb, me);
    return new PPC_rlwnm(rt, ra, rb, mb, me);
  }

  static inline PPC_Instruction* ppc_rlwnm_(uint32_t instr) {
    uint8_t rt, ra, rb, mb, me;
    PPC_M_FORM(instr, rt, ra, rb, mb, me);
    return new PPC_rlwnm_(rt, ra, rb, mb, me);
  }

  static inline PPC_Instruction* ppc_sld(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_sld(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_sld_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_sld_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_slw(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_slw(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_slw_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_slw_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_srad(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_srad(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_srad_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_srad_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_sradi(uint32_t instr) {
    uint8_t rs, ra, sh;
    PPC_XS_FORM(instr, rs, ra, sh);
    return new PPC_sradi(rs, ra, sh);
  }

  static inline PPC_Instruction* ppc_sradi_(uint32_t instr) {
    uint8_t rs, ra, sh;
    PPC_XS_FORM(instr, rs, ra, sh);
    return new PPC_sradi_(rs, ra, sh);
  }

  static inline PPC_Instruction* ppc_sraw(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_sraw(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_sraw_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_sraw_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_srawi(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_srawi(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_srawi_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_srawi_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_srd(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_srd(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_srd_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_srd_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_srw(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_srw(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_srw_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_srw_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subf(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subf(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subf_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subf_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfc(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfc(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfc_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfc_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfco(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfco(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfco_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfco_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfe(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfe(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfe_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfe_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfeo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfeo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfeo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfeo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfic(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_subfic(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_subfme(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfme(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfme_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfme_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfmeo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfmeo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfmeo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfmeo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfze(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfze(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfze_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfze_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfzeo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfzeo(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_subfzeo_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_XO_FORM(instr, rt, ra, rb);
    return new PPC_subfzeo_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_xor(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_xor(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_xor_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_xor_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_xori(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_UI(instr, rt, ra, d);
    return new PPC_xori(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_xoris(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_UI(instr, rt, ra, d);
    return new PPC_xoris(rt, ra, d);
  }

} // namespace simsoc

#endif // PPCIS_ALU_HPP
