//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "ppc_statistics_simple.hpp"
#include "ppcis.hpp"
#include <libsimsoc/display.hpp>
#include <iostream>
#include <fstream>

using namespace std;

namespace simsoc {

  PPC_StatisticsSimple::PPC_StatisticsSimple():
    arithmetic(0), farithmetic(0), load_store(0), branch(0), other(0)
  {}

  void PPC_StatisticsSimple::write(const char *filename) {
    ofstream os(filename);
    if (!os) {
      error() <<"Failed to open \"" <<filename <<"\" for writing.\n";
      exit(1);
    }
    os <<"arithmetic: " <<dec <<arithmetic <<'\n';
    os <<"farithmetic: " <<dec <<farithmetic <<'\n';
    os <<"load/store: " <<dec <<load_store <<'\n';
    os <<"branch: " <<dec <<branch <<'\n';
    os <<"other:" <<dec <<other <<'\n';
    os <<"total: " <<dec <<arithmetic+farithmetic+load_store+branch+other <<'\n';
    os.close();
  }

  //ppcis_alu.hpp
  void PPC_StatisticsSimple::visit(PPC_add &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_add_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addc &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addc_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addco &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addco_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_adde &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_adde_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addeo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addeo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addi &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addic &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addic_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addis &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addme &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addme_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addmeo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addmeo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addze &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addze_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addzeo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_addzeo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_and &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_and_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_andc &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_andc_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_andi_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_andis_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_cmp &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_cmpi &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_cmpl &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_cmpli &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_cntlzd &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_cntlzd_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_cntlzw &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_cntlzw_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_crand &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_crandc &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_creqv &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_crnand &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_crnor &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_cror &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_crorc &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_crxor &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divd &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divd_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divdo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divdo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divdu &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divdu_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divduo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divduo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divw &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divw_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divwo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divwo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divwu &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divwu_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divwuo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_divwuo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_eqv &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_eqv_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_extsb &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_extsb_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_extsh &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_extsh_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_extsw &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_extsw_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulhd &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulhd_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulhdu &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulhdu_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulhw &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulhw_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulhwu &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulhwu_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulld &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulld_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulldo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulldo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mulli &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mullw &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mullw_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mullwo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_mullwo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_nand &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_nand_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_neg &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_neg_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_nego &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_nego_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_nor &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_nor_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_or &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_or_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_orc &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_orc_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_ori &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_oris &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldcl &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldcl_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldcr &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldcr_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldic &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldic_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldicl &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldicl_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldicr &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldicr_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldimi &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rldimi_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rlwimi &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rlwimi_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rlwinm &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rlwinm_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rlwnm &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_rlwnm_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_sld &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_sld_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_slw &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_slw_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_srad &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_srad_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_sradi &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_sradi_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_sraw &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_sraw_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_srawi &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_srawi_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_srd &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_srd_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_srw &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_srw_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subf &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subf_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfc &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfc_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfco &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfco_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfe &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfe_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfeo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfeo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfic &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfme &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfme_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfmeo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfmeo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfze &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfze_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfzeo &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_subfzeo_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_xor &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_xor_ &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_xori &instruction){
    ++arithmetic;
  }

  void PPC_StatisticsSimple::visit(PPC_xoris &instruction){
    ++arithmetic;
  }

  //ppcis_fpu.hpp
  void PPC_StatisticsSimple::visit(PPC_FP_Instruction &instruction){
    ++farithmetic;
  }
 // void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fadd> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fadd_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fadds> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fadds_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fdiv> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fdiv_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fdivs> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fdivs_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fmul> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fmul_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fmuls> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fmuls_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fsub> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fsub_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fsubs> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPArithmetic<PPC_fsubs_> &instruction){
//     ++farithmetic;
//     ++total;
//   }
//   //void PPC_StatisticsSimple::visit(PPC_FPArithmetic_1op<PPC_fsqrt> &instruction){
//   //  ++farithmetic;
//   //}

//  // void PPC_StatisticsSimple::visit(PPC_FPArithmetic_1op<PPC_fsqrt_> &instruction){
//  //   ++farithmetic;
//  // }

//  // void PPC_StatisticsSimple::visit(PPC_FPArithmetic_1op<PPC_fsqrts> &instruction){
//   //  ++farithmetic;
//  // }

//  // void PPC_StatisticsSimple::visit(PPC_FPArithmetic_1op<PPC_fsqrts_> &instruction){
//  //   ++farithmetic;
//  // }

//   void PPC_StatisticsSimple::visit(PPC_FPConvert<PPC_fctid> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPConvert<PPC_fctid_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPConvert<PPC_fctidz> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPConvert<PPC_fctidz_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPConvert<PPC_fctiw> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPConvert<PPC_fctiw_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPConvert<PPC_fctiwz> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPConvert<PPC_fctiwz_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPCompare<PPC_fcmpo> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPCompare<PPC_fcmpu> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fmadd> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fmadd_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fmadds> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fmadds_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fmsub> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fmsub_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fmsubs> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fmsubs_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fnmadd> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fnmadd_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fnmadds> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fnmadds_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fnmsub> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fnmsub_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fnmsubs> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_FPMultiAdd<PPC_fnmsubs_> &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fabs &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fabs_ &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fcfid &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fcfid_ &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fmadds &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fmr &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fmr_ &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fnabs &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fnabs_ &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fneg &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fneg_ &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fres &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fres_ &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_frsp &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_frsp_ &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_frsqrte &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_frsqrte_ &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fsel &instruction){
//     ++farithmetic;
//     ++total;
//   }

//   void PPC_StatisticsSimple::visit(PPC_fsel_ &instruction){
//     ++farithmetic;
//     ++total;
//   }

  //ppcis_loadstore.hpp
  void PPC_StatisticsSimple::visit(PPC_dcbf &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_dcbst &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_dcbt &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_dcbtst &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_dcbz &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lbz &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lbzu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lbzux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lbzx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_ld &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_ldarx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_ldu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_ldux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_ldx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lfd &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lfdu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lfdux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lfdx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lfs &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lfsu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lfsux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lfsx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lha &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lhau &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lhaux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lhax &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lhbrx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lhz &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lhzu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lhzux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lhzx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lmw &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lswi &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lswx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lwa &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lwarx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lwaux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lwax &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lwbrx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lwz &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lwzu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lwzux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_lwzx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stb &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stbu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stbux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stbx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_std &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stdcx_ &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stdu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stdux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stdx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stfd &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stfdu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stfdux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stfdx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stfiwx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stfs &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stfsu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stfsux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stfsx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_sth &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_sthbrx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_sthu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_sthux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_sthx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stmw &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stswi &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stswx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stw &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stwbrx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stwcx_ &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stwu &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stwux &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_stwx &instruction) {
    ++load_store;
  }

  void PPC_StatisticsSimple::visit(PPC_dss &instruction) {
    ++load_store;
  }

  //ppcis_misc.hpp
  void PPC_StatisticsSimple::visit(PPC_b &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_ba &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_bl &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_bla &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_bc &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_bca &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_bcl &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_bcla &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_bcctr &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_bcctrl &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_bclr &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_bclrl &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_eciwx &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_ecowx &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_eieio &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_icbi &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_isync &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mcrf &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mcrfs &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mcrxr &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mfcr &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mfocrf &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mffs &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mffs_ &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mfmsr &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mfspr &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mfsr &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mfsrin &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mftb &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtcrf &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtocrf &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtfsb0 &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtfsb0_ &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtfsb1 &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtfsb1_ &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtfsf &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtfsf_ &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtfsfi &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtfsfi_ &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtmsr &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtmsrd &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtspr &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtsr &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_mtsrin &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_rfi &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_sc &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_slbia &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_slbie &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_slbmfee &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_slbmfev &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_slbmte &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_sync &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_td &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_tdi &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_tlbia &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_tlbie &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_tlbsync &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_tw &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_twi &instruction) {
    ++branch;
  }

  void PPC_StatisticsSimple::visit(PPC_Instruction &instruction) {
    ++other;
  }

} // namespace simsoc
