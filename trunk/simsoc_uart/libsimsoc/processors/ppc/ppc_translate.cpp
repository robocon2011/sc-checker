#include "ppc_translate.hpp"
#include "ppcis_alu.hpp"
#include "ppcis_misc.hpp"
#include "ppcis_loadstore.hpp"
#include "ppcis_fpu.hpp"
#include "ppc_pi.hpp"
#include <libsimsoc/translation_page.hpp>
#include <libsimsoc/display.hpp>
#include <cassert>

namespace simsoc {

  PPC_Translate::PPC_Translate(PPC_Processor &processor,
                               PPC_Instruction *instr,
                               PPC_PseudoInstruction &pseudo):
    proc(processor), pi(pseudo)
  {
    instr->accept(*this);
  }

  void PPC_Translate::visit(PPC_Instruction &i) {
    error() <<"internal error: visitor not implemented for instruction: "
            <<i<<std::endl;
    exit(1);
    // FIXME: once all instructions are implemented,
    //        replace code above by "UNREACHABLE;".
  }

  void PPC_Translate::visit(PPC_Undefined &instruction) {
    ppcTranslateGeneric(pi,&instruction);
  }

  void PPC_Translate::visit(PPC_Unpredictable &instruction) {
    ppcTranslateGeneric(pi,&instruction);
  }

  void PPC_Translate::visit(PPC_Nop &instruction) {
    pi.f = ppc_pi_nop;
  }

  void PPC_Translate::visit(PPC_Break &i) {
    ppcTranslateGeneric(pi,&i);
  }

  void PPC_Translate::visit(PPC_add &i) {
    pi.f = ppc_add;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_add_ &i) {
    pi.f = ppc_add_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addo &i) {
    pi.f = ppc_addo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addo_ &i) {
    pi.f = ppc_addo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addc &i) {
    pi.f = ppc_addc;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addc_ &i) {
    pi.f = ppc_addc_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addco &i) {
    pi.f = ppc_addco;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addco_ &i) {
    pi.f = ppc_addco_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

void PPC_Translate::visit(PPC_adde &i) {
    pi.f = ppc_adde;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_adde_ &i) {
    pi.f = ppc_adde_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addeo &i) {
    pi.f = ppc_addeo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addeo_ &i) {
    pi.f = ppc_addeo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addi &i) {
    if (i.ra!=0)
      pi.f = ppc_addi_raS;
    else
      pi.f = ppc_addi_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_addic &i) {
    pi.f = ppc_addic;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_addic_ &i) {
    pi.f = ppc_addic_;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_addis &i) {
    if (i.ra!=0)
      pi.f = ppc_addis_raS;
    else
      pi.f = ppc_addis_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_addme &i) {
    pi.f = ppc_addme;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addme_ &i) {
    pi.f = ppc_addme_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addmeo &i) {
    pi.f = ppc_addmeo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addmeo_ &i) {
    pi.f = ppc_addmeo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addze &i) {
    pi.f = ppc_addze;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addze_ &i) {
    pi.f = ppc_addze_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addzeo &i) {
    pi.f = ppc_addzeo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_addzeo_ &i) {
    pi.f = ppc_addzeo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_and &i) {
    pi.f = ppc_and;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_and_ &i) {
    pi.f = ppc_and_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_andc &i) {
    pi.f = ppc_andc;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_andc_ &i) {
    pi.f = ppc_andc_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_andi_ &i) {
    pi.f = ppc_andi_;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

 void PPC_Translate::visit(PPC_andis_ &i) {
    pi.f = ppc_andis_;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_cmp &i) {
    pi.f = ppc_cmp;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_cmpi &i) {
    pi.f = ppc_cmpi;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_cmpl &i) {
    pi.f = ppc_cmpl;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_cmpli &i) {
    pi.f = ppc_cmpli;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_cntlzd &i) {
    pi.f = ppc_cntlzd;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_cntlzd_ &i) {
    pi.f = ppc_cntlzd_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_cntlzw &i) {
    pi.f = ppc_cntlzw;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_cntlzw_ &i) {
    pi.f = ppc_cntlzw_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_crand &i) {
    pi.f = ppc_crand;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

   void PPC_Translate::visit(PPC_crandc &i) {
    pi.f = ppc_crandc;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

   void PPC_Translate::visit(PPC_creqv &i) {
    pi.f = ppc_creqv;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

   void PPC_Translate::visit(PPC_crnand &i) {
    pi.f = ppc_crnand;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

   void PPC_Translate::visit(PPC_crnor &i) {
    pi.f = ppc_crnor;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

   void PPC_Translate::visit(PPC_cror &i) {
    pi.f = ppc_cror;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

   void PPC_Translate::visit(PPC_crorc &i) {
    pi.f = ppc_crorc;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

   void PPC_Translate::visit(PPC_crxor &i) {
    pi.f = ppc_crxor;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

  void PPC_Translate::visit(PPC_divd &i) {
    pi.f = ppc_divd;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divd_ &i) {
    pi.f = ppc_divd_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divdo &i) {
    pi.f = ppc_divdo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divdo_ &i) {
    pi.f = ppc_divdo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divdu &i) {
    pi.f = ppc_divdu;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divdu_ &i) {
    pi.f = ppc_divdu_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divduo &i) {
    pi.f = ppc_divduo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divduo_ &i) {
    pi.f = ppc_divduo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divw &i) {
    pi.f = ppc_divw;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divw_ &i) {
    pi.f = ppc_divw_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divwo &i) {
    pi.f = ppc_divwo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divwo_ &i) {
    pi.f = ppc_divwo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

 void PPC_Translate::visit(PPC_divwu &i) {
    pi.f = ppc_divwu;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divwu_ &i) {
    pi.f = ppc_divwu_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divwuo &i) {
    pi.f = ppc_divwuo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_divwuo_ &i) {
    pi.f = ppc_divwuo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_eqv &i) {
    pi.f = ppc_eqv;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_eqv_ &i) {
    pi.f = ppc_eqv_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_extsb &i) {
    pi.f = ppc_extsb;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_extsb_ &i) {
    pi.f = ppc_extsb_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_extsh &i) {
    pi.f = ppc_extsh;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_extsh_ &i) {
    pi.f = ppc_extsh_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

   void PPC_Translate::visit(PPC_extsw &i) {
    pi.f = ppc_extsw;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

   void PPC_Translate::visit(PPC_extsw_ &i) {
    pi.f = ppc_extsw_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mulhd &i) {
    pi.f = ppc_mulhd;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mulhd_ &i) {
    pi.f = ppc_mulhd_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mulhdu &i) {
    pi.f = ppc_mulhdu;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mulhdu_ &i) {
    pi.f = ppc_mulhdu_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mulhw &i) {
    pi.f = ppc_mulhw;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mulhw_ &i) {
    pi.f = ppc_mulhw_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mulhwu &i) {
    pi.f = ppc_mulhwu;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mulhwu_ &i) {
    pi.f = ppc_mulhwu_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mulld &i) {
    pi.f = ppc_mulld;
    pi.args.XO.rt = i.rt;
    pi.args.XO.ra = i.ra;
    pi.args.XO.rb = i.rb;
  }

  void PPC_Translate::visit(PPC_mulld_ &i) {
    pi.f = ppc_mulld_;
    pi.args.XO.rt = i.rt;
    pi.args.XO.ra = i.ra;
    pi.args.XO.rb = i.rb;
  }

  void PPC_Translate::visit(PPC_mulldo &i) {
    pi.f = ppc_mulldo;
    pi.args.XO.rt = i.rt;
    pi.args.XO.ra = i.ra;
    pi.args.XO.rb = i.rb;
  }

  void PPC_Translate::visit(PPC_mulldo_ &i) {
    pi.f = ppc_mulldo_;
    pi.args.XO.rt = i.rt;
    pi.args.XO.ra = i.ra;
    pi.args.XO.rb = i.rb;
  }

  void PPC_Translate::visit(PPC_mulli &i) {
    pi.f = ppc_mulli;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_mullw &i) {
    pi.f = ppc_mullw;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mullw_ &i) {
    pi.f = ppc_mullw_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }
  void PPC_Translate::visit(PPC_mullwo &i) {
    pi.f = ppc_mullwo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mullwo_ &i) {
    pi.f = ppc_mullwo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_nand &i) {
    pi.f = ppc_nand;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_nand_ &i) {
    pi.f = ppc_nand_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_neg &i) {
    pi.f = ppc_neg;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_neg_ &i) {
    pi.f = ppc_neg_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_nego &i) {
    pi.f = ppc_nego;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_nego_ &i) {
    pi.f = ppc_nego_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_or &i) {
    pi.f = ppc_or;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_nor &i) {
    pi.f = ppc_nor;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_nor_ &i) {
    pi.f = ppc_nor_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_or_ &i) {
    pi.f = ppc_or_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_orc &i) {
    pi.f = ppc_orc;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_orc_ &i) {
    pi.f = ppc_orc_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_ori &i) {
    pi.f = ppc_ori;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

 void PPC_Translate::visit(PPC_oris &i) {
    pi.f = ppc_oris;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

   void PPC_Translate::visit(PPC_rldcl &i) {
    pi.f = ppc_rldcl;
    pi.args.MDS.rs = i.rs;
    pi.args.MDS.ra = i.ra;
    pi.args.MDS.rb = i.rb;
    pi.args.MDS.mb = i.mb;
  }

  void PPC_Translate::visit(PPC_rldcl_ &i) {
    pi.f = ppc_rldcl_;
    pi.args.MDS.rs = i.rs;
    pi.args.MDS.ra = i.ra;
    pi.args.MDS.rb = i.rb;
    pi.args.MDS.mb = i.mb;
  }

  void PPC_Translate::visit(PPC_rldcr &i) {
    pi.f = ppc_rldcr;
    pi.args.MDS.rs = i.rs;
    pi.args.MDS.ra = i.ra;
    pi.args.MDS.rb = i.rb;
    pi.args.MDS.mb = i.mb;
  }

  void PPC_Translate::visit(PPC_rldcr_ &i) {
    pi.f = ppc_rldcr_;
    pi.args.MDS.rs = i.rs;
    pi.args.MDS.ra = i.ra;
    pi.args.MDS.rb = i.rb;
    pi.args.MDS.mb = i.mb;
  }

  void PPC_Translate::visit(PPC_rldic &i) {
    pi.f = ppc_rldic;
    pi.args.MD.rs = i.rs;
    pi.args.MD.ra = i.ra;
    pi.args.MD.sh = i.sh;
    pi.args.MD.mb = i.mb;
  }

 void PPC_Translate::visit(PPC_rldic_ &i) {
    pi.f = ppc_rldic_;
    pi.args.MD.rs = i.rs;
    pi.args.MD.ra = i.ra;
    pi.args.MD.sh = i.sh;
    pi.args.MD.mb = i.mb;
  }

  void PPC_Translate::visit(PPC_rldicl &i) {
    pi.f = ppc_rldicl;
    pi.args.MD.rs = i.rs;
    pi.args.MD.ra = i.ra;
    pi.args.MD.sh = i.sh;
    pi.args.MD.mb = i.mb;
  }

  void PPC_Translate::visit(PPC_rldicl_ &i) {
    pi.f = ppc_rldicl_;
    pi.args.MD.rs = i.rs;
    pi.args.MD.ra = i.ra;
    pi.args.MD.sh = i.sh;
    pi.args.MD.mb = i.mb;
  }

  void PPC_Translate::visit(PPC_rldicr &i) {
    pi.f = ppc_rldicr;
    pi.args.MD.rs = i.rs;
    pi.args.MD.ra = i.ra;
    pi.args.MD.sh = i.sh;
    pi.args.MD.mb = i.mb;
  }

  void PPC_Translate::visit(PPC_rldicr_ &i) {
    pi.f = ppc_rldicr_;
    pi.args.MD.rs = i.rs;
    pi.args.MD.ra = i.ra;
    pi.args.MD.sh = i.sh;
    pi.args.MD.mb = i.mb;
  }

  void PPC_Translate::visit(PPC_rldimi &i) {
    pi.f = ppc_rldimi;
    pi.args.MD.rs = i.rs;
    pi.args.MD.ra = i.ra;
    pi.args.MD.sh = i.sh;
    pi.args.MD.mb = i.mb;
  }

   void PPC_Translate::visit(PPC_rldimi_ &i) {
    pi.f = ppc_rldimi_;
    pi.args.MD.rs = i.rs;
    pi.args.MD.ra = i.ra;
    pi.args.MD.sh = i.sh;
    pi.args.MD.mb = i.mb;
  }

  void PPC_Translate::visit(PPC_rlwimi &i) {
    pi.f = ppc_rlwimi;
    pi.args.M.rs = i.rs;
    pi.args.M.ra = i.ra;
    pi.args.M.rb = i.rb;
    pi.args.M.mb = i.mb;
    pi.args.M.me = i.me;
  }
  void PPC_Translate::visit(PPC_rlwimi_ &i) {
    pi.f = ppc_rlwimi_;
    pi.args.M.rs = i.rs;
    pi.args.M.ra = i.ra;
    pi.args.M.rb = i.rb;
    pi.args.M.mb = i.mb;
    pi.args.M.me = i.me;
  }

  void PPC_Translate::visit(PPC_rlwinm &i) {
    pi.f = ppc_rlwinm;
    pi.args.M.rs = i.rs;
    pi.args.M.ra = i.ra;
    pi.args.M.rb = i.rb;
    pi.args.M.mb = i.mb;
    pi.args.M.me = i.me;
  }

  void PPC_Translate::visit(PPC_rlwinm_ &i) {
    pi.f = ppc_rlwinm_;
    pi.args.M.rs = i.rs;
    pi.args.M.ra = i.ra;
    pi.args.M.rb = i.rb;
    pi.args.M.mb = i.mb;
    pi.args.M.me = i.me;
  }

  void PPC_Translate::visit(PPC_rlwnm &i) {
    pi.f = ppc_rlwnm;
    pi.args.M.rs = i.rs;
    pi.args.M.ra = i.ra;
    pi.args.M.rb = i.rb;
    pi.args.M.mb = i.mb;
    pi.args.M.me = i.me;
  }

  void PPC_Translate::visit(PPC_rlwnm_ &i) {
    pi.f = ppc_rlwnm_;
    pi.args.M.rs = i.rs;
    pi.args.M.ra = i.ra;
    pi.args.M.rb = i.rb;
    pi.args.M.mb = i.mb;
    pi.args.M.me = i.me;
  }

  void PPC_Translate::visit(PPC_sld &i) {
    pi.f = ppc_sld;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_sld_ &i) {
    pi.f = ppc_sld_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_slw &i) {
    pi.f = ppc_slw;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_slw_ &i) {
    pi.f = ppc_slw_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_srad &i) {
    pi.f = ppc_srad;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

   void PPC_Translate::visit(PPC_srad_ &i) {
    pi.f = ppc_srad_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_sradi &i) {
    pi.f = ppc_sradi;
    pi.args.XS.rs = i.rs;
    pi.args.XS.ra = i.ra;
    pi.args.XS.sh = i.sh;
  }

   void PPC_Translate::visit(PPC_sradi_ &i) {
    pi.f = ppc_sradi_;
    pi.args.XS.rs = i.rs;
    pi.args.XS.ra = i.ra;
    pi.args.XS.sh = i.sh;
  }

  void PPC_Translate::visit(PPC_sraw &i) {
    pi.f = ppc_sraw;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

   void PPC_Translate::visit(PPC_sraw_ &i) {
    pi.f = ppc_sraw_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }


  void PPC_Translate::visit(PPC_srawi &i) {
    pi.f = ppc_srawi;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }
  void PPC_Translate::visit(PPC_srawi_ &i) {
    pi.f = ppc_srawi_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_srd &i) {
    pi.f = ppc_srd;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_srd_ &i) {
    pi.f = ppc_srd_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_srw &i) {
    pi.f = ppc_srw;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_srw_ &i) {
    pi.f = ppc_srw_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subf &i) {
    pi.f = ppc_subf;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subf_ &i) {
    pi.f = ppc_subf_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

 void PPC_Translate::visit(PPC_subfo &i) {
    pi.f = ppc_subfo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

 void PPC_Translate::visit(PPC_subfo_ &i) {
    pi.f = ppc_subfo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfc &i) {
    pi.f = ppc_subfc;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfc_ &i) {
    pi.f = ppc_subfc_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfco &i) {
    pi.f = ppc_subfco;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfco_ &i) {
    pi.f = ppc_subfco_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

 void PPC_Translate::visit(PPC_subfe &i) {
    pi.f = ppc_subfe;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfe_ &i) {
    pi.f = ppc_subfe_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfeo &i) {
    pi.f = ppc_subfeo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfeo_ &i) {
    pi.f = ppc_subfeo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfic &i) {
    pi.f = ppc_subfic;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_subfme &i) {
    pi.f = ppc_subfme;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfme_ &i) {
    pi.f = ppc_subfme_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfmeo &i) {
    pi.f = ppc_subfmeo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfmeo_ &i) {
    pi.f = ppc_subfmeo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

void PPC_Translate::visit(PPC_subfze &i) {
    pi.f = ppc_subfze;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfze_ &i) {
    pi.f = ppc_subfze_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfzeo &i) {
    pi.f = ppc_subfzeo;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_subfzeo_ &i) {
    pi.f = ppc_subfzeo_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_xor &i) {
    pi.f = ppc_xor;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_xor_ &i) {
    pi.f = ppc_xor_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_xori &i) {
    pi.f = ppc_xori;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_xoris &i) {
    pi.f = ppc_xoris;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  //ppcis_fpu.hpp
  void PPC_Translate::visit(PPC_FP_Instruction &i) {
    // We do not implement mode DT2 for PowerPC floating point instructions.
    ppcTranslateGeneric(pi,&i);
  }

  //ppcis_loadstore.hpp

  void PPC_Translate::visit(PPC_dcbf &i) {
    pi.f = ppc_dcbf;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_dcbst &i) {
    pi.f = ppc_dcbst;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_dcbt &i) {
    pi.f = ppc_dcbt;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_dcbtst &i) {
    pi.f = ppc_dcbtst;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_dcbz &i) {
    if(i.ra != 0)
      pi.f = ppc_dcbz_raS;
    else
      pi.f = ppc_dcbz_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lbz &i) {
    if (i.ra != 0)
      pi.f = ppc_lbz_raS;
    else
      pi.f = ppc_lbz_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lbzu &i) {
    pi.f = ppc_lbzu;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lbzux &i) {
    pi.f = ppc_lbzux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lbzx &i) {
    if (i.ra != 0 )
      pi.f=ppc_lbzx_raS;
    else
    pi.f = ppc_lbzx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_ld &i) {
    pi.f = ppc_ld;
    pi.args.DS.rt = i.rt;
    pi.args.DS.ra = i.ra;
    pi.args.DS.ds = i.ds;
  }

  void PPC_Translate::visit(PPC_ldarx &i) {
    pi.f = ppc_ldarx;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_ldu &i) {
    pi.f = ppc_ldu;
    pi.args.DS.rt = i.rt;
    pi.args.DS.ra = i.ra;
    pi.args.DS.ds = i.ds;
  }

  void PPC_Translate::visit(PPC_ldux &i) {
    pi.f = ppc_ldux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_ldx &i) {
    pi.f = ppc_ldx;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lfd &i) {
    if(i.ra != 0)
      pi.f = ppc_lfd_raS;
    else
      pi.f = ppc_lfd_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lfdu &i) {
    pi.f = ppc_lfdu;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lfdux &i) {
    pi.f = ppc_lfdux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lfdx &i) {
    if(i.ra != 0)
      pi.f = ppc_lfdx_raS;
    else
      pi.f = ppc_lfdx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lfs &i) {
    if(i.ra != 0)
      pi.f = ppc_lfs_raS;
    else
      pi.f = ppc_lfs_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lfsu &i) {
    pi.f = ppc_lfsu;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lfsux &i) {
    pi.f = ppc_lfsux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lfsx &i) {
    if(i.ra != 0)
      pi.f = ppc_lfsx_raS;
    else
      pi.f = ppc_lfsx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lha &i) {
    if (i.ra != 0)
      pi.f = ppc_lha_raS;
    else
      pi.f = ppc_lha_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lhau &i) {
    pi.f = ppc_lhau;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lhaux &i) {
    pi.f = ppc_lhaux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lhax &i) {
    if (i.ra != 0 )
      pi.f = ppc_lhax_raS;
    else
      pi.f = ppc_lhax_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lhbrx &i) {
    if (i.ra != 0 )
      pi.f = ppc_lhbrx_raS;
    else
      pi.f = ppc_lhbrx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lhz &i) {
    if (i.ra != 0)
      pi.f = ppc_lhz_raS;
    else
      pi.f = ppc_lhz_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lhzu &i) {
    pi.f = ppc_lhzu;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lhzux &i) {
    pi.f = ppc_lhzux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lhzx &i) {
    if (i.ra != 0 )
      pi.f = ppc_lhzx_raS;
    else
      pi.f = ppc_lhzx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lmw &i) {
    pi.f = ppc_lmw;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lswi &i) {
    if (i.ra != 0 )
      pi.f = ppc_lswi_raS;
    else
      pi.f = ppc_lswi_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lswx &i) {
    if (i.ra != 0 )
      pi.f = ppc_lswx_raS;
    else
      pi.f = ppc_lswx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lwa &i) {
    if (i.ra != 0 )
      pi.f = ppc_lwa_raS;
    else
      pi.f = ppc_lwa_ra0;
    pi.args.DS.rt = i.rt;
    pi.args.DS.ra = i.ra;
    pi.args.DS.ds = i.ds;
  }

  void PPC_Translate::visit(PPC_lwarx &i) {
    if (i.ra != 0 )
      pi.f = ppc_lwarx_raS;
    else
      pi.f = ppc_lwarx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lwaux &i) {
    pi.f = ppc_lwaux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lwax &i) {
    if (i.ra != 0 )
      pi.f = ppc_lwax_raS;
    else
      pi.f = ppc_lwax_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lwbrx &i) {
    if (i.ra != 0 )
      pi.f = ppc_lwbrx_raS;
    else
      pi.f = ppc_lwbrx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lwz &i) {
    if (i.ra != 0)
      pi.f = ppc_lwz_raS;
    else
      pi.f = ppc_lwz_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lwzu &i) {
    pi.f = ppc_lwzu;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_lwzux &i) {
    pi.f = ppc_lwzux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_lwzx &i) {
    if (i.ra != 0 )
      pi.f = ppc_lwzx_raS;
    else
      pi.f = ppc_lwzx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stb &i) {
    if (i.ra != 0)
      pi.f = ppc_stb_raS;
    else
      pi.f = ppc_stb_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_stbu &i) {
    pi.f = ppc_stbu;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_stbux &i) {
    pi.f = ppc_stbux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stbx &i) {
    if (i.ra != 0 )
      pi.f = ppc_stbx_raS;
    else
      pi.f = ppc_stbx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_std &i) {
    pi.f = ppc_std;
    pi.args.DS.rt = i.rt;
    pi.args.DS.ra = i.ra;
    pi.args.DS.ds = i.ds;
  }

  void PPC_Translate::visit(PPC_stdcx_ &i) {
    pi.f = ppc_stdcx_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stdu &i) {
    pi.f = ppc_stdu;
    pi.args.DS.rt = i.rt;
    pi.args.DS.ra = i.ra;
    pi.args.DS.ds = i.ds;
  }

  void PPC_Translate::visit(PPC_stdux &i) {
    pi.f = ppc_stdux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stdx &i) {
    pi.f = ppc_stdx;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stfd &i) {
    if (i.ra != 0)
      pi.f = ppc_stfd_raS;
    else
      pi.f = ppc_stfd_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_stfdu &i) {
    pi.f = ppc_stfdu;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_stfdux &i) {
    pi.f = ppc_stfdux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stfdx &i) {
    if(i.ra != 0)
      pi.f = ppc_stfdx_raS;
    else
      pi.f = ppc_stfdx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stfiwx &i) {
    if(i.ra != 0)
      pi.f = ppc_stfiwx_raS;
    else
      pi.f = ppc_stfiwx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stfs &i) {
    if (i.ra != 0)
      pi.f = ppc_stfs_raS;
    else
      pi.f = ppc_stfs_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_stfsu &i) {
    pi.f = ppc_stfsu;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_stfsux &i) {
    pi.f = ppc_stfsux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stfsx &i) {
    if(i.ra != 0)
      pi.f = ppc_stfsx_raS;
    else
      pi.f = ppc_stfsx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_sth &i) {
    if (i.ra != 0)
      pi.f = ppc_sth_raS;
    else
      pi.f = ppc_sth_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_sthbrx &i) {
    if (i.ra != 0 )
      pi.f = ppc_sthbrx_raS;
    else
      pi.f = ppc_sthbrx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_sthu &i) {
    pi.f = ppc_sthu;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_sthux &i) {
    pi.f = ppc_sthux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_sthx &i) {
    if (i.ra != 0 )
      pi.f = ppc_sthx_raS;
    else
      pi.f = ppc_sthx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stswi &i) {
    if (i.ra != 0 )
      pi.f = ppc_stswi_raS;
    else
      pi.f = ppc_stswi_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stswx &i) {
    if (i.ra != 0 )
      pi.f = ppc_stswx_raS;
    else
      pi.f = ppc_stswx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stmw &i) {
    if (i.ra != 0)
      pi.f = ppc_stmw_raS;
    else
      pi.f = ppc_stmw_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_stw &i) {
    if (i.ra != 0)
      pi.f = ppc_stw_raS;
    else
      pi.f = ppc_stw_ra0;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

   void PPC_Translate::visit(PPC_stwbrx &i) {
    if (i.ra != 0 )
      pi.f = ppc_stwbrx_raS;
    else
      pi.f = ppc_stwbrx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stwcx_ &i) {
    if (i.ra != 0 )
      pi.f = ppc_stwcx__raS;
    else
      pi.f = ppc_stwcx__ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stwu &i) {
    pi.f = ppc_stwu;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_stwux &i) {
    pi.f = ppc_stwux;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_stwx &i) {
    if (i.ra != 0 )
      pi.f = ppc_stwx_raS;
    else
      pi.f = ppc_stwx_ra0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_dss &i) {
    pi.f = ppc_dss;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  //ppcis_misc.hpp

  void PPC_Translate::visit(PPC_b &i) {
    pi.f = ppc_b;
    pi.args.I.li = i.li;
  }

  void PPC_Translate::visit(PPC_ba &i) {
    pi.f = ppc_ba;
    pi.args.I.li = i.li;
  }

  void PPC_Translate::visit(PPC_bl &i) {
    pi.f = ppc_bl;
    pi.args.I.li = i.li;
  }

  void PPC_Translate::visit(PPC_bla &i) {
    pi.f = ppc_bla;
    pi.args.I.li = i.li;
  }

  void PPC_Translate::visit(PPC_bc &i) {
    bool bo_0 = i.bo & 16;
    bool bo_2 = i.bo & 4;
    if ((bo_0 == 1) && (bo_2 == 1))
      pi.f = ppc_bc_bo01_bo21;
    else if ((bo_0 == 0) && (bo_2 == 1))
      pi.f = ppc_bc_bo00_bo21;
    else if ((bo_0 == 1) && (bo_2 == 0))
      pi.f = ppc_bc_bo01_bo20;
    else
      pi.f = ppc_bc_bo00_bo20;
    pi.args.B.bo = i.bo;
    pi.args.B.bi = i.bi;
    pi.args.B.bd = i.bd;
  }

  void PPC_Translate::visit(PPC_bca &i) {
   bool bo_0 = i.bo & 16;
   bool bo_2 = i.bo & 4;
   if ((bo_0 == 1) && (bo_2 == 1))
     pi.f = ppc_bca_bo01_bo21;
   else if ((bo_0 == 0) && (bo_2 == 1))
     pi.f = ppc_bca_bo00_bo21;
   else if ((bo_0 == 1) && (bo_2 == 0))
     pi.f = ppc_bca_bo01_bo20;
   else
     pi.f = ppc_bca_bo00_bo20;
   pi.args.B.bo = i.bo;
   pi.args.B.bi = i.bi;
   pi.args.B.bd = i.bd;
 }

  void PPC_Translate::visit(PPC_bcl &i) {
    bool bo_0 = i.bo & 16;
    bool bo_2 = i.bo & 4;
    if ((bo_0 == 1) && (bo_2 == 1))
      pi.f = ppc_bcl_bo01_bo21;
    else if ((bo_0 == 0) && (bo_2 == 1))
      pi.f = ppc_bcl_bo00_bo21;
    else if ((bo_0 == 1) && (bo_2 == 0))
      pi.f = ppc_bcl_bo01_bo20;
    else
      pi.f = ppc_bcl_bo00_bo20;
    pi.args.B.bo = i.bo;
    pi.args.B.bi = i.bi;
    pi.args.B.bd = i.bd;
  }

  void PPC_Translate::visit(PPC_bcla &i) {
    bool bo_0 = i.bo & 16;
    bool bo_2 = i.bo & 4;
    if ((bo_0 == 1) && (bo_2 == 1))
      pi.f = ppc_bcla_bo01_bo21;
    else if ((bo_0 == 0) && (bo_2 == 1))
      pi.f = ppc_bcla_bo00_bo21;
    else if ((bo_0 == 1) && (bo_2 == 0))
      pi.f = ppc_bcla_bo01_bo20;
    else
      pi.f = ppc_bcla_bo00_bo20;
    pi.args.B.bo = i.bo;
    pi.args.B.bi = i.bi;
    pi.args.B.bd = i.bd;
  }

  void PPC_Translate::visit(PPC_bcctr &i) {
    bool bo_0 = i.bt & 16;
    if (bo_0 == 1)
      pi.f = ppc_bcctr_bo01;
    else
      pi.f = ppc_bcctr_bo00;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

  void PPC_Translate::visit(PPC_bcctrl &i) {
    bool bo_0 = i.bt & 16;
    if (bo_0 == 1)
      pi.f = ppc_bcctrl_bo01;
    else
      pi.f = ppc_bcctrl_bo00;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

  void PPC_Translate::visit(PPC_bclr &i) {
    bool bo_0 = i.bt & 16;
    bool bo_2 = i.bt & 4;
    if ((bo_0 == 1) && (bo_2 == 1))
      pi.f = ppc_bclr_bo01_bo21;
    else if ((bo_0 == 0) && (bo_2 == 1))
      pi.f = ppc_bclr_bo00_bo21;
    else if ((bo_0 == 1) && (bo_2 == 0))
      pi.f = ppc_bclr_bo01_bo20;
    else
      pi.f = ppc_bclr_bo00_bo20;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

  void PPC_Translate::visit(PPC_bclrl &i) {
    bool bo_0 = i.bt & 16;
    bool bo_2 = i.bt & 4;
    if ((bo_0 == 1) && (bo_2 == 1))
      pi.f = ppc_bclrl_bo01_bo21;
    else if ((bo_0 == 0) && (bo_2 == 1))
      pi.f = ppc_bclrl_bo00_bo21;
    else if ((bo_0 == 1) && (bo_2 == 0))
      pi.f = ppc_bclrl_bo01_bo20;
    else
      pi.f = ppc_bclrl_bo00_bo20;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

  void PPC_Translate::visit(PPC_eciwx &i) {
    pi.f = ppc_eciwx;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_ecowx &i) {
    pi.f = ppc_ecowx;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_eieio &i) {
    pi.f = ppc_eieio;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_icbi &i) {
    pi.f = ppc_icbi;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_isync &i) {
    pi.f = ppc_isync;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
    pi.args.XL.bb = i.bb;
  }

  void PPC_Translate::visit(PPC_mcrf &i) {
    pi.f = ppc_mcrf;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
  }

  void PPC_Translate::visit(PPC_mcrfs &i) {
    pi.f = ppc_mcrfs;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mcrxr &i) {
    pi.f = ppc_mcrxr;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mfcr &i) {
    pi.f = ppc_mfcr;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mfocrf &i) {
    pi.f = ppc_mfocrf;
    pi.args.XFX.rt = i.rt;
    pi.args.XFX.spr = i.spr;
  }

  void PPC_Translate::visit(PPC_mffs &i) {
    pi.f = ppc_mffs;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mffs_ &i) {
    pi.f = ppc_mffs_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mfmsr &i) {
    pi.f = ppc_mfmsr;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mfspr &i) {
    pi.f = ppc_mfspr;
    pi.args.XFX.rt = i.rt;
    pi.args.XFX.spr = i.spr;
  }

  void PPC_Translate::visit(PPC_mfsr &i) {
    pi.f = ppc_mfsr;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mfsrin &i) {
    pi.f = ppc_mfsrin;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mftb &i) {
    pi.f = ppc_mftb;
    pi.args.XFX.rt = i.rt;
    pi.args.XFX.spr = i.spr;
  }

  void PPC_Translate::visit(PPC_mtcrf &i) {
    pi.f = ppc_mtcrf;
    pi.args.XFX.rt = i.rt;
    pi.args.XFX.spr = i.spr;
  }

  void PPC_Translate::visit(PPC_mtocrf &i) {
    pi.f = ppc_mtocrf;
    pi.args.XFX.rt = i.rt;
    pi.args.XFX.spr = i.spr;
  }

  void PPC_Translate::visit(PPC_mtfsb0 &i) {
    pi.f = ppc_mtfsb0;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mtfsb0_ &i) {
    pi.f = ppc_mtfsb0_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mtfsb1 &i) {
    pi.f = ppc_mtfsb1;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mtfsb1_ &i) {
    pi.f = ppc_mtfsb1_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mtfsf &i) {
    pi.f = ppc_mtfsf;
    pi.args.XFL.flm = i.flm;
    pi.args.XFL.frb = i.frb;
  }

   void PPC_Translate::visit(PPC_mtfsf_ &i) {
    pi.f = ppc_mtfsf_;
    pi.args.XFL.flm = i.flm;
    pi.args.XFL.frb = i.frb;
  }

  void PPC_Translate::visit(PPC_mtfsfi &i) {
    pi.f = ppc_mtfsfi;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mtfsfi_ &i) {
    pi.f = ppc_mtfsfi_;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mtmsr &i) {
    pi.f = ppc_mtmsr;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mtmsrd &i) {
    pi.f = ppc_mtmsrd;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_mtspr &i) {
    pi.f = ppc_mtspr;
    pi.args.XFX.rt = i.rt;
    pi.args.XFX.spr = i.spr;
  }

  void PPC_Translate::visit(PPC_mtsr &i) {
    pi.f = ppc_mtsr;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

   void PPC_Translate::visit(PPC_mtsrin &i) {
    pi.f = ppc_mtsrin;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_rfi &i) {
    pi.f = ppc_rfi;
    pi.args.XL.bt = i.bt;
    pi.args.XL.ba = i.ba;
  }

  void PPC_Translate::visit(PPC_sc &i) {
    pi.f = ppc_sc;
    pi.args.SC.lev = i.lev;
  }

  void PPC_Translate::visit(PPC_slbia &i) {
    pi.f = ppc_slbia;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_slbie &i) {
    pi.f = ppc_slbie;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_slbmfee &i) {
    pi.f = ppc_slbmfee;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_slbmfev &i) {
    pi.f = ppc_slbmfev;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_slbmte &i) {
    pi.f = ppc_slbmte;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_sync &i) {
    pi.f = ppc_sync;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_td &i) {
    pi.f = ppc_td;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_tdi &i) {
    pi.f = ppc_tdi;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

  void PPC_Translate::visit(PPC_tlbia &i) {
    pi.f = ppc_tlbia;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_tlbie &i) {
    pi.f = ppc_tlbie;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_tlbsync &i) {
    pi.f = ppc_tlbsync;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_tw &i) {
    pi.f = ppc_tw;
    pi.args.X.ra = i.ra;
    pi.args.X.rb = i.rb;
    pi.args.X.rt = i.rt;
  }

  void PPC_Translate::visit(PPC_twi &i) {
    pi.f = ppc_twi;
    pi.args.D.rt = i.rt;
    pi.args.D.ra = i.ra;
    pi.args.D.d = i.d;
  }

} // namespace simsoc
