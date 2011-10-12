//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mips_translator.hpp"
#include "mipspi.hpp"
#include "mipsis.hpp"
#include "mipsis_arithmetic.hpp"
#include "mipsis_branch.hpp"
#include "mipsis_loadstore.hpp"
#include "mipsis_coprocessor.hpp"

namespace simsoc {

  // constructor
  template <typename word_t>
  MIPS_Translator<word_t>::MIPS_Translator(MIPS_Processor<word_t> &processor,
                                           MIPS_Instruction<word_t> *instr,
                                           MIPS_PseudoInstruction<word_t> &pseudo):
    proc(processor), pi(pseudo)
  {
    instr->accept(*this);
  }

  // destructor
  template <typename word_t>
  MIPS_Translator<word_t>::~MIPS_Translator () {}

  // Now all the translation functions for each instruction type

  template <typename word_t>
  void MIPS_Translator<word_t>::visit(MIPS_Instruction<word_t> *i) {
    error() <<"internal error: visitor not implemented for instruction: "
            <<*i <<std::endl;
    exit(1);
    // FIXME: once all instructions are implemented,
    //        replace code above by "UNREACHABLE;".
  }

  // classes from file mipsis.hpp

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit(MIPS_FP_Instruction<word_t> *i)
  {
    mipsTranslateGeneric(pi, i);
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit(MIPS_Reserved_Instruction<word_t> *i)
  {
    mipsTranslateGeneric(pi, i);
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_Unpredictable<word_t> *i)
  {
    mipsTranslateGeneric(pi, i);
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_Undefined<word_t> *i)
  {
    mipsTranslateGeneric(pi, i);
  }

  // classes from file mipsis_arithmetic

  template <typename word_t>
  void MIPS_Translator<word_t>::visit (MIPS_add<word_t> *i)
  {
    pi.f = mips_pi_add;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_addi<word_t> *i)
  {
    pi.f = mips_pi_addi;
    pi.args.I.rs = i->rs;
    pi.args.I.rt = i->rt;
    pi.args.I.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_addiu<word_t> *i)
  {
    pi.f = mips_pi_addiu;
    pi.args.I.rs = i->rs;
    pi.args.I.rt = i->rt;
    pi.args.I.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_addu<word_t> *i)
  {
    pi.f = mips_pi_addu;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_clo<word_t> *i)
  { pi.f = mips_pi_clo;
    pi.args.R1.rs = i->rs;
    pi.args.R1.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_clz<word_t> *i)
  { pi.f = mips_pi_clz;
    pi.args.R1.rs = i->rs;
    pi.args.R1.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_div<word_t> *i)
  { pi.f = mips_pi_div;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_divu<word_t> *i)
  { pi.f = mips_pi_divu;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_madd<word_t> *i)
  { pi.f = mips_pi_madd;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_maddu<word_t> *i)
  { pi.f = mips_pi_maddu;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_msub<word_t> *i)
  { pi.f = mips_pi_msub;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_msubu<word_t> *i)
  { pi.f = mips_pi_msubu;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_mul<word_t> *i)
  {
    pi.f = mips_pi_mul;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_mult<word_t> *i)
  { pi.f = mips_pi_mult;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_multu<word_t> *i)
  { pi.f = mips_pi_multu;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_slt<word_t> *i)
  { pi.f = mips_pi_slt;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_slti<word_t> *i)
  { pi.f = mips_pi_slti;
    pi.args.I.rs = i->rs;
    pi.args.I.rt = i->rt;
    pi.args.I.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sltiu<word_t> *i)
  { pi.f = mips_pi_sltiu;
    pi.args.I.rs = i->rs;
    pi.args.I.rt = i->rt;
    pi.args.I.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sltu<word_t> *i)
  {
    pi.f = mips_pi_sltu;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sub<word_t> *i)
  {
    pi.f = mips_pi_sub;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_subu<word_t> *i)
  {
    pi.f = mips_pi_subu;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_and<word_t> *i)
  {
    pi.f = mips_pi_and;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_andi<word_t> *i)
  { pi.f = mips_pi_andi;
    pi.args.I.rs = i->rs;
    pi.args.I.rt = i->rt;
    pi.args.I.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lui<word_t> *i)
  { pi.f = mips_pi_lui;
    pi.args.RTI.rt = i->rt;
    pi.args.RTI.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_nor<word_t> *i)
  {
    pi.f = mips_pi_nor;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_xor<word_t> *i)
  {
    pi.f = mips_pi_xor;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_xori<word_t> *i)
  { pi.f = mips_pi_xori;
    pi.args.I.rs = i->rs;
    pi.args.I.rt = i->rt;
    pi.args.I.immed = i->immed;

  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_or<word_t> *i)
  {
    pi.f = mips_pi_or;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_ori<word_t> *i)
  { pi.f = mips_pi_ori;
    pi.args.I.rs = i->rs;
    pi.args.I.rt = i->rt;
    pi.args.I.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_mfhi<word_t> *i)
  { pi.f = mips_pi_mfhi;
    pi.args.MF.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_mflo<word_t> *i)
  { pi.f = mips_pi_mflo;
    pi.args.MF.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_movf<word_t> *i)
  { pi.f = mips_pi_movf;
    pi.args.F.rs = i->rs;
    pi.args.F.cc = i->cc;
    pi.args.F.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_movz<word_t> *i)
  {
    pi.f = mips_pi_movz;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_movn<word_t> *i)
  {
    pi.f = mips_pi_movn;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_mthi<word_t> *i)
  { pi.f = mips_pi_mthi;
    pi.args.MT.rs = i->rs;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_mtlo<word_t> *i)
  { pi.f = mips_pi_mtlo;
    pi.args.MT.rs = i->rs;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sll<word_t> *i)
  { pi.f = mips_pi_sll;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sllv<word_t> *i)
  {
    pi.f = mips_pi_sllv;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sra<word_t> *i)
  {pi.f = mips_pi_sra;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_srav<word_t> *i)
  {
    pi.f = mips_pi_srav;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_srl<word_t> *i)
  { pi.f = mips_pi_srl;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_srlv<word_t> *i)
  {
    pi.f = mips_pi_srlv;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsll<word_t> *i)
  { pi.f = mips_pi_dsll;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsllv<word_t> *i)
  {
    pi.f = mips_pi_dsllv;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsrlv<word_t> *i)
  {
    pi.f = mips_pi_dsrlv;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsrav<word_t> *i)
  {
    pi.f = mips_pi_dsrav;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dmult<word_t> *i)
  { pi.f = mips_pi_dmult;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dmultu<word_t> *i)
  { pi.f = mips_pi_dmultu;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_ddiv<word_t> *i)
  { pi.f = mips_pi_ddiv;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_ddivu<word_t> *i)
  { pi.f = mips_pi_ddivu;
    pi.args.MD.rs = i->rs;
    pi.args.MD.rt = i->rt;  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dadd<word_t> *i)
  { pi.f = mips_pi_dadd;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_daddu<word_t> *i)
  {
    pi.f = mips_pi_daddu;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsub<word_t> *i)
  { pi.f = mips_pi_dsub;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsubu<word_t> *i)
  { pi.f = mips_pi_dsubu;
    pi.args.R.rs = i->rs;
    pi.args.R.rt = i->rt;
    pi.args.R.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsrl<word_t> *i)
  { pi.f = mips_pi_dsrl;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_drotr<word_t> *i)
  { pi.f = mips_pi_drotr;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsra<word_t> *i)
  { pi.f = mips_pi_dsra;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsll32<word_t> *i)
  { pi.f = mips_pi_dsll32;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsrl32<word_t> *i)
  { pi.f = mips_pi_dsrl32;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsra32<word_t> *i)
  { pi.f = mips_pi_dsra32;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_daddi<word_t> *i)
  { pi.f = mips_pi_daddi;
    pi.args.I.rs = i->rs;
    pi.args.I.rt = i->rt;
    pi.args.I.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_daddiu<word_t> *i)
  { pi.f = mips_pi_daddiu;
    pi.args.I.rs = i->rs;
    pi.args.I.rt = i->rt;
    pi.args.I.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dclo<word_t> *i)
  { pi.f = mips_pi_dclo;
    pi.args.R1.rs = i->rs;
    pi.args.R1.rd = i->rd;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dsbh<word_t> *i)
  { pi.f = mips_pi_dsbh;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_drotr32<word_t> *i)
  { pi.f = mips_pi_drotr32;
    pi.args.SH.rt = i->rt;
    pi.args.SH.rd = i->rd;
    pi.args.SH.sa = i->sa;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dclz<word_t> *i)
  { pi.f = mips_pi_dclz;
    pi.args.R1.rs = i->rs;
    pi.args.R1.rd = i->rd;
  }

  // classes from file mipsis_branch.hpp

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_b<word_t> *i)
  { pi.f = mips_pi_b;
    pi.args.B.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bal<word_t> *i)
  { pi.f = mips_pi_bal;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_beq<word_t> *i)
  { pi.f = mips_pi_beq;
    pi.args.BR.rs = i->rs;
    pi.args.BR.rt = i->rt;
    pi.args.BR.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_beql<word_t> *i)
  { pi.f = mips_pi_beql;
    pi.args.BR.rs = i->rs;
    pi.args.BR.rt = i->rt;
    pi.args.BR.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bgez<word_t> *i)
  { pi.f = mips_pi_bgez;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bgezal<word_t> *i)
  { pi.f = mips_pi_bgezal;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bgtz<word_t> *i)
  { pi.f = mips_pi_bgtz;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_blez<word_t> *i)
  { pi.f = mips_pi_blez;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bltz<word_t> *i)
  { pi.f = mips_pi_bltz;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bltzal<word_t> *i)
  { pi.f = mips_pi_bltzal;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bne<word_t> *i)
  { pi.f = mips_pi_bne;
    pi.args.BR.rs = i->rs;
    pi.args.BR.rt = i->rt;
    pi.args.BR.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_j<word_t> *i)
  { pi.f = mips_pi_j;
    pi.args.J.target_addr = i->target_addr;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_jal<word_t> *i)
  { pi.f = mips_pi_jal;
    pi.args.J.target_addr = i->target_addr;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_jalr<word_t> *i)
  { pi.f = mips_pi_jalr;
    pi.args.JR1.rs = i->rs;
    pi.args.JR1.rd = i->rd;
    pi.args.JR1.hint = i->hint;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_jr<word_t> *i)
  { pi.f = mips_pi_jr;
    pi.args.JR2.rs = i->rs;
    pi.args.JR2.hint = i->hint;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_ssnop<word_t> *i)
  {
    pi.f = mips_pi_ssnop;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_nop<word_t> *i)
  {
    pi.f = mips_pi_nop;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_break<word_t> *i)
  { pi.f = mips_pi_break;
    pi.args.C.code = i->code;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_syscall<word_t> *i)
  { pi.f = mips_pi_syscall;
    pi.args.C.code = i->code;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_teq<word_t> *i)
  { pi.f = mips_pi_teq;
    pi.args.TR.rs = i->rs;
    pi.args.TR.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_teqi<word_t> *i)
  { pi.f = mips_pi_teqi;
    pi.args.TI.rs = i->rs;
    pi.args.TI.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tge<word_t> *i)
  { pi.f = mips_pi_tge;
    pi.args.TR.rs = i->rs;
    pi.args.TR.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tgei<word_t> *i)
  { pi.f = mips_pi_tgei;
    pi.args.TI.rs = i->rs;
    pi.args.TI.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tgeiu<word_t> *i)
  { pi.f = mips_pi_tgeiu;
    pi.args.TI.rs = i->rs;
    pi.args.TI.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tgeu<word_t> *i)
  { pi.f = mips_pi_tgeu;
    pi.args.TR.rs = i->rs;
    pi.args.TR.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tlt<word_t> *i)
  { pi.f = mips_pi_tlt;
    pi.args.TR.rs = i->rs;
    pi.args.TR.rt = i->rt;  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tlti<word_t> *i)
  { pi.f = mips_pi_tlti;
    pi.args.TI.rs = i->rs;
    pi.args.TI.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tltiu<word_t> *i)
  { pi.f = mips_pi_tltiu;
    pi.args.TI.rs = i->rs;
    pi.args.TI.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tltu<word_t> *i)
  { pi.f = mips_pi_tltu;
    pi.args.TR.rs = i->rs;
    pi.args.TR.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tne<word_t> *i)
  { pi.f = mips_pi_tne;
    pi.args.TR.rs = i->rs;
    pi.args.TR.rt = i->rt;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tnei<word_t> *i)
  { pi.f = mips_pi_tnei;
    pi.args.TI.rs = i->rs;
    pi.args.TI.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bgezall<word_t> *i)
  { pi.f = mips_pi_bgezall;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bgezl<word_t> *i)
  { pi.f = mips_pi_bgezl;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bgtzl<word_t> *i)
  { pi.f = mips_pi_bgtzl;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_blezl<word_t> *i)
  { pi.f = mips_pi_blezl;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bltzall<word_t> *i)
  { pi.f = mips_pi_bltzall;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bltzl<word_t> *i)
  { pi.f = mips_pi_bltzl;
    pi.args.BI.rs = i->rs;
    pi.args.BI.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bnel<word_t> *i)
  { pi.f = mips_pi_bnel;
    pi.args.BR.rs = i->rs;
    pi.args.BR.rt = i->rt;
    pi.args.BR.branch_offset = i->branch_offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_cache<word_t> *i)
  { pi.f = mips_pi_cache;
    pi.args.CACHE.base = i->base;
    pi.args.CACHE.op = i->op;
    pi.args.CACHE.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_deret<word_t> *i)
  {
    pi.f = mips_pi_deret;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_eret<word_t> *i)
  {
    pi.f = mips_pi_eret;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_mfc0<word_t> *i)
  { pi.f = mips_pi_mfc0;
    pi.args.MC.rt = i->rt;
    pi.args.MC.rd = i->rd;
    pi.args.MC.sel = i->sel;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_mtc0<word_t> *i)
  { pi.f = mips_pi_mtc0;
    pi.args.MC.rt = i->rt;
    pi.args.MC.rd = i->rd;
    pi.args.MC.sel = i->sel;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sdbbp<word_t> *i)
  { pi.f = mips_pi_sdbbp;
    pi.args.C.code = i->code;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tlbp<word_t> *i)
  {
    pi.f = mips_pi_tlbp;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tlbr<word_t> *i)
  {
    pi.f = mips_pi_tlbr;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tlbwi<word_t> *i)
  {
    pi.f = mips_pi_tlbwi;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_tlbwr<word_t> *i)
  {
    pi.f = mips_pi_tlbwr;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_wait<word_t> *i)
  {
    pi.f = mips_pi_wait;
    pi.args.WAIT.implement = i->implement;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dmfc0<word_t> *i)
  { pi.f = mips_pi_dmfc0;
    pi.args.MC.rt = i->rt;
    pi.args.MC.rd = i->rd;
    pi.args.MC.sel = i->sel;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dmtc0<word_t> *i)
  { pi.f = mips_pi_dmtc0;
    pi.args.MC.rt = i->rt;
    pi.args.MC.rd = i->rd;
    pi.args.MC.sel = i->sel;
  }

  // classes from file mips_coprocessor.hpp

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bc2f<word_t> *i)
  { pi.f = mips_pi_bc2f;
    pi.args.C2.cc = i->cc;
    pi.args.C2.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bc2t<word_t> *i)
  { pi.f = mips_pi_bc2t;
    pi.args.C2.cc = i->cc;
    pi.args.C2.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bc2fl<word_t> *i)
  { pi.f = mips_pi_bc2fl;
    pi.args.C2.cc = i->cc;
    pi.args.C2.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_bc2tl<word_t> *i)
  { pi.f = mips_pi_bc2tl;
    pi.args.C2.cc = i->cc;
    pi.args.C2.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_cfc2<word_t> *i)
  { pi.f = mips_pi_cfc2;
    pi.args.RTI.rt = i->rt;
    pi.args.RTI.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_ctc2<word_t> *i)
  { pi.f = mips_pi_ctc2;
    pi.args.RTI.rt = i->rt;
    pi.args.RTI.immed = i->immed;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_ldc2<word_t> *i)
  { pi.f = mips_pi_ldc2;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lwc2<word_t> *i)
  { pi.f = mips_pi_lwc2;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_mfc2<word_t> *i)
  { pi.f = mips_pi_mfc2;
    pi.args.MC2.rs = i->rs;
    pi.args.MC2.rt = i->rt;
    pi.args.MC2.sel = i->sel;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_mtc2<word_t> *i)
  { pi.f = mips_pi_mtc2;
    pi.args.MC2.rs = i->rs;
    pi.args.MC2.rt = i->rt;
    pi.args.MC2.sel = i->sel;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sdc2<word_t> *i)
  { pi.f = mips_pi_sdc2;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_swc2<word_t> *i)
  { pi.f = mips_pi_swc2;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dmfc2<word_t> *i)
  { pi.f = mips_pi_dmfc2;
    pi.args.MC2.rs = i->rs;
    pi.args.MC2.rt = i->rt;
    pi.args.MC2.sel = i->sel;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dmtc2<word_t> *i)
  { pi.f = mips_pi_dmtc2;
    pi.args.MC2.rs = i->rs;
    pi.args.MC2.rt = i->rt;
    pi.args.MC2.sel = i->sel;
  }

  // classes from file mipsis_loadstore.hpp

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lb<word_t> *i)
  { pi.f = mips_pi_lb;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lbu<word_t> *i)
  { pi.f = mips_pi_lbu;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lh<word_t> *i)
  { pi.f = mips_pi_lh;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lhu<word_t> *i)
  { pi.f = mips_pi_lhu;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_ll<word_t> *i)
  { pi.f = mips_pi_ll;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lw<word_t> *i)
  { pi.f = mips_pi_lw;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lwl<word_t> *i)
  { pi.f = mips_pi_lwl;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lwr<word_t> *i)
  { pi.f = mips_pi_lwr;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_pref<word_t> *i)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(i));
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sb<word_t> *i)
  {
    pi.f = mips_pi_sb;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sc<word_t> *i)
  {
    pi.f = mips_pi_sc;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sh<word_t> *i)
  {
    pi.f = mips_pi_sh;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sw<word_t> *i)
  {
    pi.f = mips_pi_sw;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_swl<word_t> *i)
  { pi.f = mips_pi_swl;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_swr<word_t> *i)
  { pi.f = mips_pi_swr;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sync<word_t> *i)
  {
    pi.f = mips_pi_sync;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dmfc1<word_t> *i)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(i));
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_dmtc1<word_t> *i)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(i));
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_ldl<word_t> *i)
  { pi.f = mips_pi_ldl;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset; }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_ldr<word_t> *i)
  { pi.f = mips_pi_ldr;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lwu<word_t> *i)
  {
    pi.f = mips_pi_lwu;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sdl<word_t> *i)
  { pi.f = mips_pi_sdl;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sdr<word_t> *i)
  { pi.f = mips_pi_sdr;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_lld<word_t> *i)
  { pi.f = mips_pi_lld;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_ld<word_t> *i)
  { pi.f = mips_pi_ld;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_scd<word_t> *i)
  { pi.f = mips_pi_scd;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

  template <typename word_t>
  void  MIPS_Translator<word_t>::visit (MIPS_sd<word_t> *i)
  { pi.f = mips_pi_sd;
    pi.args.LS.base = i->base;
    pi.args.LS.rt = i->rt;
    pi.args.LS.offset = i->offset;
  }

} // namespace simsoc
