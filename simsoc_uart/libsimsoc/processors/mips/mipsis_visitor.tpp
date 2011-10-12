//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mipsis_visitor.hpp"
#include "mips_base.hpp"
#include "mipsis.hpp"
#include "mipsis_arithmetic.hpp"
#include "mipsis_branch.hpp"
#include "mipsis_loadstore.hpp"
#include "mipsis_coprocessor.hpp"
#include <libsimsoc/display.hpp>

namespace simsoc {

  // classes from file mipsis.hpp

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit ( MIPS_Instruction<word_t> *instruction)
  {
    error() <<"internal error: visitor not implemented for instruction: "
            <<*instruction <<std::endl;
    exit(1);
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_FP_Instruction<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_Reserved_Instruction<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_Unpredictable<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_Undefined<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  // classes from file mipsis_arithmetic

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_add<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_addi<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_addiu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_addu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_clo<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_clz<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_div<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_divu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_madd<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_maddu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_msub<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_msubu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_mul<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_mult<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_multu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_slt<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_slti<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sltiu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sltu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sub<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_subu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_and<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_andi<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lui<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_nor<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_xor<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_xori<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_or<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_ori<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_mfhi<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_mflo<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_movf<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_movz<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_movn<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_mthi<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_mtlo<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sll<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sllv<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sra<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_srav<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_srl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_srlv<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsll<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsllv<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsrlv<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsrav<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dmult<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dmultu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_ddiv<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_ddivu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dadd<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_daddu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsub<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsubu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsrl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_drotr<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsra<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsll32<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsrl32<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsra32<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_daddi<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_daddiu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dclo<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dsbh<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_drotr32<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dclz<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  // classes from file mipsis_branch.hpp

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_b<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bal<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_beq<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_beql<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bgez<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bgezal<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bgtz<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_blez<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bltz<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bltzal<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bne<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_j<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_jal<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_jalr<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_jr<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_ssnop<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_nop<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_break<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_syscall<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_teq<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_teqi<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tge<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tgei<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tgeiu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tgeu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tlt<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tlti<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tltiu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tltu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tne<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tnei<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bgezall<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bgezl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bgtzl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_blezl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bltzall<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bltzl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bnel<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_cache<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_deret<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_eret<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_mfc0<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_mtc0<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sdbbp<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tlbp<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tlbr<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tlbwi<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_tlbwr<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_wait<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dmfc0<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dmtc0<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  // classes from file mips_coprocessor.hpp

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bc2f<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bc2t<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bc2fl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_bc2tl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_cfc2<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_ctc2<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_ldc2<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lwc2<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_mfc2<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_mtc2<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sdc2<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_swc2<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dmfc2<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dmtc2<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }


  // classes from file mipsis_loadstore.hpp

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lb<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lbu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lh<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lhu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_ll<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lw<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lwl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lwr<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_pref<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sb<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sc<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sh<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sw<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_swl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_swr<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sync<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dmfc1<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_dmtc1<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_ldl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_ldr<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lwu<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sdl<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sdr<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_lld<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_ld<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_scd<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

  template <typename word_t>
  void MIPS_InstructionVisitor<word_t>::visit (MIPS_sd<word_t> *instruction)
  {
    visit(static_cast<MIPS_Instruction<word_t>*>(instruction));
  }

} // namespace simsoc
