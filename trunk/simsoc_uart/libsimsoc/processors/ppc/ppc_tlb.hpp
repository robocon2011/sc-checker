//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_TLB_HPP_
#define PPC_TLB_HPP_

#include "libsimsoc/processors/mmu.hpp"
#include "libsimsoc/processors/ppc/ppc_tool.hpp"

namespace simsoc {

  //-----------------------------------------------------
  class PPC_TLBEntry: public TLBEntry<BUS32>
  {
  public:
    uint32_t pte1; //phy_addr frame number

    PPC_TLBEntry(): pte1(0) {}

    PPC_TLBEntry(uint32_t va, uint32_t _pte1, uint32_t offset) {
      virt_addr = va;
      pte1 = _pte1;
      mask = offset;
    }

    uint32_t getPA(uint32_t va) {
      return (pte1 & (~mask)) | (va & mask);
    }
  };

  //-----------------------------------------------------
  class PPC_TLB: public TLB<BUS32> {
  public:
    typedef uint32_t word_t;

    PPC_TLB();
  };

} // namespace simsoc

#endif /* PPC_TLB_HPP_ */
