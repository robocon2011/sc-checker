//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/SoCs/TI_AM1707/psc.hpp"

namespace simsoc    {
namespace TI_AM1707 {

  // ------------------------------------------------------------------
  PSC::PSC(sc_core::sc_module_name name, size_t mnds)
    :TI_AM1x::TI_AM1x_core<PSC>(name, this)
    ,m_nmds                    (mnds)
    ,m_mdstate                 (NULL)
  {
    m_mdstate = new uint32_t[mnds];
    for (size_t i = 0; i < m_nmds; ++i)
      m_mdstate[i] = 0x02;
  }

  PSC::~PSC() {
    if (m_mdstate)
      delete[] m_mdstate;
  }

  // ------------------------------------------------------------------
  uint32_t PSC::read_word(uint32_t address) {
    if ((address & 0x3)) {
      warning()
        << "address not properly aligned: " << address
        << std::endl;
      return 0;
    }

    if (address >= R_MDSTAT && address < (R_MDSTAT + 4 * m_nmds))
      return m_mdstate[(address - R_MDSTAT) >> 2];
    if (address >= R_MDCTL && address < (R_MDCTL + 4 * m_nmds))
      return m_mdstate[(address - R_MDCTL) >> 2];

    switch (address) {
    case R_REVID:
      return REVID;

    case R_PDSTAT0:
    case R_PDSTAT1:
      return 0x00000001;

    case R_PTSTAT:
      return 0x00000000;
    }

    warning() << "unsupported R-address: " << address << std::endl;
    return 0;
  }

  // ------------------------------------------------------------------
  void PSC::write_word(uint32_t address, uint32_t value) {
    if ((address & 0x3)) {
      warning()
        << "address not properly aligned: " << address
        << std::endl;
      return ;
    }

    if (address >= R_MDCTL && address < (R_MDCTL + 4 * m_nmds)) {
      m_mdstate[(address - R_MDCTL) >> 2] = value & 0x3F;
      return ;
    }

    if (address == R_PTCMD)
      return ;                  // OK

    warning() << "unsupported W-address: " << address << std::endl;
  }

} // TI_AM1707
} // simsoc

