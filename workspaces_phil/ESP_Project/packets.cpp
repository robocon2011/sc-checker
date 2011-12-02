#include <systemc.h>
#include "packets.h"
#include <iomanip>
#include <string>
using std::setw;
using std::setfill;
using std::uppercase;

// Print a PCIX transaction packet out to a stream (usually just the terminal
// window), in a nice-looking format
ostream& operator<<(ostream& os, const packet_fulladdr& trans)
{
  int i = 0;
  string a = "",
         b = "";

  for(i=0; i<INSTANCES_FULLADDER;i++){
      if(trans.rtl_a[i] == '1') a+="1";
      else a+="0";

      if(trans.rtl_b[i] == '1') b+="1";
      else b+="0";
  }

  os << "{" << endl
     << "Integer  A: " << trans.sw_a  << ", \n"
     << "Integer  B: " << trans.sw_b  << ", \n"
     << "SC_LOGIC A: " << a << ", \n"
     << "SC_LOGIC B: " << b << " "
     << endl
     << "}\n";
  return os;
}//end operator<<

// trace function, only required if actually used
void sc_trace(sc_trace_file* tf, const packet_fulladdr& trans, const string& nm)
{
  int i = 0;

  sc_trace(tf, trans.sw_a,      nm + ".sw_a" );
  sc_trace(tf, trans.sw_b,      nm + ".sw_b" );
  for(i=0;i<INSTANCES_FULLADDER;i++){
  sc_trace(tf, trans.rtl_a[i],  nm + ".rtl_a[" + char(i) + "]");
  sc_trace(tf, trans.rtl_b[i],  nm + ".rtl_b[" + char(i) + "]");
  }
}//end sc_trace
