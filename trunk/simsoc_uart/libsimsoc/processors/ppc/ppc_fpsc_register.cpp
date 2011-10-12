#include "ppc_fpsc_register.hpp"
#include "ppc_processor.hpp"

using namespace std;

namespace simsoc{

  ostream& PPC_FPExcpId::display(ostream& os) const {
    switch (id) {
    case OX: return os << "overflow";
    case UX: return os << "underflow";
    case ZX: return os << "divide zero";
    case VXSNAN: return os << "invalid_snan";
    case VXISI: return os << "invalid_isi";
    case VXIDI: return os << "invalid_idi";
    case VXZDZ: return os << "invalid_zdz";
    case VXIMZ: return os << "invalid_imz";
    case VXVC: return os << "invalid_vc";
    case VXSOFT: return os << "invalid_soft";
    case VXSQRT: return os << "invalid_sqrt";
    case VXCVI: return os << "invalid_cvi";
    default: return os << (size_t)id;
    }
  }

  const uint8_t PPC_FPSCRegister::field_exceptions[8]={0x9,0xf,0xf,0x8,0x0,0x7,0x0,0x0};

  void PPC_FPSCRegister::set_excp(fpscr_excp_t index){
    set(index,true);
    info()<<"set exception: "<<(PPC_FPExcpId)index<<endl;
    if(index>=VXSNAN){
      set(VX,true);
      info()<<"set exception: VX"<<endl;
    }
    set(FX,true);
    update_fex();
  }

  void PPC_FPSCRegister::set_fi(bool value){
    set(FI,value);
    if(value){
      set(XX,true);
      set(FX,true);
      update_fex();
    }
  }

  void PPC_FPSCRegister::update_fex(){
    bool old_fex = get(FEX);
    bool new_fex = ((reg>>EXCEPTIONBITS_SHIFT) & 0x1f)
      & ((reg>>ENABLEBITS_SHIFT) & 0x1f);
    set(FEX,new_fex);
    if(new_fex)
      info()<<"set FEX!"<<endl;
    if(old_fex != new_fex){
      info()<<"signal "<<new_fex<<endl;
      proc->signal();
    }
  }

  void PPC_FPSCRegister::update_vx(){
    bool new_vx = reg & INVALID_EXCEPTION_MASK;
    set(VX,new_vx);
    if(new_vx)
      info()<<"set exception: VX"<<endl;
  }

  uint8_t PPC_FPSCRegister::move_field_to_cr(uint8_t field){
    const uint8_t field_shift = (7-field)*4;
    uint8_t value= (reg>>field_shift) & 0xf;
    uint32_t clear_mask = ~(field_exceptions[field] << field_shift);
    reg &= clear_mask;
    update_vx();
    update_fex();
    return value;
  }

  uint8_t PPC_FPSCRegister::get_field(uint8_t field){
    const uint8_t field_shift = (7-field)*4;
    return (reg>>field_shift) & 0xf;
  }

  void PPC_FPSCRegister::set_field(uint8_t field, const uint8_t value){
    const uint8_t field_shift = (7-field)*4;
    const uint32_t mask = 0xf << field_shift;
    reg &= ~mask;
    reg |= (value & 0xf)<<field_shift;
    update_vx();
    update_fex();
  }

}//namespace simsoc
