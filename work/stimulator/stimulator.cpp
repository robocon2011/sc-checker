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
	create_testsequences ( );

	SC_METHOD (stimulator_method)
			sensitive << nextSample;
}


int stimulator_m::create_testsequences()
{
	testsequence_c test_seq(eCONSTR, 10);

	testsequences.push_back(test_seq);

	return 0;
}

void stimulator_m::stimulator_method()
{
	list <testsequence_c>::iterator it;
	unsigned int cnt_testcases;

	for (it = testsequences.begin(); it != testsequences.end(); it++)
	{
		for (cnt_testcases=0; cnt_testcases < it->no_of_testcases;cnt_testcases++)
		{
			it->testvalues.next();
		}
	}
}
