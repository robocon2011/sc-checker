//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TI_AM1707_HPP__)
# define LIBSIMSOC_TI_AM1707_HPP__

# include "libsimsoc/module.hpp"
# include "libsimsoc/components/bus.hpp"
# include "libsimsoc/components/memory.hpp"
# include "libsimsoc/processors/processor.hpp"
# include "libsimsoc/components/ti_am1x_aintc.hpp"
# include "libsimsoc/components/ti_am1x_timer64.hpp"
# include "libsimsoc/components/ti_am1x_rtc.hpp"
# include "libsimsoc/components/ti_am1x_uart.hpp"
# include "libsimsoc/components/ti_am1x_emac.hpp"
# include "libsimsoc/components/rw_stub.hpp"
# include "libsimsoc/network/ethernet/ether-transport.hpp"

# include "libsimsoc/SoCs/TI_AM1707/syscfg.hpp"
# include "libsimsoc/SoCs/TI_AM1707/psc.hpp"

# include <vector>
# include <inttypes.h>

namespace simsoc    {
namespace TI_AM1707 {

  class Board: public Module {
  public:
    Board(sc_core::sc_module_name name);
    virtual ~Board();

  public:
    inline TI_AM1x::Uart& serial0() { return m_uart0; }
    inline TI_AM1x::Uart& serial1() { return m_uart1; }
    inline TI_AM1x::Uart& serial2() { return m_uart2; }

    inline Memory& memory()
    { return m_dram; }

    inline Processor& processor()
    { return *m_processor; }

    inline Bus& bus()
    { return m_bus; }

    void set_ether_transport(IEtherTransport *transport);

  protected:
    typedef RW_Stub stub_t;
    typedef std::vector<stub_t*> stubs_t;

    Bus               m_bus;
    Memory            m_dram;
    Processor        *m_processor;
    TI_AM1x::Uart     m_uart0;
    TI_AM1x::Uart     m_uart1;
    TI_AM1x::Uart     m_uart2;
    TI_AM1707::SYSCFG m_syscfg;
    TI_AM1707::PSC    m_psc0;
    TI_AM1707::PSC    m_psc1;
    TI_AM1x::AINTC    m_irqc;
    TI_AM1x::Timer64  m_timer64_0;
    TI_AM1x::Timer64  m_timer64_1;
    TI_AM1x::RTC      m_rtc;
    TI_AM1x::EMAC     m_emac;
    Memory            m_emac_mem; // This memory should be internal
    stubs_t           m_stubs;

  protected:
    struct stub_infos_t {
      const char *name;
      uint32_t    base;
      uint32_t    size;
    };

    static stub_infos_t stubs[];

  public:
    static const unsigned int RTC_IT              =  4;
    static const unsigned int IRQ_TIMER64P0_12    = 21;
    static const unsigned int IRQ_TIMER64P0_34    = 22;
    static const unsigned int IRQ_TIMER64P1_12    = 23;
    static const unsigned int IRQ_TIMER64P1_34    = 24;
    static const unsigned int IRQ_UART0           = 25;
    static const unsigned int IRQ_EMAC_C0RXTHRESH = 33;
    static const unsigned int IRQ_EMAC_C0RX       = 34;
    static const unsigned int IRQ_EMAC_C0TX       = 35;
    static const unsigned int IRQ_EMAC_C0MISC     = 36;
    static const unsigned int IRQ_EMAC_C1RXTHRESH = 37;
    static const unsigned int IRQ_EMAC_C1RX       = 38;
    static const unsigned int IRQ_EMAC_C1TX       = 39;
    static const unsigned int IRQ_EMAC_C1MISC     = 40;
    static const unsigned int IRQ_UART1           = 53;
    static const unsigned int IRQ_UART2           = 61;
    static const unsigned int IRQ_TIMER64P0_CMP   = 74;
    static const unsigned int IRQ_TIMER64P1_CMP   = 82;

  public:
    static const uint32_t UART0_BASE            = 0x01C42000;
    static const uint32_t UART1_BASE            = 0x01D0C000;
    static const uint32_t UART2_BASE            = 0x01D0D000;
    static const uint32_t UART_SIZE             = 0x00001000;

    static const uint32_t MEMORY_BASE           = 0xC0000000;
    static const uint32_t MEMORY_SIZE           = 0x10000000;

    static const uint32_t AINTC_BASE            = 0xFFFEE000;

    static const uint32_t SYSCFG_BASE           = 0x01C14000;
    static const uint32_t SYSCFG_SIZE           = 0x00001000;

    static const uint32_t PSC0_BASE             = 0x01C10000;
    static const uint32_t PSC0_SIZE             = 0x00001000;
    static const uint32_t PSC1_BASE             = 0x01E27000;
    static const uint32_t PSC1_SIZE             = 0x00001000;

    static const uint32_t TIMER64P0_BASE        = 0x01C20000;
    static const uint32_t TIMER64P0_SIZE        = 0x00001000;
    static const uint32_t TIMER64P1_BASE        = 0x01C21000;
    static const uint32_t TIMER64P1_SIZE        = 0x00001000;

    static const uint32_t RTC_BASE              = 0x01C23000;
    static const uint32_t RTC_SIZE              = 0x00001000;

    static const uint32_t EMAC_RAM_BASE         = 0x01E20000;
    static const uint32_t EMAC_RAM_SIZE         = 0x00002000;

    static const uint32_t EMAC_MOD_BASE         = 0x01E23000; // 0x01E22000 in spec.
    static const uint32_t EMAC_MOD_SIZE         = 0x00001000;

    static const uint32_t EMAC_CTRL_BASE        = 0x01E22000; // 0x01E23000 in spec.
    static const uint32_t EMAC_CTRL_SIZE        = 0x00001000;

    static const uint32_t EMAC_MDIO_BASE        = 0x01E24000;
    static const uint32_t EMAC_MDIO_SIZE        = 0x00001000;

  private:
    Board(const Board&);            // GNI
    Board& operator=(const Board&); // GNI
  };
  
} // TI_AM1707
} // simsoc

#endif // !LIBSIMSOC_TI_AM1707_HPP__
