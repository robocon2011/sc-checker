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
stimulator_m::stimulator_m(sc_module_name nm)
	: sc_module (nm)
{

	SC_METHOD (stimulator_method)
			sensitive << nextSample;
}


int stimulator::create_testsequences(testsequence_c *testsequences)
{
	testsequences = new testsequence_c();


	return 0;
}

void stimulator_m::stimulator_method()
{
	// IMPLEMENT_ME

}
