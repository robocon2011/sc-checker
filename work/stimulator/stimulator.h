/*
 * 	Filename:	stimulator.h
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
 *  purpose:	header file for generic data of stimulator module
 *
 *  History:	2011/11/13: first executable version implemented
 *  			2011/12/03:	testsequence_id added to class testsequence_general_c
 *  						timeout added to dutInput_constraint_base_t
 *  			2011/12/10:	global struct packet_fulladdr added, dutInput_t removed
 *
 */

#ifndef STIMULATOR_H_
#define STIMULATOR_H_

#include <systemc>
using namespace sc_core;
#include "scv.h"
#include "../global.h"


class packet_fulladdr_constraint_base_t :
	public scv_constraint_base
{
public:
	scv_smart_ptr<packet_fulladdr> pInput;
	sc_time timeout;
};

/*
 *	classname:	testsequence_general_c
 *	purpose:	general class for project testsequences
 *				class is specialized by user-defined contraint classes
 *
 */
class testsequence_general_c
{
public:
	packet_fulladdr_constraint_base_t *p_testvalues;
	unsigned int no_of_testcases;
	unsigned int testsequence_id;

	/*	dummy constructor */
	testsequence_general_c() {}
};

/*
 *	classname:	testseq_collectionentry_c
 *	purpose:	list object for each user-defined testsequence
 *				objects are doubly linked
 *
 */
class testseq_collectionentry_c
{
public:
	testsequence_general_c		*p_Sequence;
	testseq_collectionentry_c	*p_priorEntry;
	testseq_collectionentry_c	*p_lastEntry;

	/*	Constructor	*/
	testseq_collectionentry_c()
	: p_Sequence(NULL), p_priorEntry(NULL), p_lastEntry(NULL), total_entries(0)
	{}

	/*	function declarations */
	void add_Entry (testsequence_general_c *_p_Sequence);
	unsigned int get_total_entries();

private:
	/*	internal memory for linked entries, only used by root-object	*/
	unsigned int total_entries;

};

/*
 *	classname:	testsequence_specialized_c
 *	purpose:	specialized class of general testsequence class
 *				templated by user-defined constraint classes
 *
 */
template < class T >
class testsequence_specialized_c : public testsequence_general_c
{
public:
	/*	T...user-defined type of constraint class */
	T testvalues;

	/*	Constructor	declaration	*/
	testsequence_specialized_c (testseq_collectionentry_c *p_collection ,unsigned int _no_of_testcases);
};


#endif /* STIMULATOR_H_ */

/*///////////////////////////////////////////////////////////////////////////////////////
 * stimulator.h
 */

