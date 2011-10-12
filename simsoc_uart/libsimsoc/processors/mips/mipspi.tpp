//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// included at the end of mipspi.hpp

#include "mips_processor.hpp"
#include "mips_decode.hpp"
#include "mipsis.hpp"

namespace simsoc {

  template <typename word_t>
  PseudoStatus mipsPseudoGeneric(MIPS_Processor<word_t> &proc,
                                 const MIPS_PseudoInstruction<word_t>& pi) {
    proc.debug() <<"pif_generic: " <<*pi.args.generic.instr <<'\n';
    pi.args.generic.instr->exec(proc);
    if (pi.args.generic.instr->may_branch())
      return BRANCH;
    else {
      proc.pc -= 4;
      return OK;
    }
  }

  template <typename word_t>
  bool isPseudoGeneric(const MIPS_PseudoInstruction<word_t>& pi) {
    return pi.f==static_cast<typename MIPS_PseudoInstruction<word_t>::MIPS_PseudoFunction>(mipsPseudoGeneric<word_t>);
  }

  template <typename word_t>
  void destructPseudo(MIPS_PseudoInstruction<word_t>& pi) {
    if (isPseudoGeneric(pi))
      delete pi.args.generic.instr;
  }

  template <typename word_t>
  void mipsTranslateGeneric(MIPS_PseudoInstruction<word_t>& pi,
                            MIPS_Instruction<word_t>* instr) {
    pi.f = mipsPseudoGeneric;
    pi.args.generic.instr = instr;
  }

  template <typename word_t>
  PseudoStatus mips_pi_nop(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_nop\n";
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_ssnop(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sync(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    TODO("sync");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tlbp(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tlbp\n";
    proc.mmu.do_tlbp();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tlbr(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tlbr\n";
    proc.mmu.do_tlbr();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tlbwi(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tlbwi\n";
    proc.mmu.do_tlbwi();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tlbwr(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tlbwr\n";
    proc.mmu.do_tlbwr();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_deret(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_deret\n";
    /*
      MIPS_Instruction<word_t> *instr = mipsDecode<word_t>(proc.regs[depc]);
      instr->exec(proc);
      delete(instr);
    */
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_eret(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_eret\n";
    /*
      MIPS_Instruction<word_t> *instr = mipsDecode<word_t>(proc.regs[depc]);
      instr->exec(proc);
      delete(instr);
    */
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_add(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_add\n";
    // TODO("check for NOTWordValue here");
    proc.regs[p.args.R.rd] =sign_ext<word_t>((uint32_t)(proc.regs[p.args.R.rs] +
                                                        proc.regs[p.args.R.rt]));
    //TODO("did nont check IntegerOverflow");
    return OK;

  }

  template <typename word_t>
  PseudoStatus mips_pi_addu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_addu\n";
    // TODO("check for NotWordValue here");
    proc.regs[p.args.R.rd] = sign_ext<word_t>((uint32_t)proc.regs[p.args.R.rs] +
                                              (uint32_t)proc.regs[p.args.R.rt]);
    return OK;

  }

  template <typename word_t>
  PseudoStatus mips_pi_sub(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sub\n";
    // TODO("check for NotWordValue here");
    int64_t temp = (int64_t)(int32_t)proc.regs[p.args.R.rs] -
      (int64_t)(int32_t)proc.regs[p.args.R.rt];
    uint32_t s32 = (temp >> 32) & 0x1;
    uint32_t s31 = (temp >> 31) & 0x1;
    if(s32 == s31){
      proc.regs[p.args.R.rd] = sign_ext<word_t>((uint32_t)temp);
    }
    // else
    //TODO("SignalException(IntegerOverflow)");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_subu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_subu\n";
    // TODO("check for NotWordValue here");
    proc.regs[p.args.R.rd] =
      sign_ext<word_t>((uint32_t)(proc.regs[p.args.R.rs] - proc.regs[p.args.R.rt]));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_and(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_and\n";
    proc.regs[p.args.R.rd] =
      proc.regs[p.args.R.rs] & proc.regs[p.args.R.rt];
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_or(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_or\n";
    proc.regs[p.args.R.rd] =
      proc.regs[p.args.R.rs]|proc.regs[p.args.R.rt];
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_xor(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_xor\n";
    proc.regs[p.args.R.rd] =
      proc.regs[p.args.R.rs]^proc.regs[p.args.R.rt];
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_nor(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_nor\n";
    proc.regs[p.args.R.rd] =
      ~(proc.regs[p.args.R.rt] | proc.regs[p.args.R.rs]);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_slt(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_slt\n";
    if (((int32_t)proc.regs[p.args.R.rs]) < ((int32_t)proc.regs[p.args.R.rt]))
      proc.regs[p.args.R.rd] = 1;
    else
      proc.regs[p.args.R.rd] = 0;
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sltu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sltu\n";
    if ( proc.regs[p.args.R.rs] < proc.regs[p.args.R.rt])
      proc.regs[p.args.R.rd] = 1;
    else
      proc.regs[p.args.R.rd] = 0;
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sllv(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sllv\n";
    proc.regs[p.args.R.rd] =
      sign_ext<word_t>((uint32_t)proc.regs[p.args.R.rt]<<(proc.regs[p.args.R.rs]&0x1F));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_srlv(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_srlv\n";
    // TODO("check for NotWordValue here");
    uint8_t s=proc.regs[p.args.R.rs]&0x1f;
    proc.regs[p.args.R.rd] =
      sign_ext<word_t>((uint32_t)proc.regs[p.args.R.rt] >>s);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_srav(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_srav\n";
    // TODO("check for NotWordValue here");
    uint8_t sa = proc.regs[p.args.R.rs]&0x1f;
    proc.regs[p.args.R.rd] =
      sign_ext<word_t>((uint32_t)((int32_t)proc.regs[p.args.R.rt] >>sa));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dadd(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dadd\n";
    proc.regs[p.args.R.rd] =
      proc.regs[p.args.R.rs] + proc.regs[p.args.R.rt];
    //TODO:did not check IntegerOverflow
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_daddu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_daddu\n";
    proc.regs[p.args.R.rd] =
      proc.regs[p.args.R.rs] + proc.regs[p.args.R.rt];
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsub(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsub\n";
    proc.regs[p.args.R.rd] =
      proc.regs[p.args.R.rs] - proc.regs[p.args.R.rt];
    // TODO("did not check IntegerOverflow");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsubu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsubu\n";
    proc.regs[p.args.R.rd] =
      proc.regs[p.args.R.rs] - proc.regs[p.args.R.rt];
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsllv(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsllv\n";
    proc.regs[p.args.R.rd] =
      proc.regs[p.args.R.rt] << (proc.regs[p.args.R.rs]&0x1f);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsrlv(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsrlv\n";
    proc.regs[p.args.R.rd] =
      (uint64_t)proc.regs[p.args.R.rt] >> (proc.regs[p.args.R.rs]&0x1f);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsrav(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsrav\n";
    proc.regs[p.args.R.rd] =
      (int64_t)proc.regs[p.args.R.rt] >> (proc.regs[p.args.R.rs]&0x1f);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_mul(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_mul\n";
    // TODO("check for NotWordValue here");
    uint64_t temp = (int64_t)(int32_t)proc.regs[p.args.R.rs]*
      (int64_t)(int32_t)proc.regs[p.args.R.rt];
    proc.regs[p.args.R.rd] = sign_ext<word_t>((uint32_t)temp);
    proc.unset_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_movz(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_movz\n";
    if(proc.regs[p.args.R.rt]==0)
      proc.regs[p.args.R.rd] = proc.regs[p.args.R.rs];
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_movn(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_movn\n";
    if(proc.regs[p.args.R.rt]!=0)
      proc.regs[p.args.R.rd] = proc.regs[p.args.R.rs];
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_clz(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_clz\n";
    // TODO("check for NotWordValue here");
    uint32_t tmp = proc.regs[p.args.R1.rs];
    if(tmp){
      uint32_t counter = 0;
      while(!(tmp&(1<<31))){
        tmp <<= 1;
        ++counter;
      }
      proc.regs[p.args.R1.rd] = counter;
    }else
      proc.regs[p.args.R1.rd] = 32;
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_clo(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_clo\n";
    //TODO("check for NotWordValue here");
    uint32_t tmp = proc.regs[p.args.R1.rs];
    if(tmp){
      uint32_t counter = 0;
      while(tmp & (1<<31)){
        tmp <<= 1;
        ++counter;
      }
      proc.regs[p.args.R1.rd] = counter;
    }else
      proc.regs[p.args.R1.rd] = 32;
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dclz(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dclz\n";
    uint64_t temp = proc.regs[p.args.R1.rs];
    if(temp){
      for(int i = 0; i< 64; i++){
        uint64_t counter =0;
        if(!((temp >> 63) & 0x1)){
          temp <<=1;
          ++counter;
        }
        proc.regs[p.args.R1.rd] = temp;
      }
    }else
      proc.regs[p.args.R1.rd] = 64;
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dclo(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dclo\n";
    uint64_t temp = proc.regs[p.args.R1.rs];
    if(temp){
      for(int i = 0; i< 64; i++){
        uint64_t counter =0;
        if((temp >> 63) & 0x1){
          temp <<=1;
          ++counter;
        }
        proc.regs[p.args.R1.rd] = temp;
      }
    }else
      proc.regs[p.args.R1.rd] = 64;
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_addiu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_addiu\n";
    // TODO("check for NotWordValue here");
    proc.regs[p.args.I.rt] =
      sign_ext<word_t>((uint32_t)(proc.regs[p.args.I.rs] +
                                  sign_ext<uint32_t>(p.args.I.immed)));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_addi(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_addi\n";
    // TODO("check for NotWordValue here");
    proc.regs[p.args.I.rt] =
      sign_ext<word_t>((uint32_t)(proc.regs[p.args.I.rs] +
                                  sign_ext<uint32_t>(p.args.I.immed)));
    // TODO("did not check IntegerOverflow");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_slti(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_slti\n";
    if (proc.regs[p.args.I.rs] < sign_ext<word_t>(p.args.I.immed))
      proc.regs[p.args.I.rt] = 1;
    else
      proc.regs[p.args.I.rt] = 0;
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sltiu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sltiu\n";
    if (proc.regs[p.args.I.rs] < sign_ext<word_t>(p.args.I.immed))
      proc.regs[p.args.I.rt] = 1;
    else
      proc.regs[p.args.I.rt] = 0;
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_andi(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_andi\n";
    proc.regs[p.args.I.rt] =  proc.regs[p.args.I.rs] & (word_t)(p.args.I.immed);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_ori(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_ori\n";
    proc.regs[p.args.I.rt] = proc.regs[p.args.I.rs]|(uint32_t)(p.args.I.immed);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_xori(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_xori\n";
    proc.regs[p.args.I.rt] = proc.regs[p.args.I.rs]^(uint32_t)(p.args.I.immed);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_daddi(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_daddi\n";
    proc.regs[p.args.I.rt] = proc.regs[p.args.I.rs] + sign_ext<uint64_t>(p.args.I.immed);
    // TODO("did not check IntegerOverflow");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_daddiu(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_daddiu\n";
    proc.regs[p.args.I.rt] = proc.regs[p.args.I.rs]+
      sign_ext<uint64_t>(p.args.I.immed);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_lb(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lb\n";
    word_t addr = proc.regs[p.args.LS.base] + sign_ext<word_t>(p.args.LS.offset);
    proc.regs[p.args.LS.rt] = sign_ext<word_t>(proc.mmu.read_byte(addr));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_lbu(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lbu\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    proc.regs[p.args.LS.rt] = (word_t)proc.mmu.read_byte(addr);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_lh(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lh\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    if (addr&1) {
      proc.error() << "unpredictable half_word access to a non-aligned address" <<std::endl;
      exit(5);
    }
    else {
      proc.regs[p.args.LS.rt] = sign_ext<word_t>(proc.mmu.read_half(addr));
      return OK;
    }
  }

  template <typename word_t>
  PseudoStatus mips_pi_lhu(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lhu\n";
    word_t addr =  sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    if (addr&0x1) { //LM?
      proc.error() <<"unpredictable half_word access to a non-aligned address" <<std::endl;
      exit(5);
    }
    else{
      proc.regs[p.args.LS.rt] = (word_t)proc.mmu.read_half(addr);
      return OK;
    }
  }

  template <typename word_t>
  PseudoStatus mips_pi_ll(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    if(addr&0x3)
      {
        proc.error() <<  "unpredictable word access to a non-aligned address" <<std::endl;
        exit(5);
      }
    else {
      proc.regs[p.args.LS.rt] = sign_ext<word_t>(proc.mmu.read_word(addr));
      proc.LLbit=1;
      return OK;
    }
  }


  template <typename word_t>
  PseudoStatus mips_pi_lw(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lw\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    if(addr & 0x3)
      TODO("SignalException(AddressError)");
    proc.regs[p.args.LS.rt] = sign_ext<word_t>(proc.mmu.read_word(addr));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_lwl(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lwl\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    switch(addr&3) {
    case 3: {
      proc.regs[p.args.LS.rt] = proc.mmu.read_word(addr&~3);
      break;
    }
    case 2: {
      uint32_t b = proc.mmu.read_byte(addr&~3);
      uint32_t hw = proc.mmu.read_half(addr-1);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xff;
      proc.regs[p.args.LS.rt] = (b<<8) | (hw<<16) | temp;
      break;
    }
    case 1: {
      uint32_t hw = proc.mmu.read_half(addr&~3);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xffff;
      proc.regs[p.args.LS.rt] = (hw<<16) | temp;
      break;
    }
    case 0: {
      uint32_t b = proc.mmu.read_byte(addr);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xffffff;
      proc.regs[p.args.LS.rt] = (b <<24) | temp;
      break;
    }
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_lwr(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lwr\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    switch(addr&3) {
    case 3: {
      uint32_t b = proc.mmu.read_byte(addr);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xffffff00;
      proc.regs[p.args.LS.rt] = b | temp;
      break;
    }
    case 2: {
      uint32_t hw = proc.mmu.read_half(addr);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xffff0000;
      proc.regs[p.args.LS.rt] = hw | temp;
      break;
    }
    case 1: {
      uint32_t b = proc.mmu.read_byte(addr);
      uint32_t hw = proc.mmu.read_half(addr+1);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xff000000;
      proc.regs[p.args.LS.rt] = b | (hw<<8) | temp;
      break;
    }
    case 0: {
      proc.regs[p.args.LS.rt] = proc.mmu.read_word(addr);
      break;
    }
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_lwu(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lwu\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    if(addr & 0x3)
      TODO("SignalException(AddressError)");
    proc.regs[p.args.LS.rt] = proc.mmu.read_word(addr);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_ld(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_ld\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    if(addr & 0x7)
      TODO("SignalException(AddressError)");
    proc.regs[p.args.LS.rt] = proc.mmu.read_double(addr);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_lld(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lld\n";
    word_t addr = proc.regs[p.args.LS.base] + sign_ext<word_t>(p.args.LS.offset);
    if(addr & 0x7)
      TODO("SignalException(AddressError)");
    proc.regs[p.args.LS.rt] = proc.mmu.read_double(addr);
    TODO("LLbit = 1");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sd(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sd\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    if(addr & 0x7)
      TODO("SignalException(AddressError)");
    proc.mmu.write_double(addr,proc.regs[p.args.LS.rt]);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_scd(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_scd\n";
    word_t addr = proc.regs[p.args.LS.base] + sign_ext<word_t>(p.args.LS.offset);
    if(addr & 0x7)
      TODO("SignalException(AddressError)");
    proc.mmu.memory_write_double(addr,proc.regs[p.args.LS.rt]);
    TODO("when LLbit ==1");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_ldl(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_ldl\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    switch(addr&3) {
    case 3: {
      proc.regs[p.args.LS.rt] = proc.mmu.read_word(addr);
      break;
    }
    case 2: {
      uint32_t b = proc.mmu.read_byte(addr);
      uint32_t hw = proc.mmu.read_half(addr+1);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xff;
      proc.regs[p.args.LS.rt] = (b<<24) | (hw<<8) | temp;
      break;
    }
    case 1: {
      uint32_t hw = proc.mmu.read_half(addr);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xffff;
      proc.regs[p.args.LS.rt] = (hw<<16) | temp;
      break;
    }
    case 0: {
      uint32_t b = proc.mmu.read_byte(addr);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xffffff;
      proc.regs[p.args.LS.rt] = (b <<24) | temp;
      break;
    }
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_ldr(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_ldr\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    switch(addr&3) {
    case 3: {
      uint32_t b = proc.mmu.read_byte(addr);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xffffff00;
      proc.regs[p.args.LS.rt] = b | temp;
      break;
    }
    case 2: {
      uint32_t hw = proc.mmu.read_half(addr);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xffff0000;
      proc.regs[p.args.LS.rt] = hw | temp;
      break;
    }
    case 1: {
      uint32_t b = proc.mmu.read_byte(addr);
      uint32_t hw = proc.mmu.read_half(addr+1);
      uint32_t temp = proc.regs[p.args.LS.rt] & 0xff000000;
      proc.regs[p.args.LS.rt] = b | (hw<<8) | temp;
      break;
    }
    case 0: {
      proc.regs[p.args.LS.rt] = proc.mmu.read_word(addr);
      break;
    }
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sb(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sb\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    proc.mmu.write_byte(addr,proc.regs[p.args.LS.rt]);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sc(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sc\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    proc.mmu.write_byte(addr,proc.regs[p.args.LS.rt]);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sh(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sh\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    if (addr&1 == 1){
      proc.error() <<"unpredictable half_word access to a non-aligned address" <<std::endl;
      exit(5);
    }
    else{
      proc.mmu.write_half(addr,proc.regs[p.args.LS.rt]);
      return OK;
    }
  }

  template <typename word_t>
  PseudoStatus mips_pi_sw(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sw\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    if(addr & 0x3)
      TODO("SignalException(AddressError)");
    proc.mmu.write_word(addr,proc.regs[p.args.LS.rt]);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_swl(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_swl\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    switch(addr&3) {
    case 3: {
      proc.mmu.write_word(addr-3,proc.regs[p.args.LS.rt]);
      break;
    }
    case 2: {
      uint8_t b = proc.regs[p.args.LS.rt]>>24;
      uint16_t h = proc.regs[p.args.LS.rt]>>8;
      proc.mmu.write_byte(addr,b);
      proc.mmu.write_half(addr-2,h);
      break;
    }
    case 1: {
      uint16_t h = proc.regs[p.args.LS.rt]>>16;
      proc.mmu.write_half(addr-1,h);
      break;
    }
    case 0: {
      uint8_t b = proc.regs[p.args.LS.rt]>>24;
      proc.mmu.write_byte(addr,b);
      break;
    }
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_swr(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_swr\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    switch(addr&3) {
    case 3: {
      uint8_t b = proc.regs[p.args.LS.rt];
      proc.mmu.write_byte(addr,b);
      break;
    }
    case 2: {
      uint16_t h = proc.regs[p.args.LS.rt]>>0;
      proc.mmu.write_half(addr,h);
      break;
    }
    case 1: {
      uint8_t b = proc.regs[p.args.LS.rt];
      uint16_t h = proc.regs[p.args.LS.rt]>>8;
      proc.mmu.write_byte(addr,b);
      proc.mmu.write_half(addr+1,h);
      break;
    }
    case 0: {
      proc.mmu.write_word(addr,proc.regs[p.args.LS.rt]);
      break;
    }
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sdl(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sdl\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    switch(addr&3) {
    case 3: {
      proc.mmu.write_word(addr,proc.regs[p.args.LS.rt]);
      break;
    }
    case 2: {
      uint8_t b = proc.regs[p.args.LS.rt]>>24;
      uint16_t h = proc.regs[p.args.LS.rt]>>8;
      proc.mmu.write_byte(addr, b);
      proc.mmu.write_half(addr+1,h);
      break;
    }
    case 1: {
      uint16_t h = proc.regs[p.args.LS.rt]>>16;
      proc.mmu.write_half(addr,h);
      break;
    }
    case 0: {
      uint8_t b = proc.regs[p.args.LS.rt]>>24;
      proc.mmu.write_byte(addr,b);
      break;
    }
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sdr(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sdr\n";
    word_t addr = sign_ext<word_t>(p.args.LS.offset) + proc.regs[p.args.LS.base];
    switch(addr&3) {
    case 3: {
      uint8_t b = proc.regs[p.args.LS.rt];
      proc.mmu.write_byte(addr,b);
      break;
    }
    case 2: {
      uint16_t h = proc.regs[p.args.LS.rt]>>8;
      proc.mmu.write_half(addr,h);
      break;
    }
    case 1: {
      uint8_t b = proc.regs[p.args.LS.rt];
      uint16_t h = proc.regs[p.args.LS.rt]>>8;
      proc.mmu.write_byte(addr,b);
      proc.mmu.write_half(addr+1,h);
      break;
    }
    case 0: {
      proc.mmu.write_word(addr,proc.regs[p.args.LS.rt]);
      break;
    }
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_ldc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_ldc2\n";
    TODO("ldc2");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_lwc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lwc2\n";
    TODO("lwc2");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sdc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sdc2\n";
    TODO("sdc2");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_swc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_swc2\n";
    TODO("swc2");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_j(MIPS_Processor<word_t> &proc,
                         const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_j\n";
    proc.pc = (proc.pc & ~0xfffffff) |(p.args.J.target_addr);
    return BRANCH;
  }

  template <typename word_t>
  PseudoStatus mips_pi_jal(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_jal\n";
    proc.regs[31] = proc.pc+8;
    proc.pc = (proc.pc & ~0xfffffff) | (p.args.J.target_addr);
    return BRANCH;
  }

  template <typename word_t>
  PseudoStatus mips_pi_jalr(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_jalr\n";
    word_t tmp = proc.regs[p.args.JR1.rs];
    proc.regs[p.args.JR1.rd] = proc.pc + 8;
    proc.pc = tmp;
    return BRANCH;
  }

  template <typename word_t>
  PseudoStatus mips_pi_jr(MIPS_Processor<word_t> &proc,
                          const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_jr\n";
    int32_t tmp = proc.regs[p.args.JR2.rs];
    proc.pc = tmp;
    return BRANCH;
  }

  template <typename word_t>
  PseudoStatus mips_pi_b(MIPS_Processor<word_t> &proc,
                         const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_b\n";
    proc.pc += sign_ext<word_t>(p.args.B.branch_offset) + 4;
    return BRANCH;
  }

  template <typename word_t>
  PseudoStatus mips_pi_beq(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_beq\n";
    if (proc.regs[p.args.BR.rs]==proc.regs[p.args.BR.rt]) {
      proc.pc += sign_ext<word_t>(p.args.BR.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bne(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bne\n";
    if (proc.regs[p.args.BR.rs]!=proc.regs[p.args.BR.rt]) {
      proc.pc += sign_ext<word_t>(p.args.BR.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_beql(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_beql\n";
    if(proc.regs[p.args.BR.rs] == proc.regs[p.args.BR.rt]) {
      proc.pc += sign_ext<word_t>(p.args.BR.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bnel(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bnel\n";
    if (proc.regs[p.args.BR.rs]!=proc.regs[p.args.BR.rt]) {
      proc.pc += sign_ext<word_t>(p.args.BR.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_blez(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_blez\n";
    if(((int32_t)proc.regs[p.args.BI.rs])<=0) {
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bgtz(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bgtz\n";
    if ((int32_t)proc.regs[p.args.BI.rs]>0) {//?
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_blezl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_blezl\n";
    if(((int32_t)proc.regs[p.args.BI.rs])<=0) {
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bgtzl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bgtzl\n";
    if ((int32_t)proc.regs[p.args.BI.rs]>0) {
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bltz(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bltz\n";
    if (((int32_t)proc.regs[p.args.BI.rs])<0) {
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bgez(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bgez\n";

    if ((int32_t)proc.regs[p.args.BI.rs] >= 0) {
      proc.pc += sign_ext<word_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bal(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bal\n";
    if((int32_t)proc.regs[p.args.BI.rs] == 0) {
      proc.regs[31] = proc.pc + 8;
      proc.pc += sign_ext<word_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bltzl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bltzl\n";
    if ((int32_t)proc.regs[p.args.BI.rs] < 0) {
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bgezl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bgezl\n";
    if((int32_t)proc.regs[p.args.BI.rs] >= 0) {
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bltzal(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bltzal\n";
    if ((int32_t)proc.regs[p.args.BI.rs] < 0) {
      proc.regs[31] = proc.pc + 8;
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bgezal(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bgezal\n";
    if((int32_t)proc.regs[p.args.BI.rs] >= 0) {
      proc.regs[31] = proc.pc + 8;
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bltzall(MIPS_Processor<word_t> &proc,
                               const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bltzall\n";
    if ((int32_t)proc.regs[p.args.BI.rs] < 0) {
      proc.regs[31] = proc.pc + 8;
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bgezall(MIPS_Processor<word_t> &proc,
                               const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bgezall\n";
    if((int32_t)proc.regs[p.args.BI.rs] >= 0) {
      proc.regs[31] = proc.pc + 8;
      proc.pc += sign_ext<uint32_t>(p.args.BI.branch_offset) + 4;
      return BRANCH;
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_lui(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_lui\n";
    proc.regs[p.args.RTI.rt] = sign_ext<word_t>(p.args.RTI.immed<<16);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_cfc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_cfc2\n";
    TODO("cfc2");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_ctc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_ctc2\n";
    TODO("ctc2");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_wait(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_wait\n";
    TODO("wait");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_cache(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    TODO("cache");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sll(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sll\n";
    proc.regs[p.args.SH.rd] =
      sign_ext<word_t>((uint32_t)proc.regs[p.args.SH.rt]<<(p.args.SH.sa));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_srl(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_srl\n";
    proc.regs[p.args.SH.rd] =
      sign_ext<word_t>((uint32_t)proc.regs[p.args.SH.rt] >>(p.args.SH.sa));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sra(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sra\n";
    //TODO: check for NotWordValue here
    proc.regs[p.args.SH.rd] =
      sign_ext<word_t>((uint32_t)((int32_t)proc.regs[p.args.SH.rt] >>(p.args.SH.sa)));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsll(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsll\n";
    proc.regs[p.args.SH.rd] = proc.regs[p.args.SH.rt] << (p.args.SH.sa);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsrl(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsrl\n";
    proc.regs[p.args.SH.rd] =(uint64_t)proc.regs[p.args.SH.rt] >>(p.args.SH.sa);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_drotr(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_drotr\n";
    proc.regs[p.args.SH.rd] = rotateRight(proc.regs[p.args.SH.rt],(p.args.SH.sa));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_drotr32(MIPS_Processor<word_t> &proc,
                               const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_drotr32\n";
    proc.regs[p.args.SH.rd] = rotateRight(proc.regs[p.args.SH.rt],(p.args.SH.sa+32));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsbh(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsbh\n";
    TODO("dsbh");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsra(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsra\n";
    proc.regs[p.args.SH.rd] = (int64_t)proc.regs[p.args.SH.rt] >> (p.args.SH.sa);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsll32(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsll32\n";
    proc.regs[p.args.SH.rd] = proc.regs[p.args.SH.rt] << ((p.args.SH.sa)|0x20);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsrl32(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsrl32\n";
    proc.regs[p.args.SH.rd] = (uint64_t)proc.regs[p.args.SH.rt] >> ((p.args.SH.sa)|0x20);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dsra32(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dsra32\n";
    proc.regs[p.args.SH.rd] = (int64_t)proc.regs[p.args.SH.rt] >> ((p.args.SH.sa)|0x20);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tltu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tltu\n";
    if((uint32_t)proc.regs[p.args.TR.rs] >= (uint32_t)proc.regs[p.args.TR.rt]){
      TODO("TLTU trap");
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tge(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tge\n";
    TODO("TGE instruction (mode DT2)");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tgeu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tgeu\n";
    if(proc.regs[p.args.TR.rs] >= proc.regs[p.args.TR.rt]){
      TODO("TEGU trap");
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tlt(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tlt\n";
    TODO("TLT instruction (DT2 mode)");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_teq(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_teq\n";
    if((int32_t)proc.regs[p.args.TR.rs]==(int32_t)proc.regs[p.args.TR.rt]){
      TODO("TEQ instruction exeption");
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tne(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tne\n";
    if((int32_t)proc.regs[p.args.TR.rs] != (int32_t)proc.regs[p.args.TR.rt]){
      TODO("TNE trap");
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tgei(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tgei\n";
    if ((word_t)proc.regs[p.args.TI.rs] >= sign_ext<word_t>(p.args.TI.immed)) {
      TODO("TEGI trap");
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tgeiu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tgeiu\n";
    if(proc.regs[p.args.TI.rs] >= sign_ext<word_t>(p.args.TI.immed)){
      TODO("TEGIU trap");
    }
    else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tlti(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tlti\n";
    if ((word_t)proc.regs[p.args.TI.rs] <= sign_ext<word_t>(p.args.TI.immed)) {
      TODO("TLTI trap");
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tltiu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tltiu\n";
    if(proc.regs[p.args.TI.rs] <= sign_ext<word_t>(p.args.TI.immed)){
      TODO("TLTIU trap");
    }
    else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_teqi(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_teqi\n";
    if ((word_t)proc.regs[p.args.TI.rs] == sign_ext<word_t>(p.args.TI.immed)) {
      TODO("TEQI instruction exception");
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_tnei(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_tnei\n";
    if ((word_t)proc.regs[p.args.TI.rs] != sign_ext<word_t>(p.args.TI.immed)) {
      TODO("TNEI trap");
    } else
      return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_mult(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_mult\n";
    //TODO: check for NotWordValue here
    uint64_t prod =
      ((int64_t)(int32_t)proc.regs[p.args.MD.rs])*
      ((int64_t)(int32_t)proc.regs[p.args.MD.rt]);
    proc.hi = sign_ext<word_t>((uint32_t)(prod>>32));
    proc.lo = sign_ext<word_t>((uint32_t)prod);
    proc.set_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_multu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_multu\n";
    //TODO: check for NotWordValue here
    uint64_t prod = ((uint64_t)(uint32_t)proc.regs[p.args.MD.rs])*
      ((uint64_t)(uint32_t)proc.regs[p.args.MD.rt]);
    proc.hi = sign_ext<word_t>((uint32_t)(prod>>32));
    proc.lo = sign_ext<word_t>((uint32_t)prod);
    proc.set_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_div(MIPS_Processor<word_t> &proc,
                           const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_div\n";
    if(proc.regs[p.args.MD.rt] == 0){
      proc.error() << "this function is wrong " << std::endl;
    }
    else
      {
        //TODO: check for NotWordValue here
        uint32_t mod = (int32_t)proc.regs[p.args.MD.rs] /
          (int32_t)proc.regs[p.args.MD.rt];
        uint32_t quotient = (int32_t)proc.regs[p.args.MD.rs] %
          (int32_t)proc.regs[p.args.MD.rt];
        proc.lo = sign_ext<word_t>(mod);
        proc.hi = sign_ext<word_t>(quotient);
        proc.set_hilo();
        proc.pc +=4;
      }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_divu(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_divu\n";
    if (proc.regs[p.args.MD.rt] == 0) {
      proc.error() << "this function is wrong "<< std::endl;
      exit(1);
    } else {
      //TODO: check for NotWordValue here
      uint32_t quotient = (uint32_t)proc.regs[p.args.MD.rs] /
        (uint32_t)proc.regs[p.args.MD.rt];
      uint32_t mod = (uint32_t)proc.regs[p.args.MD.rs] %
        (uint32_t)proc.regs[p.args.MD.rt];
      proc.hi = sign_ext<word_t>(mod);
      proc.lo = sign_ext<word_t>(quotient);
      proc.set_hilo();
    }
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dmult(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dmult\n";
    TODO("dmult");
    uint64_t  prod = ((int64_t)proc.regs[p.args.MD.rs]) *
      ((int64_t)proc.regs[p.args.MD.rt]);//prod should be 128bit
    proc.hi = prod >> 32;
    proc.lo = prod;
    proc.set_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dmultu(MIPS_Processor<word_t> &proc,
                              const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dmultu\n";
    TODO("dmultu");
    uint64_t prod =
      ((uint64_t)proc.regs[p.args.MD.rs]) * ((uint64_t)proc.regs[p.args.MD.rt]);
    proc.hi = prod >> 32;
    proc.lo = prod;
    proc.set_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_ddiv(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_ddiv\n";
    if (proc.regs[p.args.MD.rt] == 0){
      proc.error() << "this function is wrong" << std::endl;
    }
    proc.lo = proc.regs[p.args.MD.rs] / proc.regs[p.args.MD.rt];
    proc.hi = proc.regs[p.args.MD.rs] % proc.regs[p.args.MD.rt];
    proc.set_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_ddivu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_ddivu\n";
    if (proc.regs[p.args.MD.rt] == 0){
      proc.error() << "this function is wrong" << std::endl;
    }
    uint64_t q = (uint64_t)proc.regs[p.args.MD.rs] |
      (uint64_t)proc.regs[p.args.MD.rt];
    uint64_t r = (uint64_t)proc.regs[p.args.MD.rs] %
      (uint64_t)proc.regs[p.args.MD.rt];
    proc.lo = (int64_t)q;
    proc.hi = (int64_t)r;
    proc.set_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_madd(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_madd\n";
    //TODO: check for NotWordValue here
    uint64_t hi = proc.hi;
    uint64_t lo = proc.lo;
    uint64_t accu = (hi << 32) | lo; //accumulate
    uint64_t temp =
      (int64_t)(int32_t)proc.regs[p.args.MD.rs] *
      (int64_t)(int32_t)proc.regs[p.args.MD.rt] +
      accu;
    proc.lo = sign_ext<word_t>((uint32_t)temp);
    proc.hi = sign_ext<word_t>((uint32_t)(temp >> 32));
    proc.set_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_maddu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_maddu\n";
    //TODO: check for NotWordValue here
    uint64_t lo = (uint32_t)proc.lo;
    uint64_t hi = (uint32_t)proc.hi;
    uint64_t accu = (hi << 32) | lo;
    uint64_t temp = (uint64_t)(uint32_t)proc.regs[p.args.MD.rs] *
      (uint64_t)(uint32_t)proc.regs[p.args.MD.rt] + accu;
    proc.lo = sign_ext<word_t>((uint32_t)temp);
    proc.hi = sign_ext<word_t>((uint32_t)(temp >> 32));
    proc.set_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_msub(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_msub\n";
    uint64_t lo = (uint32_t)proc.lo;
    uint64_t hi = (uint32_t)proc.hi;
    uint64_t accu = (hi << 32) | lo;
    uint64_t temp =
      accu -
      (int64_t)(int32_t)proc.regs[p.args.MD.rs] *
      (int64_t)(int32_t)proc.regs[p.args.MD.rt];
    proc.lo = sign_ext<word_t>((uint32_t)temp);
    proc.hi = sign_ext<word_t>((uint32_t)(temp >> 32));
    proc.set_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_msubu(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_msubu\n";
    //TODO: check for NotWordValue here
    uint64_t hi = (uint32_t)proc.hi;
    uint64_t lo = (uint32_t)proc.lo;
    uint64_t acc = (hi << 32) | lo;
    uint64_t temp =
      acc -
      (uint64_t)(uint32_t)proc.regs[p.args.MD.rs] *
      (uint64_t)(uint32_t)proc.regs[p.args.MD.rt];
    proc.lo = sign_ext<word_t>((uint32_t)temp);
    proc.hi = sign_ext<word_t>((uint32_t)(temp >> 32));
    proc.set_hilo();
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_mthi(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_mthi\n";
    proc.hi = proc.regs[p.args.MT.rs];
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_mtlo(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_mtlo\n";
    proc.lo = proc.regs[p.args.MT.rs];
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_mfhi(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_mfhi\n";
    proc.read_hilo();
    proc.regs[p.args.MF.rd] = proc.hi;
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_mflo(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_mflo\n";
    proc.read_hilo();
    proc.regs[p.args.MF.rd] = proc.lo;
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_mfc0(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_mfc0\n";
    proc.regs[p.args.MC.rt] = sign_ext<word_t>((uint32_t)proc.cp0.read_cp0(p.args.MC.rd));
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_mtc0(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_mtc0\n";
    proc.cp0.write_cp0((p.args.MC.rd),(uint32_t)proc.regs[p.args.MC.rt]);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dmfc0(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dmfc0\n";
    proc.regs[p.args.MC.rt] = (uint64_t)proc.cp0.read_cp0(p.args.MC.rd);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dmtc0(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dmtc0\n";
    proc.cp0.write_cp0((p.args.MC.rd),(uint64_t)proc.regs[p.args.MC.rt]);
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_break(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_break\n";

    //TODO("break");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_syscall(MIPS_Processor<word_t> &proc,
                               const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_syscall\n";

    TODO("syscall");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_sdbbp(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_sdbbp\n";

    TODO("sdbbp");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_movf(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_movf\n";
    TODO("movf");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bc2f(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bc2f\n";
    TODO("bc2f");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bc2t(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bc2t\n";
    TODO("bc2t");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bc2fl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bc2fl\n";
    TODO("bc2fl");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_bc2tl(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_bc2tl\n";
    TODO("bc2tl");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_mfc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_mfc2\n";
    TODO("mfc2");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_mtc2(MIPS_Processor<word_t> &proc,
                            const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_mtc2\n";
    TODO("mtc2");
    return OK;
  }

  template <typename word_t>
  PseudoStatus mips_pi_dmfc2(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dmfc2\n";
    TODO("dmfc2");
    return OK;
  }


  template <typename word_t>
  PseudoStatus mips_pi_dmtc2(MIPS_Processor<word_t> &proc,
                             const MIPS_PseudoInstruction<word_t> &p) {
    proc.debug() <<"mipspi_dmtc2\n";
    TODO("dmtc2");
    return OK;
  }

} // namespace simsoc
