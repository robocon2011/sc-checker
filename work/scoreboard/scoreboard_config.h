/*
 * scoreboard_config.h
 *
 *  Created on: 27.11.2011
 *      Author: ew08b033
 */

#ifndef SCOREBOARD_CONFIG_H_
#define SCOREBOARD_CONFIG_H_

#define BITWIDTH 32

#include <systemc>
#include <scv.h>
#include <fstream>
#include <iostream>
#include "scoreboard.h"

enum compareResult { eOK = 0, eMISMATCH, eTIMEOUT};


SC_MODULE (scoreboard_m)
{
public:
	sc_in < sc_uint <BITWIDTH> > output_reference;
	sc_in < bool > output_carry_reference;
	sc_in < double > timeout_reference;
	sc_in < unsigned int > testcase_id_reference;
	sc_in < unsigned int > testsequence_id_reference;

	sc_in < sc_uint <BITWIDTH> > output_monitor;
	sc_in < bool > output_carry_monitor;

	sc_inout < bool > reference_received;
	sc_inout < bool > testcase_finished;

	std::ofstream outputFile;

	scoreboard_m (sc_module_name nm);

	void store_reference_method ();
	void compare_method ();

	void write_to_file ();

private:
	sc_uint <BITWIDTH> output_reference_buffer;
	bool output_carry_reference_buffer;
	sc_time timeout_buffer;

	sc_uint <BITWIDTH> output_monitor_buffer;
	bool output_carry_monitor_buffer;

	unsigned int testsequence_id;
	unsigned int testcase_id;
	sc_time start_time_buffer;
	sc_time end_time_buffer;

	enum compareResult result;
};

//
//class reference_t
//{
//	sc_uint<BITWIDTH> input_A;
//	sc_uint<BITWIDTH> input_B;
//	sc_time timeout;
//public:
//	reference_t& operator = (const reference_t& rhs)
//	{
//		input_A = rhs.input_A;
//		input_B = rhs.input_B;
//		timeout = rhs.timeout;
//		return *this;
//	}
//	bool operator== (const reference_t& rhs)
//			const {
//		return (input_A == rhs.input_A &&
//				input_B == rhs.input_B &&
//				timeout == rhs.timeout );
//	}
//	friend ostream& operator<< (ostream& file,
//								const reference_t& trans);
//
//	friend void sc_trace(sc_trace_file*& tf,
//								const reference_t& trans,
//			string nm);
//};
//
//ostream& operator<< (ostream& file,
//					const reference_t& trans)
//{
//	file	<< "{" << endl << " "
//			<< "input_A: " << trans.input_A << ", "
//			<< "input_B: " << trans.input_B << ", "
//			<< "timeout: " << trans.timeout
//			<< endl << "}";
//	return file;
//}
//void sc_trace (sc_trace_file*& tf,
//				const reference_t& trans,
//				string nm)
//{
//	sc_trace(tf, trans.input_A, nm + ".input_A");
//	sc_trace(tf, trans.input_B, nm + ".input_B");
//	//sc_trace(tf, trans.timeout, nm + ".timeout");
//}

#endif /* SCOREBOARD_CONFIG_H_ */
