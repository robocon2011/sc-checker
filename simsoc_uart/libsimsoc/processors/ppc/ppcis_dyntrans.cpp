//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "ppcis_dyntrans.hpp"
#include "ppc_processor.hpp"
#include "ppc_translate.hpp"
#include <cassert>

#ifdef SIMSOC_HAVE_LLVM
#include <llvm/Function.h>
#include "ppc_llvm_generator.hpp"
#endif

namespace simsoc {

  static bool may_branch_and_delete(PPC_Instruction *instr, bool &dont_delete) {
    const bool may_branch = instr->may_branch();
#ifndef SIMSOC_HAVE_LLVM
    if (!dont_delete)
      delete instr;
#endif
    return may_branch;
  }

  PPC_BasicBlock::PPC_BasicBlock():
    PPC_Instruction(), pis(), count(0) {}

  PPC_BasicBlock::~PPC_BasicBlock() {
#ifndef SIMSOC_HAVE_LLVM
    std::vector<PPC_PseudoInstruction>::iterator i = pis.begin();
    const std::vector<PPC_PseudoInstruction>::iterator ei = pis.end();
    do {
      destructPseudo(*i);
      ++i;
    } while (i!=ei);
#else // SIMSOC_HAVE_LLVM
    std::vector<PPC_Instruction*>::iterator i = is.begin();
    const std::vector<PPC_Instruction*>::iterator ei = is.end();
    do {
      delete *i;
      ++i;
    } while (i!=ei);
#endif
  }

  void PPC_BasicBlock::push_back(PPC_Processor& proc,
                                     PPC_Instruction *instr,
                                     bool &is_generic_pi) {
    // This function is called just after instr is executed.
#ifdef SIMSOC_HAVE_LLVM
    is.push_back(instr);
#endif
    {
      PPC_PseudoInstruction pi;
      pis.push_back(pi);
    }
    PPC_Translate(proc,instr,pis[pis.size()-1]);

    // a "generic" pseudo-instruction takes the ownership of instr.
    is_generic_pi = isPseudoGeneric(pis[pis.size()-1]);
  }

  std::ostream& PPC_BasicBlock::display(std::ostream& os) const {
    return os <<"execute block [size=" <<std::dec <<pis.size()
              <<"; count=" <<count <<"]";
  }

  void PPC_BasicBlock::exec(PPC_Processor& proc) {
    PseudoStatus status;
    ++count;
#ifdef SIMSOC_HAVE_LLVM
    if (proc.mode==simsoc::DYN_COMP && count>proc.dt3_threshold) {
      PPC_OptimizedBasicBlock *ebn = PPC_LLVM_Generator::get().compile(this);
      PPC_Instruction **this_ptr = proc.get_current_instr_ptr();
      *this_ptr = ebn;
      proc.info() <<"basic block at address " <<hex <<proc.cpu.pc
                  <<" compiled to native code\n";
      ebn->exec(proc);
    } else {
#endif
      std::vector<PPC_PseudoInstruction>::iterator i = pis.begin();
      const std::vector<PPC_PseudoInstruction>::iterator ei = pis.end();
      do {
        status = i->f(proc, *i);
        assert(status==OK || i+1==ei);
        proc.cpu.pc += 4;
        proc.hook();
        ++i;
      } while (i!=ei);
      if (status!=OK)
        proc.cpu.pc -= 4;
#ifdef SIMSOC_HAVE_LLVM
    }
#endif
  }

  PPC_EmptyCell PPC_EmptyCell::singleton = PPC_EmptyCell();

  std::ostream& PPC_EmptyCell::display(std::ostream& os) const {
    return os <<"translate block";
  }

  void PPC_EmptyCell::exec(PPC_Processor& proc) {
    // FIXME: the block may covers many pages. So, it should be discarded:
    //        - if any of the physical page is modified
    //        - if the virtual page order changes

    PPC_BasicBlock *ebi = new PPC_BasicBlock(); // FIXME: delete if exception
    PPC_Instruction **this_ptr = proc.get_current_instr_ptr();
    PPC_Instruction *instr;
    bool is_generic_pi = false;
    const uint32_t start = proc.cpu.pc;
    proc.info() <<"translate block starting at address "
           <<hex <<start <<".\n";
    do {
      instr = proc.fetch_instruction();
      proc.debug() <<"execute & translate: " <<*instr <<'\n';
      instr->exec(proc);
      ebi->push_back(proc,instr,is_generic_pi);
      proc.hook();
    } while (!may_branch_and_delete(instr,is_generic_pi));
    *this_ptr = ebi; // REMARK: invalidated pages are not destroyed immediately
    proc.info() <<"translated block ends at address "
                <<hex <<start+4*ebi->size()-4 <<".\n";

    // The line below compiles a basic block to LLVM and next to native code
    // PPC_OptimizedBasicBlock *ebn = PPC_LLVM_Generator::get().compile(ebi);
    // COMMENT THE LINE ABOVE BEFORE COMMITING
  }

#ifdef SIMSOC_HAVE_LLVM
  PPC_OptimizedBasicBlock::PPC_OptimizedBasicBlock(PPC_BasicBlock *eb,
                                                 llvm::Function *lf,
                                                 ExecFunction nf):
    ebi(eb), llvm_function(lf), native_function(nf)
  {}

  PPC_OptimizedBasicBlock::~PPC_OptimizedBasicBlock() {
    llvm_function->eraseFromParent();
    delete ebi;
  }

  std::ostream &PPC_OptimizedBasicBlock::display(std::ostream& os) const {
    return os <<"block translated to native code";
  }

  void PPC_OptimizedBasicBlock::exec(PPC_Processor &proc) {
    (*native_function)(&proc);
  }
#endif

} // namespace simsoc
