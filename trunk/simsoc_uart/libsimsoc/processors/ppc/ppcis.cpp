//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <assert.h>
#include "libsimsoc/processors/ppc/ppcis.hpp"
#include "libsimsoc/processors/ppc/ppc_processor.hpp"
#include "libsimsoc/display.hpp"

using namespace std;

namespace simsoc {

  std::ostream& operator<<(std::ostream &os, const PPC_Instruction &instr) {
    return instr.display(os);
  }
  bool PPC_Instruction::may_branch() const {return true;}
  void PPC_Undefined::exec(PPC_Processor &proc) {
    proc.error()<<"pc: "<<hex<<proc.cpu.pc<<endl;//debug...
    TODO("fatal error: undefined instruction");
    //abort();
    tlm::tlm_generic_payload trans;
    uint32_t bincode=0;
    trans.set_data_length(4);
    trans.set_streaming_width(4);
    trans.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    trans.set_address(proc.cpu.pc);
    trans.set_command(tlm::TLM_READ_COMMAND);
    trans.set_data_ptr(reinterpret_cast<uint8_t*>(bincode));
    const unsigned int n = proc.mmu.transport_dbg(trans);
    proc.debug()<<"*pc: "<<bincode<<endl;//debug...
    TODO("fatal error: undefined instruction!\n");
  }

  ostream& PPC_Undefined::display(ostream& os) const {
    return os <<"Undefined instruction: " <<msg;
  }

  void PPC_Unpredictable::exec(PPC_Processor &proc) {
    proc.error() <<"unpredictable instruction: " <<msg <<endl;
    exit(4);
  }

  ostream& PPC_Unpredictable::display(ostream& os) const {
    return os <<"Unpredictable instruction: " <<msg;
  }

  void PPC_Nop::exec(PPC_Processor &proc) {
    proc.cpu.pc += 4;
  }

  ostream& PPC_Nop::display(ostream &os) const {
    return os <<"NOP";
  }

  void PPC_Break::exec(PPC_Processor &proc) {
    TODO("raise the right exception (prefetch)");
  }

  ostream& PPC_Break::display(ostream &os) const {
    return os <<"Break";
  }

  bool PPC_Nop::may_branch() const {return false;}


} // namespace simsoc
