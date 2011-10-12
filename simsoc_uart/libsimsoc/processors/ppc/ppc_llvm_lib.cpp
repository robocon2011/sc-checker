//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "ppc_processor.hpp"
#include "ppc_utils.hpp"
#include <libsimsoc/bitwise_operator.hpp>
#include <libsimsoc/display.hpp>

namespace simsoc {

  // Some functions useful for LLVM code generation

  extern "C" void ppc_increment_pc(PPC_Processor *proc) {
    proc->cpu.pc += 4;
  }

  extern "C" void ppc_proc_hook(PPC_Processor *proc) {
    proc->hook();
  }

  extern "C" void ppc_decrement_pc_if_not_OK(PseudoStatus status, PPC_Processor *proc) {
    if (status!=OK)
      proc->cpu.pc -= 4;
  }

  // Semantics functions for the instructions

  extern "C" PseudoStatus ppc_add(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_add\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = a+b;
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_generic(PPC_Processor &proc,
                                      PPC_Instruction *instr) {
    proc.debug() <<"pif_generic: " <<*instr <<endl;
    instr->exec(proc);
    if (instr->may_branch())
      return BRANCH;
    else {
      proc.cpu.pc -= 4;
      return OK;
    }
  }

  extern "C" PseudoStatus ppc_add_(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_add.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = a+b;
    ppc_update_cr0(proc,rt);
    return OK;
  }
  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addc(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_addc\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t t = a+b;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (t < a)
      proc.cpu.xer |= XER_CA; // XER[CA] = 1
    else
      proc.cpu.xer &= ~XER_CA; // XER[CA] = 0
    return OK;
  }

  extern "C" PseudoStatus ppc_addc_(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_addc.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t t = a+b;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (t < a)
      proc.cpu.xer |= XER_CA; // XER[CA] = 1
    else
      proc.cpu.xer &= ~XER_CA; // XER[CA] = 0
    ppc_update_cr0(proc,rt);
    return OK;
  }

/*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addco(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_addco\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t t = a+b;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (t < a)
      proc.cpu.xer |= XER_CA; // XER[CA] = 1
    else
      proc.cpu.xer &= ~XER_CA; // XER[CA] = 0

    if((a ^ (~b)) & (a ^ t))
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    return OK;
  }

  extern "C" PseudoStatus ppc_addco_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_addco.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t t = a+b;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (t < a)
      proc.cpu.xer |= XER_CA; // XER[CA] = 1
    else
      proc.cpu.xer &= ~XER_CA; // XER[CA] = 0

    if((a ^ (~b)) & (a ^ t) >> 31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }
/*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_adde(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_adde\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + b + ca;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (t < a)
      proc.cpu.xer |= XER_CA; // XER[CA] = 1
    else
      proc.cpu.xer &= ~XER_CA; // XER[CA] = 0
    return OK;
  }

  extern "C" PseudoStatus ppc_adde_(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_adde.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + b + ca;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (t < a)
      proc.cpu.xer |= XER_CA; // XER[CA] = 1
    else
      proc.cpu.xer &= ~XER_CA; // XER[CA] = 0
    ppc_update_cr0(proc, rt);
    return OK;
  }

/*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addeo(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_addeo\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + b + ca;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (t < a)
      proc.cpu.xer |= XER_CA; // XER[CA] = 1
    else
      proc.cpu.xer &= ~XER_CA; // XER[CA] = 0

    if((a ^ (~b)) & (a ^ t) >> 31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    return OK;
  }

  extern "C" PseudoStatus ppc_addeo_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_addeo.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + b + ca;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (t < a)
      proc.cpu.xer |= XER_CA; // XER[CA] = 1
    else
      proc.cpu.xer &= ~XER_CA; // XER[CA] = 0

    if((a ^ (~ b)) & (a ^ t))
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }

/*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addme(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_addme\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + ca + 0xffffffff;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (a || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    return OK;
  }

  extern "C" PseudoStatus ppc_addme_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_addme.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + ca + 0xffffffff;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (a || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addmeo(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_addmeo\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + ca + 0xffffffff;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (a || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    if((a ^~ (0xffffffff + ca)) & (a ^ t) << 31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    return OK;
  }

  extern "C" PseudoStatus ppc_addmeo_(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_addmeo.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + ca + 0xffffffff;
    proc.cpu.gpr[rt] = t;
    // update xer
    if (a || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    if((a ^~ (0xffffffff + ca)) & (a ^ t) << 31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addze(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_addze\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + ca ;
    proc.cpu.gpr[rt] = t;
    // update xer
    if ((a == 0xffffffff) && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    return OK;
  }

  extern "C" PseudoStatus ppc_addze_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_addze.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + ca ;
    proc.cpu.gpr[rt] = t;
    // update xer
    if ((a == 0xffffffff) && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    ppc_update_cr0(proc, rt);
    return OK;
  }

 /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addzeo(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_addzeo\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + ca ;
    proc.cpu.gpr[rt] = t;
    // update xer
    if ((a == 0xffffffff) && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    if((a ^~ ca) & ((a ^ t)) << 31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    return OK;
  }

  extern "C" PseudoStatus ppc_addzeo_(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_addzeo.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    const uint32_t t = a + ca ;
    proc.cpu.gpr[rt] = t;
    // update xer
    if ((a == 0xffffffff) && ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    if((a ^~ ca) & (a ^ t) << 31)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addic(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_addic\n";
    const uint32_t ra_content = proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] = ra_content + d;
    // update XER
    if (proc.cpu.gpr[rt] < ra_content)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    return OK;
  }

  extern "C" PseudoStatus ppc_addic_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_addic.\n";
    const uint32_t ra_content = proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] = ra_content + d;
    // update XER
    if (proc.cpu.gpr[rt] < ra_content)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    // update cr0 flags
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addo(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_addo\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t t = a+b;
    proc.cpu.gpr[rt] = t;
    if ((a^~b)&(a^t)>>31)
      proc.cpu.xer |= (XER_SO | XER_OV); // set OV and SO
    else
      proc.cpu.xer &= ~XER_OV;//remain so bits.
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addo_(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_addo.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t t = a+b;
    proc.cpu.gpr[rt] = t;
    if ((a^~b)&(a^t)>>31)
      proc.cpu.xer |= (XER_SO | XER_OV); // set OV and SO
    else
      proc.cpu.xer &= ~XER_OV;//remain so bits.
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_and(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_and\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] &  proc.cpu.gpr[rb];
    return OK;
  }

  extern "C" PseudoStatus ppc_and_(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_and.\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] &  proc.cpu.gpr[rb];

    // update cr0 flags
    ppc_update_cr0(proc, ra);
    return OK;
  }


  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_andc(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_andc\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] & ~ proc.cpu.gpr[rb];
    return OK;
  }

  extern "C" PseudoStatus ppc_andc_(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_andc.\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] &  ~proc.cpu.gpr[rb];

    // update cr0 flags
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_andi_(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_andi.\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] & d;

    // update cr0 flags
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_andis_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_andis.\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] & (d << 16);

    // update cr0 flags
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_cmp(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_cmp\n";
    const int32_t a = proc.cpu.gpr[ra];
    const int32_t b = proc.cpu.gpr[rb];
    uint32_t c, bf;

    bf = rt >> 2;
    if (a < b)
      c = 8;
    else if (a > b)
      c = 4;
    else
      c = 2;

    if (proc.cpu.xer & XER_SO)
      c |= 1;

    proc.cpu.cr &= ppc_cmp_and_mask[bf];
    proc.cpu.cr |= c<<((7 - bf)*4);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_cmpl(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_cmpl\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];

    uint32_t c, bf;

    bf = rt >> 2;
    if (a < b)
      c = 8;
    else if (a > b)
      c = 4;
    else
      c = 2;

    if (proc.cpu.xer & XER_SO)
      c |= 1;

    proc.cpu.cr &= ppc_cmp_and_mask[bf];
    proc.cpu.cr |= c<<((7 - bf)*4);

    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_cmpli(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_cmpli\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = d;
    uint32_t c, bf;

    bf = rt >> 2;
    if (a < b)
      c = 8;
    else if (a > b)
      c = 4;
    else
      c = 2;

    if (proc.cpu.xer & XER_SO)
      c |= 1;

    proc.cpu.cr &= ppc_cmp_and_mask[bf];
    proc.cpu.cr |= c<<((7 - bf)*4);
    return OK;
  }


  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_cntlzd(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_cntlzd\n";
    TODO("cntlzd");;

    return OK;
  }

  extern "C" PseudoStatus ppc_cntlzd_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_cntlzd.\n";
    TODO("cntlzd_");;

    return OK;
  }


 /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_cntlzw(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_cntlzw\n";
     uint32_t n = 0;
     uint32_t x = 0x80000000;
     uint32_t v = proc.cpu.gpr[rt];
    while (!(v & x)) {
      n++;
      if (n == 32)
        break;
      x >>= 1;
    }

    proc.cpu.gpr[ra] = n;

    return OK;
  }

  extern "C" PseudoStatus ppc_cntlzw_(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_cntlzw.\n";
    uint32_t n = 0;
    uint32_t x = 0x80000000;
    uint32_t v = proc.cpu.gpr[rt];
    while (!(v & x)) {
      n++;
      if (n == 32)
        break;
      x >>= 1;
    }

    proc.cpu.gpr[ra] = n;
    ppc_update_cr0(proc, ra);

    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_crand(PPC_Processor &proc,
                                    uint8_t bt, uint8_t ba, uint8_t bb) {
    proc.debug() <<"ppcpi_crand\n";
    if ((proc.cpu.cr & (1<<(31-ba))) && (proc.cpu.cr & (1<<(31-bb))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_crandc(PPC_Processor &proc,
                                     uint8_t bt, uint8_t ba, uint8_t bb) {
    proc.debug() <<"ppcpi_crandc\n";
    if ((proc.cpu.cr & (1<<(31-ba))) && !(proc.cpu.cr & (1<<(31-bb))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    return OK;
  }


  /*--------------------------------------------------------------------------*/
  extern "C"  PseudoStatus ppc_creqv(PPC_Processor &proc,
                                     uint8_t bt, uint8_t ba, uint8_t bb) {
    proc.debug() <<"ppcpi_creqv\n";
    if (((proc.cpu.cr & (1<<(31-ba))) && (proc.cpu.cr & (1<<(31-bb))))
        || (!(proc.cpu.cr & (1<<(31-ba))) && !(proc.cpu.cr & (1<<(31-bb)))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_crnand(PPC_Processor &proc,
                                    uint8_t bt, uint8_t ba, uint8_t bb) {
    proc.debug() <<"ppcpi_crnand\n";
    if ( !((proc.cpu.cr & (1<<(31-ba))) && (proc.cpu.cr & (1<<(31-bb)))) )
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_crnor(PPC_Processor &proc,
                                    uint8_t bt, uint8_t ba, uint8_t bb) {
    proc.debug() <<"ppcpi_crnor\n";
    if ( !((proc.cpu.cr & (1<<(31-ba))) | (proc.cpu.cr & (1<<(31-bb)))) )
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_cror(PPC_Processor &proc,
                                   uint8_t bt, uint8_t ba, uint8_t bb) {
    proc.debug() <<"ppcpi_cror\n";
    if ( ((proc.cpu.cr & (1<<(31-ba))) | (proc.cpu.cr & (1<<(31-bb)))) )
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_crorc(PPC_Processor &proc,
                                    uint8_t bt, uint8_t ba, uint8_t bb) {
    proc.debug() <<"ppcpi_crorc\n";
    if ((proc.cpu.cr & (1<<(31-ba))) || !(proc.cpu.cr & (1<<(31-bb))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));

    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_crxor(PPC_Processor &proc,
                                    uint8_t bt, uint8_t ba, uint8_t bb) {
    proc.debug() <<"ppcpi_crxor\n";
    if ((!(proc.cpu.cr & (1<<(31-ba))) && (proc.cpu.cr & (1<<(31-bb))))
        || ((proc.cpu.cr & (1<<(31-ba))) && !(proc.cpu.cr & (1<<(31-bb)))))
      proc.cpu.cr |= (1<<(31-bt));
    else
      proc.cpu.cr &= ~(1<<(31-bt));
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_divd(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_divd\n";
    TODO("divd");
    return OK;
  }

  extern "C" PseudoStatus ppc_divd_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_divd.\n";
    TODO("divd.");
    return OK;
  }

  extern "C" PseudoStatus ppc_divdo(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_divdo\n";
    TODO("divdo");
    return OK;
  }

  extern "C" PseudoStatus ppc_divdo_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_divdo.\n";
    TODO("divdo_");
    return OK;
  }

/*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_divdu(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_divdu\n";
    TODO("divdu");
    return OK;
  }

  extern "C" PseudoStatus ppc_divdu_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_divdu.\n";
    TODO("divdu.");
    return OK;
  }

  extern "C" PseudoStatus ppc_divduo(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_divduo\n";
    TODO("divduo");
    return OK;
  }

  extern "C" PseudoStatus ppc_divduo_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_divduo.\n";
    TODO("divduo_");
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_divw(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_divw\n";
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    int32_t a = proc.cpu.gpr[ra];
    int32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = a / b;

    return OK;
  }

  extern "C" PseudoStatus ppc_divw_(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_divw.\n";
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    int32_t a = proc.cpu.gpr[ra];
    int32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = a / b;
    ppc_update_cr0(proc, rt);
    return OK;
  }

 /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_divwo(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_divwo\n";
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    int32_t a = proc.cpu.gpr[ra];
    int32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = a / b;
    if(((a == 1<<31) && b==-1) || b==0)
    proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
   else
    proc.cpu.xer &= ~XER_OV;
    return OK;
  }

  extern "C" PseudoStatus ppc_divwo_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_divwo.\n";
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    int32_t a = proc.cpu.gpr[ra];
    int32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = a / b;
    if(((a == 1<<31) && b==-1) || b==0)
    proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
   else
    proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }


/*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_divwu(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_divwu\n";
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] / proc.cpu.gpr[rb];
    return OK;
  }

  extern "C" PseudoStatus ppc_divwu_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_divwu.\n";
    if (!proc.cpu.gpr[rb]) {
      error()<<"div instruction invalid!\n";
    }

    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] / proc.cpu.gpr[rb];
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_divwuo(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_divwuo\n";
    uint32_t b = proc.cpu.gpr[rb];
    if (!b) {
      error()<<"div instruction invalid!\n";
    }

    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] / b;
    if(b==0)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    return OK;
  }

  extern "C" PseudoStatus ppc_divwuo_(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_divwuo.\n";
    uint32_t b = proc.cpu.gpr[rb];
    if (!b) {
      error()<<"div instruction invalid!\n";
    }

    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] / b;
    if(b==0)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_dcbf(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_dcbf\n";
    //TODO("dcbf");
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_dcbst(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_dcbst\n";
    //TODO("dcbst");
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_dcbt(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_dcbt\n";
    //TODO("dcbt");
    return OK;
  }

   /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_dcbtst(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_dcbtst\n";
    //TODO("dcbtst");
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_dcbz_ra0(PPC_Processor &proc,
                                       uint8_t rb) {
    proc.debug() <<"ppcpi_dcbz_ra0\n";
    //PPC_L1_CACHE_LINE_SIZE=32
    uint32_t addr = proc.cpu.gpr[rb];
    assert((addr&0x3) == 0);
    for(int i = 0; i < 8; i++)
      proc.mmu.write_word(addr+i*4, 0);

    return OK;
  }

  extern "C" PseudoStatus ppc_dcbz_raS(PPC_Processor &proc,
                                       uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_dcbz_raS\n";
    //PPC_L1_CACHE_LINE_SIZE=32
    uint32_t addr = proc.cpu.gpr[ra] +  proc.cpu.gpr[rb];
    assert((addr&0x3) == 0);
    for(int i = 0; i < 8; i++)
      proc.mmu.write_word(addr+i*4, 0);

    return OK;
  }

  /*--------------------------------------------------------------------------*/

  extern "C" PseudoStatus ppc_eqv(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_eqv\n";
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] ^ proc.cpu.gpr[rb]);
    return OK;
  }

  extern "C" PseudoStatus ppc_eqv_(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_eqv.\n";
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] ^ proc.cpu.gpr[rb]);
    ppc_update_cr0(proc, ra);
    return OK;
  }

   /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_extsb(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_extsb\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    if (proc.cpu.gpr[ra] & 0x80)
      proc.cpu.gpr[ra] |= 0xffffff00;
    else
      proc.cpu.gpr[ra] &= ~0xffffff00;
    return OK;
  }

  extern "C" PseudoStatus ppc_extsb_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_extsb.\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    if (proc.cpu.gpr[ra] & 0x80)
      proc.cpu.gpr[ra] |= 0xffffff00;
    else
      proc.cpu.gpr[ra] &= ~0xffffff00;
    ppc_update_cr0(proc, ra);
    return OK;
  }

   /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_extsh(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_extsh\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    if (proc.cpu.gpr[ra] & 0x8000)
      proc.cpu.gpr[ra] |= 0xffff0000;
    else
      proc.cpu.gpr[ra] &= ~0xffff0000;
    return OK;
  }

  extern "C" PseudoStatus ppc_extsh_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_extsh.\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    if (proc.cpu.gpr[ra] & 0x8000)
      proc.cpu.gpr[ra] |= 0xffff0000;
    else
      proc.cpu.gpr[ra] &= ~0xffff0000;
    ppc_update_cr0(proc, ra);
    return OK;
  }

 /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_extsw(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_extsw\n";
    TODO("extsw");
    return OK;
  }

  extern "C" PseudoStatus ppc_extsw_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_extsw.\n";
    TODO("extsw_");
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stwu(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_stwu\n";
    const uint32_t addr = proc.cpu.gpr[ra] + d;
    if ((addr&0x3) == 0) { //word valignment
      proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
    } else {
      uint32_t data = proc.cpu.gpr[rt];
      for (int i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }
    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stw_ra0(PPC_Processor &proc,
                                      uint8_t rt,  uint32_t d) {
    proc.debug() <<"ppcpi_stw_ra0\n";
    uint32_t addr = d;
    if ((addr & 0x3) == 0) { //word valignment
      proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
    } else {
      int i;
      uint32_t data = proc.cpu.gpr[rt];
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_stw_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_stw_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + d;
    if ((addr & 0x3) == 0) { //word valignment
      proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
    } else {
      int i;
      uint32_t data = proc.cpu.gpr[rt];
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stwbrx_ra0(PPC_Processor &proc,
                                         uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_stwbrx_ra0\n";
     uint32_t addr = proc.cpu.gpr[rb];
    if((addr&0x3) == 0){ //word valignment
      proc.mmu.write_word(addr, word_be_le_translate(proc.cpu.gpr[rt]));
    } else {
      int i;
      uint32_t data = word_be_le_translate(proc.cpu.gpr[rt]);
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_stwbrx_raS(PPC_Processor &proc,
                                         uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stwbrx_raS\n";
     uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    if((addr&0x3) == 0){ //word valignment
      proc.mmu.write_word(addr, word_be_le_translate(proc.cpu.gpr[rt]));
    } else {
      int i;
      uint32_t data = word_be_le_translate(proc.cpu.gpr[rt]);
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stwcx__ra0(PPC_Processor &proc,
                                         uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_stwcx._ra0\n";
    uint32_t v, addr;
    proc.cpu.cr &= 0x0fffffff;
    if (proc.cpu.have_reservation) {
      proc.cpu.have_reservation = false;
      addr = proc.cpu.gpr[rb];

      assert((addr&0x3) == 0);
      v = proc.mmu.read_word(addr);

      if (v == proc.cpu.reserve) {
        proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
        proc.cpu.cr |= CR_CR0_EQ;
      } else
        proc.cpu.cr &= ~CR_CR0_EQ;

      if (proc.cpu.xer & XER_SO) {
        proc.cpu.cr |= CR_CR0_SO;
      }
    }

    return OK;
  }

  extern "C" PseudoStatus ppc_stwcx__raS(PPC_Processor &proc,
                                         uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stwcx._raS\n";
    uint32_t v, addr;
    proc.cpu.cr &= 0x0fffffff;
    if (proc.cpu.have_reservation) {
      proc.cpu.have_reservation = false;
      addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

      assert((addr&0x3) == 0);
      v = proc.mmu.read_word(addr);

      if (v == proc.cpu.reserve) {
        proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
        proc.cpu.cr |= CR_CR0_EQ;
      } else
        proc.cpu.cr &= ~CR_CR0_EQ;

      if (proc.cpu.xer & XER_SO) {
        proc.cpu.cr |= CR_CR0_SO;
      }
    }

    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stwux(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stwux\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
    } else {
      int i;
      uint32_t data = proc.cpu.gpr[rt];
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }

    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stwx_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_stwx_ra0\n";
    uint32_t addr = proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
    } else {
      int i;
      uint32_t data = proc.cpu.gpr[rt];
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }

    return OK;
  }

  extern "C" PseudoStatus ppc_stwx_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stwx_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.mmu.write_word(addr, proc.cpu.gpr[rt]);
    } else {
      int i;
      uint32_t data = proc.cpu.gpr[rt];
      for(i = 0; i < 4; i++, data <<= 8) {
        proc.mmu.write_byte(addr+i, (uint8_t)(data>>24));
      }
    }

    return OK;
  }
  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_dss(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_dss\n";
    TODO("dss");
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_std(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_std\n";
    TODO("std");
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stdcx_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_stdcx_\n";
    TODO("stdcx_");
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stdu(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_stdu\n";
    TODO("stdu");
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C"PseudoStatus ppc_stdux(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_stdux\n";
    TODO("stdux");
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stdx(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_stdx\n";
    TODO("stdx");
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stfd_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_stfd_ra0\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = d;//d is already sign extended
    proc.mmu.write_double(addr,proc.cpu.fpr[rt]);

    //for debug
    double dbl = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<<dbl<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  extern "C" PseudoStatus ppc_stfd_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_stfd_raS\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extended
    proc.mmu.write_double(addr,proc.cpu.fpr[rt]);

    //for debug
    double dbl = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< dbl<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stfdu(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_stfdu\n";
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"instruction form with ra =0 is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extended
    proc.mmu.write_double(addr,proc.cpu.fpr[rt]);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double dbl = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< dbl<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stfdux(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stfdux\n";
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"instruction form with ra =0 is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb] ;
    proc.mmu.write_double(addr,proc.cpu.fpr[rt]);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stfdx_ra0(PPC_Processor &proc,
                                        uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_stfdx_ra0\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[rb] ;
    proc.mmu.write_double(addr,proc.cpu.fpr[rt]);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  extern "C" PseudoStatus ppc_stfdx_raS(PPC_Processor &proc,
                                        uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stfdx_raS\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[ra]+ proc.cpu.gpr[rb] ;
    proc.mmu.write_double(addr,proc.cpu.fpr[rt]);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stfiwx_ra0(PPC_Processor &proc,
                                         uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_stfiwx_ra0\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[rb] ;
    proc.mmu.write_word(addr, (uint32_t) proc.cpu.fpr[rt]);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  extern "C" PseudoStatus ppc_stfiwx_raS(PPC_Processor &proc,
                                         uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stfiwx_raS\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb] ;
    proc.mmu.write_word(addr, (uint32_t) proc.cpu.fpr[rt]);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"store :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C"PseudoStatus ppc_stfs_ra0(PPC_Processor &proc,
                                      uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_stfs_ra0\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = d;//d is already sign extended
    uint32_t data = fp_t::single_format(proc.cpu.fpr[rt]);
    proc.mmu.write_word(addr, data);

    //for debug
    float f = *reinterpret_cast<float*>(&data);
    debug()<<"store :"<< f<<" ["<<hex<<data<<"]"<<endl;
    return OK;
  }

  extern "C" PseudoStatus ppc_stfs_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_stfs_raS\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extended
    uint32_t data = fp_t::single_format(proc.cpu.fpr[rt]);
    proc.mmu.write_word(addr, data);

    //for debug
    float f = *reinterpret_cast<float*>(&data);
    debug()<<"store :"<< f<<" ["<<hex<<data<<"]"<<endl;
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stfsu(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_stfsu\n";
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"instruction form with ra=0 is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extended
    uint32_t data = fp_t::single_format(proc.cpu.fpr[rt]);
    proc.mmu.write_word(addr, data);
    proc.cpu.gpr[ra] = addr;

    //for debug
    float f = *reinterpret_cast<float*>(&data);
    debug()<<"store :"<< f<<" ["<<hex<<data<<"]"<<endl;

    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stfsux(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stfsux\n";
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"instruction form with ra=0 is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    uint32_t data = fp_t::single_format(proc.cpu.fpr[rt]);
    proc.mmu.write_word(addr,data);
    proc.cpu.gpr[ra] = addr;

    //for debug
    float f = *reinterpret_cast<float*>(&data);
    debug()<<"store :"<< f<<" ["<<hex<<data<<"]"<<endl;
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stfsx_ra0(PPC_Processor &proc,
                                        uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stfsx_ra0\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[rb];
    uint32_t data = fp_t::single_format(proc.cpu.fpr[rt]);
    proc.mmu.write_word(addr,data);
    proc.cpu.gpr[ra] = addr;

    //for debug
    float f = *reinterpret_cast<float*>(&data);
    debug()<<"store :"<< f<<" ["<<hex<<data<<"]"<<endl;

    return OK;
  }

  extern "C" PseudoStatus ppc_stfsx_raS(PPC_Processor &proc,
                                        uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stfsx_raS\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    uint32_t data = fp_t::single_format(proc.cpu.fpr[rt]);
    proc.mmu.write_word(addr,data);
    proc.cpu.gpr[ra] = addr;

    //for debug
    float f = *reinterpret_cast<float*>(&data);
    debug()<<"store :"<< f<<" ["<<hex<<data<<"]"<<endl;

    return OK;
  }

  /*----------------------------------------------------------------------------*/

  extern "C" PseudoStatus ppc_mfspr(PPC_Processor &proc,
                         uint8_t rt, uint16_t spr) {
    proc.debug() <<"ppcpi_mfspr\n";
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

    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtcrf(PPC_Processor &proc,
                                    uint8_t rt, uint16_t spr) {
    proc.debug() <<"ppcpi_mtcrf\n";
    uint32_t tmp, tmp1 = (spr >> 1) & 0xff;
    tmp =  ((tmp1 & 0x80) ? 0xf0000000 : 0) | ((tmp1 & 0x40) ? 0x0f000000 : 0)
      | ((tmp1 & 0x20) ? 0x00f00000 : 0) | ((tmp1 & 0x10) ? 0x000f0000 : 0)
      | ((tmp1 & 0x08) ? 0x0000f000 : 0) | ((tmp1 & 0x04) ? 0x00000f00 : 0)
      | ((tmp1 & 0x02) ? 0x000000f0 : 0) | ((tmp1 & 0x01) ? 0x0000000f : 0);
    proc.cpu.cr = (proc.cpu.gpr[rt] & tmp) | (proc.cpu.cr & ~tmp);
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mfcr(PPC_Processor &proc,
                                   uint8_t rt) {
    proc.debug() <<"ppcpi_mfcr\n";
    proc.cpu.gpr[rt] = proc.cpu.cr;
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mfmsr(PPC_Processor &proc,
                                    uint8_t rt) {
    proc.debug() <<"ppcpi_mfmsr\n";
    proc.cpu.gpr[rt] = proc.cpu.msr;
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mfsr(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_mfsr\n";
    proc.cpu.gpr[rt] = proc.cpu.sr[ra & 0xf];
    return OK;
  }

  /*------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_mftb(PPC_Processor &proc,
                                  uint8_t rt, uint16_t spr) {
    proc.debug() <<"ppcpi_mftb\n";
    proc.cpu.tbr.tbr = proc.cpu.ptbr;
    uint16_t n = ((spr & 0x1f) << 5) | ((spr >> 5) & 0x1f);
    if(n == 268)
      proc.cpu.gpr[rt]= proc.cpu.tbr._tbr[0];
    else if(n == 269)
      proc.cpu.gpr[rt]= proc.cpu.tbr._tbr[1];
    else {
      cout<<"ppcpi_mftb error : "<<n<<hex<<" spr : "<<spr<<endl;
      exit(-1);
    }
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mfsrin(PPC_Processor &proc,
                                     uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_mfsrin\n";
    proc.cpu.gpr[rt] = proc.cpu.sr[proc.cpu.gpr[rb] >> 28];
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mcrf(PPC_Processor &proc,
                                   uint8_t bt, uint8_t ba) {
    proc.debug() <<"ppcpi_mcrf\n";
    int bf = bt >> 2;
    int bfa = ba >> 2;
    bf = 7-bf;
    bfa = 7-bfa;
    uint32_t c = (proc.cpu.cr>>(bfa*4)) & 0xf;
    proc.cpu.cr &= ppc_cmp_and_mask[bf];
    proc.cpu.cr |= c<<(bf*4);

    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mcrfs(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_mcrfs\n";
    proc.fp_unit.check_fp_enabled();
    uint8_t crfD = rt>>2;
    uint8_t crfS = ra>>2;
    uint8_t value = proc.fp_unit.fpscr.move_field_to_cr(crfS);
    proc.cpu.update_CR_field(crfD,value);
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mcrxr(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mcrxr\n";
    TODO("mcrxr");
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mfocrf(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mfocrf\n";
    TODO("mfocrf");
    return OK;
  }

   /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mffs(PPC_Processor &proc,
                                   uint8_t rt) {
    proc.debug() <<"ppcpi_mffs\n";
    proc.fp_unit.check_fp_enabled();
    proc.cpu.fpr[rt] = proc.fp_unit.fpscr.get_value();
    return OK;
  }

   /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mffs_(PPC_Processor &proc,
                                    uint8_t rt) {
    proc.debug() <<"ppcpi_mffs.\n";
    proc.fp_unit.check_fp_enabled();
    proc.cpu.fpr[rt] = proc.fp_unit.fpscr.get_value();
    proc.fp_unit.update_CR1();
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtmsr(PPC_Processor &proc,
                                    uint8_t rt) {
    proc.debug() <<"ppcpi_mtmsr\n";
    proc.cpu.msr = proc.cpu.gpr[rt];
    proc.signal();
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtmsrd(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mtmsrd\n";
    TODO("mtmsrd");
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtsr(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_mtsr\n";
    proc.cpu.sr[ra & 0xf] = proc.cpu.gpr[rt];
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtsrin(PPC_Processor &proc,
                                     uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_mtsrin\n";
    proc.cpu.sr[proc.cpu.gpr[rb] >> 28] = proc.cpu.gpr[rt];
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtocrf(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mtocrf\n";
    TODO("mtocrf");
    return OK;
  }


  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtfsb0(PPC_Processor &proc,
                                     uint8_t rt) {
    proc.debug() <<"ppcpi_mtfsb0\n";
    proc.fp_unit.check_fp_enabled();
    proc.fp_unit.fpscr.set_bit(rt,false);
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtfsb0_(PPC_Processor &proc,
                                      uint8_t rt) {
    proc.debug() <<"ppcpi_mtfsb0.\n";
    proc.fp_unit.check_fp_enabled();
    proc.fp_unit.fpscr.set_bit(rt,false);
    proc.fp_unit.update_CR1();
    return OK;
  }

   /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtfsb1(PPC_Processor &proc,
                                     uint8_t rt) {
    proc.debug() <<"ppcpi_mtfsb1\n";
    proc.fp_unit.check_fp_enabled();
    proc.fp_unit.fpscr.set_bit(rt,true);
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtfsb1_(PPC_Processor &proc,
                                      uint8_t rt) {
    proc.debug() <<"ppcpi_mtfsb1.\n";
    proc.fp_unit.check_fp_enabled();
    proc.fp_unit.fpscr.set_bit(rt,true);
    proc.fp_unit.update_CR1();
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtfsf(PPC_Processor &proc,
                                    uint8_t flm, uint8_t frb) {
    proc.debug() <<"ppcpi_mtfsf\n";
    uint32_t value = (uint32_t)proc.cpu.fpr[frb];
    for(int8_t field=7;field>=0;field--){
      if(flm & (0x1<<(7-field))){
        proc.fp_unit.fpscr.set_field(field,value&0xf);
      }
      value = value >> 4;
    }
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtfsf_(PPC_Processor &proc,
                                     uint8_t flm, uint8_t frb) {
    proc.debug() <<"ppcpi_mtfsf.\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t value = (uint32_t)proc.cpu.fpr[frb];
    for(int8_t field=7;field>=0;field--){
      if(flm & (0x1<<(7-field))){
        proc.fp_unit.fpscr.set_field(field,value&0xf);
        value = value >> 4;
      }
    }
    proc.fp_unit.update_CR1();
    return OK;
  }


  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtfsfi(PPC_Processor &proc,
                                     uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_mtfsfi\n";
    proc.fp_unit.check_fp_enabled();
    uint8_t crfD = rt>>2;
    uint8_t imm = rb>>1;
    proc.fp_unit.fpscr.set_field(crfD,imm);
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtfsfi_(PPC_Processor &proc,
                                      uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_mtfsfi.\n";
    proc.fp_unit.check_fp_enabled();
    uint8_t crfD = rt>>2;
    uint8_t imm = rb>>1;
    proc.fp_unit.fpscr.set_field(crfD,imm);
    proc.fp_unit.update_CR1();
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_rfi(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rfi\n";
    //todo interrupt
    if(check_MSR_PR(proc.cpu.msr))
      proc.interrupt(INT_PROGRAM, PPC_EXC_PROGRAM_PRIV);
    proc.cpu.msr = proc.cpu.srr[1] & 0xff73;//todo...
    proc.signal();
    proc.cpu.pc = proc.cpu.srr[0] & (~3);
    return BRANCH;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_or(PPC_Processor &proc,
                                 uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_or\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | proc.cpu.gpr[rb];
    return OK;
  }

  extern "C" PseudoStatus ppc_or_(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_or.\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | proc.cpu.gpr[rb];
    ppc_update_cr0(proc, ra);
    return OK;
  }

 /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_orc(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_orc\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | ~ proc.cpu.gpr[rb];
    return OK;
  }

  extern "C" PseudoStatus ppc_orc_(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_orc.\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | ~ proc.cpu.gpr[rb];
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_bl(PPC_Processor &proc,
                                 uint32_t li) {
    proc.debug() <<"ppcpi_bl\n";
    proc.cpu.lr = proc.cpu.pc + 4;
    proc.cpu.pc += li;
    return BRANCH;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_ba(PPC_Processor &proc,
                                 uint32_t li) {
    proc.debug() <<"ppcpi_ba\n";
    proc.cpu.pc = li;
    return BRANCH;
  }
  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_bla(PPC_Processor &proc,
                                  uint32_t li) {
    proc.debug() <<"ppcpi_bla\n";
    proc.cpu.lr = proc.cpu.pc + 4;
    proc.cpu.pc = li;
    return BRANCH;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_ld(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_ld\n";
    TODO("ld");
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_ldarx(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_ldarx\n";
    TODO("ldarx");
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_ldu(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_ldu\n";
    TODO("ldu");
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_ldux(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_ldux\n";
    TODO("ldux");
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_ldx(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_ldx\n";
    TODO("ldx");
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lfd_ra0(PPC_Processor &proc,
                                      uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_lfd_ra0\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = d;//d is already sign extended
    proc.cpu.fpr[rt] = proc.mmu.read_double(addr);

    //for debug
    double dbl = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< dbl<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  extern "C" PseudoStatus ppc_lfd_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lfd_raS\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extended
    proc.cpu.fpr[rt] = proc.mmu.read_double(addr);

    //for debug
    double dbl = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< dbl<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lfdu(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra,  uint32_t d) {
    proc.debug() <<"ppcpi_lfdu\n";
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"rA=0,instruction form is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extended
    proc.cpu.fpr[rt] = proc.mmu.read_double(addr);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double dbl = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< dbl<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lfdux(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lfdux\n";
    proc.fp_unit.check_fp_enabled();
    if(ra==0){
      error()<<"rA=0,instruction form is invalid"<<endl;
      exit(1);
    }
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    proc.cpu.fpr[rt] = proc.mmu.read_double(addr);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;
    return OK;
  }

   /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lfdx_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lfdx_ra0\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr =  proc.cpu.gpr[rb];
    proc.cpu.fpr[rt] = proc.mmu.read_double(addr);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  extern "C" PseudoStatus ppc_lfdx_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lfdx_raS\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    proc.cpu.fpr[rt] = proc.mmu.read_double(addr);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

 /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lfs_ra0(PPC_Processor &proc,
                                      uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_lfs_ra0\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = d;//d is already sign extened
    uint32_t single_format = proc.mmu.read_word(addr);
    proc.cpu.fpr[rt] = fp_t::double_format(single_format);

    //for debug
    double dbl = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< dbl<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  extern "C" PseudoStatus ppc_lfs_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lfs_raS\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extened
    uint32_t single_format = proc.mmu.read_word(addr);
    proc.cpu.fpr[rt] = fp_t::double_format(single_format);

    //for debug
    double dbl = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< dbl<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lfsu(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lfsu\n";
    proc.fp_unit.check_fp_enabled();
    if(ra==0)
      {
        error()<<"instruction form with ra=0 is invalid"<<endl;
        exit(1);
      }
    uint32_t addr = proc.cpu.gpr[ra] + d;//d is already sign extened
    uint32_t single_format = proc.mmu.read_word(addr);
    proc.cpu.fpr[rt] = fp_t::double_format(single_format);
    proc.cpu.gpr[ra] = addr;

    //for debug
    double dbl = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< dbl<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

      return OK;
    }

  /*------------------------------------------------------------------------*/
    extern "C" PseudoStatus ppc_lfsux(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint8_t rb) {
      proc.debug() <<"ppcpi_lfsux\n";
      proc.fp_unit.check_fp_enabled();
      if(ra==0)
        {
          error()<<"instruction form with ra=0 is invalid"<<endl;
          exit(1);
        }
      uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
      uint32_t single_format = proc.mmu.read_word(addr);
      proc.cpu.fpr[rt] = fp_t::double_format(single_format);
      proc.cpu.gpr[ra] = addr;

      //for debug
      double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
      debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

      return OK;
    }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lfsx_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lfsx_ra0\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[rb];
    uint32_t single_format = proc.mmu.read_word(addr);
    proc.cpu.fpr[rt] = fp_t::double_format(single_format);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  extern "C" PseudoStatus ppc_lfsx_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lfsx_raS\n";
    proc.fp_unit.check_fp_enabled();
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    uint32_t single_format = proc.mmu.read_word(addr);
    proc.cpu.fpr[rt] = fp_t::double_format(single_format);

    //for debug
    double d = *reinterpret_cast<double*>(&proc.cpu.fpr[rt]);
    debug()<<"load :"<< d<<" ["<<hex<<proc.cpu.fpr[rt]<<"]"<<endl;

    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lwz_ra0(PPC_Processor &proc,
                                      uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_lwz_ra0\n";
    const uint32_t addr =  d;
    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_lwz_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lwz_raS\n";
    const uint32_t addr = proc.cpu.gpr[ra] + d;
    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }
    return OK;
  }

  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lwzu(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lwzu\n";
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.gpr[ra] = addr;
    return OK;
  }

   /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lwzux(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lwzux\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.gpr[ra] = addr;
    return OK;
  }

/*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lwzx_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lwzux_ra0\n";
    uint32_t addr = proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    return OK;
  }

  extern "C" PseudoStatus ppc_lwzx_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lwzux_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    return OK;
  }
  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_neg(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_neg\n";
    proc.cpu.gpr[rt] = -proc.cpu.gpr[ra];
    return OK;
  }

  extern "C" PseudoStatus ppc_neg_(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_neg.\n";
    proc.cpu.gpr[rt] = -proc.cpu.gpr[ra];
    ppc_update_cr0(proc, rt);
    return OK;
  }

  extern "C" PseudoStatus ppc_nego(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_nego\n";
    const uint32_t a=proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] = -a;
    if (a == 0x80000000)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    return OK;
  }

  extern "C" PseudoStatus ppc_nego_(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_nego.\n";
    const uint32_t a=proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] = -a;
    if (a == 0x80000000)
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }
  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_cmpi(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_cmpi\n";
    const int32_t a = proc.cpu.gpr[ra];
    const int32_t b = d;
    uint32_t c, bf;

    bf = rt >> 2;
    if (a < b)
      c = 8;
    else if (a > b)
      c = 4;
    else
      c = 2;

    if (proc.cpu.xer & XER_SO)
      c |= 1;

    proc.cpu.cr &= ppc_cmp_and_mask[bf];
    proc.cpu.cr |= c<<((7 - bf)*4);
    return OK;
  }
  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_bc_bo00_bo20(PPC_Processor &proc,
                                          uint8_t  bo, uint8_t bi, uint32_t bd) {
    proc.debug() <<"ppcpi_bc_bo00_bo20\n";
    proc.cpu.ctr--;

    bool bo2 = (bo & 2);
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));

    if ((((proc.cpu.ctr != 0) ^ bo2)) && ( (!(cr ^ bo8)))) {
      proc.cpu.pc += bd;
      return BRANCH;
    } else
      return OK;
  }


  extern "C" PseudoStatus ppc_bc_bo01_bo21(PPC_Processor &proc,
                                           uint32_t bd) {
    proc.debug() <<"ppcpi_bc_bo01_bo21\n";

    proc.cpu.pc += bd;

    return BRANCH;
  }

  extern "C" PseudoStatus ppc_bc_bo01_bo20(PPC_Processor &proc,
                                           uint8_t  bo, uint32_t bd) {
    proc.debug() <<"ppcpi_bc_bo10_bo20\n";
    proc.cpu.ctr--;

    bool bo2 = (bo & 2);

    if ((proc.cpu.ctr != 0) ^ bo2) {
      proc.cpu.pc += bd;
      return BRANCH;
    } else
    return OK;
  }

  extern "C" PseudoStatus ppc_bc_bo00_bo21(PPC_Processor &proc,
                                           uint8_t  bo, uint8_t bi, uint32_t bd) {
    proc.debug() <<"ppcpi_bc_bo00_bo21\n";
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));
    if (!(cr ^ bo8)) {
      proc.cpu.pc += bd;
      return BRANCH;
    } else
    return OK;
  }

  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_bca_bo00_bo20(PPC_Processor &proc,
                                            uint8_t  bo, uint8_t bi, uint32_t bd) {
    proc.debug() <<"ppcpi_bca_bo00_bo20\n";
    proc.cpu.ctr--;

    bool bo2 = (bo & 2);
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));

    if ((((proc.cpu.ctr != 0) ^ bo2)) && ( (!(cr ^ bo8)))) {
      proc.cpu.pc = bd;
      return BRANCH;
    } else
      return OK;
  }


  extern "C" PseudoStatus ppc_bca_bo01_bo21(PPC_Processor &proc,
                                            uint32_t bd) {
    proc.debug() <<"ppcpi_bca_bo01_bo21\n";

    proc.cpu.pc = bd;

    return OK;
  }

  extern "C" PseudoStatus ppc_bca_bo01_bo20(PPC_Processor &proc,
                                            uint8_t  bo, uint32_t bd) {
    proc.debug() <<"ppcpi_bca_bo10_bo20\n";
    proc.cpu.ctr--;

    bool bo2 = (bo & 2);

    if ((proc.cpu.ctr != 0) ^ bo2)
      proc.cpu.pc = bd;

    return OK;
  }

  extern "C" PseudoStatus ppc_bca_bo00_bo21(PPC_Processor &proc,
                                            uint8_t  bo, uint8_t bi, uint32_t bd) {
    proc.debug() <<"ppcpi_bca_bo00_bo21\n";
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));

    if (!(cr ^ bo8)) {
      proc.cpu.pc = bd;
      return BRANCH;
    } else
      return OK;
  }

  /*-----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_bcl_bo00_bo20(PPC_Processor &proc,
                                            uint8_t  bo, uint8_t bi, uint32_t bd) {
    proc.debug() <<"ppcpi_bcl_bo00_bo20\n";
    proc.cpu.ctr--;
    proc.cpu.lr = proc.cpu.pc + 4;
    bool bo2 = (bo & 2);
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));

    if ((((proc.cpu.ctr != 0) ^ bo2)) && ( (!(cr ^ bo8)))) {
      proc.cpu.pc += bd;
      return BRANCH;
    } else
      return OK;
  }

  extern "C" PseudoStatus ppc_bcl_bo01_bo21(PPC_Processor &proc,
                                            uint32_t bd) {
    proc.debug() <<"ppcpi_bcl_bo01_bo21\n";
    proc.cpu.lr = proc.cpu.pc + 4;
    proc.cpu.pc += bd;

    return BRANCH;
  }

  extern "C" PseudoStatus ppc_bcl_bo01_bo20(PPC_Processor &proc,
                                            uint8_t  bo, uint32_t bd) {
    proc.debug() <<"ppcpi_bcl_bo10_bo20\n";
    proc.cpu.ctr--;
    proc.cpu.lr = proc.cpu.pc + 4;
    bool bo2 = (bo & 2);

    if ((proc.cpu.ctr != 0) ^ bo2) {
      proc.cpu.pc += bd;
      return BRANCH;
    } else
      return OK;
  }

  extern "C" PseudoStatus ppc_bcl_bo00_bo21(PPC_Processor &proc,
                                            uint8_t  bo, uint8_t bi, uint32_t bd) {
    proc.debug() <<"ppcpi_bcl_bo00_bo21\n";
    proc.cpu.lr = proc.cpu.pc + 4;
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));

    if (!(cr ^ bo8)) {
      proc.cpu.pc += bd;
      return BRANCH;
    } else
      return OK;
  }

  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_bcla_bo00_bo20(PPC_Processor &proc,
                                             uint8_t  bo, uint8_t bi, uint32_t bd) {
    proc.debug() <<"ppcpi_bcla_bo00_bo20\n";
    proc.cpu.ctr--;
    proc.cpu.lr = proc.cpu.pc + 4;
    bool bo2 = (bo & 2);
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));

    if ((((proc.cpu.ctr != 0) ^ bo2)) && ( (!(cr ^ bo8)))) {
      proc.cpu.pc = bd;
      return BRANCH;
    } else
      return OK;
  }

  extern "C" PseudoStatus ppc_bcla_bo01_bo21(PPC_Processor &proc,
                                             uint32_t bd) {
    proc.debug() <<"ppcpi_bcla_bo01_bo21\n";
    proc.cpu.lr = proc.cpu.pc + 4;
    proc.cpu.pc = bd;

    return BRANCH;
  }

  extern "C" PseudoStatus ppc_bcla_bo01_bo20(PPC_Processor &proc,
                                             uint8_t  bo, uint32_t bd) {
    proc.debug() <<"ppcpi_bcla_bo10_bo20\n";
    proc.cpu.ctr--;
    proc.cpu.lr = proc.cpu.pc + 4;
    bool bo2 = (bo & 2);

    if ((proc.cpu.ctr != 0) ^ bo2) {
      proc.cpu.pc = bd;
      return BRANCH;
    } else
      return OK;
  }

  extern "C" PseudoStatus ppc_bcla_bo00_bo21(PPC_Processor &proc,
                                             uint8_t bo, uint8_t bi, uint32_t bd) {
    proc.debug() <<"ppcpi_bcla_bo00_bo21\n";
    proc.cpu.lr = proc.cpu.pc + 4;
    bool bo8 = (bo & 8);
    bool cr = (proc.cpu.cr & (1<<(31-bi)));

    if (!(cr ^ bo8)) {
      proc.cpu.pc = bd;
      return BRANCH;
    } else
      return OK;
  }

  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_bcctr_bo00(PPC_Processor &proc,
                                         uint8_t bt, uint8_t ba) {
    proc.debug() <<"ppcpi_bcctr_bo00\n";
    bool bt8 = (bt & 8);
    bool cr = (proc.cpu.cr & (1<<(31-ba)));

    if (!(cr ^ bt8)){
      proc.cpu.pc = proc.cpu.ctr & 0xfffffffc;
    return BRANCH;
    }else
    return OK;
  }

  extern "C" PseudoStatus ppc_bcctr_bo01(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_bcctr_bo01\n";
    proc.cpu.pc = proc.cpu.ctr & 0xfffffffc;
    return BRANCH;
  }

  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_bcctrl_bo00(PPC_Processor &proc,
                                          uint8_t bt, uint8_t ba) {
    proc.debug() <<"ppcpi_bcctrl_bo00\n";
    bool bt8 = (bt & 8);
    bool cr = (proc.cpu.cr & (1<<(31-ba)));
    proc.cpu.lr = proc.cpu.pc + 4;
    if (!(cr ^ bt8)){
      proc.cpu.pc = proc.cpu.ctr & 0xfffffffc;
    return BRANCH;
    }else
    return OK;
  }

  extern "C" PseudoStatus ppc_bcctrl_bo01(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_bcctrl_bo01\n";
    proc.cpu.lr = proc.cpu.pc + 4;
    proc.cpu.pc = proc.cpu.ctr & 0xfffffffc;
    return BRANCH;
  }

  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addis_ra0(PPC_Processor &proc,
                                        uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_addis_ra0\n";
    proc.cpu.gpr[rt] = d << 16;
    return OK;
  }

  extern "C" PseudoStatus ppc_addis_raS(PPC_Processor &proc,
                                        uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_addis_raS\n";
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] + (d << 16);
    return OK;
  }


  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_ori(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_ori\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | d;
    return OK;
  }

  /*-------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_oris(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_oris\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] | (d << 16);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_addi_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_addi_ra0\n";
    proc.cpu.gpr[rt] = d;
    return OK;
  }

  extern "C" PseudoStatus ppc_addi_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_addi_raS\n";
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] + d;
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stb_ra0(PPC_Processor &proc,
                                      uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_stb_ra0\n";
    const uint32_t addr = d;
    proc.mmu.write_byte(addr, (uint8_t) proc.cpu.gpr[rt]);
    return OK;
  }

  extern "C" PseudoStatus ppc_stb_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_stb_raS\n";
    const uint32_t addr = proc.cpu.gpr[ra] + d;
    proc.mmu.write_byte(addr, (uint8_t) proc.cpu.gpr[rt]);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_stbu(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_stbu\n";
    const uint32_t addr = proc.cpu.gpr[ra] + d;
    proc.mmu.write_byte(addr, (uint8_t) proc.cpu.gpr[rt]);
    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*----------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_stbux(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stbux\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    proc.mmu.write_byte(addr, (uint8_t) proc.cpu.gpr[rt]);
    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*----------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_stbx_ra0(PPC_Processor &proc,
                                      uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_stbx_ra0\n";
    uint32_t addr = proc.cpu.gpr[rb];
    proc.mmu.write_byte(addr, (uint8_t) proc.cpu.gpr[rt]);
    return OK;
  }

 extern "C" PseudoStatus ppc_stbx_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_stbx_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    proc.mmu.write_byte(addr, (uint8_t) proc.cpu.gpr[rt]);
    return OK;
  }

  /*----------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_sth_ra0(PPC_Processor &proc,
                                     uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_sth_ra0\n";
    uint32_t addr = d;

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, (uint16_t)proc.cpu.gpr[rt]);
    } else {
      proc.mmu.write_byte(addr, (uint8_t)(proc.cpu.gpr[rt]>>8));
      proc.mmu.write_byte(addr+1, (uint8_t)proc.cpu.gpr[rt]);
    }

    return OK;
  }

  extern "C" PseudoStatus ppc_sth_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_sth_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, (uint16_t)proc.cpu.gpr[rt]);
    } else {
      proc.mmu.write_byte(addr, (uint8_t)(proc.cpu.gpr[rt]>>8));
      proc.mmu.write_byte(addr+1, (uint8_t)proc.cpu.gpr[rt]);
    }

    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_sthbrx_ra0(PPC_Processor &proc,
                                         uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_sthbrx_ra0\n";
    uint32_t addr = proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, half_be_le_translate((uint16_t) proc.cpu.gpr[rt]));
    } else {
      proc.mmu.write_byte(addr, (uint8_t)proc.cpu.gpr[rt]);
      proc.mmu.write_byte(addr+1, (uint8_t)(proc.cpu.gpr[rt]>>8));
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_sthbrx_raS(PPC_Processor &proc,
                                         uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_sthbrx_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, half_be_le_translate((uint16_t) proc.cpu.gpr[rt]));
    } else {
      proc.mmu.write_byte(addr, (uint8_t)proc.cpu.gpr[rt]);
      proc.mmu.write_byte(addr+1, (uint8_t)(proc.cpu.gpr[rt]>>8));
    }
    return OK;
  }

 /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_sthu(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_sthu\n";
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, (uint16_t)proc.cpu.gpr[rt]);
    } else {
      proc.mmu.write_byte(addr, (uint8_t)(proc.cpu.gpr[rt]>>8));
      proc.mmu.write_byte(addr+1, (uint8_t)proc.cpu.gpr[rt]);
    }

    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_sthux(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_sthux\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, (uint16_t)proc.cpu.gpr[rt]);
    } else {
      proc.mmu.write_byte(addr, (uint8_t)(proc.cpu.gpr[rt]>>8));
      proc.mmu.write_byte(addr+1, (uint8_t)proc.cpu.gpr[rt]);
    }

    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_sthx_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_sthx_ra0\n";
    uint32_t addr = proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, (uint16_t)proc.cpu.gpr[rt]);
    } else {
      proc.mmu.write_byte(addr, (uint8_t)(proc.cpu.gpr[rt]>>8));
      proc.mmu.write_byte(addr+1, (uint8_t)proc.cpu.gpr[rt]);
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_sthx_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_sthx_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.mmu.write_half(addr, (uint16_t)proc.cpu.gpr[rt]);
    } else {
      proc.mmu.write_byte(addr, (uint8_t)(proc.cpu.gpr[rt]>>8));
      proc.mmu.write_byte(addr+1, (uint8_t)proc.cpu.gpr[rt]);
    }
    return OK;
  }

  /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stmw_ra0(PPC_Processor &proc,
                                       uint8_t rt,  uint32_t d) {
    proc.debug() <<"ppcpi_stmw_ra0\n";
    uint32_t addr =  d;
    uint32_t r;//tmp;
    for(r = rt; r <= 31; r++){
      //tmp = word_be_le_translate(proc.cpu.gpr[r]);
      proc.mmu.write_word(addr, proc.cpu.gpr[r]);
      addr +=4;
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_stmw_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra,  uint32_t d) {
    proc.debug() <<"ppcpi_stmw_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + d;
    uint32_t r;//tmp;
    for(r = rt; r <= 31; r++){
      //tmp = word_be_le_translate(proc.cpu.gpr[r]);
      proc.mmu.write_word(addr, proc.cpu.gpr[r]);
      addr +=4;
    }
    return OK;
  }

   /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stswi_ra0(PPC_Processor &proc,
                                        uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_stswi_ra0\n";
    uint32_t addr = 0;
    uint32_t r = 0, tmp_rt = rt;
    int i;
    uint8_t nb = rb;
    if (nb==0)
      nb = 32;

    for (i = 0; nb > 0; i--, nb--) {
      if (!i) {
        r = proc.cpu.gpr[tmp_rt];
        tmp_rt++;
        tmp_rt%=32;
        i = 4;
      }
      proc.mmu.write_byte(addr, r>>24);
      r<<=8;
      addr++;
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_stswi_raS(PPC_Processor &proc,
                                        uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_stswi_raS\n";
    uint32_t addr = proc.cpu.gpr[ra];
    uint32_t r = 0, tmp_rt = rt;
    int i;
    uint8_t nb = rb;
    if (nb==0)
      nb = 32;

    for (i = 0; nb > 0; i--, nb--) {
      if (!i) {
        r = proc.cpu.gpr[tmp_rt];
        tmp_rt++;
        tmp_rt%=32;
        i = 4;
      }
      proc.mmu.write_byte(addr, r>>24);
      r<<=8;
      addr++;
    }
    return OK;
  }


   /*----------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_stswx_ra0(PPC_Processor &proc,
                                        uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_stswx_ra0\n";
    uint32_t addr = proc.cpu.gpr[rb];
    int i=0;
    uint32_t r = rt-1;
    uint32_t temp = 0;
    int nb = XER_n(proc.cpu.xer);
    while(nb>0) {
      if (i == 0){
          r++;
          r%=32;
          temp = proc.cpu.gpr[r];
        }
      proc.mmu.write_byte(addr,(uint8_t)(temp>>(24-i)));
      addr++;
      i += 8;
      if(i==32) i=0;
      nb--;
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_stswx_raS(PPC_Processor &proc,
                                        uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_stswx_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    int i=0;
    uint32_t r = rt-1;
    uint32_t temp = 0;
    int nb = XER_n(proc.cpu.xer);
    while(nb>0) {
      if (i == 0){
          r++;
          r%=32;
          temp = proc.cpu.gpr[r];
        }
      proc.mmu.write_byte(addr,(uint8_t)(temp>>(24-i)));
      addr++;
      i += 8;
      if(i==32) i=0;
      nb--;
    }
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mtspr(PPC_Processor &proc,
                         uint8_t rt, uint16_t spr) {
    proc.debug() <<"ppcpi_mtspr\n";

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
    return OK;
  }

  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_bclr_bo00_bo20(PPC_Processor &proc,
                                             uint8_t bt, uint8_t ba) {
    proc.debug() <<"ppcpi_bclr_bo00_bo20\n";
    proc.cpu.ctr--;
    const uint32_t  tmp = proc.cpu.lr;
    bool bo2 = (bt & 2);
    bool bo8 = (bt & 8);
    bool cr = (proc.cpu.cr & (1<<(31-ba)));

    if ((((proc.cpu.ctr != 0) ^ bo2)) && ( (!(cr ^ bo8)))) {
      proc.cpu.pc = tmp & 0xfffffffc;
      return BRANCH;
    } else
      return OK;
  }

  extern "C" PseudoStatus ppc_bclr_bo01_bo21(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_bclr_bo01_bo21\n";
    const uint32_t  tmp = proc.cpu.lr;
    proc.cpu.pc = tmp & 0xfffffffc;
    return BRANCH;
  }

  extern "C" PseudoStatus ppc_bclr_bo01_bo20(PPC_Processor &proc,
                                             uint8_t bt) {
    proc.debug() <<"ppcpi_bclr_bo10_bo20\n";
    proc.cpu.ctr--;
    const uint32_t  tmp = proc.cpu.lr;
    bool bo2 = (bt & 2);

    if ((proc.cpu.ctr != 0) ^ bo2) {
      proc.cpu.pc = tmp & 0xfffffffc;
      return BRANCH;
    } else
      return OK;
  }

  extern "C" PseudoStatus ppc_bclr_bo00_bo21(PPC_Processor &proc,
                                             uint8_t bt, uint8_t ba) {
    proc.debug() <<"ppcpi_bclr_bo00_bo21\n";
    bool bo8 = (bt & 8);
    bool cr = (proc.cpu.cr & (1<<(31-ba)));
    const uint32_t  tmp = proc.cpu.lr;
    if (!(cr ^ bo8)) {
      proc.cpu.pc = tmp & 0xfffffffc;
      return BRANCH;
    } else
      return OK;
  }

  /*-------------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_bclrl_bo00_bo20(PPC_Processor &proc,
                                              uint8_t bt, uint8_t ba) {
    proc.debug() <<"ppcpi_bclrl_bo00_bo20\n";
    proc.cpu.ctr--;
    const uint32_t  tmp = proc.cpu.lr;
    bool bo2 = (bt & 2);
    bool bo8 = (bt & 8);
    bool cr = (proc.cpu.cr & (1<<(31-ba)));
    proc.cpu.lr = proc.cpu.pc + 4;

    if ((((proc.cpu.ctr != 0) ^ bo2)) && ( (!(cr ^ bo8)))) {
      proc.cpu.pc = tmp & 0xfffffffc;
      return BRANCH;
    } else
      return OK;
  }

  extern "C" PseudoStatus ppc_bclrl_bo01_bo21(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_bclrl_bo01_bo21\n";
    const uint32_t  tmp = proc.cpu.lr;
    proc.cpu.lr = proc.cpu.pc + 4;
    proc.cpu.pc = tmp & 0xfffffffc;
    return BRANCH;
  }

  extern "C" PseudoStatus ppc_bclrl_bo01_bo20(PPC_Processor &proc,
                                              uint8_t bt) {
    proc.debug() <<"ppcpi_bclrl_bo10_bo20\n";
    proc.cpu.ctr--;
    const uint32_t  tmp = proc.cpu.lr;
    bool bo2 = (bt & 2);
    proc.cpu.lr = proc.cpu.pc + 4;
    if ((proc.cpu.ctr != 0) ^ bo2) {
      proc.cpu.pc = tmp & 0xfffffffc;
      return BRANCH;
    } else
      return OK;
  }

  extern "C" PseudoStatus ppc_bclrl_bo00_bo21(PPC_Processor &proc,
                                              uint8_t bt, uint8_t ba) {
    proc.debug() <<"ppcpi_bclrl_bo00_bo21\n";
    bool bo8 = (bt & 8);
    bool cr = (proc.cpu.cr & (1<<(31-ba)));
    const uint32_t  tmp = proc.cpu.lr;
    proc.cpu.lr = proc.cpu.pc + 4;
    if (!(cr ^ bo8)) {
      proc.cpu.pc = tmp & 0xfffffffc;
      return BRANCH;
    } else
      return OK;
  }

  /*---------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_b(PPC_Processor &proc,
                                uint32_t li) {
    proc.debug() <<"ppcpi_b\n";
    proc.cpu.pc += li;
    return BRANCH;
  }

  /*---------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_eciwx(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_eciwx\n";
    TODO("eciwx");
    return OK;
  }

  /*---------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_ecowx(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_ecowx\n";
    TODO("ecowx");
    return OK;
  }

  /*---------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_eieio(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_eieio\n";
    TODO("eieio");
    return OK;
  }

  /*---------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_icbi(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_icbi\n";
    TODO("icbi");
    return OK;
  }

  /*---------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_isync(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_isync\n";
    TODO("isync");
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lbz_ra0(PPC_Processor &proc,
                                      uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_lbz_ra0\n";
    const uint32_t addr = d;
    proc.cpu.gpr[rt] = (uint32_t) proc.mmu.read_byte(addr);
    return OK;
  }

  extern "C" PseudoStatus ppc_lbz_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lbz_raS\n";
    const uint32_t addr = proc.cpu.gpr[ra] + d;
    proc.cpu.gpr[rt] = (uint32_t) proc.mmu.read_byte(addr);
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lbzu(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lbzu\n";
    const uint32_t addr = proc.cpu.gpr[ra] +  d;
    proc.cpu.gpr[rt] = (uint32_t) proc.mmu.read_byte(addr);
    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lbzux(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lbzux\n";
    const uint32_t addr = proc.cpu.gpr[ra] +  proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = (uint32_t) proc.mmu.read_byte(addr);
    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lbzx_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lbzx_ra0\n";
    const uint32_t addr =  proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = (uint32_t) proc.mmu.read_byte(addr);
    return OK;
  }

  extern "C" PseudoStatus ppc_lbzx_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lbzx_raS\n";
    const uint32_t addr = proc.cpu.gpr[ra] +  proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = (uint32_t) proc.mmu.read_byte(addr);
    return OK;
  }

  /*-------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_rldcl(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldcl\n";
    TODO("rldcl");
    return OK;
  }

  extern "C" PseudoStatus ppc_rldcl_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldcl_\n";
    TODO("rldcl_");
    return OK;
  }

  /*-------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_rldcr(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldcr\n";
    TODO("rldcr");
    return OK;
  }

 extern "C" PseudoStatus ppc_rldcr_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldcr_\n";
    TODO("rldcr_");
    return OK;
  }

  /*-------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_rldic(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldic\n";
    TODO("rldic");
    return OK;
  }

 extern "C" PseudoStatus ppc_rldic_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldic.\n";
    TODO("rldic_");
    return OK;
  }

  /*-------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_rldicl(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldicl\n";
    TODO("rldicl");
    return OK;
  }

 extern "C" PseudoStatus ppc_rldicl_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldicl.\n";
    TODO("rldicl_");
    return OK;
  }

  /*-------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_rldicr(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldicr\n";
    TODO("rldicr");
    return OK;
  }

  extern "C" PseudoStatus ppc_rldicr_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldicr.\n";
    TODO("rldicr_");
    return OK;
  }

  /*-------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_rldimi(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldimi\n";
    TODO("rldimi");
    return OK;
  }

  extern "C" PseudoStatus ppc_rldimi_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_rldimi.\n";
    TODO("rldimi_");
    return OK;
  }

  /*-------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_rlwimi(PPC_Processor &proc,
                                     uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb, uint8_t me) {
    proc.debug() <<"ppcpi_rlwimi\n";
    const uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs],rb);
    const uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = (v & mask) | (proc.cpu.gpr[ra] & ~mask);
    return OK;
  }

  extern "C" PseudoStatus ppc_rlwimi_(PPC_Processor &proc,
                                      uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb, uint8_t me) {
    proc.debug() <<"ppcpi_rlwimi.\n";
    const uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs],rb);
    const uint32_t mask = ppc_mask(mb, me);
   proc.cpu.gpr[ra] = (v & mask) | (proc.cpu.gpr[ra] & ~mask);
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*-------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_rlwinm(PPC_Processor &proc,
                                     uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb, uint8_t me) {
    proc.debug() <<"ppcpi_rlwinm\n";
    const uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs],rb);
    const uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = v & mask;
    return OK;
  }

  extern "C" PseudoStatus ppc_rlwinm_(PPC_Processor &proc,
                                      uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb, uint8_t me) {
    proc.debug() <<"ppcpi_rlwinm.\n";
    const uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs],rb);
    const uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = v & mask;
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*-------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_rlwnm(PPC_Processor &proc,
                                    uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb, uint8_t me) {
    proc.debug() <<"ppcpi_rlwnm\n";
    const uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs],proc.cpu.gpr[rb]);
    const uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = v & mask;
    return OK;
  }

  extern "C" PseudoStatus ppc_rlwnm_(PPC_Processor &proc,
                                     uint8_t rs, uint8_t ra, uint8_t rb, uint8_t mb, uint8_t me) {
    proc.debug() <<"ppcpi_rlwnm.\n";
    const uint32_t v = ppc_word_rotl(proc.cpu.gpr[rs],proc.cpu.gpr[rb]);
    const uint32_t mask = ppc_mask(mb, me);
    proc.cpu.gpr[ra] = v & mask;
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*----------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_sc(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_sc\n";
    proc.set_something_pending();
    proc.set_it_pending ();
    proc.trap_exception = true;
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_subf(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subf\n";
    proc.cpu.gpr[rt] = ~proc.cpu.gpr[ra] + proc.cpu.gpr[rb] + 1;
    return OK;
  }

  extern "C" PseudoStatus ppc_subf_(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subf.\n";
    proc.cpu.gpr[rt] = ~proc.cpu.gpr[ra] + proc.cpu.gpr[rb] + 1;
    ppc_update_cr0(proc, rt);
    return OK;
  }

  extern "C" PseudoStatus ppc_subfo(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subfo\n";
    const uint32_t a=proc.cpu.gpr[ra];
    const uint32_t b=proc.cpu.gpr[rb];
    const uint32_t  c = ~a + b + 1;
    proc.cpu.gpr[rt] =c ;
    if((b^a)&(b^c)>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    return OK;
  }

  extern "C" PseudoStatus ppc_subfo_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subfo.\n";
    const uint32_t a=proc.cpu.gpr[ra];
    const uint32_t b=proc.cpu.gpr[rb];
    const uint32_t  c = ~a + b + 1;
    proc.cpu.gpr[rt] =c ;
    if((b^a)&(b^c)>>31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_subfc(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subfc\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ~a + b + 1;
    // update xer
    if (ppc_carry(~a, b, 1))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    return OK;
  }

  extern "C" PseudoStatus ppc_subfc_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subfc.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ~a + b + 1;
    // update xer
    if (ppc_carry(~a, b, 1))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    ppc_update_cr0(proc, rt);

    return OK;
  }

  extern "C" PseudoStatus ppc_subfco(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subfco\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ~a + b + 1;
    // update xer
    if (ppc_carry(~a, b, 1))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    if((b ^ a) & (b^proc.cpu.gpr[rt]) >> 31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;

    return OK;
  }

  extern "C" PseudoStatus ppc_subfco_(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subfco.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = ~a + b + 1;
    // update xer
    if (ppc_carry(~a, b, 1))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((b ^ a) & (b ^ proc.cpu.gpr[rt]) >> 31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }


  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_subfe(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subfe\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + b + ca;
    // update xer
    if (ppc_carry(~a, b, ca))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    return OK;
  }

  extern "C" PseudoStatus ppc_subfe_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subfe.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + b + ca;
    // update xer
    if (ppc_carry(~a, b, ca))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    ppc_update_cr0(proc, rt);

    return OK;
  }

 extern "C" PseudoStatus ppc_subfeo(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subfeo\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + b + ca;
    // update xer
    if (ppc_carry(~a, b, ca))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((b ^ (a+ca)) & (b ^ proc.cpu.gpr[rt]) >> 31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;

    return OK;
  }

 extern "C" PseudoStatus ppc_subfeo_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_subfeo.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t b = proc.cpu.gpr[rb];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + b + ca;
    // update xer
    if (ppc_carry(~a, b, ca))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((b ^ (a+ca)) & (b ^ proc.cpu.gpr[rt]) >> 31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);

    return OK;
  }


  /*------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_subfme(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_subfme\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca + 0xffffffff;
    // update xer
    if ((a!=0xffffffff) || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    return OK;
  }

 extern "C" PseudoStatus ppc_subfme_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_subfme.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca + 0xffffffff;
    // update xer
    if ((a!=0xffffffff) || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    ppc_update_cr0(proc, rt);

    return OK;
  }

  /*------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_subfmeo(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_subfmeo\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca + 0xffffffff;
    // update xer
    if ((a!=0xffffffff) || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ca ^ (a + 0xffffffff)) & (ca ^ (proc.cpu.gpr[rt] + 1)) >> 31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;

    return OK;
  }

 extern "C" PseudoStatus ppc_subfmeo_(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_subfmeo.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca + 0xffffffff;
    // update xer
    if ((a!=0xffffffff) || ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ca ^ (a + 0xffffffff)) & (ca ^ (proc.cpu.gpr[rt] + 1)) >> 31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);

    return OK;
  }

  /*------------------------------------------------------------------------*/
 extern "C" PseudoStatus ppc_subfze(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_subfze\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca;
    // update xer
    if (!a & ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;

    return OK;
  }

 extern "C" PseudoStatus ppc_subfze_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_subfze_\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca;
    // update xer
    if (!a & ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
     ppc_update_cr0(proc, rt);
    return OK;
  }

  extern "C" PseudoStatus ppc_subfzeo(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_subfzeo\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca;
    // update xer
    if (!a & ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ca ^a ) & (ca ^ (proc.cpu.gpr[rt] + 1)) >> 31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;

    return OK;
  }

  extern "C" PseudoStatus ppc_subfzeo_(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra) {
    proc.debug() <<"ppcpi_subfzeo.\n";
    const uint32_t a = proc.cpu.gpr[ra];
    const uint32_t ca = ((proc.cpu.xer & XER_CA) ? 1 : 0);
    proc.cpu.gpr[rt] = ~a + ca;
    // update xer
    if (!a & ca)
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    if((ca ^a ) & (ca ^ (proc.cpu.gpr[rt] + 1)) >> 31)
      proc.cpu.xer |= (XER_SO | XER_OV);//FIXME
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_subfic(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_subfic\n";
    const uint32_t a = proc.cpu.gpr[ra];
    proc.cpu.gpr[rt] = ~a + d + 1;

    // update XER
    if (ppc_carry(~a, d, 1))
      proc.cpu.xer |= XER_CA;
    else
      proc.cpu.xer &= ~XER_CA;
    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_sld(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_sld\n";
    TODO("sld");

    return OK;
  }

  extern "C" PseudoStatus ppc_sld_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_sld.\n";
    TODO("sld_");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_slw(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_slw\n";
    uint32_t s = proc.cpu.gpr[rb] & 0x3f;
    if (s > 31)
      proc.cpu.gpr[ra] = 0;
    else
      proc.cpu.gpr[ra] = proc.cpu.gpr[rt] << s;
    return OK;
  }

  extern "C" PseudoStatus ppc_slw_(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_slw.\n";
    uint32_t s = proc.cpu.gpr[rb] & 0x3f;
    if (s > 31)
      proc.cpu.gpr[ra] = 0;
    else
      proc.cpu.gpr[ra] = proc.cpu.gpr[rt] << s;
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_slbia(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_slbia\n";
    TODO("slbia");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_slbie(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_slbie\n";
    TODO("slbie");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_slbmfee(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_slbmfee\n";
    TODO("slbmfee");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_slbmfev(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_slbmfev\n";
    TODO("slbmfev");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_slbmte(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_slbmte\n";
    TODO("slbmte");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_sync(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_sync\n";
    TODO("sync");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_td(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_td\n";
    TODO("td");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_tlbia(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_tlbia\n";
    TODO("tlbia");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_tlbie(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_tlbie\n";
    TODO("tlbie");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_tlbsync(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_tlbsync\n";
    TODO("tlbsync");

    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_tw(PPC_Processor &proc,
                                 uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_tw\n";
    if(proc.debugger() && rt==12 && ra==rb)
      proc.debugger()->notify(Debugger::EV_TRAP);
    else
      TODO("tw");
    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_twi(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_tw\n";
    uint32_t a = proc.cpu.gpr[ra];
    if (((rt & 16) && ((int32_t)a < (int32_t)d))
        || ((rt & 8) && ((int32_t)a > (int32_t)d))
        || ((rt & 4) && ((int32_t)a == (int32_t)d))
        || ((rt & 2) && ((uint32_t)a < (uint32_t)d))
        || ((rt & 1) && ((uint32_t)a > (uint32_t)d))) {
      proc.interrupt(INT_PROGRAM, PPC_EXC_PROGRAM_TRAP);
    }
    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_srd(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_srd\n";
    TODO("srd");
    return OK;
  }

  extern "C" PseudoStatus ppc_srd_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_srd.\n";
    TODO("srd_");
    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_srw(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_srw\n";
    uint32_t v = proc.cpu.gpr[rb] & 0x3f;
    if (v > 31)
      proc.cpu.gpr[ra] = 0;
    else
      proc.cpu.gpr[ra] = proc.cpu.gpr[rt] >> v;

    return OK;
  }

  extern "C" PseudoStatus ppc_srw_(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_srw.\n";
    uint32_t v = proc.cpu.gpr[rb] & 0x3f;
    if (v > 31)
      proc.cpu.gpr[ra] = 0;
    else
      proc.cpu.gpr[ra] = proc.cpu.gpr[rt] >> v;
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_srad(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_srad\n";
    TODO("srad");
    return OK;
  }

  extern "C" PseudoStatus ppc_srad_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_srad.\n";
    TODO("srad_");
    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_sradi(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_sradi\n";
    TODO("sradi");
    return OK;
  }

  extern "C" PseudoStatus ppc_sradi_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_sradi.\n";
    TODO("sradi_");
    return OK;
  }

  /*---------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_sraw(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_sraw\n";
    uint32_t SH = proc.cpu.gpr[rb] & 0x3f;
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    proc.cpu.xer &= ~XER_CA;
    if (proc.cpu.gpr[ra] & 0x80000000) {
      uint32_t ca = 0;
      for (uint32_t i = 0; i < SH; i++) {
        if (proc.cpu.gpr[ra] & 1)
          ca = 1;
        proc.cpu.gpr[ra] >>= 1;
        proc.cpu.gpr[ra] |= 0x80000000;
      }
      if (ca) proc.cpu.xer |= XER_CA;

    } else {
      if (SH > 31)
        proc.cpu.gpr[ra] = 0;
      else
        proc.cpu.gpr[ra] >>= SH;
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_sraw_(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_sraw.\n";
    uint32_t SH = proc.cpu.gpr[rb] & 0x3f;
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    proc.cpu.xer &= ~XER_CA;
    if (proc.cpu.gpr[ra] & 0x80000000) {
      uint32_t ca = 0;
      for (uint32_t i = 0; i < SH; i++) {
        if (proc.cpu.gpr[ra] & 1)
          ca = 1;
        proc.cpu.gpr[ra] >>= 1;
        proc.cpu.gpr[ra] |= 0x80000000;
      }
      if (ca) proc.cpu.xer |= XER_CA;

    } else {
      if (SH > 31)
        proc.cpu.gpr[ra] = 0;
      else
        proc.cpu.gpr[ra] >>= SH;
    }

    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_srawi(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_srawi\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    proc.cpu.xer &= ~XER_CA;
    if (proc.cpu.gpr[ra] & 0x80000000) {
      uint32_t ca = 0;
      for (uint32_t i = 0; i < rb; i++) {
        if (proc.cpu.gpr[ra] & 1)
          ca = 1;
        proc.cpu.gpr[ra] >>= 1;
        proc.cpu.gpr[ra] |= 0x80000000;
      }
      if (ca) proc.cpu.xer |= XER_CA;

    } else {
      if (rb > 31)
        proc.cpu.gpr[ra] = 0;
      else
        proc.cpu.gpr[ra] >>= rb;
    }

    return OK;
  }

  extern "C" PseudoStatus ppc_srawi_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_srawi.\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt];
    proc.cpu.xer &= ~XER_CA;
    if (proc.cpu.gpr[ra] & 0x80000000) {
      uint32_t ca = 0;
      for (uint32_t i = 0; i < rb; i++) {
        if (proc.cpu.gpr[ra] & 1)
          ca = 1;
        proc.cpu.gpr[ra] >>= 1;
        proc.cpu.gpr[ra] |= 0x80000000;
      }
      if (ca) proc.cpu.xer |= XER_CA;

    } else {
      if (rb > 31)
        proc.cpu.gpr[ra] = 0;
      else
        proc.cpu.gpr[ra] >>= rb;
    }
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_xor(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_xor\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] ^ proc.cpu.gpr[rb];
    return OK;
  }

  extern "C" PseudoStatus ppc_xor_(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_xor.\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] ^ proc.cpu.gpr[rb];
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*-------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_xori(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_xori\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] ^ d;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_xoris(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_xoris\n";
    proc.cpu.gpr[ra] = proc.cpu.gpr[rt] ^ ( d << 16);
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lha_ra0(PPC_Processor &proc,
                                      uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_lha_ra0\n";
    uint16_t r = 0;
    uint32_t addr = d;

    if((addr&0x1) == 0){ //half word valignment
      r = proc.mmu.read_half(addr);
    } else {
      r |= proc.mmu.read_byte(addr);
      r <<= 8;
      r |= proc.mmu.read_byte(addr+1);
    }

    proc.cpu.gpr[rt] = (r & 0x8000) ? (r |0x0ffff0000) : r;
    return OK;
  }

  extern "C" PseudoStatus ppc_lha_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lha_raS\n";
    uint16_t r = 0;
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x1) == 0){ //half word valignment
      r = proc.mmu.read_half(addr);
    } else {
      r |= proc.mmu.read_byte(addr);
      r <<= 8;
      r |= proc.mmu.read_byte(addr+1);
    }

    proc.cpu.gpr[rt] = (r & 0x8000) ? (r |0x0ffff0000) : r;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lhau(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lhau\n";
    uint16_t r =0;
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x1) == 0){ //half word valignment
      r = proc.mmu.read_half(addr);
    } else {
      r |= proc.mmu.read_byte(addr);
      r <<= 8;
      r |= proc.mmu.read_byte(addr+1);
    }

    proc.cpu.gpr[rt] = (r & 0x8000) ? (r |0x0ffff0000) : r;
    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lhaux(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lhaux\n";
    uint16_t r = 0;
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];
    if((addr&0x1) == 0){ //half word valignment
      r = proc.mmu.read_half(addr);
    } else {
      r |= proc.mmu.read_byte(addr);
      r <<= 8;
      r |= proc.mmu.read_byte(addr+1);
    }

    proc.cpu.gpr[rt] = (r & 0x8000) ? (r |0x0ffff0000) : r;
    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lhax_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lhax_ra0\n";
    uint16_t r = 0;
    uint32_t addr = proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      r = proc.mmu.read_half(addr);
    } else {
      r |= proc.mmu.read_byte(addr);
      r <<= 8;
      r |= proc.mmu.read_byte(addr+1);
    }

    proc.cpu.gpr[rt] = (r & 0x8000) ? (r |0x0ffff0000) : r;
    return OK;
  }

  extern "C" PseudoStatus ppc_lhax_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lhax_raS\n";
    uint16_t r = 0;
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      r = proc.mmu.read_half(addr);
    } else {
      r |= proc.mmu.read_byte(addr);
      r <<= 8;
      r |= proc.mmu.read_byte(addr+1);
    }

    proc.cpu.gpr[rt] = (r & 0x8000) ? (r |0x0ffff0000) : r;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lhbrx_ra0(PPC_Processor &proc,
                                        uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lhbrx_ra0\n";
    uint32_t addr = proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = half_be_le_translate(proc.mmu.read_half(addr));
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = half_be_le_translate(data);
    }

    return OK;
  }

  extern "C" PseudoStatus ppc_lhbrx_raS(PPC_Processor &proc,
                                        uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lhbrx_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = half_be_le_translate(proc.mmu.read_half(addr));
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = half_be_le_translate(data);
    }

    return OK;
  }

   /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lhz_ra0(PPC_Processor &proc,
                                      uint8_t rt, uint32_t d) {
    proc.debug() <<"ppcpi_lhz_ra0\n";
    uint32_t addr = d;

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_half(addr);
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = data;
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_lhz_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lhz_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_half(addr);
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = data;
    }
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lhzu(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lhzu\n";
    uint32_t addr = proc.cpu.gpr[ra] + d;

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_half(addr);
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lhzux(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lhzux\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_half(addr);
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.gpr[ra] = addr;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lhzx_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lhzx_ra0\n";
    uint32_t addr = proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_half(addr);
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = data;
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_lhzx_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lhzx_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x1) == 0){ //half word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_half(addr);
    } else {
      uint16_t data = 0;
      data |= proc.mmu.read_byte(addr);
      data <<= 8;
      data |= proc.mmu.read_byte(addr+1);
      proc.cpu.gpr[rt] = data;
    }
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lmw(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra, uint32_t d) {
    proc.debug() <<"ppcpi_lmw\n";
    uint32_t addr = proc.cpu.gpr[ra] + d;
    uint32_t r;
    for (r = rt; r <= 31; r++) {
      proc.cpu.gpr[r] = proc.mmu.read_word(addr);
      addr += 4;
    }
    return OK;
  }

   /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lswi_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lswi_ra0\n";
    uint32_t r = 0, tmp_rt = rt;
    int i;
    uint8_t tmp, nb = rb;
    uint32_t addr = 0;
    if (nb == 0)
      nb = 32;

    for (i = 4; nb > 0; nb--, i--) {
      if (!i) {
        i = 4;
        proc.cpu.gpr[tmp_rt] = r;
        tmp_rt++;
        tmp_rt %= 32;
        r = 0;
      }
      tmp = proc.mmu.read_byte(addr);
      r <<= 8;
      r |= tmp;
      addr++;
    }

    while (i) {
      r <<= 8;
      i--;
    }
    proc.cpu.gpr[tmp_rt] = r;
    return OK;
  }

  extern "C" PseudoStatus ppc_lswi_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra, uint8_t rb) {
    proc.debug() <<"ppcpi_lswi_raS\n";
    uint32_t r = 0, tmp_rt = rt;
    int i;
    uint8_t tmp, nb = rb;
    uint32_t addr = proc.cpu.gpr[ra];
    if (nb == 0)
      nb = 32;

    for (i = 4; nb > 0; nb--, i--) {
      if (!i) {
        i = 4;
        proc.cpu.gpr[tmp_rt] = r;
        tmp_rt++;
        tmp_rt %= 32;
        r = 0;
      }
      tmp = proc.mmu.read_byte(addr);
      r <<= 8;
      r |= tmp;
      addr++;
    }

    while (i) {
      r <<= 8;
      i--;
    }
    proc.cpu.gpr[tmp_rt] = r;
    return OK;
  }

   /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lswx_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lswx_ra0\n";
    uint32_t r = 0,tmp_rt = rt;
    int i;
    uint8_t tmp;
    uint32_t addr = proc.cpu.gpr[rb];
    int nb = XER_n(proc.cpu.xer);

    for (i = 4; nb > 0; nb--, i--) {
      if (!i) {
        i = 4;
        proc.cpu.gpr[tmp_rt] = r;
        tmp_rt++;
        tmp_rt %= 32;
        r = 0;
      }
      tmp = proc.mmu.read_byte(addr);
      r <<= 8;
      r |= tmp;
      addr++;
    }

    while (i) { //the unfilled loworder byte(s) of the register are set to 0
      r<<=8;
      i--;
    }
    proc.cpu.gpr[tmp_rt] = r;
    return OK;
  }

  extern "C" PseudoStatus ppc_lswx_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_lswx_raS\n";
    uint32_t r = 0, tmp_rt = rt;
    int i;
    uint8_t tmp;
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb] ;
    int nb = XER_n(proc.cpu.xer);

    for (i = 4; nb > 0; nb--, i--) {
      if (!i) {
        i = 4;
        proc.cpu.gpr[tmp_rt] = r;
        tmp_rt++;
        tmp_rt %= 32;
        r = 0;
      }
      tmp = proc.mmu.read_byte(addr);
      r <<= 8;
      r |= tmp;
      addr++;
    }

    while (i) { //the unfilled loworder byte(s) of the register are set to 0
      r<<=8;
      i--;
    }
    proc.cpu.gpr[tmp_rt] = r;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lwa_ra0(PPC_Processor &proc,
                                      uint8_t rt, uint32_t ds) {
    proc.debug() <<"ppcpi_lwa_ra0\n";
    uint32_t addr = ds;
    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }
    return OK;
  }

  extern "C" PseudoStatus ppc_lwa_raS(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra, uint32_t ds) {
    proc.debug() <<"ppcpi_lwa_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + ds;
    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lwarx_ra0(PPC_Processor &proc,
                                        uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lwarx_ra0\n";
    uint32_t v;
    uint32_t addr = proc.cpu.gpr[rb];

    assert((addr&0x3) == 0);
    v = proc.mmu.read_word(addr);

    proc.cpu.have_reservation= true;
    proc.cpu.reserve = v; //todo pa(addr)
    proc.cpu.gpr[rt] = v;
    return OK;
  }

  extern "C" PseudoStatus ppc_lwarx_raS(PPC_Processor &proc,
                                        uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_lwarx_raS\n";
    uint32_t v;
    uint32_t addr =  proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    assert((addr&0x3) == 0);
    v = proc.mmu.read_word(addr);

    proc.cpu.have_reservation= true;
    proc.cpu.reserve = v; //todo pa(addr)
    proc.cpu.gpr[rt] = v;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lwax_ra0(PPC_Processor &proc,
                                       uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lwax_ra0\n";
    uint32_t addr = proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    return OK;
  }

  extern "C" PseudoStatus ppc_lwax_raS(PPC_Processor &proc,
                                       uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_lwax_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    return OK;
  }
  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lwbrx_ra0(PPC_Processor &proc,
                                        uint8_t rt, uint8_t rb) {
    proc.debug() <<"ppcpi_lwbrx_ra0\n";
    uint32_t addr = proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = word_be_le_translate(proc.mmu.read_word(addr));
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = word_be_le_translate(data);
    }

    return OK;
  }

  extern "C" PseudoStatus ppc_lwbrx_raS(PPC_Processor &proc,
                                        uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_lwbrx_raS\n";
    uint32_t addr = proc.cpu.gpr[ra] + proc.cpu.gpr[rb];

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = word_be_le_translate(proc.mmu.read_word(addr));
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = word_be_le_translate(data);
    }

    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_lwaux(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_lwaux\n";
    uint32_t addr = proc.cpu.gpr[ra]  + proc.cpu.gpr[rb] ;

    if((addr&0x3) == 0){ //word valignment
      proc.cpu.gpr[rt] = proc.mmu.read_word(addr);
    } else {
      int i;
      uint32_t data = 0;
      for(i = 0; i < 3; i++, data <<= 8) {
        data |= proc.mmu.read_byte(addr+i);
      }
      data |= proc.mmu.read_byte(addr+i);
      proc.cpu.gpr[rt] = data;
    }

    proc.cpu.gpr[ra] = addr;

    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C"  PseudoStatus ppc_mulld(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mulld\n";
    TODO("mulld");
    return OK;
  }

  extern "C" PseudoStatus ppc_mulld_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mulld_\n";
    TODO("mulld_");
    return OK;
  }

   /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mulldo(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mulldo\n";
    TODO("mulldo");
    return OK;
  }

  extern "C" PseudoStatus ppc_mulldo_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mulldo_\n";
    TODO("mulld_");
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mulli(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra,  uint32_t d) {
    proc.debug() <<"ppcpi_mulli\n";
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] * d;
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mullw(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_mullw\n";
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] * proc.cpu.gpr[rb];
    return OK;
  }

  extern "C" PseudoStatus ppc_mullw_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_mullw.\n";
    proc.cpu.gpr[rt] = proc.cpu.gpr[ra] * proc.cpu.gpr[rb];
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mullwo(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_mullwo\n";
    int64_t temp = (int32_t)proc.cpu.gpr[ra] * (int32_t)proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = (uint32_t)temp;

    if(!(temp >> 31 == 0 || temp >> 31 == ~0ll ))
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    return OK;
  }

  extern "C" PseudoStatus ppc_mullwo_(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_mullwo.\n";
    int64_t temp = (int32_t)proc.cpu.gpr[ra] * (int32_t)proc.cpu.gpr[rb];
    proc.cpu.gpr[rt] = (uint32_t)temp;

    if(!(temp >> 31 == 0 || temp >> 31 == ~0ll ))
      proc.cpu.xer |= (XER_SO | XER_OV);
    else
      proc.cpu.xer &= ~XER_OV;
    ppc_update_cr0(proc, rt);
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mulhw(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_mulhw\n";
    const int64_t a = (int32_t)proc.cpu.gpr[ra];
    const int64_t b = (int32_t)proc.cpu.gpr[rb];
    int64_t c = a * b;
    proc.cpu.gpr[rt] = ((uint64_t) c) >> 32;

    return OK;
  }

  extern "C" PseudoStatus ppc_mulhw_(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_mulhw.\n";
    const int64_t a = (int32_t)proc.cpu.gpr[ra];
    const int64_t b = (int32_t)proc.cpu.gpr[rb];
    int64_t c = a * b;
    proc.cpu.gpr[rt] = ((uint64_t) c) >> 32;
    ppc_update_cr0(proc, rt);
    return OK;
  }


  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mulhwu(PPC_Processor &proc,
                                     uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_mulhwu\n";
    const uint64_t a = proc.cpu.gpr[ra];
    const uint64_t b = proc.cpu.gpr[rb];
    uint64_t c = a * b;
    proc.cpu.gpr[rt] =  c >> 32;

    return OK;
  }

  extern "C" PseudoStatus ppc_mulhwu_(PPC_Processor &proc,
                                      uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_mulhwu.\n";
    const uint64_t a = proc.cpu.gpr[ra];
    const uint64_t b = proc.cpu.gpr[rb];
    uint64_t c = a * b;
    proc.cpu.gpr[rt] =  c >> 32;
    ppc_update_cr0(proc, rt);

    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_mulhd(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mulhd\n";
    TODO("mulhd");
    return OK;
  }

  extern "C" PseudoStatus ppc_mulhd_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mulhd.\n";
    TODO("mulhd_");
    return OK;
  }

 extern "C" PseudoStatus ppc_mulhdu(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mulhdu\n";
    TODO("mulhdu");
    return OK;
  }

 extern "C" PseudoStatus ppc_mulhdu_(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_mulhdu.\n";
    TODO("mulhdu_");
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_nand(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_nand\n";
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] & proc.cpu.gpr[rb]);
    return OK;
  }

  extern "C" PseudoStatus ppc_nand_(PPC_Processor &proc,
                                    uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_nand.\n";
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] & proc.cpu.gpr[rb]);
    ppc_update_cr0(proc, ra);
    return OK;
  }

  /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_nor(PPC_Processor &proc,
                                  uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_nor\n";
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] | proc.cpu.gpr[rb]);
    return OK;
  }

  extern "C" PseudoStatus ppc_nor_(PPC_Processor &proc,
                                   uint8_t rt, uint8_t ra,  uint8_t rb) {
    proc.debug() <<"ppcpi_nor.\n";
    proc.cpu.gpr[ra] = ~(proc.cpu.gpr[rt] | proc.cpu.gpr[rb]);
    ppc_update_cr0(proc, ra);
    return OK;
  }

 /*--------------------------------------------------------------------------*/
  extern "C" PseudoStatus ppc_tdi(PPC_Processor &proc) {
    proc.debug() <<"ppcpi_tdi\n";
    TODO("tdi");
    return OK;
  }


} // namespace simsoc
