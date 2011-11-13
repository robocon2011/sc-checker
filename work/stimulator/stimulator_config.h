/*
 * stimulator_config.h
 *
 *  Created on: 04.11.2011
 *      Author: ew08b033
 */

#ifndef STIMULATOR_CONFIG_H_
#define STIMULATOR_CONFIG_H_

#include <systemc>
using namespace sc_core;
using namespace sc_dt;
#include <scv.h>
#include "stimulator.h"


#define BITWIDTH 32


struct dutInput_t
{
	sc_uint<BITWIDTH> input_A;
	sc_uint<BITWIDTH> input_B;
};

SCV_EXTENSIONS(dutInput_t) {
public:
	scv_extensions < sc_uint<BITWIDTH> > input_A;
	scv_extensions < sc_uint<BITWIDTH> > input_B;
	SCV_EXTENSIONS_CTOR(dutInput_t) {
		SCV_FIELD (input_A);
		SCV_FIELD (input_B);
	}
};

class dutInput_constraint_base_t
	: public scv_constraint_base
{
public:
	scv_smart_ptr<dutInput_t> pInput;
};

class dutInput_constraint_t_01
	: public dutInput_constraint_base_t
{
public:
	SCV_CONSTRAINT_CTOR(dutInput_constraint_t_01)
	{
		SCV_CONSTRAINT (pInput->input_A() < 100);
		SCV_CONSTRAINT (pInput->input_B() < 100);
	}
};

class dutInput_constraint_t_02
	: public dutInput_constraint_base_t
{
	SCV_CONSTRAINT_CTOR(dutInput_constraint_t_02)
	{
		SCV_CONSTRAINT (pInput->input_A() > 100000);
		SCV_CONSTRAINT (pInput->input_B() > 100000);
	}
};

class dutInput_constraint_t_03
	: public dutInput_constraint_base_t
{
	SCV_CONSTRAINT_CTOR(dutInput_constraint_t_03)
	{
		SCV_CONSTRAINT (pInput->input_B() < 50000);
		pInput->input_A.disable_randomization();
	}
};

class project_testsequences
{
public:
	project_testsequences(testseq_collectionentry_c *p_testsequences)
	{
		addSequence(new testsequence_specialized_c < dutInput_constraint_t_01 > (p_testsequences, 3));
		addSequence(new testsequence_specialized_c < dutInput_constraint_t_02 > (p_testsequences, 3));
		addSequence(new testsequence_specialized_c < dutInput_constraint_t_03 > (p_testsequences, 5));
	}

	void addSequence(void * dummy) {}
};


SC_MODULE (stimulator_m)
{
public:
	// TODO: selbst definiertes Port für dutInput_t schreiben!
	sc_inout < sc_uint<BITWIDTH> > input_A;
	sc_inout < sc_uint<BITWIDTH> > input_B;
	sc_in < bool > nextSample;
	sc_inout < bool > testsequences_finished;
	sc_uint<BITWIDTH> s_input_A;
	sc_uint<BITWIDTH> s_input_B;
	//scv_smart_ptr <dutInput_t> stim_value;

	stimulator_m (sc_module_name nm);

	void create_testsequences ( );
	void stimulator_thread (void);

	void stimulator_m::write_values(dutInput_constraint_base_t *p_values)
	{
		s_input_A = p_values->pInput->input_A;
		s_input_B = p_values->pInput->input_B;

		input_A.write(s_input_A);
		input_B.write(s_input_B);
	}

private:
	unsigned int numOfTestsequences;
	testseq_collectionentry_c testsequences;
};


#endif /* STIMULATOR_CONFIG_H_ */

