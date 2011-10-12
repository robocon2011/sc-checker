//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_COPROCESSOR_HPP
#define MIPS_COPROCESSOR_HPP

#include "mips_base.hpp"
#include "mips_registers.hpp"
#include <libsimsoc/bitwise_operator.hpp>
#include <libsimsoc/module.hpp>
#include <cassert>
#include <cstdlib>

namespace simsoc {

  template <typename word_t> class MIPS_MMU;

  template <typename word_t>
  class MIPS_Coprocessor: public Module {
  public:

    //mmu related register
    //index into the TLB array
    static const uint32_t CP0_INDEX = 0;
    //mmu related register,Read Only
    //randomly generated index into the TLB array
    static const uint32_t CP0_RANDOM = 1;
    //mmu related register
    //Low-order portion of the TLB entry for even-numbered virtual pages
    static const uint32_t CP0_ENTRYLO0 = 2;
    //mmu related register
    //Low-order portion of the TLB entry for odd-numbered virtual pages
    static const uint32_t CP0_ENTRYLO1 = 3;
    //mask:
    static const word_t CP0_ENTRYLO_PFN_MASK = ~0x3f;
    static const word_t CP0_ENTRYLO_C_MASK = 0x38;
    static const word_t CP0_ENTRYLO_D_MASK = 0x4;
    static const word_t CP0_ENTRYLO_V_MASK = 0x2;
    static const word_t CP0_ENTRYLO_G_MASK = 0x1;

    //mmu related register
    //pointer to page table entry in memory
    static const uint32_t CP0_CONTEXT = 4;
    //mmu related register
    //control for variable page size in TLB entries
    static const uint32_t CP0_PAGEMASK = 5;
    //mask
    static const word_t CP0_PAGEMASK_MASK=0x1fffe000;
    //mmu related register
    //controls the number of fixed TLB entries
    static const uint32_t CP0_WIRED = 6;
    //reports the address for the most recent address-related exception
    static const uint32_t CP0_BADADDR = 8;
    //processor cycle count
    static const uint32_t CP0_COUNT = 9;
    //mmu related register
    //high-order portion of the tlb entry
    static const uint32_t CP0_ENTRYHI = 10;
    //mask
    static const word_t CP0_ENTRYHI_VPN_MASK = ~0x1fff;
    static const word_t CP0_ENTRYHI_ASID_MASK = 0xff;

    //Timer interrupt control
    static const uint32_t CP0_COMPARE = 11;
    //Processor status and control
    static const uint32_t CP0_STATUS = 12;
    //mask
    static const word_t CP0_STATUS_IE = 0; //global interrupt enable
    static const word_t CP0_STATUS_EXL = 1; //exception level
    static const word_t CP0_STATUS_ERL = 2; //error level
    static const word_t CP0_STATUS_KSU = 0x18; //bit4-3
    static const word_t CP0_STATUS_TS = 21; //TLB shutdown
    static const word_t CP0_STATUS_RE = 25; //reverse endianness in usr mode
    //Cause of last general exception
    static const uint32_t CP0_CAUSE = 13;
    //mask

    //Program counter at last exception
    static const uint32_t CP0_EPC = 14;
    //Processor identification and revision
    static const uint32_t CP0_PRID = 15;
    //Configuration register
    static const uint32_t CP0_CONFIG = 16;
    //mask
    static const word_t CP0_CONFIG_BE = 1<<15;

    static const uint32_t CP0_LLADDR = 17;
    static const uint32_t CP0_WATCHLO = 18;
    static const uint32_t CP0_WATCHHI = 19;
    //mmu related register
    static const uint32_t CP0_XCONTEXT = 20;
    static const uint32_t CP0_ECC = 26;
    static const uint32_t CP0_CACHEERR = 27;
    static const uint32_t CP0_TAGL0 = 28;
    static const uint32_t CP0_TAGHI = 29;
    static const uint32_t CP0_ERROREPC = 30;


    MIPS_Coprocessor(sc_core::sc_module_name name,
                     MIPS_Processor<word_t> *proc,
                     MIPS_MMU<word_t> *mmu);
    virtual ~MIPS_Coprocessor() {}

    word_t regs[32];
    MIPS_CauseRegister reg_cause;
    MIPS_StatusRegister reg_status;

    word_t read_cp0(uint32_t n);
    void write_cp0(uint32_t n, word_t Rd_Value);

    /*
     * Index register related function
     */

    //tlbwi tlbr related operation
    inline uint32_t get_tlb_index(){
      //works because mips tlb size is between 16-64 entries
      assert(tlb_size);
      return bits<uint32_t>(regs[CP0_INDEX],index_N-1,0);
    }
    //tlbp related operation
    inline void set_tlb_index(bool match,uint32_t value=0){
      assert(tlb_size);
      if(match){
        assert(value<tlb_size);
        regs[CP0_INDEX] = 0;
        regs[CP0_INDEX] |= value;
      }else
        {
          regs[CP0_INDEX] = 0x80000000;
        }
    }

    //return random index for tlbwr (TLB Write Random)
    inline uint32_t get_random(){
      assert(tlb_size);
      srand(regs[CP0_RANDOM]);
      regs[CP0_RANDOM] = rand()%(index_N-regs[CP0_WIRED])+regs[CP0_WIRED];
      return regs[CP0_RANDOM];
    }

    /*
     * EntryLo register related function
     */

    inline void set_entrylo0(word_t pfn,uint8_t c,uint8_t d,uint8_t v,uint8_t g) {
      regs[CP0_ENTRYLO0] = pfn;
      regs[CP0_ENTRYLO0] |= g | (v<<1) | (d<<2) | (c<<3);
    }

    inline void set_entrylo1(word_t pfn,uint8_t c,uint8_t d,uint8_t v,uint8_t g) {
      regs[CP0_ENTRYLO1] = pfn;
      regs[CP0_ENTRYLO1] |= g | (v<<1) | (d<<2) | (c<<3);
    }

    inline void get_entrylo0(word_t& pfn,uint8_t& c,bool& d,bool& v,bool& g) const
    {
      word_t pagemask=0;
      get_pagemask(pagemask);
      word_t entrylo0=regs[CP0_ENTRYLO0];
      g = (bool)(entrylo0 & CP0_ENTRYLO_G_MASK);
      v = (bool)((entrylo0 & CP0_ENTRYLO_V_MASK)>>1);
      d = (bool)((entrylo0 & CP0_ENTRYLO_D_MASK)>>2);
      c = (uint8_t)((entrylo0 & CP0_ENTRYLO_C_MASK)>>3);
      pfn = (entrylo0 & CP0_ENTRYLO_PFN_MASK) & ~pagemask;
    }

    inline void get_entrylo1(word_t& pfn,uint8_t& c,bool& d,bool& v,bool& g) const
    {
      word_t pagemask=0;
      get_pagemask(pagemask);
      word_t entrylo1=regs[CP0_ENTRYLO1];
      g = (bool)(entrylo1 & CP0_ENTRYLO_G_MASK);
      v = (bool)((entrylo1 & CP0_ENTRYLO_V_MASK)>>1);
      d = (bool)((entrylo1 & CP0_ENTRYLO_D_MASK)>>2);
      c = (uint8_t)((entrylo1 & CP0_ENTRYLO_C_MASK)>>3);
      pfn = (entrylo1 & CP0_ENTRYLO_PFN_MASK) & ~pagemask;
    }

    /*
     * Context register related function
     */
    inline void set_contex_badvpn(word_t va){
      word_t vpn=va & ~0x1fff;
      regs[CP0_ENTRYLO1]|= vpn>>9;
    }

    /*
     * PageMask register related function
     */
    //interface to get tlb entry
    inline void get_pagemask(word_t& mask) const {
      mask = regs[CP0_PAGEMASK] & CP0_PAGEMASK_MASK;
      mask |= 0x1fff;
    }
    //interface to set tlb entry
    inline void set_pagemask(word_t mask){
      regs[CP0_PAGEMASK]= mask & CP0_PAGEMASK_MASK;
    }

    /*
     * Wired register related function
     */
    inline void set_wired(word_t value){
      assert(tlb_size);
      regs[CP0_WIRED] = 0;
      regs[CP0_WIRED] |= bits<word_t>(value,index_N-1,0);
    }

    /*
     * BadAddr register related function
     */
    //interface to set mmu faults
    inline void set_bad_addr(word_t va){
      regs[CP0_BADADDR]=va;
    }

    /*
     * EntryHi register related function
     */
    inline void set_entryhi(word_t va,word_t asid){
      regs[CP0_ENTRYHI] = va & CP0_ENTRYHI_VPN_MASK;
      regs[CP0_ENTRYHI]|= asid & CP0_ENTRYHI_ASID_MASK;
    }

    inline void get_entryhi(word_t& vpn2,uint8_t& asid) const
    {
      word_t pagemask=0;
      get_pagemask(pagemask);
      vpn2 = (regs[CP0_ENTRYHI] & CP0_ENTRYHI_VPN_MASK) & ~pagemask;
      asid = (uint8_t)(regs[CP0_ENTRYHI] & CP0_ENTRYHI_ASID_MASK);
    }

    inline word_t get_entryhi_vpn() const {
      return regs[CP0_ENTRYHI] & CP0_ENTRYHI_VPN_MASK;
    }

    inline void set_entryhi_vpn(word_t va) {
      word_t vpn= va & CP0_ENTRYHI_VPN_MASK;
      regs[CP0_ENTRYHI]|= vpn;
    }
    /*
     * Status register related function
     */
    inline const MIPS_StatusRegister& status() const {
      return reg_status;
    };
    inline MIPS_StatusRegister& status() {
      return reg_status;
    };

    inline bool user_add64_enable() const {
      return reg_status.um;
    };
    inline bool kernal_add64_enable() const {
      return reg_status.sx;
    };
    inline bool supervisor_add64_enable() const {
      return reg_status.ux;
    };

    /*
     * Status register related function
     */
    inline MIPS_CauseRegister& cause(){
      return reg_cause;
    };

    /*
     * EPC register related function
     */
    inline void set_epc(word_t addr)
    {
      regs[CP0_EPC]= addr;
    };

    /*
     * Config register related function
     */
    inline bool is_big_endian()
    {
      return (bool)(regs[CP0_CONFIG]&CP0_CONFIG_BE);
    };

    inline void set_tlb_size(const uint32_t size){
      tlb_size=size;
      index_N=fls(size)-1;
    };

  protected:
    MIPS_Processor<word_t> &mips_processor;
    MIPS_MMU<word_t> &mips_mmu;

    uint32_t tlb_size;
    uint32_t index_N;
  };

} // namespace simsoc

// We do not include "mips_coprocessor.tpp" here,
// because the user can only use a restricted number of parameter values.
// Code for these parameter values is created in "mips_coprocessor.cpp".

#endif // MIPS_COPROCESSOR_HPP
