//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "ppc_processor.hpp"
#include "ppc_statistics_simple.hpp"
#include "ppc_statistics_verysimple.hpp"
#include "ppc_statistics_arithmetic.hpp"
#include "ppc_debugger.hpp"
#include <libsimsoc/bitwise_operator.hpp>
#include <sys/mman.h>
#include <errno.h>
#include "ppcis_dyntrans.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

  static ParameterBool use_verysimple_stat("PPC processor", "-verysimple",
                                           "Compute very simple statistics");
  static ParameterBool use_arithmetic_stat("PPC processor", "-arithmetic",
                                           "Compute arithmetic statistics");
  static ParameterBool param_user_mode("PPC processor", "-u",
                                       "user-level simulation");

  void PPC_Processor::debug_hook() {
    static uint64_t count = 0;
    const uint64_t START = main_context().start;
    const uint64_t PERIOD = main_context().period;
    const uint64_t END = START + PERIOD*main_context().number;
    if (START<=count) {
      if (count>=END) {
        if (main_context().number!=0)
          exit(0);
      } else {
        if ((count-START)%PERIOD==0) {
          std::cout <<"STEP #" <<dec <<count <<'\n';
          std::cout <<cpu;
        }
      }
    }
    ++count;
  }

  PPC_Processor::PPC_Processor(sc_core::sc_module_name name,
                               int coreId, bool holdoff):
    Processor(name, POWERPC),
    cpu(coreId),
    iss("ISS",this,coreId,holdoff),
    mmu("MMU",this),
    fp_unit("FloatPoint_Unit",this),
    irq_port(false),
    nb_instr(0),
    current_instruction(NULL),
    current_page(NULL),
    dec_exception(false),
    ext_exception(false),
    trap_exception(false),
    statistics_visitor(NULL)
  {
    if (use_verysimple_stat.get() && use_arithmetic_stat.get()) {
      error() <<"options -verysimple and -arithmetic are not compatible.\n";
      exit(1);
    }
    if (use_verysimple_stat.get())
      statistics_visitor = new PPC_StatisticsVerySimple();
    else if (use_arithmetic_stat.get())
      statistics_visitor = new PPC_StatisticsArithmetic();
    else
      statistics_visitor = new PPC_StatisticsSimple();
    debug_port.register_transport_dbg(this,&Processor::transport_dbg);
    irq_port(*this);

    if (param_user_mode.get()) {
      linux_os = new PPC_LinuxOS("LinuxOS",this);
    } else
      linux_os = NULL;
  }

  PPC_Processor::~PPC_Processor() {
    if (do_statistics())
      statistics_visitor->write(stat_file);
    delete statistics_visitor;
    delete current_instruction;
    if (nb_instr)
      info() <<nb_instr <<" instructions executed" <<endl;
    debug() <<"sc_time_stamp() = " <<sc_time_stamp() <<endl;
    debug() <<"Destructor called." <<endl;
  }

  /*------------------------------------------------------------------------*/

  // used by Compute_noDT
  PPC_Instruction * PPC_Processor::fetch_instruction() {
    return ppcDecode(mmu.load_instr_32(cpu.pc));
  }

  /*-------------------------------------------------------------------------*/

  PPC_Instruction *PPC_Processor::fetch_from_cache__nopage() {
    info() <<"fetch page failed; "
           <<"dynamic translation not used for current instruction (pc="
           <<cpu.pc <<").\n";
    delete current_instruction;
    current_instruction = NULL; // next instruction may fail
    current_instruction = fetch_instruction();
    return current_instruction;
  }

  PPC_TranslationPage
  *PPC_Processor::fetch_from_cache__decode(const uint32_t page_id,
                                            uint32_t *const host_address) {
    info() <<"decode and translate virtual code page " <<page_id <<endl;
    PPC_TranslationPage * page = new PPC_TranslationPage(host_address);
    if (mode>=DYN_TRANS_SPEC) {
      page->fill(PPC_EmptyCell::get());
    } else {
      page->decode();
    }
    //change access permission of translated code page
    if (mprotect(host_address, TranslationPage::TR_PAGE_SIZE,PROT_READ)) {
      error()<<"change access permission of translated code page failed! errmsg=["
             <<strerror(errno)<<"]"<<endl;
      exit(1);
    }
    return page;
  }

  // used by PPC_EmptyCell::exec(PPC_Processor&)
  PPC_Instruction **PPC_Processor::get_current_instr_ptr() {
    TranslationTableItem *p_page;
    uint32_t *host_address;
    const uint32_t page_id = TranslationPage::pageId(cpu.pc);
    mmu.fetch_page(page_id, // input
                   host_address, p_page); //output
    assert(p_page);
    assert(p_page->ppc);
    return p_page->ppc->locateInstrPtr(cpu.pc);
  }

  /*-------------------------------------------------------------------------*/

  void PPC_Processor::set_pc(uint64_t pc) {
    info() <<"PC initialized with value " <<hex <<(uint32_t) pc<<endl;
    cpu.pc = pc;
  }

  void PPC_Processor::set_sp(uint64_t sp) {
    info() <<"SP initialized with value " <<hex << (uint32_t) sp<<endl;
    cpu.gpr[1] = sp;
  }

  uint64_t PPC_Processor::get_gp_register(size_t n) const {
    assert(n<32);
    return cpu.gpr[n];
  }

  void PPC_Processor:: set_gp_register(size_t n, uint64_t data) {
    assert(!(data>>32));
    assert(n<32);
    cpu.gpr[n] = static_cast<uint32_t>(data);
  }

  /*--------------------------------Interrupt-------------------------------*/
  void PPC_Processor::raise_interrupt() {
    if(fp_unit.fpscr.get_fex()
       && fp_unit.get_fp_excp_mode() == PRECISE){
      interrupt(INT_PROGRAM,PPC_EXC_PROGRAM_FLOAT);
      return;
    }

    if(trap_exception) {
      trap_exception = false;
      if(ext_exception || dec_exception)
        something_pending = true;
      else
        it_ack();
      interrupt(INT_SC, PPC_EXC_PROGRAM_TRAP);
      return;
    }

    if(fp_unit.fpscr.get_fex() &&
             ( fp_unit.get_fp_excp_mode() == IMPRE_NONREC
               || fp_unit.get_fp_excp_mode() == IMPRE_RECOV)
             ){
      interrupt(INT_PROGRAM,PPC_EXC_PROGRAM_FLOAT);
      return;
    }

    if(cpu.msr & MSR_EE) {
      if (ext_exception) {
        ext_exception = false;
        if(dec_exception) {
          something_pending = true;//still have int to handle...
        } else
          it_ack();
        interrupt(INT_EXT);
        return;
      }

      if(dec_exception) {
        dec_exception = false;
        it_ack();
        interrupt(INT_DEC);
        return;
      }

    } else {
      if(ext_exception || dec_exception)
        something_pending = true;
    }

  }

  void PPC_Processor::signal(bool) {
    ext_exception = irq_port;
    it_pending = ext_exception || (fp_unit.fpscr.get_fex() && fp_unit.get_fp_excp_mode()!= DISABLED);
    something_pending = something_pending || it_pending;
    debug()<<"PPC_Processor::signal::core: "<<hex<<cpu.pir<<"...IRQ: " <<irq_port.get() <<endl;
  }

  uint32_t PPC_Processor::predefined_phy_base(){
    return check_MSR_IP(cpu.msr)?0xfff00000:0x00000000;
  }

  void PPC_Processor::interrupt(uint32_t type, uint32_t flags, uint32_t addr) {
    switch (type) {
    case INT_SYS_RESET:
      info()<<"INT_SYS_RESET interrupt at "<<hex<<cpu.pc<<endl;

      cpu.srr[0] = cpu.pc;
      cpu.srr[1] = cpu.msr & MSR_MASK;
      cpu.msr = 1/*<< MSR_HV*/;

      cpu.msr = 0;
      cpu.pc = predefined_phy_base()+type;
      //throw(ISS_Exception(""));
      break;
    case INT_MACHINE_CHECK:
      info()<<"INT_MACHINE_CHECK interrupt at "<<hex<<cpu.pc<<endl;

      if (!(cpu.msr & MSR_ME))
        error()<<"machine check exception and MSR[ME]=0.\n";
      cpu.srr[0] = cpu.pc;
      cpu.srr[1] = cpu.msr & MSR_MASK;
      cpu.msr = 1/*<< MSR_HV*/;

      cpu.msr = 0;
      cpu.pc = predefined_phy_base()+type;
      //throw(ISS_Exception(""));
      break;
    case INT_DSI:
      info()<<"INT_DSI interrupt at "<<hex<<cpu.pc<<endl;

      cpu.srr[0] = cpu.pc;
      cpu.srr[1] = cpu.msr & MSR_MASK;
      cpu.dar = addr;
      cpu.dsisr = flags;

      cpu.msr = 0;
      cpu.pc = predefined_phy_base()+type;
      throw(ISS_Exception("INT_DSI interrupt"));
      break;
    case INT_ISI:
      info()<<"INT_ISI interrupt at "<<hex<<cpu.pc<<endl;

      cpu.srr[0] = cpu.pc;
      cpu.srr[1] = (cpu.msr & MSR_MASK) | flags;
      //cpu.dar = addr;
      //cpu.dsisr = flags;

      cpu.msr = 0;
      cpu.pc = predefined_phy_base()+type;
      throw(ISS_Exception("INT_ISI interrupt"));
      break;
    case INT_EXT:
      info()<<"INT_EXT interrupt at "<<hex<<cpu.pc<<endl;

      cpu.srr[0] = cpu.pc;
      cpu.srr[1] = cpu.msr & MSR_MASK;

      cpu.msr = 0;
      cpu.pc = predefined_phy_base()+type;
      //throw(ISS_Exception(""));
      break;
    case INT_ALIGNMENT:
      info()<<"INT_ALIGNMENT interrupt at "<<hex<<cpu.pc<<endl;

      cpu.srr[0] = cpu.pc;
      cpu.srr[1] = cpu.msr & MSR_MASK;

      cpu.msr = 0;
      cpu.pc = predefined_phy_base()+type;
      //throw(ISS_Exception(""));
      break;
    case INT_PROGRAM:
      {
        info()<<"INT_PROGRAM interrupt at "<<hex<<cpu.pc<<endl;

        if (flags & INT_PROGRAM_NEXT)
          cpu.srr[0] = cpu.npc;
        else
          cpu.srr[0] = cpu.pc;

        uint32_t clear_bits = 0x783f0000;//1-4 10-15 cleared
        uint32_t copy_bits = 0x0000ff73; //16-23 25-27 30-31 copyed
        uint32_t msr_copy = cpu.msr & copy_bits;
        cpu.srr[1] &= ~copy_bits;
        cpu.srr[1] |= msr_copy;
        cpu.srr[1] &= ~clear_bits;
        cpu.srr[1] |= flags;

        uint32_t new_msr_clear_bits = 0x0004ef33;
        cpu.msr &= ~new_msr_clear_bits;
        cpu.msr |= (uint32_t)check_MSR_ILE(cpu.msr);

        cpu.pc = predefined_phy_base()+type;
        throw(ISS_Exception("INT_PROGRAM interrupt"));
      }
      break;
    case INT_NO_FPU:
      {
      info()<<"INT_NO_FPU interrupt at "<<hex<<cpu.pc<<endl;

      cpu.srr[0] = cpu.pc;
      uint32_t clear_bits = 0x783f0000;//1-4 10-15 cleared
      uint32_t copy_bits = 0x0000ff73; //16-23 25-27 30-31 copyed
      uint32_t msr_copy = cpu.msr & copy_bits;
      cpu.srr[1] &= ~copy_bits;
      cpu.srr[1] |= msr_copy;
      cpu.srr[1] &= ~clear_bits;

      uint32_t new_msr_clear_bits = 0x0004ef33;
      cpu.msr &= ~new_msr_clear_bits;
      cpu.msr |= (uint32_t)check_MSR_ILE(cpu.msr);
      cpu.pc = predefined_phy_base()+type;
      throw(ISS_Exception("INT_NO_FPU interrupt"));
      }
      break;
    case INT_DEC:
      info()<<"INT_DEC interrupt at "<<hex<<cpu.pc<<endl;

      cpu.srr[0] = cpu.pc;
      cpu.srr[1] = cpu.msr & MSR_MASK;

      cpu.msr = 0;
      cpu.pc = predefined_phy_base()+type;
      //throw(ISS_Exception(""));
      break;
    case INT_SC:
      info()<<"INT_SC interrupt at "<<hex<<cpu.pc<<endl;

      cpu.srr[0] = cpu.pc;
      cpu.srr[1] = cpu.msr & MSR_MASK;

      cpu.msr = 0;
      cpu.pc = predefined_phy_base()+type;
      //throw(ISS_Exception(""));
      break;
    case INT_TRACE:
      info()<<"INT_TRACE interrupt at "<<hex<<cpu.pc<<endl;

      cpu.srr[0] = cpu.pc;
      cpu.srr[1] = cpu.msr & MSR_MASK;

      cpu.msr = 0;
      cpu.pc = predefined_phy_base()+type;
      //throw(ISS_Exception(""));
      break;
    case INT_FLOAT_ASSIST:
      info()<<"INT_FLOAT_ASSIST interrupt at "<<hex<<cpu.pc<<endl;

      cpu.srr[0] = cpu.pc;
      cpu.srr[1] = cpu.msr & MSR_MASK;

      cpu.msr = 0;
      cpu.pc = predefined_phy_base()+type;
      //throw(ISS_Exception(""));
      break;
    default:
      error() <<"unknown\n";
    }

    return;
  }

  void PPC_Processor::hook__pdec_zero() {
    set_something_pending();
    set_it_pending();
    dec_exception = true;
    cpu.pdec = 0xffffffff * PPC_CPU::TBF_RATIO;
  }

  // ------------------------------------------------------------------
  // Debugger interface
  // ------------------------------------------------------------------
  DebugInterface* PPC_Processor::create_dbi() {
    return new PPC_Debugger(*this);
  }


} // namespace simsoc
