//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPCIS_VISITOR_HPP
#define PPCIS_VISITOR_HPP

namespace simsoc {

  // ppcis.hpp
  class PPC_Instruction;
  class PPC_Undefined;
  class PPC_Unpredictable;
  class PPC_Nop;
  class PPC_Break;

  // ppcis_alu.hpp
  class PPC_add;
  class PPC_add_;
  class PPC_addo;
  class PPC_addo_;
  class PPC_addc;
  class PPC_addc_;
  class PPC_addco;
  class PPC_addco_;
  class PPC_adde;
  class PPC_adde_;
  class PPC_addeo;
  class PPC_addeo_;
  class PPC_addi;
  class PPC_addic;
  class PPC_addic_;
  class PPC_addis;
  class PPC_addme;
  class PPC_addme_;
  class PPC_addmeo;
  class PPC_addmeo_;
  class PPC_addze;
  class PPC_addze_;
  class PPC_addzeo;
  class PPC_addzeo_;
  class PPC_and;
  class PPC_and_;
  class PPC_andc;
  class PPC_andc_;
  class PPC_andi_;
  class PPC_andis_;
  class PPC_cmp;
  class PPC_cmpi;
  class PPC_cmpl;
  class PPC_cmpli;
  class PPC_cntlzd;
  class PPC_cntlzd_;
  class PPC_cntlzw;
  class PPC_cntlzw_;
  class PPC_crand;
  class PPC_crandc;
  class PPC_creqv;
  class PPC_crnand;
  class PPC_crnor;
  class PPC_cror;
  class PPC_crorc;
  class PPC_crxor;
  class PPC_divd;
  class PPC_divd_;
  class PPC_divdo;
  class PPC_divdo_;
  class PPC_divdu;
  class PPC_divdu_;
  class PPC_divduo;
  class PPC_divduo_;
  class PPC_divw;
  class PPC_divw_;
  class PPC_divwo;
  class PPC_divwo_;
  class PPC_divwu;
  class PPC_divwu_;
  class PPC_divwuo;
  class PPC_divwuo_;
  class PPC_eqv;
  class PPC_eqv_;
  class PPC_extsb;
  class PPC_extsb_;
  class PPC_extsh;
  class PPC_extsh_;
  class PPC_extsw;
  class PPC_extsw_;
  class PPC_mulhd;
  class PPC_mulhd_;
  class PPC_mulhdu;
  class PPC_mulhdu_;
  class PPC_mulhw;
  class PPC_mulhw_;
  class PPC_mulhwu;
  class PPC_mulhwu_;
  class PPC_mulld;
  class PPC_mulld_;
  class PPC_mulldo_;
  class PPC_mulldo;
  class PPC_mulli;
  class PPC_mullw;
  class PPC_mullw_;
  class PPC_mullwo;
  class PPC_mullwo_;
  class PPC_nand;
  class PPC_nand_;
  class PPC_neg;
  class PPC_neg_;
  class PPC_nego;
  class PPC_nego_;
  class PPC_nor;
  class PPC_nor_;
  class PPC_or;
  class PPC_or_;
  class PPC_orc;
  class PPC_orc_;
  class PPC_ori;
  class PPC_oris;
  class PPC_rldcl;
  class PPC_rldcl_;
  class PPC_rldcr;
  class PPC_rldcr_;
  class PPC_rldic;
  class PPC_rldic_;
  class PPC_rldicl_;
  class PPC_rldicl;
  class PPC_rldicr;
  class PPC_rldicr_;
  class PPC_rldimi;
  class PPC_rldimi_;
  class PPC_rlwimi;
  class PPC_rlwimi_;
  class PPC_rlwinm;
  class PPC_rlwinm_;
  class PPC_rlwnm;
  class PPC_rlwnm_;
  class PPC_sld;
  class PPC_sld_;
  class PPC_slw;
  class PPC_slw_;
  class PPC_srad;
  class PPC_srad_;
  class PPC_sradi;
  class PPC_sradi_;
  class PPC_sraw;
  class PPC_sraw_;
  class PPC_srawi;
  class PPC_srawi_;
  class PPC_srd;
  class PPC_srd_;
  class PPC_srw;
  class PPC_srw_;
  class PPC_subf;
  class PPC_subf_;
  class PPC_subfo;
  class PPC_subfo_;
  class PPC_subfc;
  class PPC_subfc_;
  class PPC_subfco;
  class PPC_subfco_;
  class PPC_subfe;
  class PPC_subfe_;
  class PPC_subfeo;
  class PPC_subfeo_;
  class PPC_subfic;
  class PPC_subfme;
  class PPC_subfme_;
  class PPC_subfmeo;
  class PPC_subfmeo_;
  class PPC_subfze;
  class PPC_subfze_;
  class PPC_subfzeo;
  class PPC_subfzeo_;
  class PPC_xor;
  class PPC_xor_;
  class PPC_xori;
  class PPC_xoris;

  //ppcis_fpu.hpp
  class PPC_FP_Instruction;
  class PPC_fadd;
  class PPC_fadd_;
  class PPC_fadds;
  class PPC_fadds_;
  class PPC_fdiv;
  class PPC_fdiv_;
  class PPC_fdivs;
  class PPC_fdivs_;
  class PPC_fmul;
  class PPC_fmul_;
  class PPC_fmuls;
  class PPC_fmuls_;
  class PPC_fsub;
  class PPC_fsub_;
  class PPC_fsubs;
  class PPC_fsubs_;
  template <class op> class PPC_FPArithmetic;

  class PPC_fsqrt;
  class PPC_fsqrt_;
  class PPC_fsqrts;
  class PPC_fsqrts_;
  template <class op> class PPC_FPArithmetic_1op;

  class PPC_fctid;
  class PPC_fctid_;
  class PPC_fctidz;
  class PPC_fctidz_;
  class PPC_fctiw;
  class PPC_fctiw_;
  class PPC_fctiwz;
  class PPC_fctiwz_;
  template <class op> class PPC_FPConvert;

  class PPC_fcmpo;
  class PPC_fcmpu;
  template <class op> class PPC_FPCompare;

  class PPC_fmadd;
  class PPC_fmadd_;
  class PPC_fmadds;
  class PPC_fmadds_;
  class PPC_fmsub;
  class PPC_fmsub_;
  class PPC_fmsubs;
  class PPC_fmsubs_;
  class PPC_fnmadd;
  class PPC_fnmadd_;
  class PPC_fnmadds;
  class PPC_fnmadds_;
  class PPC_fnmsub;
  class PPC_fnmsub_;
  class PPC_fnmsubs;
  class PPC_fnmsubs_;
  template <class op> class PPC_FPMultiAdd;

  class PPC_fabs;
  class PPC_fabs_;
  class PPC_fcfid;
  class PPC_fcfid_;
  class PPC_fcmpu;
  class PPC_fmr;
  class PPC_fmr_;
  class PPC_fnabs;
  class PPC_fnabs_;
  class PPC_fneg;
  class PPC_fneg_;
  class PPC_fres;
  class PPC_fres_;
  class PPC_frsp;
  class PPC_frsp_;
  class PPC_frsqrte;
  class PPC_frsqrte_;
  class PPC_fsel;
  class PPC_fsel_;

  //ppcis_loadstore.hpp
  class PPC_dcbf;
  class PPC_dcbst;
  class PPC_dcbt;
  class PPC_dcbtst;
  class PPC_dcbz;
  class PPC_lbz;
  class PPC_lbzu;
  class PPC_lbzux;
  class PPC_lbzx;
  class PPC_ld;
  class PPC_ldarx;
  class PPC_ldu;
  class PPC_ldux;
  class PPC_ldx;
  class PPC_lfd;
  class PPC_lfdu;
  class PPC_lfdux;
  class PPC_lfdx;
  class PPC_lfs;
  class PPC_lfsu;
  class PPC_lfsux;
  class PPC_lfsx;
  class PPC_lha;
  class PPC_lhau;
  class PPC_lhaux;
  class PPC_lhax;
  class PPC_lhbrx;
  class PPC_lhz;
  class PPC_lhzu;
  class PPC_lhzux;
  class PPC_lhzx;
  class PPC_lmw;
  class PPC_lswi;
  class PPC_lswx;
  class PPC_lwa;
  class PPC_lwarx;
  class PPC_lwaux;
  class PPC_lwax;
  class PPC_lwbrx;
  class PPC_lwz;
  class PPC_lwzu;
  class PPC_lwzux;
  class PPC_lwzx;
  class PPC_stb;
  class PPC_stbu;
  class PPC_stbux;
  class PPC_stbx;
  class PPC_std;
  class PPC_stdcx_;
  class PPC_stdu;
  class PPC_stdux;
  class PPC_stdx;
  class PPC_stfd;
  class PPC_stfdu;
  class PPC_stfdux;
  class PPC_stfdx;
  class PPC_stfiwx;
  class PPC_stfs;
  class PPC_stfsu;
  class PPC_stfsux;
  class PPC_stfsx;
  class PPC_sth;
  class PPC_sthbrx;
  class PPC_sthu;
  class PPC_sthux;
  class PPC_sthx;
  class PPC_stmw;
  class PPC_stswi;
  class PPC_stswx;
  class PPC_stw;
  class PPC_stwbrx;
  class PPC_stwcx_;
  class PPC_stwu;
  class PPC_stwux;
  class PPC_stwx;
  class PPC_dss;

  //ppcis_misc.hpp
  class PPC_b;
  class PPC_ba;
  class PPC_bl;
  class PPC_bla;
  class PPC_bc;
  class PPC_bca;
  class PPC_bcl;
  class PPC_bcla;
  class PPC_bcctr;
  class PPC_bcctrl;
  class PPC_bclr;
  class PPC_bclrl;
  class PPC_eciwx;
  class PPC_ecowx;
  class PPC_eieio;
  class PPC_icbi;
  class PPC_isync;
  class PPC_mcrf;
  class PPC_mcrfs;
  class PPC_mcrxr;
  class PPC_mfcr;
  class PPC_mfocrf;
  class PPC_mffs;
  class PPC_mffs_;
  class PPC_mfmsr;
  class PPC_mfspr;
  class PPC_mfsr;
  class PPC_mfsrin;
  class PPC_mftb;
  class PPC_mtcrf;
  class PPC_mtocrf;
  class PPC_mtfsb0;
  class PPC_mtfsb0_;
  class PPC_mtfsb1;
  class PPC_mtfsb1_;
  class PPC_mtfsf;
  class PPC_mtfsf_;
  class PPC_mtfsfi;
  class PPC_mtfsfi_;
  class PPC_mtmsr;
  class PPC_mtmsrd;
  class PPC_mtspr;
  class PPC_mtsr;
  class PPC_mtsrin;
  class PPC_rfi;
  class PPC_sc;
  class PPC_slbia;
  class PPC_slbie;
  class PPC_slbmfee;
  class PPC_slbmfev;
  class PPC_slbmte;
  class PPC_sync;
  class PPC_td;
  class PPC_tdi;
  class PPC_tlbia;
  class PPC_tlbie;
  class PPC_tlbsync;
  class PPC_tw;
  class PPC_twi;

  class PPC_InstructionVisitor {
  public:
    virtual ~PPC_InstructionVisitor() {}

    // ppcis.hpp
    virtual void visit(PPC_Instruction &instruction);
    virtual void visit(PPC_Undefined &instruction);
    virtual void visit(PPC_Unpredictable &instruction);
    virtual void visit(PPC_Nop &instruction);
    virtual void visit(PPC_Break &instruction);

    // ppcis_alu.hpp
    virtual void visit(PPC_add &instruction);
    virtual void visit(PPC_add_ &instruction);
    virtual void visit(PPC_addo &instruction);
    virtual void visit(PPC_addo_ &instruction);
    virtual void visit(PPC_addc &instruction);
    virtual void visit(PPC_addc_ &instruction);
    virtual void visit(PPC_addco &instruction);
    virtual void visit(PPC_addco_ &instruction);
    virtual void visit(PPC_adde &instruction);
    virtual void visit(PPC_adde_ &instruction);
    virtual void visit(PPC_addeo &instruction);
    virtual void visit(PPC_addeo_ &instruction);
    virtual void visit(PPC_addi &instruction);
    virtual void visit(PPC_addic &instruction);
    virtual void visit(PPC_addic_ &instruction);
    virtual void visit(PPC_addis &instruction);
    virtual void visit(PPC_addme &instruction);
    virtual void visit(PPC_addme_ &instruction);
    virtual void visit(PPC_addmeo &instruction);
    virtual void visit(PPC_addmeo_ &instruction);
    virtual void visit(PPC_addze &instruction);
    virtual void visit(PPC_addze_ &instruction);
    virtual void visit(PPC_addzeo &instruction);
    virtual void visit(PPC_addzeo_ &instruction);
    virtual void visit(PPC_and &instruction);
    virtual void visit(PPC_and_ &instruction);
    virtual void visit(PPC_andc &instruction);
    virtual void visit(PPC_andc_ &instruction);
    virtual void visit(PPC_andi_ &instruction);
    virtual void visit(PPC_andis_ &instruction);
    virtual void visit(PPC_cmp &instruction);
    virtual void visit(PPC_cmpi &instruction);
    virtual void visit(PPC_cmpl &instruction);
    virtual void visit(PPC_cmpli &instruction);
    virtual void visit(PPC_cntlzd &instruction);
    virtual void visit(PPC_cntlzd_ &instruction);
    virtual void visit(PPC_cntlzw &instruction);
    virtual void visit(PPC_cntlzw_ &instruction);
    virtual void visit(PPC_crand &instruction);
    virtual void visit(PPC_crandc &instruction);
    virtual void visit(PPC_creqv &instruction);
    virtual void visit(PPC_crnand &instruction);
    virtual void visit(PPC_crnor &instruction);
    virtual void visit(PPC_cror &instruction);
    virtual void visit(PPC_crorc &instruction);
    virtual void visit(PPC_crxor &instruction);
    virtual void visit(PPC_divd &instruction);
    virtual void visit(PPC_divd_ &instruction);
    virtual void visit(PPC_divdo &instruction);
    virtual void visit(PPC_divdo_ &instruction);
    virtual void visit(PPC_divdu &instruction);
    virtual void visit(PPC_divdu_ &instruction);
    virtual void visit(PPC_divduo &instruction);
    virtual void visit(PPC_divduo_ &instruction);
    virtual void visit(PPC_divw &instruction);
    virtual void visit(PPC_divw_ &instruction);
    virtual void visit(PPC_divwo &instruction);
    virtual void visit(PPC_divwo_ &instruction);
    virtual void visit(PPC_divwu &instruction);
    virtual void visit(PPC_divwu_ &instruction);
    virtual void visit(PPC_divwuo &instruction);
    virtual void visit(PPC_divwuo_ &instruction);
    virtual void visit(PPC_eqv &instruction);
    virtual void visit(PPC_eqv_ &instruction);
    virtual void visit(PPC_extsb &instruction);
    virtual void visit(PPC_extsb_ &instruction);
    virtual void visit(PPC_extsh &instruction);
    virtual void visit(PPC_extsh_ &instruction);
    virtual void visit(PPC_extsw &instruction);
    virtual void visit(PPC_extsw_ &instruction);
    virtual void visit(PPC_mulhd &instruction);
    virtual void visit(PPC_mulhd_ &instruction);
    virtual void visit(PPC_mulhdu &instruction);
    virtual void visit(PPC_mulhdu_ &instruction);
    virtual void visit(PPC_mulhw &instruction);
    virtual void visit(PPC_mulhw_ &instruction);
    virtual void visit(PPC_mulhwu &instruction);
    virtual void visit(PPC_mulhwu_ &instruction);
    virtual void visit(PPC_mulld &instruction);
    virtual void visit(PPC_mulld_ &instruction);
    virtual void visit(PPC_mulldo_ &instruction);
    virtual void visit(PPC_mulldo &instruction);
    virtual void visit(PPC_mulli &instruction);
    virtual void visit(PPC_mullw &instruction);
    virtual void visit(PPC_mullw_ &instruction);
    virtual void visit(PPC_mullwo &instruction);
    virtual void visit(PPC_mullwo_ &instruction);
    virtual void visit(PPC_nand &instruction);
    virtual void visit(PPC_nand_ &instruction);
    virtual void visit(PPC_neg &instruction);
    virtual void visit(PPC_neg_ &instruction);
    virtual void visit(PPC_nego &instruction);
    virtual void visit(PPC_nego_ &instruction);
    virtual void visit(PPC_nor &instruction);
    virtual void visit(PPC_nor_ &instruction);
    virtual void visit(PPC_or &instruction);
    virtual void visit(PPC_or_ &instruction);
    virtual void visit(PPC_orc &instruction);
    virtual void visit(PPC_orc_ &instruction);
    virtual void visit(PPC_ori &instruction);
    virtual void visit(PPC_oris &instruction);
    virtual void visit(PPC_rldcl &instruction);
    virtual void visit(PPC_rldcl_ &instruction);
    virtual void visit(PPC_rldcr &instruction);
    virtual void visit(PPC_rldcr_ &instruction);
    virtual void visit(PPC_rldic &instruction);
    virtual void visit(PPC_rldic_ &instruction);
    virtual void visit(PPC_rldicl_ &instruction);
    virtual void visit(PPC_rldicl &instruction);
    virtual void visit(PPC_rldicr &instruction);
    virtual void visit(PPC_rldicr_ &instruction);
    virtual void visit(PPC_rldimi &instruction);
    virtual void visit(PPC_rldimi_ &instruction);
    virtual void visit(PPC_rlwimi &instruction);
    virtual void visit(PPC_rlwimi_ &instruction);
    virtual void visit(PPC_rlwinm &instruction);
    virtual void visit(PPC_rlwinm_ &instruction);
    virtual void visit(PPC_rlwnm &instruction);
    virtual void visit(PPC_rlwnm_ &instruction);
    virtual void visit(PPC_sld &instruction);
    virtual void visit(PPC_sld_ &instruction);
    virtual void visit(PPC_slw &instruction);
    virtual void visit(PPC_slw_ &instruction);
    virtual void visit(PPC_srad &instruction);
    virtual void visit(PPC_srad_ &instruction);
    virtual void visit(PPC_sradi &instruction);
    virtual void visit(PPC_sradi_ &instruction);
    virtual void visit(PPC_sraw &instruction);
    virtual void visit(PPC_sraw_ &instruction);
    virtual void visit(PPC_srawi &instruction);
    virtual void visit(PPC_srawi_ &instruction);
    virtual void visit(PPC_srd &instruction);
    virtual void visit(PPC_srd_ &instruction);
    virtual void visit(PPC_srw &instruction);
    virtual void visit(PPC_srw_ &instruction);
    virtual void visit(PPC_subf &instruction);
    virtual void visit(PPC_subf_ &instruction);
    virtual void visit(PPC_subfo &instruction);
    virtual void visit(PPC_subfo_ &instruction);
    virtual void visit(PPC_subfc &instruction);
    virtual void visit(PPC_subfc_ &instruction);
    virtual void visit(PPC_subfco &instruction);
    virtual void visit(PPC_subfco_ &instruction);
    virtual void visit(PPC_subfe &instruction);
    virtual void visit(PPC_subfe_ &instruction);
    virtual void visit(PPC_subfeo &instruction);
    virtual void visit(PPC_subfeo_ &instruction);
    virtual void visit(PPC_subfic &instruction);
    virtual void visit(PPC_subfme &instruction);
    virtual void visit(PPC_subfme_ &instruction);
    virtual void visit(PPC_subfmeo &instruction);
    virtual void visit(PPC_subfmeo_ &instruction);
    virtual void visit(PPC_subfze &instruction);
    virtual void visit(PPC_subfze_ &instruction);
    virtual void visit(PPC_subfzeo &instruction);
    virtual void visit(PPC_subfzeo_ &instruction);
    virtual void visit(PPC_xor &instruction);
    virtual void visit(PPC_xor_ &instruction);
    virtual void visit(PPC_xori &instruction);
    virtual void visit(PPC_xoris &instruction);

    //ppcis_fpu.hpp
    virtual void visit(PPC_FP_Instruction &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fadd> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fadd_> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fadds> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fadds_> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fdiv> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fdiv_> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fdivs> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fdivs_> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fmul> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fmul_> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fmuls> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fmuls_> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fsub> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fsub_> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fsubs> &instruction);
    virtual void visit(PPC_FPArithmetic<PPC_fsubs_> &instruction);
    virtual void visit(PPC_FPArithmetic_1op<PPC_fsqrt> &instruction);
    virtual void visit(PPC_FPArithmetic_1op<PPC_fsqrt_> &instruction);
    virtual void visit(PPC_FPArithmetic_1op<PPC_fsqrts> &instruction);
    virtual void visit(PPC_FPArithmetic_1op<PPC_fsqrts_> &instruction);
    virtual void visit(PPC_FPConvert<PPC_fctid> &instruction);
    virtual void visit(PPC_FPConvert<PPC_fctid_> &instruction);
    virtual void visit(PPC_FPConvert<PPC_fctidz> &instruction);
    virtual void visit(PPC_FPConvert<PPC_fctidz_> &instruction);
    virtual void visit(PPC_FPConvert<PPC_fctiw> &instruction);
    virtual void visit(PPC_FPConvert<PPC_fctiw_> &instruction);
    virtual void visit(PPC_FPConvert<PPC_fctiwz> &instruction);
    virtual void visit(PPC_FPConvert<PPC_fctiwz_> &instruction);
    virtual void visit(PPC_FPCompare<PPC_fcmpo> &instruction);
    virtual void visit(PPC_FPCompare<PPC_fcmpu> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fmadd> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fmadd_> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fmadds> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fmadds_> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fmsub> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fmsub_> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fmsubs> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fmsubs_> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fnmadd> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fnmadd_> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fnmadds> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fnmadds_> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fnmsub> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fnmsub_> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fnmsubs> &instruction);
    virtual void visit(PPC_FPMultiAdd<PPC_fnmsubs_> &instruction);
    virtual void visit(PPC_fabs &instruction);
    virtual void visit(PPC_fabs_ &instruction);
    virtual void visit(PPC_fcfid &instruction);
    virtual void visit(PPC_fcfid_ &instruction);
    virtual void visit(PPC_fmr &instruction);
    virtual void visit(PPC_fmr_ &instruction);
    virtual void visit(PPC_fnabs &instruction);
    virtual void visit(PPC_fnabs_ &instruction);
    virtual void visit(PPC_fneg &instruction);
    virtual void visit(PPC_fneg_ &instruction);
    virtual void visit(PPC_fres &instruction);
    virtual void visit(PPC_fres_ &instruction);
    virtual void visit(PPC_frsp &instruction);
    virtual void visit(PPC_frsp_ &instruction);
    virtual void visit(PPC_frsqrte &instruction);
    virtual void visit(PPC_frsqrte_ &instruction);
    virtual void visit(PPC_fsel &instruction);
    virtual void visit(PPC_fsel_ &instruction);

    //ppcis_loadstore.hpp
    virtual void visit(PPC_dcbf &instruction);
    virtual void visit(PPC_dcbst &instruction);
    virtual void visit(PPC_dcbt &instruction);
    virtual void visit(PPC_dcbtst &instruction);
    virtual void visit(PPC_dcbz &instruction);
    virtual void visit(PPC_lbz &instruction);
    virtual void visit(PPC_lbzu &instruction);
    virtual void visit(PPC_lbzux &instruction);
    virtual void visit(PPC_lbzx &instruction);
    virtual void visit(PPC_ld &instruction);
    virtual void visit(PPC_ldarx &instruction);
    virtual void visit(PPC_ldu &instruction);
    virtual void visit(PPC_ldux &instruction);
    virtual void visit(PPC_ldx &instruction);
    virtual void visit(PPC_lfd &instruction);
    virtual void visit(PPC_lfdu &instruction);
    virtual void visit(PPC_lfdux &instruction);
    virtual void visit(PPC_lfdx &instruction);
    virtual void visit(PPC_lfs &instruction);
    virtual void visit(PPC_lfsu &instruction);
    virtual void visit(PPC_lfsux &instruction);
    virtual void visit(PPC_lfsx &instruction);
    virtual void visit(PPC_lha &instruction);
    virtual void visit(PPC_lhau &instruction);
    virtual void visit(PPC_lhaux &instruction);
    virtual void visit(PPC_lhax &instruction);
    virtual void visit(PPC_lhbrx &instruction);
    virtual void visit(PPC_lhz &instruction);
    virtual void visit(PPC_lhzu &instruction);
    virtual void visit(PPC_lhzux &instruction);
    virtual void visit(PPC_lhzx &instruction);
    virtual void visit(PPC_lmw &instruction);
    virtual void visit(PPC_lswi &instruction);
    virtual void visit(PPC_lswx &instruction);
    virtual void visit(PPC_lwa &instruction);
    virtual void visit(PPC_lwarx &instruction);
    virtual void visit(PPC_lwaux &instruction);
    virtual void visit(PPC_lwax &instruction);
    virtual void visit(PPC_lwbrx &instruction);
    virtual void visit(PPC_lwz &instruction);
    virtual void visit(PPC_lwzu &instruction);
    virtual void visit(PPC_lwzux &instruction);
    virtual void visit(PPC_lwzx &instruction);
    virtual void visit(PPC_stb &instruction);
    virtual void visit(PPC_stbu &instruction);
    virtual void visit(PPC_stbux &instruction);
    virtual void visit(PPC_stbx &instruction);
    virtual void visit(PPC_std &instruction);
    virtual void visit(PPC_stdcx_ &instruction);
    virtual void visit(PPC_stdu &instruction);
    virtual void visit(PPC_stdux &instruction);
    virtual void visit(PPC_stdx &instruction);
    virtual void visit(PPC_stfd &instruction);
    virtual void visit(PPC_stfdu &instruction);
    virtual void visit(PPC_stfdux &instruction);
    virtual void visit(PPC_stfdx &instruction);
    virtual void visit(PPC_stfiwx &instruction);
    virtual void visit(PPC_stfs &instruction);
    virtual void visit(PPC_stfsu &instruction);
    virtual void visit(PPC_stfsux &instruction);
    virtual void visit(PPC_stfsx &instruction);
    virtual void visit(PPC_sth &instruction);
    virtual void visit(PPC_sthbrx &instruction);
    virtual void visit(PPC_sthu &instruction);
    virtual void visit(PPC_sthux &instruction);
    virtual void visit(PPC_sthx &instruction);
    virtual void visit(PPC_stmw &instruction);
    virtual void visit(PPC_stswi &instruction);
    virtual void visit(PPC_stswx &instruction);
    virtual void visit(PPC_stw &instruction);
    virtual void visit(PPC_stwbrx &instruction);
    virtual void visit(PPC_stwcx_ &instruction);
    virtual void visit(PPC_stwu &instruction);
    virtual void visit(PPC_stwux &instruction);
    virtual void visit(PPC_stwx &instruction);
    virtual void visit(PPC_dss &instruction);

    //ppcis_misc.hpp
    virtual void visit(PPC_b &instruction);
    virtual void visit(PPC_ba &instruction);
    virtual void visit(PPC_bl &instruction);
    virtual void visit(PPC_bla &instruction);
    virtual void visit(PPC_bc &instruction);
    virtual void visit(PPC_bca &instruction);
    virtual void visit(PPC_bcl &instruction);
    virtual void visit(PPC_bcla &instruction);
    virtual void visit(PPC_bcctr &instruction);
    virtual void visit(PPC_bcctrl &instruction);
    virtual void visit(PPC_bclr &instruction);
    virtual void visit(PPC_bclrl &instruction);
    virtual void visit(PPC_eciwx &instruction);
    virtual void visit(PPC_ecowx &instruction);
    virtual void visit(PPC_eieio &instruction);
    virtual void visit(PPC_icbi &instruction);
    virtual void visit(PPC_isync &instruction);
    virtual void visit(PPC_mcrf &instruction);
    virtual void visit(PPC_mcrfs &instruction);
    virtual void visit(PPC_mcrxr &instruction);
    virtual void visit(PPC_mfcr &instruction);
    virtual void visit(PPC_mfocrf &instruction);
    virtual void visit(PPC_mffs &instruction);
    virtual void visit(PPC_mffs_ &instruction);
    virtual void visit(PPC_mfmsr &instruction);
    virtual void visit(PPC_mfspr &instruction);
    virtual void visit(PPC_mfsr &instruction);
    virtual void visit(PPC_mfsrin &instruction);
    virtual void visit(PPC_mftb &instruction);
    virtual void visit(PPC_mtcrf &instruction);
    virtual void visit(PPC_mtocrf &instruction);
    virtual void visit(PPC_mtfsb0 &instruction);
    virtual void visit(PPC_mtfsb0_ &instruction);
    virtual void visit(PPC_mtfsb1 &instruction);
    virtual void visit(PPC_mtfsb1_ &instruction);
    virtual void visit(PPC_mtfsf &instruction);
    virtual void visit(PPC_mtfsf_ &instruction);
    virtual void visit(PPC_mtfsfi &instruction);
    virtual void visit(PPC_mtfsfi_ &instruction);
    virtual void visit(PPC_mtmsr &instruction);
    virtual void visit(PPC_mtmsrd &instruction);
    virtual void visit(PPC_mtspr &instruction);
    virtual void visit(PPC_mtsr &instruction);
    virtual void visit(PPC_mtsrin &instruction);
    virtual void visit(PPC_rfi &instruction);
    virtual void visit(PPC_sc &instruction);
    virtual void visit(PPC_slbia &instruction);
    virtual void visit(PPC_slbie &instruction);
    virtual void visit(PPC_slbmfee &instruction);
    virtual void visit(PPC_slbmfev &instruction);
    virtual void visit(PPC_slbmte &instruction);
    virtual void visit(PPC_sync &instruction);
    virtual void visit(PPC_td &instruction);
    virtual void visit(PPC_tdi &instruction);
    virtual void visit(PPC_tlbia &instruction);
    virtual void visit(PPC_tlbie &instruction);
    virtual void visit(PPC_tlbsync &instruction);
    virtual void visit(PPC_tw &instruction);
    virtual void visit(PPC_twi &instruction);

  };

} // namespace simsoc

#endif  //PPCIS_VISITOR_HPP
