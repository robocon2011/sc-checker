//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "ppcis_alu.hpp"
#include "ppc_utils.hpp"
#include "ppc_processor.hpp"

namespace simsoc {

  /*----------------------------------------------------------------------------*/
  PPC_add::PPC_add(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_add::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_add::display(std::ostream& os) const {
    return os<<"add\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_add_::PPC_add_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_add_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    ppc_update_cr0(proc, rt);// update cr0 flags
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_add_::display(std::ostream& os) const {
    return os<<"add_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addo::PPC_addo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addo::exec(PPC_Processor &proc) {
    uint32_t ra_content=proc.cpu.gpr[ra];
    uint32_t rb_content=proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    if((ra_content^~rb_content)&(ra_content^proc.cpu.gpr[rt])>>31)
      proc.cpu.xer |= (XER_SO | XER_OV); // set OV and SO
    else
      proc.cpu.xer &= ~XER_OV;//remain so bits.
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addo::display(std::ostream& os) const {
    return os<<"addo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addo_::PPC_addo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addo_::exec(PPC_Processor &proc) {
    uint32_t ra_content=proc.cpu.gpr[ra];
    uint32_t rb_content=proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ra_content + rb_content;
    if((ra_content^~rb_content)&(ra_content^proc.cpu.gpr[rt]))
      proc.cpu.xer |= (XER_SO | XER_OV);//update xer
    else
      proc.cpu.xer &= ~XER_OV;//update xer
    ppc_update_cr0(proc, rt);// update cr0 flags
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addo_::display(std::ostream& os) const {
    return os<<"addo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addc::PPC_addc(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addc::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];

    proc.cpu.gpr[rt] = ra_content + proc.cpu.gpr[rb];

    // update xer
    if (proc.cpu.gpr[rt] < ra_content)
      proc.cpu.xer |= XER_CA; // XER[CA] = 1
    else
      proc.cpu.xer &= ~XER_CA; // XER[CA] = 0

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addc::display(std::ostream& os) const {
    return os<<"addc\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addc_::PPC_addc_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addc_::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] =  ra_content + proc.cpu.gpr[rb];

    // update xer
    if (proc.cpu.gpr[rt] < ra_content)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    ppc_update_cr0(proc, rt);// update cr0 flags
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addc_::display(std::ostream& os) const {
    return os<<"addc_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addco::PPC_addco(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addco::exec(PPC_Processor &proc) {
    uint32_t ra_content=proc.cpu.gpr[ra];
    uint32_t rb_content=proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ra_content + rb_content;

    // update xer
    if (proc.cpu.gpr[rt] < ra_content)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ra_content^~rb_content)&(ra_content^proc.cpu.gpr[rt]))
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addco::display(std::ostream& os) const {
    return os<<"addco\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addco_::PPC_addco_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addco_::exec(PPC_Processor &proc) {
    uint32_t ra_content=proc.cpu.gpr[ra];
    uint32_t rb_content=proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ra_content + rb_content;

    // update xer
    if (proc.cpu.gpr[rt] < ra_content)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ra_content^~rb_content)&(ra_content^proc.cpu.gpr[rt])>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);// update cr0 flags
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addco_::display(std::ostream& os) const {
    return os<<"addco_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_adde::PPC_adde(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_adde::exec(PPC_Processor &proc) {
    uint32_t ra_content=proc.cpu.gpr[ra];
    uint32_t rb_content=proc.cpu.gpr[rb];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + rb_content + ca;

    // update xer
    if (ppc_carry(ra_content,rb_content,ca)) //FIXME
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_adde::display(std::ostream& os) const {
    return os<<"adde\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb<<"+ CA";
  }

  /*----------------------------------------------------------------------------*/
  PPC_adde_::PPC_adde_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_adde_::exec(PPC_Processor &proc) {
    uint32_t ra_content=proc.cpu.gpr[ra];
    uint32_t rb_content=proc.cpu.gpr[rb];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + rb_content + ca;

    // update xer
    if (ppc_carry(ra_content, rb_content , ca))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;


    ppc_update_cr0(proc, rt);// update cr0 flags
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_adde_::display(std::ostream& os) const {
    return os<<"adde_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb<<"+ CA";
  }

  /*----------------------------------------------------------------------------*/
  PPC_addeo::PPC_addeo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addeo::exec(PPC_Processor &proc) {
    uint32_t ra_content=proc.cpu.gpr[ra];
    uint32_t rb_content=proc.cpu.gpr[rb];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + rb_content + ca;

    // update xer
    if (ppc_carry(ra_content , rb_content  , ca))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ra_content^~rb_content)&(ra_content^proc.cpu.gpr[rt])>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addeo::display(std::ostream& os) const {
    return os<<"addeo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb<<"+ CA";
  }

  /*----------------------------------------------------------------------------*/
  PPC_addeo_::PPC_addeo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addeo_::exec(PPC_Processor &proc) {
    uint32_t ra_content=proc.cpu.gpr[ra];
    uint32_t rb_content=proc.cpu.gpr[rb];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + rb_content + ca;

    // update xer
    if (ppc_carry(ra_content, ra_content , ca))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ra_content^~rb_content)&(ra_content^proc.cpu.gpr[rt]))
      proc.cpu.xer |= (XER_SO | XER_OV); // FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);// update cr0 flags
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addeo_::display(std::ostream& os) const {
    return os<<"addeo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb<<"+ CA";
  }

  /*----------------------------------------------------------------------------*/
  PPC_addi::PPC_addi(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_addi::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = (ra ? proc.cpu.gpr[ra] : 0) + d;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addi::display(std::ostream& os) const {
    return os<<"addi\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(int)d;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addic::PPC_addic(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_addic::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] = ra_content + d;

    // update XER
    if (proc.cpu.gpr[rt] < ra_content)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addic::display(std::ostream& os) const {
    return os<<"addic\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(int)d;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addic_::PPC_addic_(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_addic_::exec(PPC_Processor &proc) {
    const uint32_t ra_content = proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] = ra_content + d;

    // update XER
    if (proc.cpu.gpr[rt] < ra_content)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    // update cr0 flags
    ppc_update_cr0(proc, rt);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addic_::display(std::ostream& os) const {
    return os<<"addic_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(int)d;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addis::PPC_addis(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_addis::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = (ra ? proc.cpu.gpr[ra] : 0) +(d << 16);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addis::display(std::ostream& os) const {
    return os<<"addis\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(int)d;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addme::PPC_addme(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addme::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + ca + 0xffffffff;

    if (ra_content || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addme::display(std::ostream& os) const {
    return os<<"addme\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addme_::PPC_addme_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addme_::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + ca + 0xffffffff;

    if (ra_content || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    // update cr0 flags
    ppc_update_cr0(proc, rt);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addme_::display(std::ostream& os) const {
    return os<<"addme_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addmeo::PPC_addmeo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addmeo::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + ca + 0xffffffff;

    if (ra_content || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ra_content^~(0xffffffff+ca))&((ra_content^proc.cpu.gpr[rt]))<<31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addmeo::display(std::ostream& os) const {
    return os<<"addmeo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addmeo_::PPC_addmeo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addmeo_::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + ca + 0xffffffff;

    if (ra_content || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if ((ra_content^~(ca+0xffffffff))&((ra_content^proc.cpu.gpr[rt]))<<31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    // update cr0 flags
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addmeo_::display(std::ostream& os) const {
    return os<<"addmeo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addze::PPC_addze(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addze::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + ca;

    if ((ra_content == 0xffffffff) && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addze::display(std::ostream& os) const {
    return os<<"addze\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addze_::PPC_addze_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addze_::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + ca;

    if ((ra_content == 0xffffffff) && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    // update cr0
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addze_::display(std::ostream& os) const {
    return os<<"addze_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addzeo::PPC_addzeo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addzeo::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + ca;

    if ((ra_content == 0xffffffff) && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ra_content^~ca)&(ra_content^proc.cpu.gpr[rt])<<31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addzeo::display(std::ostream& os) const {
    return os<<"addzeo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_addzeo_::PPC_addzeo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_addzeo_::exec(PPC_Processor &proc) {
    uint32_t ra_content = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ra_content + ca;

    if ((ra_content == 0xffffffff) && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    if((ra_content^~ca)&(ra_content^proc.cpu.gpr[rt])<<31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    // update cr0
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_addzeo_::display(std::ostream& os) const {
    return os<<"addzeo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_and::PPC_and(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_and::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] & proc.cpu.gpr[rb];

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_and::display(std::ostream& os) const {
    return os<<"and\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_and_::PPC_and_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_and_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] & proc.cpu.gpr[rb];

    // update cr0 flags
    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_and_::display(std::ostream& os) const {
    return os<<"and_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_andc::PPC_andc(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_andc::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] & ~proc.cpu.gpr[rb];

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_andc::display(std::ostream& os) const {
    return os<<"andc\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_andc_::PPC_andc_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_andc_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] & ~proc.cpu.gpr[rb];

    // update cr0 flags
    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_andc_::display(std::ostream& os) const {
    return os<<"andc_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_andi_::PPC_andi_(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_andi_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] & d;

    // update cr0 flags
    ppc_update_cr0(proc, ra);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_andi_::display(std::ostream& os) const {
    return os<<"andi_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<d;
  }

  /*----------------------------------------------------------------------------*/
  PPC_andis_::PPC_andis_(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_andis_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] & (d << 16);

    // update cr0 flags
    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_andis_::display(std::ostream& os) const {
    return os<<"andis_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<d;
  }

  /*----------------------------------------------------------------------------*/
  PPC_cmp::PPC_cmp(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_cmp::exec(PPC_Processor &proc) {
    int32_t a = proc.cpu.gpr[ra];
    int32_t b = proc.cpu.gpr[rb];
    uint32_t c, bf;

    bf = rt >> 2;
    if (a < b)
      c = 8;
    else if (a > b)
      c = 4;
    else
      c = 2;

    if (proc.cpu.xer & XER_SO)
      c |= 1;

    proc.cpu.cr &= ppc_cmp_and_mask[bf];
    proc.cpu.cr |= c<<((7 - bf)*4);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_cmp::display(std::ostream& os) const {
    return os<<"cmp\tcr"<<std::dec<<(int)(rt >> 2)<<", "<<"L, "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_cmpi::PPC_cmpi(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_cmpi::exec(PPC_Processor &proc) {
    int32_t a = proc.cpu.gpr[ra];
    int32_t b = d;
    uint32_t c, bf;

    bf = rt>> 2;
    if (a < b)
      c = 8;
    else if (a > b)
      c = 4;
    else
      c = 2;

    if (proc.cpu.xer & XER_SO)
      c |= 1;

    proc.cpu.cr &= ppc_cmp_and_mask[bf];
    proc.cpu.cr |= c<<((7 - bf)*4);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_cmpi::display(std::ostream& os) const {
    return os<<"cmpi\tcr"<<std::dec<<(int)(rt >> 2)<<", "<<"L, "<<(PPC_AsmId)ra<<", "<<(int)d;
  }

  /*----------------------------------------------------------------------------*/
  PPC_cmpl::PPC_cmpl(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_cmpl::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t b = proc.cpu.gpr[rb];
    uint32_t c, bf;

    bf = rt >> 2;
    if (a < b)
      c = 8;
    else if (a > b)
      c = 4;
    else
      c = 2;

    if (proc.cpu.xer & XER_SO)
      c |= 1;

    proc.cpu.cr &= ppc_cmp_and_mask[bf];
    proc.cpu.cr |= c<<((7 - bf)*4);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_cmpl::display(std::ostream& os) const {
    return os<<"cmpl\tcr"<<std::dec<<(int)(rt >> 2)<<", "<<"L, "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_cmpli::PPC_cmpli(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_cmpli::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t b = d;
    uint32_t c, bf;

    bf = rt >> 2;
    if (a < b)
      c = 8;
    else if (a > b)
      c = 4;
    else
      c = 2;

    if (proc.cpu.xer & XER_SO)
      c |= 1;

    proc.cpu.cr &= ppc_cmp_and_mask[bf];
    proc.cpu.cr |= c<<((7 - bf)*4);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_cmpli::display(std::ostream& os) const {
    return os<<"cmpli\tcr"<<std::dec<<(int)(rt >> 2)<<", "<<"L, "<<(PPC_AsmId)ra<<", "<<(int)d;
  }

  /*----------------------------------------------------------------------------*/
  PPC_cntlzd::PPC_cntlzd(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_cntlzd::exec(PPC_Processor &proc) {
    TODO("cntlzd");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_cntlzd::display(std::ostream& os) const {
    return os<<"cntlzd\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_cntlzd_::PPC_cntlzd_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_cntlzd_::exec(PPC_Processor &proc) {
    TODO("cntlzd_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_cntlzd_::display(std::ostream& os) const {
    return os<<"cntlzd_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_cntlzw::PPC_cntlzw(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_cntlzw::exec(PPC_Processor &proc) {
    uint32_t n = 0;
    uint32_t x = 0x80000000;
    uint32_t v = proc.cpu.gpr[rt];
    while (!(v & x)) {
      n++;
      if (n == 32)
        break;
      x >>= 1;
    }

    proc.cpu.gpr[ra] = n;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_cntlzw::display(std::ostream& os) const {
    return os<<"cntlzw\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_cntlzw_::PPC_cntlzw_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_cntlzw_::exec(PPC_Processor &proc) {
    uint32_t n = 0;
    uint32_t x = 0x80000000;
    uint32_t v = proc.cpu.gpr[rt];
    while (!(v & x)) {
      n++;
      if (n == 32)
        break;
      x >>= 1;
    }

    proc.cpu.gpr[ra] = n;

    // update cr0 flags
    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_cntlzw_::display(std::ostream& os) const {
    return os<<"cntlzw_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_crand::PPC_crand(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_crand::exec(PPC_Processor &proc) {
    if ((proc.cpu.cr & (1<<(31-ba))) && (proc.cpu.cr & (1<<(31-bb))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_crand::display(std::ostream& os) const {
    return os<<"crand\t"<<(PPC_CRId)bt<<", "<<(PPC_CRId)ba<<", "<<(PPC_CRId)bb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_crandc::PPC_crandc(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb){}

  void PPC_crandc::exec(PPC_Processor &proc) {
    if ((proc.cpu.cr & (1<<(31-ba))) && !(proc.cpu.cr & (1<<(31-bb))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_crandc::display(std::ostream& os) const {
    return os<<"crandc\t"<<(PPC_CRId)bt<<", "<<(PPC_CRId)ba<<", "<<(PPC_CRId)bb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_creqv::PPC_creqv(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_creqv::exec(PPC_Processor &proc) {
    if (((proc.cpu.cr & (1<<(31-ba))) && (proc.cpu.cr & (1<<(31-bb))))
        || (!(proc.cpu.cr & (1<<(31-ba))) && !(proc.cpu.cr & (1<<(31-bb)))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_creqv::display(std::ostream& os) const {
    return os<<"creqv\t"<<(PPC_CRId)bt<<", "<<(PPC_CRId)ba<<", "<<(PPC_CRId)bb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_crnand::PPC_crnand(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_crnand::exec(PPC_Processor &proc) {
    if ( !((proc.cpu.cr & (1<<(31-ba))) && (proc.cpu.cr & (1<<(31-bb)))) )
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_crnand::display(std::ostream& os) const {
    return os<<"crnand\t"<<(PPC_CRId)bt<<", "<<(PPC_CRId)ba<<", "<<(PPC_CRId)bb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_crnor::PPC_crnor(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_crnor::exec(PPC_Processor &proc) {
    if ( !((proc.cpu.cr & (1<<(31-ba))) | (proc.cpu.cr & (1<<(31-bb)))) )
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_crnor::display(std::ostream& os) const {
    return os<<"crnor\t"<<(PPC_CRId)bt<<", "<<(PPC_CRId)ba<<", "<<(PPC_CRId)bb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_cror::PPC_cror(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_cror::exec(PPC_Processor &proc) {
    if ( ((proc.cpu.cr & (1<<(31-ba))) | (proc.cpu.cr & (1<<(31-bb)))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_cror::display(std::ostream& os) const {
    return os<<"cror\t"<<(PPC_CRId)bt<<", "<<(PPC_CRId)ba<<", "<<(PPC_CRId)bb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_crorc::PPC_crorc(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_crorc::exec(PPC_Processor &proc) {
    if ((proc.cpu.cr & (1<<(31-ba))) || !(proc.cpu.cr & (1<<(31-bb))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_crorc::display(std::ostream& os) const {
    return os<<"crorc\t"<<(PPC_CRId)bt<<", "<<(PPC_CRId)ba<<", "<<(PPC_CRId)bb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_crxor::PPC_crxor(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_crxor::exec(PPC_Processor &proc) {
    if ((!(proc.cpu.cr & (1<<(31-ba))) && (proc.cpu.cr & (1<<(31-bb))))
        || ((proc.cpu.cr & (1<<(31-ba))) && !(proc.cpu.cr & (1<<(31-bb)))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_crxor::display(std::ostream& os) const {
    return os<<"crxor\t"<<(PPC_CRId)bt<<", "<<(PPC_CRId)ba<<", "<<(PPC_CRId)bb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divd::PPC_divd(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divd::exec(PPC_Processor &proc) {
    TODO("divd");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divd::display(std::ostream& os) const {
    return os<<"divd\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divd_::PPC_divd_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divd_::exec(PPC_Processor &proc) {
    TODO("divd_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divd_::display(std::ostream& os) const {
    return os<<"divd_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divdo::PPC_divdo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divdo::exec(PPC_Processor &proc) {
    TODO("divdo");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divdo::display(std::ostream& os) const {
    return os<<"divdo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divdo_::PPC_divdo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divdo_::exec(PPC_Processor &proc) {
    TODO("divdo_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divdo_::display(std::ostream& os) const {
    return os<<"divdo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divdu::PPC_divdu(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divdu::exec(PPC_Processor &proc) {
    TODO("divdu");

  }

  std::ostream& PPC_divdu::display(std::ostream& os) const {
    return os<<"divdu\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divdu_::PPC_divdu_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divdu_::exec(PPC_Processor &proc) {
    TODO("divdu_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divdu_::display(std::ostream& os) const {
  return os<<"divdu_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divduo::PPC_divduo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divduo::exec(PPC_Processor &proc) {
    TODO("divduo");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divduo::display(std::ostream& os) const {
    return os<<"divduo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divduo_::PPC_divduo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divduo_::exec(PPC_Processor &proc) {
    TODO("divduo_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divduo_::display(std::ostream& os) const {
    return os<<"divduo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divw::PPC_divw(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divw::exec(PPC_Processor &proc) {
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    int32_t a = proc.cpu.gpr[ra];
    int32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = a / b;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divw::display(std::ostream& os) const {
    return os<<"divw\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divw_::PPC_divw_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divw_::exec(PPC_Processor &proc) {
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    int32_t a = proc.cpu.gpr[ra];
    int32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = a / b;

    ppc_update_cr0(proc, rt);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divw_::display(std::ostream& os) const {
    return os<<"divw_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divwo::PPC_divwo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divwo::exec(PPC_Processor &proc) {
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    int32_t a = proc.cpu.gpr[ra];
    int32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = a / b;
    if(((a == 1<<31) && b==-1) || b==0)
    proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
   else
    proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divwo::display(std::ostream& os) const {
    return os<<"divwo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divwo_::PPC_divwo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divwo_::exec(PPC_Processor &proc) {
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    int32_t a = proc.cpu.gpr[ra];
    int32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = a / b;
    if(((a==1<<31) && (b==-1)) || b==0)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divwo_::display(std::ostream& os) const {
    return os<<"divwo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divwu::PPC_divwu(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divwu::exec(PPC_Processor &proc) {
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] / proc.cpu.gpr[rb];

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divwu::display(std::ostream& os) const {
    return os<<"divwu\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divwu_::PPC_divwu_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divwu_::exec(PPC_Processor &proc) {
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] / proc.cpu.gpr[rb];
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divwu_::display(std::ostream& os) const {
    return os<<"divwu_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divwuo::PPC_divwuo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb){}

  void PPC_divwuo::exec(PPC_Processor &proc) {
    uint32_t b = proc.cpu.gpr[rb];
    if (!b) {
      error()<<"div instruction invalid!\n";
    }

    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] / b;
    if(b==0)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divwuo::display(std::ostream& os) const {
    return os<<"divwuo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_divwuo_::PPC_divwuo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_divwuo_::exec(PPC_Processor &proc) {
    uint32_t b = proc.cpu.gpr[rb];
    if (!b) {
      error()<<"div instruction invalid!\n";
    }

    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] / b;
    if(b == 0)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_divwuo_::display(std::ostream& os) const {
    return os<<"divwuo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_eqv::PPC_eqv(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_eqv::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] ^ proc.cpu.gpr[rb]);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_eqv::display(std::ostream& os) const {
    return os<<"eqv\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_eqv_::PPC_eqv_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_eqv_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] ^ proc.cpu.gpr[rb]);

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_eqv_::display(std::ostream& os) const {
    return os<<"eqv_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_extsb::PPC_extsb(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_extsb::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    if (proc.cpu.gpr[ra] & 0x80)
      proc.cpu.gpr[ra] |= 0xffffff00;
    else
      proc.cpu.gpr[ra] &= ~0xffffff00;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_extsb::display(std::ostream& os) const {
    return os<<"extsb\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_extsb_::PPC_extsb_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_extsb_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    if (proc.cpu.gpr[ra] & 0x80)
      proc.cpu.gpr[ra] |= 0xffffff00;
    else
      proc.cpu.gpr[ra] &= ~0xffffff00;

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_extsb_::display(std::ostream& os) const {
    return os<<"extsb_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_extsh::PPC_extsh(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_extsh::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    if (proc.cpu.gpr[ra] & 0x8000)
      proc.cpu.gpr[ra] |= 0xffff0000;
    else
      proc.cpu.gpr[ra] &= ~0xffff0000;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_extsh::display(std::ostream& os) const {
    return os<<"extsh\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_extsh_::PPC_extsh_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_extsh_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    if (proc.cpu.gpr[ra] & 0x8000)
      proc.cpu.gpr[ra] |= 0xffff0000;
    else
      proc.cpu.gpr[ra] &= ~0xffff0000;

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_extsh_::display(std::ostream& os) const {
    return os<<"extsh_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_extsw::PPC_extsw(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_extsw::exec(PPC_Processor &proc) {
    TODO("extsw");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_extsw::display(std::ostream& os) const {
    return os<<"extsw\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_extsw_::PPC_extsw_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_extsw_::exec(PPC_Processor &proc) {
    TODO("extsw_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_extsw_::display(std::ostream& os) const {
    return os<<"extsw_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulhd::PPC_mulhd(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulhd::exec(PPC_Processor &proc) {
    TODO("mulhd");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulhd::display(std::ostream& os) const {
    return os<<"mulhd\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulhd_::PPC_mulhd_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulhd_::exec(PPC_Processor &proc) {
    TODO("mulhd_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulhd_::display(std::ostream& os) const {
    return os<<"mulhd_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulhdu::PPC_mulhdu(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulhdu::exec(PPC_Processor &proc) {
    TODO("mulhdu");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulhdu::display(std::ostream& os) const {
    return os<<"mulhdu\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulhdu_::PPC_mulhdu_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulhdu_::exec(PPC_Processor &proc) {
    TODO("mulhdu_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulhdu_::display(std::ostream& os) const {
    return os<<"mulhdu_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulhw::PPC_mulhw(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulhw::exec(PPC_Processor &proc) {
    int64_t a = (int32_t)proc.cpu.gpr[ra];
    int64_t b = (int32_t)proc.cpu.gpr[rb];
    int64_t c = a * b;
    proc.cpu.gpr[rt] = ((uint64_t) c) >> 32;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulhw::display(std::ostream& os) const {
    return os<<"mulhw\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulhw_::PPC_mulhw_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulhw_::exec(PPC_Processor &proc) {
    int64_t a = (int32_t)proc.cpu.gpr[ra];
    int64_t b = (int32_t)proc.cpu.gpr[rb];
    int64_t c = a * b;
    proc.cpu.gpr[rt] = ((uint64_t) c) >> 32;

    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulhw_::display(std::ostream& os) const {
    return os<<"mulhw_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulhwu_::PPC_mulhwu_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulhwu_::exec(PPC_Processor &proc) {
    uint64_t a = proc.cpu.gpr[ra];
    uint64_t b = proc.cpu.gpr[rb];
    uint64_t c = a * b;
    proc.cpu.gpr[rt] = c >> 32;

    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulhwu_::display(std::ostream& os) const {
    return os<<"mulhwu_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulhwu::PPC_mulhwu(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulhwu::exec(PPC_Processor &proc) {
    uint64_t a = proc.cpu.gpr[ra];
    uint64_t b = proc.cpu.gpr[rb];
    uint64_t c = a * b;
    proc.cpu.gpr[rt] = c >> 32;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulhwu::display(std::ostream& os) const {
    return os<<"mulhwu\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulld::PPC_mulld(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulld::exec(PPC_Processor &proc) {
    TODO("mulld");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulld::display(std::ostream& os) const {
    return os<<"mulld\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulld_::PPC_mulld_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulld_::exec(PPC_Processor &proc) {
    TODO("mulld_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulld_::display(std::ostream& os) const {
    return os<<"mulld_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulldo::PPC_mulldo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulldo::exec(PPC_Processor &proc) {
    TODO("mulldo");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulldo::display(std::ostream& os) const {
    return os<<"mulldo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulldo_::PPC_mulldo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mulldo_::exec(PPC_Processor &proc) {
    TODO("mulldo_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulldo_::display(std::ostream& os) const {
    return os<<"mulldo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mulli::PPC_mulli(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_mulli::exec(PPC_Processor &proc) {
    //signed / unsigned correct?
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] * d;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mulli::display(std::ostream& os) const {
    return os<<"mulli\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(int)d;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mullw::PPC_mullw(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mullw::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] * proc.cpu.gpr[rb];
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mullw::display(std::ostream& os) const {
    return os<<"mullw\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mullw_::PPC_mullw_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mullw_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] * proc.cpu.gpr[rb];

    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mullw_::display(std::ostream& os) const {
    return os<<"mullw_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mullwo::PPC_mullwo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mullwo::exec(PPC_Processor &proc) {
    int64_t temp = (int32_t)proc.cpu.gpr[ra] * (int32_t)proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = (uint32_t)temp;
    if (!(temp >> 31 == 0 || temp >> 31 == ~0ll ))
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mullwo::display(std::ostream& os) const {
    return os<<"mullwo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mullwo_::PPC_mullwo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mullwo_::exec(PPC_Processor &proc) {
    int64_t temp = (int32_t)proc.cpu.gpr[ra] * (int32_t)proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = (uint32_t)temp;

    ppc_update_cr0(proc, rt);
    if(!(temp >> 31 == 0 || temp >> 31 == ~0ll ))
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mullwo_::display(std::ostream& os) const {
    return os<<"mullwo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_nand::PPC_nand(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_nand::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] & proc.cpu.gpr[rb]);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_nand::display(std::ostream& os) const {
    return os<<"nand\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_nand_::PPC_nand_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_nand_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] & proc.cpu.gpr[rb]);

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_nand_::display(std::ostream& os) const {
    return os<<"nand_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_neg::PPC_neg(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_neg::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = -proc.cpu.gpr[ra];

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_neg::display(std::ostream& os) const {
    return os<<"neg\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_neg_::PPC_neg_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_neg_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = -proc.cpu.gpr[ra];

    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_neg_::display(std::ostream& os) const {
    return os<<"neg_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_nego::PPC_nego(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_nego::exec(PPC_Processor &proc) {
    uint32_t a=proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] = -a;
    if (a == 0x80000000)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;

  }

  std::ostream& PPC_nego::display(std::ostream& os) const {
    return os<<"nego\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_nego_::PPC_nego_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_nego_::exec(PPC_Processor &proc) {
    uint32_t a=proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] = -a;

    ppc_update_cr0(proc, rt);
    if (a == 0x80000000)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_nego_::display(std::ostream& os) const {
    return os<<"nego_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_nor::PPC_nor(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_nor::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] | proc.cpu.gpr[rb]);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_nor::display(std::ostream& os) const {
    return os<<"nor\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_nor_::PPC_nor_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_nor_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] | proc.cpu.gpr[rb]);

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_nor_::display(std::ostream& os) const {
    return os<<"nor_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_or::PPC_or(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_or::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | proc.cpu.gpr[rb];
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_or::display(std::ostream& os) const {
    return os<<"or\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_or_::PPC_or_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_or_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | proc.cpu.gpr[rb];

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_or_::display(std::ostream& os) const {
    return os<<"or_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_orc::PPC_orc(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_orc::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | ~ proc.cpu.gpr[rb];

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_orc::display(std::ostream& os) const {
    return os<<"orc\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_orc_::PPC_orc_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_orc_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | ~ proc.cpu.gpr[rb];

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_orc_::display(std::ostream& os) const {
    return os<<"orc_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_ori::PPC_ori(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_ori::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | d;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_ori::display(std::ostream& os) const {
    return os<<"ori\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(int)d;
  }


  /*----------------------------------------------------------------------------*/
  PPC_oris::PPC_oris(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_oris::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | (d<<16);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_oris::display(std::ostream& os) const {
    return os<<"oris\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(int)d;
  }


  /*----------------------------------------------------------------------------*/
  PPC_rldcl::PPC_rldcl(uint8_t _rs, uint8_t _ra, uint8_t _rb, uint8_t _mb):
    rs(_rs), ra(_ra), rb(_rb), mb(_mb) {}

  void PPC_rldcl::exec(PPC_Processor &proc) {
    TODO("rldcl");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldcl::display(std::ostream& os) const {
    return os<<"rldcl\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<(PPC_AsmId)rb<<", "<<"MB";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldcl_::PPC_rldcl_(uint8_t _rs, uint8_t _ra, uint8_t _rb, uint8_t _mb):
    rs(_rs), ra(_ra), rb(_rb), mb(_mb) {}

  void PPC_rldcl_::exec(PPC_Processor &proc) {
    TODO("rldcl_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldcl_::display(std::ostream& os) const {
    return os<<"rldcl_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<(PPC_AsmId)rb<<", "<<"MB";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldcr::PPC_rldcr(uint8_t _rs, uint8_t _ra, uint8_t _rb, uint8_t _mb):
    rs(_rs), ra(_ra), rb(_rb), mb(_mb) {}

  void PPC_rldcr::exec(PPC_Processor &proc) {
    TODO("rldcr");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldcr::display(std::ostream& os) const {
    return os<<"rldcr\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<(PPC_AsmId)rb<<", "<<"MB";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldcr_::PPC_rldcr_(uint8_t _rs, uint8_t _ra, uint8_t _rb, uint8_t _mb):
    rs(_rs), ra(_ra), rb(_rb), mb(_mb) {}

  void PPC_rldcr_::exec(PPC_Processor &proc) {
    TODO("rldcr_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldcr_::display(std::ostream& os) const {
    return os<<"rldcr_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<(PPC_AsmId)rb<<", "<<"MB";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldic::PPC_rldic(uint8_t _rs, uint8_t _ra, uint8_t _sh, uint8_t _mb):
    rs(_rs), ra(_ra), sh(_sh), mb(_mb) {}

  void PPC_rldic::exec(PPC_Processor &proc) {
    TODO("rldic");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldic::display(std::ostream& os) const {
    return os<<"rldic\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"MB, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldic_::PPC_rldic_(uint8_t _rs, uint8_t _ra, uint8_t _sh, uint8_t _mb):
    rs(_rs), ra(_ra), sh(_sh), mb(_mb) {}

  void PPC_rldic_::exec(PPC_Processor &proc) {
    TODO("rldic_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldic_::display(std::ostream& os) const {
    return os<<"rldic_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"MB, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldicl::PPC_rldicl(uint8_t _rs, uint8_t _ra, uint8_t _sh, uint8_t _mb):
    rs(_rs), ra(_ra), sh(_sh), mb(_mb) {}

  void PPC_rldicl::exec(PPC_Processor &proc) {
    TODO("rldicl");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldicl::display(std::ostream& os) const {
    return os<<"rldicl\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"MB";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldicl_::PPC_rldicl_(uint8_t _rs, uint8_t _ra, uint8_t _sh, uint8_t _mb):
    rs(_rs), ra(_ra), sh(_sh), mb(_mb) {}

  void PPC_rldicl_::exec(PPC_Processor &proc) {
    TODO("rldicl_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldicl_::display(std::ostream& os) const {
    return os<<"rldicl_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"MB";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldicr::PPC_rldicr(uint8_t _rs, uint8_t _ra, uint8_t _sh, uint8_t _mb):
    rs(_rs), ra(_ra), sh(_sh), mb(_mb) {}

  void PPC_rldicr::exec(PPC_Processor &proc) {
    TODO("rldicr");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldicr::display(std::ostream& os) const {
    return os<<"rldicr\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldicr_::PPC_rldicr_(uint8_t _rs, uint8_t _ra, uint8_t _sh, uint8_t _mb):
    rs(_rs), ra(_ra), sh(_sh), mb(_mb) {}

  void PPC_rldicr_::exec(PPC_Processor &proc) {
    TODO("rldicr_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldicr_::display(std::ostream& os) const {
    return os<<"rldicr_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldimi::PPC_rldimi(uint8_t _rs, uint8_t _ra, uint8_t _sh, uint8_t _mb):
    rs(_rs), ra(_ra), sh(_sh), mb(_mb) {}

  void PPC_rldimi::exec(PPC_Processor &proc) {
    TODO("rldimi");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldimi::display(std::ostream& os) const {
    return os<<"rldimi\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rldimi_::PPC_rldimi_(uint8_t _rs, uint8_t _ra, uint8_t _sh, uint8_t _mb):
    rs(_rs), ra(_ra), sh(_sh), mb(_mb) {}

  void PPC_rldimi_::exec(PPC_Processor &proc) {
    TODO("rldimi_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rldimi_::display(std::ostream& os) const {
    return os<<"rldimi_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rlwimi::PPC_rlwimi(uint8_t _rs, uint8_t _ra, uint8_t _rb, uint8_t _mb, uint8_t _me):
    rs(_rs), ra(_ra), rb(_rb), mb(_mb), me(_me) {}

  void PPC_rlwimi::exec(PPC_Processor &proc) {
    uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs], rb);
    uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = (v & mask) | (proc.cpu.gpr[ra] & ~mask);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rlwimi::display(std::ostream& os) const {
    return os<<"rlwimi\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"MB, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rlwimi_::PPC_rlwimi_(uint8_t _rs, uint8_t _ra, uint8_t _rb, uint8_t _mb, uint8_t _me):
    rs(_rs), ra(_ra), rb(_rb), mb(_mb), me(_me) {}

  void PPC_rlwimi_::exec(PPC_Processor &proc) {
    uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs], rb);
    uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = (v & mask) | (proc.cpu.gpr[ra] & ~mask);

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rlwimi_::display(std::ostream& os) const {
    return os<<"rlwimi_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"MB, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rlwinm::PPC_rlwinm(uint8_t _rs, uint8_t _ra, uint8_t _rb, uint8_t _mb, uint8_t _me):
    rs(_rs), ra(_ra), rb(_rb), mb(_mb), me(_me) {}

  void PPC_rlwinm::exec(PPC_Processor &proc) {
    uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs], rb);
    uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = v & mask;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rlwinm::display(std::ostream& os) const {
    return os<<"rlwinm\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<(int)rb<<", "<<(int)mb<<", "<<(int)me;
  }

  /*----------------------------------------------------------------------------*/
  PPC_rlwinm_::PPC_rlwinm_(uint8_t _rs, uint8_t _ra, uint8_t _rb, uint8_t _mb, uint8_t _me):
    rs(_rs), ra(_ra), rb(_rb), mb(_mb), me(_me) {}

  void PPC_rlwinm_::exec(PPC_Processor &proc) {
    uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs], rb);
    uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = v & mask;

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rlwinm_::display(std::ostream& os) const {
    return os<<"rlwinm_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH, "<<"MB, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rlwnm::PPC_rlwnm(uint8_t _rs, uint8_t _ra, uint8_t _rb, uint8_t _mb, uint8_t _me):
    rs(_rs), ra(_ra), rb(_rb), mb(_mb), me(_me) {}

  void PPC_rlwnm::exec(PPC_Processor &proc) {
    uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs], proc.cpu.gpr[rb]);
    uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = v & mask;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rlwnm::display(std::ostream& os) const {
    return os<<"rlwnm\t"<<(PPC_AsmId)rs<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb<<", "<<"MB, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_rlwnm_::PPC_rlwnm_(uint8_t _rs, uint8_t _ra, uint8_t _rb, uint8_t _mb, uint8_t _me):
    rs(_rs), ra(_ra), rb(_rb), mb(_mb), me(_me) {}

  void PPC_rlwnm_::exec(PPC_Processor &proc) {
    uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs], proc.cpu.gpr[rb]);
    uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = v & mask;

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_rlwnm_::display(std::ostream& os) const {
    return os<<"rlwnm_\t"<<(PPC_AsmId)rs<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb<<", "<<"MB, "<<"ME";
  }

  /*----------------------------------------------------------------------------*/
  PPC_sld::PPC_sld(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_sld::exec(PPC_Processor &proc) {
    TODO("sld");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sld::display(std::ostream& os) const {
    return os<<"sld\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_sld_::PPC_sld_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_sld_::exec(PPC_Processor &proc) {
    TODO("sld_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sld_::display(std::ostream& os) const {
    return os<<"sld_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_slw::PPC_slw(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_slw::exec(PPC_Processor &proc) {
    uint32_t s = proc.cpu.gpr[rb] & 0x3f;
    if (s > 31)
      proc.cpu.gpr[ra] = 0;
    else
      proc.cpu.gpr[ra] = proc.cpu.gpr[rt] << s;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_slw::display(std::ostream& os) const {
    return os<<"slw\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_slw_::PPC_slw_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_slw_::exec(PPC_Processor &proc) {
    uint32_t s = proc.cpu.gpr[rb] & 0x3f;
    if (s > 31)
      proc.cpu.gpr[ra] = 0;
    else
      proc.cpu.gpr[ra] = proc.cpu.gpr[rt] << s;

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_slw_::display(std::ostream& os) const {
    return os<<"slw_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_srad::PPC_srad(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_srad::exec(PPC_Processor &proc) {
    TODO("srad");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_srad::display(std::ostream& os) const {
    return os<<"srad\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_srad_::PPC_srad_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_srad_::exec(PPC_Processor &proc) {
    TODO("srad_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_srad_::display(std::ostream& os) const {
    return os<<"srad_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_sradi::PPC_sradi(uint8_t _rs, uint8_t _ra, uint8_t _sh):
    rs(_rs), ra(_ra), sh(_sh) {}

  void PPC_sradi::exec(PPC_Processor &proc) {
    TODO("sradi");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sradi::display(std::ostream& os) const {
    return os<<"sradi\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH";
  }

  /*----------------------------------------------------------------------------*/
  PPC_sradi_::PPC_sradi_(uint8_t _rs, uint8_t _ra, uint8_t _sh):
    rs(_rs), ra(_ra), sh(_sh) {}

  void PPC_sradi_::exec(PPC_Processor &proc) {
    TODO("sradi_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sradi_::display(std::ostream& os) const {
    return os<<"sradi_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rs<<", "<<"SH";
  }

  /*----------------------------------------------------------------------------*/
  PPC_sraw::PPC_sraw(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_sraw::exec(PPC_Processor &proc) {
    uint32_t SH = proc.cpu.gpr[rb] & 0x3f;
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    proc.cpu.xer &= ~XER_CA;
    if (proc.cpu.gpr[ra] & 0x80000000) {
      uint32_t ca = 0;
      for (uint32_t i = 0; i < SH; i++) {
        if (proc.cpu.gpr[ra] & 1)
          ca = 1;
        proc.cpu.gpr[ra] >>= 1;
        proc.cpu.gpr[ra] |= 0x80000000;
      }
      if (ca) proc.cpu.xer |= XER_CA;

    } else {
      if (SH > 31)
        proc.cpu.gpr[ra] = 0;
      else
        proc.cpu.gpr[ra] >>= SH;
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sraw::display(std::ostream& os) const {
    return os<<"sraw\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_sraw_::PPC_sraw_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_sraw_::exec(PPC_Processor &proc) {
    uint32_t SH = proc.cpu.gpr[rb] & 0x3f;
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    proc.cpu.xer &= ~XER_CA;
    if (proc.cpu.gpr[ra] & 0x80000000) {
      uint32_t ca = 0;
      for (uint32_t i = 0; i < SH; i++) {
        if (proc.cpu.gpr[ra] & 1)
          ca = 1;
        proc.cpu.gpr[ra] >>= 1;
        proc.cpu.gpr[ra] |= 0x80000000;
      }
      if (ca) proc.cpu.xer |= XER_CA;

    } else {
      if (SH > 31)
        proc.cpu.gpr[ra] = 0;
      else
        proc.cpu.gpr[ra] >>= SH;
    }

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sraw_::display(std::ostream& os) const {
    return os<<"sraw_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_srawi::PPC_srawi(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_srawi::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    proc.cpu.xer &= ~XER_CA;
    if (proc.cpu.gpr[ra] & 0x80000000) {
      uint32_t ca = 0;
      for (uint32_t i = 0; i < rb; i++) {
        if (proc.cpu.gpr[ra] & 1)
          ca = 1;
        proc.cpu.gpr[ra] >>= 1;
        proc.cpu.gpr[ra] |= 0x80000000;
      }
      if (ca) proc.cpu.xer |= XER_CA;

    } else {
      if (rb > 31)
        proc.cpu.gpr[ra] = 0;
      else
        proc.cpu.gpr[ra] >>= rb;
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_srawi::display(std::ostream& os) const {
    return os<<"srawi\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<"SH";
  }

  /*----------------------------------------------------------------------------*/
  PPC_srawi_::PPC_srawi_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_srawi_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    proc.cpu.xer &= ~XER_CA;
    if (proc.cpu.gpr[ra] & 0x80000000) {
      uint32_t ca = 0;
      for (uint32_t i = 0; i < rb; i++) {
        if (proc.cpu.gpr[ra] & 1)
          ca = 1;
        proc.cpu.gpr[ra] >>= 1;
        proc.cpu.gpr[ra] |= 0x80000000;
      }
      if (ca) proc.cpu.xer |= XER_CA;

    } else {
      if (rb > 31)
        proc.cpu.gpr[ra] = 0;
      else
        proc.cpu.gpr[ra] >>= rb;
    }
    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_srawi_::display(std::ostream& os) const {
    return os<<"srawi_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<"SH";
  }

  /*----------------------------------------------------------------------------*/
  PPC_srd::PPC_srd(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_srd::exec(PPC_Processor &proc) {
    TODO("srd");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_srd::display(std::ostream& os) const {
    return os<<"srd\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_srd_::PPC_srd_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_srd_::exec(PPC_Processor &proc) {
    TODO("srd_");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_srd_::display(std::ostream& os) const {
    return os<<"srd_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_srw::PPC_srw(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_srw::exec(PPC_Processor &proc) {
    uint32_t v = proc.cpu.gpr[rb] & 0x3f;
    if (v > 31)
      proc.cpu.gpr[ra] = 0;
    else
      proc.cpu.gpr[ra] = proc.cpu.gpr[rt] >> v;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_srw::display(std::ostream& os) const {
    return os<<"srw\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_srw_::PPC_srw_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_srw_::exec(PPC_Processor &proc) {
    uint32_t v = proc.cpu.gpr[rb] & 0x3f;
    if (v > 31)
      proc.cpu.gpr[ra] = 0;
    else
      proc.cpu.gpr[ra] = proc.cpu.gpr[rt] >> v;

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_srw_::display(std::ostream& os) const {
    return os<<"srw_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subf::PPC_subf(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subf::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = ~proc.cpu.gpr[ra] + proc.cpu.gpr[rb] + 1;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subf::display(std::ostream& os) const {
    return os<<"subf\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subf_::PPC_subf_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subf_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = ~proc.cpu.gpr[ra] + proc.cpu.gpr[rb] + 1;

    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subf_::display(std::ostream& os) const {
    return os<<"subf_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfo::PPC_subfo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfo::exec(PPC_Processor &proc) {
    uint32_t a=proc.cpu.gpr[ra];
    uint32_t b=proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ~a + b + 1;
    if((b^a)&(b^proc.cpu.gpr[rt])>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfo::display(std::ostream& os) const {
    return os<<"subfo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfo_::PPC_subfo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfo_::exec(PPC_Processor &proc) {
    uint32_t a=proc.cpu.gpr[ra];
    uint32_t b=proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ~a + b + 1;
    if((b^a)&(b^proc.cpu.gpr[rt])>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfo_::display(std::ostream& os) const {
    return os<<"subfo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfc::PPC_subfc(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfc::exec(PPC_Processor &proc) {
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ~a + b + 1;
    // update xer
    if (ppc_carry(~a, b, 1))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfc::display(std::ostream& os) const {
    return os<<"subfc\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfc_::PPC_subfc_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfc_::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ~a + b + 1;
    // update xer
    if (ppc_carry(~a, b, 1))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfc_::display(std::ostream& os) const {
    return os<<"subfc_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfco::PPC_subfco(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfco::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ~a + b + 1;
    // update xer
    if (ppc_carry(~a, b, 1))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((b^a)&(b^proc.cpu.gpr[rt])>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfco::display(std::ostream& os) const {
    return os<<"subfco\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfco_::PPC_subfco_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfco_::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ~a + b + 1;
    // update xer
    if (ppc_carry(~a, b, 1))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((b^a)&(b^proc.cpu.gpr[rt])>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfco_::display(std::ostream& os) const {
    return os<<"subfco_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfe::PPC_subfe(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfe::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t b = proc.cpu.gpr[rb];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + b + ca;

    // update xer
    if (ppc_carry(~a, b, ca)) {
      proc.cpu.xer |= XER_CA;
    } else {
      proc.cpu.xer &= ~XER_CA;	}

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfe::display(std::ostream& os) const {
    return os<<"subfe\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfe_::PPC_subfe_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfe_::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t b = proc.cpu.gpr[rb];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + b + ca;

    // update xer
    if (ppc_carry(~a, b, ca))
      {
        proc.cpu.xer |= XER_CA;
      }
    else
      {proc.cpu.xer &= ~XER_CA;}
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfe_::display(std::ostream& os) const {
    return os<<"subfe_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfeo::PPC_subfeo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfeo::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t b = proc.cpu.gpr[rb];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + b + ca;

    // update xer
    if (ppc_carry(~a, b, ca)) {
      proc.cpu.xer |= XER_CA;
    } else {
      proc.cpu.xer &= ~XER_CA;	}
    if((b^(a+ca))&(b^proc.cpu.gpr[rt])>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfeo::display(std::ostream& os) const {
    return os<<"subfeo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfeo_::PPC_subfeo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfeo_::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t b = proc.cpu.gpr[rb];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + b + ca;

    // update xer
    if (ppc_carry(~a, b, ca)) {
      proc.cpu.xer |= XER_CA;
    } else {
      proc.cpu.xer &= ~XER_CA;	}

    if((b^(a+ca))&(b^proc.cpu.gpr[rt])>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfeo_::display(std::ostream& os) const {
    return os<<"subfeo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfic::PPC_subfic(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_subfic::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] = ~a + d + 1;

    // update XER
    if (ppc_carry(~a, d, 1))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfic::display(std::ostream& os) const {
    return os<<"subfic\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(int)d;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfme::PPC_subfme(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfme::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca + 0xffffffff;

    // update XER
    if ((a!=0xffffffff) || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfme::display(std::ostream& os) const {
    return os<<"subfme\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfme_::PPC_subfme_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfme_::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca + 0xffffffff;

    // update XER
    if ((a!=0xffffffff) || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;


    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfme_::display(std::ostream& os) const {
    return os<<"subfme_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfmeo::PPC_subfmeo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfmeo::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca + 0xffffffff;

    // update XER
    if ((a!=0xffffffff) || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ca^(a+0xffffffff))&(ca^(proc.cpu.gpr[rt]+1))>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfmeo::display(std::ostream& os) const {
    return os<<"subfmeo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfmeo_::PPC_subfmeo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfmeo_::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca + 0xffffffff;

    // update XER
    if ((a!=0xffffffff) || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ca^(a+0xffffffff))&(ca^(proc.cpu.gpr[rt]+1))>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~ XER_OV;
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfmeo_::display(std::ostream& os) const {
    return os<<"subfmeo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfze::PPC_subfze(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfze::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca;

    // update XER
    if (!a && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfze::display(std::ostream& os) const {
    return os<<"subfze\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfze_::PPC_subfze_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfze_::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca;

    // update XER
    if (!a && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfze_::display(std::ostream& os) const {
    return os<<"subfze_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfzeo::PPC_subfzeo(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfzeo::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca;

    // update XER
    if (!a && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ca^a)&(ca^(proc.cpu.gpr[rt]+1))>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfzeo::display(std::ostream& os) const {
    return os<<"subfzeo\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_subfzeo_::PPC_subfzeo_(uint8_t _rt, uint8_t _ra, uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_subfzeo_::exec(PPC_Processor &proc) {
    uint32_t a = proc.cpu.gpr[ra];
    uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca;

    // update XER
    if (!a && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ca^a)&(ca^(proc.cpu.gpr[rt]+1))>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_subfzeo_::display(std::ostream& os) const {
    return os<<"subfzeo_\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_xor::PPC_xor(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_xor::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] ^ proc.cpu.gpr[rb];

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_xor::display(std::ostream& os) const {
    return os<<"xor\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_xor_::PPC_xor_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_xor_::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] ^ proc.cpu.gpr[rb];

    ppc_update_cr0(proc, ra);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_xor_::display(std::ostream& os) const {
    return os<<"xor_\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_xori::PPC_xori(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_xori::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] ^ d;

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_xori::display(std::ostream& os) const {
    return os<<"xori\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(int)d;
  }


  /*----------------------------------------------------------------------------*/
  PPC_xoris::PPC_xoris(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_xoris::exec(PPC_Processor &proc) {
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] ^ (d <<16);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_xoris::display(std::ostream& os) const {
    return os<<"xoris\t"<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rt<<", "<<(int)d;
  }

} // namespace simsoc
