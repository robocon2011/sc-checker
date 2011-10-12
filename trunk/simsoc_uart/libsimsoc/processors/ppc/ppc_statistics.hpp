//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_STATISTICS_HPP
#define PPC_STATISTICS_HPP

#include "ppcis_visitor.hpp"
#include <cstdlib>

namespace simsoc {

  struct PPC_Statistics: PPC_InstructionVisitor {

    virtual void write(const char *filename) = 0;
  };

} // namespace simsoc

#endif // PPC_STATISTICS_HPP
