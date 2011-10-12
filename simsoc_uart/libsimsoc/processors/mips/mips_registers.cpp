//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mips_registers.hpp"

using namespace std;

namespace simsoc {

MIPS_CauseRegister::MIPS_CauseRegister():
  bd(false),ce(0),iv(false),exc_code(Exc_Int),reg_value(0)
{
 uint8_t m;
  for(m=0;m<8;++m)
    ip[m] = false;
}

MIPS_CauseRegister& MIPS_CauseRegister::operator=(const uint32_t& value){
  reg_value = value;
  bd = (bool)((value >> 31) & 0x1);
  ce = (uint8_t)((value >> 28) & 0x3);
  iv = (bool)((value >> 26) & 0x1);
  for(uint32_t i=0;i<8;i++){
    ip[i] = (bool)((value>>(8+i)) & 0x1);
  }
  exc_code = (ExcCode)((value>>2) & 0x1f);
  return *this;
}

uint32_t MIPS_CauseRegister::get_value(){
  uint32_t update_value=0;
  for(uint32_t i=0;i<8;i++){
    update_value |= ip[i] << (8+i);
  }
  update_value |= (bd<<31) | (ce<<28) |(iv<<26) | (uint32_t)exc_code << 2;
  return reg_value | update_value;
}

MIPS_StatusRegister::MIPS_StatusRegister():
  bev(true),sx(false),ux(false),um(false),ksu(kernel),erl(true),exl(true),ie(true)
  ,reg_value(0x40ff07)
{
  uint8_t m;
  for(m=0;m<8;++m)
    im[m] = true;
}

MIPS_StatusRegister& MIPS_StatusRegister::operator=(const uint32_t& value){
  reg_value = value;
  bev= (bool)((value >> 22) & 0x1);
  for(uint32_t i=0;i<8;i++){
    im[i] = (bool)((value>>(8+i)) & 0x1);
  }
  sx= (bool)((value >> 6) & 0x1);
  ux= (bool)((value >> 5) & 0x1);
  um= (bool)((value >> 4) & 0x1);
  ksu = (MMU_Mode)((value>>3) & 0x3);
  erl= (bool)((value >> 2) & 0x1);
  exl= (bool)((value >> 1) & 0x1);
  ie= (bool)((value >> 0) & 0x1);
  return *this;
}

uint32_t MIPS_StatusRegister::get_value(){
  uint32_t update_value=0;
  for(uint32_t i=0;i<8;i++){
    update_value |= im[i] << (8+i);
  }
  update_value |= (bev<<22) | (sx<<6) |(ux<<5) |((uint32_t)ksu<<3)
    |(erl<<2) |(exl<<1) | ie;
  return reg_value | update_value;
}

} // namespace simsoc
