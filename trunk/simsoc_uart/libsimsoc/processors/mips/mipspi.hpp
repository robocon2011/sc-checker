//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPSPI_HPP
#define MIPSPI_HPP

#include <libsimsoc/processors/common.hpp>

namespace simsoc {

  // forward declaration
  template <typename word_t> class MIPS_Processor;
  template <typename word_t> class MIPS_Instruction;

  template <typename word_t>
  struct MIPS_PseudoGeneric {
    MIPS_Instruction<word_t> *instr;
  };

  struct MIPS_Rform {
    uint8_t rs;
    uint8_t rt;
    uint8_t rd;
  };

  struct MIPS_R1form {
    uint8_t rs;
    uint8_t rd;
  };

  struct MIPS_Iform {
    uint8_t rs;
    uint8_t rt;
    uint32_t immed;
  };

  struct MIPS_LSform {
    uint8_t base;
    uint8_t rt;
    uint32_t offset;
  };

  struct MIPS_Jform {
    uint32_t target_addr;
  };

  struct MIPS_JR1form {
    uint8_t rs;
    uint8_t rd;
    uint8_t hint;
  };

  struct MIPS_JR2form {
    uint8_t rs;
    uint8_t hint;
  };

  struct MIPS_Bform {
    uint32_t branch_offset;
  };

  struct MIPS_BRform {
    uint8_t rs;
    uint8_t rt;
    uint32_t branch_offset;
  };

  struct MIPS_BIform {
    uint8_t rs;
    uint32_t branch_offset;
  };

  struct MIPS_RTIform {
    uint8_t rt;
    uint32_t immed;
  };

  struct MIPS_WAITform {
    uint32_t implement;
  };

  struct MIPS_CACHEform {
    uint8_t base;
    uint8_t op;
    uint32_t offset;
  };

  struct MIPS_SHform {
    uint8_t rt;
    uint8_t rd;
    uint8_t sa;
  };

  struct MIPS_TRform {
    uint8_t rs;
    uint8_t rt;
  };

  struct MIPS_TIform {
    uint8_t rs;
    uint32_t immed;
  };

  struct MIPS_MDform {
    uint8_t rs;
    uint8_t rt;
  };

  struct MIPS_MTform {
    uint8_t rs;
  };

  struct MIPS_MFform {
    uint8_t rd;
  };

  struct MIPS_MCform {
    uint8_t rt;
    uint8_t rd;
    uint8_t sel;
  };

  struct MIPS_Cform {
    uint32_t code;
  };

  struct MIPS_Fform {
    uint8_t rs;
    uint8_t cc;
    uint8_t rd;
  };

  struct MIPS_C2form {
    uint8_t cc;
    uint8_t offset;
  };

  struct MIPS_MC2form{
    uint8_t rs;
    uint8_t rt;
    uint8_t sel;
  };

  template <typename word_t>
  union MIPS_PI_data {
    MIPS_PseudoGeneric<word_t> generic;
    MIPS_Rform R;
    MIPS_R1form R1;
    MIPS_Iform I;
    MIPS_LSform LS;
    MIPS_Jform J;
    MIPS_JR1form JR1;
    MIPS_JR2form JR2;
    MIPS_Bform B;
    MIPS_BRform BR;
    MIPS_BIform BI;
    MIPS_RTIform RTI;
    MIPS_WAITform WAIT;
    MIPS_CACHEform CACHE;
    MIPS_SHform SH;
    MIPS_TRform TR;
    MIPS_TIform TI;
    MIPS_MDform MD;
    MIPS_MTform MT;
    MIPS_MFform MF;
    MIPS_MCform MC;
    MIPS_Cform C;
    MIPS_Fform F;
    MIPS_C2form C2;
    MIPS_MC2form MC2;
  };

  template <typename word_t>
  struct MIPS_PseudoInstruction {
    typedef PseudoStatus (*MIPS_PseudoFunction) (MIPS_Processor<word_t> &proc,
                                                 const MIPS_PseudoInstruction<word_t>& p);
    MIPS_PseudoFunction f;
    MIPS_PI_data<word_t> args;
  };

  template <typename word_t>
  bool isPseudoGeneric(const MIPS_PseudoInstruction<word_t>& pi);

  template <typename word_t>
  void destructPseudo(MIPS_PseudoInstruction<word_t>& pi);

  template <typename word_t>
  void mipsTranslateGeneric(MIPS_PseudoInstruction<word_t> &pi,
                            MIPS_Instruction<word_t> *instr);

  template <typename word_t>
  PseudoStatus mips_pi_add(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_addu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sub(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_subu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_and(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_or(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_xor(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_nor(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_slt(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sltu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sllv(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_srlv(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_srav(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dadd(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_daddu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsub(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsubu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsllv(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsrlv(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsrav(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mul(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_movz(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_movn(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_clz(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_clo(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dclz(MIPS_Processor<word_t> &proc,

                            const MIPS_PseudoInstruction<word_t> &p);
  template <typename word_t>
  PseudoStatus mips_pi_dclo(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_addiu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_addi(MIPS_Processor<word_t> &proc,

                            const MIPS_PseudoInstruction<word_t> &P);
  template <typename word_t>
  PseudoStatus mips_pi_slti(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sltiu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_andi(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_ori(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_xori(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_daddi(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_daddiu(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lb(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lbu(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lh(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lhu(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_ll(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lw(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lwl(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lwr(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lwu(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_ld(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lld(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sd(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_scd(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_ldl(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_ldr(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sb(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sh(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sw(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_swl(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_swr(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sdl(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sdr(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_ldc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lwc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sdc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_swc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_j(MIPS_Processor<word_t> &proc,
                         const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_jal(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_jalr(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_jr(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p);


  template <typename word_t>
  PseudoStatus mips_pi_nop(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_ssnop(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sync(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tlbp(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tlbr(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tlbwi(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tlbwr(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_deret(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_eret(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_b(MIPS_Processor<word_t> &proc,
                         const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_beq(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);
  template <typename word_t>
  PseudoStatus mips_pi_bne(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_beql(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);
  template <typename word_t>
  PseudoStatus mips_pi_bnel(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_blez(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bgtz(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_blezl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bgtzl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bltz(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);
  template <typename word_t>
  PseudoStatus mips_pi_bgez(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bltzl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bgezl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bltzal(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bgezal(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bltzall(MIPS_Processor<word_t> &proc,
                               const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bgezall(MIPS_Processor<word_t> &proc,
                               const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bal(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_lui(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_cfc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_ctc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_wait(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_cache(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sll(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_srl(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sra(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsll(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsrl(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_drotr(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_drotr32(MIPS_Processor<word_t> &proc,
                               const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsbh(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsra(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsll32(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsrl32(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dsra32(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tltu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tge(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tgeu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tlt(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_teq(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tne(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tgei(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tgeiu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tlti(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tltiu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_teqi(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_tnei(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mult(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mutlu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_div(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_divu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dmult(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dmultu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_ddiv(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_ddivu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_madd(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_maddu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_msub(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_msubu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mthi(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mtlo(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mfhi(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mflo(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mfc0(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mtc0(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dmfc0(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dmtc0(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);


  template <typename word_t>
  PseudoStatus mips_pi_break(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_syscall(MIPS_Processor<word_t> &proc,
                               const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_sdbbp(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_movf(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bc2f(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bc2t(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bc2fl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_bc2tl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mfc2(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_mtc2(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dmfc2(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);

  template <typename word_t>
  PseudoStatus mips_pi_dmtc2(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p);


} // namespace simsoc

#include "mipspi.tpp"

#endif //MIPSPI_HPP
