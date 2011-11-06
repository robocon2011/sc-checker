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


class testsequence_c {
public:
	testsequence_c () {}

private:
	constraint_t kindOfConstraint;
	struct dutInput_t* lowerLimits;
	struct dutInput_t* upperLimits;

};


class stimulator {
public:
	stimulator() {}
	int create_testsequences ( testsequence_c* testsequences);
	void create_stimulator_module (sc_module_name name);

private:
	int numOfTestsequences;
	testsequence_c* testsequences;
	stimulator_m i_stimulator;

};

#endif /* STIMULATOR_H_ */
