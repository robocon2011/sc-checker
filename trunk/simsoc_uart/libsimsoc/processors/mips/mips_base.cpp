//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mips_base.hpp"
#include "mips_processor.hpp"

using namespace std;

namespace simsoc {

  ostream& MIPS_AsmId::display(ostream& os) const {
    switch (id) {
    case MIPS_Processor<uint32_t>::RA: return os << "ra";
    case MIPS_Processor<uint32_t>::S8: return os << "s8";
    case MIPS_Processor<uint32_t>::SP: return os << "sp";
    case MIPS_Processor<uint32_t>::GP: return os << "gp";
    case MIPS_Processor<uint32_t>::K1: return os << "k1";
    case MIPS_Processor<uint32_t>::K0: return os << "k0";
    case MIPS_Processor<uint32_t>::T9: return os << "t9";
    case MIPS_Processor<uint32_t>::T8: return os << "t8";
    case MIPS_Processor<uint32_t>::S7: return os << "s7";
    case MIPS_Processor<uint32_t>::S6: return os << "s6";
    case MIPS_Processor<uint32_t>::S5: return os << "s5";
    case MIPS_Processor<uint32_t>::S4: return os << "s4";
    case MIPS_Processor<uint32_t>::S3: return os << "s3";
    case MIPS_Processor<uint32_t>::S2: return os << "s2";
    case MIPS_Processor<uint32_t>::S1: return os << "s1";
    case MIPS_Processor<uint32_t>::S0: return os << "s0";
    case MIPS_Processor<uint32_t>::T7: return os << "t7";
    case MIPS_Processor<uint32_t>::T6: return os << "t6";
    case MIPS_Processor<uint32_t>::T5: return os << "t5";
    case MIPS_Processor<uint32_t>::T4: return os << "t4";
    case MIPS_Processor<uint32_t>::T3: return os << "t3";
    case MIPS_Processor<uint32_t>::T2: return os << "t2";
    case MIPS_Processor<uint32_t>::T1: return os << "t1";
    case MIPS_Processor<uint32_t>::T0: return os << "t0";
    case MIPS_Processor<uint32_t>::A3: return os << "a3";
    case MIPS_Processor<uint32_t>::A2: return os << "a2";
    case MIPS_Processor<uint32_t>::A1: return os << "a1";
    case MIPS_Processor<uint32_t>::A0: return os << "a0";
    case MIPS_Processor<uint32_t>::V1: return os << "v1";
    case MIPS_Processor<uint32_t>::V0: return os << "v0";
    case MIPS_Processor<uint32_t>::AT: return os << "at";
    case MIPS_Processor<uint32_t>::R0: return os << "zero";
    }
    UNREACHABLE;
    return os;
  }

} // namespace simsoc
