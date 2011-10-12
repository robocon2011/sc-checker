//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/processors/ppc/ppc_processor.hpp"
#include "libsimsoc/processors/ppc/ppcis_fpu.hpp"

namespace simsoc {

  /*----------------------------------------------------------------------------*/
  PPC_fabs::PPC_fabs(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_fabs::exec(PPC_Processor &proc) {
    //The contents of frB with bit 0 cleared are placed into frD
    //does not alter FPSCR,treats NaNs like any other kind of value
    proc.fp_unit.check_fp_enabled();
    const uint64_t sign_mask = (uint64_t)1<<63;
    proc.cpu.fpr[rt] = proc.cpu.fpr[rb] & ~sign_mask;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fabs::display(std::ostream& os) const {
    return os<<"fabs\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)ra;
  }

  PPC_fabs_::PPC_fabs_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_fabs_::exec(PPC_Processor &proc) {
    //does not alter FPSCR,treats NaNs like any other kind of value
    //CR1 Affected: FX,FEX,VX,OX
    proc.fp_unit.check_fp_enabled();
    const uint64_t sign_mask = (uint64_t)1<<63;
    proc.cpu.fpr[rt] = proc.cpu.fpr[rb] & ~sign_mask;
    proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fabs_::display(std::ostream& os) const {
    return os<<"fabs.\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_fcfid::PPC_fcfid(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_fcfid::exec(PPC_Processor &proc) {
    TODO("fcfid");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fcfid::display(std::ostream& os) const {
    return os<<"fcfid\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)ra;
  }

  PPC_fcfid_::PPC_fcfid_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_fcfid_::exec(PPC_Processor &proc) {
    TODO("fcfid.");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fcfid_::display(std::ostream& os) const {
    return os<<"fcfid.\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)ra;
  }

  /*----------------------------------------------------------------------------*/
  PPC_fmr::PPC_fmr(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_fmr::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    proc.cpu.fpr[rt] = proc.cpu.fpr[rb];
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fmr::display(std::ostream& os) const {
    return os<<"fmr\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)rb;
  }

  PPC_fmr_::PPC_fmr_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_fmr_::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    //CR1 Affected: FX,FEX,VX,OX
    proc.cpu.fpr[rt] = proc.cpu.fpr[rb];
    proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fmr_::display(std::ostream& os) const {
    return os<<"fmr.\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_fnabs::PPC_fnabs(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_fnabs::exec(PPC_Processor &proc) {
    //treats NaNs just like any other kind of value
    proc.fp_unit.check_fp_enabled();
    const uint64_t sign_mask = (uint64_t)1<<63;
    proc.cpu.fpr[rt] = proc.cpu.fpr[rb] | sign_mask;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fnabs_::display(std::ostream& os) const {
    return os<<"fnabs\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)rb;
  }

  PPC_fnabs_::PPC_fnabs_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_fnabs_::exec(PPC_Processor &proc) {
    //CR1 Affected: FX,FEX,VX,OX
    //treats NaNs just like any other kind of value
    proc.fp_unit.check_fp_enabled();
    const uint64_t sign_mask = (uint64_t)1<<63;
    proc.cpu.fpr[rt] = proc.cpu.fpr[rb] | sign_mask;
    proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fnabs::display(std::ostream& os) const {
    return os<<"fnabs.\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_fneg::PPC_fneg(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_fneg::exec(PPC_Processor &proc) {
    //treats NaNs just like any other kind of value
    proc.fp_unit.check_fp_enabled();
    const uint64_t sign_mask = (uint64_t)1<<63;
    proc.cpu.fpr[rt] = proc.cpu.fpr[rb] & sign_mask?
      proc.cpu.fpr[rb] & ~sign_mask
      :proc.cpu.fpr[rb] | sign_mask;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fneg_::display(std::ostream& os) const {
    return os<<"fneg\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)rb;
  }

  PPC_fneg_::PPC_fneg_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_fneg_::exec(PPC_Processor &proc) {
    //treats NaNs just like any other kind of value
    proc.fp_unit.check_fp_enabled();
    const uint64_t sign_mask = (uint64_t)1<<63;
    proc.cpu.fpr[rt] = proc.cpu.fpr[rb] & sign_mask?
      proc.cpu.fpr[rb] & ~sign_mask
      :proc.cpu.fpr[rb] | sign_mask;
    proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fneg::display(std::ostream& os) const {
    return os<<"fneg.\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_fres::PPC_fres(uint8_t _frt, uint8_t _fra, uint8_t _frb, uint8_t _frc):
    frt(_frt), fra(_fra), frb(_frb), frc(_frc) {}

  void PPC_fres::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    TODO("Graphics group instruction: fres");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fres_::display(std::ostream& os) const {
    return os<<"fres\tfr"<<std::dec<<(int)frt<<", "<<"fr"<<(int)frb;
  }

  PPC_fres_::PPC_fres_(uint8_t _frt, uint8_t _fra, uint8_t _frb, uint8_t _frc):
    frt(_frt), fra(_fra), frb(_frb), frc(_frc) {}

  void PPC_fres_::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    TODO("Graphics group instruction: fres.");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fres::display(std::ostream& os) const {
    return os<<"fres.\tfr"<<std::dec<<(int)frt<<", "<<"fr"<<(int)frb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_frsp::PPC_frsp(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_frsp::exec(PPC_Processor &proc) {
    //Floating Round to Single
    //FPSCR Affected: FPRF,FR,FI,FX,OX,UX,XX,VXSNAN
    proc.fp_unit.check_fp_enabled();
    fp_t frb(proc.cpu.fpr[rb]),frd(Single);
    if(frb.is_nan()){
      fp_excp_status status = NOEXCP;
      if((status = proc.fp_unit.check_invalid_operand(FRND,frb))
         == ENABLED_EXCP){
        proc.info()<<"raise fp enabled exception"<<endl;
        return;//instruction supressed, frD unchanged
      }
      if(frb.is_nan())
        proc.cpu.fpr[rt] = proc.cpu.fpr[rb] & 0xFFFFFFFFE0000000ULL;
      else if(status==DISABLED_EXCP)
        proc.cpu.fpr[rt] = QNAN_VALUE;

      proc.fp_unit.fpscr.set_fi(false);
      proc.fp_unit.fpscr.set_fr(false);
      proc.fp_unit.fpscr.set_fprf(QNAN);
      proc.cpu.pc += 4;
      return;
    }
    mpfr_clear_flags();
    int inext=mpfr_set(*frd,*frb,proc.fp_unit.rnd_mode());
    if(frd.is_zero() || frd.is_inf()){
      proc.fp_unit.handle_nonregular_result(frd,inext);
      proc.cpu.fpr[rt]=frd.get_value();
      proc.cpu.pc += 4;
      return;
    }else{
      proc.fp_unit.handle_regular_result(frd,inext);
      proc.cpu.fpr[rt]=frd.get_value();
      if(proc.fp_unit.fp_exception_enabled()){
        proc.info()<<"raise fp enabled exception"<<endl;
      }else{
        proc.cpu.pc += 4;
        return;
      }
    }
  }

  std::ostream& PPC_frsp_::display(std::ostream& os) const {
    return os<<"frsp\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)rb;
  }

  PPC_frsp_::PPC_frsp_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_frsp_::exec(PPC_Processor &proc) {
    //Floating Round to Single
    //CR1 Affected: FX, FEX, VX, OX
    //FPSCR Affected: FPRF,FR,FI,FX,OX,UX,XX,VXSNAN
    proc.fp_unit.check_fp_enabled();
    fp_t frb(proc.cpu.fpr[rb]),frd(Single);
    if(frb.is_nan()){
      fp_excp_status status = NOEXCP;
      if((status = proc.fp_unit.check_invalid_operand(FRND,frb))
         == ENABLED_EXCP){
        proc.info()<<"raise fp enabled exception"<<endl;
        return;//instruction supressed, frD unchanged
      }

      if(frb.is_nan())
        proc.cpu.fpr[rt] = proc.cpu.fpr[rb] & 0xFFFFFFFFE0000000ULL;
      else if(status==DISABLED_EXCP)
        proc.cpu.fpr[rt] = QNAN_VALUE;

      proc.fp_unit.fpscr.set_fi(false);
      proc.fp_unit.fpscr.set_fr(false);
      proc.fp_unit.fpscr.set_fprf(QNAN);
      proc.fp_unit.update_CR1();
      proc.cpu.pc += 4;
      return;
    }
    mpfr_clear_flags();
    int inext=mpfr_set(*frd,*frb,proc.fp_unit.rnd_mode());
    if(frd.is_zero() || frd.is_inf()){
      proc.fp_unit.handle_nonregular_result(frd,inext);
      proc.cpu.fpr[rt]=frd.get_value();
      proc.fp_unit.update_CR1();
      proc.cpu.pc += 4;
      return;
    }else{
      proc.fp_unit.handle_regular_result(frd,inext);
      proc.cpu.fpr[rt]=frd.get_value();
      proc.fp_unit.update_CR1();
      if(proc.fp_unit.fp_exception_enabled()){
        proc.info()<<"raise fp enabled exception"<<endl;
      }else{
        proc.cpu.pc += 4;
        return;
      }
    }
  }

  std::ostream& PPC_frsp::display(std::ostream& os) const {
    return os<<"frsp.\tfr"<<std::dec<<(int)rt<<", "<<"fr"<<(int)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_frsqrte::PPC_frsqrte(uint8_t _frt, uint8_t _fra, uint8_t _frb, uint8_t _frc):
    frt(_frt), fra(_fra), frb(_frb), frc(_frc) {}

  void PPC_frsqrte::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    TODO("Graphics group instruction: frsqrte");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_frsqrte_::display(std::ostream& os) const {
    return os<<"frsqrte\tfr"<<std::dec<<(int)frt<<", "<<"fr"<<(int)frb;
  }

  PPC_frsqrte_::PPC_frsqrte_(uint8_t _frt, uint8_t _fra, uint8_t _frb, uint8_t _frc):
    frt(_frt), fra(_fra), frb(_frb), frc(_frc) {}

  void PPC_frsqrte_::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    TODO("Graphics group instruction: frsqrte");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_frsqrte::display(std::ostream& os) const {
    return os<<"frsqrte.\tfr"<<std::dec<<(int)frt<<", "<<"fr"<<(int)frb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_fsel::PPC_fsel(uint8_t _frt, uint8_t _fra, uint8_t _frb, uint8_t _frc):
    frt(_frt), fra(_fra), frb(_frb), frc(_frc) {}

  void PPC_fsel::exec(PPC_Processor &proc) {
    //Floating Select
    proc.fp_unit.check_fp_enabled();
    fp_t fa(proc.cpu.fpr[fra]),fzero(0.0);
    mpfr_clear_flags();
    int result=mpfr_cmp(*fa,*fzero);
    if(result<0 || mpfr_erangeflag_p()/* equal to result==0 & NaN */){
      proc.cpu.fpr[frt] = proc.cpu.fpr[frb];
      debug()<<"select fr"<<std::dec<<(int)frb<<endl;
    }else{/*result>=0*/
      proc.cpu.fpr[frt] = proc.cpu.fpr[frc];
      debug()<<"select fr"<<std::dec<<(int)frc<<endl;
    }
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fsel::display(std::ostream& os) const {
    return os<<"fsel\tfr"<<std::dec<<(int)frt<<", "<<"fr"<<(int)fra<<", "<<"fr"<<(int)frc<<", "<<"fr"<<(int)frb;
  }

  PPC_fsel_::PPC_fsel_(uint8_t _frt, uint8_t _fra, uint8_t _frb, uint8_t _frc):
    frt(_frt), fra(_fra), frb(_frb), frc(_frc) {}

  void PPC_fsel_::exec(PPC_Processor &proc) {
    //Floating Select
    //CR1 Affected: FX, FEX, VX, OX
    proc.fp_unit.check_fp_enabled();
    fp_t fa(proc.cpu.fpr[fra]),fzero(0.0);
    mpfr_clear_flags();
    int result=mpfr_cmp(*fa,*fzero);
    if(result<0 || mpfr_erangeflag_p()/* result==0 & NaN */){
      proc.cpu.fpr[frt] = proc.cpu.fpr[frb];
      debug()<<"select fr"<<std::dec<<(int)frb<<endl;
    }else{/*result>=0*/
      proc.cpu.fpr[frt] = proc.cpu.fpr[frc];
      debug()<<"select fr"<<std::dec<<(int)frc<<endl;
    }
    proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_fsel_::display(std::ostream& os) const {
    return os<<"fsel.\tfr"<<std::dec<<(int)frt<<", "<<"fr"<<(int)fra<<", "<<"fr"<<(int)frc<<", "<<"fr"<<(int)frb;
  }

} // namespace simsoc
