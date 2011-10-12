#include "ppc_fp_unit.hpp"
#include "ppc_processor.hpp"
#include "ppc_tool.hpp"

namespace simsoc{
  const fpscr_excp_t PPC_FloatPoint_Unit::exception_index[FP_EXCP_NUM]= {
      XX,UX,ZX,OX,VXCVI,VXZDZ,VXIDI,VXISI,VXIMZ,VXSQRT,VXSOFT,VXSNAN,VXVC
    };

  PPC_FloatPoint_Unit::PPC_FloatPoint_Unit(sc_core::sc_module_name name,PPC_Processor *_proc)
    :FloatPoint_Unit(name),fpscr(_proc),proc(_proc){
  };

  ppc_fp_excp_mode PPC_FloatPoint_Unit::get_fp_excp_mode(){
    bool fe0 = check_MSR_FE0(proc->cpu.msr);
    bool fe1 = check_MSR_FE1(proc->cpu.msr);
    uint8_t mode = (uint8_t)fe0<<1 | fe1;
    return (ppc_fp_excp_mode)mode;
  }

  bool PPC_FloatPoint_Unit::fp_exception_enabled(){
    return fpscr.get_fex() && (get_fp_excp_mode()!=DISABLED);
  }

  void PPC_FloatPoint_Unit::check_fp_enabled(){
    if(!check_MSR_FP(proc->cpu.msr)){
      proc->info()<<"raise floating point not enabled exception"<<endl;
      proc->interrupt(INT_NO_FPU);
    }
    static const int DP_MAX = 1024;
    static const int DP_MIN = -1073;
    mpfr_set_emax(2 * DP_MAX );
    mpfr_set_emin(2 * DP_MIN -1);
  }

  void PPC_FloatPoint_Unit:: update_CR1(){
    proc->cpu.cr &= ~(0xf << 24);
    proc->cpu.cr |= fpscr.get_field(0) << 24;
  }

   fp_excp_status PPC_FloatPoint_Unit::set_invalid_excp(fp_op_t op_type,fp_excp_t excp){
    assert(exception_index[excp]>=VXSNAN);
    fpscr.set_excp(exception_index[excp]);

    switch(op_type){
    default:
      {
        fpscr.set_fr(false);
        fpscr.set_fi(false);
        if(!fpscr.get(PPC_FPSCR::VE)){
          fpscr.set_fprf(QNAN);
          return DISABLED_EXCP;
        }else
          return ENABLED_EXCP;
      }
      break;
    case FCOV32S:
    case FCOV32U:
    case FCOV64S:
    case FCOV64U:
      {
        fpscr.set_fr(false);
        fpscr.set_fi(false);
        if(!fpscr.get(PPC_FPSCR::VE)){
          fpscr.set_fprf(NON);
          return DISABLED_EXCP;
        }else
          return ENABLED_EXCP;
      }
      break;
    case FCOMPO:
      {
        fpscr.set_fpcc(FU);
        if(!fpscr.get(PPC_FPSCR::VE)){
          if(excp == UNDTA)
            fpscr.set_excp(VXVC);
          return DISABLED_EXCP;
        }else
          return ENABLED_EXCP;
      }
      break;
    case FCOMPU:
      {
        //fr fi c unchanged
        fpscr.set_fpcc(FU);
        if(!fpscr.get(PPC_FPSCR::VE))
          return DISABLED_EXCP;
        else
          return ENABLED_EXCP;
      }
      break;
    }
  }

  fp_excp_status PPC_FloatPoint_Unit::set_divzero_excp(int sign){
    fpscr.set_excp(ZX);
    fpscr.set_fi(false);
    fpscr.set_fr(false);
    if(!fpscr.get(PPC_FPSCR::ZE)){
      fpscr.set_fprf(sign>0?PINF:MINF);
      return DISABLED_EXCP;
    }else
      return ENABLED_EXCP;
  }

  int PPC_FloatPoint_Unit::handle_nonregular_result(fp_t &frd,int inext){
    //for intermediate result is 0 or inf
    assert(inext==0);
    set_round_status(0);
    set_fprf(frd);
    return inext;
  }

  int PPC_FloatPoint_Unit::handle_regular_result(fp_t &frd,int inext){
    //zero or inf case is already handled
    if(frd.is_tiny()){ //denormalized or may underflow
      inext=handle_tiny_result(frd,inext);
    }else{ //normalized or may overflow
      inext=handle_normal_result(frd,inext);
    }

    if(inext){
      info()<<"Inexact Result!!"<<endl;
      fpscr.set_excp(XX);
    }

    set_fprf(frd);
    return inext;
  }

  int PPC_FloatPoint_Unit::handle_tiny_result(fp_t &frd,int inext){
    if(!fpscr.get(PPC_FPSCR::UE)){//underflow disabled
      info()<<"Disabled Underflow!!"<<endl;
      inext = frd.underflow(inext,rnd_mode());
      set_round_status(inext);
      if(inext!=0){
        info()<<"Set Exception Underflow"<<endl;
        fpscr.set_excp(UX);
      }
    }else{
      info()<<"Enabled Underflow!!"<<endl;
      fpscr.set_excp(UX);
      frd.adjust_exp_for_udflo_trap();
      set_round_status(inext);
    }
    return inext;
  }

  int PPC_FloatPoint_Unit::handle_normal_result(fp_t &frd,int inext){
    if(frd.is_overflow()){
      fpscr.set_excp(OX);
      if(!fpscr.get(PPC_FPSCR::OE)){//overflow disabled
        info()<<"Disabled Overflow!!"<<endl;
        fpscr.set_excp(XX);
        inext = frd.overflow(inext,rnd_mode());
        assert(inext!=0);
        assert(mpfr_overflow_p());
        fpscr.set_fi(true);
        //fr undefined
      }else{
        info()<<"Enabled Overflow!!"<<endl;
        frd.adjust_exp_for_ovflo_trap();
        set_round_status(inext);
      }
    }else{//normalized number
      set_round_status(inext);
    }
    return inext;
  }

  void PPC_FloatPoint_Unit::set_fprf(fp_t &frd){
    if(frd.is_zero())
      fpscr.set_fprf(frd.sign()==-1? MZERO : RVC_PZERO);
    else if(frd.is_inf())
      fpscr.set_fprf(frd.sign()==-1? MINF : PINF);
    else if(frd.is_normalized())
      fpscr.set_fprf(frd.sign()==-1? MNORM : PNORM);
    else if(frd.is_denormalized())
      fpscr.set_fprf(frd.sign()==-1? MDORM : PDORM);
    else
      fpscr.set_fprf(QNAN);
  };

   void PPC_FloatPoint_Unit::set_round_status(int inext){
    if(inext>0){
      fpscr.set_fr(true);
      fpscr.set_fi(true);
    }else if(inext<0){
      fpscr.set_fr(false);
      fpscr.set_fi(true);
    }else{
      fpscr.set_fr(false);
      fpscr.set_fi(false);
    }
  };

}//namespace
