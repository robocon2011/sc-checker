//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// Implementation of "mmu.hpp"
// This file is included only by "mmu.cpp"
#include "mmu.hpp"

using namespace std;

namespace simsoc {
  // initilization
  template <typename word_t>
  MMU<word_t>::MMU(sc_core::sc_module_name name, Processor *proc_):
    Module(name),
    hmemory(),
    iTLBs(NULL), dTLBs(NULL), user_mode(true),
    proc(proc_)
  {
    isUnified = getTLBs();
    pl.set_streaming_width(sizeof(word_t));
    rw_socket.register_invalidate_direct_mem_ptr(this, &MMU<word_t>::invalidate_dm_ptr);
  }

  // free on exit
  template <typename word_t>
  MMU<word_t>::~MMU() {
    if (!isUnified)
      delete iTLBs;
    else
      assert(iTLBs==dTLBs);
    delete dTLBs;
  }

  template <typename word_t>
  void MMU<word_t>::reset() {
    hmemory.reset();
    assert(dTLBs);
    dTLBs->invalidate_all_entries();
    if(!isUnified)
      iTLBs->invalidate_all_entries();
  }

  // memory related operation

  // Get DMI using TLM 2.0.1
  template <typename word_t>
  void MMU<word_t>::get_dmi_at_address(uint64_t addr) {
    pl.set_command(tlm::TLM_WRITE_COMMAND);
    pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
    pl.set_address(addr);
    pl.set_data_ptr(NULL);
    pl.set_data_length(0);
    DirectInstrCacheExtension ext = DirectInstrCacheExtension(proc);
    pl.set_extension(&ext);
    tlm::tlm_dmi dmi_data;
    dmi_data.init();
    bool status = rw_socket->get_direct_mem_ptr(pl,dmi_data);
    if (!status) {
      info() <<"cannot get DMI access at address " <<hex <<addr <<'\n';
      pl.clear_extension(&ext);
      return;
    }
    if (!dmi_data.is_read_write_allowed()) {
      error() <<"wrong permission for DMI at address " <<hex <<addr <<'\n';
      exit(1);
    }
    if (!ext.table) {
      warning() <<"no instruction cache for DMI at address " <<hex <<addr <<'\n';
    }
    pl.clear_extension(&ext);
    const uint64_t start_addr = dmi_data.get_start_address();
    const uint64_t size = dmi_data.get_end_address()+1-start_addr;
    hmemory.add_dmi(dmi_data.get_dmi_ptr(),size,start_addr,ext.table);
    info() <<"DMI successfully obtained for address " <<hex <<addr <<".\n";
  }

  template <typename word_t>
  unsigned int MMU<word_t>::transport_dbg(tlm::tlm_generic_payload &payload) {
    const word_t va_begin = payload.get_address();
    const word_t va_end = va_begin+payload.get_data_length();
    debug() <<"debug access from " <<hex <<va_begin << " to " <<va_end-1 <<".\n";
    const uint32_t page_size = TranslationPage::TR_PAGE_SIZE;
    if (va_begin/page_size!=(va_end-1)/page_size) {
      debug() <<"transport_dbg accesses many pages.\n";
      tlm::tlm_generic_payload pl;
      pl.set_command(payload.get_command());
      pl.set_data_ptr(payload.get_data_ptr());
      pl.set_streaming_width(payload.get_streaming_width());
      pl.set_byte_enable_ptr(payload.get_byte_enable_ptr());
      pl.set_byte_enable_length(payload.get_byte_enable_length());
      pl.set_dmi_allowed(false);
      uint32_t count = 0;
      word_t va = va_begin;
      while (count!=payload.get_data_length()) {
        const uint32_t size = std::min(static_cast<uint32_t>(page_size-(va%page_size)),
                                       payload.get_data_length()-count);
        pl.set_address(va);
        pl.set_data_length(size);
        pl.set_response_status(tlm::TLM_INCOMPLETE_RESPONSE);
        const uint32_t n = this->transport_dbg(pl);
        count += n;
        if (size!=n || !pl.is_response_ok()) {
          info() <<"a partial transport_dbg access failed.\n";
          payload.set_response_status(pl.get_response_status());
          return count;
        } else {
          va += n;
          pl.set_data_ptr(pl.get_data_ptr()+n);
        }
      }
      return count;
    } else { // access inside one page
      // check command
      mem_op_type op;
      switch (payload.get_command()) {
      case tlm::TLM_READ_COMMAND: op = MMU_READ; break;
      case tlm::TLM_WRITE_COMMAND: op = MMU_WRITE; break;
      default:
        info() <<"transport_dbg command is neither READ nor WRITE.\n";
        payload.set_response_status(tlm::TLM_COMMAND_ERROR_RESPONSE);
        return 0;
      }
      // do the address translation
      word_t pa = va_begin;
      if (data_preprocess_and_is_enabled(pa)) {
        try {
          mmu_data_type dt;
          switch (payload.get_streaming_width()) {
          case 1: dt = MMU_BYTE_TYPE; break;
          case 2: dt = MMU_HALF_TYPE; break;
          case 4: dt = MMU_WORD_TYPE; break;
          default: dt = MMU_DATA_TYPE; break;
          }
          pa = virt_to_phy(pa,dt,op,dTLBs);
        } catch (MMU_Faults<word_t>& faults) {
          info() <<"transport_dbg rejected by MMU.\n";
          payload.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
          return 0;
        }
      } else {
        // check alignment
        const unsigned int sw = payload.get_streaming_width();
        if (pa%sw!=0 || payload.get_data_length()%sw!=0) {
          info() <<"wrong alignment; check streaming_width.\n";
          payload.set_response_status(tlm::TLM_ADDRESS_ERROR_RESPONSE);
          return 0;
        }
      }
      if (pa!=va_begin) {
        payload.set_address(pa);
        info() <<"address translation: " <<hex <<va_begin <<" -> " <<pa <<'\n';
      }
      // do the access
      const unsigned int sw = payload.get_streaming_width();
      if (is_bigendian() && sw!=sizeof(word_t)) {
        // big endian: we proceed step by step
        unsigned int size = payload.get_data_length();
        unsigned char *data = payload.get_data_ptr();
        tlm::tlm_generic_payload *pl = NULL;
        for (unsigned int i = 0; i<size; i+=sw) {
          const word_t addr = addr_swizzling(pa+i,sw);
          if (hmemory.dmi_address(addr)) {
            // debug() <<"using DMI.\n";
            if (op==MMU_READ)
              memcpy(&data[i],hmemory.raw(addr),sw);
            else
              memcpy(hmemory.raw(addr),&data[i],sw);
          } else {
            // debug() <<"using transaction.\n";
            if (!pl) {
              // initialize pl if necessary
              pl = new tlm::tlm_generic_payload();
              pl->set_streaming_width(sw);
              pl->set_command(op==MMU_READ? tlm::TLM_READ_COMMAND:
                              tlm::TLM_WRITE_COMMAND);
            }
            set_payload(*pl,addr,&data[i],sw);
            const unsigned int n = rw_socket->transport_dbg(*pl);
            if (n!=sw || !pl->is_response_ok()) {
              payload.set_response_status(pl->get_response_status());
              delete pl;
              return i;
            }
          }
        }
        delete pl;
        payload.set_response_status(tlm::TLM_OK_RESPONSE);
        return size;
      } else {
        // no endianness conversion is required
        // debug() <<"using burst transaction.\n";
        return rw_socket->transport_dbg(payload);
      }
    }
  }

  template <typename word_t>
  void MMU<word_t>::invalidate_dm_ptr(sc_dt::uint64 start_range,
                                      sc_dt::uint64 end_range) {
    TODO("invalidate direct memory interface");
  }

  /*
   * default mmu implementation
   */
  template <typename word_t>
  uint8_t MMU<word_t>::read_byte(word_t va)
  {
    if (!data_preprocess_and_is_enabled(va)) {
      const uint8_t data= memory_read_byte(va);
      debug()<<hex<<"read byte at ["<<va<<"] return " <<(size_t)data <<endl;
      return data;
    } else {
      try {
        const word_t pa=virt_to_phy(va,MMU_BYTE_TYPE,MMU_READ,dTLBs);
        const uint8_t data=memory_read_byte(pa);
        debug()<<hex<<"read byte at ["<<va<<"]->["<<pa<<"] return "<<(size_t)data <<endl;
        return data;
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
        return 0;
      }
    }
  }

  template <typename word_t>
  void MMU<word_t>::write_byte(word_t va,uint8_t data){
    if (!data_preprocess_and_is_enabled(va)) {
      debug()<<hex<<"write byte "<<(size_t)data<<" at ["<<va<<"]"<<endl;
      memory_write_byte(va,data);
    } else {
      try {
        const word_t pa=virt_to_phy(va,MMU_BYTE_TYPE,MMU_WRITE,dTLBs);
        debug()<<hex<<"write byte "<<(size_t)data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
        memory_write_byte(pa,data);
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
      }
    }
  }

  template <typename word_t>
  uint16_t MMU<word_t>::read_half(word_t va){
    if (!data_preprocess_and_is_enabled(va)) {
      const uint16_t data=memory_read_half(va);
      debug()<<hex<<"read half at ["<<va<<"] return "<<data<<endl;
      return data;
    } else {
      try{
        const word_t pa=virt_to_phy(va,MMU_HALF_TYPE,MMU_READ,dTLBs);
        const uint16_t data=memory_read_half(pa);
        debug()<<hex<<"read half at ["<<va<<"]->["<<pa<<"] return "<<data<<endl;
        return data;
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
        return 0;
      }
    }
  }

  template <typename word_t>
  void MMU<word_t>::write_half(word_t va,uint16_t data){
    if (!data_preprocess_and_is_enabled(va)) {
      debug()<<hex<<"write half "<<data<<" at ["<<va<<"]"<<endl;
      memory_write_half(va,data);
    } else {
      try {
        const word_t pa=virt_to_phy(va,MMU_HALF_TYPE,MMU_WRITE,dTLBs);
        debug()<<hex<<"write half "<<data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
        memory_write_half(pa,data);
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
      }
    }
  }

  template <typename word_t>
  uint32_t MMU<word_t>::read_word(word_t va){
    if (!data_preprocess_and_is_enabled(va)) {
      const uint32_t data=memory_read_word(va);
      debug() <<hex<<"read word at ["<<va<<"] return "<<data <<endl;
      return data;
    } else {
      try{
        const word_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_READ,dTLBs);
        const uint32_t data=memory_read_word(pa);
        debug() <<hex<<"read word at ["<<va<<"]->["<<pa<<"] return "<<data<<endl;
        return data;
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
        return 0;
      }
    }
  }

  template <typename word_t>
  void MMU<word_t>::write_word(word_t va,uint32_t data){
    if (!data_preprocess_and_is_enabled(va)) {
      debug() <<hex<<"write word "<<data<<" at ["<<va<<"]"<<endl;
      memory_write_word(va,data);
    } else {
      try {
        const word_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_WRITE,dTLBs);
        debug() <<hex<<"write word "<<data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
        memory_write_word(pa,data);
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
      }
    }
  }

  template <typename word_t>
  uint64_t MMU<word_t>::read_double(word_t va){
    if(!data_preprocess_and_is_enabled(va)) {
      const uint64_t data=memory_read_double(va);
      debug() <<hex<<"read double at ["<<va<<"] return "<<data <<endl;
      return data;
    } else {
      try{
        const word_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_READ,dTLBs);
        const uint64_t data=memory_read_double(pa);
        debug() <<hex<<"read double at ["<<va<<"]->["<<pa<<"] return "<<data<<endl;
        return data;
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_READ);
        return 0;
      }
    }
  }

  template <typename word_t>
  void MMU<word_t>::write_double(word_t va,uint64_t data){
    if (!data_preprocess_and_is_enabled(va)) {
      debug() <<hex<<"write double "<<data<<" at ["<<va<<"]"<<endl;
      memory_write_double(va,data);
    } else {
      try{
        const word_t pa = virt_to_phy(va,MMU_WORD_TYPE,MMU_WRITE,dTLBs);
        debug() <<hex<<"write double "<<data<<" at ["<<va<<"]->["<<pa<<"]"<<endl;
        memory_write_double(pa,data);
      } catch(MMU_Faults<word_t>& faults) {
        handle_data_faults(faults.virt_addr,faults.fault,faults.domain,MMU_WRITE);
      }
    }
  }

  template <typename word_t>
  uint32_t MMU<word_t>::load_instr_32(word_t va) {
    if (!code_preprocess_and_is_enabled(va)) {
      debug() <<hex <<"load instruction at [" <<va <<"]" <<endl;
      return memory_read_word(va);
    } else {
      try {
        const word_t pa = virt_to_phy(va, MMU_WORD_TYPE, MMU_READ, iTLBs);//when unified,iTLBs == dTLBs
        debug() <<hex <<"load instruction at [" <<va <<"]->[" <<pa <<"]" <<endl;
        return  memory_read_word(pa);
      } catch(MMU_Faults<word_t>& faults) {
        handle_instruction_faults(faults.virt_addr,faults.fault,faults.domain);
        return 0;
      }
    }
  }

  template <typename word_t>
  uint16_t MMU<word_t>::load_instr_16(word_t va){
    if (!code_preprocess_and_is_enabled(va)) {
      debug()<<hex<<"load instruction at ["<<va<<"]"<<endl;
      return memory_read_half(va);
    } else {
      try{
        word_t pa=virt_to_phy(va,MMU_HALF_TYPE,MMU_READ,iTLBs);
        debug()<<hex<<"load instruction at ["<<va<<"]->["<<pa<<"]"<<endl;
        return memory_read_half(pa);
      } catch(MMU_Faults<word_t>& faults) {
        handle_instruction_faults(faults.virt_addr,faults.fault,faults.domain);
        return 0;
      }
    }
  };

  /*
   * Memory access of data size equal or larger than buswidth for 64bit architecture
   */
  template<>
  uint64_t MMU<uint64_t>::memory_read_double(uint64_t addr) {
    if (hmemory.dmi_address(addr)) {
      return *hmemory.raw64(addr);
    } else {
      uint64_t data=0;
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      set_payload(pl,addr,(unsigned char*)(&data),8);
      pl.set_command(tlm::TLM_READ_COMMAND);
      rw_socket->b_transport(pl,delay);
      if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      	TODO("should raise an exception (memory abort)");
      return data;
    }
  }

  template<>
  void MMU<uint64_t>::memory_write_double(uint64_t addr, uint64_t data){
    if (hmemory.dmi_address(addr)) {
      *hmemory.raw64(addr)=data;
    } else {
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      set_payload(pl,addr,(unsigned char*)(&data),8);
      pl.set_command(tlm::TLM_WRITE_COMMAND);
      rw_socket->b_transport(pl,delay);
      if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      	TODO("should raise an exception (memory abort)");
    }
  }

  /*
   * Memory access of data size equal or larger than buswidth for 32bit architecture
   */
  template<>
  uint64_t MMU<uint32_t>::memory_read_double(uint32_t addr) {
    if (!is_bigendian()){
      if (hmemory.dmi_address(addr)) {
        return *hmemory.raw64(addr);
      } else {
        uint64_t data=0;
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&data),8);
        pl.set_command(tlm::TLM_READ_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
        return data;
      }
    }else{
      if (hmemory.dmi_address(addr)) {
        uint64_t data = (uint64_t)(*hmemory.raw32(addr)) << 32;
        assert(hmemory.dmi_address(addr+4));
        data  |= (uint64_t)(*hmemory.raw32(addr + 4));
        return data;
      } else {
        uint64_t host_dword = 0;
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&host_dword),8);
        pl.set_command(tlm::TLM_READ_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
        return swap_words<uint32_t>(host_dword);
      }
    }
  }

  template<>
  void MMU<uint32_t>::memory_write_double(uint32_t addr, uint64_t data){
    if (!is_bigendian()) {
      if (hmemory.dmi_address(addr)) {
        *hmemory.raw64(addr)=data;
      } else {
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&data),8);
        pl.set_command(tlm::TLM_WRITE_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
      }
    } else {
      if (hmemory.dmi_address(addr)) {
        *hmemory.raw32(addr) = (uint32_t)(data>>32);
        assert(hmemory.dmi_address(addr+4));
        *hmemory.raw32(addr+4) = (uint32_t)data;
      } else {
        uint64_t host_dword = swap_words<uint32_t>(data);
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&host_dword),8);
        pl.set_command(tlm::TLM_WRITE_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
      }
    }
  }

  template <typename word_t>
  uint32_t MMU<word_t>::memory_read_word__transaction(word_t addr) {
    uint32_t data=0;
    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
    set_payload(pl, addr, (unsigned char*)(&data),4);
    pl.set_command(tlm::TLM_READ_COMMAND);
    rw_socket->b_transport(pl,delay);
    if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      TODO("should raise an exception (memory abort)");
    if (pl.is_dmi_allowed())
      get_dmi_at_address(addr);
    return data;
  }

  template <typename word_t>
  void MMU<word_t>::memory_write_word__transaction(word_t addr, uint32_t data){
    sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
    set_payload(pl,addr,(unsigned char*)(&data),4);
    pl.set_command(tlm::TLM_WRITE_COMMAND);
    rw_socket->b_transport(pl,delay);
    if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
      TODO("should raise an exception (memory abort)");
    if (pl.is_dmi_allowed())
      get_dmi_at_address(addr);
  }

  //access data size smaller than buswidth
  template <typename word_t>
  uint16_t MMU<word_t>::memory_read_half(word_t addr){
    if (is_bigendian())
      addr = addr_swizzling(addr,2);
    if (hmemory.dmi_address(addr)) {
      return *hmemory.raw16(addr);
    } else {
      uint16_t data = 0;
      sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
      set_payload(pl,addr,(unsigned char*)(&data),2);
      pl.set_command(tlm::TLM_READ_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
        return data;
    }
  }

  template <typename word_t>
  void MMU<word_t>::memory_write_byte(word_t addr, uint8_t data){
      if (is_bigendian())
        addr = addr_swizzling(addr,1);
      if (hmemory.dmi_address(addr)) {
        hmemory[addr]=data;
      } else {
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&data),1);
        pl.set_command(tlm::TLM_WRITE_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
      }
    }

  template <typename word_t>
  uint8_t MMU<word_t>::memory_read_byte(word_t addr) {
      if (is_bigendian())
        addr = addr_swizzling(addr,1);
      if (hmemory.dmi_address(addr)) {
        return hmemory[addr];
      } else {
        uint8_t data=0;
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&data),1);
        pl.set_command(tlm::TLM_READ_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
        return data;
      }
    }

  template <typename word_t>
  void MMU<word_t>::memory_write_half(word_t addr, uint16_t data){
      if (is_bigendian())
        addr = addr_swizzling(addr,2);
      if (hmemory.dmi_address(addr)) {
        *hmemory.raw16(addr)=data;
      } else {
        sc_core::sc_time delay = sc_core::SC_ZERO_TIME;
        set_payload(pl,addr,(unsigned char*)(&data),2);
        pl.set_command(tlm::TLM_WRITE_COMMAND);
        rw_socket->b_transport(pl,delay);
        if (pl.get_response_status()!=tlm::TLM_OK_RESPONSE)
          TODO("should raise an exception (memory abort)");
      }
    }

} // namespace simsoc
