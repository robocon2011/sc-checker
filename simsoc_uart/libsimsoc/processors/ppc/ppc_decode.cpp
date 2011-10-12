//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/processors/ppc/ppcis_loadstore.hpp"
#include "libsimsoc/processors/ppc/ppcis_misc.hpp"
#include "libsimsoc/processors/ppc/ppcis_fpu.hpp"
#include "libsimsoc/processors/ppc/ppcis_alu.hpp"

namespace simsoc {

PPC_Instruction *  ppc_invalid(uint32_t instr) {
    return new PPC_Undefined("no defined!");
}

PPC_Instruction *  ppc_break(uint32_t instr) {
	 return new PPC_Break();
}

//main opcode 16
static PPC_Instruction * ppc_group1(uint32_t instr) {
    bool lk =instr&0x1;
    bool aa =(instr>>1)&0x1;

    if(aa){
        if(lk)
            return ppc_bcla(instr);
        else   return ppc_bca(instr);
    }else
    {
        if(lk)
            return ppc_bcl(instr);
        else   return ppc_bc(instr);
    }
}

//main opcode 18
static PPC_Instruction * ppc_group2(uint32_t instr) {
    bool lk =instr&0x1;
    bool aa =(instr>>1)&0x1;
    if(aa){
        if(lk)
            return ppc_bla(instr);
        else   return ppc_ba(instr);
    }else
    {
        if(lk)
            return ppc_bl(instr);
        else   return ppc_b(instr);
    }
}


// main opcode 19
static PPC_Instruction * ppc_group3(uint32_t instr) {
    uint32_t ext = (instr>>1) & 0x3ff; //XL-FORM
    bool lk =instr&0x1;

    switch (ext) {
        case   0 : return ppc_mcrf(instr);
        case  16 : if(lk)
                       return ppc_bclrl(instr);
                   else  return ppc_bclr(instr);
        case  33 : return ppc_crnor(instr);
        case  50 : return ppc_rfi(instr);      //book III
        case 129 : return ppc_crandc(instr);
        case 150 : return ppc_isync(instr);    //book II
        case 193 : return ppc_crxor(instr);
        case 225 : return ppc_crnand(instr);
        case 257 : return ppc_crand(instr);
        case 289 : return ppc_creqv(instr);
        case 417 : return ppc_crorc(instr);
        case 449 : return ppc_cror(instr);
        case 528 : if(lk)
                       return ppc_bcctrl(instr);
                   else  return ppc_bcctr(instr);
    }

    return ppc_invalid(instr);
}

//main opcode 20
static PPC_Instruction * ppc_group4(uint32_t instr) {
    bool rc =instr&0x1;

    if(rc)        return ppc_rlwimi_(instr);
    else   return ppc_rlwimi(instr);
}

//main opcode 21
static PPC_Instruction * ppc_group5(uint32_t instr) {
    bool rc =instr&0x1;

    if(rc)        return ppc_rlwinm_(instr);
    else   return ppc_rlwinm(instr);
}

//main opcode 23
static PPC_Instruction * ppc_group6(uint32_t instr) {
    bool rc =instr&0x1;

    if(rc)        return ppc_rlwnm_(instr);
    else   return ppc_rlwnm(instr);
}

// main opcode 30
static PPC_Instruction * ppc_group7(uint32_t instr){
    uint32_t ext = (instr>>2) & 0x7;	//MD-FORM
    bool rc =instr&0x1;

    switch (ext) {
        case 0 : if(rc)
                     return ppc_rldicl_(instr);
                 else  return ppc_rldicl(instr);
        case 1 : if(rc)
                     return ppc_rldicr_(instr);
                 else  return ppc_rldicr(instr);
        case 2 : if(rc)
                     return ppc_rldic_(instr);
                 else  return ppc_rldic(instr);
        case 3 : if(rc)
                     return ppc_rldimi_(instr);
                 return ppc_rldimi(instr);	}

                 ext = (instr>>1) & 0xf; //MDS-FORM
                 rc =instr&0x1;

                 switch (ext) {
                     case 8 : if(rc)
                                  return ppc_rldcl_(instr);
                              else  return ppc_rldcl(instr);
                     case 9 : if(rc)
                                  return ppc_rldcr_(instr);
                              else  return ppc_rldcr(instr);
                 }
                 return ppc_invalid(instr);
}

// main opcode 31
static PPC_Instruction * ppc_group8(uint32_t instr) {

    uint32_t ext = (instr>>1) & 0x3ff; //X-FORM, XFX-FORM
    bool rc=instr&0x1;

    switch (ext) {
        case    0 : return ppc_cmp(instr);
        case    4 : return ppc_tw(instr);
        case   19 : return ppc_mfcr(instr);	     //case     19 : return ppc_mfocrf(instr);
        case   20 : return ppc_lwarx(instr);	    //book II
        case   21 : return ppc_ldx(instr);
        case   23 : return ppc_lwzx(instr);
        case   24 : if(rc)
                        return ppc_slw_(instr);
                    else  return ppc_slw(instr);
        case   26 : if(rc)
                        return ppc_cntlzw_(instr);
                    else  return ppc_cntlzw(instr);
        case   27 : if(rc)
                        return ppc_sld_(instr);
                    else  return ppc_sld(instr);
        case   28 : if(rc)
                        return ppc_and_(instr);
                    else  return ppc_and(instr);
        case   32 : return ppc_cmpl(instr);
        case   53 : return ppc_ldux(instr);
        case   54 : return ppc_dcbst(instr);     //book II
        case   55 : return ppc_lwzux(instr);
        case   58 : if(rc)
                        return ppc_cntlzd_(instr);
                    else   return ppc_cntlzd(instr);
        case   60 : if(rc)
                        return ppc_andc_(instr);
                    else   return ppc_andc(instr);
        case   68 : return ppc_td(instr);
        case   83 : return ppc_mfmsr(instr);    //book III
        case   84 : return ppc_ldarx(instr);      //book II
        case   86 : return ppc_dcbf(instr);	    //book II
        case   87 : return ppc_lbzx(instr);
        case  119 : return ppc_lbzux(instr);
        case  124 : if(rc)
                        return ppc_nor_(instr);
                    else   return ppc_nor(instr);
        case  144 : return ppc_mtcrf(instr);      //case   144 : return ppc_mtocrf(instr);
        case  146 : return ppc_mtmsr(instr);    //book III
        case  149 : return ppc_stdx(instr);
        case  150 : return ppc_stwcx_(instr);   //book II
        case  151 : return ppc_stwx(instr);
        case  178 : return ppc_mtmsrd(instr);  //book III
        case  181 : return ppc_stdux(instr);
        case  183 : return ppc_stwux(instr);
        case  210 : return ppc_mtsr(instr);	   //book III
        case  214 : return ppc_stdcx_(instr);    //book II
        case  215 : return ppc_stbx(instr);
        case  242 : return ppc_mtsrin(instr);  //book III
        case  246 : return ppc_dcbtst(instr);	  //book II
        case  247 : return ppc_stbux(instr);
        case  278 : return ppc_dcbt(instr);     //book II
        case  279 : return ppc_lhzx(instr);
        case  284 : if(rc)
                        return ppc_eqv_(instr);
                    else   return ppc_eqv(instr);
        case  306 : return ppc_tlbie(instr);     //book III
        case  310 : return ppc_eciwx(instr);	  //book II
        case  311 : return ppc_lhzux(instr);
        case  316 : if(rc)
                        return ppc_xor_(instr);
                    else   return ppc_xor(instr);
        case  339 : return ppc_mfspr(instr);
        case  341 : return ppc_lwax(instr);
        case  343 : return ppc_lhax(instr);
        case  370 : return ppc_tlbia(instr);     //book III
        case  371 : return ppc_mftb(instr);	  //book II
        case  373 : return ppc_lwaux(instr);
        case  375 : return ppc_lhaux(instr);
        case  402 : return ppc_slbmte(instr);  //book III
        case  407 : return ppc_sthx(instr);
        case  412 : if(rc)
                        return ppc_orc_(instr);
                    else   return ppc_orc(instr);
        case  413 : if(rc)
                        return ppc_sradi_(instr);
                    else   return ppc_sradi(instr);
        case  434 : return ppc_slbie(instr);    //book III
        case  438 : return ppc_ecowx(instr);  //book II
        case  439 : return ppc_sthux(instr);
        case  444 : if(rc)
                        return ppc_or_(instr);
                    else   return ppc_or(instr);
        case  467 : return ppc_mtspr(instr);
        case  476 : if(rc)
                        return ppc_nand_(instr);
                    else   return ppc_nand(instr);
        case  498 : return ppc_slbia(instr);    //book III
        case  512 : return ppc_mcrxr(instr);
        case  533 : return ppc_lswx(instr);
        case  534 : return ppc_lwbrx(instr);
        case  535 : return ppc_lfsx(instr);
        case  536 : if(rc)
                        return ppc_srw_(instr);
                    else   return ppc_srw(instr);
        case  539 : if(rc)
                        return ppc_srd_(instr);
                    else   return ppc_srd(instr);
        case  566 : return ppc_tlbsync(instr);  //book III
        case  567 : return ppc_lfsux(instr);
        case  595 : return ppc_mfsr(instr);	  //book III
        case  597 : return ppc_lswi(instr);
        case  598 : return ppc_sync(instr);	  //book II
        case  599 : return ppc_lfdx(instr);
        case  631 : return ppc_lfdux(instr);
        case  659 : return ppc_mfsrin(instr);  //book III
        case  661 : return ppc_stswx(instr);
        case  662 : return ppc_stwbrx(instr);
        case  663 : return ppc_stfsx(instr);
        case  695 : return ppc_stfsux(instr);
        case  725 : return ppc_stswi(instr);
        case  727 : return ppc_stfdx(instr);
        case  759 : return ppc_stfdux(instr);
        case  790 : return ppc_lhbrx(instr);
        case  792 : if(rc)
                        return ppc_sraw_(instr);
                    else   return ppc_sraw(instr);
        case  794 : if(rc)
                        return ppc_srad_(instr);
                    else   return ppc_srad(instr);
        case  822 : return ppc_dss(instr);
        case  824 : if(rc)
                        return ppc_srawi_(instr);
                    else   return ppc_srawi(instr);
        case  851 : return ppc_slbmfev(instr);  //book III
        case  854 : return ppc_eieio(instr);	    //book II
        case  915 : return ppc_slbmfee(instr);  //book III
        case  918 : return ppc_sthbrx(instr);
        case  922 : if(rc)
                        return ppc_extsh_(instr);
                    else   return ppc_extsh(instr);
        case  954 : if(rc)
                        return ppc_extsb_(instr);
                    else   return ppc_extsb(instr);
        case  982 : return ppc_icbi(instr);	  //book II
        case  983 : return ppc_stfiwx(instr);
        case  986 : if(rc)
                        return ppc_extsw_(instr);
                    else   return ppc_extsw(instr);
        case 1014 : return ppc_dcbz(instr);     //book II
    }


    ext = (instr>>1) & 0x1ff; //XO-FORM
    bool oe=(instr>>10)&0x1;
    rc=instr&0x1;

    switch (ext) {
        case     8 : if(oe){
                         if(rc)
                             return ppc_subfco_(instr);
                         else   return ppc_subfco(instr);
                     }else {
                         if(rc)
                             return ppc_subfc_(instr);
                         else   return ppc_subfc(instr);
                     }
        case     9 : if(rc)
                         return ppc_mulhdu_(instr);
                     else   return ppc_mulhdu(instr);
        case    10 : if (oe){
                         if(rc)
                             return ppc_addco_(instr);
                         else   return ppc_addco(instr);
                     }else {
                         if(rc)
                             return ppc_addc_(instr);
                         else   return ppc_addc(instr);
                     }
        case    11 : if(rc)
                         return ppc_mulhwu_(instr);
                     else   return ppc_mulhwu(instr);
        case    40 : if(oe){
                         if(rc)
                             return ppc_subfo_(instr);
                         else   return ppc_subfo(instr);
                     }else {
                         if(rc)
                             return ppc_subf_(instr);
                         return ppc_subf(instr);
                     }
        case    73 : if(rc)
                         return ppc_mulhd_(instr);
                     else   return ppc_mulhd(instr);
        case    75 : if(rc)
                         return ppc_mulhw_(instr);
                     else   return ppc_mulhw(instr);
        case   104 : if(oe){
                         if(rc)
                             return ppc_nego_(instr);
                         else   return ppc_nego(instr);
                     }else {
                         if(rc)
                             return ppc_neg_(instr);
                         else   return ppc_neg(instr);
                     }
        case   136 : if(oe){
                         if(rc)
                             return ppc_subfeo_(instr);
                         else   return ppc_subfeo(instr);
                     }else {
                         if(rc)
                             return ppc_subfe_(instr);
                         else   return ppc_subfe(instr);
                     }
        case   138 : if(oe){
                         if(rc)
                             return ppc_addeo_(instr);
                         else   return ppc_addeo(instr);
                     }else {
                         if(rc)
                             return ppc_adde_(instr);
                         else   return ppc_adde(instr);
                     }
        case   200 : if(oe){
                         if(rc)
                             return ppc_subfzeo_(instr);
                         else   return ppc_subfzeo(instr);
                     }else {
                         if(rc)
                             return ppc_subfze_(instr);
                         else   return ppc_subfze(instr);
                     }
        case   202 : if(oe){
                         if(rc)
                             return ppc_addzeo_(instr);

                         else  return ppc_addzeo(instr);
                     }else {
                         if(rc)
                             return ppc_addze_(instr);
                         else   return ppc_addze(instr);
                     }
        case   232 : if(oe){
                         if(rc)
                             return ppc_subfmeo_(instr);
                         else   return ppc_subfmeo(instr);
                     }else {
                         if(rc)
                             return ppc_subfme_(instr);
                         else   return ppc_subfme(instr);
                     }
        case   233 : if(oe){
                         if(rc)
                             return ppc_mulldo_(instr);
                         else   return ppc_mulldo(instr);
                     }else {
                         if(rc)
                             return ppc_mulld_(instr);
                         else   return ppc_mulld(instr);
                     }

        case   234 : if(oe){
                         if(rc)
                             return ppc_addmeo_(instr);
                         else   return ppc_addmeo(instr);
                     }else {
                         if(rc)
                             return ppc_addme_(instr);
                         else   return ppc_addme(instr);
                     }

        case   235 : if(oe){
                         if(rc)
                             return ppc_mullwo_(instr);
                         else   return ppc_mullwo(instr);
                     }else {
                         if(rc)
                             return ppc_mullw_(instr);
                         else   return ppc_mullw(instr);
                     }

        case   266 : if(oe){
                         if(rc)
                             return ppc_addo_(instr);
                         else   return ppc_addo(instr);
                     }else {
                         if(rc)
                             return ppc_add_(instr);
                         else   return ppc_add(instr);
                     }

        case   457 : if(oe){
                         if(rc)
                             return ppc_divduo_(instr);
                         else   return ppc_divduo(instr);
                     }else {
                         if(rc)
                             return ppc_divdu_(instr);
                         else   return ppc_divdu(instr);
                     }

        case   459 : if(oe){
                         if(rc)
                             return ppc_divwuo_(instr);
                         else   return ppc_divwuo(instr);
                     }else {
                         if(rc)
                             return ppc_divwu_(instr);
                         else   return ppc_divwu(instr);
                     }

        case   489 : if(oe){
                         if(rc)
                             return ppc_divdo_(instr);
                         else   return ppc_divdo(instr);
                     }else {
                         if(rc)
                             return ppc_divd_(instr);
                         else   return ppc_divd(instr);
                     }

        case   491 : if(oe){
                         if(rc)
                             return ppc_divwo_(instr);
                         else   return ppc_divwo(instr);
                     }else {
                         if(rc)
                             return ppc_divw_(instr);
                         else   return ppc_divw(instr);
                     }
    }
    return ppc_invalid(instr);
}

// main opcode 58
static PPC_Instruction * ppc_group9(uint32_t instr){
    uint32_t ext = instr & 0x3; //DS-FORM

    switch (ext) {
        case 0 : return ppc_ld(instr);
        case 1 : return ppc_ldu(instr);
        case 2 : return ppc_lwa(instr);
    }
    return ppc_invalid(instr);
}

// main opcode 59
static PPC_Instruction * ppc_group10(uint32_t instr){
    uint32_t ext = (instr>>1) & 0x1f;  //A-FORM
    uint32_t rc =instr&0x1;
    switch (ext) {
    case 18 : if(rc) return ppc_fdivs_(instr);
      else return ppc_fdivs(instr);
    case 20 : if(rc) return ppc_fsubs_(instr);
      else return ppc_fsubs(instr);
    case 21 : if(rc) return ppc_fadds_(instr);
      else return ppc_fadds(instr);
    case 22 : if(rc) return ppc_fsqrts_(instr);
      else return ppc_fsqrts(instr);
    case 24 : if(rc) return ppc_fres_(instr);
      else return ppc_fres(instr);
    case 25 : if(rc) return ppc_fmuls_(instr);
      else return ppc_fmuls(instr);
    case 28 : if(rc) return ppc_fmsubs_(instr);
      else return ppc_fmsubs(instr);
    case 29 : if(rc) return ppc_fmadds_(instr);
      else return ppc_fmadds(instr);
    case 30 : if(rc) return ppc_fnmsubs_(instr);
      else return ppc_fnmsubs(instr);
    case 31 : if(rc) return ppc_fnmadds_(instr);
      else return ppc_fnmadds(instr);
    }
    return ppc_invalid(instr);
}

// main opcode 62
static PPC_Instruction * ppc_group11(uint32_t instr){
    uint32_t ext = instr & 0x3; //DS-FORM

    switch (ext) {
        case 0 : return ppc_std(instr);
        case 1 : return ppc_stdu(instr);
    }
    return ppc_invalid(instr);
}

// main opcode 63
static PPC_Instruction * ppc_group12(uint32_t instr) {
    uint32_t ext = (instr>>1) & 0x3ff; //X-FORM	, XFL-FORM
    uint32_t rc =instr&0x1;
    switch (ext) {
    case   0 : return ppc_fcmpu(instr);
    case  12 : if(rc) return ppc_frsp_(instr);
      else return ppc_frsp(instr);
    case  14 : if(rc) return ppc_fctiw_(instr);
      else return ppc_fctiw(instr);
    case  15 : if(rc) return ppc_fctiwz_(instr);
      else return ppc_fctiwz(instr);
    case  32 : return ppc_fcmpo(instr);
    case  38 : if(rc) return ppc_mtfsb1_(instr);
      else return ppc_mtfsb1(instr);
    case  40 : if(rc) return ppc_fneg_(instr);
      else return ppc_fneg(instr);
    case  64 : return ppc_mcrfs(instr);
    case  70 : if(rc) return ppc_mtfsb0_(instr);
      else return ppc_mtfsb0(instr);
    case  72 : if(rc) return ppc_fmr_(instr);
      else return ppc_fmr(instr);
    case 134 : if(rc) return ppc_mtfsfi_(instr);
      else return ppc_mtfsfi(instr);
    case 136 : if(rc) return ppc_fnabs_(instr);
      else return ppc_fnabs(instr);
    case 264 : if(rc) return ppc_fabs_(instr);
      else return ppc_fabs(instr);
    case 583 : if(rc) return ppc_mffs_(instr);
      else return ppc_mffs(instr);
    case 711 : if(rc) return ppc_mtfsf_(instr);
      else return ppc_mtfsf(instr);
    case 814 : if(rc) return ppc_fctid_(instr);
      else return ppc_fctid(instr);
    case 815 : if(rc) return ppc_fctidz_(instr);
      else return ppc_fctidz(instr);
    case 846 : if(rc) return ppc_fcfid_(instr);
      else return ppc_fcfid(instr);
    }

    ext = (instr>>1) & 0x1f;  //A-FORM
    switch (ext) {
    case 18 : if(rc) return ppc_fdiv_(instr);
      else return ppc_fdiv(instr);
    case 20 : if(rc) return ppc_fsub_(instr);
      else return ppc_fsub(instr);
    case 21 : if(rc) return ppc_fadd_(instr);
      else return ppc_fadd(instr);
    case 22 : if(rc) return ppc_fsqrt_(instr);
      else return ppc_fsqrt(instr);
    case 23 : if(rc) return ppc_fsel_(instr);
      else return ppc_fsel(instr);
    case 25 : if(rc) return ppc_fmul_(instr);
      else return ppc_fmul(instr);
    case 26 : if(rc) return ppc_frsqrte_(instr);
      else return ppc_frsqrte(instr);
    case 28 : if(rc) return ppc_fmsub_(instr);
      else return ppc_fmsub(instr);
    case 29 : if(rc) return ppc_fmadd_(instr);
      else return ppc_fmadd(instr);
    case 30 : if(rc) return ppc_fnmsub_(instr);
      else return ppc_fnmsub(instr);
    case 31 : if(rc) return ppc_fnmadd_(instr);
      else return ppc_fnmadd(instr);

    }
    return ppc_invalid(instr);
}

//first, i want to use "switch case", but it is too long, so i use function table instead.
static ppc_func ppc_table_main[64] = {

    &ppc_invalid,	//  0
    &ppc_break,     //breakpoint for gdb
    &ppc_tdi,
    &ppc_twi,
    &ppc_invalid,
    &ppc_invalid,	//  5
    &ppc_invalid,
    &ppc_mulli,
    &ppc_subfic,
    &ppc_invalid,
    &ppc_cmpli,		// 10
    &ppc_cmpi,
    &ppc_addic,
    &ppc_addic_,
    &ppc_addi,
    &ppc_addis,		// 15
    &ppc_group1,
    &ppc_sc,
    &ppc_group2,
    &ppc_group3,	//need extend opcode
    &ppc_group4,	// 20
    &ppc_group5,
    &ppc_invalid,
    &ppc_group6,
    &ppc_ori,
    &ppc_oris,		// 25
    &ppc_xori,
    &ppc_xoris,
    &ppc_andi_,
    &ppc_andis_,
    &ppc_group7,	// 30  (group_rld on 64 bit platforms)
    &ppc_group8,
    &ppc_lwz,
    &ppc_lwzu,
    &ppc_lbz,
    &ppc_lbzu,		// 35
    &ppc_stw,
    &ppc_stwu,
    &ppc_stb,
    &ppc_stbu,
    &ppc_lhz,		// 40
    &ppc_lhzu,
    &ppc_lha,
    &ppc_lhau,
    &ppc_sth,
    &ppc_sthu,		// 45
    &ppc_lmw,
    &ppc_stmw,
    &ppc_lfs,
    &ppc_lfsu,
    &ppc_lfd,		// 50
    &ppc_lfdu,
    &ppc_stfs,
    &ppc_stfsu,
    &ppc_stfd,
    &ppc_stfdu,		// 55
    &ppc_invalid,
    &ppc_invalid,
    &ppc_group9,
    &ppc_group10,
    &ppc_invalid,	// 60
    &ppc_invalid,
    &ppc_group11,
    &ppc_group12,
};



PPC_Instruction *  ppcDecode(uint32_t instr) {
    //instr = word_be_le_translate(instr);
    uint32_t mainopc = (instr >> 26) & 0x3f;
    return  ppc_table_main[mainopc](instr);
}

} // namespace simsoc
