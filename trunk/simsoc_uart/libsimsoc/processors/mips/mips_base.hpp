//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_BASE_HPP
#define MIPS_BASE_HPP

#include "mipsis_visitor.hpp"
#include <iostream>
#include <inttypes.h>
#include <libsimsoc/display.hpp>

namespace simsoc {

  template <typename word_t> class MIPS_Processor;

  template <typename word_t>
  struct MIPS_Instruction: Printable {

    MIPS_Instruction(){}
    virtual ~MIPS_Instruction(){}
    // each subclass must have an exec function
    virtual void exec(MIPS_Processor<word_t> & proc); // = 0;
    // accept visitor
    virtual void accept(MIPS_InstructionVisitor<word_t> &v) {v.visit(this);}
    // block terminator
    virtual bool may_branch() const {return true;}
    // some allocation are not allocated on the heap
    virtual bool delete_me() const {return true;}
  };

  // special types to display general purpose register

  struct MIPS_AsmId: Printable {
    uint8_t id;
    MIPS_AsmId(uint8_t n): id(n) {}
    virtual std::ostream& display(std::ostream& os) const;
  };

} // namespace simsoc

#endif // MIPS_BASE_HPP
