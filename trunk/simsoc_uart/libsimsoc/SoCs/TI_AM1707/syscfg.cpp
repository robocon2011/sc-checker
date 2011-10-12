//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/SoCs/TI_AM1707/syscfg.hpp"
#include <cstring>

namespace simsoc    {
namespace TI_AM1707 {

  // ------------------------------------------------------------------
  SYSCFG::SYSCFG(sc_core::sc_module_name name)
    :TI_AM1x::TI_AM1x_core<SYSCFG>(name, this)
  {
    memset(m_registers, 0, NREGS * sizeof(uint32_t));
    m_registers[REG_INDEX_REVID]   = REVID;
    m_registers[REG_INDEX_DEVIDR0] = DEVIDR0;
  }

  // ------------------------------------------------------------------
  size_t SYSCFG::to_regindex(uint32_t address) {
    if ((address & 0x3)) {
      warning()
        << "address not properly aligned: " << address
        << std::endl;
      return (size_t) -1;
    }

    const size_t regindex = (address >> 2);

    if (regindex >= NREGS) {
      warning()
        << "address does not denote a valid register: " << address
        << std::endl;
      return (size_t) -1;
    }

    return regindex;
  }

  // ------------------------------------------------------------------
  uint32_t SYSCFG::read_word(uint32_t address) {
    size_t regindex = this->to_regindex(address);
    return (regindex == (size_t) -1) ? 0 : m_registers[regindex];
  }

  // ------------------------------------------------------------------
  void SYSCFG::write_word(uint32_t address, uint32_t value) {
    size_t regindex = this->to_regindex(address);

    if (regindex != (size_t) -1) {
      if (regindex == REG_INDEX_REVID) {
        warning() << "[REVID] is read-only" << std::endl;
        return ;
      }
      if (regindex == REG_INDEX_DEVIDR0) {
        warning() << "[DEVIDR0] is read-only" << std::endl;
        return ;
      }

      m_registers[regindex] = value;
    }
  }

} // TI_AM1707
} // simsoc
