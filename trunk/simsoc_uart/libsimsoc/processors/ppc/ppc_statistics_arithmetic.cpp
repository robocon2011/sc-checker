//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "ppc_statistics_arithmetic.hpp"
#include "ppcis.hpp"
#include <libsimsoc/display.hpp>
#include <iostream>
#include <fstream>

using namespace std;

namespace simsoc {

  PPC_StatisticsArithmetic::PPC_StatisticsArithmetic():
    arithmetic_add(0), arithmetic_add_(0), arithmetic_addo(0), arithmetic_addo_(0)
  {}

  void PPC_StatisticsArithmetic::write(const char *filename) {
    ofstream os(filename);
    if (!os) {
      error() <<"Failed to open \"" <<filename <<"\" for writing.\n";
      exit(1);
    }
    os <<"arithmetic_add: " <<dec <<arithmetic_add <<'\n';
    os <<"arithmetic_add_: " <<dec <<arithmetic_add_ <<'\n';
    os <<"arithmetic_addo: " <<dec <<arithmetic_addo <<'\n';
    os <<"arithmetic_addo_: " <<dec <<arithmetic_addo_<<'\n';
    os <<"total: " <<dec <<arithmetic_add + arithmetic_add_ + arithmetic_addo + arithmetic_addo_ <<'\n';
    os.close();//close the file
  }

  void PPC_StatisticsArithmetic::visit(PPC_Instruction &instruction) {}

  //ppcis_alu.hpp
  void PPC_StatisticsArithmetic::visit(PPC_add &instruction){
    ++arithmetic_add;
  }

  void PPC_StatisticsArithmetic::visit(PPC_add_ &instruction){
    ++arithmetic_add_;
  }

  void PPC_StatisticsArithmetic::visit(PPC_addo &instruction){
    ++arithmetic_addo;
  }

  void PPC_StatisticsArithmetic::visit(PPC_addo_ &instruction){
    ++arithmetic_addo_;
  }
} // namespace simsoc
