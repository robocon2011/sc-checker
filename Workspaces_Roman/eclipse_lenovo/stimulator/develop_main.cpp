/*
 * develop_main.cpp
 *
 *  Created on: 06.11.2011
 *      Author: ew08b033
 */



#include <systemc>
#include <scv.h>
#include "stimulator/stimulator.h"
#include "stimulator/stimulator_config.h"
#include "dut/fulladder/fulladder_rtl.h"

int sc_main (int argc, char *argv[])
{
	stimulator stimulator;

	stimulator();

	stimulator.create_stimulator_module("i_stimulator");


	return 0;
}
