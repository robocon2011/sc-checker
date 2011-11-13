/*
 * stimulator.h
 *
 *  Created on: 02.11.2011
 *      Author: sollboer
 */

#ifndef STIMULATOR_H_
#define STIMULATOR_H_

#include <systemc>
using namespace sc_core;
#include "scv.h"

class dutInput_constraint_base_t;

class testsequence_general_c
{
public:
	unsigned int no_of_testcases;
	dutInput_constraint_base_t *p_testvalues;

	testsequence_general_c() {}
};

class testseq_collectionentry_c
{
public:
	unsigned int total_entries;
	testsequence_general_c		*p_Sequence;
	testseq_collectionentry_c	*p_priorEntry;
	testseq_collectionentry_c	*p_lastEntry;

	testseq_collectionentry_c()
	:total_entries(0), p_Sequence(NULL), p_priorEntry(NULL), p_lastEntry(NULL)
	{}

	void add_Entry (testsequence_general_c *_p_Sequence)
	{
		testseq_collectionentry_c	*newEntry;

		newEntry = new testseq_collectionentry_c;

		if (this->p_lastEntry != NULL)
		{
			newEntry->p_priorEntry = this->p_lastEntry;
			this->p_lastEntry->p_lastEntry = newEntry;
		}
		else
		{
			newEntry->p_priorEntry = NULL;
		}

		newEntry->p_Sequence = _p_Sequence;

		this->p_lastEntry = newEntry;
		this->p_priorEntry = newEntry;
	}
};

template < class T >
class testsequence_specialized_c : public testsequence_general_c
{
public:
	T testvalues;

	testsequence_specialized_c (testseq_collectionentry_c *p_collection ,unsigned int _no_of_testcases)
	:testvalues("testvalues")
	{
		p_collection->add_Entry(this);
		this->no_of_testcases = _no_of_testcases;
		p_testvalues = &testvalues;
	}
};


#endif /* STIMULATOR_H_ */
