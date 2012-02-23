/******************************************************************************/
/*                                                                            */
/* Filename:    sp_packets.h                                                  */
/*                                                                            */
/* Author:      Philipp Maroschek                                             */
/*                                                                            */
/* Tools:       Compiles with SystemC 2.2.v0                                  */
/*                                                                            */
/* Project:     SystemC Checker                                               */
/*                                                                            */
/* Topmodule:   ------                                                        */
/* Submodules:  ------                                                        */
/*                                                                            */
/******************************************************************************/


#ifndef PACKETS_H
#define PACKETS_H

#include <systemc>
#include <scv.h>
#include <string>
#include <bitset>
using std::string;

#include "global.h"

#ifndef BITWIDTH
#define BITWIDTH 32
#endif

struct packet_fulladdr{
  sc_uint <BITWIDTH> sw_a;
  sc_uint <BITWIDTH> sw_b;
  bool sw_cy;

  sc_logic rtl_a[BITWIDTH];
  sc_logic rtl_b[BITWIDTH];
  sc_logic rtl_cy;

  bitset<BITWIDTH> b_set[1];

  packet_fulladdr()
  : sw_a (0)
  , sw_b (0)
  , sw_cy (0)
  , rtl_cy (0)
  {
    for (unsigned i=0;i<BITWIDTH;i++){
        rtl_a[i] = SC_LOGIC_X;
        rtl_b[i] = SC_LOGIC_X;
        b_set[0] = (0);
        b_set[1] = (0);
    }
  }

  packet_fulladdr(
      sc_uint<BITWIDTH> _sw_a,
      sc_uint<BITWIDTH> _sw_b,
      bool _sw_cy,
      sc_logic _rtl_cy
      )
  : sw_a   (_sw_a)
  , sw_b   (_sw_b)
  , sw_cy  (_sw_cy)
  , rtl_cy (_rtl_cy)
  {}


  packet_fulladdr& operator =
      (const packet_fulladdr& rhs){
    sw_a = rhs.sw_a;
    sw_b = rhs.sw_b;
    sw_cy = rhs.sw_cy;
    rtl_cy = rhs.rtl_cy;
   for(unsigned i=0;i<BITWIDTH;i++){
    rtl_a[i] = rhs.rtl_a[i];
    rtl_b[i] = rhs.rtl_b[i];
    b_set[0][i] = rhs.b_set[0][i];
    b_set[1][i] = rhs.b_set[1][i];
    }
    return *this;
  }

  bool operator== (const packet_fulladdr& rhs)
      const{
    int a = 0;
    a &= (sw_a == rhs.sw_a) ? 1 : 0;
    a &= (sw_b == rhs.sw_b) ? 1 : 0;
    a &= (sw_cy == rhs.sw_cy) ? 1 : 0;
    a &= (rtl_cy == rhs.rtl_cy) ? 1 : 0;
    for(unsigned i=0; i<BITWIDTH;i++){
        a &= (rtl_a[i] == rhs.rtl_a[i]) ? 1 : 0;
        a &= (rtl_b[i] == rhs.rtl_b[i]) ? 1 : 0;
        a &= (b_set[0][i] == rhs.b_set[0][i]) ? 1 : 0;
        a &= (b_set[1][i] == rhs.b_set[1][i]) ? 1 : 0;
    }
    return(a);
  }

private:

};

// Stream operator to output the package
ostream& operator<<(ostream& file, const packet_fulladdr& trans);

// Trace a transaction packet in case it is used in an sc_signal
void sc_trace_fulladr(sc_trace_file* tf, const packet_fulladdr& trans, const string& nm);

/**********************************************************************************************/
/**********************************************************************************************/

struct packet_fulladdr_lv{
  sc_uint<BITWIDTH> sw_a;
  sc_uint<BITWIDTH> sw_b;
  bool sw_cy;

  sc_lv<BITWIDTH> rtl_a;
  sc_lv<BITWIDTH> rtl_b;
  sc_logic rtl_cy;

  packet_fulladdr_lv()
  : sw_a (0)
  , sw_b (0)
  , sw_cy (0)
  , rtl_cy (0)
  {
    for (unsigned i=0;i<BITWIDTH;i++){
        rtl_a[i] = 'X';
        rtl_b[i] = 'X';
    }
  }

  packet_fulladdr_lv(
      sc_uint<BITWIDTH> _sw_a,
      sc_uint<BITWIDTH> _sw_b,
      bool _sw_cy,
      sc_logic _rtl_cy,
      sc_lv<BITWIDTH> _rtl_a,
      sc_lv<BITWIDTH> _rtl_b
      )
  : sw_a   (_sw_a)
  , sw_b   (_sw_b)
  , sw_cy  (_sw_cy)
  , rtl_cy (_rtl_cy)
  {}

  packet_fulladdr_lv& operator =
      (const packet_fulladdr_lv& rhs){
    sw_a = rhs.sw_a;
    sw_b = rhs.sw_b;
    sw_cy = rhs.sw_cy;
    rtl_cy = rhs.rtl_cy;
   for(unsigned i=0;i<BITWIDTH;i++){
    rtl_a[i] = rhs.rtl_a[i];
    rtl_b[i] = rhs.rtl_b[i];
    }
    return *this;
  }

  bool operator== (const packet_fulladdr_lv& rhs)
      const{
    int a = 0;
    a &= (sw_a == rhs.sw_a) ? 1 : 0;
    a &= (sw_b == rhs.sw_b) ? 1 : 0;
    a &= (sw_cy == rhs.sw_cy) ? 1 : 0;
    a &= (rtl_cy == rhs.rtl_cy) ? 1 : 0;
    for(unsigned i=0; i<BITWIDTH;i++){
        a &= (rtl_a[i] == rhs.rtl_a[i]) ? 1 : 0;
        a &= (rtl_b[i] == rhs.rtl_b[i]) ? 1 : 0;
    }
    return(a);
  }

};

// Stream operator to output the package
ostream& operator<<(ostream& file, const packet_fulladdr_lv& trans);

// Trace a transaction packet in case it is used in an sc_signal
void sc_trace_fulladdr_lv(sc_trace_file* tf, const packet_fulladdr_lv& trans, const string& nm);

/**********************************************************************************************/
/**********************************************************************************************/

struct packet_uart_rx_data{

  /* sw-level of abstraction */
  sc_uint <DATABITS> sw_data_rx;
  bool sw_reset;
  bool sw_rx_enable;
  bool sw_uld_rx_data;

  /* control signals */
  sc_logic rtl_reset;

  sc_logic rtl_uld_rx_data;
  sc_logic rtl_rx_enable;
  sc_logic rtl_rx_in;
  sc_logic rtl_rx_empty;

  /* data */
  sc_logic rtl_rx_data[DATABITS];

  bitset<DATABITS> b_set;

  packet_uart_rx_data()
  : sw_data_rx (255)
  , sw_reset (false)
  , sw_rx_enable (false)
  , sw_uld_rx_data (false)
  , rtl_reset (0)
  , rtl_uld_rx_data (0)
  , rtl_rx_enable (0)
  , rtl_rx_in (1)
  , rtl_rx_empty (0)
  {
    for (unsigned i=0;i<DATABITS;i++){
        rtl_rx_data[i] = SC_LOGIC_1;
        b_set[i] = (1);
    }
  }


  packet_uart_rx_data& operator =
    (const packet_uart_rx_data& rhs){
    sw_data_rx = rhs.sw_data_rx;
    sw_reset = rhs.sw_reset;
    sw_rx_enable = rhs.sw_rx_enable;
    sw_rx_enable = rhs.sw_rx_enable;
    sw_uld_rx_data = rhs.sw_uld_rx_data;
    rtl_reset = rhs.rtl_reset;
    rtl_uld_rx_data = rhs.rtl_uld_rx_data;
    rtl_rx_enable = rhs.rtl_rx_enable;
    rtl_rx_in = rhs.rtl_rx_in;
    rtl_rx_empty = rhs.rtl_rx_empty;
    for(unsigned i=0;i<DATABITS;i++){
      rtl_rx_data[i] = rhs.rtl_rx_data[i];
      b_set[i] = rhs.b_set[i];
    }
    return *this;
  }

  bool operator== (const packet_uart_rx_data& rhs)
      const{
    int a = 0;
    a &= (sw_data_rx == rhs.sw_data_rx) ? 1 : 0;
    a &= (sw_reset == rhs.sw_reset) ? 1 : 0;
    a &= (sw_rx_enable == rhs.sw_rx_enable) ? 1 : 0;
    a &= (sw_uld_rx_data == rhs.sw_uld_rx_data) ? 1 : 0;
    a &= (rtl_reset == rhs.rtl_reset) ? 1 : 0;
    a &= (rtl_uld_rx_data == rhs.rtl_uld_rx_data) ? 1 : 0;
    a &= (rtl_rx_enable == rhs.rtl_rx_enable) ? 1 : 0;
    a &= (rtl_rx_in == rhs.rtl_rx_in) ? 1 : 0;
    a &= (rtl_rx_empty == rhs.rtl_rx_empty) ? 1 : 0;
    for(unsigned i=0; i < DATABITS;i++){
        a &= (rtl_rx_data[i] == rhs.rtl_rx_data[i]) ? 1 : 0;
        a &= (b_set[i] == rhs.b_set[i]) ? 1 : 0;
    }
    return(a);
  }

private:

};

// Stream operator to output the package
ostream& operator<<(ostream& file, const packet_uart_rx_data& trans);

/**********************************************************************************************/

struct packet_uart_tx_data{

  /* sw-level of abstraction */
  sc_uint <DATABITS> sw_data_tx;
  bool sw_reset;
  bool sw_tx_enable;
  bool sw_ld_tx_data;

  /* control signals */
  sc_logic rtl_reset;

  sc_logic rtl_ld_tx_data;
  sc_logic rtl_tx_enable;
  sc_logic rtl_tx_out;
  sc_logic rtl_tx_empty;

  /* data */
  sc_logic rtl_tx_data[DATABITS];

  bitset<DATABITS> b_set;

  packet_uart_tx_data()
  : sw_data_tx (255)
  , sw_reset (false)
  , sw_tx_enable (false)
  , sw_ld_tx_data (false)
  , rtl_reset (0)
  , rtl_ld_tx_data (0)
  , rtl_tx_enable (0)
  , rtl_tx_out (1)
  , rtl_tx_empty (0)
  {
    for (unsigned i=0;i<DATABITS;i++){
        rtl_tx_data[i] = SC_LOGIC_1;
        b_set[i] = (1);
    }
  }

  packet_uart_tx_data& operator =
    (const packet_uart_tx_data& rhs){
    sw_data_tx = rhs.sw_data_tx;
    sw_reset = rhs.sw_reset;
    sw_ld_tx_data = rhs.sw_ld_tx_data;
    rtl_reset = rhs.rtl_reset;
    rtl_ld_tx_data = rhs.rtl_ld_tx_data;
    rtl_tx_enable = rhs.rtl_tx_enable;
    rtl_tx_out = rhs.rtl_tx_out;
    rtl_tx_empty = rhs.rtl_tx_empty;
    for(unsigned i=0;i<DATABITS;i++){
      rtl_tx_data[i] = rhs.rtl_tx_data[i];
      b_set[i] = rhs.b_set[i];
    }
    return *this;
  }

  bool operator== (const packet_uart_tx_data& rhs)
      const{
    int a = 0;
    a &= (sw_data_tx == rhs.sw_data_tx) ? 1 : 0;
    a &= (sw_reset == rhs.sw_reset) ? 1 : 0;
    a &= (sw_tx_enable == rhs.sw_tx_enable) ? 1 : 0;
    a &= (sw_ld_tx_data == rhs.sw_ld_tx_data) ? 1 : 0;
    a &= (rtl_reset == rhs.rtl_reset) ? 1 : 0;
    a &= (rtl_ld_tx_data == rhs.rtl_ld_tx_data) ? 1 : 0;
    a &= (rtl_tx_enable == rhs.rtl_tx_enable) ? 1 : 0;
    a &= (rtl_tx_out == rhs.rtl_tx_out) ? 1 : 0;
    a &= (rtl_tx_empty == rhs.rtl_tx_empty) ? 1 : 0;
    for(unsigned i=0; i < DATABITS;i++){
        a &= (rtl_tx_data[i] == rhs.rtl_tx_data[i]) ? 1 : 0;
        a &= (b_set[i] == rhs.b_set[i]) ? 1 : 0;
    }
    return(a);
  }

private:

};

// Stream operator to output the package
ostream& operator<<(ostream& file, const packet_uart_tx_data& trans);

#endif
