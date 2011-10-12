//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//


#if !defined (LIBSIMSOC_TMPR3927_HPP__)
# define LIBSIMSOC_TMPR3927_HPP__

# include "libsimsoc/module.hpp"
# include "libsimsoc/components/bus.hpp"
# include "libsimsoc/components/memory.hpp"
# include "libsimsoc/processors/mips/mips_processor.hpp"
# include "libsimsoc/SoCs/TMPR3927/tmpr3927_irc.hpp"
//# include "libsimsoc/components/ti_am1x_uart.hpp"
#include "libsimsoc/components/uart_16550.hpp"
# include "libsimsoc/components/rw_stub.hpp"


namespace simsoc{
namespace TMPR3927{

class Board: public Module{
public:
  Board(sc_core::sc_module_name name);
  ~Board(){}

  // SDRAM Controller
  static const uint32_t SDRAMC_BASE=0xFFFE8000;
  static const uint32_t SDRAMC_SIZE=0x00000034;

  static const uint32_t MEMORY_BASE=0;
  static const uint32_t MEMORY_SIZE=0x80000000;
 
  // Serial I/O
  static const uint32_t UART0_BASE=0x1F00900; 
  static const uint32_t UART_SIZE=0x00000A00;

  // IRQ
  static const uint32_t IRQ_UART0=6;
  //static const uint32_t IRQ_UART1=7;

  // IRC
  static const uint32_t IRC_BASE=0xFFFEC000;
  static const uint32_t IRC_SIZE=0x000000B0;

  Processor* get_proc(){ return m_processor; }

protected:
  MIPS_Processor<BUS32> *m_processor;
  Bus m_bus;
  Memory m_dram;
  //Uart16550 m_uart0, m_uart1;
  IRC m_irc;
  
};

} // TMP3927
} // simsoc

# endif  // endif !LIBSIMSOC_TMPR3927_HPP__
