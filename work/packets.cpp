#include <systemc.h>
#include <iomanip>
#include <string>
#include "packets.h"

using std::setw;
using std::setfill;
using std::uppercase;

ostream& operator<<(ostream& os, const packet_fulladdr& trans)
{
  int i = 0;
  string a = "",
         b = "";

  for(i=0; i<BITWIDTH;i++){
      if(trans.rtl_a[i] == '1') a+="1";
      else a+="0";

      if(trans.rtl_b[i] == '1') b+="1";
      else b+="0";
  }

  os << "{" << endl
     << "Integer  A: " << trans.sw_a   << ", \n"
     << "Integer  B: " << trans.sw_b   << ", \n"
     << "Carry     : " << trans.sw_cy  << ", \n"
     << "SC_LOGIC A: " << a << ", \n"
     << "SC_LOGIC B: " << b << ", \n"
     << "Carry RTL : " << trans.rtl_cy
     << endl
     << "}\n";
  return os;
}

void sc_trace(sc_trace_file* tf, const packet_fulladdr& trans, const string& nm)
{
  int i = 0;

  sc_trace(tf, trans.sw_a,      nm + ".sw_a"    );
  sc_trace(tf, trans.sw_b,      nm + ".sw_b"    );
  sc_trace(tf, trans.sw_cy,     nm + ".sw_cy"   );
  sc_trace(tf, trans.rtl_cy,    nm + ".rtl_cy"  );
  for(i=0;i<BITWIDTH;i++){
  sc_trace(tf, trans.rtl_a[i],  nm + ".rtl_a[" + char(i) + "]");
  sc_trace(tf, trans.rtl_b[i],  nm + ".rtl_b[" + char(i) + "]");
  }
}

/*****************************************************************************************/

ostream& operator<<(ostream& os, const packet_fulladdr_lv& trans)
{
  int i = 0;
  string a = "",
         b = "";

  for(i=0; i<BITWIDTH;i++){
      if(trans.rtl_a[i] == '1') a+="1";
      else a+="0";

      if(trans.rtl_b[i] == '1') b+="1";
      else b+="0";
  }

  os << "{" << endl
     << "Integer  A: "  << trans.sw_a   << ", \n"
     << "Integer  B: "  << trans.sw_b   << ", \n"
     << "Carry     : "  << trans.sw_cy  << ", \n"
     << "SC_LV A: "     << a << ", \n"
     << "SC_LV B: "     << b << ", \n"
     << "Carry RTL : "  << trans.rtl_cy
     << endl
     << "}\n";
  return os;
}

void sc_trace(sc_trace_file* tf, const packet_fulladdr_lv& trans, const string& nm)
{
  int i = 0;

  sc_trace(tf, trans.sw_a,      nm + ".sw_a"    );
  sc_trace(tf, trans.sw_b,      nm + ".sw_b"    );
  sc_trace(tf, trans.sw_cy,     nm + ".sw_cy"   );
  sc_trace(tf, trans.rtl_cy,    nm + ".rtl_cy"  );
  for(i=0;i<BITWIDTH;i++){
  sc_trace(tf, trans.rtl_a[i],  nm + ".rtl_a[" + char(i) + "]");
  sc_trace(tf, trans.rtl_b[i],  nm + ".rtl_b[" + char(i) + "]");
  }
}


