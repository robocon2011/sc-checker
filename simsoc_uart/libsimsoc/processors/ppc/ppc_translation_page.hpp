//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_TRANSLATION_PAGE_HPP
#define PPC_TRANSLATION_PAGE_HPP

#include "ppcis.hpp"
#include "ppc_pi.hpp"
#include <libsimsoc/translation_page.hpp>

namespace simsoc {

  class PPC_TranslationPage: public TranslationPage {
  public:
    PPC_TranslationPage(uint32_t *host_address);
    ~PPC_TranslationPage();

    void decode();
    void fill(PPC_Instruction*);
    inline PPC_Instruction * locateInstr(uint32_t a) const;
    inline PPC_Instruction **locateInstrPtr(uint32_t a) const;
    uint32_t getBincode(uint32_t pc);
    void translate();
  protected:
    const size_t nb_instr;
    static const int instr_size = 4;
    PPC_Instruction **instructions;
  };

  PPC_Instruction * PPC_TranslationPage::locateInstr(uint32_t addr) const {
    return instructions[(addr&(TR_PAGE_SIZE-1))/4];
  }

  PPC_Instruction **PPC_TranslationPage::locateInstrPtr(uint32_t addr) const {
    return &instructions[(addr&(TR_PAGE_SIZE-1))/4];
  }

} // namespace simsoc

#endif //PPC_TRANSLATION_PAGE_HPP
