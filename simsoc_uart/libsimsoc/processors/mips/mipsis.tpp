//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// included at the end of "mipsis.hpp"

#include "mips_processor.hpp"

namespace simsoc {

  template <typename word_t>
  void MIPS_Instruction<word_t>::exec(MIPS_Processor<word_t> &proc) {
    proc.error() <<"instruction not yet implemented: " <<*this <<'\n';
    exit(1);
  }

  // void MIPS_Instruction::translate(MIPS_PseudoInstruction &pi) {
  //   mipsTranslateGeneric(pi,this);
  // }

  /******************************************************************************/

  template <typename word_t>
  void MIPS_FP_Instruction<word_t>::exec(MIPS_Processor<word_t> &proc) {
    proc.error() <<"floating point instructions (pc = " <<std::hex <<proc.pc <<")\n";
    exit(1);
  }

  template <typename word_t>
  std::ostream& MIPS_FP_Instruction<word_t>::display(std::ostream& os) const {
    return os <<"Not Implemented Floating Point Instruction:: " <<msg;
  }

  template <typename word_t>
  std::ostream&  MIPS_Reserved_Instruction<word_t>::display(std::ostream& os) const {
    return os <<"Reserved Instruction:: " <<msg;
  }

  /******************************************************************************/

  template <typename word_t>
  void MIPS_Unpredictable<word_t>::exec(MIPS_Processor<word_t> &proc) {
    proc.error() <<"unpredictable instruction: " <<msg <<'\n';
    exit(4);
  }

  template <typename word_t>
  std::ostream& MIPS_Unpredictable<word_t>::display(std::ostream& os) const {
    return os <<"Unpredictable instruction: " <<msg;
  }
  /*******************************************************************************/

  template <typename word_t>
  void MIPS_Undefined<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.error() << "undefined instruction at pc = " <<std::hex <<proc.pc<<" "<< msg <<"\n";
    exit(4);
  }

  template <typename word_t>
  std::ostream& MIPS_Undefined<word_t>::display(std::ostream& os) const{
    return os << "undefined instruction: "<< msg<<"\n";
  }

} // namespace simsoc
