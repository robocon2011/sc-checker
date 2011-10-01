/*-------------------------------------
 * Project: Fulladder
 * ------------------------------------
 * file: testbench.cpp
 * ------------------------------------
 * 23.09.2o11: Sollböck, initial version
 *
 *
 * ------------------------------------
*/

#include <systemc.h>
using namespace sc_core;
#include <scv.h>

#include "testvalues_ext.h"
#include "fulladder.h"
#include "testbench.h"


SC_HAS_PROCESS(testbench);
testbench::testbench(sc_module_name nm)
	: sc_module (nm), pTest("pTest"), constrValues("constrValues")
{
	//scv_smart_ptr<testvalues> pTest("pTest");
	SC_THREAD(testbench_thread);
}

void testbench::testbench_thread ()
{
	sc_uint<8> input_A;
	sc_uint<8> input_B;
	sc_uint<8> output_C;

	bool output_carry;
	int i;	

	for( i=0; i<20; i++ )
	{
		//cin >> input_A;
		//cin >> input_B;
		
		if (i==8) pTest->disable_randomization();
		if (i==15) 
		{
			constrValues.pTest->value_A.set_mode(constrValues.valueDistribution);
			constrValues.pTest->value_B.set_mode(constrValues.valueDistribution);
		}

		po_A->write((sc_uint<8>) 0);
		po_B->write((sc_uint<8>) 0);
		wait(SC_ZERO_TIME);

		if (i<10)
		{
			if (i<5) pTest->next();
			else if (i<8)	pTest->value_A.next();
			else if (i<10)	pTest->next();

			input_A = pTest->value_A;
			input_B = pTest->value_B;		
		}
		else
		{
			if (i<15) constrValues.pTest->next();
			else if (i<18)	constrValues.pTest->value_A.next();
			else if (i<20)	constrValues.pTest->next();

			input_A = constrValues.pTest->value_A;
			input_B = constrValues.pTest->value_B;	
		}

		po_A->write(input_A);
		po_B->write(input_B);

		wait(pi_C->default_event());

		output_C = pi_C->read();
		output_carry = pi_carry->read();

		if (i<10) pTest->print();
		else constrValues.pTest->print();
		
		cout << "result = " << output_C << ", carry_bit=" << output_carry << endl;

		wait(5,SC_NS);
	}



}
