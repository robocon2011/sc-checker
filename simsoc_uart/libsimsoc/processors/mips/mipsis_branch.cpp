//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mipsis_branch.hpp"

using namespace std;

namespace simsoc {

  template <>
  void MIPS_bgezal<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    proc.pc += 4;
    if((int32_t)proc.regs[rs] >= 0)
      {
        MIPS_Instruction<uint32_t>* instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
        proc.debug() << "execute the instruction in delay slot " << *instr << endl;
        instr->exec(proc);
        delete(instr);
        proc.regs[31] = proc.pc + 4;
        proc.pc += sign_ext<uint32_t>(branch_offset) -4;
        proc.debug() << "brand to " << proc.pc << endl;
      }
  }

  template <>
  void MIPS_bgezal<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    proc.pc += 4;
    if((int64_t)proc.regs[rs] >= 0)
      {
        MIPS_Instruction<uint64_t>* instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
        proc.debug() << "execute the instruction in delay slot " << *instr << endl;
        instr->exec(proc);
        delete(instr);
        proc.regs[31] = proc.pc + 4;
        proc.pc += sign_ext<uint64_t>(branch_offset) -4;
        proc.debug() << "brand to " << proc.pc << endl;
      }
  }

  template <>
  void MIPS_bgezall<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    proc.pc += 4;
    if((int32_t)proc.regs[rs] >= 0)
      {
        MIPS_Instruction<uint32_t>* instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
        proc.debug() << "execute the instruction in delay slot " << *instr << endl;
        instr->exec(proc);
        delete(instr);
        proc.regs[31] = proc.pc + 4;
        proc.pc += sign_ext<uint32_t>(branch_offset) -4;
        proc.debug() << "brand to " << proc.pc << endl;
      }
  }

  template <>
  void MIPS_bgezall<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    proc.pc += 4;
    if((int64_t)proc.regs[rs] >= 0)
      {
        MIPS_Instruction<uint64_t>* instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
        proc.debug() << "execute the instruction in delay slot " << *instr << endl;
        instr->exec(proc);
        delete(instr);
        proc.regs[31] = proc.pc + 4;
        proc.pc += sign_ext<uint64_t>(branch_offset) -4;
        proc.debug() << "brand to " << proc.pc << endl;
      }
  }

  template <>
  void MIPS_bgezl<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    proc.pc += 4;
    if((int32_t)proc.regs[rs] >= 0)
      {
        MIPS_Instruction<uint32_t>* instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
        proc.debug() << "execute the instruction in delay slot " << *instr << endl;
        instr->exec(proc);
        delete(instr);
        proc.pc += sign_ext<uint32_t>(branch_offset) -4;
        proc.debug() << "brand to " << proc.pc << endl;
      }
  }

  template <>
  void MIPS_bgezl<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    proc.pc += 4;
    if((int64_t)proc.regs[rs] >= 0)
      {
        MIPS_Instruction<uint64_t>* instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
        proc.debug() << "execute the instruction in delay slot " << *instr << endl;
        instr->exec(proc);
        delete(instr);
        proc.pc += sign_ext<uint64_t>(branch_offset) -4;
        proc.debug() << "brand to " << proc.pc << endl;
      }
  }

  template <>
  void MIPS_bgtz<uint32_t>::exec(MIPS_Processor<uint32_t> &proc) {
    proc.pc +=4;
    if ((int32_t)proc.regs[rs]>0) {//?
      MIPS_Instruction<uint32_t> * instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<endl;
      instr->exec(proc);
      delete(instr);
      proc.pc = proc.pc + sign_ext<uint32_t>(branch_offset) - 4;
      proc.debug() <<"branch to: \t" << hex << proc.pc <<endl;
    }
  }

  template <>
  void MIPS_bgtz<uint64_t>::exec(MIPS_Processor<uint64_t> &proc) {
    proc.pc +=4;
    if ((int64_t)proc.regs[rs]>0) {//?
      MIPS_Instruction<uint64_t> * instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<endl;
      instr->exec(proc);
      delete(instr);
      proc.pc = proc.pc + sign_ext<uint64_t>(branch_offset) - 4;
      proc.debug() <<"branch to: \t" << hex << proc.pc <<endl;
    }
  }

  template <>
  void MIPS_bgtzl<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    proc.pc +=4;
    if ((int32_t)proc.regs[rs]>0) {
      MIPS_Instruction<uint32_t> * instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<endl;
      instr->exec(proc);
      delete(instr);
      proc.pc = proc.pc + sign_ext<uint32_t>(branch_offset) - 4;
      proc.debug() <<"branch to: \t" << hex << proc.pc <<endl;
    }
  }

  template <>
  void MIPS_bgtzl<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    proc.pc +=4;
    if ((int64_t)proc.regs[rs]>0) {
      MIPS_Instruction<uint64_t> * instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<endl;
      instr->exec(proc);
      delete(instr);
      proc.pc = proc.pc + sign_ext<uint64_t>(branch_offset) - 4;
      proc.debug() <<"branch to: \t" << hex << proc.pc <<endl;
    }
  }

  template <>
  void MIPS_blez<uint32_t>::exec(MIPS_Processor<uint32_t> &proc) {
    proc.pc +=4;
    if(((int32_t)proc.regs[rs])<=0) {
      MIPS_Instruction<uint32_t> * instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<endl;
      instr->exec(proc);
      delete(instr);
      proc.pc += sign_ext<uint32_t>(branch_offset) - 4;
    }
  }

  template <>
  void MIPS_blez<uint64_t>::exec(MIPS_Processor<uint64_t> &proc) {
    proc.pc +=4;
    if(((int64_t)proc.regs[rs])<=0) {
      MIPS_Instruction<uint64_t> * instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<endl;
      instr->exec(proc);
      delete(instr);
      proc.pc += sign_ext<uint64_t>(branch_offset) - 4;
    }
  }

  template <>
  void MIPS_blezl<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    proc.pc +=4;
    if(((int32_t)proc.regs[rs])<=0) {
      MIPS_Instruction<uint32_t> * instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<endl;
      instr->exec(proc);
      delete(instr);
      proc.pc += sign_ext<uint32_t>(branch_offset) - 4;
    }
  }

  template <>
  void MIPS_blezl<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    proc.pc +=4;
    if (((int64_t)proc.regs[rs])<=0) {
      MIPS_Instruction<uint64_t> * instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<endl;
      instr->exec(proc);
      delete(instr);
      proc.pc += sign_ext<uint64_t>(branch_offset) - 4;
    }
  }

  template <>
  void MIPS_bltzal<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    proc.pc += 4;
    if ((int32_t)proc.regs[rs] < 0) {
      MIPS_Instruction<uint32_t> *instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
      proc.debug() << "execute the instruction in delay slot " << *instr << endl;
      instr -> exec(proc);
      delete(instr);
      proc.regs[31] = proc.pc + 4;
      proc.pc += sign_ext<uint32_t>(branch_offset) - 4;
      proc.debug() << "branch to " << proc.pc << endl;
    }
  }

  template <>
  void MIPS_bltzal<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    proc.pc += 4;
    if ((int64_t)proc.regs[rs] < 0) {
      MIPS_Instruction<uint64_t> *instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
      proc.debug() << "execute the instruction in delay slot " << *instr << endl;
      instr -> exec(proc);
      delete(instr);
      proc.regs[31] = proc.pc + 4;
      proc.pc += sign_ext<uint64_t>(branch_offset) - 4;
      proc.debug() << "branch to " << proc.pc << endl;
    }
  }

  template <>
  void MIPS_bltzall<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    proc.pc += 4;
    if ((int32_t)proc.regs[rs] < 0) {
      MIPS_Instruction<uint32_t> *instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
      proc.debug() << "execute the instruction in delay slot " << *instr << endl;
      instr -> exec(proc);
      delete(instr);
      proc.regs[31] = proc.pc + 4;
      proc.pc += sign_ext<uint32_t>(branch_offset) - 4;
      proc.debug() << "branch to " << proc.pc << endl;
    }
  }

  template <>
  void MIPS_bltzall<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    proc.pc += 4;
    if ((int64_t)proc.regs[rs] < 0) {
      MIPS_Instruction<uint64_t> *instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
      proc.debug() << "execute the instruction in delay slot " << *instr << endl;
      instr -> exec(proc);
      delete(instr);
      proc.regs[31] = proc.pc + 4;
      proc.pc += sign_ext<uint64_t>(branch_offset) - 4;
      proc.debug() << "branch to " << proc.pc << endl;
    }
  }

  template <>
  void MIPS_bltzl<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    proc.pc += 4;
    if ((int32_t)proc.regs[rs] < 0) {
      MIPS_Instruction<uint32_t> *instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
      proc.debug() << "execute the instruction in delay slot " << *instr << endl;
      instr -> exec(proc);
      delete(instr);
      proc.pc += sign_ext<uint32_t>(branch_offset) - 4;
      proc.debug() << "branch to " << proc.pc << endl;
    }
  }

  template <>
  void MIPS_bltzl<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    proc.pc += 4;
    if ((int64_t)proc.regs[rs] < 0) {
      MIPS_Instruction<uint64_t> *instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
      proc.debug() << "execute the instruction in delay slot " << *instr << endl;
      instr -> exec(proc);
      delete(instr);
      proc.pc += sign_ext<uint64_t>(branch_offset) - 4;
      proc.debug() << "branch to " << proc.pc << endl;
    }
  }

  template <>
  void MIPS_bltz<uint32_t>::exec(MIPS_Processor<uint32_t> &proc) {
    proc.pc +=4;
    if (((int32_t)proc.regs[rs])<0) {
      MIPS_Instruction<uint32_t> * instr = mipsDecode<uint32_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<endl;
      instr->exec(proc);
      delete(instr);
      proc.pc += sign_ext<uint32_t>(branch_offset) - 4;
      proc.debug() <<"branch to: \t" <<hex<<proc.pc<<endl;
    }
  }

  template <>
  void MIPS_bltz<uint64_t>::exec(MIPS_Processor<uint64_t> &proc) {
    proc.pc +=4;
    if (((int64_t)proc.regs[rs])<0) {
      MIPS_Instruction<uint64_t> * instr = mipsDecode<uint64_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<endl;
      instr->exec(proc);
      delete(instr);
      proc.pc += sign_ext<uint64_t>(branch_offset) - 4;
      proc.debug() <<"branch to: \t" <<hex<<proc.pc<<endl;
    }
  }

  template <>
  void MIPS_teqi<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    if ((int32_t)proc.regs[rs] == (int32_t)sign_ext<uint32_t>(immed)) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc +=4;
  }

  template <>
  void MIPS_teqi<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    if ((int64_t)proc.regs[rs] == (int64_t)sign_ext<uint64_t>(immed)) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc +=4;
  }

  template <>
  void MIPS_tge<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    if ((int32_t)proc.regs[rs] >= (int32_t)proc.regs[rt]) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc += 4;
  }

  template <>
  void MIPS_tge<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    if ((int64_t)proc.regs[rs] >= (int64_t)proc.regs[rt]) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc += 4;
  }

  template <>
  void MIPS_tgei<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    if ((int32_t)proc.regs[rs] >= (int32_t)sign_ext<uint32_t>(immed)) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc += 4;
  }

  template <>
  void MIPS_tgei<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    if ((int64_t)proc.regs[rs] >= (int64_t)sign_ext<uint64_t>(immed)) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc += 4;
  }

  template <>
  void MIPS_tlt<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    if((int32_t)proc.regs[rs] <= (int32_t)proc.regs[rt]) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    }
    else
      proc.pc += 4;
  }

  template <>
  void MIPS_tlt<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    if ((int64_t)proc.regs[rs] <= (int64_t)proc.regs[rt]) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc += 4;
  }

  template <>
  void MIPS_tlti<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    if ((int32_t)proc.regs[rs] <= (int32_t)sign_ext<uint32_t>(immed)) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc += 4;
  }

  template <>
  void MIPS_tlti<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    if ((int64_t)proc.regs[rs] <= (int64_t)sign_ext<uint64_t>(immed)) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc += 4;
  }

  template <>
  void MIPS_tnei<uint32_t>::exec(MIPS_Processor<uint32_t> &proc)
  {
    if ((int32_t)proc.regs[rs] != (int32_t)sign_ext<uint32_t>(immed)) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc += 4;
  }

  template <>
  void MIPS_tnei<uint64_t>::exec(MIPS_Processor<uint64_t> &proc)
  {
    if ((int64_t)proc.regs[rs] != (int64_t)sign_ext<uint64_t>(immed)) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    } else
      proc.pc += 4;
  }

} // namespace simsoc
