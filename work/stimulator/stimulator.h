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
#include "stimulator_config.h"

enum eConstraint {eCONSTR, eDIST};
typedef eConstraint constraint_t;

struct dutInput_constraint_t
	: public scv_constraint_base
{
public:
	scv_expression *expr;
	scv_smart_ptr<dutInput_t> pInput;

	// TODO:  SCV_CONSTRAINT macro durch selbst geschriebenen Konstruktur ersetzen,
	//		  dem constraint-Werte übergeben werden können
	SCV_CONSTRAINT_CTOR(dutInput_constraint_t)
	{
		// eh() &= get_expression(pInput)
		SCV_CONSTRAINT (pInput->input_A() < 100);
		SCV_CONSTRAINT (pInput->input_B() > 12000);
	}
};

class testsequence_c {
public:
	dutInput_constraint_t testvalues;
	unsigned int no_of_testcases;

	testsequence_c (constraint_t arg_kindOfConstr, unsigned int arg_noOfTc)
	:testvalues("testvalues"), no_of_testcases(arg_noOfTc)
	{}

private:
	constraint_t kindOfConstraint;
	struct dutInput_t* lowerLimits;
	struct dutInput_t* upperLimits;

};

SC_MODULE (stimulator_m)
{
public:
	// TODO: selbst definiertes Port für dutInput_t schreiben!
	sc_inout < sc_uint<BITWIDTH> > input_A;
	sc_inout < sc_uint<BITWIDTH> > input_B;
	sc_in < bool > nextSample;
	scv_smart_ptr <dutInput_t> stim_value;

	stimulator_m (sc_module_name nm);

//	int create_testsequences ( testsequence_c* testsequences);
	int create_testsequences ( );
	void stimulator_method (void);

private:
	int numOfTestsequences;
	list <testsequence_c> testsequences;
	//testsequence_c* testsequences;
};

#endif /* STIMULATOR_H_ */
