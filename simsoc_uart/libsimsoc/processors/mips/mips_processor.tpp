//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "mips_processor.hpp"
#include "mips_debugger.hpp"
#include "mipsis_dyntrans.hpp"
#include <libsimsoc/bitwise_operator.hpp>

namespace simsoc {

  template <typename word_t>
  MIPS_Processor<word_t>::MIPS_Processor(sc_core::sc_module_name name,
                                         int coreId):
    Processor(name,MIPS),
    current_instruction(NULL),
    current_page(NULL),
    pc(0),
    hi(0),
    lo(0),
    hilo_predictable(false),
    LLbit(false),
    iss("ISS",this,coreId,false),
    mmu("MMU",this),
    cp0("cp0",this,&mmu),
    hard_port0(false),
    hard_port1(false),
    hard_port2(false),
    hard_port3(false),
    hard_port4(false),
    mixed_port(false)
  {
    debug_port.register_transport_dbg(this,&ProcessorBase::transport_dbg);
    hard_port0(*this);
    hard_port1(*this);
    hard_port2(*this);
    hard_port3(*this);
    hard_port4(*this);
    mixed_port(*this);
    for (unsigned n=0; n<32; ++n)
      regs[n] = 0;
  }

  template <typename word_t>
  MIPS_Processor<word_t>::~MIPS_Processor() {
    delete current_instruction;
    debug() <<"sc_time_stamp() = " <<sc_core::sc_time_stamp() <<std::endl;
    debug() <<"Destructor called." <<std::endl;
  }

  template <typename word_t>
  uint64_t MIPS_Processor<word_t>::get_gp_register(size_t n) const {
    assert(n<32);
    return regs[n];
  }

  template <typename word_t>
  void MIPS_Processor<word_t>:: set_gp_register(size_t n, uint64_t data) {
    assert(n<32);
    regs[n] = static_cast<word_t>(data);
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::set_GP_register(word_t gp_value) {
    set_gp_register(GP,gp_value);
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::set_pc(uint64_t pc64) {
    pc = static_cast<word_t>(pc64);
    info() <<"PC initialized with value " <<std::hex <<pc <<std::endl;
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::set_sp(uint64_t sp64) {
    regs[SP] = static_cast<word_t>(sp64);
    info() <<"SP initialized with value " <<std::hex <<regs[SP] <<std::endl;
  }

  template <typename word_t>
  tlm::tlm_initiator_socket<> &MIPS_Processor<word_t>::get_rw_port() {
    return mmu.rw_socket;
  }

  template <typename word_t>
  SignalTargetPort<bool> &MIPS_Processor<word_t>::get_it_port() {
    return hard_port0;
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::interrupt1(MIPS_Processor<word_t> &proc) {
    cp0.status().ie = true;
    cp0.status().bev = false;
    cp0.status().exl = false;
    cp0.status().erl = false;
    cp0.cause().iv = false;
    proc.epc = proc.pc -4;
    signal();
    proc.pc = 0x80000180;
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::interrupt2(MIPS_Processor<word_t> &proc) {
    cp0.status().ie = true;
    cp0.status().bev = false;
    cp0.status().exl = false;
    cp0.status().erl = false;
    cp0.cause().iv = true;
    proc.epc = proc.pc -4;
    signal();
    proc.pc = 0x80000200;
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::interrupt3(MIPS_Processor<word_t> &proc) {
    cp0.status().ie = true;
    cp0.status().bev = true;
    cp0.status().exl = false;
    cp0.status().erl = false;
    cp0.cause().iv = false;
    proc.epc = proc.pc -4;
    signal();
    proc.pc = 0xBFC00380;
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::interrupt4(MIPS_Processor<word_t> &proc) {
    cp0.status().ie = true;
    cp0.status().bev = true;
    cp0.status().exl = false;
    cp0.status().erl = false;
    cp0.cause().iv = true;
    proc.epc = proc.pc -4;
    signal();
    proc.pc = 0xBFC00400;
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::signal(bool) {
    if (it_pending) {
      it_pending = hard_port0&&cp0.status().im[2] ||
        hard_port1&&cp0.status().im[3] ||
        hard_port2&&cp0.status().im[4] ||
        hard_port3&&cp0.status().im[5] ||
        hard_port4&&cp0.status().im[6] ||
        mixed_port&&cp0.status().im[7];
    } else {
      it_pending = hard_port0&&cp0.status().im[2] ||
        hard_port1&&cp0.status().im[3] ||
        hard_port2&&cp0.status().im[4] ||
        hard_port3&&cp0.status().im[5] ||
        hard_port4&&cp0.status().im[6] ||
        mixed_port&&cp0.status().im[7];
      if (it_pending)
        it_event.notify();
    }
    info() <<"hardware0: " <<hard_port0 <<std::endl;
    info() <<"hardware1: " <<hard_port1 <<std::endl;
    info() <<"hardware2: " <<hard_port2 <<std::endl;
    info() <<"hardware3: " <<hard_port3 <<std::endl;
    info() <<"hardware4: " <<hard_port4 <<std::endl;
    info() <<"mixed: " <<mixed_port <<std::endl;

  }

  template <typename word_t>
  void MIPS_Processor<word_t>::tlb_refill_exception() {
    info()<<"raising tlb refill exception"<<std::endl;
    word_t vector_offset=0;
    if(cp0.status().exl==0)
      {
        //todo: instruction in Branch Delay Slot
        cp0.set_epc(pc);
        cp0.cause().bd = 0;
        vector_offset = 0x0;
      }else
      vector_offset=0x180;
    cp0.status().exl = true;
    signal();
    if(cp0.status().bev)
      pc=0xBFC00200 + vector_offset;
    else
      pc=0x80000000 + vector_offset;
    throw(ISS_Exception("tlb refill exception"));
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::cache_error_exception() {
    info()<<"raising cache error exception"<<std::endl;
    cp0.status().erl = true;
    signal();
    if(cp0.status().bev)
      pc=0xBFC00300;
    else
      pc=0xA0000100;
    throw(ISS_Exception("cache error exception"));
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::general_exception() {
    info()<<"raising general exception"<<std::endl;
    signal();
    if(cp0.status().bev)
      pc=0xBFC00380;
    else
      pc=0x80000180;
    throw(ISS_Exception("general exception"));
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::interrupt_causeiv_exception() {
    info() <<"raising interrupt exception" <<std::endl;
    word_t vector_offset=0;
    //todo: instruction in Branch Delay Slot
    cp0.set_epc(pc);
    cp0.cause().bd = 0;

    if(cp0.cause().iv)
      {
        vector_offset = 0x200;
      }else
      vector_offset=0x180;

    cp0.status().exl = true;
    signal();
    if(cp0.status().bev)
      pc=0xBFC00200 + vector_offset;
    else
      pc=0x80000000 + vector_offset;
    throw(ISS_Exception("interrupt causeiv exception"));
  }

  template <typename word_t>
  void MIPS_Processor<word_t>::reset_exception() {
    info()<<"raising reset exception"<<std::endl;
    cp0.status().erl = true;
    signal();
    pc=0xBFC00000;
    throw(ISS_Exception("reset exception"));
  }

  /************************************************************************************/

  template <typename word_t>
  void MIPS_Processor<word_t>::read_hilo() {
    if (hilo_predictable)
      return;
    error() <<"read unpredictable values from HI or LO" <<std::endl;
    exit(1);
  }


  template <typename word_t>
  void MIPS_Processor<word_t>::set_hilo() {
    hilo_predictable = true;
  }


  template <typename word_t>
  void MIPS_Processor<word_t>::unset_hilo() {
    hilo_predictable = false;
  }
  /*===================================================================================*/

  //D0 RUN FROM HERE
  template <typename word_t>
  MIPS_Instruction<word_t> * MIPS_Processor<word_t>::fetch_instruction()
  {
    return mipsDecode<word_t>(mmu.read_word(pc));
  }

  //D1 USE CACHE
  template <typename word_t>
  MIPS_Instruction<word_t>* MIPS_Processor<word_t>::fetch_from_cache__nopage() {
    info() <<"fetch page failed; dynamic translation not used for current instruction"
           <<std::endl;
    delete current_instruction;
    current_instruction = NULL; // next instruction may fail
    current_instruction = fetch_instruction();
    return current_instruction;
  }

  template <typename word_t>
  MIPS_TranslationPage<word_t> *MIPS_Processor<word_t>::
  fetch_from_cache__decode(const uint32_t page_id,
                           uint32_t *const host_address) {
    info() <<"decode virtual code page " <<page_id <<" (mips)" <<std::endl;
    MIPS_TranslationPage<word_t> * page =
      new MIPS_TranslationPage<word_t>(host_address);
    if (mode>=DYN_TRANS_SPEC) {
      page->fill(MIPS_TranslateBlock<word_t>::get());
    } else {
      page->decode();
    }
    //change access permission of translated code page
    if (mprotect(host_address, MIPS_TranslationPage<word_t>::TR_PAGE_SIZE, PROT_READ)) {
      error() <<"change access permission of translated code page failed! errmsg = \""
              <<strerror(errno) <<"\"\n";
      exit(1);
    }
    return page;
  }

  // used by MIPS_TranslateBloc<...>k::exec(MIPS_Processor<...>&)
  template <typename word_t>
  MIPS_Instruction<word_t> **MIPS_Processor<word_t>::get_current_instr_ptr() {
    TranslationTableItem *p_page;
    uint32_t *host_address;
    const uint32_t page_id = TranslationPage::pageId(pc);
    mmu.fetch_page(page_id, // input
                   host_address, p_page); //output
    assert(p_page);
    assert(select_page(p_page));
    return select_page(p_page)->locateInstrPtr(pc);
  }


  template <typename word_t>
  void MIPS_Processor<word_t>::raise_interrupt() {}

  template <typename word_t>
  void MIPS_Processor<word_t>::unpredictable(const char *msg) {
    error() <<"unpredictable instruction: " <<msg <<".\n";
    exit(1);
  }

  // ------------------------------------------------------------------
  // Debugger interface
  // ------------------------------------------------------------------
  
  template <typename word_t>
  DebugInterface* MIPS_Processor<word_t>::create_dbi() {
    return new MIPS_Debugger<word_t>(*this);
}

} // namespace simsoc
