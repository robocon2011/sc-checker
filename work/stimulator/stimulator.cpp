/*
 * stimulator.cpp
 *
 *  Created on: 02.11.2011
 *      Author: sollboer
 */

#include <systemc>
#include <scv.h>
#include "stimulator.h"

SC_HAS_PROCESS(stimulator_m);
stimulator_m::stimulator_m(sc_module_name nm):
		sc_module (nm)
{

	SC_METHOD (stimulator_method)
			sensitive >> nextSample;
}

void stimulator::create_stimulator_module(sc_module_name name)
{
	i_stimulator(name);

}


int stimulator::create_testsequences(testsequence_c *testsequences)
{
	// IMPLEMENT_ME
	return 0;
}

void stimulator_m::stimulator_method()
{
	// IMPLEMENT_ME

}
