//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_CPU_HPP
#define PPC_CPU_HPP

#include "ppc_tool.hpp"
#include <libsimsoc/display.hpp>
#include <cstdlib>
#include <cstring>
#include <inttypes.h>

namespace simsoc {

  // special types to display general purpose register
  struct PPC_AsmId: Printable {
    uint8_t id;
    PPC_AsmId(uint8_t n): id(n) {}
    virtual std::ostream &display(std::ostream&) const;
  };

  struct PPC_BCId: Printable{
    uint8_t id;
    PPC_BCId(uint8_t n): id(n) {}
    virtual std::ostream &display(std::ostream&) const;
  };

  struct PPC_CRId: Printable{
    uint8_t id;
    PPC_CRId(uint8_t n): id(n) {}
    virtual std::ostream &display(std::ostream&) const;
  };

  class PPC_CPU: public Printable {
  public:
    PPC_CPU(int coreId = 0);

    //--------------------user model--UISA------------------------
    uint32_t ctr;	       //Count Register CTR, SPR 9
    uint32_t xer;	       //Fixed-Point Exception Register, SPR 1
    uint32_t lr;	       //Link Register, SPR 8
    uint32_t gpr[32];      //General-purpose Register
    uint32_t cr;           //Condition Register

    static const uint32_t TBF_RATIO = 10;
    union {
      uint32_t _tbr[2];
      uint64_t tbr; //Time Base Facility(Read Only), TBR 268, 269
    } tbr;

    uint64_t ptbr;         //more precise tbr

    uint32_t upmc[6];      //Performance Counters, SPR 937,938,941,942,929,930
    uint32_t usiar;        //Sampled Instruction Address, SPR 939
    uint32_t ummcr[3];     //Monitor Control, SPR 936,940,928

    uint32_t vrsave;       //Vector Save/Restore Register, SPR 256
    uint32_t vscr;         //Vector Status and Control Register
    uint32_t vr[32];       //Vector Registers
    uint64_t fpr[32];      //Floating-point Register

    //--------------------supervisor model--OEA------------------
    //Configuration Registers
    uint32_t hid[2];       //Hardware Implementation Register, SPR 1008, 1009
    static const uint32_t svr = 0x80900100;  //System Version Register, SPR 286
    static const uint32_t pvr = 0x80040010;  //Processor Version Register, SPR 287
    uint32_t msr;          //Machine State Register
    uint32_t pir;	       //Processor Identification Register, SPR 1023

    //Memory Management Registers
    uint32_t ibatu[8];      //instruction BAT registers
    uint32_t ibatl[8];
    uint32_t dbatu[8];
    uint32_t dbatl[8];
    uint32_t sr[16];       //Segment Registers
    uint32_t ptehl;        //PTE Hige/Low Register, SPR 981
    uint32_t ptelo;        //PTE Hige/Low Register, SPR 982
    uint32_t tlbmiss;       //TLB Miss Register, SPR 980
    uint32_t sdr1;	       //page table base address, SPR 25

    //Interrupt Handling Registers
    uint32_t sprg[8];      //SPRGs, SPR 272-279
    uint32_t dar;          //Data address Register, SPR 19
    uint32_t dsisr;        //SPR 18
    uint32_t srr[2];       //Save and Restore Register, SPR 26, 27

    //Cache/Memory Subsystem Register
    uint32_t ldstcr;        //Load/Store Control Register, SPR 1016
    uint32_t msscr0;        //Memory Subsystem Status Control Reg, SPR 1014
    uint32_t msssr0;        //SPR 1015
    uint32_t ictrl;         //Instruction Cache/Interrupt Control Reg, SPR 1011
    uint32_t ldstdb;         //Load/Store Debug, SPR 1012

    //Miscessaneous Registers
    uint32_t dec;	       //Decrementer Register, SPR 22
    uint64_t pdec;         //more precise dec
    uint32_t ear;	       //External Access Register, SPR 282
    //uint32_t tb[2];        //Time Base (For Writing), SPR 284,285
    uint32_t iabr;         //Instruction Address Breakpoint Register, SPR 1010
    uint32_t dabr;         //Data Addrress Breakpoint Register, SPR 1013

    uint32_t ictc;         //Instruction Cache Throttling Control Register, SPR1019

    //--------------------
    uint32_t reserve;
    bool     have_reservation;
    uint32_t pc;
    uint32_t npc;

    //--------------------
    //bool something_pending;

    void update_CR_field(uint8_t field,const uint8_t value) {
      const uint32_t shift_bits = (7 - field) * 4;
      const uint32_t mask = 0xf << shift_bits;
      cr &= ~mask;
      cr |= (value & 0xf)<<shift_bits;
    }

    std::ostream& display(std::ostream& os) const;
  };

} // namespace simsoc


#endif //PPC_CPU_HPP
