//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPCIS_LOADSTORE_HPP
#define PPCIS_LOADSTORE_HPP

#include "libsimsoc/processors/ppc/ppcis.hpp"
#include "libsimsoc/processors/ppc/ppc_decode.hpp"

namespace simsoc {

  /*--------------------------------------------------------------------------*/
  struct PPC_dcbf : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_dcbf(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_dcbst : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_dcbst(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_dcbt : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_dcbt(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_dcbtst : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_dcbtst(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_dcbz : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_dcbz(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lbz : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lbz(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lbzu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lbzu(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lbzux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lbzux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lbzx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lbzx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_ld : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t ds;
    PPC_ld(uint8_t rt, uint8_t ra, uint32_t ds);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_ldarx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_ldarx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_ldu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t ds;
    PPC_ldu(uint8_t rt, uint8_t ra, uint32_t ds);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_ldux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_ldux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_ldx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_ldx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lfd : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lfd(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lfdu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lfdu(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lfdux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lfdux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lfdx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lfdx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lfs : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lfs(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lfsu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lfsu(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lfsux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lfsux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lfsx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lfsx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lha : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lha(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lhau : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lhau(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lhaux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lhaux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lhax : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lhax(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lhbrx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lhbrx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lhz : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lhz(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lhzu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lhzu(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lhzux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lhzux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lhzx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lhzx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lmw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lmw(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lswi : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lswi(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lswx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lswx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lwa : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t ds;
    PPC_lwa(uint8_t rt, uint8_t ra, uint32_t ds);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lwarx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lwarx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lwaux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lwaux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lwax : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lwax(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lwbrx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lwbrx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lwz : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lwz(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lwzu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_lwzu(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lwzux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lwzux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_lwzx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_lwzx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stb : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_stb(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stbu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_stbu(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stbux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stbux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stbx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stbx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_std : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t ds;
    PPC_std(uint8_t rt, uint8_t ra, uint32_t ds);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stdcx_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stdcx_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stdu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t ds;
    PPC_stdu(uint8_t rt, uint8_t ra, uint32_t ds);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stdux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stdux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stdx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stdx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stfd : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_stfd(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stfdu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_stfdu(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stfdux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stfdux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stfdx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stfdx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stfiwx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stfiwx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stfs : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_stfs(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stfsu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_stfsu(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stfsux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stfsux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stfsx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stfsx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sth : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_sth(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sthbrx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_sthbrx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sthu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_sthu(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sthux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_sthux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sthx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_sthx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stmw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_stmw(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stswi : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stswi(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stswx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stswx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_stw(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stwbrx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stwbrx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stwcx_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stwcx_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stwu : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_stwu(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stwux : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stwux(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_stwx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_stwx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_dss : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_dss(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  //---------------------------------------------------
  //
  static inline PPC_Instruction* ppc_dcbf(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_dcbf(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_dcbst(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_dcbst(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_dcbt(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_dcbt(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_dcbtst(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_dcbtst(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_dcbz(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_dcbz(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lbz(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lbz(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lbzu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lbzu(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lbzux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lbzux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lbzx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lbzx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_ld(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t ds;
    PPC_DS_FORM(instr, rt, ra, ds);
    return new PPC_ld(rt, ra, ds);
  }

  static inline PPC_Instruction* ppc_ldarx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_ldarx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_ldu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t ds;
    PPC_DS_FORM(instr, rt, ra, ds);
    return new PPC_ldu(rt, ra, ds);
  }

  static inline PPC_Instruction* ppc_ldux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_ldux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_ldx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_ldx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lfd(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lfd(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lfdu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lfdu(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lfdux(uint32_t instr) {
    uint8_t rt, ra, rb;

    if(instr&0x1==1)
      return new PPC_Unpredictable("Invalid form with CR updating option enabled");

    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lfdux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lfdx(uint32_t instr) {
    uint8_t rt, ra, rb;

    if(instr&0x1==1)
      return new PPC_Unpredictable("Invalid form with CR updating option enabled");

    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lfdx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lfs(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lfs(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lfsu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lfsu(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lfsux(uint32_t instr) {
    uint8_t rt, ra, rb;

    if(instr&0x1==1)
      return new PPC_Unpredictable("Invalid form with CR updating option enabled");

    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lfsux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lfsx(uint32_t instr) {
    uint8_t rt, ra, rb;

    if(instr&0x1==1)
      return new PPC_Unpredictable("Invalid form with CR updating option enabled");

    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lfsx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lha(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lha(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lhau(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lhau(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lhaux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lhaux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lhax(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lhax(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lhbrx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lhbrx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lhz(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lhz(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lhzu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lhzu(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lhzux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lhzux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lhzx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lhzx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lmw(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lmw(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lswi(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lswi(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lswx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lswx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lwa(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t ds;
    PPC_DS_FORM(instr, rt, ra, ds);
    return new PPC_lwa(rt, ra, ds);
  }

  static inline PPC_Instruction* ppc_lwarx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lwarx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lwaux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lwaux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lwax(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lwax(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lwbrx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lwbrx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lwz(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lwz(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lwzu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_lwzu(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_lwzux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lwzux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_lwzx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_lwzx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stb(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_stb(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_stbu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_stbu(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_stbux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stbux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stbx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stbx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_std(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t ds;
    PPC_DS_FORM(instr, rt, ra, ds);
    return new PPC_std(rt, ra, ds);
  }

  static inline PPC_Instruction* ppc_stdcx_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stdcx_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stdu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t ds;
    PPC_DS_FORM(instr, rt, ra, ds);
    return new PPC_stdu(rt, ra, ds);
  }

  static inline PPC_Instruction* ppc_stdux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stdux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stdx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stdx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stfd(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_stfd(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_stfdu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_stfdu(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_stfdux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);

    if(instr&0x1==1)
      return new PPC_Unpredictable("Invalid form with CR updating option enabled");

    return new PPC_stfdux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stfdx(uint32_t instr) {
    uint8_t rt, ra, rb;

    if(instr&0x1==1)
      return new PPC_Unpredictable("Invalid form with CR updating option enabled");

    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stfdx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stfiwx(uint32_t instr) {
    uint8_t rt, ra, rb;

    if(instr&0x1==1)
      return new PPC_Unpredictable("Invalid form with CR updating option enabled");

    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stfiwx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stfs(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_stfs(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_stfsu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_stfsu(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_stfsux(uint32_t instr) {
    uint8_t rt, ra, rb;

    if(instr&0x1==1)
      return new PPC_Unpredictable("Invalid form with CR updating option enabled");

    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stfsux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stfsx(uint32_t instr) {
    uint8_t rt, ra, rb;

    if(instr&0x1==1)
      return new PPC_Unpredictable("Invalid form with CR updating option enabled");

    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stfsx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_sth(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_sth(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_sthbrx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_sthbrx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_sthu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_sthu(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_sthux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_sthux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_sthx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_sthx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stmw(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_stmw(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_stswi(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stswi(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stswx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stswx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stw(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_stw(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_stwbrx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stwbrx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stwcx_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stwcx_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stwu(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_stwu(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_stwux(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stwux(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_stwx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_stwx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_dss(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_dss(rt, ra, rb);
  }

} // namespace simsoc

#endif // PPCIS_LOADSTORE_HPP
