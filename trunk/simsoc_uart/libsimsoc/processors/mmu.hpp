//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MMU_HPP
#define MMU_HPP

#include "libsimsoc/interfaces/dmi.hpp"
#include "libsimsoc/interfaces/tlm_helper.hpp"
#include "libsimsoc/module.hpp"
#include "libsimsoc/processors/common.hpp"
#include "tlb.hpp"
#include "host_memory.hpp"
#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <sys/mman.h>
#include <cerrno>
#include <stdexcept>
#include <csignal>

// This header file defines:
// - the enumerated types: mmu_data_type, mem_op_type.
// - the classes: MMU_Faults, MMU

namespace simsoc {

  /*
   * * definition of operation/data type
   */

  template <typename uint32_t>
  inline uint64_t swap_words(uint64_t data) {
    return (data<<32) | (data>>32);
  }

  typedef enum mmu_data_type {
    MMU_BYTE_TYPE			=0,
    MMU_HALF_TYPE			=1,
    MMU_WORD_TYPE			=3,
    MMU_DATA_TYPE			=4,
    MMU_CODE_TYPE			=5
  } mmu_data_type;

  typedef enum mem_op_type {
    MMU_READ	=0,
    MMU_WRITE	=1
  } mem_op_type;

  template <typename word_t>
  class MMU_Faults : public std::exception {
  public:
    word_t virt_addr;
    uint32_t fault, domain, isWrite;

    explicit MMU_Faults() :
      exception() {
    }

    MMU_Faults(word_t virt_addr_, uint32_t fault_, uint32_t domain_=0,
               uint32_t isWrite_=0) :
      exception(), virt_addr(virt_addr_), fault(fault_), domain(domain_),
      isWrite(isWrite_) {
    }

    virtual ~MMU_Faults() throw() {
    }

    virtual const char *what() const throw() {
      warning() <<"MMU Fault[" <<fault <<"] at va address: " <<std::hex
                <<virt_addr <<" domain: " <<domain <<" is write: " <<(bool)isWrite;
      return "MMU Page Fault Exception!";
    }
  };

  /*
   * definition of MMU
   */
  template <typename word_t>
  class MMU: public Module {
  public:

    // DMI related variable
    HostMemory<word_t> hmemory;

    // TLB related variable
    TLB<word_t> *iTLBs;
    TLB<word_t> *dTLBs;
    bool isUnified;	//if Unified, iTLBs == dTLBs
    bool user_mode;	//used for access permission check

    // interface with other components
    Processor *proc;	//to raise data fault exception
    tlm_utils::simple_initiator_socket<MMU> rw_socket;

    // Payload used for transactions
    tlm::tlm_generic_payload pl;

  public:
    MMU(sc_core::sc_module_name name, Processor *proc_);
    virtual ~MMU();

    void reset();

    // public MMU interface
    virtual uint8_t read_byte(word_t va);
    virtual void write_byte(word_t va,uint8_t data);
    virtual uint16_t read_half(word_t va);
    virtual void write_half(word_t va,uint16_t data);
    virtual uint32_t read_word(word_t va);
    virtual void write_word(word_t va,uint32_t data);
    virtual uint64_t read_double(word_t va);
    virtual void write_double(word_t va,uint64_t data);

    inline word_t addr_swizzling(word_t va,uint32_t datasize);
    unsigned int transport_dbg(tlm::tlm_generic_payload &payload);
    void invalidate_dm_ptr(sc_dt::uint64 start_range, sc_dt::uint64 end_range);

    uint32_t load_instr_32(word_t va);
    uint16_t load_instr_16(word_t va);

    //virtual interface for virtual to physical translation

    // This function combines the 2 old functions:
    // - virtual word_t va_context_switch(word_t va)
    // - virtual bool is_enable(word_t& va)
    virtual bool code_preprocess_and_is_enabled(word_t &addr) const {
      return data_preprocess_and_is_enabled(addr);
    };
    virtual bool data_preprocess_and_is_enabled(word_t &addr) const = 0;
    // return true if MMU is enabled (i.e., a call to virt_to_phy is necessary)

    virtual word_t virt_to_phy(word_t va,
                               mmu_data_type data_type/*used to check alignment*/,
                               mem_op_type op_type/*used to check permission*/,
                               TLB<word_t> *tlbs) = 0;


    virtual bool is_bigendian() const =0;
    virtual void handle_data_faults(word_t virt_addr, word_t fault,
                                    word_t domain, mem_op_type op_type=MMU_READ) =0;
    virtual void handle_instruction_faults(word_t virt_addr, word_t fault,
                                           word_t domain,
                                           mem_op_type op_type=MMU_READ) =0;
    virtual bool getTLBs() {return true;}

    void fetch_page(word_t virtual_page_id, //input
                    uint32_t *&target_code, //output
                    TranslationTableItem *&translated_page) { //output
      word_t va = virtual_page_id * TranslationPage::TR_PAGE_SIZE;
      word_t pa;
      if (code_preprocess_and_is_enabled(va)) {
        try {
          pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_READ,iTLBs);
          debug() <<std::hex <<"fetch page [" <<virtual_page_id <<"]->["
                  <<pa/TranslationPage::TR_PAGE_SIZE <<"]\n";
        } catch(MMU_Faults<word_t>& faults) {
          target_code = NULL;
          translated_page = NULL;
          // Take care: it is forbidden to raise an interrupt in fetch page!
          // Do not do that: handle_instruction_faults(faults.virt_addr,faults.fault,faults.domain);
          return;
        }
      } else {
        debug() <<std::hex <<"fetch page [" <<virtual_page_id <<"]\n";
        pa = va;
      }
      if (!hmemory.has_instruction_cache(pa))
        get_dmi_at_address(pa);
      if (hmemory.has_instruction_cache(pa)) {
        target_code = hmemory.raw32(pa); //todo: just for 32bit instructions now
        translated_page =
          &(*hmemory.get_code_table(pa))
          [hmemory.relative(pa)/TranslationPage::TR_PAGE_SIZE];
      } else {
        target_code = NULL;
        translated_page = NULL;
      }
    }

    // memory related operation
    void get_dmi_at_address(uint64_t addr);

    // memory accesses, either using DMI or transaction
    uint64_t memory_read_double(word_t addr);
    inline uint32_t memory_read_word(word_t addr);
    uint32_t memory_read_word__transaction(word_t addr); // this part is not inlined
    uint16_t memory_read_half(word_t addr);
    uint8_t memory_read_byte(word_t addr);
    void memory_write_double(word_t addr, uint64_t data);
    inline void memory_write_word(word_t addr, uint32_t data);
    void memory_write_word__transaction(word_t addr, uint32_t data);
    void memory_write_half(word_t addr, uint16_t data);
    void memory_write_byte(word_t addr, uint8_t data);
  };

  template<>
  inline uint32_t MMU<uint32_t>::addr_swizzling(uint32_t addr,uint32_t data_size){
    switch(data_size){
    case 1:
      return addr^3;
    case 2:
      return addr^2;
    case 4:
      return addr;
    default:
      error() <<"Data size " <<data_size <<"are not supported for addr swizzling!"
              <<"Only byte/harf/word address are supported!" <<std::endl;
      exit(1);
    }
  }

  template<>
  inline uint64_t MMU<uint64_t>::addr_swizzling(uint64_t addr,uint32_t data_size){
    switch(data_size){
    case 1:
      return addr^7;
    case 2:
      return addr^6;
    case 4:
      return addr^4;
    case 8:
      return addr;
    default:
      error() <<"Data size " <<data_size <<"are not supported for addr swizzling!"
              <<"Only byte/harf/word/double word address are supported!" <<std::endl;
      exit(1);
    }
  }

  template<>
  inline void MMU<uint32_t>::memory_write_word(uint32_t addr, uint32_t data){
    if (hmemory.dmi_address(addr))
      *hmemory.raw32(addr)=data;
    else
      memory_write_word__transaction(addr,data);
  }

  template<>
  inline uint32_t MMU<uint32_t>::memory_read_word(uint32_t addr) {
    if (hmemory.dmi_address(addr))
      return *hmemory.raw32(addr);
    else
      return memory_read_word__transaction(addr);
  }

  template<>
  inline void MMU<uint64_t>::memory_write_word(uint64_t addr, uint32_t data) {
    if (is_bigendian())
      addr = addr_swizzling(addr,4);
    if (hmemory.dmi_address(addr))
      *hmemory.raw32(addr) = data;
    else
      memory_write_word__transaction(addr,data);
  }

  template<>
  inline uint32_t MMU<uint64_t>::memory_read_word(uint64_t addr) {
    if (is_bigendian())
      addr = addr_swizzling(addr,4);
    if (hmemory.dmi_address(addr))
      return *hmemory.raw32(addr);
    else
      return memory_read_word__transaction(addr);
  }

} // namespace simsoc

// We do not include "mmu.tpp" here,
// because we only use a restricted number of parameter values.
// Code for these parameter values is created in "mmu.cpp".

#endif // MMU_HPP
