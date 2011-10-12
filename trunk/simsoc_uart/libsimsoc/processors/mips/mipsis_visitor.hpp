//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPSIS_VISITOR_HPP
#define MIPSIS_VISITOR_HPP

namespace simsoc {

  // ABSTRACT Macro defines method as abstract or not with compile time flag

#ifdef ABSTRACT_VISIT_METHOD
#define ABSTRACT = 0
#else
#define ABSTRACT
#endif

  template <typename word_t> class MIPS_Instruction; // the default visitor

  // classes from file mipsis.hpp
  template <typename word_t> class MIPS_FP_Instruction;
  template <typename word_t> class MIPS_Reserved_Instruction;
  template <typename word_t> class MIPS_Unpredictable;
  template <typename word_t> class MIPS_Undefined ;

  // classes from file mipsis_arithmetic

  template <typename word_t> class MIPS_add ;
  template <typename word_t> class MIPS_addi ;
  template <typename word_t> class MIPS_addiu ;
  template <typename word_t> class MIPS_addu ;
  template <typename word_t> class MIPS_clo ;
  template <typename word_t> class MIPS_clz ;
  template <typename word_t> class MIPS_div ;
  template <typename word_t> class MIPS_divu ;
  template <typename word_t> class MIPS_madd ;
  template <typename word_t> class MIPS_maddu ;
  template <typename word_t> class MIPS_msub ;
  template <typename word_t> class MIPS_msubu ;
  template <typename word_t> class MIPS_mul ;
  template <typename word_t> class MIPS_mult ;
  template <typename word_t> class MIPS_multu ;
  template <typename word_t> class MIPS_slt ;
  template <typename word_t> class MIPS_slti ;
  template <typename word_t> class MIPS_sltiu ;
  template <typename word_t> class MIPS_sltu ;
  template <typename word_t> class MIPS_sub ;
  template <typename word_t> class MIPS_subu ;
  template <typename word_t> class MIPS_and ;
  template <typename word_t> class MIPS_andi ;
  template <typename word_t> class MIPS_lui ;
  template <typename word_t> class MIPS_nor ;
  template <typename word_t> class MIPS_xor ;
  template <typename word_t> class MIPS_xori ;
  template <typename word_t> class MIPS_or ;
  template <typename word_t> class MIPS_ori ;
  template <typename word_t> class MIPS_mfhi ;
  template <typename word_t> class MIPS_mflo ;
  template <typename word_t> class MIPS_movf ;
  template <typename word_t> class MIPS_movz ;
  template <typename word_t> class MIPS_movn ;
  template <typename word_t> class MIPS_mthi ;
  template <typename word_t> class MIPS_mtlo ;
  template <typename word_t> class MIPS_sll ;
  template <typename word_t> class MIPS_sllv ;
  template <typename word_t> class MIPS_sra ;
  template <typename word_t> class MIPS_srav ;
  template <typename word_t> class MIPS_srl ;
  template <typename word_t> class MIPS_srlv ;
  template <typename word_t> class MIPS_dsll ;
  template <typename word_t> class MIPS_dsllv ;
  template <typename word_t> class MIPS_dsrlv ;
  template <typename word_t> class MIPS_dsrav ;
  template <typename word_t> class MIPS_dmult ;
  template <typename word_t> class MIPS_dmultu ;
  template <typename word_t> class MIPS_ddiv ;
  template <typename word_t> class MIPS_ddivu ;
  template <typename word_t> class MIPS_dadd ;
  template <typename word_t> class MIPS_daddu ;
  template <typename word_t> class MIPS_dsub ;
  template <typename word_t> class MIPS_dsubu ;
  template <typename word_t> class MIPS_dsrl ;
  template <typename word_t> class MIPS_drotr ;
  template <typename word_t> class MIPS_dsra ;
  template <typename word_t> class MIPS_dsll32 ;
  template <typename word_t> class MIPS_dsrl32 ;
  template <typename word_t> class MIPS_dsra32 ;
  template <typename word_t> class MIPS_daddi ;
  template <typename word_t> class MIPS_daddiu ;
  template <typename word_t> class MIPS_dclo ;
  template <typename word_t> class MIPS_dsbh ;
  template <typename word_t> class MIPS_drotr32 ;
  template <typename word_t> class MIPS_dclz ;

  // classes from file mipsis_branch.hpp
  template <typename word_t> class MIPS_b ;
  template <typename word_t> class MIPS_bal ;
  template <typename word_t> class MIPS_beq ;
  template <typename word_t> class MIPS_beql ;
  template <typename word_t> class MIPS_bgez ;
  template <typename word_t> class MIPS_bgezal ;
  template <typename word_t> class MIPS_bgtz ;
  template <typename word_t> class MIPS_blez ;
  template <typename word_t> class MIPS_bltz ;
  template <typename word_t> class MIPS_bltzal ;
  template <typename word_t> class MIPS_bne ;
  template <typename word_t> class MIPS_j ;
  template <typename word_t> class MIPS_jal ;
  template <typename word_t> class MIPS_jalr ;
  template <typename word_t> class MIPS_jr ;
  template <typename word_t> class MIPS_ssnop ;
  template <typename word_t> class MIPS_nop ;
  template <typename word_t> class MIPS_break ;
  template <typename word_t> class MIPS_syscall ;
  template <typename word_t> class MIPS_teq ;
  template <typename word_t> class MIPS_teqi ;
  template <typename word_t> class MIPS_tge ;
  template <typename word_t> class MIPS_tgei ;
  template <typename word_t> class MIPS_tgeiu ;
  template <typename word_t> class MIPS_tgeu ;
  template <typename word_t> class MIPS_tlt ;
  template <typename word_t> class MIPS_tlti ;
  template <typename word_t> class MIPS_tltiu ;
  template <typename word_t> class MIPS_tltu ;
  template <typename word_t> class MIPS_tne ;
  template <typename word_t> class MIPS_tnei ;
  template <typename word_t> class MIPS_bgezall ;
  template <typename word_t> class MIPS_bgezl ;
  template <typename word_t> class MIPS_bgtzl ;
  template <typename word_t> class MIPS_blezl ;
  template <typename word_t> class MIPS_bltzall ;
  template <typename word_t> class MIPS_bltzl ;
  template <typename word_t> class MIPS_bnel ;
  template <typename word_t> class MIPS_cache ;
  template <typename word_t> class MIPS_deret ;
  template <typename word_t> class MIPS_eret ;
  template <typename word_t> class MIPS_mfc0 ;
  template <typename word_t> class MIPS_mtc0 ;
  template <typename word_t> class MIPS_sdbbp ;
  template <typename word_t> class MIPS_tlbp ;
  template <typename word_t> class MIPS_tlbr ;
  template <typename word_t> class MIPS_tlbwi ;
  template <typename word_t> class MIPS_tlbwr ;
  template <typename word_t> class MIPS_wait ;
  template <typename word_t> class MIPS_dmfc0 ;
  template <typename word_t> class MIPS_dmtc0 ;

  // classes from file mips_coprocessor.hpp
  template <typename word_t> class MIPS_bc2f ;
  template <typename word_t> class MIPS_bc2t ;
  template <typename word_t> class MIPS_bc2fl ;
  template <typename word_t> class MIPS_bc2tl ;
  template <typename word_t> class MIPS_cfc2 ;
  template <typename word_t> class MIPS_ctc2 ;
  template <typename word_t> class MIPS_ldc2 ;
  template <typename word_t> class MIPS_lwc2 ;
  template <typename word_t> class MIPS_mfc2 ;
  template <typename word_t> class MIPS_mtc2 ;
  template <typename word_t> class MIPS_sdc2 ;
  template <typename word_t> class MIPS_swc2 ;
  template <typename word_t> class MIPS_dmfc2 ;
  template <typename word_t> class MIPS_dmtc2 ;

  // classes from file mipsis_loadstore.hpp

  template <typename word_t> class MIPS_lb ;
  template <typename word_t> class MIPS_lbu ;
  template <typename word_t> class MIPS_lh ;
  template <typename word_t> class MIPS_lhu ;
  template <typename word_t> class MIPS_ll ;
  template <typename word_t> class MIPS_lw ;
  template <typename word_t> class MIPS_lwl ;
  template <typename word_t> class MIPS_lwr ;
  template <typename word_t> class MIPS_pref ;
  template <typename word_t> class MIPS_sb ;
  template <typename word_t> class MIPS_sc ;
  template <typename word_t> class MIPS_sh ;
  template <typename word_t> class MIPS_sw ;
  template <typename word_t> class MIPS_swl ;
  template <typename word_t> class MIPS_swr ;
  template <typename word_t> class MIPS_sync ;
  template <typename word_t> class MIPS_dmfc1 ;
  template <typename word_t> class MIPS_dmtc1 ;
  template <typename word_t> class MIPS_ldl ;
  template <typename word_t> class MIPS_ldr ;
  template <typename word_t> class MIPS_lwu ;
  template <typename word_t> class MIPS_sdl ;
  template <typename word_t> class MIPS_sdr ;
  template <typename word_t> class MIPS_lld ;
  template <typename word_t> class MIPS_ld ;
  template <typename word_t> class MIPS_scd ;
  template <typename word_t> class MIPS_sd ;

  template <typename word_t>
  class MIPS_InstructionVisitor {
  public:
    virtual void visit (MIPS_Instruction<word_t> *instruction) ABSTRACT ;

    // classes from file mipsis.hpp
    virtual void visit (MIPS_FP_Instruction<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_Reserved_Instruction<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_Unpredictable<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_Undefined<word_t> *instruction ) ABSTRACT ;

    // classes from file mipsis_arithmetic

    virtual void visit (MIPS_add<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_addi<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_addiu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_addu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_clo<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_clz<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_div<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_divu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_madd<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_maddu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_msub<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_msubu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_mul<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_mult<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_multu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_slt<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_slti<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sltiu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sltu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sub<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_subu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_and<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_andi<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_lui<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_nor<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_xor<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_xori<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_or<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_ori<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_mfhi<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_mflo<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_movf<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_movz<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_movn<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_mthi<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_mtlo<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sll<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sllv<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sra<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_srav<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_srl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_srlv<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsll<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsllv<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsrlv<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsrav<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dmult<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dmultu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_ddiv<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_ddivu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dadd<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_daddu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsub<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsubu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsrl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_drotr<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsra<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsll32<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsrl32<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsra32<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_daddi<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_daddiu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dclo<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dsbh<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_drotr32<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dclz<word_t> *instruction ) ABSTRACT ;

    // classes from file mipsis_branch.hpp
    virtual void visit (MIPS_b<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bal<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_beq<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_beql<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bgez<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bgezal<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bgtz<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_blez<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bltz<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bltzal<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bne<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_j<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_jal<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_jalr<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_jr<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_ssnop<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_nop<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_break<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_syscall<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_teq<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_teqi<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tge<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tgei<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tgeiu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tgeu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tlt<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tlti<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tltiu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tltu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tne<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tnei<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bgezall<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bgezl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bgtzl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_blezl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bltzall<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bltzl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bnel<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_cache<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_deret<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_eret<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_mfc0<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_mtc0<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sdbbp<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tlbp<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tlbr<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tlbwi<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_tlbwr<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_wait<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dmfc0<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dmtc0<word_t> *instruction ) ABSTRACT ;

    // classes from file mips_coprocessor.hpp
    virtual void visit (MIPS_bc2f<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bc2t<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bc2fl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_bc2tl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_cfc2<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_ctc2<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_ldc2<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_lwc2<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_mfc2<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_mtc2<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sdc2<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_swc2<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dmfc2<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dmtc2<word_t> *instruction ) ABSTRACT ;

    // classes from file mipsis_loadstore.hpp

    virtual void visit (MIPS_lb<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_lbu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_lh<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_lhu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_ll<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_lw<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_lwl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_lwr<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_pref<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sb<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sc<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sh<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sw<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_swl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_swr<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sync<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dmfc1<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_dmtc1<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_ldl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_ldr<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_lwu<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sdl<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sdr<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_lld<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_ld<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_scd<word_t> *instruction ) ABSTRACT ;
    virtual void visit (MIPS_sd<word_t> *instruction ) ABSTRACT ;

  } ;

} // namespace simsoc

#endif // MIPSIS_VISITOR_H
