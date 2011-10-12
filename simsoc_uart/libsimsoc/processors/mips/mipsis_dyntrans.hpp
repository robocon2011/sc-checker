//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPSIS_DYNTRANS_HPP
#define MIPSIS_DYNTRANS_HPP

#include "mipsis.hpp"
#include "mipspi.hpp"
#include <vector>

namespace simsoc {

  template <typename word_t>
  class MIPS_ExecuteBlock: public MIPS_Instruction<word_t> {
  public:
    MIPS_ExecuteBlock();
    ~MIPS_ExecuteBlock();
    void push_back(MIPS_Processor<word_t> &proc,
                   MIPS_Instruction<word_t> *i, bool &is_generic_pi);
    std::ostream& display(std::ostream& os) const;
    void exec(MIPS_Processor<word_t>& proc);
    size_t size() const {return pis.size();}
  private:
    typedef std::vector<MIPS_PseudoInstruction<word_t> > vector_t;
    typedef typename vector_t::iterator iterator_t;
    vector_t pis;
    size_t count;
  };

  template <typename word_t>
  class MIPS_TranslateBlock: public MIPS_Instruction<word_t> {
    MIPS_TranslateBlock(): MIPS_Instruction<word_t>() {}
    static MIPS_TranslateBlock<word_t> singleton;
  public:
    static MIPS_TranslateBlock<word_t> *get() {
      return &singleton;
    }
    std::ostream& display(std::ostream& os) const;
    void exec(MIPS_Processor<word_t>& proc);
    bool delete_me() const {return false;}
  };

} // namespace simsoc

#endif //MIPSIS_DYNTRANS_HPP
