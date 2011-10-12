//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_TRANSLATION_PAGE_HPP
#define MIPS_TRANSLATION_PAGE_HPP

#include "mips_base.hpp"
#include <libsimsoc/translation_page.hpp>

namespace simsoc {

  // macro to get a 32 bits word page offset in bytes
  inline size_t mips_page_offset(uint64_t addr) {
    return (addr & (TranslationPage::TR_PAGE_SIZE-1)) >> 2;
  }

  template<typename word_t>
  class MIPS_TranslationPage: public TranslationPage {
  public:
    MIPS_TranslationPage(uint32_t *binary_address);
    ~MIPS_TranslationPage();

    void decode();
    void fill(MIPS_Instruction<word_t>*);
    inline MIPS_Instruction<word_t> * locateInstr(word_t) const;
    inline MIPS_Instruction<word_t> **locateInstrPtr(word_t) const;
    uint32_t getBincode(word_t pc) const;

  protected:
    const size_t nb_instr; // size of instructions array
    static const int instr_size = 4;
    MIPS_Instruction<word_t> **instructions; // array of pointers to instructions
  };

  template<typename word_t>
  MIPS_Instruction<word_t>*
  MIPS_TranslationPage<word_t>::locateInstr(word_t addr) const {
    return instructions[mips_page_offset(addr)];
  }

  template<typename word_t>
  MIPS_Instruction<word_t>**
  MIPS_TranslationPage<word_t>::locateInstrPtr(word_t addr) const {
    return &instructions[mips_page_offset(addr)];
  }


} // namespace simsoc

#endif // MIPS_TRANSLATION_PAGE_HPP
