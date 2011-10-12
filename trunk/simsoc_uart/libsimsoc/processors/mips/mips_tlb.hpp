//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_TLB_HPP
#define MIPS_TLB_HPP

#include "libsimsoc/processors/mmu.hpp"
#include <cassert>

// This header file declares the classes MIPS_TLBEntry and MIPS_TLB

namespace simsoc {

  // Forward declarations
  template <typename word_t> class MIPS_Coprocessor;

/*
 * the definition of the tlb entry
 */
template <typename word_t>
class MIPS_TLBEntry: public TLBEntry<word_t>
{
public:

  word_t PFN[2];
  uint8_t C[2];
  bool D[2];
  bool V[2];
  bool isGlobal;
  uint8_t ASID;
  word_t VPN2;
  uint16_t pageMask;

  MIPS_TLBEntry() :
    PFN(), C(), D(), V(),isGlobal(0),ASID(0){}

  word_t getPA(word_t va){
    word_t odd_select=!!(va & TLBEntry<word_t>::mask & ~(TLBEntry<word_t>::mask>>1));
    //get pfn[24:6] for pa[31:12]
    return (PFN[odd_select]<<7) | (va & TLBEntry<word_t>::mask);
  }

  word_t getCached(word_t va) {
    word_t odd_select=!!(va & TLBEntry<word_t>::mask & ~(TLBEntry<word_t>::mask>>1));
    return C[odd_select];
  }

  word_t getBuffered(word_t va) {
    word_t odd_select=!!(va & TLBEntry<word_t>::mask & ~(TLBEntry<word_t>::mask>>1));
    return D[odd_select];
  }

  word_t getV(word_t va) {
    word_t odd_select=!!(va & TLBEntry<word_t>::mask & ~(TLBEntry<word_t>::mask>>1));
    return V[odd_select];
  }

  word_t get_ASID(){
    return ASID;
  }
};

/*
 * * definition of mips tlb
 */

template <typename word_t>
class MIPS_TLB: public TLB<word_t>
{
public:
  MIPS_TLB(const char* tlb_name, uint32_t tlb_size);

  TLBEntry<word_t> **search_entry(word_t virt_addr);
  void add_entry(TLBEntry<word_t> *entry, word_t index);

  MIPS_Coprocessor<word_t>* cp0;
};

} // namespace simsoc

#endif
