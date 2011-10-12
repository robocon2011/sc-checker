//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "tmpr3927.hpp"

namespace simsoc{
namespace TMPR3927{

  Board::Board(sc_core::sc_module_name name)
    :Module(name)
    ,m_processor(NULL)
    ,m_bus("BUS")
    ,m_dram("DRAM",MEMORY_SIZE)
     //,m_uart0("UART0")
     //,m_uart1("UART1")
    ,m_irc("IRC")
    {
    
    m_processor=new MIPS_Processor<BUS32>("MIPS32");
    m_processor->set_endian_little();
    m_processor->cp0.status().bev=0;
    m_processor->cp0.status().ksu=kernel;
    m_processor->cp0.status().ie=0;
    m_processor->cp0.status().exl=0;
    //m_processor->cp0.regs[CP0_PRID]=0;
    //// bind the cpu to the bus...
    m_processor->get_rw_port()(m_bus.target_sockets);
    // and to the IRC
    m_irc.connect(static_cast<MIPS_Processor<BUS32>&>(*m_processor));
    

    // Set IRQs ports
    // -> SEGFAULT HERE <-
    //m_uart0.it_signal(m_irc.get_irq_port(IRQ_UART0));
    //m_uart1.it_signal(m_irc.get_irq_port(IRQ_UART1));
    // then ask for DCE binding

    // bind the bus
    // m_bus.bind_target(m_uart0.rw_port, UART0_BASE,  UART_SIZE);
    //m_bus.bind_target(m_uart1.rw_port, UART1_BASE, UART_SIZE);
    m_bus.bind_target(m_dram.rw_socket, MEMORY_BASE, MEMORY_SIZE);
    m_bus.bind_target(m_irc.get_rw_port(),IRC_BASE, IRC_SIZE);
   
    // Done
    debug() << "Initialization done" << std::endl;
    }

}
}
