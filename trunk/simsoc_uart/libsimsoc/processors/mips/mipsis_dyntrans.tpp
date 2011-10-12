//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// included from mipsis_dyntrans.cpp

#include "mipsis_dyntrans.hpp"
#include "mips_processor.hpp"
#include "mips_translator.hpp"
#include <cassert>

namespace simsoc {

  template <typename word_t>
  static bool may_branch_and_delete(MIPS_Instruction<word_t> *instr, bool &dont_delete) {
    const bool may_branch = instr->may_branch();
    if (!dont_delete)
      delete instr;
    return may_branch;
  }

  template <typename word_t>
  MIPS_ExecuteBlock<word_t>::MIPS_ExecuteBlock():
    MIPS_Instruction<word_t>(), pis(), count(0) {}

  template <typename word_t>
  MIPS_ExecuteBlock<word_t>::~MIPS_ExecuteBlock() {
    iterator_t i = pis.begin();
    const iterator_t ei = pis.end();
    do {
      destructPseudo(*i);
      ++i;
    } while (i!=ei);
  }

  template <typename word_t>
  void MIPS_ExecuteBlock<word_t>::push_back(MIPS_Processor<word_t>& proc,
                                            MIPS_Instruction<word_t> *instr,
                                            bool &is_generic_pi) {
    // This function is called just after instr is executed.
    {
      MIPS_PseudoInstruction<word_t> pi;
      pis.push_back(pi);
    }
    MIPS_Translator<word_t>(proc,instr,pis[pis.size()-1]);

    // a "generic" pseudo-instruction takes the ownership of instr.
    is_generic_pi = isPseudoGeneric<word_t>(pis[pis.size()-1]);
  }

  template <typename word_t>
  std::ostream& MIPS_ExecuteBlock<word_t>::display(std::ostream& os) const {
    return os <<"execute block [size=" <<std::dec <<pis.size()
              <<"; count=" <<count <<"]";
  }

  template <typename word_t>
  void MIPS_ExecuteBlock<word_t>::exec(MIPS_Processor<word_t>& proc) {
    assert(pis.size()>=2);
    ++count;
    iterator_t i = pis.begin();
    const iterator_t ei = pis.end()-2; // do not execute last 2 instructions
    while (i!=ei) {
      const PseudoStatus status =  i->f(proc, *i);
      assert(status==OK); (void) status;
      proc.pc += 4;
      proc.hook();
      ++i;
    }
    const PseudoStatus br_status = i->f(proc, *i); // execute branch instruction
    const word_t target_pc = proc.pc; (void) target_pc;
    if (br_status==OK)
      proc.pc += 4;
    proc.hook();
    ++i;
    const PseudoStatus dl_status = i->f(proc, *i); // execute delay_slot instruction
    assert(dl_status==OK); (void) dl_status;
    if (br_status==OK)
      proc.pc += 4;
    proc.hook();
    assert(br_status==OK || proc.pc==target_pc);
    assert(br_status!=OK || proc.pc==target_pc+8);
  }

  template <typename word_t>
  MIPS_TranslateBlock<word_t> MIPS_TranslateBlock<word_t>::singleton =
                             MIPS_TranslateBlock<word_t>();

  template <typename word_t>
  std::ostream& MIPS_TranslateBlock<word_t>::display(std::ostream& os) const {
    return os <<"translate block";
  }

  template <typename word_t>
  void MIPS_TranslateBlock<word_t>::exec(MIPS_Processor<word_t>& proc) {
    // FIXME: the block may covers many pages. So, it should be discarded:
    //        - if any of the physical page is modified
    //        - if the virtual page order changes

    MIPS_ExecuteBlock<word_t> *ebi = new MIPS_ExecuteBlock<word_t>();
    // FIXME: delete if exception

    MIPS_Instruction<word_t> **this_ptr = proc.get_current_instr_ptr();
    MIPS_Instruction<word_t> *instr;
    bool is_generic_pi = false;
    const word_t start = proc.pc;
    word_t previous_pc = proc.pc;
    proc.info() <<"translate block starting at address "
                <<std::hex <<start <<".\n";
    do {
      instr = proc.fetch_instruction();
      proc.debug() <<"execute & translate: " <<*instr <<'\n';
      previous_pc = proc.pc;
      instr->exec(proc);
      ebi->push_back(proc,instr,is_generic_pi);
      proc.hook();
    } while (!may_branch_and_delete(instr,is_generic_pi));
    word_t end = start+4*ebi->size();
    if (end==proc.pc+4) { // the instruction did not branch
      instr = proc.fetch_instruction();
      proc.debug() <<"execute & translate: " <<*instr <<'\n';
      instr->exec(proc);
    } else {
      const word_t target_pc = proc.pc;
      proc.pc = previous_pc+4;
      instr = proc.fetch_instruction(); // instruction in delay slot
      proc.pc = target_pc;
      proc.debug() <<"translate: " <<*instr <<'\n';
    }
    assert(!instr->may_branch());
    ebi->push_back(proc,instr,is_generic_pi);
    proc.hook();
    delete instr;

    *this_ptr = ebi; // REMARK: invalidated pages are not destroyed immediately
    proc.info() <<"translated block ends at address "
                <<std::hex <<end <<".\n";
  }

} // namespace simsoc
