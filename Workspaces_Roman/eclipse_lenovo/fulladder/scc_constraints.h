#ifndef SCC_CONSTRAINTS_H
#define SCC_CONSTRAINTS_H

#include "testvalues_ext.h"
#include <scv.h>


void scc_set_constraints(scv_smart_ptr<testvalues> pTest)
{
	int valA_countConstraints_lowerThan = 1;
	int valA_lt_1 = 20;

	int valB_countConstraints_higherTan = 1;
	int valB_ht_1 = 250;

	if (valA_countConstraints_lowerThan > 0)
	{
		SCV_CONSTRAINT (pTest->value_A() < valA_lt_1 );
	}

	if (valB_countConstraints_higherTan > 0)
	{
		SCV_CONSTRAINT (pTest->value_B() > valB_ht_1);
	}
}


#endif
