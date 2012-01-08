#ifndef GLOBAL_H
#define GLOBAL_H

#ifndef BITWIDTH
#define BITWIDTH 32
#endif

#ifndef DATABITS
#define DATABITS 8
#endif

#ifndef ESP_DL
#define ESP_DL 0
#define DRIVER 1
#define MONITOR 2
#endif

#include <systemc.h>
#include <scv.h>
#include "packets.h"
#include "sp_ports.h"
#include "sp_channels.h"

#endif
