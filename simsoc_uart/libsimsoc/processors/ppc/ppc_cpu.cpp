//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/processors/ppc/ppc_cpu.hpp"
#include "libsimsoc/display.hpp"

using namespace std;

namespace simsoc {

  ostream& PPC_AsmId::display(ostream& os) const {
    return os << 'r' <<dec <<(int) id;
  }

  ostream& PPC_BCId::display(ostream& os) const {
    switch(id & 0x1e){ //clear y bit
    case 0: return os << "dnzf";
    case 2: return os << "dzf";
    case 4: return os << "f";
    case 8: return os << "dnzt";
    case 10: return os << "dzt";
    case 12: return os << "t";
    case 16: return os << "dnz";
    case 20: return os << "";
    default:
      if((id&0x1c) == 4)
        return os << "f";
      else if((id & 0x1c) == 12)
        return os << "t";
      else if( (id & 0x17) == 16 )
        return os << "dnz";
      else if( (id & 0x17) == 18 )
        return os << "dz";
      else if( (id & 0x14) == 20)
        return os << "";
      else return os<<"c\t"<<dec<<(int)id;
    }
  }

  std::ostream& PPC_CRId::display(std::ostream& os) const {
    uint8_t n = (id&0x1f)>>2;
    const char* cr_field[4]={"lt","gt","eq","so"};
    return os<< "4*cr"<<(char)('0'+n)<<"+"<<cr_field[id&0x3];
  }

  PPC_CPU::PPC_CPU(int coreId):
    ctr(0), xer(0), lr(0), cr(0),
    ptbr(0), usiar(0), vrsave(0), vscr(0),
    msr(0), pir(0),
    ptehl(0), ptelo(0), tlbmiss(0), sdr1(0),
    dar(0), dsisr(0),
    ldstcr(0), msscr0(0), msssr0(0), ictrl(0), ldstdb(0),
    dec(0), pdec(0), ear(0), iabr(0), dabr(0), ictc(0),
    reserve(0), have_reservation(false), pc(0), npc(0)
  {
    memset(gpr,0,sizeof(gpr));
    tbr.tbr = 0;
    memset(upmc,0,sizeof(upmc));
    memset(ummcr,0,sizeof(ummcr));
    memset(vr,0,sizeof(vr));
    memset(fpr,0,sizeof(fpr));
    memset(hid,0,sizeof(hid));
    memset(ibatu,0,sizeof(ibatu));
    memset(ibatl,0,sizeof(ibatl));
    memset(dbatu,0,sizeof(dbatu));
    memset(dbatl,0,sizeof(dbatl));
    memset(sr,0,sizeof(sr));
    memset(sprg,0,sizeof(sprg));
    memset(srr,0,sizeof(srr));

    if (coreId == 0) {
      msscr0 = 0x00008000;
    } else if (coreId == 1) {
      msscr0 = 0x00008020;
    } else
      msscr0 = coreId; //for multi-core

    //set floating point enabled
    set_MSR_FP(msr);
  }

  ostream& PPC_CPU::display(ostream &os) const {
    os <<hex <<"pc=" <<pc <<", ctr=" <<ctr <<", xer=" <<xer
       <<", lr=" <<lr <<", cr=" <<cr <<", msr=" <<msr <<", sdr1=" <<sdr1 <<".\n";
    for (size_t i = 0; i<32; ++i)
      os <<PPC_AsmId(i) <<'=' <<hex <<gpr[i]
         <<(i==31 ? '.' : ',') <<(i%8==7 ? '\n' : ' ');
    os <<"ibatu = {";
    for (size_t i = 0; i<8; ++i) os <<ibatu[i] <<(i==7 ? "}\n" : ", ");
    os <<"ibatl = {";
    for (size_t i = 0; i<8; ++i) os <<ibatl[i] <<(i==7 ? "}\n" : ", ");
    os <<"dbatu = {";
    for (size_t i = 0; i<8; ++i) os <<dbatu[i] <<(i==7 ? "}\n" : ", ");
    os <<"dbatl = {";
    for (size_t i = 0; i<8; ++i) os <<dbatl[i] <<(i==7 ? "}\n" : ", ");
    os <<"sr = {";
    for (size_t i = 0; i<16; ++i)
      os <<sr[i] <<(i==15 ? "}\n" : (i==7 ? ",\n      " : ", "));
    return os;
  }

} // namespace simsoc
