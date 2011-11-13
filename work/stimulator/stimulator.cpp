/*
 * stimulator.cpp
 *
 *  Created on: 02.11.2011
 *      Author: sollboer
 */

#include <systemc>
#include <scv.h>
#include "stimulator_config.h"

SC_HAS_PROCESS(stimulator_m);
stimulator_m::stimulator_m(sc_module_name nm)
	: sc_module (nm)
{
	create_testsequences ( );

	SC_THREAD (stimulator_thread);
}


void stimulator_m::create_testsequences()
{
	project_testsequences pT(&testsequences);

	numOfTestsequences = testsequences.total_entries;

}

void stimulator_m::stimulator_thread()
{
	testseq_collectionentry_c *p_help;
	unsigned int cnt_testcases;

	p_help = testsequences.p_priorEntry;

	while (p_help->p_priorEntry != 0)
	{
		p_help = p_help->p_priorEntry;
	}

	while (p_help != NULL)
	{

		for (cnt_testcases = 0; cnt_testcases < p_help->p_Sequence->no_of_testcases; cnt_testcases++)
		{
			wait(nextSample.value_changed_event());

			p_help->p_Sequence->p_testvalues->next();
			wait(SC_ZERO_TIME);
			write_values(p_help->p_Sequence->p_testvalues);
		}

		p_help = p_help->p_lastEntry;
	}

	testsequences_finished.write(true);
}





