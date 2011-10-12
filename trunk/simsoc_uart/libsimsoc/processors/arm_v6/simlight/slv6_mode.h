/* SimSoC-Cert, a library on processor architectures for embedded systems. */
/* See the COPYRIGHTS and LICENSE files. */

/* The modes of an ARM processor */

#ifndef SLV6_MODE_H
#define SLV6_MODE_H

#include "common.h"
#include <stdio.h>

BEGIN_SIMSOC_NAMESPACE

typedef enum {fiq, irq, svc, abt, und, sys, usr} SLv6_Mode;

extern bool decode_mode(SLv6_Mode*, uint32_t);
/* return false in case of invalid mode */

extern uint32_t encode_mode(SLv6_Mode);

extern const char *mode2string(SLv6_Mode);

extern void slv6_print_mode(FILE *f, SLv6_Mode m);

END_SIMSOC_NAMESPACE

#endif /* SLV6_MODE_H */
