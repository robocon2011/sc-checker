//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include <inttypes.h>

#ifndef PPC_TOOL_HPP
#define PPC_TOOL_HPP

namespace simsoc {

  /**
   *cr0 bits:
   *0  LT  Negative
   *1  GT  Positive
   *2  EQ  Zero
   *3  SO  Summary Overflow
   */
  const uint32_t CR_CR0_LT = 1<<31;
  const uint32_t CR_CR0_GT = 1<<30;
  const uint32_t CR_CR0_EQ = 1<<29;
  const uint32_t CR_CR0_SO = 1<<28;

  inline void set_CR_CR0_LT(uint32_t& val) {val |= CR_CR0_LT;}
  inline void set_CR_CR0_GT(uint32_t& val) {val |= CR_CR0_GT;}
  inline void set_CR_CR0_EQ(uint32_t& val) {val |= CR_CR0_EQ;}
  inline void set_CR_CR0_SO(uint32_t& val) {val |= CR_CR0_SO;}

  inline bool check_CR_CR0_LT(uint32_t val) {return val&CR_CR0_LT;}
  inline bool check_CR_CR0_GT(uint32_t val) {return val&CR_CR0_GT;}
  inline bool check_CR_CR0_EQ(uint32_t val) {return val&CR_CR0_EQ;}
  inline bool check_CR_CR0_SO(uint32_t val) {return val&CR_CR0_SO;}

  /**
   *cr1 bits:
   *4  FX  Floating-point exception
   *5  FEX Floating-point enabled exception
   *6  VX  Floating-point invalid exception
   *7  OX  Floating-point overflow exception
   */
  const uint32_t CR_CR1_FX  = 1<<27;
  const uint32_t CR_CR1_FEX = 1<<26;
  const uint32_t CR_CR1_VX  = 1<<25;
  const uint32_t CR_CR1_OX  = 1<<24;

  inline void set_CR_CR1_FX(uint32_t& val) {val |= CR_CR1_FX;}
  inline void set_CR_CR1_FEX(uint32_t& val) {val |= CR_CR1_FEX;}
  inline void set_CR_CR1_VX(uint32_t& val) {val |= CR_CR1_VX;}
  inline void set_CR_CR1_OX(uint32_t& val) {val |= CR_CR1_OX;}

  inline bool check_CR_CR1_FX(uint32_t val) {return val&CR_CR1_FX;}
  inline bool check_CR_CR1_FEX(uint32_t val) {return val&CR_CR1_FEX;}
  inline bool check_CR_CR1_VX(uint32_t val) {return val&CR_CR1_VX;}
  inline bool check_CR_CR1_OX(uint32_t val) {return val&CR_CR1_OX;}

  /**
   *xer bits:
   *0  SO  Summary Overflow
   *1  OV  Overflow
   *2  CA  Carry
   *3:24   Reserved
   *25:31  This field specifies the number of bytes to be transferred by a Load String Indexed or Store
   *String Indexed instruction.
   */
  const uint32_t XER_SO = 1<<31;
  const uint32_t XER_OV = 1<<30;
  const uint32_t XER_CA = 1<<29;

  inline void set_XER_SO(uint32_t& val) {val |= XER_SO;}
  inline void set_XER_OV(uint32_t& val) {val |= XER_OV;}
  inline void set_XER_CA(uint32_t& val) {val |= XER_CA;}

  inline bool check_XER_SO(uint32_t val) {return val&XER_SO;}
  inline bool check_XER_OV(uint32_t val) {return val&XER_OV;}
  inline bool check_XER_CA(uint32_t val) {return val&XER_CA;}

  inline  uint32_t XER_n(uint32_t v) { return v & 0x7f; }

  /**
   *msr bits:
   *0:12  Reserved
   *13    POW  power management enabled
   *14    Reserved
   *15	ILE	 Interrupt Little-Endian Mode
   *16	EE	 External Interrupt Enable
   *17	PR	 Privilege level
   *18	FP	 Floating-Point Available
   *19	ME	 Machine Check Interrupt Enable
   *20	FE0  Floating-Point Exception Mode 0
   *21	SE   Single-Step Trace Enable
   *22	BE	 Branch Trace Enable
   *23	FE1	 Floating-Point Exception Mode 1
   *24    Reserved
   *25    IP   exception prefix
   *26    IR   Instruction address translation
   *27    DR   Data address translation
   *28:29 Reserved
   *30    RI	 Recoverable Interrupt
   *31	LE   Little-Endian Mode
   */
  const uint32_t MSR_POW = 1<<18;
  const uint32_t MSR_ILE = 1<<16;
  const uint32_t MSR_EE  = 1<<15;
  const uint32_t MSR_PR  = 1<<14;
  const uint32_t MSR_FP  = 1<<13;
  const uint32_t MSR_ME  = 1<<12;
  const uint32_t MSR_FE0 = 1<<11;
  const uint32_t MSR_SE  = 1<<10;
  const uint32_t MSR_BE  = 1<<9;
  const uint32_t MSR_FE1 = 1<<8;
  const uint32_t MSR_IP  = 1<<6;
  const uint32_t MSR_IR  = 1<<5;
  const uint32_t MSR_DR  = 1<<4;
  const uint32_t MSR_PM  = 1<<2;
  const uint32_t MSR_RI  = 1<<1;
  const uint32_t MSR_LE  = 1;

  inline void set_MSR_POW(uint32_t& val) {val |= MSR_POW;}
  inline void set_MSR_ILE(uint32_t& val) {val |= MSR_ILE;}
  inline void set_MSR_EE(uint32_t& val) {val |= MSR_EE;}
  inline void set_MSR_PR(uint32_t& val) {val |= MSR_PR;}
  inline void set_MSR_FP(uint32_t& val) {val |= MSR_FP;}
  inline void set_MSR_ME(uint32_t& val) {val |= MSR_ME;}
  inline void set_MSR_FE0(uint32_t& val) {val |= MSR_FE0;}
  inline void set_MSR_SE(uint32_t& val) {val |= MSR_SE;}
  inline void set_MSR_BE(uint32_t& val) {val |= MSR_BE;}
  inline void set_MSR_FE1(uint32_t& val) {val |= MSR_FE1;}
  inline void set_MSR_IP(uint32_t& val) {val |= MSR_IP;}
  inline void set_MSR_IR(uint32_t& val) {val |= MSR_IR;}
  inline void set_MSR_DR(uint32_t& val) {val |= MSR_DR;}
  inline void set_MSR_PM(uint32_t& val) {val |= MSR_PM;}
  inline void set_MSR_RI(uint32_t& val) {val |= MSR_RI;}
  inline void set_MSR_LE(uint32_t& val) {val |= MSR_LE;}

  inline bool check_MSR_POW(uint32_t val) {return val&MSR_POW;}
  inline bool check_MSR_ILE(uint32_t val) {return val&MSR_ILE;}
  inline bool check_MSR_EE(uint32_t val) {return val&MSR_EE;}
  inline bool check_MSR_PR(uint32_t val) {return val&MSR_PR;}
  inline bool check_MSR_FP(uint32_t val) {return val&MSR_FP;}
  inline bool check_MSR_ME(uint32_t val) {return val&MSR_ME;}
  inline bool check_MSR_FE0(uint32_t val) {return val&MSR_FE0;}
  inline bool check_MSR_SE(uint32_t val) {return val&MSR_SE;}
  inline bool check_MSR_BE(uint32_t val) {return val&MSR_BE;}
  inline bool check_MSR_FE1(uint32_t val) {return val&MSR_FE1;}
  inline bool check_MSR_IP(uint32_t val) {return val&MSR_IP;}
  inline bool check_MSR_IR(uint32_t val) {return val&MSR_IR;}
  inline bool check_MSR_DR(uint32_t val) {return val&MSR_DR;}
  inline bool check_MSR_PM(uint32_t val) {return val&MSR_PM;}
  inline bool check_MSR_RI(uint32_t val) {return val&MSR_RI;}
  inline bool check_MSR_LE(uint32_t val) {return val&MSR_LE;}

  const uint32_t MSR_MASK = 0x0200FFFF;//0x87C0FFFF; //srr[1] = msr & MSR_MASK;

  //---------------------------------MMU--------------------------------
  /**
   *BAT Register:
   *upper:
   * 0:14  BEPI Block Effective Gage Index.
   *15:18  Reserved
   *19:29  BL   Block Length.
   *30     Vs   Supervisor mode valid bit.
   *31     Vp   User mode valid bit.
   *lower:
   *0:14  BRPN Physical Block Number.
   *15:24  Reserved
   *25:28  WIMG Memory/cache access mode bits
   *29     Reserved
   *30:31  PP   Protection bits for block.

   *BAT Area
   *Length		BL Encoding
   *128 Kbytes	000 0000 0000
   *256 Kbytes	000 0000 0001
   *512 Kbytes	000 0000 0011
   *  1 Mbyte		000 0000 0111
   *  2 Mbytes	000 0000 1111
   *  4 Mbytes	000 0001 1111
   *  8 Mbytes	000 0011 1111
   * 16 Mbytes	000 0111 1111
   * 32 Mbytes	000 1111 1111
   * 64 Mbytes	001 1111 1111
   *128 Mbytes	011 1111 1111
   *256 Mbytes	111 1111 1111
   */

  /* BAT Access Protection */
  const uint32_t BPP_XX = 0x00; /* No access */
  const uint32_t BPP_RX = 0x01; /* Read only */
  const uint32_t BPP_RW	= 0x02; /* Read/write */

  inline uint32_t BATU_BEPI(uint32_t v) { return (v>>17) & 0x7fff; }
  inline uint32_t BATU_BEPI_SHIFT(uint32_t v) { return v & 0xfffe0000; }
  inline uint32_t BATU_BL(uint32_t v) { return (v & 0x1ffc) >> 2; }
  inline uint32_t BATU_BL_SHIFT(uint32_t v) { return v & 0x1ffc; }

  const  uint32_t BATU_Vs = 1 << 1;
  const  uint32_t BATU_Vp = 1;

  inline void set_BATU_Vs(uint32_t& val) {val |= BATU_Vs;}
  inline void set_BATU_Vp(uint32_t& val) {val |= BATU_Vp;}

  inline bool check_BATU_Vs(uint32_t val) {return val&BATU_Vs;}
  inline bool check_BATU_Vp(uint32_t val) {return val&BATU_Vp;}

  inline uint32_t BATL_BRPN_SHIFT(uint32_t v) { return v & 0xfffe0000; }
  inline uint32_t BAT_EA_OFFSET(uint32_t v) { return v & 0x1ffff; }
  inline uint32_t BAT_EA_11_SHIFT(uint32_t v) { return v & 0x0ffe0000; }
  inline uint32_t BAT_EA_4_SHIFT(uint32_t v) { return v & 0xf0000000; }

  const uint32_t BAT_SHIFT = (1<<17) - 1;

  //--------------------SDR1------------------------
  /**
   *SDR1:
   *0:15 HTABORG: Physical base address of page table
   *16:22 Reserved
   *23:31 HTABMASK:Mask for page table address
   */
  inline uint32_t SDR1_HTABORG_SHIFT(uint32_t v) { return v & 0xffff0000; }
  inline uint32_t SDR1_HTABORG(uint32_t v) { return (v>>16) & 0xffff; }
  inline uint32_t SDR1_HTABMASK(uint32_t v) { return v & 0x1ff; }
  inline uint32_t SDR1_PAGETABLE_BASE(uint32_t v) { return v & 0xffff; }

  //------------------------SR----------------------
  /**
   *sr:
   *0    T=0
   *1    Ks   Supervisor-state protection key
   *2    Kp   User-state protection key
   *3    N    No-execute protection
   *4:7  reserved
   *8:31 VSID Virtual Segment ID
   *
   *0     T=1:
   *1     Ks    Supervisor-state protection key
   *2     Kp    User-state protection key
   *3:11  BUID  Bus Unit ID
   *12:31 CNTRL_SPEC Device-specific date for I/O controller
   */
  /* Segment Register */
  const uint32_t SR_T  = 1 << 31;
  const uint32_t SR_Ks = 1 << 30;
  const uint32_t SR_Kp = 1 << 29;
  const uint32_t SR_N  = 1 << 28;

  inline void set_SR_T(uint32_t& val) {val |= SR_T;}
  inline void set_SR_Ks(uint32_t& val) {val |= SR_Ks;}
  inline void set_SR_Kp(uint32_t& val) {val |= SR_Kp;}
  inline void set_SR_N(uint32_t& val) {val |= SR_N;}

  inline bool check_SR_T(uint32_t val) {return val&SR_T;}
  inline bool check_SR_Ks(uint32_t val) {return val&SR_Ks;}
  inline bool check_SR_Kp(uint32_t val) {return val&SR_Kp;}
  inline bool check_SR_N(uint32_t val) {return val&SR_N;}

  inline uint32_t SR_VSID(uint32_t v) { return v & 0xffffff; }
  inline uint32_t SR_BUID(uint32_t v) { return (v >> 20) & 0x1ff; }
  inline uint32_t SR_CNTRL_SPEC(uint32_t v) { return v & 0xfffff; }
  inline uint32_t EA_SR(uint32_t v) { return (v >> 28) & 0xf; }
  inline uint32_t EA_PageIndex(uint32_t v) { return (v >> 12) & 0xffff; }
  inline uint32_t EA_Offset(uint32_t v) { return v & 0xfff; }
  inline uint32_t EA_API(uint32_t v) { return (v >> 22) & 0x3f; }
  inline uint32_t PA_RPN(uint32_t v) { return (v >> 12) & 0xfffff; }
  inline uint32_t PA_Offset(uint32_t v) { return v & 0xfff; }

  //-------------------------pte-------------------------
  /**
   *PTE0:
   *0     V     Entry valid(V = 1) or invalid(V = 0)
   *1:24  VSID  Virtual segment ID
   *25    H     Hash function identifier
   *26:31 API   Abbreviated page index

   *PTE1:
   * 0:19 RPN   Physical page number
   *20:22       Reserved
   *23    R     Reference bit
   *24    C     Change bit
   *25:28 WIMG  Memory/cache control bits
   *30:31 PP    Page protection bits
   */

  /* Values for PP (assumes Ks=0, Kp=1) */
  const uint32_t PP_RWXX = 0; /* Supervisor read/write, User none */
  const uint32_t PP_RWRX = 1; /* Supervisor read/write, User read */
  const uint32_t PP_RWRW = 2; /* Supervisor read/write, User read/write */
  const uint32_t PP_RXRX = 3; /* Supervisor read,       User read */

  const uint32_t PTE0_V = 1 << 31;
  const uint32_t PTE0_H = 1 << 6;
  const uint32_t PTE1_R = 1 << 8;
  const uint32_t PTE1_C = 1 << 7;
  const uint32_t PPC_PAGE_SHIFT = (1<<12) - 1;

  inline void set_PTE0_V(uint32_t& val) {val |= PTE0_V;}
  inline void set_PTE0_H(uint32_t& val) {val |= PTE0_H;}
  inline void set_PTE1_R(uint32_t& val) {val |= PTE1_R;}
  inline void set_PTE1_C(uint32_t& val) {val |= PTE1_C;}
  inline void set_PAGE_SHIFT(uint32_t& val) {val |= PPC_PAGE_SHIFT;}

  inline bool check_PTE0_V(const uint32_t& val) {return val&PTE0_V;}
  inline bool check_PTE0_H(const uint32_t& val) {return val&PTE0_H;}
  inline bool check_PTE1_R(const uint32_t& val) {return val&PTE1_R;}
  inline bool check_PTE1_C(const uint32_t& val) {return val&PTE1_C;}
  inline bool check_PAGE_SHIFT(const uint32_t& val) {return val&PPC_PAGE_SHIFT;}

  inline uint32_t PTE0_VSID(uint32_t v) { return(v >> 7) & 0xffffff; }
  inline uint32_t PTE0_API(uint32_t v) { return v & 0x3f; }
  inline uint32_t PTE1_RPN(uint32_t v) { return (v >> 12) & 0xfffff; }
  inline uint32_t PTE1_RPN_SHIFT(uint32_t v) { return v & 0xfffff000; }
  inline uint32_t PTE1_WIMG(uint32_t v) { return (v >> 3) & 0xf; }
  inline uint32_t PTE1_PP(uint32_t v) { return v & 3; }

  //--------------------------------------Interrupt--------------------------------
  const uint32_t INT_UNKNOWN       = 0x000;
  const uint32_t INT_SYS_RESET     = 0x100;
  const uint32_t INT_MACHINE_CHECK = 0x200;
  const uint32_t INT_DSI           = 0x300;     //Data Storage Interruption
  const uint32_t INT_ISI           = 0x400;     //Instruction Storage Interruption
  const uint32_t INT_EXT           = 0x500;     //External
  const uint32_t INT_ALIGNMENT     = 0x600;     //Alignment
  const uint32_t INT_PROGRAM       = 0x700;     //Program
  const uint32_t INT_NO_FPU        = 0x800;     //Floating-point Unavailable
  const uint32_t INT_DEC           = 0x900;     //Decrementer
  //Reserved 0xA00
  //Reserved 0xB00
  const uint32_t INT_SC            = 0xC00;     //System Call
  const uint32_t INT_TRACE         = 0xD00;     //Trace
  const uint32_t INT_FLOAT_ASSIST  = 0xE00;
  const uint32_t INT_PERF_MON      = 0xF00;     //Performance Monitor
  //Reserved 0xF10~0xFFF

  //interrupt flags
  const uint32_t PPC_EXC_PAGE  = 1<<30;
  const uint32_t PPC_EXC_PROT  = 1<<27;
  const uint32_t PPC_EXC_STORE = 1<<25;

  const uint32_t PPC_EXC_DSISR_PAGE  = 1<<30;
  const uint32_t PPC_EXC_DSISR_PROT  = 1<<27;
  const uint32_t PPC_EXC_DSISR_STORE = 1<<25;

  const uint32_t PPC_EXC_SRR1_PAGE  = PPC_EXC_DSISR_PAGE;
  const uint32_t PPC_EXC_SRR1_GUARD = 1<<28;
  const uint32_t PPC_EXC_SRR1_PROT  = PPC_EXC_DSISR_PROT;

  const uint32_t PPC_EXC_PROGRAM_FLOAT = 1<<20;
  const uint32_t PPC_EXC_PROGRAM_ILL   = 1<<19;
  const uint32_t PPC_EXC_PROGRAM_PRIV  = 1<<18;
  const uint32_t PPC_EXC_PROGRAM_TRAP  = 1<<17;

  /*
   * set if srr0 does not not contain the address of the intruction
   * causing the exception
   */
  const uint32_t INT_PROGRAM_NEXT  = 1<<16;
  const uint32_t KERNEL_BASE  = 0xC0000000;

} // namespace simsoc

#endif //PPC_TOOL_HPP
