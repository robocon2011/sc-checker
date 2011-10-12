//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "ppc_mmu.hpp"
#include "ppc_processor.hpp"
#include <libsimsoc/display.hpp>
#include <sys/mman.h>
#include <cerrno>

using namespace sc_core;
using namespace std;

namespace simsoc {

#ifdef CACHE
  inline void update_list(block_t* head, block_t* node) {
    if(head == node)
      return;
    if(head->prev != node) {
      node->prev->next = node->next;//remove node
      node->next->prev = node->prev;

      node->next = head;//add node
      node->prev = head->prev;
      head->prev->next = node;
      head->prev = node;
    }

    head = node;
  }
#endif

  //------------------------------------------------------------------------
  void sigsegv_handler(int signo, struct siginfo *siginfo, void *ucontext);

  PPC_MMU::PPC_MMU(sc_core::sc_module_name name, PPC_Processor *proc_):
    MMU<BUS32>(name,proc_),
    cpu(static_cast<PPC_Processor*>(proc)->cpu)
  {
    iTLBs = NULL;
    dTLBs = NULL;

#ifdef CACHE
    int i, j;
    for(i = 0; i < CACHE_SETS_L1; i++) {
      for(j = 0; j < BLOCKS_PER_SET_L1; j++) {
        if(j == 0) {
          icache[i][j].prev = &icache[i][BLOCKS_PER_SET_L1-1];
          icache[i][j].next = &icache[i][j+1];
          dcache[i][j].prev = &dcache[i][BLOCKS_PER_SET_L1-1];
          dcache[i][j].next = &dcache[i][j+1];
        } else if(j == BLOCKS_PER_SET_L1-1) {
          icache[i][j].prev = &icache[i][j-1];
          icache[i][j].next = &icache[i][0];
          dcache[i][j].prev = &dcache[i][j-1];
          dcache[i][j].next = &dcache[i][0];
        } else {

cache[i];
    }
#endif
  }

  bool PPC_MMU::data_preprocess_and_is_enabled(uint32_t& va) const {
    return check_MSR_DR(cpu.msr);
  }

  uint8_t PPC_MMU::read_byte(uint32_t va)
  {
    try{
      if(!data_preprocess_and_is_enabled(va))
        {
          uint32_t data= memory_read_byte(va);
          debug()<<hex<<"read byte at ["<<va<<"] return "<<(size_t)data<<endl;
          return data;
        } else
        {
          uint32_t pa=virt_to_phy(va,MMU_BYTE_TYPE,MMU_READ,dTLBs);
#ifdef CACHE
          uint32_t data=cache_search(va, 0, MMU_BYTE_TYPE, MMU_READ, MMU_BYTE_TYPE);
#else
          uint32_t data=memory_read_byte(pa);
#endif
          debug()<<hex<<"read byte at ["<<va<<"]->["<<pa<<"] return "<<(size_t)data<<endl;
          return data;
        }
    }catch(MMU_Faults<BUS32>& faults)
      {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
        return 0;
      }
  };

  void PPC_MMU::write_byte(uint32_t va,uint8_t data){
    try{
      if (!data_preprocess_and_is_enabled(va)) {
        debug()<<hex<<"write byte "<<(size_t)data<<" at ["<<va<<"]"<<endl;
        memory_write_byte(va,data);
      } else {
        uint32_t pa=virt_to_phy(va,MMU_BYTE_TYPE,MMU_WRITE,dTLBs);
        debug()<<hex<<"write byte "<<(size_t)data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
#ifdef CACHE
        cache_search(pa, data, MMU_BYTE_TYPE, MMU_WRITE, MMU_BYTE_TYPE);
#else
        memory_write_byte(pa,data);
#endif
      }
    }catch(MMU_Faults<BUS32>& faults)
      {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
      }
  };

  uint16_t PPC_MMU::read_half(uint32_t va){
    try{
      if (!data_preprocess_and_is_enabled(va))
        {
          uint32_t data=memory_read_half(va);
          debug()<<hex<<"read half at ["<<va<<"] return "<<data<<endl;
          return data;
        } else
        {
          uint32_t pa=virt_to_phy(va,MMU_HALF_TYPE,MMU_READ,dTLBs);
#ifdef CACHE
          uint32_t data=cache_search(pa, 0, MMU_HALF_TYPE, MMU_READ, MMU_HALF_TYPE);
#else
          uint32_t data=memory_read_half(pa);
#endif
          debug()<<hex<<"read half at ["<<va<<"]->["<<pa<<"] return "<<data<<endl;
          return data;
        }
    }catch(MMU_Faults<BUS32>& faults)
      {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
        return 0;
      }
  };

  void PPC_MMU::write_half(uint32_t va,uint16_t data){
    try{
      if (!data_preprocess_and_is_enabled(va))
        {
          debug()<<hex<<"write half "<<data<<" at ["<<va<<"]"<<endl;
          memory_write_half(va,data);
        } else
        {
          uint32_t pa=virt_to_phy(va,MMU_HALF_TYPE,MMU_WRITE,dTLBs);
          debug()<<hex<<"write half "<<data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
#ifdef CACHE
          cache_search(pa, data, MMU_HALF_TYPE, MMU_WRITE, MMU_HALF_TYPE);
#else
          memory_write_half(pa,data);
#endif
        }
    }catch(MMU_Faults<BUS32>& faults)
      {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
      }
  };

  uint16_t PPC_MMU::load_instr_16(uint32_t va){
    try{
      if (!code_preprocess_and_is_enabled(va)) {
        debug()<<hex<<"load instruction at ["<<va<<"]"<<endl;
        return memory_read_half(va);
      } else {
        uint32_t pa=virt_to_phy(va,MMU_HALF_TYPE,MMU_READ,iTLBs);
        debug()<<hex<<"load instruction at ["<<va<<"]->["<<pa<<"]"<<endl;
        return memory_read_half(pa);
      }
    }catch(MMU_Faults<BUS32>& faults)
      {
        handle_instruction_faults(faults.virt_addr,faults.fault,faults.domain);
        return 0;
      }
  };

  uint32_t PPC_MMU::virt_to_phy(const uint32_t va,
                                const mmu_data_type data_type, // used to check alignment
                                const mem_op_type op_type, // used to check permission
                                TLB<PPC_MMU::word_t> *tlbs) {
    PPC_TLBEntry tlbEntry(va, 0, PPC_PAGE_SHIFT);
    translation_table_walk(tlbEntry, data_type, op_type);
    return tlbEntry.getPA(va);
  }

  bool PPC_MMU::bat_translate(const mmu_data_type data_type,
                              const mem_op_type op_type, PPC_TLBEntry &tlbEntry) {
    //MSR_PR=0 in supervisor mode, 1 in user mode
    const uint32_t va = tlbEntry.virt_addr;
    const uint32_t isvalid =
      check_MSR_PR(cpu.msr) ? BATU_Vp : BATU_Vs;
    debug()<<"va: "<<hex<<va<<endl;
    for (int i = 0; i < 8; i++) {
      uint32_t batu;
      uint32_t batl;
      if (data_type == MMU_CODE_TYPE) {
        batu = cpu.ibatu[i];
        batl = cpu.ibatl[i];
      } else {
        batu = cpu.dbatu[i];
        batl = cpu.dbatl[i];
      }

      const uint32_t bl = BATU_BL(batu);
      const uint32_t addr = va & ((~bl) <<17);
      if (BATU_BEPI_SHIFT(addr) == BATU_BEPI_SHIFT(batu)) {
        //bat hit
        if (batu & isvalid) {
          // bat entry valid
          bat = true;
          uint32_t page = BAT_EA_11_SHIFT(va);
          page &= (bl << 17);
          page |= BATL_BRPN_SHIFT(batl);
          tlbEntry.pte1 = page;
          tlbEntry.mask = BAT_SHIFT;
          return true;
        }
      }
    }
    bat = false;
    return false;
  }

  bool PPC_MMU::seg_translate(const mmu_data_type data_type,
                              const mem_op_type op_type,
                              PPC_TLBEntry &tlbEntry) {
    const uint32_t va = tlbEntry.virt_addr;

    const uint32_t API  = EA_API(va);
    const uint32_t sr   = cpu.sr[EA_SR(va)];
    const uint32_t VSID = SR_VSID(sr);
    const uint32_t htaborg_shift =
      SDR1_HTABORG_SHIFT(cpu.sdr1);
    const uint32_t htabmask = SDR1_HTABMASK(cpu.sdr1);

    if (check_SR_T(sr))  //direct-store segment-optional
      debug()<<"SR_T = 1: direct-store segment-optional\n";

    /*TLB check should be here, but simsoc do it in mmu.h
     *FIXME: page address translation and segment executable check
     */

    //MSR_PR=0 in supervisor mode, 1 in user mode
    const int key =
      (check_MSR_PR(cpu.msr))?
      ((sr & check_SR_Kp(sr)) ? 1 : 0):
      ((sr & check_SR_Ks(sr)) ? 1 : 0); //super mode

    uint32_t hashval = VSID ^ EA_PageIndex(va);//primary PTEG
    for (int flag = 0; flag<2; ++flag) {
      if (flag == 1)//secondary PTEG
        hashval = ~hashval;
      uint32_t ptabgroup_addr = (htaborg_shift & ((~htabmask) << 16))
        | (((((htabmask + 1) << 10) - 1) & hashval) << 6);

      for (int i = 0; i<8; i++, ptabgroup_addr += 8) {
        uint32_t pte = memory_read_word(ptabgroup_addr);

        if (check_PTE0_V(pte) && (!check_PTE0_H(pte))
            && (VSID == PTE0_VSID(pte)) && (API == PTE0_API(pte))) {
          // page found and check access
          pte = memory_read_word(ptabgroup_addr + 4);

          if (key == 1 && PTE1_PP(pte) == 0) {//prohibited R/W
            if (op_type ==  MMU_WRITE)
              throw MMU_Faults<BUS32>(va, PPC_EXC_PROT | PPC_EXC_STORE);
            else
              throw MMU_Faults<BUS32>(va, PPC_EXC_PROT);
          }
          if (op_type == MMU_WRITE) {//prohibited W
            if((PTE1_PP(pte) == 0x3)
               || (key == 1 && PTE1_PP(pte) == 0x1))
              throw MMU_Faults<BUS32>(va, PPC_EXC_PROT | PPC_EXC_STORE);
          }

          // update access bits
          if (op_type == MMU_WRITE) {
            set_PTE1_C(pte);
            set_PTE1_R(pte);
          } else
            set_PTE1_R(pte);
          memory_write_word(ptabgroup_addr + 4, pte);

          tlbEntry.pte1 = pte;
          return true;
        }
      }
    }//end flag for

    return false;
  }

  void PPC_MMU::translation_table_walk(PPC_TLBEntry &tlbEntry,
                                       const mmu_data_type data_type,
                                       const mem_op_type op_type) {
    if (data_type == MMU_CODE_TYPE) {
      if (!(cpu.msr & MSR_IR)) {// mmu disabled [code]
        tlbEntry.pte1 = tlbEntry.virt_addr;
        return;
      }
    } else {
      if (!(cpu.msr & MSR_DR)) {// mmu disabled [data]
        tlbEntry.pte1 = tlbEntry.virt_addr;
        return;
      }
    }

    if (bat_translate(data_type, op_type, tlbEntry)) //bat translate first
      return;

    if (seg_translate(data_type, op_type, tlbEntry))
      return;

    //page fault...
    throw MMU_Faults<BUS32>(tlbEntry.virt_addr, PPC_EXC_PAGE);//TODO
  }


  void PPC_MMU::handle_data_faults(uint32_t va, uint32_t fault,
                                   uint32_t domain, mem_op_type op_type) {
    //debug() <<"data abort exception raised." <<endl;
    if(op_type == MMU_WRITE)
      fault |= PPC_EXC_STORE;
    static_cast<PPC_Processor*>(proc)->interrupt(INT_DSI, fault, va);
  }

  void PPC_MMU::handle_instruction_faults(uint32_t va,
                                          uint32_t fault,uint32_t domain,mem_op_type op_type) {
    //debug() <<"software interrupt raised." <<endl;
    static_cast<PPC_Processor*>(proc)->interrupt(INT_ISI, fault, va);
  }

#ifdef CACHE
  uint32_t cache_search(uint32_t pa, uint32_t data, mmu_data_type data_type, mem_op_type op_type, mmu_data_type code_data) {
    uint32_t addr_tag = pa >> 12;
    uint32_t set_num = (pa >> BLOCK_SIZE_LOG_L1) & 0x7f;

  again:
    if(code_data == MMU_CODE_TYPE) {
      for(int i = 0; i < BLOCKS_PER_SET_L1; i++) {

        if(icache[set_num][i].addr_tag == addr_tag) {//hit... todo: mesi protocol...
          update_list(ihead[set_num], &icache[set_num][i]);

          switch(data_type) {
          case MMU_BYTE_TYPE:
            if(op_type == MMU_READ)
              return icache[set_num][i].block[(pa & 0x1f) ^ 3];
            else {
              icache[set_num][i].block[(pa & 0x1f) ^ 3] = data;
              icache[set_num][i].status = MODIFY;
            }
            return 0;
          case MMU_HALF_TYPE:
            if(op_type == MMU_READ)
              return (((uint16_t*))icache[set_num][i].block)[((pa & 0x1f)/2) ^ 1];
            else {
              ((uint16_t*)icache[set_num][i].block)[((pa & 0x1f)/2) ^ 1] = data;
              icache[set_num][i].status = MODIFY;
            }
            return 0;
          case MMU_WORD_TYPE:
            if(op_type == MMU_READ)
              return ((uint32_t*)icache[set_num][i].block)[pa & 0x1f];
            else {
              ((uint32_t*)icache[set_num][i].block)[pa & 0x1f] = data;
              icache[set_num][i].status = MODIFY;
            }
            return 0;
          default:
            debug()<<"mmu data type error!"<<endl;
            exit(-1);
          }
        }
      }
    } else {
      for(int i = 0; i < BLOCKS_PER_SET_L1; i++) {
        if(dcache[set_num][i].addr_tag == addr_tag) {//hit... todo: mesi protocol...
          update_list(dhead[set_num], &dcache[set_num][i]);

          switch(data_type) {
          case MMU_BYTE_TYPE:
            if(op_type == MMU_READ)
              return dcache[set_num][i].block[(pa & 0x1f) ^ 3];
            else {
              dcache[set_num][i].block[(pa & 0x1f) ^ 3] = data;
              dcache[set_num][i].status = MODIFY;
            }
            return 0;
          case MMU_HALF_TYPE:
            if(op_type == MMU_READ)
              return ((uint16_t*)dcache[set_num][i].block)[((pa & 0x1f)/2) ^ 1];
            else {
              ((uint16_t*)dcache[set_num][i].block)[((pa & 0x1f)/2) ^ 1] = data;
              dcache[set_num][i].status = MODIFY;
            }
            return 0;
          case MMU_WORD_TYPE:
            if(op_type == MMU_READ)
              return ((uint32_t*)dcache[set_num][i].block)[pa & 0x1f];
            else {
              ((uint32_t*)dcache[set_num][i].block)[pa & 0x1f] = data;
              dcache[set_num][i].status = MODIFY;
            }
            return 0;
          default:
            debug()<<"mmu data type error!"<<endl;
            exit(-1);
          }
        }
      }
    }

    //cache l1  miss...
    update_cache_l1(pa, code_data);
    goto again;

  }


  uint32_t cache_search_l2(uint32_t pa, uint32_t data, mmu_data_type data_type, mem_op_type op_type) {
    uint32_t addr_tag = pa >> 17;
    uint32_t set_num = (pa >> BLOCK_SIZE_LOG_L2) & 0xfff;

  again:
    for(int i = 0; i < BLOCKS_PER_SET_L2; i++) {
      if(cache[set_num][i].addr_tag == addr_tag) {//hit... todo: mesi protocol...
        update_list(head[set_num], &cache[set_num][i]);

        switch(data_type) {
        case MMU_BYTE_TYPE:
          if(op_type == MMU_READ)
            return cache[set_num][i].block[(pa & 0x1f) ^ 3];
          else {
            cache[set_num][i].block[(pa & 0x1f) ^ 3] = data;
            cache[set_num][i].status = MODIFY;
          }
          return 0;
        case MMU_HALF_TYPE:
          if(op_type == MMU_READ)
            return ((uint16_t*)cache[set_num][i].block)[((pa & 0x1f)/2) ^ 1];
          else {
            ((uint16_t*)cache[set_num][i].block)[((pa & 0x1f)/2) ^ 1] = data;
            cache[set_num][i].status = MODIFY;
          }
          return 0;
        case MMU_WORD_TYPE:
          if(op_type == MMU_READ)
            return ((uint32_t*)cache[set_num][i].block)[pa & 0x1f];
          else {
            ((uint32_t*)cache[set_num][i].block)[pa & 0x1f] = data;
            cache[set_num][i].status = MODIFY;
          }
          return 0;
        default:
          debug()<<"mmu data type error!"<<endl;
          exit(-1);
        }
      }
    }

    //cache l2  miss...
    update_cache_l2(pa);
    goto again;

  }

  void update_cache_l1(uint32_t pa, mmu_data_type code_data) {
    int blockn = -1, tmp = -1;
    block_t* bp = NULL;
    uint32_t addr_tag = pa >> 12;
    uint32_t set_num = (pa >> BLOCK_SIZE_LOG_L1) & 0x7f;

    if(code_data == MMU_CODE_TYPE) {
      for(int i = 0; i < BLOCKS_PER_SET_L1; i++) {
        if((icache[set_num][i].status & 4) == 0) {
          blockn = i;
          bp = &icache[set_num][i];
          break;
        }
        if(ihead->prev == &icache[set_num][i])
          tmp = i;
      }
      if(blockn == -1) {
        bp = ihead->prev;
      }
    } else {
      for(int i = 0; i < BLOCKS_PER_SET_L1; i++) {
        if((dcache[set_num][i].status & 4) == 0) {
          blockn = i;
          bp = &dcache[set_num][i];
          break;
        }
        if(dhead->prev == &dcache[set_num][i])
          tmp = i;
      }
      if(blockn == -1) {
        bp = dhead->prev;
      }
    }

    if(blockn == -1) {//full, have to relpace block out
      assert(tmp!=-1);
      blockn = tmp;
      if(pb->status == MODIFY)
        for(int i = 0; i < BLOCKS_SIZE_L1; i++) {
          cache_search_l2((pb->addr_tag<<12)|(set_num<<5)+i, ((uint32_t*)pb->block)[i], MMU_WORD_TYPE, MMU_WRITE);
        }
    }

    if(code_data == MMU_CODE_TYPE) {
      for(int i = 0; i < BLOCKS_SIZE_L1; i++) {
        ((uint32_t*)icache[set_num][blockn].block)[i] = cache_search_l2((pa+i) & ~0x3, 0, MMU_WORD_TYPE, MMU_READ);
      }

      icache[set_num][blockn].status = SHARED;
      icache[set_num][blockn].addr_tag = addr_tag;
    } else {
      for(int i = 0; i < BLOCKS_SIZE_L1; i++) {
        ((uint32_t*)dcache[set_num][blockn].block)[i] = cache_search_l2((pa+i) & ~0x3, 0, MMU_WORD_TYPE, MMU_READ);
      }

      dcache[set_num][blockn].status = SHARED;
      dcache[set_num][blockn].addr_tag = addr_tag;
    }

  }

  void update_cache_l2(uint32_t pa) {
    int blockn = -1, tmp = -1;
    block_t* bp = NULL;
    uint32_t addr_tag = pa >> 17;
    uint32_t set_num = (pa >> BLOCK_SIZE_LOG_L2) & 0xfff;

    for(int i = 0; i < BLOCKS_PER_SET_L2; i++) {
      if((cache[set_num][i].status & 4) == 0) {
        blockn = i;
        bp = &cache[set_num][i];
        break;
      }
      if(head->prev == &cache[set_num][i])
        tmp = i;
    }

    if(blockn == -1) {//full, have to relpace block out
      assert(tmp!=-1);
      blockn = tmp;
      bp = head->prev;
      if(pb->status == MODIFY)
        for(int i = 0; i < BLOCKS_SIZE_L1; i++) {
          memory_write_word((pb->addr_tag<<12)|(set_num<<5)+i, ((uint32_t*)pb->block)[i]);
        }
    }

    for(int i = 0; i < BLOCKS_SIZE_L2; i++) {
      ((uint32_t*)cache[set_num][blockn].block)[i] = memory_read_word((pa+i) & ~0x3);
      cache[set_num][blockn].status = SHARED;
      cache[set_num][blockn].addr_tag = addr_tag;
    }

  }

#endif

} // namespace simsoc
