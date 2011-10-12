//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mips_translation_page.tpp"
#include <libsimsoc/processors/common.hpp>

namespace simsoc {

  template class MIPS_TranslationPage<BUS32>;

  template class MIPS_TranslationPage<BUS64>;

} // namespace simsoc
