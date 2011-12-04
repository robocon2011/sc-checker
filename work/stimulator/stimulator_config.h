/*
 * 	Filename:	stimulator_config.h
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
 *  purpose:	user-specific configuration for stimulator module
 *  			config file for fulladder
 *
 *  History:	2011/11/13: first executable version implemented
 *				2011/11/20:	Additional constraint classes created
 *				2011/12/03: carry bit added to all related modules,
 *							control signals next_sample_to_reference, next_sample_to_dut added
 *							functions write_values_to_reference, write_values_to_dut added
 *							ports for timeout, testsequence_id and testcase_id added to stimulator_m
 */

#ifndef STIMULATOR_CONFIG_H_
#define STIMULATOR_CONFIG_H_

#include <systemc>
using namespace sc_core;
using namespace sc_dt;
#include <scv.h>
/*	patch for dealing with issue from OSCI forum
 * 	http://www.systemc.org/Discussion_Forums/systemc-forum/archive/msg?list_name=systemc-forum&monthdir=201005&msg=msg00010.html
 */
void _scv_pop_constraint();	/*	patch	*/

#include "stimulator.h"

/*	<ENTER BELOW>	------------------------------------------------
 *
 * 	define Bitwidth of fulladder design
 *
 */
#define BITWIDTH 32


/*	<ENTER BELOW>	------------------------------------------------
 *
 *	structname:		dutInput_t
 *	purpose:		declares structure of user-specific source data
 *					needs to be adapted to DUT
 */
struct dutInput_t
{
	sc_uint<BITWIDTH> input_A;
	sc_uint<BITWIDTH> input_B;
	bool carry_in;
};

/*	<ENTER BELOW>	------------------------------------------------
 *
 *	classname:	scv_extensions <dutInput_t>
 *	purpose:	SCV extension class specialized by user-specific source data
 *				for creating SCV-internal extensions interface
 *				needs to be adapted to dutInput_t
 */
SCV_EXTENSIONS(dutInput_t) {
public:
	scv_extensions < sc_uint<BITWIDTH> > input_A;
	scv_extensions < sc_uint<BITWIDTH> > input_B;
	scv_extensions < bool > carry_in;
	SCV_EXTENSIONS_CTOR(dutInput_t) {
		SCV_FIELD (input_A);
		SCV_FIELD (input_B);
		SCV_FIELD (carry_in);
	}
};

/*
 *	classname:	dutInput_constraint_base_t
 *	purpose:	forward declaration of base constraint class
 *				see stimulator.h
 */
class dutInput_constraint_base_t;

/*	<ENTER BELOW>	------------------------------------------------
 *
 *	classname:	[user-defined constraint classes]
 *	purpose:	specialized base constraint class according SCV-guidelines
 *				no limit for user-specific amount of specialized classes
 *				testsequences are templated by these classes
 *
 *	Important:	use SCV_CONSTRAINT_CTOR,
 *				specialize from dutInput_constraint_base_t,
 *				redeclaration of scv_smart_ptr not necessary
 */
class dutInput_constraint_t_01
	: public dutInput_constraint_base_t
{
public:
	SCV_CONSTRAINT_CTOR(dutInput_constraint_t_01)
	{
		SCV_CONSTRAINT (pInput->input_A() < 100);
		SCV_CONSTRAINT (pInput->input_B() < 100);
		//SCV_CONSTRAINT ( ( pInput->input_A() + pInput->input_B() ) == 193);
		pInput->carry_in.disable_randomization();
		pInput->carry_in.write(false);

		timeout = sc_time(10, SC_NS);
	}
};

class dutInput_constraint_t_02
	: public dutInput_constraint_base_t
{
	SCV_CONSTRAINT_CTOR(dutInput_constraint_t_02)
	{
		SCV_CONSTRAINT (pInput->input_A() > 100000);
		SCV_CONSTRAINT (pInput->input_B() > 100000);
		pInput->carry_in.disable_randomization();
		pInput->carry_in.write(false);

		timeout = sc_time(10, SC_NS);
	}
};

class dutInput_constraint_t_03
	: public dutInput_constraint_base_t
{
	SCV_CONSTRAINT_CTOR(dutInput_constraint_t_03)
	{
		SCV_CONSTRAINT (pInput->input_B() < 50000);
		pInput->input_A.disable_randomization();
		pInput->carry_in.disable_randomization();
		pInput->carry_in.write(false);

		timeout = sc_time(10, SC_NS);
	}
};

class dutInput_constraint_t_04
	: public dutInput_constraint_base_t
{
	SCV_CONSTRAINT_CTOR(dutInput_constraint_t_04)
	{
		pInput->input_A.keep_only(500, 1000);
		pInput->input_A.keep_out(550, 950);
		pInput->input_B.keep_only(0, 500);
		pInput->input_B.keep_out(50, 450);
		pInput->carry_in.disable_randomization();
		pInput->carry_in.write(false);

		timeout = sc_time(10, SC_NS);
	}
};

class dutInput_constraint_t_05
	: public dutInput_constraint_base_t
{
public:
	list < sc_uint <BITWIDTH> > legal_values;

	SCV_CONSTRAINT_CTOR(dutInput_constraint_t_05)
	{
		for (int i = 0; i < 100; i++)
		{
			legal_values.push_back(i*1000);
		}
		pInput->input_A.keep_only(legal_values);
		pInput->input_B.keep_only(legal_values);
		pInput->carry_in.disable_randomization();
		pInput->carry_in.write(false);

		timeout = sc_time(10, SC_NS);
	}
};

class dutInput_constraint_t_06
	: public dutInput_constraint_base_t
{
public:
	scv_bag < sc_uint<BITWIDTH> > distribution_input_A;
	scv_bag < sc_uint<BITWIDTH> > distribution_input_B;
	scv_smart_ptr < sc_uint<BITWIDTH> > helpA;
	scv_smart_ptr < sc_uint<BITWIDTH> > helpB;

	//SCV_CONSTRAINT_CTOR(dutInput_constraint_t_06)
	dutInput_constraint_t_06(char *arg)
	{
		distribution_input_A.push(10000, 20);
		distribution_input_A.push(100000, 20);
		distribution_input_A.push(1000000, 60);
		distribution_input_B.push(10000, 20);
		distribution_input_B.push(100000, 20);
		distribution_input_B.push(1000000, 60);

		pInput->input_A.disable_randomization();	//set_mode(distribution_input_A);
		pInput->input_B.disable_randomization();	//set_mode(distribution_input_B);
		pInput->carry_in.disable_randomization();
		pInput->carry_in.write(false);

		helpA->set_mode(distribution_input_A);
		helpB->set_mode(distribution_input_B);

		timeout = sc_time(10, SC_NS);
	}

	void next ()
	{
		helpA->next();
		helpB->next();

		pInput->input_A.write(*(helpA->get_instance()));
		pInput->input_B.write(*(helpB->get_instance()));
	}
};

/*	<ENTER BELOW>	------------------------------------------------
 *
 *	classname:	project_testsequences
 *	purpose:	class consisting of user-specific test sequences
 *				one class inside stimulator module, which holds
 *				all testsequences
 *				testsequences are processed in the order of instantiation
 *				new testsequences are added the same as the samples
 *				using user-defined constraint classes
 */
class project_testsequences
{
public:
	/*	functionname:	project_testsequences (inline Constructor)
	 *  purpose:		instantiation and registration of testsequences
	 *  parameters:		p_testsequences...pointer to collection of all user-defined testsequences
	 *  returnvalues:	none
	 */
	project_testsequences(testseq_collectionentry_c *p_testsequences)
	{
		/*			|	templated classes for testsequence 						|	pointer to collection		|	specific number of
		 * 			|							< specialized constraint class >|	of testsequences (only one)	|	testcases (randoms)	*/
		addSequence	(new testsequence_specialized_c < dutInput_constraint_t_01 > 	(p_testsequences, 				3));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < dutInput_constraint_t_02 > 	(p_testsequences, 				5));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < dutInput_constraint_t_03 > 	(p_testsequences, 				5));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < dutInput_constraint_t_04 > 	(p_testsequences, 				5));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < dutInput_constraint_t_05 > 	(p_testsequences, 				5));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < dutInput_constraint_t_06 > 	(p_testsequences, 				20));
		/*			|															|								|						*/
		/*	<ENTER> new testsequences	*/
	}

	/*	dummy function for catching return pointer of "new" operator	*/
	void addSequence(void * dummy) {}
};

/*	<ENTER BELOW>	------------------------------------------------
 *
 *	structname:	stimulator_m
 *	purpose:	Stimulator SystemC Module for propagation of
 *				constraint randomized values to DUT
 *				needs partly to be adapted to DUT
 *
 */
SC_MODULE (stimulator_m)
{
public:
	/*	user defined ports for DUT - connected to Driver-module	*/
	// TODO: selbst definiertes Port für dutInput_t schreiben!
	sc_inout < sc_uint<BITWIDTH> > input_A_reference;
	sc_inout < sc_uint<BITWIDTH> > input_B_reference;
	sc_inout < bool > carry_in_reference;
	sc_inout < double > timeout;
	sc_inout < unsigned int > testsequence_id;
	sc_inout < unsigned int > testcase_id;

	sc_inout < sc_uint<BITWIDTH> > input_A;
	sc_inout < sc_uint<BITWIDTH> > input_B;
	sc_inout < bool > carry_in;

	/*	helper variables for port assignment	*/
	sc_uint<BITWIDTH> s_input_A;
	sc_uint<BITWIDTH> s_input_B;
	bool s_carry_in;
	//scv_smart_ptr <dutInput_t> stim_value;

	/*	-> DO NOT MODIFY <-
	 * 	control signal ports for stimulator */
	sc_in < bool > next_sample_to_reference;
	sc_in < bool > next_sample_to_dut;
	sc_inout < bool > testsequences_finished;

	/*	Constructor declaration	*/
	stimulator_m (sc_module_name nm);

	/*	module function declarations	*/
	void create_testsequences ( );

	/*	<ENTER BELOW> --------------------------------------------------
	 * 	user-defined function for assigning the created values to
	 * 	the module ports of dut
	 */
	void stimulator_m::write_values_to_dut(dutInput_constraint_base_t *p_values)
	{
		s_input_A = p_values->pInput->input_A;
		s_input_B = p_values->pInput->input_B;
		s_carry_in = p_values->pInput->carry_in;


		input_A.write(s_input_A);
		input_B.write(s_input_B);
		carry_in.write(s_carry_in);
	}

	/*	<ENTER BELOW> --------------------------------------------------
	 * 	user-defined function for assigning the created values to
	 * 	the module ports of reference model
	 */
	void write_values_to_reference(dutInput_constraint_base_t *p_values, unsigned int _cnt_testcases, unsigned int _testsequence_id)
	{
		s_input_A = p_values->pInput->input_A;
		s_input_B = p_values->pInput->input_B;
		s_carry_in = p_values->pInput->carry_in;


		input_A_reference.write(s_input_A);
		input_B_reference.write(s_input_B);
		carry_in_reference.write(s_carry_in);
		timeout.write( p_values->timeout.to_seconds() );
		testcase_id.write(_cnt_testcases);
		testsequence_id.write(_testsequence_id);
	}


	/*	SystemC module thread for stimulator	*/
	void stimulator_thread (void);


private:
	/*	extracted number of testsequences	*/
	unsigned int numOfTestsequences;
	/*	modules root element for list of testsequences	*/
	testseq_collectionentry_c testsequences;
};

#endif /* STIMULATOR_CONFIG_H_ */

/*///////////////////////////////////////////////////////////////////////////////////////
 * stimulator_config.h
 */

