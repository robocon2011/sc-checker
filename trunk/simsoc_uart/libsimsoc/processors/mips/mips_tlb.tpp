//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mips_tlb.hpp"

#include "libsimsoc/processors/mips/mips_coprocessor.hpp"

namespace simsoc {

template<typename word_t>
MIPS_TLB<word_t>::MIPS_TLB(const char* tlb_name,
		      uint32_t tlb_size):
  TLB<word_t>(tlb_name, tlb_size){
}

template<typename word_t>
TLBEntry<word_t> **MIPS_TLB<word_t>::search_entry(word_t virt_addr) {
  MIPS_TLBEntry<word_t> *entry;
  for (uint32_t i = 0; i < this->size; i++) {
    entry = static_cast<MIPS_TLBEntry<word_t>*>(this->entries[i]);
    if (!entry) {
      continue;
    }
    if ((virt_addr & ~(entry ->mask)) == entry ->virt_addr) {
      if ((entry->isGlobal) || (entry->ASID == entry->get_ASID())) {
        this->search_pos=i;
        return &this->entries[i];
      }
    }
  }
  return NULL;
}

template<typename word_t>
void MIPS_TLB<word_t>::add_entry(TLBEntry<word_t> *entry, word_t index) {
  assert(index<this->size);
  if(this->entries[index])
    {
      delete this->entries[index];
      this->entries[index]=NULL;
    }
  this->entries[index]=entry;
  this->curpos=index;
}

} // namespace simsoc
