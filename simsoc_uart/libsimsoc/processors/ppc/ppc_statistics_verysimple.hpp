//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_STATISTICS_VERYSIMPLE_HPP
#define PPC_STATISTICS_VERYSIMPLE_HPP

#include "ppc_statistics.hpp"
#include <cstdlib>

namespace simsoc {

  struct PPC_StatisticsVerySimple: PPC_Statistics {

    PPC_StatisticsVerySimple();

    void write(const char *filename);

    // default visit function
    void visit(PPC_Instruction &instruction);

    //ppcis_fpu.hpp
    void visit(PPC_FP_Instruction &instruction);

    size_t farithmetic;
    size_t other;

  };

} // namespace simsoc

#endif // PPC_STATISTICS_VERYSIMPLE_HPP
