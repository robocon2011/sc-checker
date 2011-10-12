//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_MMU_HPP
#define MIPS_MMU_HPP

#include <map>
#include <signal.h>
#include <sys/mman.h>
#include <errno.h>

#include "libsimsoc/processors/mips/mips_tlb.hpp"
#include "libsimsoc/interfaces/dmi.hpp"
#include "libsimsoc/processors/mmu.hpp"
#include "libsimsoc/processors/mips/mips_registers.hpp"
#include "libsimsoc/processors/mips/mips_coprocessor.hpp"

namespace simsoc {

// typedef enum {
//   // the 32-bit compatibility segments
//   kseg3, sseg, kseg1,kseg0,kuseg,
//   //the 64 bits segment
//   xkseg,// kernel segment in 64 bits
//   // the two implementation defined 64 bits(xkphys)
//   xkphys0, xkphys1,
//   xkphys_uncached, xkphys_cached, // 2 and 3
//   xkphys4, xkphys5, xkphys6, xkphys7, // impl. defined
//   //supervisor and 64-bit user space
//   xsseg,xkuseg,
// // should never happen, used to avoid compiler warnings
//   SEG_ERROR
// } MipsMemorySegment;

//****************************************************
static const uint32_t BIT31 = 0x1 << 31;
static const uint32_t MAPPED_FLAG = 0x1 << 30;
static const uint32_t UNCACHED_OR_KERNEL_FLAG = 0x1 << 29;
// 100 Kernel UNMAPPED both 29 and 30 off
static const uint32_t KSEG0_MASK =  BIT31;
// 101 Kernel UNMAPPED UNCACHED 29 on and 30 off
static const  uint32_t KSEG1_MASK =  BIT31 | UNCACHED_OR_KERNEL_FLAG;
// 110 Supervisor MAPPED 29 off  30 set
static const  uint32_t SSEG_MASK =  BIT31 | MAPPED_FLAG  ;
// 111 Kernel MAPPED both 29 and 30 set
static const uint32_t KSEG3_MASK =  BIT31 | MAPPED_FLAG | UNCACHED_OR_KERNEL_FLAG;
// 111 Mask to locate 32 bits segment
static const uint32_t ADDR32_MASK =  BIT31 | MAPPED_FLAG | UNCACHED_OR_KERNEL_FLAG ;
  static const uint32_t KSEG0_FLAG = KSEG0_MASK>>29;
  static const uint32_t KSEG1_FLAG = KSEG1_MASK>>29;
  static const uint32_t SSEG_FLAG = SSEG_MASK>>29;
  static const uint32_t KSEG3_FLAG = KSEG3_MASK>>29;

// These constants are specific to 64 bits addressing
  static const uint64_t COMPATIBILITY = 0xFFFFFFFF80000000llu;
  static const uint64_t BIT63 = 1llu << 63;
  static const uint64_t BIT62 = 1llu << 62;
  static const uint64_t BIT61 = 1llu << 61;
  static const uint64_t BIT60 = 1llu << 60;
  static const uint64_t BIT59 = 1llu << 59;

// 00 mask
static const  uint64_t USER_MASK64 = 0;
// 01
static const  uint64_t SUPERVISOR_MASK64 = BIT62 ;
// 10
static const  uint64_t XKPHYS_MASK64 = BIT63 ;
// 11
static const  uint64_t KERNEL_MASK64 = BIT63 | BIT62;

// Mask to locate 64 bits extended segment
static const  uint64_t ADDR64_MASK =  BIT63 | BIT62;
static const  uint64_t ADDR64_PHYS_MASK = BIT63 | BIT62 | BIT61 | BIT60 | BIT59;
// uncache mask for physical address access by the kernel

static const  uint64_t ADDR64_PHYS0_FLAG = 0;
static const  uint64_t ADDR64_PHYS1_FLAG = BIT59;
static const  uint64_t ADDR64_UNCACHED_FLAG = BIT60;
static const  uint64_t ADDR64_CACHED_FLAG = BIT60 | BIT59;
static const  uint64_t ADDR64_PHYS4_FLAG = BIT61;
static const  uint64_t ADDR64_PHYS5_FLAG = BIT61 | BIT59;
static const  uint64_t ADDR64_PHYS6_FLAG = BIT61 | BIT60;
static const  uint64_t ADDR64_PHYS7_FLAG = BIT61 | BIT60 | BIT59;

typedef enum mips_mmu_fault_t
  {
    TLB_DIRTY_ENTRY,
    TLB_INVALID_ENTRY,
    TLB_NOMATCH,
    MMU_BADADDR
  } mips_mmu_fault_t;


//mmu class definition
template <typename word_t>
class MIPS_MMU:public MMU<word_t>
{
public:

  /*initilization */
  MIPS_MMU(sc_core::sc_module_name name, MIPS_Processor<word_t> *proc_);

  uint16_t load_instr_16(word_t addr) {
    error() <<std::hex <<"load 16bit instruction at [" <<addr <<"]" <<std::endl;
    exit(-1);
  }

  word_t virt_to_phy(word_t va,
                     mmu_data_type data_type/*used to check alignment*/,
                     mem_op_type op_type/*used to check permission*/,
                     TLB<word_t> *tlbs);

  //tlb related operation
  void do_tlbp(); //search entry and put index to index register
  void do_tlbr();      	        //read tlb entry according to the index register
  void do_tlbwi();	        //write tlb entry according to the index register
  void do_tlbwr();	        //write tlb entry according to the random register
  void set_tlbEntry(MIPS_TLBEntry<word_t>* entry);
  void get_tlbEntry(MIPS_TLBEntry<word_t>* entry);

private:
  //coprocessor related operation
  MIPS_Coprocessor<word_t> *cp0;
  MIPS_Processor<word_t> *mips_proc;
  bool data_preprocess_and_is_enabled(word_t& va) const; // called outsize try..catch..
  void check_perm(word_t &va) const; // generate fault if not permitted

  void end_of_elaboration() {
    assert(cp0);
    cp0->set_tlb_size(this->dTLBs->size);
  }

  inline bool is_bigendian() const {
    return cp0->is_big_endian();
  }

  inline MMU_Mode mmu_mode() const {
    return cp0->status().ksu;
  }

  //tlb related operation
  bool getTLBs();

  void check_alignment(word_t va, mmu_data_type data_type);

  //translation related operation
  void check_access(word_t va,
		    MIPS_TLBEntry<word_t> *mipsTLBEntry,
		    mem_op_type op_type);

  void handle_data_faults(word_t virt_addr,
			  word_t fault,
			  word_t domain,
			  mem_op_type op_type=MMU_READ);

  void handle_instruction_faults(word_t virt_addr,
				 word_t fault,
				 word_t domain,
				 mem_op_type op_type=MMU_READ) {}
};

} // namespace simsoc

// We do not include "mips_mmu.tpp" here,
// because we only use a restricted number of parameter values.
// Code for these parameter values is created in "mips_mmu.cpp".

#endif // MIPS_MMU_HPP
