/*
 * stimulator_config.h
 *
 *  Created on: 04.11.2011
 *      Author: ew08b033
 */

#ifndef STIMULATOR_CONFIG_H_
#define STIMULATOR_CONFIG_H_

#include <systemc>
using namespace sc_core;
using namespace sc_dt;
#include <scv.h>

#define BITWIDTH 32

#include "stimulator.h"

struct dutInput_t
{
	sc_uint<BITWIDTH> input_A;
	sc_uint<BITWIDTH> input_B;
};

SCV_EXTENSIONS(dutInput_t) {
public:
	scv_extensions < sc_uint<BITWIDTH> > input_A;
	scv_extensions < sc_uint<BITWIDTH> > input_B;
	SCV_EXTENSIONS_CTOR(dutInput_t) {
		SCV_FIELD (input_A);
		SCV_FIELD (input_B);
	}
};


#endif /* STIMULATOR_CONFIG_H_ */
