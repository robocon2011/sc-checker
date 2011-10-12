//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPCIS_MISC_HPP
#define PPCIS_MISC_HPP

#include "libsimsoc/processors/ppc/ppcis.hpp"
#include "libsimsoc/processors/ppc/ppc_decode.hpp"

namespace simsoc {

  /*--------------------------------------------------------------------------*/
  struct PPC_b : public PPC_Instruction {
    uint32_t li;
    PPC_b(uint32_t li);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_ba : public PPC_Instruction {
    uint32_t li;
    PPC_ba(uint32_t li);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_bl : public PPC_Instruction {
    uint32_t li;
    PPC_bl(uint32_t li);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_bla : public PPC_Instruction {
    uint32_t li;
    PPC_bla(uint32_t li);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_bc : public PPC_Instruction {
    uint8_t bo;
    uint8_t bi;
    uint32_t bd;
    PPC_bc(uint8_t bo, uint8_t bi, uint32_t bd);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_bca : public PPC_Instruction {
    uint8_t bo;
    uint8_t bi;
    uint32_t bd;
    PPC_bca(uint8_t bo, uint8_t bi, uint32_t bd);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_bcl : public PPC_Instruction {
    uint8_t bo;
    uint8_t bi;
    uint32_t bd;
    PPC_bcl(uint8_t bo, uint8_t bi, uint32_t bd);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_bcla : public PPC_Instruction {
    uint8_t bo;
    uint8_t bi;
    uint32_t bd;
    PPC_bcla(uint8_t bo, uint8_t bi, uint32_t bd);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_bcctr : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_bcctr(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_bcctrl : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_bcctrl(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_bclr : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_bclr(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_bclrl : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_bclrl(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_eciwx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_eciwx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_ecowx : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_ecowx(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_eieio : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_eieio(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_icbi : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_icbi(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_isync : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_isync(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mcrf : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_mcrf(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mcrfs : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mcrfs(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mcrxr : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mcrxr(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mfcr : public PPC_Instruction {
    uint8_t rt;
    uint16_t spr;
    PPC_mfcr(uint8_t rt, uint16_t spr);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mfocrf : public PPC_Instruction {
    uint8_t rt;
    uint16_t spr;
    PPC_mfocrf(uint8_t rt, uint16_t spr);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mffs : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mffs(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mffs_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mffs_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mfmsr : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mfmsr(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mfspr : public PPC_Instruction {
    uint8_t rt;
    uint16_t spr;
    PPC_mfspr(uint8_t rt, uint16_t spr);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mfsr : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mfsr(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mfsrin : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mfsrin(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mftb : public PPC_Instruction {
    uint8_t rt;
    uint16_t spr;
    PPC_mftb(uint8_t rt, uint16_t spr);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtcrf : public PPC_Instruction {
    uint8_t rt;
    uint16_t spr;
    PPC_mtcrf(uint8_t rt, uint16_t spr);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtocrf : public PPC_Instruction {
    uint8_t rt;
    uint16_t spr;
    PPC_mtocrf(uint8_t rt, uint16_t spr);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtfsb0 : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mtfsb0(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtfsb0_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mtfsb0_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtfsb1 : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mtfsb1(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtfsb1_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mtfsb1_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtfsf : public PPC_Instruction {
    uint8_t flm;
    uint8_t frb;
    PPC_mtfsf(uint8_t rt, uint8_t ds);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtfsf_ : public PPC_Instruction {
    uint8_t flm;
    uint8_t frb;
    PPC_mtfsf_(uint8_t rt, uint8_t ds);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtfsfi : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mtfsfi(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtfsfi_ : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mtfsfi_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtmsr : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mtmsr(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtmsrd : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mtmsrd(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtspr : public PPC_Instruction {
    uint8_t rt;
    uint16_t spr;
    PPC_mtspr(uint8_t rt, uint16_t spr);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtsr : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mtsr(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_mtsrin : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_mtsrin(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_rfi : public PPC_Instruction {
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
    PPC_rfi(uint8_t bt,  uint8_t ba,  uint8_t bb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sc : public PPC_Instruction {
    uint8_t lev;
    PPC_sc(uint8_t lev);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_slbia : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_slbia(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_slbie : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_slbie(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_slbmfee : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_slbmfee(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_slbmfev : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_slbmfev(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_slbmte : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_slbmte(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_sync : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_sync(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_td : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_td(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_tdi : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_tdi(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_tlbia : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_tlbia(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_tlbie : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_tlbie(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_tlbsync : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_tlbsync(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_tw : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_tw(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_twi : public PPC_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
    PPC_twi(uint8_t rt, uint8_t ra, uint32_t d);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  //---------------------------------------------------
  //
  static inline PPC_Instruction* ppc_b(uint32_t instr) {
    uint32_t li;
    PPC_I_FORM(instr, li);
    return new PPC_b(li);
  }

  static inline PPC_Instruction* ppc_ba(uint32_t instr) {
    uint32_t li;
    PPC_I_FORM(instr, li);
    return new PPC_ba(li);
  }

  static inline PPC_Instruction* ppc_bl(uint32_t instr) {
    uint32_t li;
    PPC_I_FORM(instr, li);
    return new PPC_bl(li);
  }

  static inline PPC_Instruction* ppc_bla(uint32_t instr) {
    uint32_t li;
    PPC_I_FORM(instr, li);
    return new PPC_bla(li);
  }

  static inline PPC_Instruction* ppc_bc(uint32_t instr) {
    uint8_t bo, bi;
    uint32_t bd;
    PPC_B_FORM(instr, bo, bi, bd);
    return new PPC_bc(bo, bi, bd);
  }

  static inline PPC_Instruction* ppc_bca(uint32_t instr) {
    uint8_t bo, bi;
    uint32_t bd;
    PPC_B_FORM(instr, bo, bi, bd);
    return new PPC_bca(bo, bi, bd);
  }

  static inline PPC_Instruction* ppc_bcl(uint32_t instr) {
    uint8_t bo, bi;
    uint32_t bd;
    PPC_B_FORM(instr, bo, bi, bd);
    return new PPC_bcl(bo, bi, bd);
  }

  static inline PPC_Instruction* ppc_bcla(uint32_t instr) {
    uint8_t bo, bi;
    uint32_t bd;
    PPC_B_FORM(instr, bo, bi, bd);
    return new PPC_bcla(bo, bi, bd);
  }

  static inline PPC_Instruction* ppc_bcctr(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_bcctr(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_bcctrl(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_bcctrl(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_bclr(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_bclr(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_bclrl(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_bclrl(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_eciwx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_eciwx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_ecowx(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_ecowx(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_eieio(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_eieio(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_icbi(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_icbi(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_isync(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_isync(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_mcrf(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_mcrf(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_mcrfs(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mcrfs(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mcrxr(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mcrxr(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mfcr(uint32_t instr) {
    uint8_t rt;
    uint16_t spr;
    PPC_XFX_FORM(instr, rt, spr);
    return new PPC_mfcr(rt, spr);
  }

  static inline PPC_Instruction* ppc_mfocrf(uint32_t instr) {
    uint8_t rt;
    uint16_t spr;
    PPC_XFX_FORM(instr, rt, spr);
    return new PPC_mfocrf(rt, spr);
  }

  static inline PPC_Instruction* ppc_mffs(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mffs(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mffs_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mffs_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mfmsr(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mfmsr(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mfspr(uint32_t instr) {
    uint8_t rt;
    uint16_t spr;
    PPC_XFX_FORM(instr, rt, spr);
    return new PPC_mfspr(rt, spr);
  }

  static inline PPC_Instruction* ppc_mfsr(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mfsr(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mfsrin(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mfsrin(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mftb(uint32_t instr) {
    uint8_t rt;
    uint16_t spr;
    PPC_XFX_FORM(instr, rt, spr);
    return new PPC_mftb(rt, spr);
  }

  static inline PPC_Instruction* ppc_mtcrf(uint32_t instr) {
    uint8_t rt;
    uint16_t spr;
    PPC_XFX_FORM(instr, rt, spr);
    return new PPC_mtcrf(rt, spr);
  }

  static inline PPC_Instruction* ppc_mtocrf(uint32_t instr) {
    uint8_t rt;
    uint16_t spr;
    PPC_XFX_FORM(instr, rt, spr);
    return new PPC_mtocrf(rt, spr);
  }

  static inline PPC_Instruction* ppc_mtfsb0(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mtfsb0(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mtfsb0_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mtfsb0_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mtfsb1(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mtfsb1(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mtfsb1_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mtfsb1_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mtfsf(uint32_t instr) {
    uint8_t flm, frb;
    PPC_XFL_FORM(instr, flm, frb);
    return new PPC_mtfsf(flm, frb);
  }

  static inline PPC_Instruction* ppc_mtfsf_(uint32_t instr) {
    uint8_t flm, frb;
    PPC_XFL_FORM(instr, flm, frb);
    return new PPC_mtfsf_(flm, frb);
  }

  static inline PPC_Instruction* ppc_mtfsfi(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mtfsfi(rt, ra,rb);
  }

  static inline PPC_Instruction* ppc_mtfsfi_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mtfsfi_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mtmsr(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mtmsr(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mtmsrd(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mtmsrd(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mtspr(uint32_t instr) {
    uint8_t rt;
    uint16_t spr;
    PPC_XFX_FORM(instr, rt, spr);
    return new PPC_mtspr(rt, spr);
  }

  static inline PPC_Instruction* ppc_mtsr(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mtsr(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_mtsrin(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_mtsrin(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_rfi(uint32_t instr) {
    uint8_t bt, ba, bb;
    PPC_XL_FORM(instr, bt, ba, bb);
    return new PPC_rfi(bt, ba, bb);
  }

  static inline PPC_Instruction* ppc_sc(uint32_t instr) {
    uint8_t lev;
    PPC_SC_FORM(instr, lev);
    return new PPC_sc(lev);
  }

  static inline PPC_Instruction* ppc_slbia(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_slbia(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_slbie(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_slbie(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_slbmfee(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_slbmfee(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_slbmfev(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_slbmfev(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_slbmte(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_slbmte(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_sync(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_sync(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_td(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_td(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_tdi(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_tdi(rt, ra, d);
  }

  static inline PPC_Instruction* ppc_tlbia(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_tlbia(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_tlbie(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_tlbie(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_tlbsync(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_tlbsync(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_tw(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_tw(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_twi(uint32_t instr) {
    uint8_t rt, ra;
    uint32_t d;
    PPC_D_FORM_SI(instr, rt, ra, d);
    return new PPC_twi(rt, ra, d);
  }

} // namespace simsoc

#endif // PPCIS_MISC_HPP
