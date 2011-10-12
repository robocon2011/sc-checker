//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/SoCs/TMPR3927/tmpr3927_irc.hpp"
#include "libsimsoc/processors/mips/mips_processor.hpp"

namespace simsoc {
  namespace TMPR3927 {

    // ------------------------------------------------------------------
    enum ac_action {
      AC_IRCER,
      AC_IRCR0,
      AC_IRILR3,
      AC_IRIMR,
      AC_IRSCR,
      AC_IRSSR,
      AC_IRCSR,
    };

    static enum ac_action AC_INVALID = (enum ac_action) -1;

    // -----------------------------------------------------------------
#define WR_RECOMPUTE   IRC::WR_RECOMPUTE

    IRC::writer_infos_t IRC::writers[] = {
      { &IRC::_write_IRCER ,WR_RECOMPUTE}, // AC_IRCER
      { &IRC::_write_IRCR0 ,WR_RECOMPUTE}, // AC_IRCR0
      { &IRC::_write_IRILR3,WR_RECOMPUTE}, // AC_IRILR3
      { &IRC::_write_IRIMR ,WR_RECOMPUTE}, // AC_IRIMR
      { &IRC::_write_IRSCR ,WR_RECOMPUTE}, // AC_IRSCR
      { &IRC::_write_IRSSR ,WR_RECOMPUTE}, // AC_IRSSR
      { &IRC::_write_IRCSR ,WR_RECOMPUTE}, // AC_IRCSR
    };

    // ------------------------------------------------------------------
    class address_class_t {
    public:
      uint32_t  rawaddress;
      ac_action action;
      size_t    index;

    public:
      static address_class_t classify(uint32_t address);

    public:
      address_class_t(uint32_t address)
        :rawaddress(address)
        ,action    (AC_INVALID)
        ,index     (0)
      {}

      address_class_t(uint32_t  address,
                      ac_action action)
        :rawaddress(address)
        ,action    (action)
        ,index     (index)
      {}

    public:
      static const uint32_t A_IRCER =  0x00;
      static const uint32_t A_IRCR0 =  0x04;
      static const uint32_t A_IRILR3 = 0x1c;
      static const uint32_t A_IRIMR =  0x40;
      static const uint32_t A_IRSCR =  0x60;
      static const uint32_t A_IRSSR =  0x80;
      static const uint32_t A_IRCSR =  0xa0;

    };

    // ------------------------------------------------------------------
    address_class_t address_class_t::classify(uint32_t address) {
      const uint32_t rawaddress = address;

#define INVALID         (address_class_t(rawaddress))
#define ADDRESS(C)      (address_class_t(rawaddress, C))

      if (address >> 16 || (address & 0x3))
        return INVALID;

      switch (address) {
      case A_IRCER  : return ADDRESS(AC_IRCER);
      case A_IRCR0  : return ADDRESS(AC_IRCR0);
      case A_IRILR3 : return ADDRESS(AC_IRILR3);
      case A_IRIMR  : return ADDRESS(AC_IRIMR);
      case A_IRSCR  : return ADDRESS(AC_IRSCR);
      case A_IRSSR  : return ADDRESS(AC_IRSSR);
      case A_IRCSR  : return ADDRESS(AC_IRCSR);
      }

      return INVALID;

#undef INVALID
#undef ADDRESS
    };

    // ------------------------------------------------------------------
    IRC::IRC(sc_core::sc_module_name name)
      :TMPR3927_core<IRC>(name,this)
      ,m_in_ports    ()
      ,m_R_IRCER     ()
      ,m_R_IRCR0     ()
      ,m_R_IRILR3    ()
      ,m_R_IRIMR     ()
      ,m_R_IRSCR     ()
      ,m_R_IRSSR     ()
      ,m_R_IRCSR     ()
    {
      m_in_ports.reserve(NINTERRUPTS);
      for (unsigned int i = 0; i < NINTERRUPTS; ++i)
        m_in_ports.push_back(new signal_t(static_cast <SignalMultiTarget<bool>*>(this), i, true));
    }

    IRC::~IRC() {
      for (size_t i = 0; i < m_in_ports.size(); ++i)
        delete m_in_ports[i];
    }

    // ------------------------------------------------------------------
    void IRC::connect(MIPS_Processor<BUS32> &processor) {
      this->m_hard_port0(processor.hard_port0);
      this->m_hard_port1(processor.hard_port1);
      this->m_hard_port2(processor.hard_port2);
      this->m_hard_port3(processor.hard_port3);
      this->m_hard_port4(processor.hard_port4);
    }

    IRC::signal_t& IRC::get_irq_port(unsigned port) {
      return *this->m_in_ports[port];
    }
    // ------------------------------------------------------------------
    uint32_t IRC::read_word(uint32_t address) {
      debug()
        << "reading at address " << std::hex << address
        << std::endl;

      if ((address & 0x3)) {
        warning() << "address not properly aligned" << std::endl;
        return 0;
      }

      const address_class_t ac = address_class_t::classify(address);

      if (ac.action == AC_INVALID) {
        warning()
          << "invalid address: "
          << std::hex << address << std::endl;
        return 0;
      }

      switch (ac.action) {
      case AC_IRCER : return m_R_IRCER.get();
      case AC_IRCR0 : return m_R_IRCR0.get();
      case AC_IRILR3: return m_R_IRILR3.get();
      case AC_IRIMR : return m_R_IRIMR.get();
      case AC_IRSCR : return m_R_IRSCR.get();
      case AC_IRSSR : return m_R_IRSSR.get();
      case AC_IRCSR : return m_R_IRCSR.get();
      }

      abort();
    }

    // ------------------------------------------------------------------
    void IRC::write_word(uint32_t address, uint32_t data) {
      debug()
        << "writing "     << std::hex << data
        << " at address " << std::hex << address
        << std::endl;

      const address_class_t ac = address_class_t::classify(address);

      if (ac.action == AC_INVALID) {
        warning() << "invalid address: "
                  << std::hex << address << std::endl;
        return ;
      }

      const writer_infos_t &writer = this->writers[ac.action];

      (this->*writer.wr_callback)(ac, data);
      if ((writer.flags & WR_RECOMPUTE))
        this->_compute();
    }

    // ------------------------------------------------------------------
    void IRC::_write_IRCER(const address_class_t &ac, uint32_t data) {
      m_R_IRCER.set(data);
    }

    void IRC::_write_IRCR0(const address_class_t &ac, uint32_t data) {
      m_R_IRCR0.set_mode(data);
    }

    void IRC::_write_IRILR3(const address_class_t &ac, uint32_t data){
      m_R_IRILR3.set(data);
    }

    void IRC::_write_IRIMR(const address_class_t &ac, uint32_t data) {
      m_R_IRIMR.set(data);
    }

    void IRC::_write_IRSCR(const address_class_t &ac, uint32_t data) {
      m_R_IRSCR.set(data);
    }

    void IRC::_write_IRSSR(const address_class_t &ac, uint32_t data) {
      m_R_IRSSR.set(data);
    }

    void IRC::_write_IRCSR(const address_class_t &ac, uint32_t data) {
      m_R_IRCSR.set(data);
    }

    // ------------------------------------------------------------------
    void IRC::_compute() {
      m_hard_port0
        = m_R_IRCER.enabled();
      m_hard_port1
        = m_R_IRCER.enabled();
      m_hard_port2
        = m_R_IRCER.enabled();
      m_hard_port3
        = m_R_IRCER.enabled();
      m_hard_port4
        = m_R_IRCER.enabled();
    }
    // ------------------------------------------------------------------
    void IRC::pulse(size_t line) {
      debug() << "PULSE: " << line << std::endl;
      //m_R_interrupts.set_rawpending(line);
      //this->_compute();
    }
  } // namespace TMPR3927
} // namespace simsoc
