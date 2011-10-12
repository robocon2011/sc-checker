//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/processors/ppc/ppc_debugger.hpp"
#include "libsimsoc/processors/ppc/ppc_processor.hpp"
#include "libsimsoc/io.hpp"

#include <vector>
#include <algorithm>
#include <inttypes.h>

namespace simsoc {

  // ------------------------------------------------------------------
  PPC_Debugger::PPC_Debugger(PPC_Processor &processor)
    :m_proc(processor)
  {}

  // ------------------------------------------------------------------
  bool PPC_Debugger::add_breakpoint(uint64_t address64, uint64_t length) {
    if ((address64 >> 32) || (address64 & 0x3))
      return false;

    uint32_t address = (uint32_t) address64;

    if (m_traps.find(address) != m_traps.end())
      return true;

    const uint32_t instruction = m_proc.mmu.read_word(address);

    try {
      m_proc.mmu.write_word(address, TRAP_EABI_INSTRUCTION);
    } catch (ISS_Exception) {
      return false;
    }
    m_traps[address] = instruction;

    return true;
  }

  // ------------------------------------------------------------------
  bool PPC_Debugger::del_breakpoint(uint64_t address64, uint64_t length) {
    if ((address64 >> 32) || (address64 & 0x3))
      return false;

    uint32_t address = (uint32_t) address64;
    traps_t::iterator instruction = m_traps.find(address);

    if (instruction == m_traps.end())
      return false;

    try {
      m_proc.mmu.write_word(address, instruction->second);
    } catch (ISS_Exception) {
      return false;
    }
    m_traps.erase(instruction);

    return true;
  }

  // ------------------------------------------------------------------
  bool PPC_Debugger::readregs(bytes_t &result) {
    Marshaller marshaller(result, Marshaller::ED_BIG);

    for (size_t i = 0; i < 32; ++i) {
      uint32_t reg = m_proc.cpu.gpr[i];

      marshaller.push_uint32(reg);
    }
    marshaller.push_uint32(m_proc.cpu.pc);
    marshaller.push_uint32(m_proc.cpu.msr);
    marshaller.push_uint32(m_proc.cpu.cr);
    marshaller.push_uint32(m_proc.cpu.lr);
    marshaller.push_uint32(m_proc.cpu.ctr);
    marshaller.push_uint32(m_proc.cpu.xer);
    return true;
  }

  bool PPC_Debugger::readreg(size_t reg_num,bytes_t &result) {
    Marshaller marshaller(result, Marshaller::ED_BIG);

    if(reg_num>=0 && reg_num<32) {
      uint32_t reg = m_proc.cpu.gpr[reg_num];
      marshaller.push_uint32(reg);
      return true;
    }

    if(reg_num == 64){
      marshaller.push_uint32(m_proc.cpu.pc);
      return true;
    }

    if(reg_num == 65){
      marshaller.push_uint32(m_proc.cpu.msr);
      return true;
    }

    if(reg_num == 66){
      marshaller.push_uint32(m_proc.cpu.cr);
      return true;
    }

    if(reg_num == 67){
      marshaller.push_uint32(m_proc.cpu.lr);
      return true;
    }

    if(reg_num == 68){
      marshaller.push_uint32(m_proc.cpu.ctr);
      return true;
    }

    if(reg_num == 69){
      marshaller.push_uint32(m_proc.cpu.xer);
      return true;
    }

    return false;
  }

  // ------------------------------------------------------------------
  size_t PPC_Debugger::read(uint64_t address64, size_t length, bytes_t &result) {
    if ((address64 >> 32))
      return false;

    tlm::tlm_generic_payload payload;

    result.resize(length);

    payload.set_command(tlm::TLM_READ_COMMAND);
    payload.set_streaming_width(1);
    payload.set_address(address64);
    payload.set_data_ptr(&result[0]);
    payload.set_data_length(length);

    unsigned rsize = m_proc.transport_dbg(0, payload);

    result.resize(rsize);

    return length;
  }

  // ------------------------------------------------------------------
  void PPC_Debugger::enable_traps () {
    traps_t::const_iterator it;

    for (it = m_traps.begin(); it != m_traps.end(); ++it) {
      try {
        m_proc.mmu.write_word(it->first, TRAP_EABI_INSTRUCTION);
      } catch (ISS_Exception) {}
    }
  }

  // ------------------------------------------------------------------
  void PPC_Debugger::disable_traps() {
    traps_t::const_iterator it;

    for (it = m_traps.begin(); it != m_traps.end(); ++it) {
      try {
        m_proc.mmu.write_word(it->first, it->second);
      } catch (ISS_Exception) {}
    }
  }
}
