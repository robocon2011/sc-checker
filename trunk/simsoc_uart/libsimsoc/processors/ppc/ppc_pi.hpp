//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_PI_HPP
#define PPC_PI_HPP

#include <libsimsoc/processors/common.hpp>

namespace simsoc {

  // Forward declarations (defined in other files)
  class PPC_Processor;
  class PPC_Instruction;

  // Forward declararion (defined below in this file)
  struct PPC_PseudoInstruction;

  typedef PseudoStatus (*PPC_PseudoFunction) (PPC_Processor &proc,
                                              const PPC_PseudoInstruction& p);

  struct PPC_PseudoGeneric {
    PPC_Instruction *instr;
  };

  struct PPC_Aform {
    uint8_t frt;
    uint8_t fra;
    uint8_t frb;
    uint8_t frc;
  };

  struct PPC_Xform {
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
  };

  struct PPC_Dform{
    uint8_t rt;
    uint8_t ra;
    uint32_t d;
  };

  struct PPC_XFXform{
    uint8_t rt;
    uint16_t spr;
  };

  struct PPC_Iform{
    uint32_t li;
  };

  struct PPC_Bform{
    uint8_t bo;
    uint8_t bi;
    uint32_t bd;
  };

  struct PPC_XLform{
    uint8_t bt;
    uint8_t ba;
    uint8_t bb;
  };

  struct PPC_Mform{
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
    uint8_t me;
  };

  struct PPC_SCform{
    uint8_t lev;
  };

  struct PPC_MDform{
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
    uint8_t mb;
  };

  struct PPC_MDSform{
    uint8_t rs;
    uint8_t ra;
    uint8_t rb;
    uint8_t mb;
  };

  struct PPC_DSform{
    uint8_t rt;
    uint8_t ra;
    uint32_t ds;
  };

  struct PPC_XSform{
    uint8_t rs;
    uint8_t ra;
    uint8_t sh;
  };

  struct PPC_XOform{
    uint8_t rt;
    uint8_t ra;
    uint8_t rb;
  };

  struct PPC_XFLform{
    uint8_t flm;
    uint8_t frb;
  };

  typedef union {
    PPC_PseudoGeneric generic;
    PPC_Aform A;
    PPC_Xform X;
    PPC_Dform D;
    PPC_XFXform XFX;
    PPC_Iform I;
    PPC_Bform B;
    PPC_XLform XL;
    PPC_Mform M;
    PPC_SCform SC;
    PPC_MDform MD;
    PPC_MDSform MDS;
    PPC_DSform DS;
    PPC_XSform XS;
    PPC_XOform XO;
    PPC_XFLform XFL;
  } PPC_PI_data;

  struct PPC_PseudoInstruction {
    PPC_PseudoFunction f;
    PPC_PI_data args;
  };

  void ppcTranslateNextPage(PPC_PseudoInstruction& pi);

  void ppcTranslateGeneric(PPC_PseudoInstruction& pi, PPC_Instruction * instr);

  bool isPseudoGeneric(const PPC_PseudoInstruction& pi);

  void destructPseudo(PPC_PseudoInstruction& pi);

  PseudoStatus ppc_pi_nop(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_add(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_add_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addc(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addc_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addco(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addco_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_adde(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_adde_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addeo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addeo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addis_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addis_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addi_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addi_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addme(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addme_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addmeo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addmeo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addze(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addze_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addzeo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addzeo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_and(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_and_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_andc(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_andc_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divd(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divd_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divdo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divdo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divdu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divdu_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divduo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divduo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divw(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divw_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divwo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divwo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divwu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divwu_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divwuo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_divwuo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_dcbf(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_dcbst(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_dcbtst(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_dcbt(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_dcbz_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_dcbz_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_eqv(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_eqv_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_extsb(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_extsb_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_extsh(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_extsh_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_extsw(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_extsw_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stwu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stw_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stw_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stwbrx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stwbrx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stwcx__ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stwcx__raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stwux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stwx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stwx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_dss(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mfspr(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mfmsr(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mcrf(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_or(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bl(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bla(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_ba(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_ld(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_ldarx(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_ldu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_ldux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_ldx(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfd_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfd_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfdu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfdux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfdx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfdx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfs_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfs_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfsu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfsux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfsx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lfsx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwz_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwz_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwzu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwzux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwzx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwzx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwa_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwa_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwarx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwarx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwaux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwax_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwax_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwbrx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lwbrx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_cmpi(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bc_bo00_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bc_bo01_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bc_bo01_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bc_bo00_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bca_bo00_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bca_bo01_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bca_bo01_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bca_bo00_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcl_bo00_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcl_bo01_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcl_bo01_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcl_bo00_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcla_bo00_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcla_bo01_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcla_bo01_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcla_bo00_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcctr_bo01(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcctr_bo00(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcctrl_bo01(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bcctrl_bo00(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_crand(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_crandc(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_creqv(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_crnand(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_crnor(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_cror(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_crorc(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_crxor(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_ori(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_or_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_orc(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_orc_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stb_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stb_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stbu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stbux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stbx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stbx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_std(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stdcx_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stdu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stdux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stdx(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfd_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfd_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfdu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfdux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfdx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfdx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfiwx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfiwx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfs_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfs_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfsu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfsux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfsx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stfsx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sth_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sth_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sthbrx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sthbrx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sthu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sthux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sthx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sthx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stmw_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stmw_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stswi_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stswi_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stswx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_stswx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtspr(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtcrf(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtmsr(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtmsrd(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtocrf(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtfsb0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtfsb0_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtfsb1(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtfsb1_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtfsf(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtfsf_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtfsfi(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtfsfi_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mfcr(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mfsr(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mfsrin(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mftb(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtsr(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mtsrin(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rfi(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bclr_bo00_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bclr_bo01_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bclr_bo01_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bclr_bo00_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bclrl_bo00_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bclrl_bo01_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bclrl_bo01_bo20(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_bclrl_bo00_bo21(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_eciwx(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_ecowx(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_eieio(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_icbi(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_isync(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mcrfs(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mcrxr(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mfocrf(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mffs(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mffs_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_b(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lbz_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lbz_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lbzu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lbzux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lbzx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lbzx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldcl(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldcl_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldcr(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldcr_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldic(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldic_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldicl(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldicl_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldicr(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldicr_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldimi(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rldimi_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rlwinm(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rlwinm_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rlwimi(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rlwimi_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rlwnm(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_rlwnm_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addic(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_addic_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_srawi(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_srawi_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_srad(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_srad_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sradi(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sradi_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sraw(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sraw_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_xor(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_xor_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subf(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subf_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfc(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfc_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfco(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfco_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfe(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfe_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfeo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfeo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfme(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfme_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfmeo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfmeo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfze(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfze_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfzeo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfzeo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sld(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sld_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_slw(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_slw_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_srd(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_srd_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_srw(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_srw_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_neg(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_neg_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_nego(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_nego_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_cmp(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_cmpl(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_cmpli(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_cntlzd(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_cntlzd_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_cntlzw(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_cntlzw_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sc(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_oris(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_subfic(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_andis_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_andi_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_xori(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_xoris(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lha_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lha_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhau(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhaux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhax_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhax_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhbrx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhbrx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhz_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhz_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhzu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhzux(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhzx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lhzx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lmw(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lswi_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lswi_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lswx_ra0(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_lswx_raS(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulld(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulld_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulldo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulldo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulli(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mullw(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mullw_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mullwo(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mullwo_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulli(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulhw(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulhw_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulhwu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulhwu_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulhd(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulhd_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulhdu(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_mulhdu_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_nand(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_nand_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_nor(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_nor_(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_slbia(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_slbie(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_slbmfee(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_slbmfev(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_slbmte(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_sync(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_td(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_tdi(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_tlbia(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_tlbie(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_tlbsync(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_tw(PPC_Processor &proc, const PPC_PseudoInstruction& p);

  PseudoStatus ppc_twi(PPC_Processor &proc, const PPC_PseudoInstruction& p);

} // namespace simsoc

#endif //PPC_PI_HPP
