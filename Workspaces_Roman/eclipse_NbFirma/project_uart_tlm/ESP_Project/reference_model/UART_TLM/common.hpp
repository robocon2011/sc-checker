/*common.hpp*/
#include <iostream>
#include <string>
#include <stdint.h>
#include <bitset>

#include <tlm.h>
/*std convinience sockets, which encapsulate the explicite inheritance of interfaces*/
#include <tlm_utils/simple_initiator_socket.h>
#include <tlm_utils/simple_target_socket.h>

using namespace std;



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


