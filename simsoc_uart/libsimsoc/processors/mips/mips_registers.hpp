//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_REGISTERS_HPP
#define MIPS_REGISTERS_HPP

#include <inttypes.h>

namespace simsoc {

  typedef enum mode {
    kernel=0,
    supervisor=1,
    user=2
  } MMU_Mode;

  typedef enum ExcCode{
    Exc_Int=0,  // interrupt
    Exc_Mod=1,  // TLB modified exception
    Exc_TLBL=2, // TLB exception (load or instruction fetch)
    Exc_TLBS=3, // TLB exception (store)
    Exc_AdEL=4, // Address error exception (load or fetch)
    Exc_AdES=5, // Address error exception (store)
    Exc_IBE=6,  // Bus error exception (instruction fetch)
    Exc_DBE=7,  // Bus error exception (load or store)
    Exc_Sys=8,  // Syscall exception
    Exc_Bp=9,   // Breakpoint exception
    Exc_Ri=10,  // Reserved instruction exception
    Exc_CpU=11, // Coprocessor Unusable exception
    Exc_Ov=12,  // Arithmetic overflow exception
    Exc_Tr=13,  // Trap exception
    Exc_FPE=15, // Floating Point exception
    Exc_C2E=18,
    Exc_MDMX=22,
    Exc_WATCH=23,// Reference to WatchHi/WatchLo address
    Exc_MCheck=24,
    Exc_CacheErr=30
  }ExcCode;

  class MIPS_CauseRegister
  {
  public:

    MIPS_CauseRegister();
    MIPS_CauseRegister& operator=(const uint32_t&);
    uint32_t get_value();

    bool bd; //bit 31
    uint8_t ce; //bit 29:28
    bool iv; //bit 23
    bool ip[8]; //bit 15:8
    ExcCode exc_code; //bit 6:2
  private:
    uint32_t reg_value;
  };

  class MIPS_StatusRegister
  {
  public:
    MIPS_StatusRegister();
    MIPS_StatusRegister& operator=(const uint32_t&);
    uint32_t get_value();

    bool bev; //bit 22
    bool im[8]; //bit 15:8
    bool sx; //bit 6
    bool ux; //bit 5
    bool um; //bit 4
    MMU_Mode ksu; //bit4:3
    bool erl; //bit 2
    bool exl; //bit 1
    bool ie; //bit 0
  private:
    uint32_t reg_value;
  };

} // namespace simsoc

#endif
