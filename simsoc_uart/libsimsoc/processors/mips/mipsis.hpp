//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPSIS_HPP
#define MIPSIS_HPP

#include "mips_base.hpp"
#include <libsimsoc/display.hpp>
#include <cassert>

namespace simsoc {

  template <typename word_t>
  class MIPS_FP_Instruction: public MIPS_Instruction<word_t>  {
  public:
    const char * msg;
    MIPS_FP_Instruction(const char * message):
      msg(message){}
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
  };

  template <typename word_t>
  class MIPS_Reserved_Instruction: public MIPS_Instruction<word_t> {
  public:
    const char * msg;
    MIPS_Reserved_Instruction(const char * message):
      msg(message) {}
    //   void exec(MIPS_Processor &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
  };

  template <typename word_t>
  class MIPS_Unpredictable: public MIPS_Instruction<word_t> {
  public:
    const char * msg;
    MIPS_Unpredictable(const char * message):
      msg(message) {}
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
  };

  template <typename word_t>
  class MIPS_Undefined: public MIPS_Instruction<word_t> {
  public:
    const char * msg;
    MIPS_Undefined(const char * message):
      msg(message) {}
    void exec(MIPS_Processor<word_t> &proc);
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    std::ostream& display(std::ostream& os) const;
  };

} // namespace simsoc

#include "mipsis.tpp"

#endif

