//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TMPR3927_IRC_HPP__)
# define LIBSIMSOC_TMPR3927_IRC_HPP__

# include "libsimsoc/interfaces/tlm.hpp"
# include "libsimsoc/interfaces/tlm_signal.hpp"
# include "libsimsoc/module.hpp"
# include "libsimsoc/bitwise_operator.hpp"
# include "libsimsoc/processors/mips/mips_processor.hpp"
# include "libsimsoc/SoCs/TMPR3927/tmpr3927_core.hpp"
#include "libsimsoc/components/debug_console.hpp"

namespace simsoc {
  namespace TMPR3927 {
    // ------------------------------------------------------------------
    class IRC_R_IRCER {
    public:
      IRC_R_IRCER();

    public:
      uint32_t get() const;
      void set(uint32_t value);

      bool enabled() const;

    private:
      bool m_enabled;

    private:
      IRC_R_IRCER(const IRC_R_IRCER&);
      IRC_R_IRCER& operator=(const IRC_R_IRCER&);
    };
    // ------------------------------------------------------------------
    class IRC_R_IRCR0 {
    public:
      IRC_R_IRCR0();
      uint32_t get() const;
      void set_mode(uint32_t value);

    private:
      uint32_t m_value;

    private:
      IRC_R_IRCR0(const  IRC_R_IRCR0&);
      IRC_R_IRCR0& operator=(const IRC_R_IRCR0&);
    };
    // ------------------------------------------------------------------
    class  IRC_R_IRILR3 {
    public:
      IRC_R_IRILR3();
      uint32_t get() const;
      void set(uint32_t value);

    private:
      uint32_t m_value;

    private:
      IRC_R_IRILR3(const IRC_R_IRILR3&);
      IRC_R_IRILR3& operator=(const IRC_R_IRILR3&);
    };
    // ------------------------------------------------------------------
    class IRC_R_IRIMR {
    public:
      IRC_R_IRIMR();
      uint32_t get() const;
      void set(uint32_t value);

    private:
      uint32_t m_value;

    private:
      IRC_R_IRIMR(const IRC_R_IRIMR&);
      IRC_R_IRIMR& operator=(const IRC_R_IRIMR&);
    };
    // ------------------------------------------------------------------
    class IRC_R_IRSCR {
    public:
      IRC_R_IRSCR();

    public:
      uint32_t get() const;
      void set(uint32_t value);

    private:
      uint32_t m_value;

    private:
      IRC_R_IRSCR(const  IRC_R_IRSCR&);
      IRC_R_IRSCR operator=(const IRC_R_IRSCR&);
    };
    // ------------------------------------------------------------------
    class IRC_R_IRSSR {
    public:
      IRC_R_IRSSR();

    public:
      void set(uint32_t value);
      uint32_t get() const;

    private:
      uint32_t m_value;
    private:
      IRC_R_IRSSR(const  IRC_R_IRSSR&);
      IRC_R_IRSSR& operator=(const IRC_R_IRSSR&);
    };
    // ------------------------------------------------------------------

    class IRC_R_IRCSR {
    public:
      IRC_R_IRCSR();

    public:
      uint32_t get() const;
      void set(uint32_t value);

    private:
      uint32_t m_value;

    private:
      IRC_R_IRCSR(const  IRC_R_IRCSR&);
      IRC_R_IRCSR operator=(const IRC_R_IRCSR&);
    };

    // ------------------------------------------------------------------
    class address_class_t;

    // -----------------------------------------------------------------
    class IRC
      :public TMPR3927_core<IRC>
      ,public SignalMultiTarget<bool>
    {
    public:
      static const uint32_t NINTERRUPTS = 2;

    public:
      IRC(sc_core::sc_module_name name);
      virtual ~IRC();

    public:
      void pulse(size_t line);
      void signal(bool,size_t) {}

    protected:
      void _compute();

    protected:
      uint32_t read_word(uint32_t address);
      void write_word(uint32_t address, uint32_t value);

    protected:
      typedef void (IRC::*writer_t)(const address_class_t &ac, uint32_t data);

    struct writer_infos_t {
      writer_t wr_callback;
      uint32_t flags;
    };

    static const uint32_t WR_RECOMPUTE   = (1 << 0);

    static writer_infos_t writers[];

      void _write_IRCER  (const address_class_t &ac, uint32_t data);
      void _write_IRCR0  (const address_class_t &ac, uint32_t data);
      void _write_IRILR3 (const address_class_t &ac, uint32_t data);
      void _write_IRIMR  (const address_class_t &ac, uint32_t data);
      void _write_IRSCR  (const address_class_t &ac, uint32_t data);
      void _write_IRSSR  (const address_class_t &ac, uint32_t data);
      void _write_IRCSR  (const address_class_t &ac, uint32_t data);

    public:
      typedef SignalMultiTargetPort<bool> signal_t;

    public:
      void connect(MIPS_Processor<BUS32> &processor);
      signal_t& get_irq_port(unsigned irq);

    protected:
      std::vector<signal_t*>     m_in_ports;
      SignalInitiatorPort<bool>  m_hard_port0;
      SignalInitiatorPort<bool>  m_hard_port1;
      SignalInitiatorPort<bool>  m_hard_port2;
      SignalInitiatorPort<bool>  m_hard_port3;
      SignalInitiatorPort<bool>  m_hard_port4;

    private:
      IRC_R_IRCER   m_R_IRCER;
      IRC_R_IRCR0   m_R_IRCR0;
      IRC_R_IRILR3  m_R_IRILR3;
      IRC_R_IRIMR   m_R_IRIMR;
      IRC_R_IRSCR   m_R_IRSCR;
      IRC_R_IRSSR   m_R_IRSSR;
      IRC_R_IRCSR   m_R_IRCSR;
    };
  }
}

# include "libsimsoc/SoCs/TMPR3927/tmpr3927_irc.hxx"


#endif // TX39_IRC_HPP
