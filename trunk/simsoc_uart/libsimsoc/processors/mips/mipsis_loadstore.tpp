//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//


// File included by "mipsis_loadstore.hpp"

namespace simsoc {

template <typename word_t>
MIPS_lb<word_t>::MIPS_lb(uint8_t s, uint8_t t, uint32_t i):
  base(s), rt(t), offset(i) {}


template <typename word_t>
void MIPS_lb<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = proc.regs[base] + sign_ext<word_t>(offset);
  proc.regs[rt] = sign_ext<word_t>(proc.mmu.read_byte(addr));
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_lb<word_t>::display(std::ostream& os) const{
  return os <<"lb\t" <<(MIPS_AsmId) rt <<","<<std::dec
            <<(int)offset <<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_lb(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_lb<word_t>(s,t,i);
}

/***********************************************************************************/

template <typename word_t>
MIPS_lbu<word_t>::MIPS_lbu(uint8_t s, uint8_t t, uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_lbu<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  proc.regs[rt] = (word_t)proc.mmu.read_byte(addr);
  proc.pc += 4;
}


template <typename word_t>
std::ostream& MIPS_lbu<word_t>::display(std::ostream& os) const {
  return os <<"lbu\t" <<(MIPS_AsmId) rt <<","<<std::dec <<(int)offset <<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_lbu(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_IU_FORMAT(instr,s,t,i);
  return new MIPS_lbu<word_t>(s,t,i);
}

/*lh**********************************************************************************/

template <typename word_t>
MIPS_lh<word_t>::MIPS_lh(uint8_t s,uint8_t t,uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_lh<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  if (addr&1) {
    proc.error() << "unpredictable half_word access to a non-aligned address" <<std::endl;
    exit(5);
  }
  else {
    proc.regs[rt] = sign_ext<word_t>(proc.mmu.read_half(addr));
    proc.pc += 4;
  }
}

template <typename word_t>
std::ostream& MIPS_lh<word_t>::display(std::ostream& os) const{
  return os <<"lh\t" <<(MIPS_AsmId) rt <<"," <<std::dec <<(int)offset <<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_lh(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_lh<word_t>(s,t,i);
}

/***********************************************************************************/

template <typename word_t>
MIPS_lhu<word_t>::MIPS_lhu(uint8_t s,uint8_t t,uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_lhu<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr =  sign_ext<word_t>(offset) + proc.regs[base];
  if (addr&0x1) { //LM?
    proc.error() <<"unpredictable half_word access to a non-aligned address" <<std::endl;
    exit(5);
  }
  else{
    proc.regs[rt] = (word_t)proc.mmu.read_half(addr);
    proc.pc += 4;
  }
}

template <typename word_t>
std::ostream& MIPS_lhu<word_t>::display(std::ostream& os) const{
  return os <<"lhu\t"<<(MIPS_AsmId) rt<<","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_lhu(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_IU_FORMAT(instr,s,t,i);
  return new MIPS_lhu<word_t>(s,t,i);
}

/***********************************************************************************/

template <typename word_t>
MIPS_ll<word_t>::MIPS_ll(uint8_t s, uint8_t t, uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_ll<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  if(addr&0x3)
    {
      proc.error() <<  "unpredictable word access to a non-aligned address" <<std::endl;
      exit(5);
    }
  else {
    proc.regs[rt] = sign_ext<word_t>(proc.mmu.read_word(addr));
    proc.LLbit=true;
    proc.pc += 4;
  }
}

template <typename word_t>
std::ostream& MIPS_ll<word_t>::display(std::ostream& os) const{
  return os <<"ll\t"<<(MIPS_AsmId) rt<<","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_ll( uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_ll<word_t>(s,t,i);
}
/**********************************************************************************/

template <typename word_t>
MIPS_lw<word_t>::MIPS_lw(uint8_t s,uint8_t t, uint32_t i):
    base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_lw<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  if(addr & 0x3) {
    proc.cp0.reg_cause.exc_code=Exc_AdEL;
    proc.cp0.status().bev=0;
    proc.general_exception();
  }
  proc.regs[rt] = sign_ext<word_t>(proc.mmu.read_word(addr));
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_lw<word_t>::display(std::ostream& os) const{
  return os <<"lw\t" <<(MIPS_AsmId) rt <<","<<std::dec <<(int)offset <<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_lw(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_lw<word_t>(s,t,i);
}

/***********************************************************************************/
template <typename word_t>
MIPS_lwl<word_t>::MIPS_lwl(uint8_t s,uint8_t t,uint32_t i):
   base(s),rt(t),offset(i) {}
/* big_endian */

/*void MIPS_lwl<word_t>::exec(MIPS_Processor<word_t> &proc){
  uint32_t addr = (int32_t) offset + proc.regs[base];
  switch(addr&3) {
  case 0: {
     proc.regs[rt] = proc.mmu.read_word(addr);
     break;
  }
  case 1: {
    uint32_t b = proc.mmu.read_byte(addr);
    uint32_t hw = proc.mmu.read_half(addr+1);
    uint32_t temp = proc.regs[rt] & 0xff;
    proc.regs[rt] = (b<<24) | (hw<<8) | temp;
    break;
  }
  case 2: {
    uint32_t hw = proc.mmu.read_half(addr);
    uint32_t temp = proc.regs[rt] & 0xffff;
    proc.regs[rt] = (hw<<16) | temp;
    break;

  }
  case 3: {
    uint32_t b = proc.mmu.read_byte(addr);
    uint32_t temp = proc.regs[rt] & 0xffffff;
    proc.regs[rt] = (b <<24) | temp;
    break;
  }
  }
  proc.pc += 4;
  }*/

/* little endian */
template <typename word_t>
void MIPS_lwl<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  switch(addr&3) {
  case 3: {
     proc.regs[rt] = proc.mmu.read_word(addr&~3);
     break;
  }
  case 2: {
    uint32_t b = proc.mmu.read_byte(addr&~3);
    uint32_t hw = proc.mmu.read_half(addr-1);
    uint32_t temp = proc.regs[rt] & 0xff;
    proc.regs[rt] = (b<<8) | (hw<<16) | temp;
    break;
  }
  case 1: {
    uint32_t hw = proc.mmu.read_half(addr&~3);
    uint32_t temp = proc.regs[rt] & 0xffff;
    proc.regs[rt] = (hw<<16) | temp;
    break;
  }
  case 0: {
    uint32_t b = proc.mmu.read_byte(addr);
    uint32_t temp = proc.regs[rt] & 0xffffff;
    proc.regs[rt] = (b <<24) | temp;
    break;
  }
  }
  proc.pc += 4;
}
template <typename word_t>
std::ostream& MIPS_lwl<word_t>::display(std::ostream& os) const{
  return os <<"lwl\t"<<(MIPS_AsmId) rt<<","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}


template <typename word_t>
MIPS_Instruction<word_t>* mips_lwl(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_lwl<word_t>(s,t,i);
}

/***********************************************************************************/
template <typename word_t>
MIPS_lwr<word_t>::MIPS_lwr(uint8_t s,uint8_t t,uint32_t i):
   base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_lwr<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  switch(addr&3) {
  case 3: {
    uint32_t b = proc.mmu.read_byte(addr);
    uint32_t temp = proc.regs[rt] & 0xffffff00;
    proc.regs[rt] = b | temp;
    break;
  }
  case 2: {
    uint32_t hw = proc.mmu.read_half(addr);
    uint32_t temp = proc.regs[rt] & 0xffff0000;
    proc.regs[rt] = hw | temp;
    break;
  }
  case 1: {
    uint32_t b = proc.mmu.read_byte(addr);
    uint32_t hw = proc.mmu.read_half(addr+1);
    uint32_t temp = proc.regs[rt] & 0xff000000;
    proc.regs[rt] = b | (hw<<8) | temp;
    break;
  }
  case 0: {
    proc.regs[rt] = proc.mmu.read_word(addr);
    break;
  }
  }
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_lwr<word_t>::display(std::ostream& os) const{
  return os <<"lwr\t"<<(MIPS_AsmId) rt<<","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_lwr(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_lwr<word_t>(s,t,i);
}

/**********************************************************************************/

template <typename word_t>
MIPS_pref<word_t>::MIPS_pref(uint8_t s,uint8_t t,uint32_t i):
   base(s),hint(t),offset(i) {}

template <typename word_t>
void MIPS_pref<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  //cache is not simulated
  proc.pc += 4;
}
template <typename word_t>
std::ostream& MIPS_pref<word_t>::display(std::ostream& os) const {
  return os <<"pref\t" <<(MIPS_AsmId) hint<< ","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}


template <typename word_t>
MIPS_Instruction<word_t>* mips_pref(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_pref<word_t>(s,t,i);
}

/**********************************************************************************/

template <typename word_t>
MIPS_sb<word_t>::MIPS_sb(uint8_t s,uint8_t t,uint32_t i):
   base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_sb<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  proc.mmu.write_byte(addr,proc.regs[rt]);
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_sb<word_t>::display(std::ostream& os) const {
  return os <<"sb\t" <<(MIPS_AsmId) rt <<","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_sb(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_sb<word_t>(s,t,i);
}

  /******************************************************************************/

template <typename word_t>
MIPS_sc<word_t>::MIPS_sc(uint8_t s,uint8_t t,uint32_t i):
   base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_sc<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  if(addr&0x3)
    {
      proc.error() <<  "unpredictable word access to a non-aligned address" <<std::endl;
      exit(5);
    }
  else if(proc.LLbit=true)
    proc.mmu.write_word(addr,proc.regs[rt]);

  proc.regs[rt]=proc.LLbit;
  proc.pc += 4;
}


template <typename word_t>
std::ostream& MIPS_sc<word_t>::display(std::ostream& os) const {
    return os <<"sc\t" <<(MIPS_AsmId) rt<< ","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_sc(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_sc<word_t>(s,t,i);
}

/**********************************************************************************/
template <typename word_t>
MIPS_sh<word_t>::MIPS_sh(uint8_t s,uint8_t t,uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_sh<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  if (addr&1 == 1){
    proc.error() <<"unpredictable half_word access to a non-aligned address" <<std::endl;
    exit(5);
  }
  else{
    proc.mmu.write_half(addr,proc.regs[rt]);
    proc.pc += 4;
  }
}

template <typename word_t>
std::ostream& MIPS_sh<word_t>::display(std::ostream& os) const {
  return os <<"sh\t" <<(MIPS_AsmId) rt<< ","<<std::dec
            <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_sh(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_sh<word_t>(s,t,i);
}


/***********************************************************************************/

template <typename word_t>
MIPS_sw<word_t>::MIPS_sw(uint8_t s,uint8_t t,int32_t i):
   base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_sw<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  if(addr & 0x3) {
    proc.cp0.reg_cause.exc_code=Exc_AdES;
    proc.cp0.status().bev=0;
    proc.general_exception();
  }
  proc.mmu.write_word(addr,proc.regs[rt]);
  proc.pc += 4;
}
template <typename word_t>
std::ostream& MIPS_sw<word_t>::display(std::ostream& os) const {
  return os <<"sw\t" <<(MIPS_AsmId) rt << "," <<std::dec <<offset
            <<'(' <<(MIPS_AsmId) base <<')';
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_sw(uint32_t instr){
  uint8_t s,t;
  uint32_t f;
  MIPS_I_FORMAT(instr,s,t,f);
  int32_t i = (int32_t)f;
  return new MIPS_sw<word_t>(s,t,i);
}

/**********************************************************************************/

template <typename word_t>
MIPS_swl<word_t>::MIPS_swl(uint8_t s,uint8_t t,uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_swl<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  switch(addr&3) {
  case 3: {
    proc.mmu.write_word(addr-3,proc.regs[rt]);
     break;
  }
  case 2: {
    uint8_t b = proc.regs[rt]>>24;
    uint16_t h = proc.regs[rt]>>8;
    proc.mmu.write_byte(addr,b);
    proc.mmu.write_half(addr-2,h);
    break;
  }
  case 1: {
    uint16_t h = proc.regs[rt]>>16;
    proc.mmu.write_half(addr-1,h);
    break;
  }
  case 0: {
    uint8_t b = proc.regs[rt]>>24;
    proc.mmu.write_byte(addr,b);
    break;
  }
  }
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_swl<word_t>::display(std::ostream& os) const {
  return os <<"swl\t" <<(MIPS_AsmId) rt<< ","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}


template <typename word_t>
MIPS_Instruction<word_t>* mips_swl(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_swl<word_t>(s,t,i);
}

/**********************************************************************************/
template <typename word_t>
MIPS_swr<word_t>::MIPS_swr(uint8_t s,uint8_t t,uint32_t i):
   base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_swr<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  switch(addr&3) {
  case 3: {
    uint8_t b = proc.regs[rt];
    proc.mmu.write_byte(addr,b);
     break;
  }
  case 2: {
    uint16_t h = proc.regs[rt]>>0;
    proc.mmu.write_half(addr,h);
    break;
  }
  case 1: {
    uint8_t b = proc.regs[rt];
    uint16_t h = proc.regs[rt]>>8;
    proc.mmu.write_byte(addr,b);
    proc.mmu.write_half(addr+1,h);
    break;
  }
  case 0: {
    proc.mmu.write_word(addr,proc.regs[rt]);
    break;
  }
  }
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_swr<word_t>::display(std::ostream& os) const {
  return os <<"swr\t" <<(MIPS_AsmId) rt<< ","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}


template <typename word_t>
MIPS_Instruction<word_t>* mips_swr(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_swr<word_t>(s,t,i);
}


/**********************************************************************************/
template <typename word_t>
MIPS_sync<word_t>::MIPS_sync(){}

template <typename word_t>
void MIPS_sync<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  //TODO("sync");
  // Used only for multi-processor platform
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_sync<word_t>::display(std::ostream& os) const{
  return os <<"sync\t";
}

/*
 MIPS_Instruction<word_t>* mips_sync(uint32_t instr){
   return new MIPS_sync<word_t>();
*/
/**********************************************************************************///以下是MIPS64

template <typename word_t>
MIPS_sd<word_t>::MIPS_sd(uint8_t s,uint8_t t,uint32_t i):
  base(s), rt(t), offset(i) {}

template <typename word_t>
void MIPS_sd<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  if(addr & 0x7)
    TODO("SignalException(AddressError)");
  proc.mmu.write_double(addr,proc.regs[rt]);
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_sd<word_t>::display(std::ostream& os) const {
  return os <<"sd\t" <<(MIPS_AsmId) rt << "," <<std::dec <<offset
            <<'(' <<(MIPS_AsmId) base <<')';
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_sd(uint32_t instr){
  uint8_t s,t;
  uint32_t f;
  MIPS_I_FORMAT(instr,s,t,f);
  int32_t i = (int32_t)f;
  return new MIPS_sd<word_t>(s,t,i);
}

/**********************************************************************************/
template <typename word_t>
MIPS_scd<word_t>::MIPS_scd(uint8_t s, uint8_t t, uint32_t i):
  base(s), rt(t), offset(i) {}

template <typename word_t>
std::ostream& MIPS_scd<word_t>::display(std::ostream& os) const {
  return os <<"scd\t" << (MIPS_AsmId)rt << ","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
void MIPS_scd<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  word_t addr = proc.regs[base] + sign_ext<word_t>(offset);
  if(addr & 0x7)
    TODO("SignalException(AddressError)");
  proc.mmu.memory_write_double(addr,proc.regs[rt]);
  TODO("when LLbit ==1");
  proc.pc +=4;
}
template <typename word_t>
MIPS_Instruction<word_t>* mips_scd(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_scd<word_t>(s,t,i);
}

/**********************************************************************************/

template <typename word_t>
MIPS_ld<word_t>::MIPS_ld(uint8_t s,uint8_t t,uint32_t i):
    base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_ld<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  if(addr & 0x7)
    TODO("SignalException(AddressError)");
  proc.regs[rt] = proc.mmu.read_double(addr);
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_ld<word_t>::display(std::ostream& os) const{
  return os <<"ld\t" <<(MIPS_AsmId) rt <<","<<std::dec <<(int)offset <<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_ld(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_ld<word_t>(s,t,i);
}

/***********************************************************************************/
template <typename word_t>
MIPS_lld<word_t>::MIPS_lld(uint8_t s,uint8_t t,uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_lld<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  word_t addr = proc.regs[base] + sign_ext<word_t>(offset);
  if(addr & 0x7)
    TODO("SignalException(AddressError)");
  proc.regs[rt] = proc.mmu.read_double(addr);
  proc.LLbit=1;
  proc.pc +=4;
}

template <typename word_t>
std::ostream& MIPS_lld<word_t>::display(std::ostream& os) const{
  return os <<"lld\t"<<(MIPS_AsmId) rt<<","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_lld(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_lld<word_t>(s,t,i);
}
/**********************************************************************************/
template <typename word_t>
MIPS_sdr<word_t>::MIPS_sdr(uint8_t s,uint8_t t,uint32_t i):                         //sdr,sdl **********need think over
   base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_sdr<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  switch(addr&3) {
  case 3: {
    uint8_t b = proc.regs[rt];
    proc.mmu.write_byte(addr,b);
     break;
  }
  case 2: {
    uint16_t h = proc.regs[rt]>>8;
    proc.mmu.write_half(addr,h);
    break;
  }
  case 1: {
    uint8_t b = proc.regs[rt];
    uint16_t h = proc.regs[rt]>>8;
    proc.mmu.write_byte(addr,b);
    proc.mmu.write_half(addr+1,h);
    break;
  }
  case 0: {
    proc.mmu.write_word(addr,proc.regs[rt]);
    break;
  }
  }
  proc.pc += 4;
}
template <typename word_t>
std::ostream& MIPS_sdr<word_t>::display(std::ostream& os) const {
  return os <<"sdr\t" <<(MIPS_AsmId) rt<< ","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_sdr(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_sdr<word_t>(s,t,i);
}


/**********************************************************************************/
template <typename word_t>
MIPS_sdl<word_t>::MIPS_sdl(uint8_t s,uint8_t t,uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_sdl<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  switch(addr&3) {
  case 3: {
    proc.mmu.write_word(addr,proc.regs[rt]);
     break;
  }
  case 2: {
    uint8_t b = proc.regs[rt]>>24;
    uint16_t h = proc.regs[rt]>>8;
    proc.mmu.write_byte(addr, b);
    proc.mmu.write_half(addr+1,h);
    break;
  }
  case 1: {
    uint16_t h = proc.regs[rt]>>16;
    proc.mmu.write_half(addr,h);
    break;
  }
  case 0: {
    uint8_t b = proc.regs[rt]>>24;
    proc.mmu.write_byte(addr,b);
    break;
  }
  }
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_sdl<word_t>::display(std::ostream& os) const {
  return os <<"sdl\t" <<(MIPS_AsmId) rt<< ","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}


template <typename word_t>
MIPS_Instruction<word_t>* mips_sdl(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_sdl<word_t>(s,t,i);
}

/**********************************************************************************/
template <typename word_t>
MIPS_lwu<word_t>::MIPS_lwu(uint8_t s,uint8_t t,uint32_t i):
    base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_lwu<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  if(addr & 0x3) {
    proc.cp0.reg_cause.exc_code=Exc_AdEL;
    proc.cp0.status().bev=0;
    proc.general_exception();
  }
  proc.regs[rt] = proc.mmu.read_word(addr);
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_lwu<word_t>::display(std::ostream& os) const{
  return os <<"lwu\t" <<(MIPS_AsmId) rt <<","<<std::dec <<(int)offset <<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_lwu(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_lwu<word_t>(s,t,i);
}

/***********************************************************************************/
template <typename word_t>
MIPS_ldl<word_t>::MIPS_ldl(uint8_t s,uint8_t t,uint32_t i):
   base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_ldl<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  switch(addr&3) {
  case 3: {
     proc.regs[rt] = proc.mmu.read_word(addr);
     break;
  }
  case 2: {
    uint32_t b = proc.mmu.read_byte(addr);
    uint32_t hw = proc.mmu.read_half(addr+1);
    uint32_t temp = proc.regs[rt] & 0xff;
    proc.regs[rt] = (b<<24) | (hw<<8) | temp;
    break;
  }
  case 1: {
    uint32_t hw = proc.mmu.read_half(addr);
    uint32_t temp = proc.regs[rt] & 0xffff;
    proc.regs[rt] = (hw<<16) | temp;
    break;
  }
  case 0: {
    uint32_t b = proc.mmu.read_byte(addr);
    uint32_t temp = proc.regs[rt] & 0xffffff;
    proc.regs[rt] = (b <<24) | temp;
    break;
  }
  }
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_ldl<word_t>::display(std::ostream& os) const{
  return os <<"ldl\t"<<(MIPS_AsmId) rt<<","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}


template <typename word_t>
MIPS_Instruction<word_t>* mips_ldl(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_ldl<word_t>(s,t,i);
}

/*******************************************************************/
template <typename word_t>
MIPS_ldr<word_t>::MIPS_ldr(uint8_t s,uint8_t t,uint32_t i):
   base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_ldr<word_t>::exec(MIPS_Processor<word_t> &proc){
  word_t addr = sign_ext<word_t>(offset) + proc.regs[base];
  switch(addr&3) {
  case 3: {
    uint32_t b = proc.mmu.read_byte(addr);
    uint32_t temp = proc.regs[rt] & 0xffffff00;
    proc.regs[rt] = b | temp;
    break;
  }
  case 2: {
    uint32_t hw = proc.mmu.read_half(addr);
    uint32_t temp = proc.regs[rt] & 0xffff0000;
    proc.regs[rt] = hw | temp;
    break;
  }
  case 1: {
    uint32_t b = proc.mmu.read_byte(addr);
    uint32_t hw = proc.mmu.read_half(addr+1);
    uint32_t temp = proc.regs[rt] & 0xff000000;
    proc.regs[rt] = b | (hw<<8) | temp;
    break;
  }
  case 0: {
    proc.regs[rt] = proc.mmu.read_word(addr);
    break;
  }
  }
  proc.pc += 4;
}

template <typename word_t>
std::ostream& MIPS_ldr<word_t>::display(std::ostream& os) const{
  return os <<"ldr\t"<<(MIPS_AsmId) rt<<","<<std::dec <<(int)offset<<"(" <<(MIPS_AsmId) base <<")";
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_ldr(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_ldr<word_t>(s,t,i);
}

} // namespace simsoc
