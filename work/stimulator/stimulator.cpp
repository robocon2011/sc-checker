/*
 * 	Filename:	stimulator.cpp
 *
 * 	Version:	---
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
 *  History:	2011/11/13: first executable version implemented
 *  			2011/11/20: stimulator thread - cout for next sequence added,
 *  						wait(zero) statement after write_values added
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
	numOfTestsequences = testsequences.get_total_entries();

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

		cout << endl << this->name() << ": start of next testsequence" << endl;

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
			/*	wait statement for internal SystemC update-process	*/
			wait(SC_ZERO_TIME);
		}

		/*	load pointer with next testsequence instance	*/
		p_help = p_help->p_lastEntry;
	}

	/*	indicate completion of all testsequences by boolean flag signal	*/
	testsequences_finished.write(true);
}
/*	stimulator_thread	*/

/*
 * **************************************************************
 *
 * functionname:	add_Entry
 * purpose:			links a new list element between root element
 * 					and prior instantiated testsequence list elements
 * parameters:		pointer to testsequences element
 * returnvalue:		none
 *
 * **************************************************************
 */
void testseq_collectionentry_c::add_Entry (testsequence_general_c *_p_Sequence)
{
	testseq_collectionentry_c	*newEntry;

	/*	dynamic allocation of new list element */
	newEntry = new testseq_collectionentry_c;

	/*	 update list with new element	*/
	if (this->p_lastEntry != NULL)
	{
		newEntry->p_priorEntry = this->p_lastEntry;
		this->p_lastEntry->p_lastEntry = newEntry;
	}
	else
	{
		newEntry->p_priorEntry = NULL;
	}
	this->p_lastEntry = newEntry;
	this->p_priorEntry = newEntry;

	/*	attach passed testsequence to new element	*/
	newEntry->p_Sequence = _p_Sequence;
}

/*
 * **************************************************************
 *
 * functionname:	get_total_entries
 * purpose:			Getter-function for obtaining the total entries of root element
 * parameters:		none
 * returnvalue:		number of total entries
 *
 * **************************************************************
 */
unsigned int testseq_collectionentry_c::get_total_entries()
{
	return total_entries;
}

/*
 * **************************************************************
 *
 * functionname:	testsequence_specialized_c
 * purpose:			Constructor for user-defined testsequence object
 * parameters:		p_collection.......Pointer to root element of list of testsequences
 * 					_no_of_testcases...specified number of random values to be generated
 * returnvalue:		none
 *
 * **************************************************************
 */
template <class T>
testsequence_specialized_c <T> ::testsequence_specialized_c (testseq_collectionentry_c *p_collection ,unsigned int _no_of_testcases)
:testvalues("testvalues")
{
	/*	append testsequences to root element of list of testsequences
	 * 	and set number of testsequences	*/
	p_collection->add_Entry(this);
	this->no_of_testcases = _no_of_testcases;

	/*	apply handle of user-defined type of constraint class
	 * 	to member of generic testsequence class
	 */
	p_testvalues = &testvalues;
}

/*///////////////////////////////////////////////////////////////////////////////////////
 * stimulator.cpp
 */

