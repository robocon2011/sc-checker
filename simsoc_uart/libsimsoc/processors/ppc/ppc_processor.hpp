//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_PROCESSOR_HPP
#define PPC_PROCESSOR_HPP

#include "ppc_cpu.hpp"
#include "ppc_decode.hpp"
#include "ppc_mmu.hpp"
#include "ppc_translation_page.hpp"
#include "ppc_fp_unit.hpp"
#include "ppc_statistics.hpp"
#include <libsimsoc/processors/processor.hpp>
#include <libsimsoc/processors/iss.hpp>
#include <libsimsoc/tools/debugger/debugger.hpp>
#include <libsimsoc/module.hpp>
#include "ppc_syscall.hpp"
#include "ppc_linux_os.hpp"

namespace simsoc {

  //----------------------------------PPC_Processor---------------------------------
  class PPC_Processor: public Processor,
                       public SignalTarget<bool> {
  public:
    typedef PPC_Instruction Instruction;

    //*** hardware parts:
    PPC_CPU cpu;
    ISS<PPC_Processor> iss;
    PPC_MMU mmu;
    PPC_FloatPoint_Unit fp_unit;
    PPC_LinuxOS* linux_os;

    SignalTargetPort<bool> irq_port; //bind with irqc

    //*** other data:
    uint64_t nb_instr;// how many ins have been executed, for statistics
    uint8_t dt_mode;
    PPC_Instruction *current_instruction;
    PPC_TranslationPage *current_page;

    bool dec_exception;
    bool ext_exception;
    bool trap_exception;

    // statistic
    PPC_Statistics  *statistics_visitor;

    SC_HAS_PROCESS(PPC_Processor);
    PPC_Processor(sc_core::sc_module_name name,
                  int processor_id = 0, bool holdoff = false);
    ~PPC_Processor();

    // methods for initialization
    void set_pc(uint64_t pc);
    uint64_t get_pc() const {return cpu.pc;}
    void set_sp(uint64_t sp);
    uint32_t get_sp(){return cpu.gpr[1];};
    uint64_t get_gp_register(size_t n) const;
    void set_gp_register(size_t n, uint64_t data);
    void set_endian_big() {}

    tlm::tlm_initiator_socket<> &get_rw_port() {return mmu.rw_socket;}
    SignalTargetPort<bool> &get_it_port() {return irq_port;}
    const PPC_TranslationPage *get_current_page() const {return current_page;}

    SimulationMode max_mode_available() const {return DYN_COMP;}

    // methods used by Core Template
    // to be extended in the future
    int bus_width() {return 32;}
    inline PPC_PseudoInstruction* get_branch_on_same_page() {
      error() << "PPC branch same page not yet implemented\n";
      return NULL;
    }

    inline PseudoStatus exec_pseudo(const PPC_PseudoInstruction &pi) {
      const PseudoStatus status = pi.f(*this, pi) ;
      if (status==OK)
        cpu.pc += 4;
      return status;
    }

    // fetching:
    PPC_Instruction* fetch_instruction();
    inline  PPC_Instruction* fetch_instr_from_cache();
    PPC_Instruction *fetch_from_cache__nopage();
    PPC_TranslationPage *fetch_from_cache__decode(const uint32_t page_id,
                                                   uint32_t *const host_address);
    PPC_Instruction **get_current_instr_ptr();

    // interrupts:
    void signal(bool b = false);
    void interrupt(uint32_t type, uint32_t flags = 0, uint32_t addr = 0);
    uint32_t predefined_phy_base();

    // for debug port
    unsigned int transport_dbg(int, tlm::tlm_generic_payload &payload) {
      return mmu.transport_dbg(payload);
    }

    // statistics computation:
    void update_statistics(PPC_Instruction *instr) {
      instr->accept(*statistics_visitor);
    }

    void write_statistics(std::ostream& os = std::cout) {}
    void read_statistics(std::istream& is) {}

    void raise_interrupt();

    inline void hook();
    void debug_hook();

    void hook__pdec_zero(); // part of the hook function that is not inlined

    // GDB interface
    virtual DebugInterface* create_dbi();
  }; // class PPC_Processor

  void PPC_Processor::hook() {
// #if 0 // code disabled for performance checking
    cpu.ptbr += 11; //update Time Base Facility
    if (cpu.pdec == 0)
      hook__pdec_zero();
    else
      cpu.pdec--;
// #endif
    // debug_hook(); // DO NOT COMMIT
  }

  PPC_Instruction * PPC_Processor::fetch_instr_from_cache() {
    TranslationTableItem *p_page;
    uint32_t *host_address;
    const uint32_t page_id =
      PPC_TranslationPage::pageId(cpu.pc);
    mmu.fetch_page(page_id, // input
                   host_address, p_page); //output
    if (!p_page)
      return fetch_from_cache__nopage();
    if (!(p_page->ppc))
      p_page->ppc = fetch_from_cache__decode(page_id, host_address);
    current_page = p_page->ppc;
    assert(current_page);
    return p_page->ppc->locateInstr(cpu.pc);
  }

} // namespace simsoc

#endif //PPC_PROCESSOR_HPP
