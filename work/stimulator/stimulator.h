/*
 * stimulator.h
 *
 *  Created on: 02.11.2011
 *      Author: sollboer
 */

/*
 * Problems:
 * 06.11.2011:
 * - Modul innerhalb der Klasse stimulator kann bei Konstruktor nicht erzeugt werden,
 * - sensitive Operator von SC_METHOD wird nicht erkannt
 * - indirekter Konstruktor für stimulator_m durch create_stimulator_module hat noch Fehler
 */


#ifndef STIMULATOR_H_
#define STIMULATOR_H_

#include <systemc>
using namespace sc_core;

#include "scv.h"
#include "stimulator_config.h"

enum eConstraint {eCONSTR, eDIST};
typedef eConstraint constraint_t;

SC_MODULE (stimulator_m)
{
	// TODO: selbst definiertes Port für dutInput_t schreiben!
	sc_inout < sc_uint<BITWIDTH> > input_A;
	sc_inout < sc_uint<BITWIDTH> > input_B;
	sc_in < bool > nextSample;

	stimulator_m (sc_module_name nm);

	void stimulator_method (void);

};

struct dutInput_constraint_t
	: public scv_constraint_base
{
	scv_smart_ptr<dutInput_t> pInput;

	// TODO:  SCV_CONSTRAINT macro durch selbst geschriebenen Konstruktur ersetzen,
	//		  dem constraint-Werte übergeben werden können
	SCV_CONSTRAINT_CTOR(dutInput_constraint_t)
	{
		SCV_CONSTRAINT (pInput->input_A() < 100);
		SCV_CONSTRAINT (pInput->input_B() > 12000);
	}
};


class testsequence_c {
public:
	dutInput_constraint_t testvalues;

	testsequence_c () {}

private:
	constraint_t kindOfConstraint;
	struct dutInput_t* lowerLimits;
	struct dutInput_t* upperLimits;

};


class stimulator {
public:
	stimulator(sc_module_name name): numOfTestsequences(0), i_stimulator(name)
	{
		create_testsequences ( );
	}

	int create_testsequences ( testsequence_c* testsequences);
	int create_testsequences ( );

private:
	int numOfTestsequences;
	testsequence_c* testsequences;
	stimulator_m i_stimulator;

};

#endif /* STIMULATOR_H_ */
