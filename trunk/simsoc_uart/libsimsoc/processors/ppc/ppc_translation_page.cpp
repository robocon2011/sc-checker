//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "ppc_translation_page.hpp"
#include "ppc_decode.hpp"
#include "ppc_translate.hpp"
#include <cstring>

namespace simsoc {

  /*--------------------------------------------------------------------------*/
  PPC_TranslationPage::PPC_TranslationPage(uint32_t* host_addr):
    TranslationPage(host_addr),
    nb_instr(TR_PAGE_SIZE/instr_size),
    instructions(NULL)
  {
    instructions = new PPC_Instruction*[nb_instr];
    memset(instructions, '\0', nb_instr*sizeof(PPC_Instruction*));
  }

  PPC_TranslationPage::~PPC_TranslationPage() {
    for (unsigned i=0; i<nb_instr; ++i)
      if (instructions[i]->delete_me())
        delete instructions[i];
    delete[] instructions;
  }

  void PPC_TranslationPage::decode() {
    for (unsigned n = 0; n<TR_PAGE_SIZE/4; ++n) {
      instructions[n] = ppcDecode(host_address[n]);
    }
  }

  void PPC_TranslationPage::fill(PPC_Instruction *inst) {
    for (unsigned n = 0; n<TR_PAGE_SIZE/4; ++n)
      instructions[n] = inst;
  }

  uint32_t PPC_TranslationPage::getBincode(uint32_t pc) {
    return host_address[(pc&(TR_PAGE_SIZE-1))/4];
  }

} // namespace simsoc
