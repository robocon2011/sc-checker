//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1707_PSC_HPP__)
# define LIBSIMSOC_TI_AM1707_PSC_HPP__

# include "libsimsoc/components/ti_am1x_core.hpp"

namespace simsoc    {
namespace TI_AM1707 {

  class PSC: public TI_AM1x::TI_AM1x_core<PSC> {
  public:
    static const uint32_t REVID = 0x44823A00;

    static const uint32_t R_REVID   = 0x0000;
    static const uint32_t R_PTCMD   = 0x0120;
    static const uint32_t R_PTSTAT  = 0x0128;
    static const uint32_t R_PDSTAT0 = 0x0200;
    static const uint32_t R_PDSTAT1 = 0x0204;
    static const uint32_t R_MDSTAT  = 0x0800;
    static const uint32_t R_MDCTL   = 0x0A00;

  public:
    PSC(sc_core::sc_module_name name, size_t nmds);
    virtual ~PSC();

  protected:
    uint32_t read_word (uint32_t address);
    void     write_word(uint32_t address, uint32_t value);

  protected:
    size_t    m_nmds;
    uint32_t *m_mdstate;
  };

} // TI_AM1707
} // simsoc

#endif // !LIBSIMSOC_TI_AM1707_PSC_HPP__
