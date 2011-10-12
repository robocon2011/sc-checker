//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// File included by "mipsis_arithmetic.hpp"

namespace simsoc {

  /*================================================================*/
  template <typename word_t>
  MIPS_add<word_t>::MIPS_add(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_add<word_t>::exec(MIPS_Processor<word_t> &proc){
    // TODO("check for NOTWordValue here");
    int64_t temp = (int64_t)(int32_t)proc.regs[rs] + (int64_t)(int32_t)proc.regs[rt];
    uint32_t s32 = (temp >> 32) & 0x1;
    uint32_t s31 = (temp >> 31) & 0x1;
    if(s32 == s31){
      proc.regs[rd] = sign_ext<word_t>((uint32_t)temp);
    }
    else{
      proc.cp0.reg_cause.exc_code=Exc_Ov;
      proc.cp0.status().bev=0;
      proc.general_exception();
    }
    proc.pc += 4;

  }

  template <typename word_t>
  std::ostream& MIPS_add<word_t>::display(std::ostream& os) const{
    return os <<"add\t" <<(MIPS_AsmId) rd <<"," <<(MIPS_AsmId) rs <<","<<(MIPS_AsmId) rt;
  }

  /***********************************************************************/

  template <typename word_t>
  MIPS_addi<word_t>::MIPS_addi(uint8_t s,uint8_t t,int32_t imme):
    rs(s),rt(t),immed(imme) {}

  template <typename word_t>
  void MIPS_addi<word_t>::exec(MIPS_Processor<word_t> &proc) {
    // TODO("check for NOTWordValue here");
    int64_t temp = (int64_t)(int32_t)proc.regs[rs] + (int64_t)(int32_t)(immed);
    uint32_t s32 = (temp >> 32) & 0x1;
    uint32_t s31 = (temp >> 31) & 0x1;
    if(s32 == s31){
      proc.regs[rt] = sign_ext<word_t>((uint32_t)temp);
    }
    else{
      proc.cp0.reg_cause.exc_code=Exc_Ov;
      proc.cp0.status().bev=0;
      proc.general_exception();
    }
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_addi<word_t>::display(std::ostream& os) const {
    return os <<"addi\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rs<<"," <<(int) immed;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_addi(uint32_t instr){
    uint8_t s,t;
    uint32_t i;
    MIPS_I_FORMAT(instr,s,t,i);
    int32_t imme  = (int32_t) i;
    return new MIPS_addi<word_t>(s,t,imme);
  }
  /*************************************************************************/

  template <typename word_t>
  MIPS_addiu<word_t>::MIPS_addiu(uint8_t s,uint8_t t,int32_t i):
    rs(s),rt(t),immed(i) {}

  template <typename word_t>
  void MIPS_addiu<word_t>::exec(MIPS_Processor<word_t> &proc){
    //TODO: check for NotWordValue here
    //     proc.regs[rt] = sign_ext<word_t>((uint32_t)(proc.regs[rs]+sign_ext<uint32_t>(immed)));
    int32_t temp = (int32_t)(proc.regs[rs] + sign_ext<uint32_t>(immed));
    proc.regs[rt] = sign_ext<word_t>((uint32_t)temp);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_addiu<word_t>::display(std::ostream& os) const {
    if (rs==0)
      return os <<"li\t"<<(MIPS_AsmId) rt <<","<<std::dec  <<(int) immed;
    else
      return os <<"addiu\t" <<(MIPS_AsmId) rt <<"," <<(MIPS_AsmId) rs <<","
                <<std::dec <<(int)immed;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_addiu(uint32_t instr){
    uint8_t s,t;
    uint32_t f;
    MIPS_I_FORMAT(instr,s,t,f);
    int32_t i = (int32_t)f;
    return new MIPS_addiu<word_t>(s,t,i);
  }

  /***************************************************************************/

  template <typename word_t>
  MIPS_addu<word_t>::MIPS_addu(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_addu<word_t>::exec(MIPS_Processor<word_t> &proc){
    //TODO: check for NotWordValue here
    proc.regs[rd] = sign_ext<word_t>((uint32_t)proc.regs[rs] + (uint32_t)proc.regs[rt]);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_addu<word_t>::display(std::ostream& os) const {
    if (rt==0)
      return os <<"move\t"<<(MIPS_AsmId) rd <<"," <<(MIPS_AsmId) rs;
    else
      return os <<"addu\t"<<(MIPS_AsmId) rd <<"," <<(MIPS_AsmId) rs
                <<"," <<(MIPS_AsmId) rt;
  }

  /**************************************************************************/

  template <typename word_t>
  MIPS_clo<word_t>::MIPS_clo(uint8_t s,uint8_t d):
    rs(s),rd(d) {}

  template <typename word_t>
  void MIPS_clo<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    // TODO("check for NOTWordValue here");
    uint32_t tmp = proc.regs[rs];
    if(tmp){
      uint32_t counter = 0;
      while(tmp & (1<<31)){
        tmp <<= 1;
        ++counter;
      }
      proc.regs[rd] = counter;
    }else
      proc.regs[rd] = 32;
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_clo<word_t>::display(std::ostream& os) const{
    return os <<"clo\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs << std::endl;
  }

  /**************************************************************************/

  template <typename word_t>
  MIPS_clz<word_t>::MIPS_clz(uint8_t s,uint8_t d):
    rs(s), rd(d) {}

  template <typename word_t>
  void MIPS_clz<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    // TODO("check for NOTWordValue here");
    uint32_t tmp = proc.regs[rs];
    if(tmp){
      uint32_t counter = 0;
      while(!(tmp&(1<<31))){
        tmp <<= 1;
        ++counter;
      }
      proc.regs[rd] = counter;
    }else
      proc.regs[rd] = 32;
    proc.pc += 4;
  }


  template <typename word_t>
  std::ostream& MIPS_clz<word_t>::display(std::ostream& os) const{
    return os <<"clz\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs;
  }

  /***************************************************************************/

  template <typename word_t>
  MIPS_div<word_t>::MIPS_div(uint8_t s,uint8_t t):
    rs(s),rt(t) {}

  template <typename word_t>
  void MIPS_div<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    if(proc.regs[rt] == 0){
      proc.error() << "this function is wrong " << std::endl;
    }
    else
      {
        // TODO("check for NOTWordValue here");
        uint32_t mod = (int32_t)proc.regs[rs] / (int32_t)proc.regs[rt];
        uint32_t quotient = (int32_t)proc.regs[rs] % (int32_t)proc.regs[rt];
        proc.lo = sign_ext<word_t>(mod);
        proc.hi = sign_ext<word_t>(quotient);
        proc.set_hilo();
        proc.pc += 4;
      }
  }

  template <typename word_t>
  std::ostream& MIPS_div<word_t>::display(std::ostream& os) const{
    return os <<"div\t"<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /***************************************************************************/

  template <typename word_t>
  MIPS_divu<word_t>::MIPS_divu(uint8_t s,uint8_t t):
    rs(s),rt(t) {}

  template <typename word_t>
  void MIPS_divu<word_t>::exec(MIPS_Processor<word_t> &proc){
    if(proc.regs[rt] == 0)
      {
        proc.error() << "this function is wrong "<< std::endl;
      }
    else
      {
        // TODO("check for NOTWordValue here");
        uint32_t quotient = (uint32_t)proc.regs[rs] / (uint32_t)proc.regs[rt];
        uint32_t mod = (uint32_t)proc.regs[rs] % (uint32_t)proc.regs[rt];
        proc.hi = sign_ext<word_t>(mod);
        proc.lo = sign_ext<word_t>(quotient);
        proc.set_hilo();
        proc.pc +=4 ;
      }
  }

  template <typename word_t>
  std::ostream& MIPS_divu<word_t>::display(std::ostream& os) const{
    return os <<"divu\t"<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }


  /*************************************************************************/

  template <typename word_t>
  MIPS_madd<word_t>::MIPS_madd(uint8_t s,uint8_t t):
    rs(s),rt(t) {}

  template <typename word_t>
  void MIPS_madd<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    // TODO("check for NOTWordValue here");
    uint64_t hi = proc.hi;
    uint64_t lo = proc.lo;
    uint64_t accu = (hi << 32) | lo; //accumulate
    uint64_t temp =
      (int64_t)(int32_t)proc.regs[rs] *
      (int64_t)(int32_t)proc.regs[rt] +
      accu;
    proc.lo = sign_ext<word_t>((uint32_t)temp);
    proc.hi = sign_ext<word_t>((uint32_t)(temp >> 32));
    proc.set_hilo();
    proc.pc +=4;

  }

  template <typename word_t>
  std::ostream& MIPS_madd<word_t>::display(std::ostream& os) const {
    return os <<"madd\t" <<(MIPS_AsmId) rs<< ","<<(MIPS_AsmId) rt ;
  }

  /*maddu*****************************************************************/
  template <typename word_t>
  MIPS_maddu<word_t>::MIPS_maddu(uint8_t s,uint8_t t):
    rs(s),rt(t) {}

  template <typename word_t>
  void MIPS_maddu<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    // TODO("check for NOTWordValue here");
    uint64_t lo = (uint32_t)proc.lo;
    uint64_t hi = (uint32_t)proc.hi;
    uint64_t accu = (hi << 32) | lo;
    uint64_t temp = (uint64_t)(uint32_t)proc.regs[rs] * (uint64_t)(uint32_t)proc.regs[rt] +
      accu;
    proc.lo = sign_ext<word_t>((uint32_t)temp);
    proc.hi = sign_ext<word_t>((uint32_t)(temp >> 32));
    proc.set_hilo();
    proc.pc +=4;

  }

  template <typename word_t>
  std::ostream& MIPS_maddu<word_t>::display(std::ostream& os) const {
    return os <<"maddu\t" <<(MIPS_AsmId) rs<< ","<<(MIPS_AsmId) rt ;
  }

  /*msub************************************************************************/

  template <typename word_t>
  MIPS_msub<word_t>::MIPS_msub(uint8_t s,uint8_t t):
    rs(s),rt(t) {}

  template <typename word_t>
  void MIPS_msub<word_t>::exec(MIPS_Processor<word_t> &proc)
  {

    uint64_t lo = (uint32_t)proc.lo;
    uint64_t hi = (uint32_t)proc.hi;
    uint64_t accu = (hi << 32) | lo;
    uint64_t temp =
      accu -
      (int64_t)(int32_t)proc.regs[rs] *
      (int64_t)(int32_t)proc.regs[rt];
    proc.lo = sign_ext<word_t>((uint32_t)temp);
    proc.hi = sign_ext<word_t>((uint32_t)(temp >> 32));
    proc.set_hilo();
    proc.pc +=4;
  }

  template <typename word_t>
  std::ostream& MIPS_msub<word_t>::display(std::ostream& os) const {
    return os <<"msub\t" <<(MIPS_AsmId) rs<< ","<<(MIPS_AsmId) rt ;
  }

  /*msubu**********************************************************************/

  template <typename word_t>
  MIPS_msubu<word_t>::MIPS_msubu(uint8_t s,uint8_t t):
    rs(s),rt(t) {}

  template <typename word_t>
  void MIPS_msubu<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    // TODO("check for NOTWordValue here");
    uint64_t hi = (uint32_t)proc.hi;
    uint64_t lo = (uint32_t)proc.lo;
    uint64_t acc = (hi << 32) | lo;
    uint64_t temp =
      acc -
      (uint64_t)(uint32_t)proc.regs[rs] *
      (uint64_t)(uint32_t)proc.regs[rt];
    proc.lo = sign_ext<word_t>((uint32_t)temp);
    proc.hi = sign_ext<word_t>((uint32_t)(temp >> 32));
    proc.set_hilo();
    proc.pc +=4;
  }

  template <typename word_t>
  std::ostream& MIPS_msubu<word_t>::display(std::ostream& os) const {
    return os <<"msubu\t" <<(MIPS_AsmId) rs<< ","<<(MIPS_AsmId) rt ;
  }

  /*mul************************************************************************/

  template <typename word_t>
  MIPS_mul<word_t>::MIPS_mul(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_mul<word_t>::exec(MIPS_Processor<word_t> &proc){
    // TODO("check for NOTWordValue here");
    uint64_t temp = (int64_t)(int32_t)proc.regs[rs]*(int64_t)(int32_t)proc.regs[rt];
    proc.regs[rd] = sign_ext<word_t>((uint32_t)temp);
    proc.unset_hilo();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_mul<word_t>::display(std::ostream& os) const{
    return os <<"mul\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /*mult**********************************************************************/
  template <typename word_t>
  MIPS_mult<word_t>::MIPS_mult(uint8_t s,uint8_t t):
    rs(s),rt(t) {}
  //?lm
  template <typename word_t>
  void MIPS_mult<word_t>::exec(MIPS_Processor<word_t> &proc){
    // TODO("check for NOTWordValue here");
    uint64_t prod =
      ((int64_t)(int32_t)proc.regs[rs])*
      ((int64_t)(int32_t)proc.regs[rt]);
    proc.hi = sign_ext<word_t>((uint32_t)(prod>>32));
    proc.lo = sign_ext<word_t>((uint32_t)prod);
    proc.set_hilo();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_mult<word_t>::display(std::ostream& os) const{
    return os <<"mult\t"<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /*multu*********************************************************************/

  template <typename word_t>
  MIPS_multu<word_t>::MIPS_multu(uint8_t s,uint8_t t):
    rs(s),rt(t) {}

  template <typename word_t>
  void MIPS_multu<word_t>::exec(MIPS_Processor<word_t> &proc){
    // TODO("check for NOTWordValue here");
    uint64_t prod = ((uint64_t)(uint32_t)proc.regs[rs])*((uint64_t)(uint32_t)proc.regs[rt]);
    proc.hi = sign_ext<word_t>((uint32_t)(prod>>32));
    proc.lo = sign_ext<word_t>((uint32_t)prod);
    proc.set_hilo();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_multu<word_t>::display(std::ostream& os) const{
    return os <<"multu\t"<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /**************************************************************************/

  template <typename word_t>
  MIPS_slt<word_t>::MIPS_slt(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  std::ostream& MIPS_slt<word_t>::display(std::ostream& os) const{
    return os <<"slt\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /*slti*****************************************************************************/

  template <typename word_t>
  MIPS_slti<word_t>::MIPS_slti(uint8_t s,uint8_t t,uint32_t i):
    rs(s),rt(t),immed(i) {}

  template <typename word_t>
  std::ostream& MIPS_slti<word_t>::display(std::ostream& os) const {
    return os <<"slti\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rs<<"," <<std::dec <<(int) immed;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_slti(uint32_t instr){
    uint8_t s,t;
    uint32_t i;
    MIPS_I_FORMAT(instr,s,t,i);
    return new MIPS_slti<word_t>(s,t,i);
  }

  /*sltiu***************************************************************************/

  template <typename word_t>
  MIPS_sltiu<word_t>::MIPS_sltiu(uint8_t s,uint8_t t,uint32_t i):
    rs(s),rt(t),immed(i) {}

  template <typename word_t>
  void MIPS_sltiu<word_t>::exec(MIPS_Processor<word_t> &proc){
    if ( proc.regs[rs] < sign_ext<word_t>(immed))
      proc.regs[rt] = 1;
    else
      proc.regs[rt] = 0;
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_sltiu<word_t>::display(std::ostream& os) const {
    return os <<"sltiu\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rs<<"," <<std::dec  <<(int) immed;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_sltiu(uint32_t instr){
    uint8_t s,t;
    uint32_t i;
    MIPS_I_FORMAT(instr,s,t,i);
    return new MIPS_sltiu<word_t>(s,t,i);
  }

  /**sltu********************************************************************************/

  template <typename word_t>
  MIPS_sltu<word_t>::MIPS_sltu(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_sltu<word_t>::exec(MIPS_Processor<word_t> &proc){
    if ( proc.regs[rs] < proc.regs[rt])
      proc.regs[rd] = 1;
    else
      proc.regs[rd] = 0;
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_sltu<word_t>::display(std::ostream& os) const{
    return os <<"sltu\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /*sub**********************************************************************************/
  template <typename word_t>
  MIPS_sub<word_t>::MIPS_sub(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_sub<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    // TODO("check for NOTWordValue here");
    int64_t temp =
      (int64_t)(int32_t)proc.regs[rs] -
      (int64_t)(int32_t)proc.regs[rt];
    uint32_t s32 = (temp >> 32) & 0x1;
    uint32_t s31 = (temp >> 31) & 0x1;
    if(s32 == s31){
      proc.regs[rd] = sign_ext<word_t>((uint32_t)temp);
    }
    else{
      proc.cp0.reg_cause.exc_code=Exc_Ov;
      proc.cp0.status().bev=0;
      proc.general_exception();
    }
   proc.pc +=4;
  }

  template <typename word_t>
  std::ostream& MIPS_sub<word_t>::display(std::ostream& os) const{
    return os <<"sub\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /*subu**********************************************************************************/
  template <typename word_t>
  MIPS_subu<word_t>::MIPS_subu(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_subu<word_t>::exec(MIPS_Processor<word_t> &proc){
    // TODO("check for NOTWordValue here");
    proc.regs[rd] = sign_ext<word_t>((uint32_t)(proc.regs[rs] - proc.regs[rt]));
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_subu<word_t>::display(std::ostream& os) const{
    if (rs==0)
      return os <<"negu\t"<<(MIPS_AsmId) rd <<","<<(MIPS_AsmId) rt;
    return os <<"subu\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /***and********************************************************************************/

  template <typename word_t>
  MIPS_and<word_t>::MIPS_and(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_and<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] =  proc.regs[rs] & proc.regs[rt];
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_and<word_t>::display(std::ostream& os) const{
    return os <<"and\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /******andi*****************************************************************************/

  template <typename word_t>
  MIPS_andi<word_t>::MIPS_andi(uint8_t s,uint8_t t,uint32_t i):
    rs(s),rt(t),immed(i) {}

  template <typename word_t>
  void MIPS_andi<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rt] =  proc.regs[rs] & (word_t)immed;
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_andi<word_t>::display(std::ostream& os) const {
    return os <<"andi\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rs<<"," <<(int) immed;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_andi(uint32_t instr){
    uint8_t s,t;
    uint32_t i;
    MIPS_IU_FORMAT(instr,s,t,i);
    return new MIPS_andi<word_t>(s,t,i);
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_lui<word_t>::MIPS_lui(uint8_t t,uint32_t i):
    rt(t),immed(i) {}

  template <typename word_t>
  void MIPS_lui<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rt] = sign_ext<word_t>(immed<<16);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_lui<word_t>::display(std::ostream& os) const {
    return os <<"lui\t" <<(MIPS_AsmId) rt<<"," <<(int) immed;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_lui(uint32_t instr){
    uint8_t s,t;
    uint32_t i;
    MIPS_I_FORMAT(instr,s,t,i);
    return new MIPS_lui<word_t>(t,i);
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_nor<word_t>::MIPS_nor(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_nor<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = ~(proc.regs[rt] | proc.regs[rs]);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_nor<word_t>::display(std::ostream& os) const{
    return os <<"nor\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /**or*********************************************************************************/

  template <typename word_t>
  MIPS_or<word_t>::MIPS_or(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_or<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = proc.regs[rs]|proc.regs[rt];
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_or<word_t>::display(std::ostream& os) const{
    return os <<"or\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_ori<word_t>::MIPS_ori(uint8_t s,uint8_t t,uint32_t i):
    rs(s),rt(t),immed(i) {}

  template <typename word_t>
  void MIPS_ori<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rt] = proc.regs[rs]|(uint32_t)immed;
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_ori<word_t>::display(std::ostream& os) const {
    return os <<"ori\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rs<<"," <<(int) immed;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_ori(uint32_t instr){
    uint8_t s,t;
    uint32_t i;
    MIPS_IU_FORMAT(instr,s,t,i);
    return new MIPS_ori<word_t>(s,t,i);
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_xor<word_t>::MIPS_xor(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_xor<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = proc.regs[rs]^proc.regs[rt];
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_xor<word_t>::display(std::ostream& os) const{
    return os <<"xor\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_xori<word_t>::MIPS_xori(uint8_t s,uint8_t t,uint32_t i):
    rs(s),rt(t),immed(i) {}

  template <typename word_t>
  void MIPS_xori<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rt] = proc.regs[rs]^(uint32_t)immed;
    proc.pc += 4;
  }


  template <typename word_t>
  std::ostream& MIPS_xori<word_t>::display(std::ostream& os) const {
    return os <<"xori\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rs<<"," <<(int) immed;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_xori(uint32_t instr){
    uint8_t t,s;
    uint32_t i;
    MIPS_IU_FORMAT(instr,s,t,i);
    return new MIPS_xori<word_t>(s,t,i);
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_mflo<word_t>::MIPS_mflo(uint8_t d):
    rd(d) {}

  template <typename word_t>
  void MIPS_mflo<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.read_hilo();
    proc.regs[rd] = proc.lo;
    proc.pc += 4;
  }
  template <typename word_t>
  std::ostream& MIPS_mflo<word_t>::display(std::ostream& os) const{
    return os <<"mflo\t"<<(MIPS_AsmId) rd;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_mfhi<word_t>::MIPS_mfhi(uint8_t d):
    rd(d) {}

  template <typename word_t>
  void MIPS_mfhi<word_t>::exec(MIPS_Processor<word_t> &proc) {
    proc.read_hilo();
    proc.regs[rd] = proc.hi;
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_mfhi<word_t>::display(std::ostream& os) const{
    return os <<"mfhi\t"<<(MIPS_AsmId) rd;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_movf<word_t>::MIPS_movf(uint8_t s,uint8_t c,uint8_t d):
    rs(s),cc(c),rd(d) {}

  template <typename word_t>
  void MIPS_movf<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    TODO("movf");
  }

  template <typename word_t>
  std::ostream& MIPS_movf<word_t>::display(std::ostream& os) const {
    return os <<"movf\t" <<(MIPS_AsmId) rd<<"," <<(MIPS_AsmId) rs<<"," <<(MIPS_AsmId) cc;
  }

  /**movz********************************************************************************/

  template <typename word_t>
  MIPS_movz<word_t>::MIPS_movz(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_movz<word_t>::exec(MIPS_Processor<word_t> &proc){
    if(proc.regs[rt]==0)
      proc.regs[rd] = proc.regs[rs];
    proc.pc +=4;
  }

  template <typename word_t>
  std::ostream& MIPS_movz<word_t>::display(std::ostream& os) const {
    return os <<"movz\t" <<(MIPS_AsmId) rd<<"," <<(MIPS_AsmId) rs<<"," <<(MIPS_AsmId) rt;
  }

  /**movn********************************************************************************/

  template <typename word_t>
  MIPS_movn<word_t>::MIPS_movn(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_movn<word_t>::exec(MIPS_Processor<word_t> &proc){
    if(proc.regs[rt]!=0)
      proc.regs[rd] = proc.regs[rs];
    proc.pc +=4;
  }

  template <typename word_t>
  std::ostream& MIPS_movn<word_t>::display(std::ostream& os) const {
    return os <<"movn\t" <<(MIPS_AsmId) rd<<"," <<(MIPS_AsmId) rs<<"," <<(MIPS_AsmId) rt;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_mthi<word_t>::MIPS_mthi(uint8_t s):
    rs(s) {}

  template <typename word_t>
  void MIPS_mthi<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.hi = proc.regs[rs];
    proc.pc +=4;
  }

  template <typename word_t>
  std::ostream& MIPS_mthi<word_t>::display(std::ostream& os) const{
    return os <<"mthi\t"<<(MIPS_AsmId) rs;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_mtlo<word_t>::MIPS_mtlo(uint8_t s):
    rs(s) {}

  template <typename word_t>
  void MIPS_mtlo<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.lo = proc.regs[rs];
    proc.pc +=4;
  }

  template <typename word_t>
  std::ostream& MIPS_mtlo<word_t>::display(std::ostream& os) const{
    return os <<"mtlo\t"<<(MIPS_AsmId) rs;
  }

  /**mips_sll command***********************************************************************/

  template <typename word_t>
  MIPS_sll<word_t>::MIPS_sll(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a) {}

  template <typename word_t>
  void MIPS_sll<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] =  sign_ext<word_t>((uint32_t)proc.regs[rt]<<sa);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_sll<word_t>::display(std::ostream& os) const{
    return os <<"sll\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rt<<","<<(int) sa;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_sll(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_sll<word_t>(t,d,a);
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_sllv<word_t>::MIPS_sllv(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_sllv<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] =  sign_ext<word_t>((uint32_t)proc.regs[rt]<<(proc.regs[rs]&0x1F));
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_sllv<word_t>::display(std::ostream& os) const{
    return os <<"sllv\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rt<<","<<(MIPS_AsmId) rs;
  }

  /**sra********************************************************************************/

  template <typename word_t>
  MIPS_sra<word_t>::MIPS_sra(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a) {}

  template <typename word_t>
  void MIPS_sra<word_t>::exec(MIPS_Processor<word_t> &proc){
    // TODO("check for NOTWordValue here");
    proc.regs[rd] =sign_ext<word_t>((uint32_t)((int32_t)proc.regs[rt] >>sa));
    proc.pc += 4;
  }
  template <typename word_t>
  std::ostream& MIPS_sra<word_t>::display(std::ostream& os) const{
    return os <<"sra\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rt<<","<<(int) sa;
  }

  /****srav*******************************************************************************/

  template <typename word_t>
  MIPS_srav<word_t>::MIPS_srav(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_srav<word_t>::exec(MIPS_Processor<word_t> &proc){
    // TODO("check for NOTWordValue here");
    uint8_t sa = proc.regs[rs]&0x1f;
    proc.regs[rd] = sign_ext<word_t>((uint32_t)((int32_t)proc.regs[rt] >>sa));
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_srav<word_t>::display(std::ostream& os) const{
    return os <<"srav\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rt<<","<<(MIPS_AsmId) rs;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_srl<word_t>::MIPS_srl(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a) {}

  template <typename word_t>
  void MIPS_srl<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] =sign_ext<word_t>((uint32_t)proc.regs[rt] >>sa);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_srl<word_t>::display(std::ostream& os) const{
    return os <<"srl\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rt<<","<<(int) sa;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_srlv<word_t>::MIPS_srlv(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_srlv<word_t>::exec(MIPS_Processor<word_t> &proc){
    // TODO("check for NOTWordValue here");
    uint8_t s=proc.regs[rs]&0x1f;
    proc.regs[rd] =sign_ext<word_t>((uint32_t)proc.regs[rt] >>s);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_srlv<word_t>::display(std::ostream& os) const{
    return os <<"srlv\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rt<<","<<(MIPS_AsmId) rs;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_srlv(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_srlv<word_t>(s,t,d);
  }

  /*******************************************************************************************///mips64 commands

  template <typename word_t>
  MIPS_dsll<word_t>::MIPS_dsll(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a){}

  template <typename word_t>
  void MIPS_dsll<word_t>::exec(MIPS_Processor<word_t> &proc) {
    proc.regs[rd] = proc.regs[rt] << sa;
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dsll<word_t>::display(std::ostream& os) const {
    return os << "dsll\t" << (MIPS_AsmId)rt << "," << (MIPS_AsmId)rd << "," << (int)sa;
  }

  //****************************//dsllv command

  template <typename word_t>
  MIPS_dsllv<word_t>::MIPS_dsllv(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d){}

  template <typename word_t>
  void MIPS_dsllv<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = proc.regs[rt] << (proc.regs[rs]&0x1f);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dsllv<word_t>::display(std::ostream& os) const{
    return os << "dsllv\t" << (MIPS_AsmId)rs << "," << (MIPS_AsmId)rt << "," << (MIPS_AsmId)rd;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dsllv(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dsllv<word_t>(s,t,d);
  }

  //*************************//dsrlv command
  template <typename word_t>
  MIPS_dsrlv<word_t>::MIPS_dsrlv(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d){}

  template <typename word_t>
  void MIPS_dsrlv<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = (uint64_t)proc.regs[rt] >> (proc.regs[rs]&0x1f);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dsrlv<word_t>::display(std::ostream& os) const{
    return os << "dsrlv\t" << (MIPS_AsmId)rs << "," << (MIPS_AsmId)rt << "," << (MIPS_AsmId)rd;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dsrlv(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dsrlv<word_t>(s,t,d);
  }

  //*************************//dsrav command
  template <typename word_t>
  MIPS_dsrav<word_t>::MIPS_dsrav(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d){}

  template <typename word_t>
  void MIPS_dsrav<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = (int64_t)proc.regs[rt] >> (proc.regs[rs]&0x1f);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dsrav<word_t>::display(std::ostream& os) const{
    return os << "dsrlv\t" << (MIPS_AsmId)rs << "," << (MIPS_AsmId)rt << "," << (MIPS_AsmId)rd;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dsrav(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dsrav<word_t>(s,t,d);
  }
  //*************************//dmult command

  template <typename word_t>
  MIPS_dmult<word_t>::MIPS_dmult(uint8_t s,uint8_t t):
    rs(s),rt(t){}

  template <typename word_t>
  void MIPS_dmult<word_t>::exec(MIPS_Processor<word_t> &proc){
    TODO("dmult");
    uint64_t  prod = ((int64_t)proc.regs[rs]) * ((int64_t)proc.regs[rt]);//prod should be 128bit
    proc.hi = prod >> 32;
    proc.lo = prod;
    proc.set_hilo();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dmult<word_t>::display(std::ostream& os) const{
    return os << "dmult\t" << (MIPS_AsmId)rs << "," << (MIPS_AsmId)rt;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dmult(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dmult<word_t>(s,t);
  }

  //*************************//dmult command
  template <typename word_t>
  MIPS_dmultu<word_t>::MIPS_dmultu(uint8_t s,uint8_t t):
    rs(s),rt(t){}

  template <typename word_t>
  void MIPS_dmultu<word_t>::exec(MIPS_Processor<word_t> &proc) {
    TODO("dmultu");
    uint64_t prod =
      ((uint64_t)proc.regs[rs]) * ((uint64_t)proc.regs[rt]);
    proc.hi = prod >> 32;
    proc.lo = prod;
    proc.set_hilo();
    proc.pc +=4;
  }

  template <typename word_t>
  std::ostream& MIPS_dmultu<word_t>::display(std::ostream& os) const{
    return os << "dmultu\t" << (MIPS_AsmId)rs << "," << (MIPS_AsmId)rt;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dmultu(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dmultu<word_t>(s,t);
  }

  //*************************//ddiv command
  template <typename word_t>
  MIPS_ddiv<word_t>::MIPS_ddiv(uint8_t s,uint8_t t):
    rs(s),rt(t){}

  template <typename word_t>
  void MIPS_ddiv<word_t>::exec(MIPS_Processor<word_t> &proc){
    if (proc.regs[rt] == 0){
      proc.error() << "this function is wrong" << std::endl;
    }
    proc.lo = proc.regs[rs] / proc.regs[rt];
    proc.hi = proc.regs[rs] % proc.regs[rt];
    proc.set_hilo();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_ddiv<word_t>::display(std::ostream& os) const{
    return os << "ddiv\t" << (MIPS_AsmId)rs << "," << (MIPS_AsmId)rt;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_ddiv(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_ddiv<word_t>(s,t);
  }
  //*************************//ddivu command
  template <typename word_t>
  MIPS_ddivu<word_t>::MIPS_ddivu(uint8_t s,uint8_t t):
    rs(s),rt(t) {}

  template <typename word_t>
  void MIPS_ddivu<word_t>::exec(MIPS_Processor<word_t> &proc){
    if (proc.regs[rt] == 0){
      proc.error() << "this function is wrong" << std::endl;
    }
    uint64_t q = (uint64_t)proc.regs[rs] | (uint64_t)proc.regs[rt];
    uint64_t r = (uint64_t)proc.regs[rs] % (uint64_t)proc.regs[rt];
    proc.lo = (int64_t)q;
    proc.hi = (int64_t)r;
    proc.set_hilo();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_ddivu<word_t>::display(std::ostream& os) const{
    return os << "ddiv\t" << (MIPS_AsmId)rs << "," << (MIPS_AsmId)rt;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_ddivu(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_ddivu<word_t>(s,t);
  }

  //*************************//dadd command

  template <typename word_t>
  MIPS_dadd<word_t>::MIPS_dadd(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_dadd<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = proc.regs[rs] + proc.regs[rt];
//     proc.general_exception();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dadd<word_t>::display(std::ostream& os) const {
    return os <<"dadd\t" <<(MIPS_AsmId) rs<< ","<<(MIPS_AsmId) rt << "," << (MIPS_AsmId) rd;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dadd(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dadd<word_t>(s,t,d);
  }

  //*************************//daddu command

  template <typename word_t>
  MIPS_daddu<word_t>::MIPS_daddu(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_daddu<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd]  = proc.regs[rs] + proc.regs[rt];
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_daddu<word_t>::display(std::ostream& os) const {
    if (rt==0)
      return os <<"move\t"<<(MIPS_AsmId) rd <<"," <<(MIPS_AsmId) rs;
    else
      return os <<"daddu\t"<<(MIPS_AsmId) rd <<"," <<(MIPS_AsmId) rs
                <<"," <<(MIPS_AsmId) rt;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_daddu(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_daddu<word_t>(s,t,d);
  }
  //*************************//daddu command
  template <typename word_t>
  MIPS_dsub<word_t>::MIPS_dsub(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_dsub<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = proc.regs[rs] - proc.regs[rt];
    proc.general_exception();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dsub<word_t>::display(std::ostream& os) const {
    return os <<"dsub\t" <<(MIPS_AsmId) rs<< ","<<(MIPS_AsmId) rt << "," << (MIPS_AsmId) rd;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dsub(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dsub<word_t>(s,t,d);
  }
  //*************************//daddu command

  template <typename word_t>
  MIPS_dsubu<word_t>::MIPS_dsubu(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_dsubu<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = proc.regs[rs] - proc.regs[rt];
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dsubu<word_t>::display(std::ostream& os) const{
    if (rs==0)
      return os <<"negu\t"<<(MIPS_AsmId) rd <<","<<(MIPS_AsmId) rt;
    return os <<"dsubu\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dsubu(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dsubu<word_t>(s,t,d);
  }

  //*************************//dsrl command

  template <typename word_t>
  MIPS_dsrl<word_t>::MIPS_dsrl(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a) {}

  template <typename word_t>
  void MIPS_dsrl<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] =(uint64_t)proc.regs[rt] >>sa;
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dsrl<word_t>::display(std::ostream& os) const{
    return os <<"dsrl\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rt<<","<<(int) sa;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dsrl(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dsrl<word_t>(t,d,a);
  }

  //*************************//drotr command

  template <typename word_t>
  MIPS_drotr<word_t>::MIPS_drotr(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a) {}


  template <typename word_t>
  void MIPS_drotr<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = rotateRight(proc.regs[rt],sa);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_drotr<word_t>::display(std::ostream& os) const {
    return os <<"drotr\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rd << "," << (int) sa;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_drotr(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_drotr<word_t>(s,t,d);
  }
  //*************************//drotr32 command
  template <typename word_t>
  MIPS_drotr32<word_t>::MIPS_drotr32(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a) {}

  template <typename word_t>
  void MIPS_drotr32<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = rotateRight(proc.regs[rt],sa+32);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_drotr32<word_t>::display(std::ostream& os) const {
    return os <<"drotr32\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rd << "," << (int) sa;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_drotr32(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_drotr32<word_t>(s,t,d);
  }

  //*************************//dsra command
  template <typename word_t>
  MIPS_dsra<word_t>::MIPS_dsra(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a){}

  template <typename word_t>
  void MIPS_dsra<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = (int64_t)proc.regs[rt] >> sa;
    proc.pc += 4;
  }
  template <typename word_t>
  std::ostream& MIPS_dsra<word_t>::display(std::ostream& os) const {
    return os <<"dsra\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rd << "," << (int) sa;

  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dsra(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dsra<word_t>(s,t,d);
  }
  //*************************//dsll32 command

  template <typename word_t>
  MIPS_dsll32<word_t>::MIPS_dsll32(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a){}

  template <typename word_t>
  void MIPS_dsll32<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = proc.regs[rt] << (sa|0x20);
    proc.pc += 4;
  }
  template <typename word_t>
  std::ostream& MIPS_dsll32<word_t>::display(std::ostream& os) const {
    return os <<"dsll32\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rd << "," << (int) sa;

  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dsll32(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dsll32<word_t>(s,t,d);
  }

  //*************************//dsrl32 command
  template <typename word_t>
  MIPS_dsrl32<word_t>::MIPS_dsrl32(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a){}

  template <typename word_t>
  void MIPS_dsrl32<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = (uint64_t)proc.regs[rt] >> (sa|0x20);
    proc.pc += 4;
  }
  template <typename word_t>
  std::ostream& MIPS_dsrl32<word_t>::display(std::ostream& os) const {
    return os <<"dsrl32\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rd << "," << (int) sa;

  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dsrl32(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dsrl32<word_t>(s,t,d);
  }
  //*************************//dsra32 command
  template <typename word_t>
  MIPS_dsra32<word_t>::MIPS_dsra32(uint8_t t,uint8_t d,uint8_t a):
    rt(t),rd(d),sa(a){}

  template <typename word_t>
  void MIPS_dsra32<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rd] = (int64_t)proc.regs[rt] >> (sa|0x20);
    proc.pc += 4;
  }
  template <typename word_t>
  std::ostream& MIPS_dsra32<word_t>::display(std::ostream& os) const {
    return os <<"dsra32\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rd << "," << (int) sa;

  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dsra32(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_dsra32<word_t>(s,t,d);
  }
  //*************************//daddi command
  template <typename word_t>
  MIPS_daddi<word_t>::MIPS_daddi(uint8_t s,uint8_t t,uint64_t i):
    rs(s),rt(t),immed(i) {}

  template <typename word_t>
  void MIPS_daddi<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rt] = proc.regs[rs] + sign_ext<uint64_t>(immed);
//     proc.general_exception();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_daddi<word_t>::display(std::ostream& os) const {
    return os <<"daddi\t" <<(MIPS_AsmId) rt<< ","<<(MIPS_AsmId) rs<<"," <<(int) immed;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_daddi(uint32_t instr){
    uint8_t s,t;
    uint32_t i;
    MIPS_I_FORMAT(instr,s,t,i);
    return new MIPS_daddi<word_t>(s,t,i);
  }

  /**************************///daddiu command
  template <typename word_t>
  MIPS_daddiu<word_t>::MIPS_daddiu(uint8_t s,uint8_t t,uint64_t i):
    rs(s),rt(t),immed(i) {}

  template <typename word_t>
  void MIPS_daddiu<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[rt] = proc.regs[rs]+sign_ext<uint64_t>(immed);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_daddiu<word_t>::display(std::ostream& os) const {
    if (rs==0)
      return os <<"li\t"<<(MIPS_AsmId) rt <<","<<std::dec  <<(int) immed;
    else
      return os <<"daddiu\t" <<(MIPS_AsmId) rt <<"," <<(MIPS_AsmId) rs <<","
                <<std::dec <<immed;
  }
  template <typename word_t>
  MIPS_Instruction<word_t>* mips_daddiu(uint32_t instr){
    uint8_t s,t;
    uint32_t f;
    MIPS_I_FORMAT(instr,s,t,f);
    int32_t i = (int32_t)f;
    return new MIPS_daddiu<word_t>(s,t,i);
  }

  /********************************************************************///dclo command
  template <typename word_t>
  MIPS_dclo<word_t>::MIPS_dclo(uint8_t s,uint8_t t,uint8_t d):
    rs(s),rt(t),rd(d) {}

  template <typename word_t>
  void MIPS_dclo<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    uint64_t temp = proc.regs[rs];
    if(temp){
      for(int i = 0; i< 64; i++){
        uint64_t counter =0;
        if((temp >> 63) & 0x1){
          temp <<=1;
          ++counter;
        }
        proc.regs[rd] = temp;
      }
    }else
      proc.regs[rd] = 64;
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dclo<word_t>::display(std::ostream& os) const{
    return os <<"dclo\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /****************************************///dclz command

  template <typename word_t>
  MIPS_dclz<word_t>::MIPS_dclz(uint8_t s,uint8_t d):
    rs(s),rd(d) {}

  template <typename word_t>
  void MIPS_dclz<word_t>::exec(MIPS_Processor<word_t> &proc){
    uint64_t temp = proc.regs[rs];
    if(temp){
      for(int i = 0; i< 64; i++){
        uint64_t counter =0;
        if(!((temp >> 63) & 0x1)){
          temp <<=1;
          ++counter;
        }
        proc.regs[rd] = temp;
      }
    }else
      proc.regs[rd] = 64;
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dclz<word_t>::display(std::ostream& os) const{
    return os <<"dclz\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dclz(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_clz<word_t>(s,d);
  }

  /*============================================================================*/
  //declare the functions

#if 0 // This code seems useless, because theses functions are defined above
  template <typename word_t>
  MIPS_Instruction<word_t>* mips_dclz(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_addi(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_addiu(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_slti(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_sltiu(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_andi(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_lui(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_ori(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_xori(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_sll(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_srlv(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_daddi(uint32_t instr);

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_daddiu(uint32_t instr);
#endif //0

} // namespace simsoc
