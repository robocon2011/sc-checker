//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// included from mips_translation_page.cpp

#include "mips_translation_page.hpp"
#include "mips_decode.hpp"
#include "mips_translator.hpp"
#include <libsimsoc/display.hpp>
#include <cstring>

namespace simsoc {

  // constructor initializes the arrays and sets the page implementation
  // in host memory address
  template<typename word_t>
  MIPS_TranslationPage<word_t>::MIPS_TranslationPage(uint32_t *host_addr):
    TranslationPage(host_addr),
    nb_instr(TR_PAGE_SIZE/instr_size), //instructions on one page
    instructions(NULL)
  {
    instructions = new MIPS_Instruction<word_t> * [nb_instr];
    memset(instructions, '\0', nb_instr*sizeof(MIPS_Instruction<word_t> *));
  }

  // destructor deletes the array
  template<typename word_t>
  MIPS_TranslationPage<word_t>::~MIPS_TranslationPage() {
    for (unsigned int i = 0; i < nb_instr; ++i)
      if (instructions[i]->delete_me())
        delete instructions[i];
    delete[] instructions;
  }

  template<typename word_t>
  void MIPS_TranslationPage<word_t>::decode() {
    info() << "decode a MIPS page of binary code.\n";
    for(unsigned n = 0; n < TR_PAGE_SIZE/4; ++n)
      instructions[n] = mipsDecode<word_t>(host_address[n]);
  }

  template<typename word_t>
  void MIPS_TranslationPage<word_t>::fill(MIPS_Instruction<word_t> *inst) {
    for (unsigned n = 0; n<TR_PAGE_SIZE/4; ++n)
      instructions[n] = inst;
  }

  template<typename word_t>
  uint32_t MIPS_TranslationPage<word_t>::getBincode(word_t pc) const {
    return host_address[mips_page_offset(pc)];
  }

} // namespace simsoc
