/*
 * stimulator.h
 *
 *  Created on: 02.11.2011
 *      Author: sollboer
 */

#ifndef STIMULATOR_H_
#define STIMULATOR_H_

#include <systemc>

class stimulator {
public:
	int numOfTestsequences;
	testsequence_t* testsequences;

	int create_testsequences ( testsequence_t* testsequences);


};


#endif /* STIMULATOR_H_ */
