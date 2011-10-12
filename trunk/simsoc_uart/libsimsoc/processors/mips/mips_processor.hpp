//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_PROCESSOR_HPP
#define MIPS_PROCESSOR_HPP

#include "mips_base.hpp"
#include "mipspi.hpp"
#include "mips_mmu.hpp"
#include "mips_coprocessor.hpp"
#include "mips_registers.hpp"
#include "mips_decode.hpp"
#include "mips_translation_page.hpp"
#include "libsimsoc/processors/processor.hpp"
#include "libsimsoc/processors/iss.hpp"
#include "libsimsoc/components/elf_loader.hpp"
#include "libsimsoc/translation_table.hpp"
#include "libsimsoc/tools/debugger/debugger.hpp"
//#include "mips_debugger.hpp"
#include <ostream>

namespace simsoc {
  
  template <typename word_t>
  class MIPS_Debugger;

  template <typename word_t>
  class MIPS_Processor: public Processor,
                        public SignalTarget<bool> {
    friend class MIPS_Debugger<word_t>;

  public:
    typedef MIPS_Instruction<word_t> Instruction;
    typedef MIPS_PseudoInstruction<word_t> PseudoInstruction;

    static const uint8_t RA = 31;
    static const uint8_t S8 = 30;
    static const uint8_t SP = 29;
    static const uint8_t GP = 28;
    static const uint8_t K1 = 27;
    static const uint8_t K0 = 26;
    static const uint8_t T9 = 25;
    static const uint8_t T8 = 24;
    static const uint8_t S7 = 23;
    static const uint8_t S6 = 22;
    static const uint8_t S5 = 21;
    static const uint8_t S4 = 20;
    static const uint8_t S3 = 19;
    static const uint8_t S2 = 18;
    static const uint8_t S1 = 17;
    static const uint8_t S0 = 16;
    static const uint8_t T7 = 15;
    static const uint8_t T6 = 14;
    static const uint8_t T5 = 13;
    static const uint8_t T4 = 12;
    static const uint8_t T3 = 11;
    static const uint8_t T2 = 10;
    static const uint8_t T1 = 9;
    static const uint8_t T0 = 8;
    static const uint8_t A3 = 7;
    static const uint8_t A2 = 6;
    static const uint8_t A1 = 5;
    static const uint8_t A0 = 4;
    static const uint8_t V1 = 3;
    static const uint8_t V0 = 2;
    static const uint8_t AT = 1;
    static const uint8_t R0 = 0;

    MIPS_Instruction<word_t> *current_instruction;
    MIPS_TranslationPage<word_t> *current_page;

    word_t epc;
    word_t depc;
    word_t pc;
    word_t hi;
    word_t lo;
    bool hilo_predictable;
    word_t regs[32];
    bool LLbit;

    ISS<MIPS_Processor<word_t> > iss;
    MIPS_MMU<word_t> mmu;
    MIPS_Coprocessor<word_t> cp0;

    SignalTargetPort<bool> hard_port0;
    SignalTargetPort<bool> hard_port1;
    SignalTargetPort<bool> hard_port2;
    SignalTargetPort<bool> hard_port3;
    SignalTargetPort<bool> hard_port4;
    SignalTargetPort<bool> mixed_port;

    // end of member data variables

    // SC_HAS_PROCESS(MIPS_Processor);
    MIPS_Processor(sc_core::sc_module_name name,
                   int processor_id = 0);
    ~MIPS_Processor();

    // methods for initialization, virtual pure in processor_base.hpp
    void set_pc(uint64_t pc);
    uint64_t get_pc() const {return pc;}
    void set_sp(uint64_t sp);
    uint64_t get_gp_register(size_t n) const; // gp as general purpose
    void set_gp_register(size_t n, uint64_t data); // gp as general purpose
    void set_endian_little() {}

    void set_GP_register(word_t gp_value); // the register named GP in MIPS architecture


    tlm::tlm_initiator_socket<> &get_rw_port();
    SignalTargetPort<bool> &get_it_port();
    const TranslationPage *get_current_page() const {return current_page;}

    SimulationMode max_mode_available() const {return DYN_TRANS_SPEC;}

    // methods used by Core Template
    // to be extended in the future
    int bus_width() {return sizeof(word_t)*8;}
    MIPS_PseudoInstruction<word_t>* get_branch_on_same_page() {
      error() << "MIPS branch same page not yet implemented\n" ;
      return NULL;
    }

    // fetching:
    Instruction *fetch_instruction();
    inline Instruction *fetch_instr_from_cache();
    Instruction *fetch_from_cache__nopage();
    MIPS_TranslationPage<word_t> *fetch_from_cache__decode(const uint32_t page_id,
                                                           uint32_t *const host_address);
    Instruction **get_current_instr_ptr();

    static inline MIPS_TranslationPage<word_t>*& select_page(TranslationTableItem *tti);

    // *** other data:

    sc_core::sc_event it_event;

    // Methods
    void read_hilo(); // call this function each time HI or LO are read
    void set_hilo(); // call this function when HI or LO contains PREDICATABLE values
    void unset_hilo(); // call this function when HI or LO contains UNPREDICATABLE values

    // statistics computation:
    virtual void update_statistics(MIPS_Instruction<word_t> *) {}
    virtual void write_statistics(std::ostream& os = std::cout) {}
    virtual void read_statistics(std::istream& is) {}
    virtual void raise_interrupt();

    // interrupts:
    void interrupt1(MIPS_Processor &proc);
    void interrupt2(MIPS_Processor &proc);
    void interrupt3(MIPS_Processor &proc);
    void interrupt4(MIPS_Processor &proc);
    void signal(bool b=false);

    // exceptions:
    void tlb_refill_exception();
    void cache_error_exception();
    void general_exception();
    void interrupt_causeiv_exception();
    void reset_exception();

    // Architecture dependent code executed after each instruction

    void hook() {};


    // for debug port
    unsigned int transport_dbg(int, tlm::tlm_generic_payload &payload) {
      return mmu.transport_dbg(payload);
    }
    // debugger interface creator called during end_of_elaboration()
    virtual DebugInterface* create_dbi();

    // complains about an unpredcitable isntruction, does not return
    void unpredictable(const char *msg);
  }; // class MIPS_Processsor<word_t>

  template<>
  inline MIPS_TranslationPage<BUS32>*&
  MIPS_Processor<BUS32>::select_page(TranslationTableItem *p_page) {
    return p_page->mips32;
  }

  template<>
  inline MIPS_TranslationPage<BUS64>*&
  MIPS_Processor<BUS64>::select_page(TranslationTableItem *p_page) {
    return p_page->mips64;
  }

  template<typename word_t>
  MIPS_Instruction<word_t> *MIPS_Processor<word_t>::fetch_instr_from_cache() {
    TranslationTableItem *p_page;
    uint32_t *host_address;
    const uint32_t page_id = TranslationPage::pageId(pc);
    mmu.fetch_page(page_id, // input
                   host_address, p_page); //output
    if (!p_page)
      return fetch_from_cache__nopage();
    if (!select_page(p_page))
      select_page(p_page) = fetch_from_cache__decode(page_id, host_address);
    current_page = select_page(p_page);
    assert(current_page);
    return select_page(p_page)->locateInstr(pc);
  }

} // namespace simsoc

#endif
