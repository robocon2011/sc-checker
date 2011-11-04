#ifndef TESTVALUES_CONSTRAINT_H
#define TESTVALUES_CONSTRAINT_H

#include "testvalues_ext.h"
#include "scc_constraints.h"

typedef pair < sc_uint<8>, sc_uint<8> > valueRange;

struct testvalues_constraint
	:public scv_constraint_base
{

	scv_smart_ptr<testvalues> pTest;
	scv_bag<valueRange> valueDistribution;

	SCV_CONSTRAINT_CTOR(testvalues_constraint)
	{
//
//		SCV_CONSTRAINT ( pTest->value_A() < 20 );
//		SCV_CONSTRAINT ( pTest->value_B() < 20 );


	}

};

#endif
