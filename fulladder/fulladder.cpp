/*-------------------------------------
 * Project: Fulladder
 * ------------------------------------
 * file: fulladder.cpp
 * ------------------------------------
 * 23.09.2o11: Sollböck, initial version
 *
 *
 * ------------------------------------
*/

#include <systemc.h>
using namespace sc_core;

#include "fulladder.h"

SC_HAS_PROCESS(fulladder);
fulladder::fulladder(sc_module_name nm)
	: sc_module(nm)
{	
	SC_METHOD(fulladder_method)
		sensitive << pi_A << pi_B;
}

void fulladder::fulladder_method()
{
	unsigned int value_A;
	unsigned int value_B;
	sc_uint<8> value_C;
	
	value_A = pi_A->read();
	value_B = pi_B->read();
	value_C = value_A + value_B;

	if ( (value_A+value_B) > 255 ) 	po_carry->write(true);
	else po_carry->write(false);

	cout << "fulladder triggered: value_A=" << value_A << ", value_B="
			<< value_B << ", result=" << value_C << endl;

	po_C->write(value_C);

};




