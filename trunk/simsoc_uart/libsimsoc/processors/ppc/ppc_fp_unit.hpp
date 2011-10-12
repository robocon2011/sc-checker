#ifndef PPC_FP_UNIT_HPP
#define PPC_FP_UNIT_HPP

#include <libsimsoc/interfaces/float_point_unit.hpp>
#include "ppc_fpsc_register.hpp"

namespace simsoc{

  class PPC_Processor;

   typedef enum PPC_FP_EXCEPTION_MODE{
    DISABLED = 0,
    IMPRE_NONREC = 1,
    IMPRE_RECOV = 2,
    PRECISE = 3
  }ppc_fp_excp_mode;


  class PPC_FloatPoint_Unit:public FloatPoint_Unit
  {
  public:
    PPC_FloatPoint_Unit(sc_core::sc_module_name name,PPC_Processor *_proc);

    /*
     * mp_rnd_t {GMP_RNDN,GMP_RNDZ,GMP_RNDU,GMP_RNDD}
     */
    mp_rnd_t rnd_mode(){
      switch(fpscr.get_rn()){
      case Round_Nearest:
        return GMP_RNDN;
      case Round_Zero:
        return GMP_RNDZ;
      case Round_Pinfinity:
        return GMP_RNDU;
      case Round_Minfinity:
        return GMP_RNDD;
      default:
        error()<<"wrong rounding mode: "<<(uint8_t)fpscr.get_rn()<<"!"<<std::endl;
        return GMP_RNDN;
      }
    };

    fp_excp_status set_invalid_excp(fp_op_t op_type,fp_excp_t excp);
    fp_excp_status set_divzero_excp(int sign);
    int handle_nonregular_result(fp_t &frd,int inext);
    int handle_regular_result(fp_t &frd,int inext);
    int handle_tiny_result(fp_t &frd,int inext);
    int handle_normal_result(fp_t &frd,int inext);

    void set_round_status(int inext);
    void set_fprf(fp_t &frd);
    void update_CR1();

    ppc_fp_excp_mode get_fp_excp_mode();
    void check_fp_enabled();
    bool fp_exception_enabled();

    PPC_FPSCRegister fpscr;
    static const fpscr_excp_t exception_index[FP_EXCP_NUM];

  private:
    PPC_Processor *proc;
  };
}//namespace simsoc

#endif
