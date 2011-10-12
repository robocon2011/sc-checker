/* SimSoC-Cert, a library on processor architectures for embedded systems. */
/* See the COPYRIGHTS and LICENSE files. */

/* The modes of an ARM processor */

#include "slv6_mode.h"

BEGIN_SIMSOC_NAMESPACE

bool decode_mode(SLv6_Mode *mode, uint32_t x) {
  switch (x&0x1f) {
  case 0x11: *mode = fiq; return true;
  case 0x12: *mode = irq; return true;
  case 0x13: *mode = svc; return true;
  case 0x17: *mode = abt; return true;
  case 0x1b: *mode = und; return true;
  case 0x1f: *mode = sys; return true;
  case 0x10: *mode = usr; return true;
  default: return false;
  }
}

uint32_t encode_mode(SLv6_Mode mode) {
  switch (mode) {
  case fiq: return 0x11;
  case irq: return 0x12;
  case svc: return 0x13;
  case abt: return 0x17;
  case und: return 0x1b;
  case sys: return 0x1f;
  case usr: return 0x10;
  }
  abort();
}

const char *mode2string(SLv6_Mode mode) {
  switch (mode) {
  case fiq: return "fiq";
  case irq: return "irq";
  case svc: return "svc";
  case abt: return "abt";
  case und: return "und";
  case sys: return "sys";
  case usr: return "usr";
  }
  abort();
}

void slv6_print_mode(FILE *f, SLv6_Mode m) {
  fprintf(f,"%s",mode2string(m));
}

END_SIMSOC_NAMESPACE
