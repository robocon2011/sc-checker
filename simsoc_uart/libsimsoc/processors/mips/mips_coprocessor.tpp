//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Implementation of "mips_coprocessor.hpp"
// This file is included only by "mips_coprocessor.cpp"
#include "mips_coprocessor.hpp"
#include "mips_processor.hpp"

namespace simsoc {

template <typename word_t>
MIPS_Coprocessor<word_t>::MIPS_Coprocessor(sc_core::sc_module_name name,
                                           MIPS_Processor<word_t> *proc,
                                           MIPS_MMU<word_t> *mmu_):
  Module(name),
  mips_processor(*proc),
  mips_mmu(*mmu_)
{
  assert(proc);
  assert(mmu_);

  for(uint8_t i=0;i<32;i++)
    regs[i]=0;
}

template<typename word_t>
void MIPS_Coprocessor<word_t>::write_cp0(uint32_t n, word_t value)
{
  switch(n) {
  case CP0_RANDOM :    //read-only register
    warning()<<"write operation on read-only CP0 Random register"<<std::endl;
    break;
  case CP0_BADADDR :   //read-only register
    warning()<<"write operation on read-only CP0 BadAddr register"<<std::endl;
    break;
  case CP0_STATUS:
    reg_status = static_cast<uint32_t>(value);
    break;
  case CP0_CAUSE:
    reg_cause = static_cast<uint32_t>(value);
    break;
  default :
    regs[n] = value;
    break;
  }
}

template<typename word_t>
word_t MIPS_Coprocessor<word_t>::read_cp0(uint32_t n)
{
  switch(n){
  case CP0_RANDOM:
    return get_random();
  case CP0_STATUS:
    return reg_status.get_value();
  case CP0_CAUSE:
    return reg_cause.get_value();
  default:
    return regs[n];
  }
}

} // namespace simsoc
