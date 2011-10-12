//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/processors/ppc/ppc_processor.hpp"
#include "libsimsoc/processors/ppc/ppcis_misc.hpp"

namespace simsoc {

  static uint32_t ppc_cmp_and_mask[8] = {
    0xfffffff0,
    0xffffff0f,
    0xfffff0ff,
    0xffff0fff,
    0xfff0ffff,
    0xff0fffff,
    0xf0ffffff,
    0x0fffffff
  };

  static inline uint64_t mask64(int pos, int len) {
    return ( (1 << len) - 1 ) << pos;

  }

  /*----------------------------------------------------------------------------*/
  PPC_b::PPC_b(uint32_t _li):
    li(_li) {}

  void PPC_b::exec(PPC_Processor &proc) {

    proc.cpu.pc += li;
  }

  std::ostream& PPC_b::display(std::ostream& os) const {
    return os<<"b\t"<<std::hex<<li;
  }

  /*----------------------------------------------------------------------------*/
  PPC_ba::PPC_ba(uint32_t _li):
    li(_li) {}

  void PPC_ba::exec(PPC_Processor &proc) {

    proc.cpu.pc = li;
  }

  std::ostream& PPC_ba::display(std::ostream& os) const {
    return os<<"ba\t"<<std::hex<<li;
  }

  /*----------------------------------------------------------------------------*/
  PPC_bl::PPC_bl(uint32_t _li):
    li(_li) {}

  void PPC_bl::exec(PPC_Processor &proc) {

    proc.cpu.lr = proc.cpu.pc + 4;
    proc.cpu.pc += li;
  }

  std::ostream& PPC_bl::display(std::ostream& os) const {
    return os<<"bl\t"<<std::hex<<li;
  }

  /*----------------------------------------------------------------------------*/
  PPC_bla::PPC_bla(uint32_t _li):
    li(_li) {}

  void PPC_bla::exec(PPC_Processor &proc) {

    proc.cpu.lr = proc.cpu.pc + 4;
    proc.cpu.pc = li;

  }

  std::ostream& PPC_bla::display(std::ostream& os) const {
    return os<<"bla\t"<<std::hex<<li;
  }

  /*----------------------------------------------------------------------------*/
  PPC_bc::PPC_bc(uint8_t _bo, uint8_t _bi, uint32_t _bd):
    bo(_bo), bi(_bi), bd(_bd) {}

  void PPC_bc::exec(PPC_Processor &proc) {


    if (!(bo & 4))
      proc.cpu.ctr--;

    bool bo2 = (bo & 2);
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));
    if ((bo & 4 || ((proc.cpu.ctr != 0) ^ bo2)) && (bo & 16 || (!(cr ^ bo8)))) {
      proc.cpu.pc += bd;
    } else
      proc.cpu.pc += 4;
  }

  std::ostream& PPC_bc::display(std::ostream& os) const {
    return os<<"b" <<(PPC_BCId)bo<<"\t"<<(PPC_CRId)bi<<","<<std::hex<<(int)bd;
  }


  /*----------------------------------------------------------------------------*/
  PPC_bca::PPC_bca(uint8_t _bo, uint8_t _bi, uint32_t _bd):
    bo(_bo), bi(_bi), bd(_bd) {}

  void PPC_bca::exec(PPC_Processor &proc) {
    if (!(bo & 4))
      proc.cpu.ctr--;

    bool bo2 = (bo & 2);
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));

    if (((bo & 4) || ((proc.cpu.ctr != 0) ^ bo2)) && ((bo & 16) || (!(cr ^ bo8)))) {
      proc.cpu.pc = bd;

    } else
      proc.cpu.pc += 4;
  }

  std::ostream& PPC_bca::display(std::ostream& os) const {
    return os<<"b"<<(PPC_BCId)bo<<"a\t"<<(PPC_CRId)bi<<","<<std::hex<<(int)bd;
  }


  /*----------------------------------------------------------------------------*/
  PPC_bcl::PPC_bcl(uint8_t _bo, uint8_t _bi, uint32_t _bd):
    bo(_bo), bi(_bi), bd(_bd) {}

  void PPC_bcl::exec(PPC_Processor &proc) {
    if (!(bo & 4))
      proc.cpu.ctr--;

    bool bo2 = (bo & 2);
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));

    proc.cpu.lr = proc.cpu.pc + 4;

    if (((bo & 4) || ((proc.cpu.ctr != 0) ^ bo2)) && ((bo & 16) || (!(cr ^ bo8)))) {

      proc.cpu.pc += bd;
    } else
      proc.cpu.pc += 4;
  }

  std::ostream& PPC_bcl::display(std::ostream& os) const {
    return os<<"b"<<(PPC_BCId)bo<<"l\t"<<(PPC_CRId)bi<<","<<std::hex<<(int)bd;
  }


  /*----------------------------------------------------------------------------*/
  PPC_bcla::PPC_bcla(uint8_t _bo, uint8_t _bi, uint32_t _bd):
    bo(_bo), bi(_bi), bd(_bd) {}

  void PPC_bcla::exec(PPC_Processor &proc) {
    if (!(bo & 4))
      proc.cpu.ctr--;

    bool bo2 = (bo & 2);
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));

    proc.cpu.lr = proc.cpu.pc + 4;

    if (((bo & 4) || ((proc.cpu.ctr != 0) ^ bo2)) && ((bo & 16) || (!(cr ^ bo8)))) {
      proc.cpu.pc = bd;

    } else
      proc.cpu.pc += 4;
  }

  std::ostream& PPC_bcla::display(std::ostream& os) const {
    return os<<"b"<<(PPC_BCId)bo<<"la\t"<<(PPC_CRId)bi<<","<<std::hex<<(int)bd;
  }


  /*----------------------------------------------------------------------------*/
  PPC_bcctr::PPC_bcctr(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_bcctr::exec(PPC_Processor &proc) {
    bool bt8 = (bt & 8);
    bool cr = (proc.cpu.cr & (1<<(31-ba)));

    if ((bt & 16) || (!(cr ^ bt8)))
      proc.cpu.pc = proc.cpu.ctr & 0xfffffffc;
    else
      proc.cpu.pc += 4;
  }

  std::ostream& PPC_bcctr::display(std::ostream& os) const {
    return os<<"b"<<(PPC_BCId)bt<<"ctr\t"<<(PPC_CRId)ba;
  }

  /*----------------------------------------------------------------------------*/
  PPC_bcctrl::PPC_bcctrl(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_bcctrl::exec(PPC_Processor &proc) {
    bool bt8 = (bt & 8);
    bool cr = (proc.cpu.cr & (1<<(31-ba)));

    proc.cpu.lr = proc.cpu.pc + 4;

    if ((bt & 16) || (!(cr ^ bt8)))
      proc.cpu.pc = proc.cpu.ctr & 0xfffffffc;
    else
      proc.cpu.pc += 4;
  }

  std::ostream& PPC_bcctrl::display(std::ostream& os) const {
    return os<<"b"<<(PPC_BCId)bt<<"ctrl\t"<<(PPC_CRId)ba;
  }

  /*----------------------------------------------------------------------------*/
  PPC_bclr::PPC_bclr(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_bclr::exec(PPC_Processor &proc) {
    uint32_t tmp;
    if (!(bt & 4))
      proc.cpu.ctr--;

    bool bt2 = (bt & 2);
    bool bt8 = (bt & 8);
    bool cr = (proc.cpu.cr & (1<<(31-ba)));

    tmp = proc.cpu.lr;

    if (((bt & 4) || ((proc.cpu.ctr != 0) ^ bt2)) && ((bt & 16) || (!(cr ^ bt8)))) {
      proc.cpu.pc = tmp & 0xfffffffc;
    } else
      proc.cpu.pc += 4;
  }

  std::ostream& PPC_bclr::display(std::ostream& os) const {
    return os<<"b"<<(PPC_BCId)bt<<"lr\t"<<(PPC_CRId)ba;
  }

  /*----------------------------------------------------------------------------*/
  PPC_bclrl::PPC_bclrl(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_bclrl::exec(PPC_Processor &proc) {
    uint32_t tmp;
    if (!(bt & 4))
      proc.cpu.ctr--;

    bool bt2 = (bt & 2);
    bool bt8 = (bt & 8);
    bool cr = (proc.cpu.cr & (1<<(31-ba)));

    tmp = proc.cpu.lr;

    proc.cpu.lr = proc.cpu.pc + 4;

    if (((bt & 4) || ((proc.cpu.ctr != 0) ^ bt2)) && ((bt & 16) || (!(cr ^ bt8)))) {
      proc.cpu.pc = tmp & 0xfffffffc;
    } else
      proc.cpu.pc += 4;
  }

  std::ostream& PPC_bclrl::display(std::ostream& os) const {
    return os<<"b"<<(PPC_BCId)bt<<"lrl\t"<<(PPC_CRId)ba;
  }

  /*----------------------------------------------------------------------------*/
  PPC_eciwx::PPC_eciwx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_eciwx::exec(PPC_Processor &proc) {
    TODO("eciwx");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_eciwx::display(std::ostream& os) const {
    return os<<"eciwx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_ecowx::PPC_ecowx(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_ecowx::exec(PPC_Processor &proc) {
    TODO("ecowx");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_ecowx::display(std::ostream& os) const {
    return os<<"ecowx\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_eieio::PPC_eieio(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_eieio::exec(PPC_Processor &proc) {
    //TODO("eieio");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_eieio::display(std::ostream& os) const {
    return os<<"eieio\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;;
  }

  /*----------------------------------------------------------------------------*/
  PPC_icbi::PPC_icbi(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_icbi::exec(PPC_Processor &proc) {
    //TODO("icbi");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_icbi::display(std::ostream& os) const {
    return os<<"icbi\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;;
  }

  /*----------------------------------------------------------------------------*/
  PPC_isync::PPC_isync(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_isync::exec(PPC_Processor &proc) {
    //TODO("isync");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_isync::display(std::ostream& os) const {
    return os<<"isync\t"<<bt<<", "<<ba<<", "<<bb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mcrf::PPC_mcrf(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_mcrf::exec(PPC_Processor &proc) {
    int bf = bt >> 2;
    int bfa = ba >> 2;
    bf = 7-bf;
    bfa = 7-bfa;
    uint32_t c = (proc.cpu.cr>>(bfa*4)) & 0xf;
    proc.cpu.cr &= ppc_cmp_and_mask[bf];
    proc.cpu.cr |= c<<(bf*4);

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mcrf::display(std::ostream& os) const {
    return os<<"mcrf\tcr"<<std::dec<<(int)(bt>>2) <<", "<<"cr"<<(int)(ba>>2)<<"";
  }

  /*----------------------------------------------------------------------------*/
  PPC_mcrfs::PPC_mcrfs(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mcrfs::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint8_t crfD = rt>>2;
    uint8_t crfS = ra>>2;
    uint8_t value = proc.fp_unit.fpscr.move_field_to_cr(crfS);
    proc.cpu.update_CR_field(crfD,value);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mcrfs::display(std::ostream& os) const {
    return os<<"mcrfs\tcrf"<<std::dec<<(int)(rt>>2) <<", "<<"crf"<<(int)(ra>>2)<<"";
  }

  /*----------------------------------------------------------------------------*/
  PPC_mcrxr::PPC_mcrxr(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mcrxr::exec(PPC_Processor &proc) {
    TODO("mcrxr");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mcrxr::display(std::ostream& os) const {
    return os<<"mcrxr\tcr"<<std::dec<<(int)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mfcr::PPC_mfcr(uint8_t _rt, uint16_t _spr):
    rt(_rt), spr(_spr) {}

  void PPC_mfcr::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = proc.cpu.cr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mfcr::display(std::ostream& os) const {
    return os<<"mfcr\t"<<(PPC_AsmId)rt;
  }


  /*----------------------------------------------------------------------------*/
  PPC_mfocrf::PPC_mfocrf(uint8_t _rt, uint16_t _spr):
    rt(_rt), spr(_spr) {}

  void PPC_mfocrf::exec(PPC_Processor &proc) {
    TODO("mfocrf");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mfocrf::display(std::ostream& os) const {
    return os<<"mfocrf\t"<<(PPC_AsmId)rt <<", "<<spr<<"";
  }


  /*----------------------------------------------------------------------------*/
  PPC_mffs::PPC_mffs(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mffs::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    proc.cpu.fpr[rt] = proc.fp_unit.fpscr.get_value();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mffs::display(std::ostream& os) const {
    return os<<"mffs\tfr"<<(size_t)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mffs_::PPC_mffs_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mffs_::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    proc.cpu.fpr[rt] = proc.fp_unit.fpscr.get_value();
    proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mffs_::display(std::ostream& os) const {
    return os<<"mffs_fr\t"<<(size_t)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mfmsr::PPC_mfmsr(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mfmsr::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = proc.cpu.msr;
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mfmsr::display(std::ostream& os) const {
    return os<<"mfmsr\t"<<(PPC_AsmId)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mfspr::PPC_mfspr(uint8_t _rt, uint16_t _spr):
    rt(_rt), spr(_spr) {}

  void PPC_mfspr::exec(PPC_Processor &proc) {
    int tmp =   ((spr & 0x1f) << 5) | ((spr >> 5) & 0x1f);

    switch(tmp) {//1,8,9 for User, or for Supervisor
    case    1 : proc.cpu.gpr[rt] = proc.cpu.xer;      break;
    case    8 : proc.cpu.gpr[rt] = proc.cpu.lr;       break;
    case    9 : proc.cpu.gpr[rt] = proc.cpu.ctr;      break;
    case   18 : proc.cpu.gpr[rt] = proc.cpu.dsisr;    break;
    case   19 : proc.cpu.gpr[rt] = proc.cpu.dar;      break;
    case   22 : proc.cpu.dec     = proc.cpu.pdec / PPC_CPU::TBF_RATIO;
      proc.cpu.gpr[rt] = proc.cpu.dec;      break;
    case   25 : proc.cpu.gpr[rt] = proc.cpu.sdr1;     break;
    case   26 : proc.cpu.gpr[rt] = proc.cpu.srr[0];   break;
    case   27 : proc.cpu.gpr[rt] = proc.cpu.srr[1];   break;
    case  256 : proc.cpu.gpr[rt] = proc.cpu.vrsave;   break;
    case  272 : proc.cpu.gpr[rt] = proc.cpu.sprg[0];  break;
    case  273 : proc.cpu.gpr[rt] = proc.cpu.sprg[1];  break;
    case  274 : proc.cpu.gpr[rt] = proc.cpu.sprg[2];  break;
    case  275 : proc.cpu.gpr[rt] = proc.cpu.sprg[3];  break;
    case  282 : proc.cpu.gpr[rt] = proc.cpu.ear;      break;
    case  286 : proc.cpu.gpr[rt] = proc.cpu.svr;      break;
    case  287 : proc.cpu.gpr[rt] = proc.cpu.pvr;      break;
    case  528 : proc.cpu.gpr[rt] = proc.cpu.ibatu[0]; break;
    case  529 : proc.cpu.gpr[rt] = proc.cpu.ibatl[0]; break;
    case  530 : proc.cpu.gpr[rt] = proc.cpu.ibatu[1]; break;
    case  531 : proc.cpu.gpr[rt] = proc.cpu.ibatl[1]; break;
    case  532 : proc.cpu.gpr[rt] = proc.cpu.ibatu[2]; break;
    case  533 : proc.cpu.gpr[rt] = proc.cpu.ibatl[2]; break;
    case  534 : proc.cpu.gpr[rt] = proc.cpu.ibatu[3]; break;
    case  535 : proc.cpu.gpr[rt] = proc.cpu.ibatl[3]; break;
    case  536 : proc.cpu.gpr[rt] = proc.cpu.dbatu[0]; break;
    case  537 : proc.cpu.gpr[rt] = proc.cpu.dbatl[0]; break;
    case  538 : proc.cpu.gpr[rt] = proc.cpu.dbatu[1]; break;
    case  539 : proc.cpu.gpr[rt] = proc.cpu.dbatl[1]; break;
    case  540 : proc.cpu.gpr[rt] = proc.cpu.dbatu[2]; break;
    case  541 : proc.cpu.gpr[rt] = proc.cpu.dbatl[2]; break;
    case  542 : proc.cpu.gpr[rt] = proc.cpu.dbatu[3]; break;
    case  543 : proc.cpu.gpr[rt] = proc.cpu.dbatl[3]; break;
    case  560 : proc.cpu.gpr[rt] = proc.cpu.ibatu[4]; break;
    case  561 : proc.cpu.gpr[rt] = proc.cpu.ibatl[4]; break;
    case  562 : proc.cpu.gpr[rt] = proc.cpu.ibatu[5]; break;
    case  563 : proc.cpu.gpr[rt] = proc.cpu.ibatl[5]; break;
    case  564 : proc.cpu.gpr[rt] = proc.cpu.ibatu[6]; break;
    case  565 : proc.cpu.gpr[rt] = proc.cpu.ibatl[6]; break;
    case  566 : proc.cpu.gpr[rt] = proc.cpu.ibatu[7]; break;
    case  567 : proc.cpu.gpr[rt] = proc.cpu.ibatl[7]; break;
    case  568 : proc.cpu.gpr[rt] = proc.cpu.dbatu[4]; break;
    case  569 : proc.cpu.gpr[rt] = proc.cpu.dbatl[4]; break;
    case  570 : proc.cpu.gpr[rt] = proc.cpu.dbatu[5]; break;
    case  571 : proc.cpu.gpr[rt] = proc.cpu.dbatl[5]; break;
    case  572 : proc.cpu.gpr[rt] = proc.cpu.dbatu[6]; break;
    case  573 : proc.cpu.gpr[rt] = proc.cpu.dbatl[6]; break;
    case  574 : proc.cpu.gpr[rt] = proc.cpu.dbatu[7]; break;
    case  575 : proc.cpu.gpr[rt] = proc.cpu.dbatl[7]; break;
    case 1008 : proc.cpu.gpr[rt] = proc.cpu.hid[0];   break;
    case 1009 : proc.cpu.gpr[rt] = proc.cpu.hid[1];   break;
    case 1011 : proc.cpu.gpr[rt] = proc.cpu.ictrl;    break;
    case 1012 : proc.cpu.gpr[rt] = proc.cpu.ldstdb;   break;
    case 1013 : proc.cpu.gpr[rt] = proc.cpu.dabr;     break;
    case 1014 : proc.cpu.gpr[rt] = proc.cpu.msscr0;   break;
    case 1015 : proc.cpu.gpr[rt] = proc.cpu.msssr0;   break;
    case 1016 : proc.cpu.gpr[rt] = proc.cpu.ldstcr;   break;
    case 1017 : /*proc.cpu.gpr[rt] = proc.cpu.l2cr;*/ break;
    case 1019 : proc.cpu.gpr[rt] = proc.cpu.ictc;     break;
    case 1023 : proc.cpu.gpr[rt] = proc.cpu.pir;      break;
    default:
      cout<<"unknow mfspr spr! case: "<<tmp<<endl;
      cout<<"pc : "<<hex<<proc.cpu.pc<<endl;
      exit(-1);
    }

    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mfspr::display(std::ostream& os) const {
    return os<<"mfspr\t"<<(PPC_AsmId)rt <<", "<<"spr";
  }


  /*----------------------------------------------------------------------------*/
  PPC_mfsr::PPC_mfsr(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mfsr::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = proc.cpu.sr[ra&0xf];
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mfsr::display(std::ostream& os) const {
    return os<<"mfsr"<<(PPC_AsmId)rt<<", "<<(ra&0xf);
  }

  /*----------------------------------------------------------------------------*/
  PPC_mfsrin::PPC_mfsrin(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mfsrin::exec(PPC_Processor &proc) {
    proc.cpu.gpr[rt] = proc.cpu.sr[proc.cpu.gpr[rb] >> 28];
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mfsrin::display(std::ostream& os) const {
    return os<<"mfsrin"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mftb::PPC_mftb(uint8_t _rt, uint16_t _spr):
    rt(_rt), spr(_spr) {}

  void PPC_mftb::exec(PPC_Processor &proc) {
    proc.cpu.tbr.tbr = proc.cpu.ptbr;
    uint16_t n = ((spr & 0x1f) << 5) | ((spr >> 5) & 0x1f);
    if(n == 268)
      proc.cpu.gpr[rt]= proc.cpu.tbr._tbr[0];
    else if(n == 269)
      proc.cpu.gpr[rt]= proc.cpu.tbr._tbr[1];
    else {
      cout<<"mftb error : "<<n<<hex<<" spr : "<<spr<<endl;
      exit(-1);
    }
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mftb::display(std::ostream& os) const {
    return os <<"mftb\t"<<(PPC_AsmId)rt<<", "<<spr;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtcrf::PPC_mtcrf(uint8_t _rt, uint16_t _spr):
    rt(_rt), spr(_spr) {}

  void PPC_mtcrf::exec(PPC_Processor &proc) {
    uint32_t tmp, tmp1 = (spr >> 1) & 0xff;
    tmp =  ((tmp1 & 0x80) ? 0xf0000000 : 0) | ((tmp1 & 0x40) ? 0x0f000000 : 0)
      | ((tmp1 & 0x20) ? 0x00f00000 : 0) | ((tmp1 & 0x10) ? 0x000f0000 : 0)
      | ((tmp1 & 0x08) ? 0x0000f000 : 0) | ((tmp1 & 0x04) ? 0x00000f00 : 0)
      | ((tmp1 & 0x02) ? 0x000000f0 : 0) | ((tmp1 & 0x01) ? 0x0000000f : 0);
    proc.cpu.cr = (proc.cpu.gpr[rt] & tmp) | (proc.cpu.cr & ~tmp);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtcrf::display(std::ostream& os) const {
    return os<<"mtcrf\t"<<"fxm, "<<(PPC_AsmId)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtocrf::PPC_mtocrf(uint8_t _rt, uint16_t _spr):
    rt(_rt), spr(_spr) {}

  void PPC_mtocrf::exec(PPC_Processor &proc) {
    TODO("mtocrf");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtocrf::display(std::ostream& os) const {
    return os<<"mtocrf\t"<<"fxm, "<<(PPC_AsmId)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtfsb0::PPC_mtfsb0(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mtfsb0::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    proc.fp_unit.fpscr.set_bit(rt,false);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtfsb0::display(std::ostream& os) const {
    return os<<"mtfsb0\t" <<dec<<(int)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtfsb0_::PPC_mtfsb0_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mtfsb0_::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    proc.fp_unit.fpscr.set_bit(rt,false);
    proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtfsb0_::display(std::ostream& os) const {
    return os<<"mtfsb0_\t" <<dec<<(int)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtfsb1::PPC_mtfsb1(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mtfsb1::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    proc.fp_unit.fpscr.set_bit(rt,true);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtfsb1::display(std::ostream& os) const {
    return os<<"mtfsb1\t" <<dec<<(int)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtfsb1_::PPC_mtfsb1_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mtfsb1_::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    proc.fp_unit.fpscr.set_bit(rt,true);
    proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtfsb1_::display(std::ostream& os) const {
    return os<<"mtfsb1_\t" <<dec<<(int)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtfsf::PPC_mtfsf(uint8_t _flm,  uint8_t _frb):
    flm(_flm), frb(_frb) {}

  void PPC_mtfsf::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t value = (uint32_t)proc.cpu.fpr[frb];
    for(int8_t field=7;field>=0;field--){
      if(flm & (0x1<<(7-field))){
        proc.fp_unit.fpscr.set_field(field,value&0xf);
      }
      value = value >> 4;
    }
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtfsf::display(std::ostream& os) const {
    return os<<"mtfsf\t"<<hex<<(size_t)flm<<", fr"<<dec<<frb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtfsf_::PPC_mtfsf_(uint8_t _flm,  uint8_t _frb):
    flm(_flm), frb(_frb) {}

  void PPC_mtfsf_::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint32_t value = (uint32_t)proc.cpu.fpr[frb];
    for(int8_t field=7;field>=0;field--){
      if(flm & (0x1<<(7-field))){
        proc.fp_unit.fpscr.set_field(field,value&0xf);
        value = value >> 4;
      }
    }
    proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtfsf_::display(std::ostream& os) const {
    return os<<"mtfsf_\t"<<hex<<flm<<", fr"<<dec<<frb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtfsfi::PPC_mtfsfi(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mtfsfi::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint8_t crfD = rt>>2;
    uint8_t imm = rb>>1;
    proc.fp_unit.fpscr.set_field(crfD,imm);
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtfsfi::display(std::ostream& os) const {
    return os<<"mtfsfi\tcrf"<<dec<<(int)(rt>>2)<<","<<hex<<(rb>>1);
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtfsfi_::PPC_mtfsfi_(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb){}

  void PPC_mtfsfi_::exec(PPC_Processor &proc) {
    proc.fp_unit.check_fp_enabled();
    uint8_t crfD = rt>>2;
    uint8_t imm = rb>>1;
    proc.fp_unit.fpscr.set_field(crfD,imm);
    proc.fp_unit.update_CR1();
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtfsfi_::display(std::ostream& os) const {
    return os<<"mtfsfi_\tcrf"<<dec<<(int)(rt>>2)<<","<<hex<<(rb>>1);
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtmsr::PPC_mtmsr(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mtmsr::exec(PPC_Processor &proc) {
    proc.cpu.msr = proc.cpu.gpr[rt];
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtmsr::display(std::ostream& os) const {
    return os<<"mtmsr\t"<<(PPC_AsmId)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtmsrd::PPC_mtmsrd(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mtmsrd::exec(PPC_Processor &proc) {
    TODO("mtmsrd");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtmsrd::display(std::ostream& os) const {
    return os<<"mtmsrd\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtspr::PPC_mtspr(uint8_t _rt, uint16_t _spr):
    rt(_rt), spr(_spr) {}

  void PPC_mtspr::exec(PPC_Processor &proc) {
    int tmp = ((spr & 0x1f) << 5) | ((spr >> 5) & 0x1f);
    switch(tmp) {//1,8,9 for User, or for Supervisor
    case    1 : proc.cpu.xer      = proc.cpu.gpr[rt]; break;
    case    8 : proc.cpu.lr       = proc.cpu.gpr[rt]; break;
    case    9 : proc.cpu.ctr      = proc.cpu.gpr[rt]; break;
    case   18 : proc.cpu.dsisr    = proc.cpu.gpr[rt]; break;
    case   19 : proc.cpu.dar      = proc.cpu.gpr[rt]; break;
    case   22 : proc.cpu.dec      = proc.cpu.gpr[rt];
      proc.cpu.pdec     = proc.cpu.dec;
      proc.cpu.pdec  *= PPC_CPU::TBF_RATIO; break;
    case   25 : proc.cpu.sdr1     = proc.cpu.gpr[rt]; break;
    case   26 : proc.cpu.srr[0]   = proc.cpu.gpr[rt]; break;
    case   27 : proc.cpu.srr[1]   = proc.cpu.gpr[rt]; break;
    case  256 : proc.cpu.vrsave   = proc.cpu.gpr[rt]; break;
    case  272 : proc.cpu.sprg[0]  = proc.cpu.gpr[rt]; break;
    case  273 : proc.cpu.sprg[1]  = proc.cpu.gpr[rt]; break;
    case  274 : proc.cpu.sprg[2]  = proc.cpu.gpr[rt]; break;
    case  275 : proc.cpu.sprg[3]  = proc.cpu.gpr[rt]; break;
    case  282 : proc.cpu.ear      = proc.cpu.gpr[rt]; break;
    case  284 :
      {
        proc.cpu.tbr._tbr[0] = proc.cpu.gpr[rt];
        proc.cpu.ptbr = proc.cpu.tbr.tbr;
        break;
      }
    case  285 :
      {
        proc.cpu.tbr._tbr[1] = proc.cpu.gpr[rt];
        proc.cpu.ptbr = proc.cpu.tbr.tbr;
        break;
      }

    case  528 : proc.cpu.ibatu[0] = proc.cpu.gpr[rt]; break;
    case  529 : proc.cpu.ibatl[0] = proc.cpu.gpr[rt]; break;
    case  530 : proc.cpu.ibatu[1] = proc.cpu.gpr[rt]; break;
    case  531 : proc.cpu.ibatl[1] = proc.cpu.gpr[rt]; break;
    case  532 : proc.cpu.ibatu[2] = proc.cpu.gpr[rt]; break;
    case  533 : proc.cpu.ibatl[2] = proc.cpu.gpr[rt]; break;
    case  534 : proc.cpu.ibatu[3] = proc.cpu.gpr[rt]; break;
    case  535 : proc.cpu.ibatl[3] = proc.cpu.gpr[rt]; break;
    case  536 : proc.cpu.dbatu[0] = proc.cpu.gpr[rt]; break;
    case  537 : proc.cpu.dbatl[0] = proc.cpu.gpr[rt]; break;
    case  538 : proc.cpu.dbatu[1] = proc.cpu.gpr[rt]; break;
    case  539 : proc.cpu.dbatl[1] = proc.cpu.gpr[rt]; break;
    case  540 : proc.cpu.dbatu[2] = proc.cpu.gpr[rt]; break;
    case  541 : proc.cpu.dbatl[2] = proc.cpu.gpr[rt]; break;
    case  542 : proc.cpu.dbatu[3] = proc.cpu.gpr[rt]; break;
    case  543 : proc.cpu.dbatl[3] = proc.cpu.gpr[rt]; break;
    case  560 : proc.cpu.ibatu[4] = proc.cpu.gpr[rt]; break;
    case  561 : proc.cpu.ibatl[4] = proc.cpu.gpr[rt]; break;
    case  562 : proc.cpu.ibatu[5] = proc.cpu.gpr[rt]; break;
    case  563 : proc.cpu.ibatl[5] = proc.cpu.gpr[rt]; break;
    case  564 : proc.cpu.ibatu[6] = proc.cpu.gpr[rt]; break;
    case  565 : proc.cpu.ibatl[6] = proc.cpu.gpr[rt]; break;
    case  566 : proc.cpu.ibatu[7] = proc.cpu.gpr[rt]; break;
    case  567 : proc.cpu.ibatl[7] = proc.cpu.gpr[rt]; break;
    case  568 : proc.cpu.dbatu[4] = proc.cpu.gpr[rt]; break;
    case  569 : proc.cpu.dbatl[4] = proc.cpu.gpr[rt]; break;
    case  570 : proc.cpu.dbatu[5] = proc.cpu.gpr[rt]; break;
    case  571 : proc.cpu.dbatl[5] = proc.cpu.gpr[rt]; break;
    case  572 : proc.cpu.dbatu[6] = proc.cpu.gpr[rt]; break;
    case  573 : proc.cpu.dbatl[6] = proc.cpu.gpr[rt]; break;
    case  574 : proc.cpu.dbatu[7] = proc.cpu.gpr[rt]; break;
    case  575 : proc.cpu.dbatl[7] = proc.cpu.gpr[rt]; break;
    case 1008 : proc.cpu.hid[0]   = proc.cpu.gpr[rt]; break;
    case 1009 : proc.cpu.hid[1]   = proc.cpu.gpr[rt]; break;
    case 1011 : proc.cpu.ictrl    = proc.cpu.gpr[rt]; break;
    case 1012 : proc.cpu.ldstdb   = proc.cpu.gpr[rt]; break;
    case 1013 : proc.cpu.dabr     = proc.cpu.gpr[rt]; break;
    case 1014 : proc.cpu.msscr0   = proc.cpu.gpr[rt]; break;
    case 1015 : proc.cpu.msssr0   = proc.cpu.gpr[rt]; break;
    case 1016 : proc.cpu.ldstcr   = proc.cpu.gpr[rt]; break;
    case 1017 : /*proc.cpu.l2cr   = proc.cpu.gpr[rt];*/ break;
    case 1019 : proc.cpu.ictc   = proc.cpu.gpr[rt];   break;
    case 1023 : proc.cpu.pir      = proc.cpu.gpr[rt]; break;
    default:
      cout<<"unknow mtspr spr! case: "<<tmp<<endl;
      cout<<"pc : "<<hex<<proc.cpu.pc<<endl;
      exit(-1);
    }
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtspr::display(std::ostream& os) const {
    return os<<"mtspr\t" <<spr<<", "<<(PPC_AsmId)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtsr::PPC_mtsr(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mtsr::exec(PPC_Processor &proc) {
    proc.cpu.sr[ra&0xf] = proc.cpu.gpr[rt];
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtsr::display(std::ostream& os) const {
    return os<<"mtsr\t"<<(ra&0xf)<<", "<<(PPC_AsmId)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_mtsrin::PPC_mtsrin(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_mtsrin::exec(PPC_Processor &proc) {
    proc.cpu.sr[proc.cpu.gpr[rb] >> 28] = proc.cpu.gpr[rt];
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_mtsrin::display(std::ostream& os) const {
    return os<<"mtsrin\t"<<(PPC_AsmId)rb<<", "<<(PPC_AsmId)rt;
  }

  /*----------------------------------------------------------------------------*/
  PPC_rfi::PPC_rfi(uint8_t _bt, uint8_t _ba,  uint8_t _bb):
    bt(_bt), ba(_ba), bb(_bb) {}

  void PPC_rfi::exec(PPC_Processor &proc) {
    //todo interrupt
    if(check_MSR_PR(proc.cpu.msr))
      proc.interrupt(INT_PROGRAM, PPC_EXC_PROGRAM_PRIV);
    proc.cpu.msr = proc.cpu.srr[1] & 0xff73;//todo...
    proc.cpu.pc = proc.cpu.srr[0] & (~3);
  }

  std::ostream& PPC_rfi::display(std::ostream& os) const {
    return os<<"rfi";
  }

  /*----------------------------------------------------------------------------*/
  PPC_sc::PPC_sc(uint8_t _lev):
    lev(_lev) {}

  void PPC_sc::exec(PPC_Processor &proc) {
    //proc.cpu.pc += 4;
    //proc.interrupt(INT_SC, PPC_EXC_PROGRAM_TRAP);
    if(proc.linux_os){
      proc.linux_os->ExecuteSystemCall(proc.cpu.gpr[0]);
      proc.cpu.pc += 4;
    }else{
      proc.set_something_pending();
      proc.set_it_pending ();
      proc.trap_exception = true;
      proc.cpu.pc += 4;
    }
  }

  std::ostream& PPC_sc::display(std::ostream& os) const {
    return os<<"sc";
  }

  /*----------------------------------------------------------------------------*/
  PPC_slbia::PPC_slbia(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_slbia::exec(PPC_Processor &proc) {
    TODO("slbia");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_slbia::display(std::ostream& os) const {
    return os<<"slbia\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_slbie::PPC_slbie(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_slbie::exec(PPC_Processor &proc) {
    TODO("slbie");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_slbie::display(std::ostream& os) const {
    return os<<"slbie\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_slbmfee::PPC_slbmfee(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_slbmfee::exec(PPC_Processor &proc) {
    TODO("slbmfee");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_slbmfee::display(std::ostream& os) const {
    return os<<"slbmfee\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_slbmfev::PPC_slbmfev(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_slbmfev::exec(PPC_Processor &proc) {
    TODO("slbmfev");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_slbmfev::display(std::ostream& os) const {
    return os<<"slbmfev\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_slbmte::PPC_slbmte(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb)  {}

  void PPC_slbmte::exec(PPC_Processor &proc) {
    TODO("slbmte");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_slbmte::display(std::ostream& os) const {
    return os<<"slbmte\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_sync::PPC_sync(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_sync::exec(PPC_Processor &proc) {
    //TODO("sync");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_sync::display(std::ostream& os) const {
    return os<<"sync\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_td::PPC_td(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_td::exec(PPC_Processor &proc) {
    TODO("td");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_td::display(std::ostream& os) const {
    return os<<"td\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_tdi::PPC_tdi(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_tdi::exec(PPC_Processor &proc) {
    TODO("tdi");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_tdi::display(std::ostream& os) const {
    return os<<"tdi\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<d;
  }


  /*----------------------------------------------------------------------------*/
  PPC_tlbia::PPC_tlbia(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_tlbia::exec(PPC_Processor &proc) {
    TODO("tlbia");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_tlbia::display(std::ostream& os) const {
    return os<<"tlbia\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_tlbie::PPC_tlbie(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_tlbie::exec(PPC_Processor &proc) {
    //TODO("tlbie");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_tlbie::display(std::ostream& os) const {
    return os<<"tlbie\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_tlbsync::PPC_tlbsync(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_tlbsync::exec(PPC_Processor &proc) {
    //TODO("tlbsync");
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_tlbsync::display(std::ostream& os) const {
    return os<<"tlbsync\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_tw::PPC_tw(uint8_t _rt, uint8_t _ra,  uint8_t _rb):
    rt(_rt), ra(_ra), rb(_rb) {}

  void PPC_tw::exec(PPC_Processor &proc) {
    if(proc.debugger() && rt==12 && ra==rb)
      proc.debugger()->notify(Debugger::EV_TRAP);
    else
      TODO("tw");
  }

  std::ostream& PPC_tw::display(std::ostream& os) const {
    return os<<"tw\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<(PPC_AsmId)rb;
  }

  /*----------------------------------------------------------------------------*/
  PPC_twi::PPC_twi(uint8_t _rt, uint8_t _ra, uint32_t _d):
    rt(_rt), ra(_ra), d(_d) {}

  void PPC_twi::exec(PPC_Processor &proc) {
    //cout<<"PPC_twi:: pc: "<<hex<<proc.cpu.pc<<endl;
    uint32_t a = proc.cpu.gpr[ra];
    if (((rt & 16) && ((int32_t)a < (int32_t)d))
        || ((rt & 8) && ((int32_t)a > (int32_t)d))
        || ((rt & 4) && (a == d))
        || ((rt & 2) && (a < d))
        || ((rt & 1) && (a > d))) {
      proc.interrupt(INT_PROGRAM, PPC_EXC_PROGRAM_TRAP);
    }
    proc.cpu.pc += 4;
  }

  std::ostream& PPC_twi::display(std::ostream& os) const {
    return os<<"twi\t"<<(PPC_AsmId)rt<<", "<<(PPC_AsmId)ra<<", "<<d;
  }

} // namespace simsoc
