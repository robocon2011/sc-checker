//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef MIPS_DEBUGGER_HPP
# define MIPS_DEBUGGER_HPP

# include "libsimsoc/interfaces/gdb.hpp"
# include <inttypes.h>
# include <map>

namespace simsoc {
  template <typename word_t>
  class MIPS_Processor;

  template <typename word_t>
  class MIPS_Debugger: public DebugInterface {
  public:
    // only for little endian -> FIXME
    static const uint32_t TRAP_O32ABI_INSTRUCTION = 13;

  public:

    MIPS_Debugger(MIPS_Processor<word_t> &processor);

  public:                       // DebugInterface
    virtual bool add_breakpoint(uint64_t address, uint64_t length);
    virtual bool del_breakpoint(uint64_t address, uint64_t length);

    virtual bool readregs(bytes_t &result);
    virtual bool readreg(size_t reg_num, bytes_t &result);
    virtual size_t read(uint64_t address, size_t length, bytes_t &result);

    virtual void enable_traps ();
    virtual void disable_traps();

  protected:
    typedef std::map<uint32_t, uint32_t> traps_t;

    MIPS_Processor<word_t> &m_proc;
    traps_t        m_traps;
  };

}

#endif // !MIPS_DEBUGGER_HPP
