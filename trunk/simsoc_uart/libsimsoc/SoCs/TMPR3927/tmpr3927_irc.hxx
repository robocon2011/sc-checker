//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#if !defined(LIBSIMSOC_TMPR3927_IRC_HPP__) || defined(LIBSIMSOC_TMPR3927_IRC_HXX__)
# error "DO NOT INCLUDE THIS FILE DIRECTLY"
#endif

#define LIBSIMSOC_TMPR3927_IRC_HXX__

#include "libsimsoc/bitwise_operator.hpp"
#include <cstring>

namespace simsoc  {
  namespace TMPR3927 {

    // ------------------------------------------------------------------
    inline IRC_R_IRCER::IRC_R_IRCER()
      :m_enabled(false)
    {}
    inline void IRC_R_IRCER::set(uint32_t value) {
      m_enabled = value & 0x1;
    }

    inline uint32_t IRC_R_IRCER::get() const {
      return m_enabled;
    }

    inline bool IRC_R_IRCER::enabled() const {
      return m_enabled ? 0x1 : 0x0;
    }

    // ------------------------------------------------------------------
    inline IRC_R_IRCR0::IRC_R_IRCR0()
      :m_value(0)
    {}

    inline uint32_t IRC_R_IRCR0::get() const {
      return m_value;
    }

    inline void IRC_R_IRCR0::set_mode(uint32_t value) {
      m_value = value & 0xffff;
    }

    // ------------------------------------------------------------------
    inline IRC_R_IRILR3::IRC_R_IRILR3()
      :m_value(0)
    {}

    inline uint32_t IRC_R_IRILR3::get() const {
      return m_value;
    }

    inline void IRC_R_IRILR3::set(uint32_t value) {
      m_value = value & 0x707;
    }

    // ------------------------------------------------------------------
    inline  IRC_R_IRIMR::IRC_R_IRIMR()
      :m_value(0)
    {}

    inline uint32_t IRC_R_IRIMR::get() const {
      return m_value;
    }

    inline void IRC_R_IRIMR::set(uint32_t value) {
      m_value = value & 0x7;
    }

    // ------------------------------------------------------------------
    inline IRC_R_IRSCR::IRC_R_IRSCR()
      :m_value(0)
    {}

    inline uint32_t IRC_R_IRSCR::get() const {
      return this->m_value;
    }

    inline void IRC_R_IRSCR::set(uint32_t value) {
      m_value = value & 0x10f;
    }

    // ------------------------------------------------------------------
    inline IRC_R_IRSSR::IRC_R_IRSSR()
      :m_value(0)
    {}

    inline void IRC_R_IRSSR::set(uint32_t value) {
      m_value = value & 0xff;
    }

    inline uint32_t IRC_R_IRSSR::get() const {
      return m_value;
    }

    // ------------------------------------------------------------------
    inline IRC_R_IRCSR::IRC_R_IRCSR()
      :m_value(0)
    {}

    inline uint32_t IRC_R_IRCSR::get() const {
      return this->m_value;
    }

    inline void IRC_R_IRCSR::set(uint32_t value) {
      m_value = value & 0x1071f;
    }

  }
}
