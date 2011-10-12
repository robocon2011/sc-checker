//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPCIS_DYNTRANS_HPP
#define PPCIS_DYNTRANS_HPP

#include "simsoc-config.h"

#include "ppcis.hpp"
#include "ppc_pi.hpp"
#include <vector>

#ifdef SIMSOC_HAVE_LLVM
namespace llvm {class Function;}
#endif

namespace simsoc {

  class PPC_BasicBlock: public PPC_Instruction {
  public:
    PPC_BasicBlock();
    ~PPC_BasicBlock();
    void push_back(PPC_Processor &proc, PPC_Instruction *i, bool &is_generic_pi);
    std::ostream& display(std::ostream& os) const;
    void exec(PPC_Processor& proc);
    size_t size() const {return pis.size();}

#ifdef SIMSOC_HAVE_LLVM
    std::vector<PPC_Instruction*> is;
#endif

  private:
    std::vector<PPC_PseudoInstruction> pis;
    size_t count;
  };

  class PPC_EmptyCell: public PPC_Instruction {
    PPC_EmptyCell(): PPC_Instruction() {}
    static PPC_EmptyCell singleton;
  public:
    static PPC_EmptyCell *get() {
      return &singleton;
    }
    std::ostream& display(std::ostream& os) const;
    void exec(PPC_Processor& proc);
    bool delete_me() const {return false;}
  };

#ifdef SIMSOC_HAVE_LLVM
  class PPC_OptimizedBasicBlock: public PPC_Instruction {
  public:
    typedef void (*ExecFunction)(PPC_Processor*);
    PPC_OptimizedBasicBlock(PPC_BasicBlock *, llvm::Function *, ExecFunction);
    ~PPC_OptimizedBasicBlock();
    std::ostream& display(std::ostream& os) const;
    void exec(PPC_Processor& proc);
  private:
    PPC_BasicBlock *ebi;
    llvm::Function *llvm_function;
    ExecFunction native_function;
  };
#endif

} // namespace simsoc

#endif // PPCIS_DYNTRANS_HPP
