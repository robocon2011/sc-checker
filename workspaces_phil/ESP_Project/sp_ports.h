#ifndef SP_PORTS_H
#define SP_PORTS_
#ifndef PACKETS_
  #include "packets.h"
#endif

class fulladr_port
  : public sc_port<sc_signal_inout_if<int>
    ,2
    ,SC_ONE_OR_MORE_BOUND
    > {
public:
    typedef sc_signal_inout_if<int> if_type;

    sc_event_finder& fa_value_changed_event() const{
      return *new sc_event_finder_t <if_type> (
          *this,
          &if_type::value_changed_event);
    }
  };

/******************************************************************/

class fa_rtl_port
  : public sc_port<sc_signal_inout_if<sc_logic>
    ,INSTANCES_FULLADDER
    ,SC_ONE_OR_MORE_BOUND
    > {
public:
    typedef sc_signal_inout_if<sc_logic> if_type;

    sc_event_finder& fa_value_changed_event() const{
      return *new sc_event_finder_t <if_type> (
          *this,
          &if_type::value_changed_event);
    }
  };
#endif
