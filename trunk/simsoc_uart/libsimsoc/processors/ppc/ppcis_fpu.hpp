//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPCIS_FPU_HPP
#define PPCIS_FPU_HPP

#include "libsimsoc/processors/ppc/ppcis.hpp"
#include "libsimsoc/processors/ppc/ppc_decode.hpp"
#include "libsimsoc/processors/ppc/ppc_processor.hpp"

namespace simsoc {

  struct PPC_FP_Instruction: PPC_Instruction {
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  template <class op>
  struct PPC_FPArithmetic:public PPC_FP_Instruction {
    uint8_t rd;
    uint8_t op1;
    uint8_t op2;
    PPC_FPArithmetic(uint8_t rd_,uint8_t op1_,uint8_t op2_):
      PPC_FP_Instruction(),rd(rd_),op1(op1_),op2(op2_){}
    virtual void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  template <class op>
  struct PPC_FPArithmetic_1op:public PPC_FP_Instruction {
    uint8_t rd;
    uint8_t op1;
    PPC_FPArithmetic_1op(uint8_t rd_,uint8_t op1_):
      PPC_FP_Instruction(),rd(rd_),op1(op1_){}
    virtual void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  template <class op>
  struct PPC_FPConvert:public PPC_FP_Instruction {
    uint8_t rd;
    uint8_t op1;
    PPC_FPConvert(uint8_t rd_,uint8_t op1_):
      PPC_FP_Instruction(),rd(rd_),op1(op1_){}
    virtual void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  template <class op>
  struct PPC_FPCompare:public PPC_FP_Instruction {
    uint8_t crfD;
    uint8_t op1;
    uint8_t op2;
    PPC_FPCompare(uint8_t crfD_,uint8_t op1_,uint8_t op2_):
      PPC_FP_Instruction(),crfD(crfD_),op1(op1_),op2(op2_){}
    virtual void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  template <class op>
  struct PPC_FPMultiAdd:public PPC_FP_Instruction {
    uint8_t rd;
    uint8_t ra;
    uint8_t rb;
    uint8_t rc;
    PPC_FPMultiAdd(uint8_t rd_,uint8_t ra_,uint8_t rb_,uint8_t rc_):
      PPC_FP_Instruction(),rd(rd_),ra(ra_),rb(rb_),rc(rc_){}
    virtual void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fabs : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_fabs(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  struct PPC_fabs_ : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_fabs_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fadd {
    static const fp_op_t type() {return FADD;}
    static const char * name() {return "fadd";}
    static const bool single_prec_operation = false;
    static const bool rc = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_add(*frd,*fra,*frb,rnd);
    };
  };

  struct PPC_fadd_{
    static const fp_op_t type() {return FADD;}
    static const char * name() {return "fadd.";}
    static const bool single_prec_operation = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_add(*frd,*fra,*frb,rnd);
    };
    static const bool rc = true;
  };
  /*--------------------------------------------------------------------------*/
  struct PPC_fadds{
    static const fp_op_t type() {return FADD;}
    static const char * name() {return "fadds";}
    static const bool single_prec_operation = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_add(*frd,*fra,*frb,rnd);
    };
    static const bool rc = false;
  };

  struct PPC_fadds_{
    static const fp_op_t type() {return FADD;}
    static const char * name() {return "fadds.";}
    static const bool single_prec_operation = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_add(*frd,*fra,*frb,rnd);
    };
    static const bool rc = true;
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fcfid : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_fcfid(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  struct PPC_fcfid_ : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_fcfid_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fcmpo {
    static const fp_op_t type() {return FCOMPO;}
    static const char * name() {return "fcmpo";}
    static const int compute(fp_t& fra,fp_t& frb){
      return mpfr_cmp(*fra,*frb);
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fcmpu {
    static const fp_op_t type() {return FCOMPU;}
    static const char * name() {return "fcmpu";}
    static const int compute(fp_t& fra,fp_t& frb){
      return mpfr_cmp(*fra,*frb);
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fctid {
    static const fp_op_t type() {return FCOV64S;}
    static const char * name() {return "fctid";}
    static const bool rc = false;
    static const uint64_t max_pos = 0x7fffffffffffffffULL;
    static const uint64_t max_neg = 0x8000000000000000ULL;
    static mp_rnd_t rnd(PPC_Processor& proc){
      return proc.fp_unit.rnd_mode();
    }
    static const int compute(uint64_t& result,fp_t& op,mp_rnd_t rnd){
      fp_t frd;
      int inext= mpfr_rint(*frd,*op,rnd);
      inext = frd.sign() * inext;
      result = mpfr_get_si(*frd,rnd);
      if(mpfr_zero_p(*frd) && frd.sign()==-1)
        result |= 0x8000000000000000ULL;
      return inext;
    };
  };

  struct PPC_fctid_ {
    static const fp_op_t type() {return FCOV64S;}
    static const char * name() {return "fctid.";}
    static const bool rc = true;
    static const uint64_t max_pos = 0x7fffffffffffffffULL;
    static const uint64_t max_neg = 0x8000000000000000ULL;
    static mp_rnd_t rnd(PPC_Processor& proc){
      return proc.fp_unit.rnd_mode();
    }
    static const int compute(uint64_t& result,fp_t& op,mp_rnd_t rnd){
      fp_t frd;
      int inext= mpfr_rint(*frd,*op,rnd);
      inext = frd.sign() * inext;
      result = mpfr_get_si(*frd,rnd);
      if(mpfr_zero_p(*frd) && frd.sign()==-1)
        result |= 0x8000000000000000ULL;
      return inext;
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fctidz {
    static const fp_op_t type() {return FCOV64S;}
    static const char * name() {return "fctidz";}
    static const bool rc = false;
    static const uint64_t max_pos = 0x7fffffffffffffffULL;
    static const uint64_t max_neg = 0x8000000000000000ULL;
    static mp_rnd_t rnd(PPC_Processor& proc){
      return GMP_RNDZ;
    }
    static const int compute(uint64_t& result,fp_t& op,mp_rnd_t rnd){
      fp_t frd;
      int inext= mpfr_rint(*frd,*op,GMP_RNDZ);
      inext = frd.sign() * inext;
      result = mpfr_get_si(*frd,GMP_RNDZ);
      if(mpfr_zero_p(*frd) && frd.sign()==-1)
        result |= 0x8000000000000000ULL;
      return inext;
    };
  };

  struct PPC_fctidz_ {
    static const fp_op_t type() {return FCOV64S;}
    static const char * name() {return "fctidz.";}
    static const bool rc = true;
    static const uint64_t max_pos = 0x7fffffffffffffffULL;
    static const uint64_t max_neg = 0x8000000000000000ULL;
    static mp_rnd_t rnd(PPC_Processor& proc){
      return GMP_RNDZ;
    }
    static const int compute(uint64_t& result,fp_t& op,mp_rnd_t rnd){
      fp_t frd;
      int inext= mpfr_rint(*frd,*op,GMP_RNDZ);
      inext = frd.sign() * inext;
      result = mpfr_get_si(*frd,GMP_RNDZ);
      if(mpfr_zero_p(*frd) && frd.sign()==-1)
        result |= 0x8000000000000000ULL;
      return inext;
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fctiw {
    static const fp_op_t type() {return FCOV32S;}
    static const char * name() {return "fctiw";}
    static const bool rc = false;
    static const uint64_t max_pos = 0x7fffffff;
    static const uint64_t max_neg = 0x80000000;
    static mp_rnd_t rnd(PPC_Processor& proc){
      return proc.fp_unit.rnd_mode();
    }
    static const int compute(uint64_t& result,fp_t& op,mp_rnd_t rnd){
      fp_t frd;
      /*
       * For setting fi and fr bit
       * mpfr_rint return rnd_away ^ (sign<0) ? uflags : -uflags;
       * for uflags:
       * 0: exact
       * 1: is an integer not representable in dst
       * 2: not an integer
       */
      int inext= mpfr_rint(*frd,*op,rnd);
      inext = frd.sign() * inext;
      result = mpfr_get_si(*frd,rnd);
      //if(mpfr_zero_p(*frd) && frd.sign()==-1)
      //   result |= 0x80000000;
      return inext;
    };
  };

  struct PPC_fctiw_ {
    static const fp_op_t type() {return FCOV32S;}
    static const char * name() {return "fctiw.";}
    static const bool rc = true;
    static const uint64_t max_pos = 0x7fffffff;
    static const uint64_t max_neg = 0x80000000;
    static mp_rnd_t rnd(PPC_Processor& proc){
      return proc.fp_unit.rnd_mode();
    }
    static const int compute(uint64_t& result,fp_t& op,mp_rnd_t rnd){
      fp_t frd;
      int inext= mpfr_rint(*frd,*op,rnd);
      inext = frd.sign() * inext;
      result = mpfr_get_si(*frd,rnd);
      //if(mpfr_zero_p(*frd) && frd.sign()==-1)
      //  result |= 0x80000000;
      return inext;
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fctiwz {
    static const fp_op_t type() {return FCOV32S;}
    static const char * name() {return "fctiwz";}
    static const bool rc = false;
    static const uint64_t max_pos = 0x7fffffff;
    static const uint64_t max_neg = 0x80000000;
    static mp_rnd_t rnd(PPC_Processor& proc){
      return GMP_RNDZ;
    }
    static const int compute(uint64_t& result,fp_t& op,mp_rnd_t rnd){
      fp_t frd;
      int inext= mpfr_rint(*frd,*op,GMP_RNDZ);
      inext = frd.sign() * inext;
      result = mpfr_get_si(*frd,GMP_RNDZ);
      //if(mpfr_zero_p(*frd) && frd.sign()==-1)
      //  result |= 80000000;
      return inext;
    };
  };

  struct PPC_fctiwz_ {
    static const fp_op_t type() {return FCOV32S;}
    static const char * name() {return "fctiwz.";}
    static const bool rc = true;
    static const uint64_t max_pos = 0x7fffffff;
    static const uint64_t max_neg = 0x80000000;
    static mp_rnd_t rnd(PPC_Processor& proc){
      return GMP_RNDZ;
    }
    static const int compute(uint64_t& result,fp_t& op,mp_rnd_t rnd){
      fp_t frd;
      int inext= mpfr_rint(*frd,*op,GMP_RNDZ);
      inext = frd.sign() * inext;
      result = mpfr_get_si(*frd,GMP_RNDZ);
      //if(mpfr_zero_p(*frd) && frd.sign()==-1)
      //  result |= 0x80000000;
      return inext;
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fdiv{
    static const fp_op_t type() {return FDIV;}
    static const char * name() {return "fdiv";}
    static const bool single_prec_operation = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_div(*frd,*fra,*frb,rnd);
    };
    static const bool rc = false;
  };

  struct PPC_fdiv_{
    static const fp_op_t type() {return FDIV;}
    static const char * name() {return "fdiv.";}
    static const bool single_prec_operation = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_div(*frd,*fra,*frb,rnd);
    };
    static const bool rc = true;
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fdivs{
    static const fp_op_t type() {return FDIV;}
    static const char * name() {return "fdivs";}
    static const bool single_prec_operation = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_div(*frd,*fra,*frb,rnd);
    };
    static const bool rc = false;
  };

  struct PPC_fdivs_ {
    static const fp_op_t type() {return FDIV;}
    static const char * name() {return "fdivs.";}
    static const bool single_prec_operation = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_div(*frd,*fra,*frb,rnd);
    };
    static const bool rc = true;
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fmadd {
    static const fp_op_t type() {return FMADD;}
    static const char * name() {return "fmadd";}
    static const bool single_prec_operation = false;
    static const bool rc = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      return mpfr_fma(*frd,*fra,*frc,*frb,rnd);
    };
  };

  struct PPC_fmadd_ {
    static const fp_op_t type() {return FMADD;}
    static const char * name() {return "fmadd.";}
    static const bool single_prec_operation = false;
    static const bool rc = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      return mpfr_fma(*frd,*fra,*frc,*frb,rnd);
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fmadds {
    static const fp_op_t type() {return FMADD;}
    static const char * name() {return "fmadds";}
    static const bool single_prec_operation = true;
    static const bool rc = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      return mpfr_fma(*frd,*fra,*frc,*frb,rnd);
    };
  };

  struct PPC_fmadds_ {
    static const fp_op_t type() {return FMADD;}
    static const char * name() {return "fmadds.";}
    static const bool single_prec_operation = true;
    static const bool rc = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      return mpfr_fma(*frd,*fra,*frc,*frb,rnd);
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fmr : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_fmr(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  struct PPC_fmr_ : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_fmr_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fmsub{
    static const fp_op_t type() {return FMSUB;}
    static const char * name() {return "fmsub";}
    static const bool single_prec_operation = false;
    static const bool rc = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      return mpfr_fms(*frd,*fra,*frc,*frb,rnd);
    };
  };

  struct PPC_fmsub_ {
    static const fp_op_t type() {return FMSUB;}
    static const char * name() {return "fmsub.";}
    static const bool single_prec_operation = false;
    static const bool rc = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      return mpfr_fms(*frd,*fra,*frc,*frb,rnd);
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fmsubs{
    static const fp_op_t type() {return FMSUB;}
    static const char * name() {return "fmsubs";}
    static const bool single_prec_operation = true;
    static const bool rc = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      return mpfr_fms(*frd,*fra,*frc,*frb,rnd);
    };
  };

  struct PPC_fmsubs_ {
    static const fp_op_t type() {return FMSUB;}
    static const char * name() {return "fmsubs.";}
    static const bool single_prec_operation = true;
    static const bool rc = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      return mpfr_fms(*frd,*fra,*frc,*frb,rnd);
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fmul{
    static const fp_op_t type() {return FMUL;}
    static const char * name() {return "fmul";}
    static const bool single_prec_operation = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frc,mp_rnd_t rnd){
      return mpfr_mul(*frd,*fra,*frc,rnd);
    };
    static const bool rc = false;
  };

  struct PPC_fmul_{
    static const fp_op_t type() {return FMUL;}
    static const char * name() {return "fmul.";}
    static const bool single_prec_operation = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frc,mp_rnd_t rnd){
      return mpfr_mul(*frd,*fra,*frc,rnd);
    };
    static const bool rc = true;
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fmuls{
    static const fp_op_t type() {return FMUL;}
    static const char * name() {return "fmuls";}
    static const bool single_prec_operation = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frc,mp_rnd_t rnd){
      return mpfr_mul(*frd,*fra,*frc,rnd);
    };
    static const bool rc = false;
  };

  struct PPC_fmuls_{
    static const fp_op_t type() {return FMUL;}
    static const char * name() {return "fmuls.";}
    static const bool single_prec_operation = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frc,mp_rnd_t rnd){
      return mpfr_mul(*frd,*fra,*frc,rnd);
    };
    static const bool rc = true;
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fnabs : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_fnabs(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  struct PPC_fnabs_ : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_fnabs_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fneg : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_fneg(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  struct PPC_fneg_ : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_fneg_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fnmadd {
    static const fp_op_t type() {return FMADD;}
    static const char * name() {return "fnmadd";}
    static const bool single_prec_operation = false;
    static const bool rc = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      int inext= mpfr_fma(*frd,*fra,*frc,*frb,rnd);
      inext = mpfr_neg(*frd,*frd,rnd);
      return inext;
    };
  };

  struct PPC_fnmadd_ {
    static const fp_op_t type() {return FMADD;}
    static const char * name() {return "fnmadd.";}
    static const bool single_prec_operation = false;
    static const bool rc = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      int inext= mpfr_fma(*frd,*fra,*frc,*frb,rnd);
      inext = mpfr_neg(*frd,*frd,rnd);
      return inext;
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fnmadds{
    static const fp_op_t type() {return FMADD;}
    static const char * name() {return "fnmadds";}
    static const bool single_prec_operation = true;
    static const bool rc = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      int inext= mpfr_fma(*frd,*fra,*frc,*frb,rnd);
      inext = mpfr_neg(*frd,*frd,rnd);
      return inext;
    };
  };

  struct PPC_fnmadds_{
    static const fp_op_t type() {return FMADD;}
    static const char * name() {return "fnmadds.";}
    static const bool single_prec_operation = true;
    static const bool rc = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      int inext= mpfr_fma(*frd,*fra,*frc,*frb,rnd);
      inext = mpfr_neg(*frd,*frd,rnd);
      return inext;
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fnmsub {
    static const fp_op_t type() {return FMSUB;}
    static const char * name() {return "fnmsub";}
    static const bool single_prec_operation = false;
    static const bool rc = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      int inext= mpfr_fms(*frd,*fra,*frc,*frb,rnd);
      inext = mpfr_neg(*frd,*frd,rnd);
      return inext;
    };
  };

  struct PPC_fnmsub_  {
    static const fp_op_t type() {return FMSUB;}
    static const char * name() {return "fnmsub.";}
    static const bool single_prec_operation = false;
    static const bool rc = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      int inext= mpfr_fms(*frd,*fra,*frc,*frb,rnd);
      inext = mpfr_neg(*frd,*frd,rnd);
      return inext;
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fnmsubs {
    static const fp_op_t type() {return FMSUB;}
    static const char * name() {return "fnmsubs";}
    static const bool single_prec_operation = true;
    static const bool rc = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      int inext= mpfr_fms(*frd,*fra,*frc,*frb,rnd);
      inext = mpfr_neg(*frd,*frd,rnd);
      return inext;
    };
  };

  struct PPC_fnmsubs_ {
    static const fp_op_t type() {return FMSUB;}
    static const char * name() {return "fnmsubs.";}
    static const bool single_prec_operation = true;
    static const bool rc = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,fp_t& frc,mp_rnd_t rnd){
      int inext= mpfr_fms(*frd,*fra,*frc,*frb,rnd);
      inext = mpfr_neg(*frd,*frd,rnd);
      return inext;
    };
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fres : public PPC_FP_Instruction {
    uint8_t frt;
    uint8_t fra;
    uint8_t frb;
    uint8_t frc;
    PPC_fres(uint8_t frt, uint8_t fra, uint8_t frb, uint8_t frc);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  struct PPC_fres_ : public PPC_FP_Instruction {
    uint8_t frt;
    uint8_t fra;
    uint8_t frb;
    uint8_t frc;
    PPC_fres_(uint8_t frt, uint8_t fra, uint8_t frb, uint8_t frc);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_frsp : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_frsp(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  struct PPC_frsp_ : public PPC_FP_Instruction {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
    PPC_frsp_(uint8_t rt, uint8_t ra,  uint8_t rb);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_frsqrte : public PPC_FP_Instruction {
    uint8_t frt;
    uint8_t fra;
    uint8_t frb;
    uint8_t frc;
    PPC_frsqrte(uint8_t frt, uint8_t fra, uint8_t frb, uint8_t frc);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  struct PPC_frsqrte_ : public PPC_FP_Instruction {
    uint8_t frt;
    uint8_t fra;
    uint8_t frb;
    uint8_t frc;
    PPC_frsqrte_(uint8_t frt, uint8_t fra, uint8_t frb, uint8_t frc);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fsel : public PPC_FP_Instruction {
    uint8_t frt;
    uint8_t fra;
    uint8_t frb;
    uint8_t frc;
    PPC_fsel(uint8_t frt, uint8_t fra, uint8_t frb, uint8_t frc);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  struct PPC_fsel_ : public PPC_FP_Instruction {
    uint8_t frt;
    uint8_t fra;
    uint8_t frb;
    uint8_t frc;
    PPC_fsel_(uint8_t frt, uint8_t fra, uint8_t frb, uint8_t frc);
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    bool may_branch() const {return false;}
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fsqrt {
    static const fp_op_t type() {return FSQRT;}
    static const char * name() {return "fsqrt";}
    static const bool single_prec_operation = false;
    static const int compute(fp_t& frd,fp_t& frb,mp_rnd_t rnd){
      return mpfr_sqrt(*frd,*frb,rnd);
    };
    static const bool rc = false;
  };

  struct PPC_fsqrt_ {
    static const fp_op_t type() {return FSQRT;}
    static const char * name() {return "fsqrt.";}
    static const bool single_prec_operation = false;
    static const int compute(fp_t& frd,fp_t& frb,mp_rnd_t rnd){
      return mpfr_sqrt(*frd,*frb,rnd);
    };
    static const bool rc = true;

  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fsqrts {
    static const fp_op_t type() {return FSQRT;}
    static const char * name() {return "fsqrts";}
    static const bool single_prec_operation = true;
    static const int compute(fp_t& frd,fp_t& frb,mp_rnd_t rnd){
      return mpfr_sqrt(*frd,*frb,rnd);
    };
    static const bool rc = false;
  };

  struct PPC_fsqrts_ {
    static const fp_op_t type() {return FSQRT;}
    static const char * name() {return "fsqrts.";}
    static const bool single_prec_operation = true;
    static const int compute(fp_t& frd,fp_t& frb,mp_rnd_t rnd){
      return mpfr_sqrt(*frd,*frb,rnd);
    };
    static const bool rc = true;
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fsub {
    static const fp_op_t type() {return FSUB;}
    static const char * name() {return "fsub";}
    static const bool single_prec_operation = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_sub(*frd,*fra,*frb,rnd);
    };
    static const bool rc = false;
  };

  struct PPC_fsub_{
    static const fp_op_t type() {return FSUB;}
    static const char * name() {return "fsub.";}
    static const bool single_prec_operation = false;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_sub(*frd,*fra,*frb,rnd);
    };
    static const bool rc = true;
  };

  /*--------------------------------------------------------------------------*/
  struct PPC_fsubs{
    static const fp_op_t type() {return FSUB;}
    static const char * name() {return "fsubs";}
    static const bool single_prec_operation = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_sub(*frd,*fra,*frb,rnd);
    };
    static const bool rc=false;
  };

  struct PPC_fsubs_{
    static const fp_op_t type() {return FSUB;}
    static const char * name() {return "fsubs.";}
    static const bool single_prec_operation = true;
    static const int compute(fp_t& frd,fp_t& fra,fp_t& frb,mp_rnd_t rnd){
      return mpfr_sub(*frd,*fra,*frb,rnd);
    };
    static const bool rc = true;
  };

  //---------------------------------------------------
  //
  static inline PPC_Instruction* ppc_fabs(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_fabs(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_fabs_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_fabs_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_fadd(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fadd>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fadd_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fadd_>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fadds(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fadds>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fadds_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fadds_>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fcfid(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_fcfid(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_fcfid_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_fcfid_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_fcmpo(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_FPCompare<PPC_fcmpo>(rt>>2, ra, rb);
  }

  static inline PPC_Instruction* ppc_fcmpu(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_FPCompare<PPC_fcmpu>(rt>>2, ra, rb);
  }

  static inline PPC_Instruction* ppc_fctid(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_FPConvert<PPC_fctid>(rt, rb);
  }

  static inline PPC_Instruction* ppc_fctid_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_FPConvert<PPC_fctid_>(rt, rb);
  }

  static inline PPC_Instruction* ppc_fctidz(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_FPConvert<PPC_fctidz>(rt, rb);
  }

  static inline PPC_Instruction* ppc_fctidz_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_FPConvert<PPC_fctidz_>(rt, rb);
  }

  static inline PPC_Instruction* ppc_fctiw(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_FPConvert<PPC_fctiw>(rt, rb);
  }

  static inline PPC_Instruction* ppc_fctiw_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_FPConvert<PPC_fctiw_>(rt, rb);
  }

  static inline PPC_Instruction* ppc_fctiwz(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_FPConvert<PPC_fctiwz>(rt, rb);
  }

  static inline PPC_Instruction* ppc_fctiwz_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_FPConvert<PPC_fctiwz_>(rt, rb);
  }

  static inline PPC_Instruction* ppc_fdiv(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fdiv>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fdiv_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fdiv_>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fdivs(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fdivs>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fdivs_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fdivs_>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fmadd(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fmadd>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fmadd_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fmadd_>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fmadds(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fmadds>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fmadds_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fmadds_>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fmr(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_fmr(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_fmr_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_fmr_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_fmsub(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fmsub>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fmsub_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fmsub_>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fmsubs(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fmsubs>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fmsubs_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fmsubs_>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fmul(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fmul>(frt, fra, frc);
  }

  static inline PPC_Instruction* ppc_fmul_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fmul_>(frt, fra, frc);
  }

  static inline PPC_Instruction* ppc_fmuls(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fmuls>(frt, fra, frc);
  }

  static inline PPC_Instruction* ppc_fmuls_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fmuls_>(frt, fra, frc);
  }

  static inline PPC_Instruction* ppc_fnabs(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_fnabs(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_fnabs_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_fnabs_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_fneg(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_fneg(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_fneg_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_fneg_(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_fnmadd(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fnmadd>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fnmadd_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fnmadd_>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fnmadds(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fnmadds>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fnmadds_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fnmadds_>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fnmsub(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fnmsub>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fnmsub_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fnmsub_>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fnmsubs(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fnmsubs>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fnmsubs_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPMultiAdd<PPC_fnmsubs_>(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fres(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_fres(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fres_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_fres_(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_frsp(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_frsp(rt, ra, rb);
  }

  static inline PPC_Instruction* ppc_frsp_(uint32_t instr) {
    uint8_t rt, ra, rb;
    PPC_X_FORM(instr, rt, ra, rb);
    return new PPC_frsp_(rt, ra, rb);
  }
  //todo
  static inline PPC_Instruction* ppc_frsqrte(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_frsqrte(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_frsqrte_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_frsqrte_(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fsel(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_fsel(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fsel_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_fsel_(frt, fra, frb, frc);
  }

  static inline PPC_Instruction* ppc_fsqrt(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic_1op<PPC_fsqrt>(frt, frb);
  }

  static inline PPC_Instruction* ppc_fsqrt_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic_1op<PPC_fsqrt_>(frt, frb);
  }

  static inline PPC_Instruction* ppc_fsqrts(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic_1op<PPC_fsqrts>(frt, frb);
  }

  static inline PPC_Instruction* ppc_fsqrts_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic_1op<PPC_fsqrts_>(frt, frb);
  }

  static inline PPC_Instruction* ppc_fsub(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fsub>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fsub_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fsub_>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fsubs(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fsubs>(frt, fra, frb);
  }

  static inline PPC_Instruction* ppc_fsubs_(uint32_t instr) {
    uint8_t frt, fra, frb, frc;
    PPC_A_FORM(instr, frt, fra, frb, frc);
    return new PPC_FPArithmetic<PPC_fsubs_>(frt, fra, frb);
  }
} // namespace simsoc

#include "ppcis_fpu.tpp"

#endif // PPCIS_FPU_HPP
