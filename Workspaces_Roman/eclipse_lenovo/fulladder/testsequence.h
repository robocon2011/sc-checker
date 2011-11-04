/*
 * testsequence.h
 *
 *  Created on: 23.10.2011
 *      Author: ew08b033
 */

#ifndef TESTSEQUENCE_H_
#define TESTSEQUENCE_H_

#include <systemc.h>
#include <scv.h>
#include "testvalues_ext.h"
#include "testvalues_constraint.h"

class testsequence
{
public:

	testvalues_constraint pTest;
	testvalues_constraint constrValues;

};



#endif /* TESTSEQUENCE_H_ */
