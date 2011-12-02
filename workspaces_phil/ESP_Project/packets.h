#ifndef PACKETS_H
#define PACKETS_

#include <systemc.h>
#include <scv.h>

#include <string>
using std::string;

#define INSTANCES_FULLADDER 8

struct packet_fulladdr{
  int sw_a;
  int sw_b;
  sc_logic rtl_a[INSTANCES_FULLADDER];
  sc_logic rtl_b[INSTANCES_FULLADDER];

  packet_fulladdr()
  : sw_a(-1)
  , sw_b(-1)
  {
    for (unsigned i=0;i<INSTANCES_FULLADDER;i++){
        rtl_a[i] = 0;
        rtl_b[i] = 0;
    }
  }

  packet_fulladdr(
      int _sw_a,
      int _sw_b,
      sc_logic _rtl_a[INSTANCES_FULLADDER],
      sc_logic _rtl_b[INSTANCES_FULLADDER]
      )
  : sw_a (_sw_a)
  , sw_b (_sw_b)

  {}

  packet_fulladdr& operator =
      (const packet_fulladdr& rhs){
    sw_a = rhs.sw_a;
    sw_b = rhs.sw_b;
   for(unsigned i=0;i<INSTANCES_FULLADDER;i++){
    rtl_a[i] = rhs.rtl_a[i];
    rtl_b[i] = rhs.rtl_b[i];
    }
    return *this;
  }

  bool operator== (const packet_fulladdr& rhs)
      const{
    int a = 0;
    a &= (sw_a == rhs.sw_a) ? 1 : 0;
    a &= (sw_b == rhs.sw_a) ? 1 : 0;
    for(unsigned i=0; i<INSTANCES_FULLADDER;i++){
        a &= (rtl_a[i] == rhs.rtl_a[i]) ? 1 : 0;
    }
    return(a);
  }

};

// Stream operator to output a PCIX transaction packet to terminal
ostream& operator<<(ostream& file, const packet_fulladdr& trans);

// Trace a PCIX transaction packet in case it is used in an sc_signal
void sc_trace(sc_trace_file* tf, const packet_fulladdr& trans, const string& nm);
#endif
