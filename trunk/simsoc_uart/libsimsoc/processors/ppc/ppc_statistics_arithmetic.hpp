//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_STATISTICS_ARITHMETIC_HPP
#define PPC_STATISTICS_ARITHMETIC_HPP

#include "ppc_statistics.hpp"
#include <cstdlib>

namespace simsoc {

  struct PPC_StatisticsArithmetic: PPC_Statistics {

    PPC_StatisticsArithmetic();

    void write(const char *filename);

    // default visit function
    void visit(PPC_Instruction &instruction);

    //ppcis_alu.hpp
    void visit(PPC_add &instruction);
    void visit(PPC_add_ &instruction);
    void visit(PPC_addo &instruction);
    void visit(PPC_addo_ &instruction);

    size_t arithmetic_add;
    size_t arithmetic_add_;
    size_t arithmetic_addo;
    size_t arithmetic_addo_;

  };

} // namespace simsoc

#endif // PPC_STATISTICS_ARITHMETIC_HPP
