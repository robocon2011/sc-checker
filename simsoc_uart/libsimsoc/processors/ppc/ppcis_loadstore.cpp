//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/processors/ppc/ppc_processor.hpp"
#include "libsimsoc/processors/ppc/ppcis_loadstore.hpp"

namespace simsoc {

  /*----------------------------------------------------------------------------*/
  PPC_dcbf::PPC_dcbf(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_dcbf::exec(PPC_Processor &proc) {
    //TODO("dcbf");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_dcbf::display(std::ostream& os) const {
    return os<<"dcbf";
  }

  /*----------------------------------------------------------------------------*/
  PPC_dcbst::PPC_dcbst(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_dcbst::exec(PPC_Processor &proc) {
    //TODO("dcbst");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_dcbst::display(std::ostream& os) const {
    return os<<"dcbst";
  }

  /*----------------------------------------------------------------------------*/
  PPC_dcbt::PPC_dcbt(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_dcbt::exec(PPC_Processor &proc) {
    //TODO("dcbt");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_dcbt::display(std::ostream& os) const {
    return os<<"dcbt";
  }

  /*----------------------------------------------------------------------------*/
  PPC_dcbtst::PPC_dcbtst(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_dcbtst::exec(PPC_Processor &proc) {
    //TODO("dcbtst");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_dcbtst::display(std::ostream& os) const {
    return os<<"dcbtst";
  }

  /*----------------------------------------------------------------------------*/
  PPC_dcbz::PPC_dcbz(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_dcbz::exec(PPC_Processor &proc) {
    //PPC_L1_CACHE_LINE_SIZE=32
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) +  proc.cpu.gpr[rb];
    assert((addr&0x3) == 0);
    for(int i = 0; i < 8; i++)
      proc.mmu.write_word(addr+i*4, 0);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_dcbz::display(std::ostream& os) const {
    return os<<"dcbz";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lbz::PPC_lbz(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lbz::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) +  d;
    proc.cpu.gpr[rt] = (uint32_t) proc.mmu.read_byte(addr);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lbz::display(std::ostream& os) const {
    return os<<"lbz\t"<<(PPC_AsmId)rt<<", "<<d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lbzu::PPC_lbzu(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lbzu::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] +  d;
    proc.cpu.gpr[rt] = (uint32_t) proc.mmu.read_byte(addr);
    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lbzu::display(std::ostream& os) const {
    return os<<"lbzu\t"<<(PPC_AsmId)rt<<", "<<d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lbzux::PPC_lbzux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):

    rt(_rt), ra(_ra), rb(_rb){}

  void PPC_lbzux::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = (uint32_t) proc.mmu.read_byte(addr);
    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lbzux::display(std::ostream& os) const {
    return os<<"lbzux\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lbzx::PPC_lbzx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lbzx::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) +  proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = (uint32_t) proc.mmu.read_byte(addr);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lbzx::display(std::ostream& os) const {
    return os<<"lbzx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  //64bit
  PPC_ld::PPC_ld(uint8_t _rt, uint8_t _ra, uint32_t _ds):
    rt(_rt), ra(_ra), ds(_ds) {}

  void PPC_ld::exec(PPC_Processor &proc) {
    TODO("ld");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_ld::display(std::ostream& os) const {
    return os<<"ld";
  }

  /*----------------------------------------------------------------------------*/
  //64bit
  PPC_ldarx::PPC_ldarx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_ldarx::exec(PPC_Processor &proc) {
    TODO("ldarx");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_ldarx::display(std::ostream& os) const {
    return os<<"ldarx";
  }

  /*----------------------------------------------------------------------------*/
  //bit64
  PPC_ldu::PPC_ldu(uint8_t _rt, uint8_t _ra, uint32_t _ds):
    rt(_rt), ra(_ra), ds(_ds) {}

  void PPC_ldu::exec(PPC_Processor &proc) {
    TODO("ldu");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_ldu::display(std::ostream& os) const {
    return os<<"ldu";
  }

  /*----------------------------------------------------------------------------*/
  //64bit
  PPC_ldux::PPC_ldux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_ldux::exec(PPC_Processor &proc) {
    TODO("ldux");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_ldux::display(std::ostream& os) const {
    return os<<"ldux";
  }

  /*----------------------------------------------------------------------------*/
  //64bit
  PPC_ldx::PPC_ldx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_ldx::exec(PPC_Processor &proc) {
    TODO("ldx");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_ldx::display(std::ostream& os) const {
    return os<<"ldx";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lfd::PPC_lfd(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lfd::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + d;//d is already sign extended
    proc.cpu.fpr[rt] = proc.mmu.read_double(addr);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lfd::display(std::ostream& os) const {
    return os<<"lfd\tfr"<<std::dec<<(int)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lfdu::PPC_lfdu(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lfdu::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"rA=0,instruction form is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extended
    proc.cpu.fpr[rt] = proc.mmu.read_double(addr);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lfdu::display(std::ostream& os) const {
    return os<<"lfdu\tfr"<<std::dec<<(int)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lfdux::PPC_lfdux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lfdux::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"rA=0,instruction form is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    proc.cpu.fpr[rt] = proc.mmu.read_double(addr);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lfdux::display(std::ostream& os) const {
    return os<<"lfdux\tfr"<<std::dec<<(int)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lfdx::PPC_lfdx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lfdx::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];
    proc.cpu.fpr[rt] = proc.mmu.read_double(addr);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lfdx::display(std::ostream& os) const {
    return os<<"lfdx\tfr"<<std::dec<<(int)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lfs::PPC_lfs(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lfs::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = (ra? proc.cpu.gpr[ra]:0) + d;//d is already sign extened
    uint32_t single_format = proc.mmu.read_word(addr);
    proc.cpu.fpr[rt] = fp_t::double_format(single_format);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lfs::display(std::ostream& os) const {
    return os<<"lfs\tfr"<<std::dec<<(int)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lfsu::PPC_lfsu(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lfsu::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    if(ra==0)
      {
        error()<<"instruction form with ra=0 is invalid"<<endl;
        exit(1);
      }
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extened
    uint32_t single_format = proc.mmu.read_word(addr);
    proc.cpu.fpr[rt] = fp_t::double_format(single_format);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lfsu::display(std::ostream& os) const {
    return os<<"lfsu\tfr"<<std::dec<<(int)rt<<",d("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lfsux::PPC_lfsux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lfsux::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    if(ra==0)
      {
        error()<<"instruction form with ra=0 is invalid"<<endl;
        exit(1);
      }
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    uint32_t single_format = proc.mmu.read_word(addr);
    proc.cpu.fpr[rt] = fp_t::double_format(single_format);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lfsux::display(std::ostream& os) const {
    return os<<"lfsux\tfr"<<dec<<(int)rt<<","<<(PPC_AsmId)ra<<","<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lfsx::PPC_lfsx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lfsx::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = (ra? proc.cpu.gpr[ra]:0) + proc.cpu.gpr[rb];
    uint32_t single_format = proc.mmu.read_word(addr);
    proc.cpu.fpr[rt] = fp_t::double_format(single_format);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lfsx::display(std::ostream& os) const {
    return os<<"lfsx\tfr"<<std::dec<<(int)rt<<","<<(PPC_AsmId)ra<<","<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lha::PPC_lha(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lha::exec(PPC_Processor &proc) {
    uint16_t r = 0;
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + d;

    if((addr&0x1) == 0){ //half word valignment
      r = proc.mmu.read_half(addr);
    } else {
      r |= proc.mmu.read_byte(addr);
      r <<= 8;
      r |= proc.mmu.read_byte(addr+1);
    }

    proc.cpu.gpr[rt] = (r & 0x8000) ? (r |0x0ffff0000) : r;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lha::display(std::ostream& os) const {
    return os<<"lha\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lhau::PPC_lhau(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lhau::exec(PPC_Processor &proc) {
    uint16_t r =0;
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x1) == 0){ //half word valignment
      r = proc.mmu.read_half(addr);
    } else {
      r |= proc.mmu.read_byte(addr);
      r <<= 8;
      r |= proc.mmu.read_byte(addr+1);
    }

    proc.cpu.gpr[rt] = (r & 0x8000) ? (r |0x0ffff0000) : r;
    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lhau::display(std::ostream& os) const {
    return os<<"lhau\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lhaux::PPC_lhaux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lhaux::exec(PPC_Processor &proc) {
    uint16_t r = 0;
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      r = proc.mmu.read_half(addr);
    } else {
      r |= proc.mmu.read_byte(addr);
      r <<= 8;
      r |= proc.mmu.read_byte(addr+1);
    }

    proc.cpu.gpr[rt] = (r & 0x8000) ? (r |0x0ffff0000) : r;
    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lhaux::display(std::ostream& os) const {
    return os<<"lhaux\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lhax::PPC_lhax(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lhax::exec(PPC_Processor &proc) {
    uint16_t r = 0;
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      r = proc.mmu.read_half(addr);
    } else {
      r |= proc.mmu.read_byte(addr);
      r <<= 8;
      r |= proc.mmu.read_byte(addr+1);
    }

    proc.cpu.gpr[rt] = (r & 0x8000) ? (r |0x0ffff0000) : r;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lhax::display(std::ostream& os) const {
    return os<<"lhax\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lhbrx::PPC_lhbrx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lhbrx::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = half_be_le_translate(proc.mmu.read_half(addr));
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = half_be_le_translate(data);
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lhbrx::display(std::ostream& os) const {
    return os<<"lhbrx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lhz::PPC_lhz(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lhz::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + d;

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_half(addr);
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = data;
    }
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lhz::display(std::ostream& os) const {
    return os<<"lhz\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lhzu::PPC_lhzu(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lhzu::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_half(addr);
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lhzu::display(std::ostream& os) const {
    return os<<"lhzu\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lhzux::PPC_lhzux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lhzux::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_half(addr);
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lhzux::display(std::ostream& os) const {
    return os<<"lhzux\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lhzx::PPC_lhzx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lhzx::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_half(addr);
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lhzx::display(std::ostream& os) const {
    return os<<"lhzx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lmw::PPC_lmw(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lmw::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + d;
    uint32_t r;
    for (r = rt; r <= 31; r++) {
      proc.cpu.gpr[r] = proc.mmu.read_word(addr);
      addr += 4;
    }
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lmw::display(std::ostream& os) const {
    return os<<"lmw\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lswi::PPC_lswi(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lswi::exec(PPC_Processor &proc) {
    uint32_t r = 0, tmp_rt = rt;
    int i;
    uint8_t tmp, nb = rb;
    uint32_t addr = ra ? proc.cpu.gpr[ra] : 0;
    if (nb == 0)
      nb = 32;

    for (i = 4; nb > 0; nb--, i--) {
      if (!i) {
        i = 4;
        proc.cpu.gpr[tmp_rt] = r;
        tmp_rt++;
        tmp_rt %= 32;
        r = 0;
      }
      tmp = proc.mmu.read_byte(addr);
      r <<= 8;
      r |= tmp;
      addr++;
    }

    while (i) {
      r <<= 8;
      i--;
    }
    proc.cpu.gpr[tmp_rt] = r;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lswi::display(std::ostream& os) const {
    return os<<"lswi\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(int)rb<<"";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lswx::PPC_lswx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lswx::exec(PPC_Processor &proc) {
    uint32_t r = 0 , tmp_rt = rt;
    int i;
    uint8_t tmp;
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb] ;
    int nb = XER_n(proc.cpu.xer);

    for (i = 4; nb > 0; nb--, i--) {
      if (!i) {
        i = 4;
        proc.cpu.gpr[tmp_rt] = r;
        tmp_rt++;
        tmp_rt %= 32;
        r = 0;
      }
      tmp = proc.mmu.read_byte(addr);
      r <<= 8;
      r |= tmp;
      addr++;
    }

    while (i) { //the unfilled loworder byte(s) of the register are set to 0
      r<<=8;
      i--;
    }
    proc.cpu.gpr[tmp_rt] = r; // modified tmp_rt
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lswx::display(std::ostream& os) const {
    return os<<"lswx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lwa::PPC_lwa(uint8_t _rt, uint8_t _ra, uint32_t _ds):
    rt(_rt), ra(_ra), ds(_ds) {}

  void PPC_lwa::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + ds;
    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lwa::display(std::ostream& os) const {
    return os<<"lwa\t"<<(PPC_AsmId)rt<<", "<<(int)ds<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lwarx::PPC_lwarx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lwarx::exec(PPC_Processor &proc) {
    uint32_t v;
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

    assert((addr&0x3) == 0);
    v = proc.mmu.read_word(addr);

    proc.cpu.have_reservation= true;
    proc.cpu.reserve = v; //todo pa(addr)
    proc.cpu.gpr[rt] = v;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lwarx::display(std::ostream& os) const {
    return os<<"lwarx\n";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lwaux::PPC_lwaux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lwaux::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra]  + proc.cpu.gpr[rb] ;

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lwaux::display(std::ostream& os) const {
    return os<<"lwaux\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb<<"\n";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lwax::PPC_lwax(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lwax::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lwax::display(std::ostream& os) const {
    return os<<"lwax\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lwbrx::PPC_lwbrx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lwbrx::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = word_be_le_translate(proc.mmu.read_word(addr));
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = word_be_le_translate(data);
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lwbrx::display(std::ostream& os) const {
    return os<<"lwbrx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lwz::PPC_lwz(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lwz::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + d;

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lwz::display(std::ostream& os) const {
    return os<<"lwz\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lwzu::PPC_lwzu(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_lwzu::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lwzu::display(std::ostream& os) const {
    return os<<"lwzu\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_lwzux::PPC_lwzux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lwzux::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lwzux::display(std::ostream& os) const {
    return os<<"lwzux\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_lwzx::PPC_lwzx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_lwzx::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_lwzx::display(std::ostream& os) const {
    return os<<"lwzx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stb::PPC_stb(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_stb::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + d;
    proc.mmu.write_byte(addr, (uint8_t) proc.cpu.gpr[rt]);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stb::display(std::ostream& os) const {
    return os<<"stb\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stbu::PPC_stbu(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_stbu::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + d;
    proc.mmu.write_byte(addr, (uint8_t) proc.cpu.gpr[rt]);
    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stbu::display(std::ostream& os) const {
    return os<<"stbu\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stbux::PPC_stbux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stbux::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    proc.mmu.write_byte(addr, (uint8_t) proc.cpu.gpr[rt]);
    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stbux::display(std::ostream& os) const {
    return os<<"stbux\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stbx::PPC_stbx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stbx::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];
    proc.mmu.write_byte(addr, (uint8_t) proc.cpu.gpr[rt]);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stbx::display(std::ostream& os) const {
    return os<<"stbx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_std::PPC_std(uint8_t _rt, uint8_t _ra, uint32_t _ds):
    rt(_rt), ra(_ra), ds(_ds) {}

  void PPC_std::exec(PPC_Processor &proc) {
    TODO("std");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_std::display(std::ostream& os) const {
    return os<<"std\t"<<(PPC_AsmId)rt<<", "<<(int)ds<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stdcx_::PPC_stdcx_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stdcx_::exec(PPC_Processor &proc) {
    TODO("stdcx_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stdcx_::display(std::ostream& os) const {
    return os<<"stdcx_";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stdu::PPC_stdu(uint8_t _rt, uint8_t _ra, uint32_t _ds):
    rt(_rt), ra(_ra), ds(_ds) {}

  void PPC_stdu::exec(PPC_Processor &proc) {
    TODO("stdu");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stdu::display(std::ostream& os) const {
    return os<<"stdu\t"<<(PPC_AsmId)rt<<", "<<(int)ds<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stdux::PPC_stdux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stdux::exec(PPC_Processor &proc) {
    TODO("stdux");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stdux::display(std::ostream& os) const {
    return os<<"stdux\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stdx::PPC_stdx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stdx::exec(PPC_Processor &proc) {
    TODO("stdx");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stdx::display(std::ostream& os) const {
    return os<<"stdx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stfd::PPC_stfd(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_stfd::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + d;//d is already sign extended
    proc.mmu.write_double(addr,proc.cpu.fpr[rt]);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stfd::display(std::ostream& os) const {
    return os<<"stfd\tfr"<<std::dec<<(int)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stfdu::PPC_stfdu(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_stfdu::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"instruction form with ra =0 is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extended
    proc.mmu.write_double(addr,proc.cpu.fpr[rt]);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stfdu::display(std::ostream& os) const {
    return os<<"stfdu\tfr"<<std::dec<<(int)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stfdux::PPC_stfdux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stfdux::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"instruction form with ra =0 is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb] ;
    proc.mmu.write_double(addr,proc.cpu.fpr[rt]);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stfdux::display(std::ostream& os) const {
    return os<<"stfdux\tfr"<<std::dec<<(int)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stfdx::PPC_stfdx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stfdx::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb] ;
    proc.mmu.write_double(addr,proc.cpu.fpr[rt]);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stfdx::display(std::ostream& os) const {
    return os<<"stfdx\tfpr"<<std::dec<<(int)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stfiwx::PPC_stfiwx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stfiwx::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb] ;
    proc.mmu.write_word(addr, (uint32_t) proc.cpu.fpr[rt]);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stfiwx::display(std::ostream& os) const {
    return os<<"stfiwx\tfr"<<std::dec<<(int)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stfs::PPC_stfs(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_stfs::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + d;//d is already sign extended
    uint32_t data = fp_t::single_format(proc.cpu.fpr[rt]);
    proc.mmu.write_word(addr, data);

    //for debug
    float f = *reinterpret_cast<float*>(&data);
    debug()<<"store :"<< f<<" ["<<hex<<data<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stfs::display(std::ostream& os) const {
    return os<<"stfs\tfr"<<std::dec<<(int)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stfsu::PPC_stfsu(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_stfsu::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"instruction form with ra=0 is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extended
    uint32_t data = fp_t::single_format(proc.cpu.fpr[rt]);
    proc.mmu.write_word(addr, data);
    proc.cpu.gpr[ra] = addr;

    //for debug
    float f = *reinterpret_cast<float*>(&data);
    debug()<<"store :"<< f<<" ["<<hex<<data<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stfsu::display(std::ostream& os) const {
    return os<<"stfsu\tfr"<<std::dec<<(int)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stfsux::PPC_stfsux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stfsux::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"instruction form with ra=0 is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    uint32_t data = fp_t::single_format(proc.cpu.fpr[rt]);
    proc.mmu.write_word(addr,data);
    proc.cpu.gpr[ra] = addr;

    //for debug
    float f = *reinterpret_cast<float*>(&data);
    debug()<<"store :"<< f<<" ["<<hex<<data<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stfsux::display(std::ostream& os) const {
    return os<<"stfsux\tfr"<<std::dec<<(int)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stfsx::PPC_stfsx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stfsx::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];
    uint32_t data = fp_t::single_format(proc.cpu.fpr[rt]);
    proc.mmu.write_word(addr,data);

    //for debug
    float f = *reinterpret_cast<float*>(&data);
    debug()<<"store :"<< f<<" ["<<hex<<data<<"]"<<endl;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stfsx::display(std::ostream& os) const {
    return os<<"stfsx\tfr"<<std::dec<<(int)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_sth::PPC_sth(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_sth::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + d;

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, (uint16_t)proc.cpu.gpr[rt]);
    } else {
      proc.mmu.write_byte(addr, (uint8_t)(proc.cpu.gpr[rt]>>8));
      proc.mmu.write_byte(addr+1, (uint8_t)proc.cpu.gpr[rt]);
    }

    proc.cpu.pc = proc.cpu.pc + 4;//= 4;
  }

  std::ostream& PPC_sth::display(std::ostream& os) const {
    return os<<"sth\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_sthbrx::PPC_sthbrx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_sthbrx::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, half_be_le_translate((uint16_t) proc.cpu.gpr[rt]));
    } else {
      proc.mmu.write_byte(addr, (uint8_t)proc.cpu.gpr[rt]);
      proc.mmu.write_byte(addr+1, (uint8_t)(proc.cpu.gpr[rt]>>8));
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sthbrx::display(std::ostream& os) const {
    return os<<"sthbrx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_sthu::PPC_sthu(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_sthu::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, (uint16_t)proc.cpu.gpr[rt]);
    } else {
      proc.mmu.write_byte(addr, (uint8_t)(proc.cpu.gpr[rt]>>8));
      proc.mmu.write_byte(addr+1, (uint8_t)proc.cpu.gpr[rt]);
    }

    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sthu::display(std::ostream& os) const {
    return os<<"sthu\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_sthux::PPC_sthux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_sthux::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, (uint16_t)proc.cpu.gpr[rt]);
    } else {
      proc.mmu.write_byte(addr, (uint8_t)(proc.cpu.gpr[rt]>>8));
      proc.mmu.write_byte(addr+1, (uint8_t)proc.cpu.gpr[rt]);
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sthux::display(std::ostream& os) const {
    return os<<"sthux\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_sthx::PPC_sthx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_sthx::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, (uint16_t)proc.cpu.gpr[rt]);
    } else {
      proc.mmu.write_byte(addr, (uint8_t)(proc.cpu.gpr[rt]>>8));
      proc.mmu.write_byte(addr+1, (uint8_t)proc.cpu.gpr[rt]);
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sthx::display(std::ostream& os) const {
    return os<<"sthx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stmw::PPC_stmw(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_stmw::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) +d;
    uint32_t r;//, tmp;
    for(r = rt; r <= 31; r++){
      //tmp = word_be_le_translate(proc.cpu.gpr[r]);
      proc.mmu.write_word(addr, proc.cpu.gpr[r]);
      addr +=4;
    }
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stmw::display(std::ostream& os) const {
    return os<<"stmw\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stswi::PPC_stswi(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stswi::exec(PPC_Processor &proc) {
    uint32_t addr = ra ? proc.cpu.gpr[ra] : 0;
    uint32_t r = 0, tmp_rt = rt;
    int i;
    uint8_t nb = rb;
    if (nb==0)
      nb = 32;

    for (i = 0; nb > 0; i--, nb--) {
      if (!i) {
        r = proc.cpu.gpr[tmp_rt];
        tmp_rt++;
        tmp_rt%=32;
        i = 4;
      }
      proc.mmu.write_byte(addr, r>>24);
      r<<=8;
      addr++;
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stswi::display(std::ostream& os) const {
    return os<<"stswi\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(int)rb<<"";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stswx::PPC_stswx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stswx::exec(PPC_Processor &proc) {
#if 0
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];
    int i;
    uint32_t r = rt - 1 ;
    int nb = XER_n(proc.cpu.xer);
    for (i = 32; 0 < nb; i--, nb--) {
      if (!i) {
        r = proc.cpu.gpr[rt];//word_be_le_translate(proc.cpu.gpr[rt]);
        rt++;
        rt%=32;
        i = 4;
      }
      proc.mmu.write_byte(addr, r>>24);//(uint8_t)r);
      r <<=8;
      addr++;
    }
    proc.cpu.pc += 4;
#endif
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];
    int i=0;
    uint32_t r = rt-1;
    uint32_t temp = 0;
    int nb = XER_n(proc.cpu.xer);
    while(nb>0) {
      if (i == 0){
          r++;
          r%=32;
          temp = proc.cpu.gpr[r];
        }
      proc.mmu.write_byte(addr,(uint8_t)(temp>>(24-i)));
      addr++;
      i += 8;
      if(i==32) i=0;
      nb--;
    }
    proc.cpu.pc += 4;

  }

  std::ostream& PPC_stswx::display(std::ostream& os) const {
    return os<<"stswx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stw::PPC_stw(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_stw::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + d;

    if((addr&0x3) == 0){ //word valignment
      proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
    } else {
      int i;
      uint32_t data = proc.cpu.gpr[rt];
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stw::display(std::ostream& os) const {
    return os<<"stw\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stwbrx::PPC_stwbrx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stwbrx::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];
    if((addr&0x3) == 0){ //word valignment
      proc.mmu.write_word(addr, word_be_le_translate(proc.cpu.gpr[rt]));
    } else {
      int i;
      uint32_t data = word_be_le_translate(proc.cpu.gpr[rt]);
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stwbrx::display(std::ostream& os) const {
    return os<<"stwbrx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stwcx_::PPC_stwcx_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stwcx_::exec(PPC_Processor &proc) {
    uint32_t v, addr;

    proc.cpu.cr &= 0x0fffffff;
    if (proc.cpu.have_reservation) {
      proc.cpu.have_reservation = false;
      addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

      assert((addr&0x3) == 0);
      v = proc.mmu.read_word(addr);

      if (v == proc.cpu.reserve) {
        proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
        proc.cpu.cr |= CR_CR0_EQ;
      } else
        proc.cpu.cr &= ~CR_CR0_EQ;

      if (proc.cpu.xer & XER_SO) {
        proc.cpu.cr |= CR_CR0_SO;
      }
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stwcx_::display(std::ostream& os) const {
    return os<<"stwcx_";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stwu::PPC_stwu(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_stwu::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x3) == 0){ //word valignment
      proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
    } else {
      int i;
      uint32_t data = proc.cpu.gpr[rt];
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }

    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stwu::display(std::ostream& os) const {
    return os<<"stwu\t"<<(PPC_AsmId)rt<<", "<<(int)d<<"("<<(PPC_AsmId)ra<<")";
  }

  /*----------------------------------------------------------------------------*/
  PPC_stwux::PPC_stwux(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stwux::exec(PPC_Processor &proc) {
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
    } else {
      int i;
      uint32_t data = proc.cpu.gpr[rt];
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }

    proc.cpu.gpr[ra] = addr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stwux::display(std::ostream& os) const {
    return os<<"stwux\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_stwx::PPC_stwx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_stwx::exec(PPC_Processor &proc) {
    uint32_t addr = (ra ? proc.cpu.gpr[ra] : 0) + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
    } else {
      int i;
      uint32_t data = proc.cpu.gpr[rt];
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_stwx::display(std::ostream& os) const {
    return os<<"stwx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_dss::PPC_dss(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_dss::exec(PPC_Processor &proc) {
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_dss::display(std::ostream& os) const {
    return os<<"dss";
  }

} // namespace simsoc
