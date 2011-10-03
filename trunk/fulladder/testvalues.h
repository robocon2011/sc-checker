#ifndef TESTVALUES_H
#define TESTVALUES_H

/*-------------------------------------
 * Project: Fulladder
 * ------------------------------------
 * file: fulladder.cpp
 * ------------------------------------
 * 23.09.2o11: Sollböck, initial version
 *
 *
 * ------------------------------------
*/

#include <systemc.h>
#include <scv.h>

struct testvalues
{
	enum type {SIMPLE, EXTENDED};
	type mode;
	sc_uint<8>	value_A;
	sc_uint<8>	value_B;
};



#endif

