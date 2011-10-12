//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/module.hpp"
#include "libsimsoc/SoCs/TI_AM1707/TI_AM1707.hpp"

#include "libsimsoc/components/ti_am1x_mdio.hpp"
#include "libsimsoc/components/ti_am1x_emac_module.hpp"
#include "libsimsoc/components/ti_am1x_emac_control.hpp"

#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/processors/arm_v6/arm_v6_processor.hpp"
#include "libsimsoc/processors/iss.hpp"
#include <signal.h>

namespace simsoc    {
namespace TI_AM1707 {

  ParameterBool arm_v6("ARM processor", "-v6",
                       "Use the ARMv6 ISS based on simlight2");

  Processor *proc = NULL;

  // ------------------------------------------------------------------
  Board::stub_infos_t Board::stubs[] = {
    { "PRUSS", 0x00000000, 0x00001000 },
    { "GPIO" , 0x01E26000, 0x00001000 },
    { "PLLC" , 0x01C11000, 0x00001000 },
    { "EDMA" , 0x01C00000, 0x00008000 },
    { NULL   , 0x00000000, 0x00000000 },
  };

  // ------------------------------------------------------------------
  void Board::set_ether_transport(IEtherTransport *transport) {
    m_emac.emac_module().set_transport(transport);
  }

  // ------------------------------------------------------------------
  Board::Board(sc_core::sc_module_name name)
    :Module     (name)
    ,m_bus      ("BUS")
    ,m_dram     ("DRAM", MEMORY_SIZE)
    ,m_processor(NULL)
    ,m_uart0    ("UART0")
    ,m_uart1    ("UART1")
    ,m_uart2    ("UART2")
    ,m_syscfg   ("SYSCFG")
    ,m_psc0     ("PSC0", 16)
    ,m_psc1     ("PSC1", 32)
    ,m_irqc     ("IRQC")
    ,m_timer64_0("TIMER64P0")
    ,m_timer64_1("TIMER64P1")
    ,m_rtc      ("RTC")
    ,m_emac     ("EMAC")
    ,m_emac_mem ("EMAC_MEM", EMAC_RAM_SIZE)
  {
    using namespace TI_AM1x;

    if (arm_v6.get()) {
      m_processor = new ARMv6_Processor("ARM");
    } else {
      m_processor = new ARM_Processor("ARM");
    }
    proc = m_processor;

    TI_AM1x::EMAC_MOD     &emac_mod  = m_emac.emac_module();
    TI_AM1x::EMAC_CONTROL &emac_ctrl = m_emac.emac_control();
    TI_AM1x::MDIO         &mdio      = m_emac.mdio();

    // bind the cpu
    m_processor->get_rw_port()(m_bus.target_sockets);

    // bind the real time controller
    m_rtc.it_signal(m_irqc.get_irq_port(RTC_IT));

    // Connect IRQ controller to processor
    if (arm_v6.get())
      m_irqc.connect(static_cast<ARMv6_Processor&>(*m_processor));
    else
      m_irqc.connect(static_cast<ARM_Processor&>(*m_processor));

    // Set IRQs ports
    m_uart0.get_it_signal()(m_irqc.get_irq_port(IRQ_UART0));
    m_uart1.get_it_signal()(m_irqc.get_irq_port(IRQ_UART1));
    m_uart2.get_it_signal()(m_irqc.get_irq_port(IRQ_UART2));

    m_timer64_0.get_tim_signal(Timer64::TM_LO)(m_irqc.get_irq_port(IRQ_TIMER64P0_12));
    m_timer64_0.get_tim_signal(Timer64::TM_HI)(m_irqc.get_irq_port(IRQ_TIMER64P0_34));
    m_timer64_1.get_tim_signal(Timer64::TM_LO)(m_irqc.get_irq_port(IRQ_TIMER64P1_12));
    m_timer64_1.get_tim_signal(Timer64::TM_HI)(m_irqc.get_irq_port(IRQ_TIMER64P1_34));

    for (size_t i = 0; i < TI_AM1x::Timer64::N_COMPARE_REGS; ++i) {
      m_timer64_0.get_cmp_signal(i)(m_irqc.get_irq_port(i+IRQ_TIMER64P0_CMP));
      m_timer64_1.get_cmp_signal(i)(m_irqc.get_irq_port(i+IRQ_TIMER64P1_CMP));
    }

    emac_ctrl.get_signal(0, TI_AM1x::IT_RXTHRESH)(m_irqc.get_irq_port(IRQ_EMAC_C0RXTHRESH));
    emac_ctrl.get_signal(0, TI_AM1x::IT_RX      )(m_irqc.get_irq_port(IRQ_EMAC_C0RX      ));
    emac_ctrl.get_signal(0, TI_AM1x::IT_TX      )(m_irqc.get_irq_port(IRQ_EMAC_C0TX      ));
    emac_ctrl.get_signal(0, TI_AM1x::IT_MISC    )(m_irqc.get_irq_port(IRQ_EMAC_C0MISC    ));

    emac_ctrl.get_signal(1, TI_AM1x::IT_RXTHRESH)(m_irqc.get_irq_port(IRQ_EMAC_C1RXTHRESH));
    emac_ctrl.get_signal(1, TI_AM1x::IT_RX      )(m_irqc.get_irq_port(IRQ_EMAC_C1RX      ));
    emac_ctrl.get_signal(1, TI_AM1x::IT_TX      )(m_irqc.get_irq_port(IRQ_EMAC_C1TX      ));
    emac_ctrl.get_signal(1, TI_AM1x::IT_MISC    )(m_irqc.get_irq_port(IRQ_EMAC_C1MISC    ));

    // Create stubs (and bind them to the bus)
    for (const stub_infos_t *st = stubs; st->name; ++st) {
      RW_Stub *stub = new RW_Stub(st->name, "not enabled");
      m_stubs.push_back(stub);
      m_bus.bind_target(stub->rw_port, st->base, st->size);
    }

    // bind the bus
    m_bus.bind_target(m_uart0.get_rw_port()    , UART0_BASE          , UART_SIZE     );
    m_bus.bind_target(m_uart1.get_rw_port()    , UART1_BASE          , UART_SIZE     );
    m_bus.bind_target(m_uart2.get_rw_port()    , UART2_BASE          , UART_SIZE     );
    m_bus.bind_target(m_dram.rw_socket         , MEMORY_BASE         , MEMORY_SIZE   );
    m_bus.bind_target(m_rtc.get_rw_port()      , RTC_BASE            , RTC_SIZE      );
    m_bus.bind_target(m_irqc.get_rw_port()     , AINTC_BASE          , AINTC::SIZE   );
    m_bus.bind_target(m_syscfg.get_rw_port()   , SYSCFG_BASE         , SYSCFG_SIZE   );
    m_bus.bind_target(m_psc0.get_rw_port()     , PSC0_BASE           , PSC0_SIZE     );
    m_bus.bind_target(m_psc1.get_rw_port()     , PSC1_BASE           , PSC1_SIZE     );
    m_bus.bind_target(m_timer64_0.get_rw_port(), TIMER64P0_BASE      , TIMER64P0_SIZE);
    m_bus.bind_target(m_timer64_1.get_rw_port(), TIMER64P1_BASE      , TIMER64P1_SIZE);
    m_bus.bind_target(mdio.get_rw_port()       , EMAC_MDIO_BASE      , EMAC_MDIO_SIZE);
    m_bus.bind_target(emac_mod.get_rw_port()   , EMAC_MOD_BASE       , EMAC_MOD_SIZE );
    m_bus.bind_target(emac_ctrl.get_rw_port()  , EMAC_CTRL_BASE      , EMAC_CTRL_SIZE);
    m_bus.bind_target(m_emac_mem.rw_socket     , EMAC_RAM_BASE       , EMAC_RAM_SIZE );

    emac_mod.outport()(m_bus.target_sockets);

    // Done
    debug() << "Initialization done" << std::endl;
  }

  // ------------------------------------------------------------------
  Board::~Board() {
    stubs_t::iterator it;

    delete m_processor;

    for (it = m_stubs.begin(); it != m_stubs.end(); ++it)
      delete *it;
  }

} // TI_AM1707
} // simsoc
