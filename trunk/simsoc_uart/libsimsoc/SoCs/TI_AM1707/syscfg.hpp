//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1707_SYSCFG_HPP__)
# define LIBSIMSOC_TI_AM1707_SYSCFG_HPP__

# include "libsimsoc/components/ti_am1x_core.hpp"

# include <sys/types.h>
# include <inttypes.h>

namespace simsoc    {
namespace TI_AM1707 {

  // ------------------------------------------------------------------
  class SYSCFG: public TI_AM1x::TI_AM1x_core<SYSCFG> {
  protected:
    static const size_t NREGS = 100;

    static const size_t REG_INDEX_REVID   = 0;
    static const size_t REG_INDEX_DEVIDR0 = 6;

    size_t to_regindex(uint32_t address);

  public:
    static const uint32_t REVID   = 0x4E840102;
    static const uint32_t DEVIDR0 = 0x0B7DF02F;

  public:
    SYSCFG(sc_core::sc_module_name name);

  protected:
    uint32_t read_word (uint32_t address);
    void     write_word(uint32_t address, uint32_t value);

  protected:
    uint32_t m_registers[NREGS];
  };

} // TI_AM1707
} // simsoc

#endif // !LIBSIMSOC_TI_AM1707_SYSCFG_HPP__
