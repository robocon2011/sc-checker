//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined (LIBSIMSOC_TMPR3927_CORE_HPP__)
# define LIBSIMSOC_TMPR3927_CORE_HPP__

# include <inttypes.h>
# include <tlm_utils/simple_target_socket.h>
# include <tlm_utils/simple_initiator_socket.h>
# include "libsimsoc/module.hpp"

# include <systemc>

namespace simsoc {
  namespace TMPR3927 {

    template < class T >
    class TMPR3927_core : public Module {
    public:
      TMPR3927_core(sc_core::sc_module_name name, T *myself);
      virtual ~TMPR3927_core();

    public:
      typedef tlm_utils::simple_target_socket<T> inport_t;

      inport_t& get_rw_port() { return m_inport; }

    protected:                    // TLM protocol
      void custom_b_transport(tlm::tlm_generic_payload &payload,
                              sc_core::sc_time &delay_time);

    protected:
      virtual uint32_t read_word (uint32_t address)                 = 0;
      virtual void     write_word(uint32_t address, uint32_t value) = 0;

    protected:
      inport_t m_inport;

    private:
      TMPR3927_core(const TMPR3927_core &);            // GNI
      TMPR3927_core& operator=(const TMPR3927_core &); // GNI
    };

    // ------------------------------------------------------------------
    template < class T >
    class TMPR3927_oport {
    public:
      TMPR3927_oport(T *myself);
      virtual ~TMPR3927_oport();

    protected:
      uint8_t  _rd_8 (uint32_t address);
      uint16_t _rd_16(uint32_t address);
      uint32_t _rd_32(uint32_t address);

      void _wr_8 (uint32_t address, uint8_t  input);
      void _wr_16(uint32_t address, uint16_t input);
      void _wr_32(uint32_t address, uint32_t input);

      void _rd(uint8_t *dst, uint32_t addr, uint32_t size);
      void _wr(const uint8_t *dst, uint32_t addr, uint32_t size);

    public:
      typedef tlm_utils::simple_initiator_socket<T> outport_t;

      outport_t& outport() { return m_outport; }

    protected:
      outport_t        m_outport;
      sc_core::sc_time m_delay;

    private:
      TMPR3927_oport(const TMPR3927_oport&);            // GNI
      TMPR3927_oport& operator=(const TMPR3927_oport&); // GNI

    };
 // ------------------------------------------------------------------
    namespace signals {
    class SignalTarget: public sc_core::sc_interface  {
    public:
      SignalTarget() {}
      virtual ~SignalTarget() {}

    public:
      virtual void pulse() = 0;
    };

    class SignalMultiTarget {
    public:
      SignalMultiTarget() {}
      virtual ~SignalMultiTarget() {}

    public:
      virtual void pulse(size_t id) = 0;
    };

    class SignalInitiatorPort;

    // template<class T>
    class SignalMultiTargetPort: public SignalTarget {
      friend class SignalInitiatorPort;

    public:
      SignalMultiTargetPort(SignalMultiTarget &host, size_t id)
        :m_id  (id)
        ,m_host(host)
      {}

      virtual ~SignalMultiTargetPort() {}

    public:
      size_t id() const { return m_id; }

    protected:
      void pulse() { m_host.pulse(m_id); }

    protected:
      const size_t       m_id;
      SignalMultiTarget &m_host;
    };

    class SignalInitiatorPort_Base {
    public:
      SignalInitiatorPort_Base() {}
      virtual ~SignalInitiatorPort_Base() {}

    public:
      void operator()(SignalTarget &port) {
        m_ports(port);
      }

    protected:
      void pulseall() {
        for (ssize_t i = 0; i < m_ports.size(); ++i)
          m_ports[i]->pulse();
      }

    protected:
      typedef
        sc_core::sc_port<SignalTarget, 0, sc_core::SC_ZERO_OR_MORE_BOUND>
        port_t;

      port_t m_ports;
    };

    class SignalInitiatorPort_Level
      : public SignalInitiatorPort_Base
    {
    public:
      SignalInitiatorPort_Level()
        :m_level(false)
      {}

      void operator=(bool level) {
        if (level != m_level) {
          m_level = level;
          if (level)
            this->pulseall();
        }
      }

    protected:
      bool m_level;
    };

    class SignalInitiatorPort_Pulse
      : public SignalInitiatorPort_Base
    {
    public:
      void pulse() { this->pulseall(); }
    };


    } // namespace signals*/
  }// namespace TMPR3927
} //namespace simsoc

# include "libsimsoc/SoCs/TMPR3927/tmpr3927_core.hxx"

#endif // !LIBSIMSOC_TMPR3927_CORE_HPP__
