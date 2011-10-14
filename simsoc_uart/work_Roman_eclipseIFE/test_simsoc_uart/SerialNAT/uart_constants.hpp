//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef UART_CONSTANTS_HPP
#define UART_CONSTANTS_HPP

const char EOT = 4;

const uint32_t UART_BASE = 0x11000000;

const uint32_t UART_THR = 0x0;
const uint32_t UART_RBR = 0x0;

const uint32_t UART_IER = 0x1;
const uint8_t UART_IER_DATA_AVAILABLE = 1<<0;
const uint8_t UART_IER_THR_EMPTY = 1<<1;
const uint8_t UART_IER_ERROR = 1<<2;
const uint8_t UART_IER_MSR_CHANGE = 1<<3;

const uint32_t UART_IIR = 0x2;
const uint8_t UART_IIR_IT_PENDING = 1<<0;
const uint8_t UART_IIR_ID_BITS = 7<<1;
const uint8_t UART_IIR_MSR_CHANGE = 0<<1;
const uint8_t UART_IIR_THR_EMPTY = 1<<1;
const uint8_t UART_IIR_ERROR = 3<<1;
const uint8_t UART_IIR_DATA_AVAILABLE = 2<<1;

const uint32_t UART_FCR = 0x2;
const uint32_t UART_LCR = 0x3;

const uint32_t UART_MCR = 0x4;
const uint8_t UART_MCR_RTS = 1<<1;

const uint32_t UART_LSR = 0x5;
const uint8_t UART_LSR_DATA_AVAILABLE = 1<<0;

const uint32_t UART_MSR = 0x6;
const uint8_t UART_MSR_CTS = 1<<4;

#endif //UART_CONSTANTS_HPP
