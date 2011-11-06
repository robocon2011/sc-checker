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

#include "stimulator.h"
#include "../dut/fulladder/fulladder_rtl.h"

struct dutInput_t
{
	sc_uint<BITWIDTH> input_A;
	sc_uint<BITWIDTH> input_B;
};




#endif /* STIMULATOR_CONFIG_H_ */
