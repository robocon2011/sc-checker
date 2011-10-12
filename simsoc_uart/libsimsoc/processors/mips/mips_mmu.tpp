//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Implementation of "mips_mmu.hpp"
// This file is included only by "mips_mmu.cpp"
#include "mips_mmu.hpp"
#include "mips_coprocessor.hpp"
#include "mips_processor.hpp"

namespace simsoc {

template <typename word_t>
MIPS_MMU<word_t>::MIPS_MMU(sc_core::sc_module_name name, MIPS_Processor<word_t> *proc):
  MMU<word_t>(name,proc)
{
  getTLBs();
  mips_proc = static_cast<MIPS_Processor<word_t>*>(proc);
  cp0 = &(mips_proc->cp0);
}

template<>
bool MIPS_MMU<BUS32>::data_preprocess_and_is_enabled(BUS32 &addr) const {
  const uint8_t flags = addr>>29;
  switch (flags) {
  case KSEG0_FLAG:
  case KSEG1_FLAG:
    debug() << "located : Kernel unmapped\n";
    if (mmu_mode()!=kernel)
      return true; // the following call to virt_to_phy will generate a fault
    addr &=~ ADDR32_MASK;
    return false;
  case SSEG_FLAG:
    debug() << "located : Supervisor mapped\n";
    return true;
  case KSEG3_FLAG:
    debug() << "located : kernel mapped\n";
    return true;
  default: // USEG
    debug() << "located : user mapped\n";
    return true;
  }
}

template <>
bool MIPS_MMU<BUS64>::data_preprocess_and_is_enabled(BUS64 &addr) const {
  const BUS64 mask = addr & ADDR64_MASK;
  switch (mask) {
  case USER_MASK64:
    debug() << "located 64 bits compat 32: unmapped \n";
    if (!cp0->user_add64_enable())
      return true; // virt_to_phy will generate a fault
    // addr &= ~ADDR64_MASK; // done in check_perm_and_unmapped
    return true;
  case SUPERVISOR_MASK64 :
    if (!cp0->supervisor_add64_enable())
      return true; // virt_to_phy will generate a fault
    // addr &= ~ADDR64_MASK; // done in check_perm_and_unmapped
    return true;
  case XKPHYS_MASK64:
    addr &= ~ADDR64_PHYS_MASK;
    return false;
  case KERNEL_MASK64 : // need to ensure 32bits compatibility
    if (addr < COMPATIBILITY) {
      error() << "64 bit address segment err\n"; // likely a bug
      exit(-1);
      // return xkseg;
    } else {
      switch (static_cast<uint32_t>(addr)>>29) {
      case KSEG0_FLAG:
      case KSEG1_FLAG:
        debug() << "located : Kernel unmapped\n";
        if (mmu_mode()!=kernel)
          return true; // virt_to_phy will generate a fault
        addr &=~ ADDR32_MASK;
        return false;
      case SSEG_FLAG:
        debug() << "located : Supervisor mapped\n";
        return true;
      case KSEG3_FLAG:
        debug() << "located : kernel mapped\n";
        return true;
      default: // USEG
        debug() << "located : user mapped\n";
        return true;
      }
    }
  default:
    error() << "64 bit address segment err\n";
    exit(1);
  }
}

template<>
void MIPS_MMU<BUS32>::check_perm(BUS32 &addr) const {
  const uint8_t flags = addr>>29;
  switch (flags) {
  case KSEG0_FLAG:
  case KSEG1_FLAG:
    assert(mmu_mode()!=kernel &&
           "this function should be called only if preprocess.. returned true");
    throw MMU_Faults<BUS32>(addr,MMU_BADADDR);
  case SSEG_FLAG:
    if (mmu_mode()==user)
      throw MMU_Faults<BUS32>(addr,MMU_BADADDR);
  case KSEG3_FLAG:
    if (mmu_mode()!=kernel)
      throw MMU_Faults<BUS32>(addr,MMU_BADADDR);
  default:; // USEG
  }
}

template <>
void MIPS_MMU<BUS64>::check_perm(BUS64 &addr) const {
  const BUS64 mask = addr & ADDR64_MASK;
  switch (mask) {
  case USER_MASK64:
    if (!cp0->user_add64_enable())
      throw MMU_Faults<BUS64>(addr,MMU_BADADDR);
    addr &= ~ADDR64_MASK;
  case SUPERVISOR_MASK64 :
    if (!cp0->supervisor_add64_enable())
      throw MMU_Faults<BUS64>(addr,MMU_BADADDR);
    addr &= ~ADDR64_MASK;
  case XKPHYS_MASK64:
    assert(false &&
           "this function should be called only if preprocess.. returned true");
    abort();
  case KERNEL_MASK64 : // need to ensure 32bits compatibility
    if (addr < COMPATIBILITY) {
      error() << "64 bit address segment err\n"; // likely a bug
      exit(-1);
      // return xkseg;
    } else {
      switch (static_cast<uint32_t>(addr)>>29) {
      case KSEG0_FLAG:
      case KSEG1_FLAG:
        assert(mmu_mode()!=kernel &&
               "this function should be called only if preprocess.. returned true");
        throw MMU_Faults<BUS64>(addr,MMU_BADADDR);
      case SSEG_FLAG:
        if (mmu_mode()==user)
          throw MMU_Faults<BUS64>(addr,MMU_BADADDR);
      case KSEG3_FLAG:
        if (mmu_mode()!=kernel)
          throw MMU_Faults<BUS64>(addr,MMU_BADADDR);
      default:; // USEG
      }
    }
  }
}

void sigsegv_handler(int signo, struct siginfo *siginfo, void *ucontext);

template <typename word_t>
word_t MIPS_MMU<word_t>::virt_to_phy(word_t va,mmu_data_type data_type,
                                     mem_op_type op_type, TLB<word_t> *tlbs) {
  assert(tlbs);
  check_perm(va);
  check_alignment(va,data_type);
  uint32_t pa = 0;
  TLBEntry<word_t> **entry_ptr = tlbs->search_entry(va);
  MIPS_TLBEntry<word_t> *entry =
    static_cast<MIPS_TLBEntry<word_t>*>(entry_ptr ? *entry_ptr : NULL);
  if (entry) {
    pa = entry->getPA(va);
    //debug()<<"Find in TLb! get physical addr["<<pa<<"]"<<endl;
  } else {
    //debug()<<"TLB miss! translation table walk!"<<endl;
    throw MMU_Faults<word_t>(va,TLB_NOMATCH,0,op_type);
  }
  check_access(va,entry,op_type);
  return pa;
}

template <typename word_t>
bool MIPS_MMU<word_t>::getTLBs() {
  MIPS_TLB<word_t>* main_tlb=new MIPS_TLB<word_t>("main tlb",64);
  this->dTLBs= this->iTLBs=main_tlb;
  return true;
}

template <typename word_t>
void MIPS_MMU<word_t>::check_alignment(word_t va, mmu_data_type data_type)
{
  if( ( (data_type==MMU_WORD_TYPE) && (va&3) )
    ||( (data_type==MMU_HALF_TYPE) && (va&1) ) )
    {
      throw MMU_Faults<word_t>(va,MMU_BADADDR);
    }
  return;
}

template <typename word_t>
void MIPS_MMU<word_t>::check_access(word_t va,
                                    MIPS_TLBEntry<word_t> *mips_tlb_entry,
                                    mem_op_type op_type) {
  if (!mips_tlb_entry->getV(va))
    throw MMU_Faults<word_t>(va, TLB_INVALID_ENTRY, 0, op_type); //tlb_invalid
  if (op_type == MMU_WRITE && !mips_tlb_entry->getBuffered(va))
    throw MMU_Faults<word_t>(va, TLB_DIRTY_ENTRY); //tlb_modified
}

template <typename word_t>
void MIPS_MMU<word_t>::do_tlbp() {
  //search entry and put index to index register
  assert(this->dTLBs);
  word_t va = cp0->get_entryhi_vpn();
  TLBEntry<word_t> **pEntry = this->dTLBs->search_entry(va);
  MIPS_TLBEntry<word_t> *entry =
    static_cast<MIPS_TLBEntry<word_t>*>(pEntry? *pEntry: NULL);
  if (entry) {
    cp0->set_tlb_index(true,this->dTLBs->search_pos);
  } else {
    cp0->set_tlb_index(false);
  }
}

template <typename word_t>
void MIPS_MMU<word_t>::do_tlbr() {
  //read tlb entry according to the index register
  assert(this->dTLBs);
  const uint32_t index = cp0->get_tlb_index();
  assert(index<=this->dTLBs->size);
  TLBEntry<word_t> **pEntry =
    static_cast<MIPS_TLB<word_t>*>(this->dTLBs)->get_entry(index);
  assert(pEntry);
  set_tlbEntry(static_cast<MIPS_TLBEntry<word_t>*>(*pEntry));
}

template <typename word_t>
void MIPS_MMU<word_t>::do_tlbwi() {
  //write tlb entry according to the index register
  assert(this->dTLBs);
  MIPS_TLBEntry<word_t>* entry=new MIPS_TLBEntry<word_t>();
  get_tlbEntry(entry);
  const uint32_t index = cp0->get_tlb_index();
  static_cast<MIPS_TLB<word_t>*>(this->dTLBs)->add_entry(entry,index);
}

template <typename word_t>
void MIPS_MMU<word_t>::do_tlbwr() {
  //write tlb entry according to the random register
  assert(this->dTLBs);
  MIPS_TLBEntry<word_t>* entry=new MIPS_TLBEntry<word_t>();
  get_tlbEntry(entry);
  uint32_t index=cp0->get_random();
  static_cast<MIPS_TLB<word_t>*>(this->dTLBs)->add_entry(entry,index);
}

template <typename word_t>
void MIPS_MMU<word_t>::set_tlbEntry(MIPS_TLBEntry<word_t>* entry){
  assert(entry);
  cp0->set_entryhi(entry->virt_addr,entry->ASID);
  cp0->set_pagemask(entry->mask);
  cp0->set_entrylo0(entry->PFN[0],entry->C[0],entry->D[0],entry->V[0],entry->isGlobal);
  cp0->set_entrylo1(entry->PFN[1],entry->C[1],entry->D[1],entry->V[1],entry->isGlobal);

}

template <typename word_t>
void MIPS_MMU<word_t>::get_tlbEntry(MIPS_TLBEntry<word_t>* entry){
  assert(entry);
  bool g0,g1=0;
  cp0->get_pagemask(entry->mask);
  cp0->get_entryhi(entry->virt_addr,entry->ASID);
  cp0->get_entrylo0(entry->PFN[0],entry->C[0],entry->D[0],entry->V[0],g0);
  cp0->get_entrylo1(entry->PFN[1],entry->C[1],entry->D[1],entry->V[1],g1);
  entry->isGlobal = g0 & g1;
}

template <typename word_t>
void MIPS_MMU<word_t>::handle_data_faults(word_t virt_addr,
				     word_t fault,
				     word_t domain,
				     mem_op_type op_type) {
  switch((mips_mmu_fault_t)fault) {
  case MMU_BADADDR:
    cp0->set_bad_addr(virt_addr);
    cp0->cause().exc_code = (op_type==MMU_WRITE)? Exc_AdES:Exc_AdEL;
    mips_proc->general_exception();
    break;
  case TLB_NOMATCH:
    cp0->set_bad_addr(virt_addr);
    cp0->set_contex_badvpn(virt_addr);
    cp0->set_entryhi_vpn(virt_addr);
    cp0->cause().exc_code = (op_type==MMU_WRITE)? Exc_TLBS:Exc_TLBL;
    mips_proc->tlb_refill_exception();
   break;
  case TLB_INVALID_ENTRY:
    cp0->set_bad_addr(virt_addr);
    cp0->set_contex_badvpn(virt_addr);
    cp0->set_entryhi_vpn(virt_addr);
    cp0->cause().exc_code = (op_type==MMU_WRITE)? Exc_TLBS:Exc_TLBL;
    mips_proc->general_exception();
    break;
  case TLB_DIRTY_ENTRY:
    cp0->set_bad_addr(virt_addr);
    cp0->set_contex_badvpn(virt_addr);
    cp0->set_entryhi_vpn(virt_addr);
    cp0->cause().exc_code=Exc_Mod;
    mips_proc->general_exception();
    break;
  default:
    error() <<"wrong exception type " <<fault <<" " <<std::endl;
	exit(1);
  }
}

} // namespace simsoc
