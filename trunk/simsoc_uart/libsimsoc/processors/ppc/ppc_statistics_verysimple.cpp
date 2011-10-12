//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "ppc_statistics_verysimple.hpp"
#include "ppcis.hpp"
#include <libsimsoc/display.hpp>
#include <iostream>
#include <fstream>

using namespace std;

namespace simsoc {

  PPC_StatisticsVerySimple::PPC_StatisticsVerySimple():
    farithmetic(0), other(0)
  {}

  void PPC_StatisticsVerySimple::write(const char *filename) {
    ofstream os(filename);
    if (!os) {
      error() <<"Failed to open \"" <<filename <<"\" for writing.\n";
      exit(1);
    }
    os <<dec <<farithmetic <<" floating-point instructions over "
       <<farithmetic+other <<".\n";
    os.close();
  }

  void PPC_StatisticsVerySimple::visit(PPC_FP_Instruction &instruction){
    ++farithmetic;
  }

  void PPC_StatisticsVerySimple::visit(PPC_Instruction &instruction) {
    ++other;
  }

} // namespace simsoc
