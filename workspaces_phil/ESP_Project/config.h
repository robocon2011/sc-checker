#ifndef CONFIG_H
#define CONFIG_

#include <systemc.h>
#include <scv.h>

#define INSTANCES_FULLADDER 32

/* later a level of print out should be realized */
enum rsmp_level_e{
  RSMP_SILENT       = 0,
  RSMP_ERROR_LEVEL   = 1,
  RSMP_WARNING_LEVEL = 2,
  RSMP_INFO_LEVEL    = 3,
  RSMP_DEBUG_LEVEL   = 4
};

#endif
