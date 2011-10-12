//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPCIS_HPP
#define PPCIS_HPP

#include "ppcis_visitor.hpp"
#include <libsimsoc/display.hpp>
#include <iostream>
#include <inttypes.h>

namespace simsoc {

  class PPC_Processor;

  struct PPC_Instruction: Printable {
    PPC_Instruction() {}
    virtual ~PPC_Instruction() {}
    virtual void exec(PPC_Processor& proc) = 0;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
    virtual bool may_branch() const;
    virtual bool delete_me() const {return true;}
  };

  struct PPC_Undefined: public PPC_Instruction {
    const char * msg;
    PPC_Undefined(const char * message): msg(message) {}
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  struct PPC_Unpredictable: public PPC_Instruction {
    const char * msg;
    PPC_Unpredictable(const char * message): msg(message) {}
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream& os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  struct PPC_Nop: public PPC_Instruction {
    PPC_Nop(){}
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream &os) const;
    bool may_branch() const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

  struct PPC_Break: public PPC_Instruction {
    PPC_Break(){}
    void exec(PPC_Processor &proc);
    std::ostream& display(std::ostream &os) const;
    virtual void accept(PPC_InstructionVisitor &visitor) {visitor.visit(*this);}
  };

} // namespace simsoc

#endif //PPCIS_HPP
