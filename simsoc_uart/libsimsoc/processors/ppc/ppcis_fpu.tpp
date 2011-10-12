// implementation of template classes declared in ppcis_fpu.hpp
#include "ppc_tool.hpp"

namespace simsoc {

  template <class op>
  void PPC_FPArithmetic<op>::exec(PPC_Processor &proc){
    proc.fp_unit.check_fp_enabled();

    fp_t frd,frop1(proc.cpu.fpr[op1]),frop2(proc.cpu.fpr[op2]);

    if(op::single_prec_operation){
      //if single operand is not fit single-precision. result is undefined
      if(!frop1.fit_single_format() || !frop2.fit_single_format()){
        error()<<"Source operands not representable in single-precision format.";
        error()<<"Result undefined"<<endl;
        exit(1);
      }
      frd.set_prec(Single);
      frop1.set_prec(Single);
      frop2.set_prec(Single);
    }

    mpfr_clear_flags();
    int inext=op::compute(frd,frop1,frop2,proc.fp_unit.rnd_mode());
    assert(mpfr_overflow_p()==0 && mpfr_underflow_p()==0);

    if(frd.is_nan()){
      debug()<<"nan result! check for invalide operand exception!"<<endl;
      fp_excp_status status = NOEXCP;
      if((status = proc.fp_unit.check_invalid_operand(op::type(),frop1,frop2))
         == ENABLED_EXCP){
        info()<<"raise fp enabled exception"<<endl;
        return;//instruction supressed, frD unchanged
      }

      debug()<<"nan operand in source "<<endl;
      if(frop1.is_nan())
        proc.cpu.fpr[rd] = proc.cpu.fpr[op1];
      else if(frop2.is_nan())
        proc.cpu.fpr[rd] = proc.cpu.fpr[op2];
      else if(status==DISABLED_EXCP)
        proc.cpu.fpr[rd] = QNAN_VALUE;

      proc.fp_unit.fpscr.set_fi(false);
      proc.fp_unit.fpscr.set_fr(false);
      proc.fp_unit.fpscr.set_fprf(QNAN);

      if(op::rc)
        proc.fp_unit.update_CR1();

      proc.cpu.pc += 4;
      return;
    }else if(frd.is_zero() || frd.is_inf()){
      if(op::type() == FDIV){
        fp_excp_status status = NOEXCP;
        if( (status= proc.fp_unit.check_zero_divide(frop1,frop2))
            == ENABLED_EXCP){
          info()<<"raise fp enabled exception"<<endl;
          return;//instruction supressed, frD unchanged
        }else if(status==DISABLED_EXCP){
          proc.cpu.fpr[rd]=frd.get_value();
          if(op::rc)
            proc.fp_unit.update_CR1();
          proc.cpu.pc += 4;
          return;
        }
      }//if(op::type() ==FDIV )

      debug()<<"non regular result"<<endl;
      proc.fp_unit.handle_nonregular_result(frd,inext);
      proc.cpu.fpr[rd]=frd.get_value();
      if(op::rc)
        proc.fp_unit.update_CR1();

      //for debug
      double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rd]);
      debug()<<"result :"<< d<<" ["<<hex<<proc.cpu.fpr[rd]<<"]"<<endl;

      proc.cpu.pc += 4;
      return;
    }else{
      debug()<<"regular result"<<endl;
      proc.fp_unit.handle_regular_result(frd,inext);
      proc.cpu.fpr[rd]=frd.get_value();
      if(op::rc)
        proc.fp_unit.update_CR1();

      //for debug
      double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rd]);
      debug()<<"result:"<< d<<" ["<<hex<<proc.cpu.fpr[rd]<<"]"<<endl;

      if(proc.fp_unit.fp_exception_enabled())
        proc.info()<<"raise fp enabled exception"<<endl;
      else
        proc.cpu.pc += 4;
      return;
    }
  }

  template <class op>
  std::ostream& PPC_FPArithmetic<op>::display(std::ostream& os) const {
    return os<<op::name()<<"\tfr"<<std::dec<<(int)rd<<", "<<"fr"<<std::dec<<(int)op1<<", "<<"fr"<<std::dec<<(int)op2<<"\n";
  }

  template <class op>
  void PPC_FPArithmetic_1op<op>::exec(PPC_Processor &proc){
    proc.fp_unit.check_fp_enabled();

    fp_t frd,frop(proc.cpu.fpr[op1]);

    if(op::single_prec_operation){
      //if single operand is not fit single-precision. result is undefined
      if(!frop.fit_single_format()){
        proc.error()<<"Source operands not representable in single-precision format.";
        proc.error()<<"Result undefined"<<endl;
        exit(1);
      }
      frd.set_prec(Single);
      frop.set_prec(Single);
    }

    mpfr_clear_flags();
    int inext=op::compute(frd,frop,proc.fp_unit.rnd_mode());

    if(frd.is_nan()){
      debug()<<"nan result! check for invalide operand exception!"<<endl;
      fp_excp_status status = NOEXCP;
      if((status = proc.fp_unit.check_invalid_operand(op::type(),frop))
         == ENABLED_EXCP){
        info()<<"raise fp enabled exception"<<endl;
        return;//instruction supressed, frD unchanged
      }

      debug()<<"nan operand in source"<<endl;
      if(frop.is_nan())
        proc.cpu.fpr[rd] = proc.cpu.fpr[op1];
      else if(status==DISABLED_EXCP)
        proc.cpu.fpr[rd] = QNAN_VALUE;

      proc.fp_unit.fpscr.set_fi(false);
      proc.fp_unit.fpscr.set_fr(false);
      proc.fp_unit.fpscr.set_fprf(QNAN);

      if(op::rc)
        proc.fp_unit.update_CR1();

      proc.cpu.pc += 4;
      return;
    }else if(frd.is_zero() || frd.is_inf()){
      debug()<<"non regular result"<<endl;
      proc.fp_unit.handle_nonregular_result(frd,inext);
      proc.cpu.fpr[rd]=frd.get_value();
      if(op::rc)
        proc.fp_unit.update_CR1();

      double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rd]);
      debug()<<"result :"<< d<<" ["<<hex<<proc.cpu.fpr[rd]<<"]"<<endl;

      proc.cpu.pc += 4;
      return;
    }else{
      debug()<<"regular result"<<endl;
      proc.fp_unit.handle_regular_result(frd,inext);
      proc.cpu.fpr[rd]=frd.get_value();
      if(op::rc)
        proc.fp_unit.update_CR1();

      double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rd]);
      debug()<<"result :"<< d<<" ["<<hex<<proc.cpu.fpr[rd]<<"]"<<endl;

      if(proc.fp_unit.fp_exception_enabled())
        proc.info()<<"raise fp enabled exception"<<endl;
      else
        proc.cpu.pc += 4;
      return;
    }
  }

  template <class op>
  std::ostream& PPC_FPArithmetic_1op<op>::display(std::ostream& os) const {
    return os<<op::name()<<"\tfr"<<std::dec<<(int)rd<<", "<<"fr"<<std::dec<<(int)op1<<"\n";
  }

  /*
   * Floating-Point Conversion Instructions
   */
  template <class op>
  void PPC_FPConvert<op>::exec(PPC_Processor &proc){
    proc.fp_unit.check_fp_enabled();

    fp_t frop(proc.cpu.fpr[op1]);

    fp_excp_status status = NOEXCP;
    if((status = proc.fp_unit.check_invalid_operand(op::type(),frop,op::rnd(proc)))
       == ENABLED_EXCP){
      info()<<"raise fp enabled exception"<<endl;
      return;//instruction supressed, frD unchanged
    }else if(status==DISABLED_EXCP){
      if(frop.sign() == 1 && (!frop.is_nan())) //positive number or +inf
        proc.cpu.fpr[rd] = op::max_pos;
      else if(frop.sign()<0 || frop.is_nan()) //negative number, NaN or -inf
        proc.cpu.fpr[rd] = op::max_neg;

      debug()<<"result :"<<hex<<proc.cpu.fpr[rd]<<endl;

      if(op::rc)
        proc.fp_unit.update_CR1();
      proc.cpu.pc += 4;
      return;
    }

    uint64_t result;
    mpfr_clear_flags();
    int inext = op::compute(result,frop,proc.fp_unit.rnd_mode());//can get fi fr set different prec rint
    proc.fp_unit.set_round_status(inext);
    proc.cpu.fpr[rd] = result;
    debug()<<"result :"<<hex<<proc.cpu.fpr[rd]<<endl;

    if(op::rc)
      proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
    return;
  }

  template <class op>
  std::ostream& PPC_FPConvert<op>::display(std::ostream& os) const {
    return os<<op::name()<<"\tfr"<<std::dec<<(int)rd<<", "<<"fr"<<std::dec<<(int)op1<<"\n";
  }

  /*
   * Floating-Point Compare Instructions
   */
  template <class op>
  void PPC_FPCompare<op>::exec(PPC_Processor &proc){
    proc.fp_unit.check_fp_enabled();

    fp_t frop1(proc.cpu.fpr[op1]),frop2(proc.cpu.fpr[op2]);

    mpfr_clear_flags();
    int result=op::compute(frop1,frop2);

    fpcc_t c;
    if(mpfr_erangeflag_p()){
      fp_excp_status status = NOEXCP;
      if((status = proc.fp_unit.check_invalid_operand(op::type(),frop1,frop2))
         == ENABLED_EXCP){
        proc.info()<<"raise fp enabled exception"<<endl;
        return;//instruction supressed, frD unchanged
      }
      c = FU;
      debug()<<"FU"<<endl;
    }else{
      if(result<0){
        c = FL;
        debug()<<"FL"<<endl;
      }
      else if(result>0){
        c = FG;
        debug()<<"FG"<<endl;
      }
      else{
        c = FE;
        debug()<<"FE"<<endl;
      }
    }

    proc.fp_unit.fpscr.set_fpcc(c);
    proc.cpu.update_CR_field(crfD,(uint8_t)c);
    proc.cpu.pc +=4;
  }

  template <class op>
  std::ostream& PPC_FPCompare<op>::display(std::ostream& os) const {
    return os<<op::name()<<"\tcr"<<std::dec<<(int)crfD<<", fr"<<std::dec<<(int)op1<<", "<<"fr"<<std::dec<<(int)op2<<"\n";
  }


  /*
   * Floating-Point Multiply-Add Instructions
   */
  template <class op>
  void PPC_FPMultiAdd<op>::exec(PPC_Processor &proc){
    proc.fp_unit.check_fp_enabled();

    fp_t frd,fra(proc.cpu.fpr[ra]),frb(proc.cpu.fpr[rb]),frc(proc.cpu.fpr[rc]);

    if(op::single_prec_operation){
      //if single operand is not fit single-precision. result is undefined
      if(!fra.fit_single_format()
         || !frb.fit_single_format()
         || !frc.fit_single_format()){
        proc.error()<<"Source operands not representable in single-precision format.";
        proc.error()<<"Result undefined"<<endl;
        exit(1);
      }
      frd.set_prec(Single);
      fra.set_prec(Single);
      frb.set_prec(Single);
      frc.set_prec(Single);
    }

    mpfr_clear_flags();
    int inext = op::compute(frd,fra,frb,frc,proc.fp_unit.rnd_mode());

    if(frd.is_nan()){
      debug()<<"nan result! check for invalide operand exception!"<<endl;
      fp_excp_status status = NOEXCP;
      if((status = proc.fp_unit.check_invalid_operand(op::type(),fra,frc,frb))
         == ENABLED_EXCP){
        proc.info()<<"raise fp enabled exception"<<endl;
        return;//instruction supressed, frD unchanged
      }

      debug()<<"nan operand in source"<<endl;
      if(fra.is_nan())
        proc.cpu.fpr[rd] = proc.cpu.fpr[ra];
      else if(frb.is_nan())
        proc.cpu.fpr[rd] = proc.cpu.fpr[rb];
      else if(frc.is_nan())
        proc.cpu.fpr[rd] = proc.cpu.fpr[rc];
      else if(status==DISABLED_EXCP)
        proc.cpu.fpr[rd] = QNAN_VALUE;

      proc.fp_unit.fpscr.set_fi(false);
      proc.fp_unit.fpscr.set_fr(false);
      proc.fp_unit.fpscr.set_fprf(QNAN);

      if(op::rc)
        proc.fp_unit.update_CR1();

      proc.cpu.pc += 4;
      return;
    }else if(frd.is_zero() || frd.is_inf()){
      debug()<<"non regular result"<<endl;
      proc.fp_unit.handle_nonregular_result(frd,inext);
      proc.cpu.fpr[rd]=frd.get_value();
      if(op::rc)
        proc.fp_unit.update_CR1();

      double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rd]);
      debug()<<"result :"<< d<<" ["<<hex<<proc.cpu.fpr[rd]<<"]"<<endl;

      proc.cpu.pc += 4;
      return;
    }else{
      proc.fp_unit.handle_regular_result(frd,inext);
      proc.cpu.fpr[rd]=frd.get_value();
      if(op::rc)
        proc.fp_unit.update_CR1();

      double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rd]);
      debug()<<"result is :"<< d<<" ["<<hex<<proc.cpu.fpr[rd]<<"]"<<endl;

      if(proc.fp_unit.fp_exception_enabled()){
        proc.info()<<"raise fp enabled exception"<<endl;
      }else
        proc.cpu.pc += 4;
      return;
    }
  }

  template <class op>
  std::ostream& PPC_FPMultiAdd<op>::display(std::ostream& os) const {
    return os<<op::name()<<"\tfr"<<std::dec<<(int)rd<<", "<<"fr"<<std::dec<<(int)ra<<", "<<"fr"<<std::dec<<(int)rb<<", fr"<<std::dec<<(int)rc<<"\n";
  }
}//namespace simsoc
