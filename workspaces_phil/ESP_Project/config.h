#ifndef CONFIG_H
#define CONFIG_

#include <systemc.h>
#include <scv.h>

#define INSTANCES_FULLADDER 32

/* later a level of print out should be realized */

/*class print_level{
public:
  enum print_level_e{
  RSMP_SILENT,
  RSMP_ERROR_LEVEL,
  RSMP_WARNING_LEVEL,
  RSMP_INFO_LEVEL,
  RSMP_DEBUG_LEVEL
  };
  typedef print_level_e print_level_t;

  print_level();

  int rsmp_printf(print_level_t level, char const* fmt, ...);
  int rsmp_error_printf(char const* fmt, ...);
  int rsmp_warning_printf(char const* fmt, ...);
  int rsmp_info_printf(char const* fmt, ...);
  int rsmp_debug_printf(char const* fmt, ...);

};


//rsmp_level_t rsmp_set_printf_level(rsmp_level_t level);
//rsmp_level_t rsmp_get_printf_level();

*/

#endif
