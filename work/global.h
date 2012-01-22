/******************************************************************************/
/*                                                                            */
/* Filename:    global.h                                                      */
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

#include <systemc.h>
#include <scv.h>
#include "packets.h"
#include "sp_ports.h"
#include "sp_channels.h"

#endif
