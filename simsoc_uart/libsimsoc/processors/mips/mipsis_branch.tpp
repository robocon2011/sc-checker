//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// File included by "mipsis_branch.hpp"

namespace simsoc{

  /*==============================================================*/
  template <typename word_t>
  MIPS_b<word_t>::MIPS_b(int32_t offset):
    branch_offset(offset) {}

  template <typename word_t>
  void MIPS_b<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.pc += 4;
    MIPS_Instruction<word_t> *instr = mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
    proc.debug() << "the instruction in delay slot will be execute:\n"
                 <<*instr <<std::endl;
    instr->exec(proc);
    delete(instr);
    proc.pc = proc.pc + sign_ext<word_t>(branch_offset) -4;
    proc.debug() << "branch to \n" << proc.pc << std::endl;
  }

  template <typename word_t>
  std::ostream& MIPS_b<word_t>::display(std::ostream& os) const {
    return os <<"b\t"  <<(int) branch_offset;
  }

  /**************************************************************************/
  template <typename word_t>
  MIPS_bal<word_t>::MIPS_bal(uint8_t s,int32_t offset):
    rs(s),branch_offset(offset) {}

  template <typename word_t>
  void MIPS_bal<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.pc += 4;
    if((int32_t)proc.regs[rs] == 0)
      {
        MIPS_Instruction<word_t>* instr =
          mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
        proc.debug() << "the instruction in the delay slot will be executed:\n"
                     << *instr <<std::endl;
        instr->exec(proc);
        delete(instr);
        proc.regs[31] = proc.pc + 4;
        proc.pc = proc.pc + sign_ext<word_t>(branch_offset) -4;
        proc.debug() << "branch to \n" << proc.pc << std::endl;
      }
  }
  template <typename word_t>
  std::ostream& MIPS_bal<word_t>::display(std::ostream& os) const {
    return os <<"bal\t"  <<(int) branch_offset;
  }

  /**************************************************************************/

  template <typename word_t>
  MIPS_beq<word_t>::MIPS_beq(uint8_t s,uint8_t t,int32_t offset):
    rs(s),rt(t),branch_offset(offset) {}

  template <typename word_t>
  void MIPS_beq<word_t>::exec(MIPS_Processor<word_t> &proc) {
    proc.pc += 4;
    if (proc.regs[rs]==proc.regs[rt]) {
      MIPS_Instruction<word_t> * instr = mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<std::endl;
      instr->exec(proc);
      delete(instr);
      proc.pc = proc.pc + sign_ext<word_t>(branch_offset) - 4;
      proc.debug() <<"branch to: \t" << std::hex <<proc.pc <<std::endl;
    }
  }

  template <typename word_t>
  std::ostream& MIPS_beq<word_t>::display(std::ostream& os) const {

    if (rt==0)
      return os <<"beqz\t"<<(MIPS_AsmId) rs <<"," <<(int) branch_offset;
    else if (rt==0 && rs==0)
      return os <<"b\t"  <<(int) branch_offset;
    else
      return os <<"beq\t" <<(MIPS_AsmId) rs << ","<<(MIPS_AsmId) rt << ","<<(int) branch_offset;
  }

  /**********************************************************************************/
  template <typename word_t>
  MIPS_beql<word_t>::MIPS_beql(uint8_t s, uint8_t t, int32_t offset):
    rs(s),rt(t), branch_offset(offset) {}

  template <typename word_t>
  void MIPS_beql<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.pc += 4;
    if(proc.regs[rs] == proc.regs[rt])
      {
        MIPS_Instruction<word_t> *instr = mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
        proc.debug() << "execute the instruction in delay slot \n" << *instr <<std::endl;
        instr -> exec(proc);
        delete(instr);

        proc.pc += sign_ext<word_t>(branch_offset) - 4;
        proc.debug() << "branch to \n" << proc.pc << std::endl;
      }
  }

  template <typename word_t>
  std::ostream& MIPS_beql<word_t>::display(std::ostream& os) const {
    return os <<"beql\t" <<(MIPS_AsmId) rs<< ","<<(MIPS_AsmId) rt << ","<<(int) branch_offset;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_beql(uint32_t instr){
    uint8_t s,t;
    uint32_t o;
    MIPS_I_FORMAT(instr,s,t,o);
    int32_t offset = (int32_t) o << 2;
    return new MIPS_beql<word_t>(s,t,offset);
  }

  /*******************************************************************/

  template <typename word_t>
  MIPS_bgez<word_t>::MIPS_bgez(uint8_t s, int32_t offset):
    rs(s),branch_offset(offset) {}

  template <typename word_t>
  void MIPS_bgez<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.pc +=4;
    if ((int32_t)proc.regs[rs] >= 0) {
      MIPS_Instruction<word_t> * instr = mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<std::endl;
      instr->exec(proc);
      delete(instr);
      proc.pc += sign_ext<word_t>(branch_offset) - 4;
    }
  }

  template <typename word_t>
  std::ostream& MIPS_bgez<word_t>::display(std::ostream& os) const {
    return os <<"bgez\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_bgezal<word_t>::MIPS_bgezal(uint8_t s,int32_t offset):
    rs(s), branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_bgezal<word_t>::display(std::ostream& os) const {
    return os <<"bgezal\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  template<typename word_t>
  MIPS_Instruction<word_t>* mips_bgezal(uint32_t instr)
  {
    uint8_t s;
    uint8_t t;
    uint32_t o;
    MIPS_I_FORMAT(instr,s,t,o);
    int32_t offset = (int32_t) o << 2;
    return new MIPS_bgezal<word_t>(s,offset);
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_bgezall<word_t>::MIPS_bgezall(uint8_t s,int32_t offset):
    rs(s),branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_bgezall<word_t>::display(std::ostream& os) const {
    return os <<"bgezall\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_bgezl<word_t>::MIPS_bgezl(uint8_t s, int32_t offset):
    rs(s),branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_bgezl<word_t>::display(std::ostream& os) const {
    return os <<"bgezl\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_bgtz<word_t>::MIPS_bgtz(uint8_t s, int32_t offset):
    rs(s),branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_bgtz<word_t>::display(std::ostream& os) const {
    return os <<"bgtz\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  template <typename word_t>
  MIPS_Instruction<word_t>* mips_bgtz(uint32_t instr){
    uint8_t s;
    uint8_t t;
    uint32_t i;
    MIPS_I_FORMAT(instr,s,t,i);
    int32_t offset = (int32_t) i << 2;
    return new MIPS_bgtz<word_t>(s,offset);
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_bgtzl<word_t>::MIPS_bgtzl(uint8_t s, int32_t offset):
    rs(s),branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_bgtzl<word_t>::display(std::ostream& os) const {
    return os <<"bgtzl\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_bgtzl(uint32_t instr){
    uint8_t s,t;
    uint32_t o;
    MIPS_I_FORMAT(instr,s,t,o);
    int32_t offset = (int32_t) o << 2;
    return new MIPS_bgtzl<word_t>(s,offset);
  }


  /**********************************************************************************/

  template <typename word_t>
  MIPS_blez<word_t>::MIPS_blez(uint8_t s, int32_t offset):
    rs(s),branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_blez<word_t>::display(std::ostream& os) const {
    return os <<"blez\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_blez(uint32_t instr){
    uint8_t s,t;
    uint32_t o;
    MIPS_I_FORMAT(instr, s, t, o);
    int32_t offset = (int32_t) o << 2;
    return new MIPS_blez<word_t>(s,offset);
  }
  /**********************************************************************************/

  template <typename word_t>
  MIPS_blezl<word_t>::MIPS_blezl(uint8_t s, int32_t offset):
    rs(s), branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_blezl<word_t>::display(std::ostream& os) const {
    return os <<"blezl\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_blezl(uint32_t instr){
    uint8_t s,t;
    uint32_t o;
    MIPS_I_FORMAT(instr, s, t, o);
    int32_t offset = (int32_t) o << 2;
    return new MIPS_blezl<word_t>(s,offset);
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_bltzal<word_t>::MIPS_bltzal(uint8_t s, int32_t offset):
    rs(s),branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_bltzal<word_t>::display(std::ostream& os) const {
    return os <<"bltzal\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_bltzall<word_t>::MIPS_bltzall(uint8_t s, int32_t offset):
    rs(s),branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_bltzall<word_t>::display(std::ostream& os) const {
    return os <<"bltzall\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_bltzl<word_t>::MIPS_bltzl(uint8_t s, int32_t offset):
    rs(s),branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_bltzl<word_t>::display(std::ostream& os) const {
    return os <<"bltzl\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_bne<word_t>::MIPS_bne(uint8_t s, uint8_t t, int32_t offset):
    rs(s), rt(t), branch_offset(offset) {}

  template <typename word_t>
  void MIPS_bne<word_t>::exec(MIPS_Processor<word_t> &proc) {
    proc.pc += 4;
    if (proc.regs[rs]!=proc.regs[rt]) {
      MIPS_Instruction<word_t> * instr = mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<std::endl;
      instr->exec(proc);
      delete(instr);
      proc.pc = proc.pc + sign_ext<word_t>(branch_offset) - 4;
    }
  }

  template <typename word_t>
  std::ostream& MIPS_bne<word_t>::display(std::ostream& os) const {
    if (rt==0)
      return os <<"bnez\t" <<(MIPS_AsmId) rs <<',' <<std::hex <<(int)branch_offset;
    else
      return os <<"bne\t" <<(MIPS_AsmId) rs <<',' <<(MIPS_AsmId) rt
                <<',' <<std::hex <<(int)branch_offset;
  }

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_bne(uint32_t instr){
    uint8_t s, t;
    uint32_t o;
    MIPS_I_FORMAT(instr,s,t,o);
    int32_t offset = (int32_t) o << 2;
    return new MIPS_bne<word_t>(s,t,offset);
  }
  /**********************************************************************************/

  template <typename word_t>
  MIPS_bnel<word_t>::MIPS_bnel(uint8_t s,uint8_t t,int32_t offset):
    rs(s),rt(t),branch_offset(offset) {}

  template <typename word_t>
  void MIPS_bnel<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.pc += 4;
    if (proc.regs[rs]!=proc.regs[rt]) {
      MIPS_Instruction<word_t> * instr = mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
      proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<std::endl;
      instr->exec(proc);
      delete(instr);
      proc.pc = proc.pc + sign_ext<word_t>(branch_offset) - 4;
    }
  }

  template <typename word_t>
  std::ostream& MIPS_bnel<word_t>::display(std::ostream& os) const {
    return os <<"bnel\t" <<(MIPS_AsmId) rs<< ","<<(MIPS_AsmId) rt << ","<<(int) branch_offset;
  }

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_bnel(uint32_t instr){
    uint8_t s,t;
    uint32_t o;
    MIPS_I_FORMAT(instr,s,t,o);
    int32_t f = (int32_t) o << 2;
    return new MIPS_bnel<word_t>(s,t,f);
  }
  /***********************************************************************************/

  template <typename word_t>
  MIPS_j<word_t>::MIPS_j(uint32_t ta):
    target_addr(ta) {}

  template <typename word_t>
  void MIPS_j<word_t>::exec(MIPS_Processor<word_t> &proc) {
    proc.pc += 4;
    MIPS_Instruction<word_t> * instr = mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
    proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<std::endl;
    instr->exec(proc);
    delete(instr);
    //proc.pc = (proc.pc && 0xF0000000) + target_addr - 1;//the first 4bits is address
    proc.pc = (proc.pc & ~0xfffffff) | target_addr;
  }

  template <typename word_t>
  std::ostream& MIPS_j<word_t>::display(std::ostream& os) const{
    return os <<"j\t"<<(int) target_addr;
  }

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_j(uint32_t instr){
    uint32_t i;
    uint32_t ta;
    MIPS_J_FORMAT(instr,i);
    ta = (int32_t)((i)<<2);
    return new MIPS_j<word_t>(ta);
  }

  /******************************************************************/
  template <typename word_t>
  MIPS_bltz<word_t>::MIPS_bltz(uint8_t s, int32_t offset):
    rs(s), branch_offset(offset) {}

  template <typename word_t>
  std::ostream& MIPS_bltz<word_t>::display(std::ostream& os) const {
    return os <<"bltz\t" <<(MIPS_AsmId) rs<< ","<<(int) branch_offset;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_jal<word_t>::MIPS_jal(uint32_t ta):
    target_addr(ta){}

  template <typename word_t>
  void MIPS_jal<word_t>::exec(MIPS_Processor<word_t> &proc){
    proc.regs[31] = proc.pc+8;
    proc.pc += 4;
    MIPS_Instruction<word_t> * instr = mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
    proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<std::endl;
    instr->exec(proc);
    delete(instr);
    //proc.pc = (proc.pc && 0xF0000000) + target_addr -1;//LM ?
    proc.pc = (proc.pc & ~0xfffffff) | target_addr;
  }

  template <typename word_t>
  std::ostream& MIPS_jal<word_t>::display(std::ostream& os) const{
    return os <<"jal\t"<< (int) target_addr ;
  }

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_jal(uint32_t instr){
    uint32_t i;
    uint32_t ta;
    MIPS_J_FORMAT(instr,i);
    ta = (int32_t)(signExtend24to32(i)<<2);
    return new MIPS_jal<word_t>(ta);
  }

  /*********************************************************************************/

  template <typename word_t>
  MIPS_jalr<word_t>::MIPS_jalr(uint8_t s,uint8_t d,uint8_t a):
    rs(s),rd(d),hint(a) {}

  template <typename word_t>
  void MIPS_jalr<word_t>::exec(MIPS_Processor<word_t> &proc){
    word_t tmp = proc.regs[rs];
    proc.regs[rd] = proc.pc + 8;
    proc.pc += 4;
    MIPS_Instruction<word_t> * instr = mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
    proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<std::endl;
    instr->exec(proc);
    delete(instr);
    proc.pc = tmp;
  }

  template <typename word_t>
  std::ostream& MIPS_jalr<word_t>::display(std::ostream& os) const{
    return os <<"jalr\t"<<(MIPS_AsmId) rd<<","<<(MIPS_AsmId) rs<<","<<(int) hint;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_jr<word_t>::MIPS_jr(uint8_t s,uint8_t a):
    rs(s),hint(a) {}

  template <typename word_t>
  void MIPS_jr<word_t>::exec(MIPS_Processor<word_t> &proc){
    int32_t tmp = proc.regs[rs];
    proc.pc += 4;
    MIPS_Instruction<word_t> * instr = mipsDecode<word_t>(proc.mmu.read_word(proc.pc));
    proc.debug() <<"execute instruction in delay slot: \t" <<*instr <<std::endl;
    instr->exec(proc);
    delete(instr);
    proc.pc = tmp;
  }
  template <typename word_t>
  std::ostream& MIPS_jr<word_t>::display(std::ostream& os) const{
    return os <<"jr\t"<<(MIPS_AsmId) rs;
  }

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_jr(uint32_t instr){
    uint8_t s,t,d,a;
    MIPS_R_FORMAT(instr,s,t,d,a);
    return new MIPS_jr<word_t>(s,a);
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_ssnop<word_t>::MIPS_ssnop(){};

  template <typename word_t>
  void MIPS_ssnop<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_ssnop<word_t>::display(std::ostream& os) const{
    return os <<"ssnop\t";
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_nop<word_t>::MIPS_nop(){}

  template <typename word_t>
  void MIPS_nop<word_t>::exec(MIPS_Processor<word_t> &proc) {
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_nop<word_t>::display(std::ostream& os) const{
    return os <<"nop\t";
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_break<word_t>::MIPS_break(uint32_t c):
    code(c) {}

  template <typename word_t>
  void MIPS_break<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.cp0.reg_cause.exc_code=Exc_Bp;
    proc.cp0.status().bev=0;
    proc.general_exception();
  }

  template <typename word_t>
  std::ostream& MIPS_break<word_t>::display(std::ostream& os) const{
    return os <<"break\t"<<(int) code;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_syscall<word_t>::MIPS_syscall(uint32_t c):
    code(c) {}

  template <typename word_t>
  void MIPS_syscall<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.cp0.reg_cause.exc_code=Exc_Sys;
    proc.cp0.status().bev=0;
    proc.general_exception();
  }

  template <typename word_t>
  std::ostream& MIPS_syscall<word_t>::display(std::ostream& os) const{
    return os <<"syscall\t"<<(int) code;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_teq<word_t>::MIPS_teq(uint8_t s,uint8_t t):
    rs(s),rt(t){}

  template <typename word_t>
  void MIPS_teq<word_t>::exec(MIPS_Processor<word_t> &proc){
    if((int32_t)proc.regs[rs]==(int32_t)proc.regs[rt]){
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    }
    else
      proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_teq<word_t>::display(std::ostream& os) const{
    return os <<"teq\t"<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt << std::endl;
  }

  /***********************************************************************************/
  template <typename word_t>
  MIPS_teqi<word_t>::MIPS_teqi(uint8_t s,int32_t imme):
    rs(s),immed(imme) {}

  template <typename word_t>
  std::ostream& MIPS_teqi<word_t>::display(std::ostream& os) const {
    return os <<"teqi\t" <<(MIPS_AsmId) rs<<"," <<(int) immed;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_tge<word_t>::MIPS_tge(uint8_t s,uint8_t t):
    rs(s),rt(t) {}

  template <typename word_t>
  std::ostream& MIPS_tge<word_t>::display(std::ostream& os) const{
    return os <<"tge\t"<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_tgei<word_t>::MIPS_tgei(uint8_t s,int32_t imme):
    rs(s),immed(imme) {}

  template <typename word_t>
  std::ostream& MIPS_tgei<word_t>::display(std::ostream& os) const {
    return os <<"tgei\t" <<(MIPS_AsmId) rs<<"," <<(int) immed;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_tgeiu<word_t>::MIPS_tgeiu(uint8_t s,uint32_t i):
    rs(s),immed(i) {}

  template <typename word_t>
  void MIPS_tgeiu<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    if(proc.regs[rs] >= sign_ext<word_t>(immed)){
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    }
    else
      proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_tgeiu<word_t>::display(std::ostream& os) const {
    return os <<"tgeiu\t" <<(MIPS_AsmId) rs<<"," <<(int) immed;
  }


  /**********************************************************************************/

  template <typename word_t>
  MIPS_tgeu<word_t>::MIPS_tgeu(uint8_t s,uint8_t t):
    rs(s),rt(t) {}

  template <typename word_t>
  void MIPS_tgeu<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    if(proc.regs[rs] >= proc.regs[rt]){
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    }
    else
      proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_tgeu<word_t>::display(std::ostream& os) const{
    return os <<"tgeu\t"<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_tlt<word_t>::MIPS_tlt(uint8_t s,uint8_t t):
    rs(s),rt(t){}

  template <typename word_t>
  std::ostream& MIPS_tlt<word_t>::display(std::ostream& os) const{
    return os <<"tlt\t"<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt << std::endl;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_tlti<word_t>::MIPS_tlti(uint8_t s,int32_t imme):
    rs(s),immed(imme) {}

  template <typename word_t>
  std::ostream& MIPS_tlti<word_t>::display(std::ostream& os) const {
    return os <<"tlti\t" <<(MIPS_AsmId) rs<<"," <<(int) immed;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_tltiu<word_t>::MIPS_tltiu(uint8_t s,uint32_t imme):
    rs(s),immed(imme) {}

  template <typename word_t>
  void MIPS_tltiu<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    if(proc.regs[rs] < sign_ext<word_t>(immed)) {
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    }
    else
      proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_tltiu<word_t>::display(std::ostream& os) const {
    return os <<"tltiu\t" <<(MIPS_AsmId) rs<<"," <<(int) immed;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_tltu<word_t>::MIPS_tltu(uint8_t s,uint8_t t):
    rs(s),rt(t){}

  template <typename word_t>
  void MIPS_tltu<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    if((uint32_t)proc.regs[rs] >= (uint32_t)proc.regs[rt]){
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    }
    else
      proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_tltu<word_t>::display(std::ostream& os) const{
    return os <<"tltu\t"<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt << std::endl;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_tne<word_t>::MIPS_tne(uint8_t s,uint8_t t):
    rs(s),rt(t){}

  template <typename word_t>
  void MIPS_tne<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    if((int32_t)proc.regs[rs] != (int32_t)proc.regs[rt]){
      proc.cp0.reg_cause.exc_code=Exc_Tr;
      proc.cp0.status().bev=0;
      proc.general_exception();
    }
    else
      proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_tne<word_t>::display(std::ostream& os) const{
    return os <<"tne\t"<<(MIPS_AsmId) rs<<","<<(MIPS_AsmId) rt << std::endl;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_tnei<word_t>::MIPS_tnei(uint8_t s,int32_t imme):
    rs(s),immed(imme) {}

  template <typename word_t>
  std::ostream& MIPS_tnei<word_t>::display(std::ostream& os) const {
    return os <<"tnei\t" <<(MIPS_AsmId) rs<<"," <<(int) immed;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_deret<word_t>::MIPS_deret(){}

  template <typename word_t>
  void MIPS_deret<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    // Instruction Used EJTAG Specification, which is not imlpemented
    TODO("DERET instruction is not supported because EJTAG protocol is not implemented");
  }

  template <typename word_t>
  std::ostream& MIPS_deret<word_t>::display(std::ostream& os) const{
    return os <<"deret\t";
  }

  /***********************************************************************************/
  template <typename word_t>
  MIPS_eret<word_t>::MIPS_eret(){}

  template <typename word_t>
  void MIPS_eret<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    if(proc.cp0.reg_status.erl)
    proc.cp0.reg_status.erl=false; // Status_ERL=0;
    else
    proc.cp0.reg_status.exl=false; // Status_EXL=0;

    proc.pc=proc.cp0.regs[30];
    proc.LLbit=0;

  }

  template <typename word_t>
  std::ostream& MIPS_eret<word_t>::display(std::ostream& os) const{
    return os <<"eret\t";
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_mfc0<word_t>::MIPS_mfc0(uint8_t t,uint8_t d,uint8_t s):
    rt(t),rd(d),sel(s) {}

  template <typename word_t>
  void MIPS_mfc0<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.regs[rt] = sign_ext<word_t>((uint32_t)proc.cp0.read_cp0(rd));
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_mfc0<word_t>::display(std::ostream& os) const{
    MIPS_AsmId tmp(rt);
    return os <<"mfc0\t"<<tmp <<","<<(MIPS_AsmId)rd<<","<<(int) sel;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_mtc0<word_t>::MIPS_mtc0(uint8_t t,uint8_t d,uint8_t s):
    rt(t),rd(d),sel(s) {}

  template <typename word_t>
  void MIPS_mtc0<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.cp0.write_cp0(rd,(uint32_t)proc.regs[rt]);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_mtc0<word_t>::display(std::ostream& os) const{
    return os <<"mtc0\t"<<(MIPS_AsmId) rt<<","<<(MIPS_AsmId) rd<<","<<(int) sel;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_sdbbp <word_t>::MIPS_sdbbp(uint32_t c):
    code(c) {}

  template <typename word_t>
  void MIPS_sdbbp<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    // TODO("sdbbp");
    // debugger not implemented
  }

  template <typename word_t>
  std::ostream& MIPS_sdbbp<word_t>::display(std::ostream& os) const {
    return os <<"sdbbp\t" <<(int) code;
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_tlbp<word_t>::MIPS_tlbp(){};

  template <typename word_t>
  void MIPS_tlbp<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.mmu.do_tlbp();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_tlbp<word_t>::display(std::ostream& os) const{
    return os <<"tlbp\t";
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_tlbr<word_t>::MIPS_tlbr(){}

  template <typename word_t>
  void MIPS_tlbr<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.mmu.do_tlbr();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_tlbr<word_t>::display(std::ostream& os) const{
    return os <<"tlbr\t";
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_tlbwi<word_t>::MIPS_tlbwi(){}

  template <typename word_t>
  void MIPS_tlbwi<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.mmu.do_tlbwi();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_tlbwi<word_t>::display(std::ostream& os) const{
    return os <<"tlbwi\t";
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_tlbwr<word_t>::MIPS_tlbwr(){}

  template <typename word_t>
  void MIPS_tlbwr<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.mmu.do_tlbwr();
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_tlbwr<word_t>::display(std::ostream& os) const{
    return os <<"tlbwr\t";
  }

  /**********************************************************************************/

  template <typename word_t>
  MIPS_wait<word_t>::MIPS_wait(uint32_t p):
    implement(p) {}

  template <typename word_t>
  void MIPS_wait<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    // Do nothing
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_wait<word_t>::display(std::ostream& os) const {
    return os <<"wait\t" <<(int) implement;
  }

  /***********************************************************************************/

  template <typename word_t>
  MIPS_cache<word_t>::MIPS_cache(uint8_t s,uint8_t t, uint32_t i):
    base(s),op(t),offset(i) {}

  template <typename word_t>
  void MIPS_cache<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    // TODO("cache");
    //cache is not simulated
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_cache<word_t>::display(std::ostream& os) const {
    return os <<"cache\t" <<(int) op<< ","<<(int) offset<<"," <<(MIPS_AsmId) base;
  }

  template <typename word_t>
  MIPS_Instruction<word_t> * mips_cache(uint32_t instr){
    uint8_t s, t;
    uint32_t i;
    MIPS_I_FORMAT(instr, s, t, i);
    return new MIPS_cache<word_t>(s,t,i);
  }

  /**********************************************************************************/
  template <typename word_t>
  MIPS_dmfc0<word_t>::MIPS_dmfc0(uint8_t t,uint8_t d,uint8_t s):
    rt(t),rd(d),sel(s) {}

  template <typename word_t>
  void MIPS_dmfc0<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.regs[rt] = (uint64_t)proc.cp0.read_cp0(rd);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dmfc0<word_t>::display(std::ostream& os) const{
    return os <<"dmfc0\t"<<(MIPS_AsmId) rt<<","<<(MIPS_AsmId) rd<<","<<(int) sel;
  }

  /**********************************************************************************///MIPS64

  template <typename word_t>
  MIPS_dmtc0<word_t>::MIPS_dmtc0(uint8_t t,uint8_t d,uint8_t s):
    rt(t),rd(d),sel(s) {}

  template <typename word_t>
  void MIPS_dmtc0<word_t>::exec(MIPS_Processor<word_t> &proc)
  {
    proc.cp0.write_cp0(rd,(uint64_t)proc.regs[rt]);
    proc.pc += 4;
  }

  template <typename word_t>
  std::ostream& MIPS_dmtc0<word_t>::display(std::ostream& os) const{
    return os <<"dmtc0\t"<<(MIPS_AsmId) rt<<","<<(MIPS_AsmId) rd<<","<<(int) sel;
  }

  /******************************************************///MIPS64


} // namespace simsoc
