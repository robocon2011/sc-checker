/******************************************************************************/
/*                                                                            */
/* Filename:    global.h	                                                  */
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

#define SC_INCLUDE_DYNAMIC_PROCESSES


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

#define BASE_ADDR 0x00000000ff000000
#define LENGTH 0x80
#define DATABITS 8

#define MEMSIZE_UART 8u

#define SCOREBOARD_BASE_ADDR	0x00000000

#define UART_BASE_ADDR		0x00000000
#define UART_BYTE_OFFS_RX_REG	0x0000
#define UART_BYTE_OFFS_TX_REG	0x0004
#define UART_BYTE_OFFS_CTRL		0x0008

#define UART_CTRL_RESET			(1u << 0)
#define UART_CTRL_RX_ENABLE		(1u << 1)
#define UART_CTRL_ULD_RX_DATA	(1u << 2)
#define UART_CTRL_TX_ENABLE		(1u << 3)
#define UART_CTRL_LD_TX_DATA	(1u << 4)

#include <systemc.h>
#include <scv.h>
#include "packets.h"
#include "sp_ports.h"
#include "sp_channels.h"

#include <iostream>
#include <string>
#include <stdint.h>
#include <bitset>

#include <tlm.h>
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace std;


#endif
