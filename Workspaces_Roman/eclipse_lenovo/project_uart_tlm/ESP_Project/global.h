/******************************************************************************/
/*                                                                            */
/* Filename:    sp_ports.cpp                                                  */
/*                                                                            */
/* Author:      Roman Sollböck, Philipp Maroschek                             */
/*                                                                            */
/* Tools:       Compiles with SystemC 2.2.v0                                  */
/*                                                                            */
/* Project:     SystemC Checker                                               */
/*                                                                            */
/* Topmodule:   ------                                                        */
/* Submodules:  ------                                                        */
/*                                                                            */
/******************************************************************************/

#ifndef GLOBAL_H
#define GLOBAL_H

/* Definition of the bitwidth of the fulladder design */
#ifndef BITWIDTH
#define BITWIDTH 32
#endif

/* Definition of the databits of the uart design */
#ifndef DATABITS
#define DATABITS 8
#endif

 /* DRIVER MONITOR DUT DETAIL DETAIL DETAIL */
#ifndef ESP_DL

/* set debug level for embedded system project */
#define ESP_DL         0x00

/* standard debug level - will be used for transaction recording and vc-dumps*/
#define DRIVER         0x01
#define DUT            0x04
#define MONITOR        0x10

/* print out some debug informations */
#define DRIVER_DETAIL  0x02
#define DUT_DETAIL     0x08
#define MONITOR_DETAIL 0x20

#endif

#include <systemc.h>
#include <scv.h>
#include "packets.h"
#include "sp_ports.h"
#include "sp_channels.h"

#endif
