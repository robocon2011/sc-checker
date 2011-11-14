/*
 * 	Filename:	stimulator.cpp
 *
 *  Created on:	2011/11/13
 *
 *  Author: 	Roman SOLLBOECK
 *
 *  Project:	SystemC Checker
 *  Submodule:	Stimulator
 *
 *  purpose:	generic function bodies for stimulator module
 *
 *  History:	2011(11/13: first executable version implemented
 *
 */

#include <systemc>
#include <scv.h>
#include "stimulator_config.h"

/*
 * **************************************************************
 *
 * functionname:	stimulator_m (constructor)
 * purpose:			Constructor for sc_module stimulator_m
 * parameters:		none
 * returnvalue:		none
 *
 * **************************************************************
 */

SC_HAS_PROCESS(stimulator_m);
stimulator_m::stimulator_m(sc_module_name nm)
	: sc_module (nm)
{
	create_testsequences ( );

	SC_THREAD (stimulator_thread);
}
/*	stimulator_m	*/


/*
 * **************************************************************
 *
 * functionname:	create_testsequences
 * purpose:			appends user-defined testsequences to stimulator
 * 					by instantiation of user-specific class project_testsequences
 * parameters:		none
 * returnvalue:		none
 *
 * **************************************************************
 */

void stimulator_m::create_testsequences()
{
	/* instantiate user-specific class holding intended sequences */
	project_testsequences pT(&testsequences);

	/* extract total number of created sequences	*/
	numOfTestsequences = testsequences.total_entries;

}
/*	create_testsequences	*/

/*
 * **************************************************************
 *
 * functionname:	stimulator_thread
 * purpose:			SC_THREAD for generating stimulation outputs
 * 					user-defined testsequences are proceeded in order of instantiation
 * 					generator is blocked until new value is triggered by boolean control signal
 * parameters:		none
 * returnvalue:		none
 *
 * **************************************************************
 */
void stimulator_m::stimulator_thread()
{
	testseq_collectionentry_c *p_help;	/*	helper pointer for switching between sequences	*/
	unsigned int cnt_testcases;			/*	counter variable	*/

	/*	init pointer with front instance of testsequences	*/
	p_help = testsequences.p_priorEntry;

	/*	crawl through doubly-linked testsequences until last element (first instance) is reached
	 * (no pointer to prior element)	*/
	while (p_help->p_priorEntry != 0)
	{
		p_help = p_help->p_priorEntry;
	}

	/*	loop through testsequences from first to last instance and generate
	 * 	the specified amount of randomized values	*/
	while (p_help != NULL)
	{

		for (cnt_testcases = 0; cnt_testcases < p_help->p_Sequence->no_of_testcases; cnt_testcases++)
		{
			/*	block loop until transition of boolean control signal	*/
			wait(nextSample.value_changed_event());

			/*	call SCV random generator function next() from currently loaded testsequence*/
			p_help->p_Sequence->p_testvalues->next();
			/*	wait statement for internal SystemC update-process	*/
			wait(SC_ZERO_TIME);
			/*	write generated values to module ports indirectly by user-defined callback function*/
			write_values(p_help->p_Sequence->p_testvalues);
		}

		/*	load pointer with next testsequence instance	*/
		p_help = p_help->p_lastEntry;
	}

	/*	indicate completion of all testsequences by boolean flag signal	*/
	testsequences_finished.write(true);
}
/*	stimulator_thread	*/



/*///////////////////////////////////////////////////////////////////////////////////////
 * stimulator.cpp
 */

