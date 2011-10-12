//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_MMU_HPP_
#define PPC_MMU_HPP_

#include "ppc_tlb.hpp"
#include "ppc_cpu.hpp"
#include "libsimsoc/interfaces/dmi.hpp"

namespace simsoc {

  class PPC_Processor;

  class PPC_MMU:public MMU<BUS32>
  {
  public:
    typedef uint32_t word_t;

    PPC_CPU &cpu;
    bool bat;

#ifdef CACHE
    typedef enum {
      LRU	=0,
      FIFO	=1
    } cache_replace_t;

    typedef enum {
      MODIFY,
      EXCLUSIVE,
      SHARED,
      INVALID
    } status_t;
    const cache_replace_t replace = LRU;

    typedef struct block {
      block_t* prev;
      block_t* next;
      uint32_t addr_tag;
      status_t status;//110 modified, 100 exclusive, 101 shared, 0xx invalid
      uint8_t block[32];
    } block_t;

    const uint32_t CACHE_SETS_L1 = 0x80;
    const uint32_t BLOCKS_PER_SET_L1 = 8;
    const uint32_t BLOCK_SIZE_LOG_L1 = 5;
    const uint32_t BLOCK_SIZE_L1 = 1 << BLOCK_SIZE_LOG_L1;
    const uint32_t CACHE_SETS_L2 = 0x1000;
    const uint32_t BLOCKS_PER_SET_L2 = 8;
    const uint32_t BLOCK_SIZE_LOG_L2 = 5;
    const uint32_t BLOCK_SIZE_L2 = 1 << BLOCK_SIZE_LOG_L2;
    block_t icache[CACHE_SETS_L1][BLOCKS_PER_SET_L1];
    block_t dcache[CACHE_SETS_L1][BLOCKS_PER_SET_L1];
    block_t cache[CACHE_SETS_L2][BLOCKS_PER_SET_L2];
    block_t* ihead[CACHE_SETS_L1];
    block_t* dhead[CACHE_SETS_L1];
    block_t* head[CACHE_SETS_L2];
#endif

    PPC_MMU(sc_core::sc_module_name name, PPC_Processor *proc_);
    ~PPC_MMU(){};

    uint8_t read_byte(uint32_t va);
    void write_byte(uint32_t va,uint8_t data);
    uint16_t read_half(uint32_t va);
    void write_half(uint32_t va,uint16_t data);
    inline uint32_t read_word(uint32_t va);
    inline void write_word(uint32_t va,uint32_t data);
    inline uint32_t load_instr_32(uint32_t va);
    uint16_t load_instr_16(uint32_t va);

    uint32_t virt_to_phy(const uint32_t va, const mmu_data_type data_type,
                         const mem_op_type op_type, TLB<word_t> *tlbs);
  public:

    // bool is_enable(uint32_t& va, mmu_data_type data_type= MMU_DATA_TYPE);
    // -> replaced by:
    bool data_preprocess_and_is_enabled(uint32_t& va) const;
    inline bool data_preprocess_and_is_enabled() const;
    inline bool code_preprocess_and_is_enabled(uint32_t& va) const;
    inline bool code_preprocess_and_is_enabled() const;

    bool is_bigendian() const {
      return true;
    }

    // field virt_addr is already set
    // mask of tlbEntry is already set to PAGE_SHIFT
    // pte1 has to be set.
    void translation_table_walk(PPC_TLBEntry &tlbEntry,
                                const mmu_data_type data_type,
                                const mem_op_type op_type);

    void handle_data_faults(uint32_t virt_addr, uint32_t fault,
                            uint32_t domain, mem_op_type op_type=MMU_READ);
    void handle_instruction_faults(uint32_t virt_addr, uint32_t fault,
                                   uint32_t domain, mem_op_type op_type=MMU_READ);

#ifdef CACHE
    uint32_t cache_search(uint32_t pa, uint32_t data, mmu_data_type data_type,
                          mem_op_type op_type, mmu_data_type data_code);
    uint32_t cache_search_l2(uint32_t pa, uint32_t data, mmu_data_type data_type,
                             mem_op_type op_type);
    void update_cache_l1(uint32_t addr, mmu_data_type code_data);
    void update_cache_l2(uint32_t addr);
#endif
  private:
    // field virt_addr is already set
    // mask of tlbEntry is already set to PAGE_SHIFT
    // pte1 has to be set.
    bool bat_translate(const mmu_data_type data_type,
                       const mem_op_type op_type, PPC_TLBEntry &tlbEntry);
    bool seg_translate(const mmu_data_type data_type,
                       const mem_op_type op_type, PPC_TLBEntry &tlbEntry);

  }; // class PPC_MMU

  bool PPC_MMU::data_preprocess_and_is_enabled() const {
    return check_MSR_DR(cpu.msr);
  }

  bool PPC_MMU::code_preprocess_and_is_enabled(uint32_t& va) const {
    return check_MSR_IR(cpu.msr);
  }

  bool PPC_MMU::code_preprocess_and_is_enabled() const {
    return check_MSR_IR(cpu.msr);
  }

  uint32_t PPC_MMU::read_word(uint32_t va) {
    try {
      if (!data_preprocess_and_is_enabled()) {
        const uint32_t data = memory_read_word(va);
        debug() <<std::hex<<"read word at ["<<va<<"] return "<<data <<std::endl;
        return data;
      } else {
        const uint32_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_READ,dTLBs);
#ifdef CACHE
        uint32_t data=cache_search(pa, 0, MMU_WORD_TYPE, MMU_READ, MMU_WORD_TYPE);
#else
        const uint32_t data = memory_read_word(pa);
#endif
        debug() <<std::hex<<"read word at ["<<va<<"]->["<<pa<<"] return "<<data<<std::endl;
        return data;
      }
    } catch (MMU_Faults<BUS32>& faults) {
      handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
      return 0;
    }
  }

  void PPC_MMU::write_word(uint32_t va, uint32_t data) {
    try {
      if (!data_preprocess_and_is_enabled()) {
        debug() <<std::hex<<"write word "<<data<<" at ["<<va<<"]"<<std::endl;
        memory_write_word(va,data);
      } else {
        const uint32_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_WRITE,dTLBs);
        debug() <<std::hex<<"write word "<<data<<" at ["<<va<<"]->["<<pa<<"]"<<std::endl;
#ifdef CACHE
        cache_search(pa, data, MMU_WORD_TYPE, MMU_WRITE, MMU_WORD_TYPE);
#else
        memory_write_word(pa,data);
#endif
      }
    } catch(MMU_Faults<BUS32>& faults) {
      handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
    }
  }

   uint32_t PPC_MMU::load_instr_32(uint32_t va){
    try{
      if (!code_preprocess_and_is_enabled()) {
        debug()<<std::hex<<"load instruction at ["<<va<<"]"<<std::endl;
        return memory_read_word(va);
      } else {
        uint32_t pa=virt_to_phy(va, MMU_CODE_TYPE, MMU_READ, iTLBs);
        debug()<<std::hex<<"load instruction at ["<<va<<"]->["<<pa<<"]"<<std::endl;
#ifdef CACHE
        return cache_search(pa, 0, MMU_CODE_TYPE, MMU_READ, MMU_CODE_TYPE);
#else
        return  memory_read_word(pa);
#endif
      }
    }catch(MMU_Faults<BUS32>& faults)
      {
        handle_instruction_faults(faults.virt_addr,faults.fault,faults.domain);
        return 0;
      }
  }

} // namespace simsoc

#endif /* PPC_MMU_HPP_ */
