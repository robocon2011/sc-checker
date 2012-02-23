/*common.hpp*/
#include <iostream>
#include <string>
#include <stdint.h>
#include <bitset>

using namespace std;



#define BASE_ADDR 0x00000000ff000000
#define LENGTH 0x80
#define DATABITS 8

struct uart_data_t
{
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
};
