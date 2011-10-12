//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_DEBUGGER_HPP
# define PPC_DEBUGGER_HPP

# include "libsimsoc/interfaces/gdb.hpp"

# include <inttypes.h>
# include <map>

namespace simsoc {

  class PPC_Processor;

  class PPC_Debugger: public DebugInterface {
  public:
    /* From gdb-7.0.1/gdb/gdbserver/linux-ppc-low.c:
       Correct in either endianness.
       This instruction is "twge r2, r2", which GDB uses as a software
       breakpoint.  */
    static const uint32_t TRAP_EABI_INSTRUCTION = 0x7d821008;

  public:
    PPC_Debugger(PPC_Processor &processor);

  public:                       // DebugInterface
    virtual bool add_breakpoint(uint64_t address, uint64_t length);
    virtual bool del_breakpoint(uint64_t address, uint64_t length);

    virtual bool readregs(bytes_t &result);
    virtual bool readreg(size_t reg_num,bytes_t &result);
    virtual size_t read(uint64_t address, size_t length, bytes_t &result);

    virtual void enable_traps ();
    virtual void disable_traps();

  protected:
    typedef std::map<uint32_t, uint32_t> traps_t;

    PPC_Processor &m_proc;
    traps_t        m_traps;
  };

}

#endif // !PPC_DEBUGGER_HPP
