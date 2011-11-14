/*
 * 	Filename:	stimulator_config.h
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
 *  History:	2011(11/13: first executable version implemented
 *
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
 *	declare structure of user-specific source data
 */
struct dutInput_t
{
	sc_uint<BITWIDTH> input_A;
	sc_uint<BITWIDTH> input_B;
};

/*	<ENTER BELOW>	------------------------------------------------
 *
 *	redefine user-specific source data for creating SCV-internal extensions interface
 */
SCV_EXTENSIONS(dutInput_t) {
public:
	scv_extensions < sc_uint<BITWIDTH> > input_A;
	scv_extensions < sc_uint<BITWIDTH> > input_B;
	SCV_EXTENSIONS_CTOR(dutInput_t) {
		SCV_FIELD (input_A);
		SCV_FIELD (input_B);
	}
};

/*	-> DO NOT MODIFY <-
 * base constraint class for further constraint class definitions
 */
class dutInput_constraint_base_t
	: public scv_constraint_base
{
public:
	scv_smart_ptr<dutInput_t> pInput;
};

/*	<ENTER BELOW>	------------------------------------------------
 *
 *	specialize base constraint class according SCV-guidelines
 *	no limit for user-specific amount of specialized classes
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

/*	<ENTER BELOW>	------------------------------------------------
 *
 *	declare class consisting of user-specific test sequences
 *	testsequences are processed in the order of instantiation
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
		/*			|	templated class for testsequence 						|	pointer to collection		|	specific number of
		 * 			|	user-defined constraint-classes							|	of testsequences (only one)	|	testcases (randoms)	*/
		addSequence	(new testsequence_specialized_c < dutInput_constraint_t_01 > 	(p_testsequences, 				3));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < dutInput_constraint_t_02 > 	(p_testsequences, 				3));
		/*			|															|								|						*/
		addSequence	(new testsequence_specialized_c < dutInput_constraint_t_03 > 	(p_testsequences, 				5));
		/*			|															|								|						*/
		/*	<ENTER> new testsequences	*/
	}

	/*	dummy function for catching return pointer of "new" operator	*/
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

