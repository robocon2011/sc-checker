/*
 * fulladder_rtl.h
 *
 *  Created on: 25.10.2011
 *      Author: Roman Sollböck
 *      Description: simple DUT for Development of
 *      			Dynamic SystemC-Testbench for automated, constraint based Verification
 */

#ifndef FULLADDER_RTL_H_
#define FULLADDER_RTL_H_

#include <systemc.h>
#include <string>
#include <stdio.h>

// define for fulladder cascade bitwidth in case of not being defined globally for project
#include "global.h"

///////////////////////////////////////////////////////////////////////////////
//
// Describe a gate-level like model of a half adder.
SC_MODULE(halfadder) {
	sc_in<sc_logic> a_i;
	sc_in<sc_logic> b_i;
	sc_out<sc_logic> sum_o;
	sc_out<sc_logic> cy_o;

	void proc_halfadder();

	SC_CTOR(halfadder) {
		SC_METHOD(proc_halfadder);
		sensitive << a_i << b_i;
	}

};

void halfadder::proc_halfadder() {
	sum_o.write(a_i ^ b_i);
	cy_o.write(a_i & b_i);
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Describe a gate-level like model of an or gate.
SC_MODULE(orgate) {
	sc_in<sc_logic> a_i;
	sc_in<sc_logic> b_i;
	sc_out<sc_logic> or_o;

	void proc_orgate();

	SC_CTOR(orgate) {
		SC_METHOD(proc_orgate);
		sensitive << a_i << b_i;
	}

};

void orgate::proc_orgate() {
	or_o.write(a_i | b_i);
}
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Describe a gate-level like model of a full adder by instantiating two half
// adders and an or gate submodule.

SC_MODULE(fulladder) {
	sc_in<sc_logic> a_i;
	sc_in<sc_logic> b_i;
	sc_in<sc_logic> cy_i;
	sc_out<sc_logic> sum_o;
	sc_out<sc_logic> cy_o;

	halfadder i_halfadder1;
	halfadder i_halfadder2;
	orgate i_orgate;

	sc_signal<sc_logic> s_sum1, s_cy1, s_cy2;

	SC_CTOR(fulladder) :
			i_halfadder1("i_halfadder1"), i_halfadder2("i_halfadder2"), i_orgate(
					"i_orgate") {
		// hook up half adder one.
		i_halfadder1.a_i(a_i);
		i_halfadder1.b_i(b_i);
		i_halfadder1.sum_o(s_sum1);
		i_halfadder1.cy_o(s_cy1);
		// hook up half adder two.
		i_halfadder2.a_i(s_sum1);
		i_halfadder2.b_i(cy_i);
		i_halfadder2.sum_o(sum_o);
		i_halfadder2.cy_o(s_cy2);
		// hook up the or gate.
		i_orgate.a_i(s_cy1);
		i_orgate.b_i(s_cy2);
		i_orgate.or_o(cy_o);
	}

};
///////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
//
// Describe a gate-level like model of a cascaded full adder by instantiating
// fulladders according bitwidth.

SC_MODULE(fulladder_cascade) {
	int i;

	sc_in<sc_logic> a_in[BITWIDTH]; // declaration style from SystemC 2.0 User's Guide, Page 74 (pdf 82)
	sc_in<sc_logic> b_in[BITWIDTH];
	sc_in<sc_logic> cy_in;
	sc_out<sc_logic> sum_out[BITWIDTH];
	sc_out<sc_logic> cy_out;

	sc_signal<sc_logic> sig_cy_out[BITWIDTH];

	// declaration style from
	// http://www.systemc.org/Discussion_Forums/helpforum/archive/summary_form/msg?list_name=help_forum&monthdir=200504&msg=msg00100.html
	fulladder *i_fulladder[BITWIDTH];

	SC_CTOR(fulladder_cascade) {
		for (i = 0; i < (BITWIDTH); i++) {
			i_fulladder[i] = new fulladder(sc_gen_unique_name("i_fulladder"));
		}

		for (i = 0; i < (BITWIDTH); i++) {
			i_fulladder[i]->a_i(a_in[i]);
			i_fulladder[i]->b_i(b_in[i]);

			if (i == 0)
				i_fulladder[i]->cy_i(cy_in);
			else
				i_fulladder[i]->cy_i(sig_cy_out[i - 1]);

			if (i == ((BITWIDTH) - 1))
				i_fulladder[i]->cy_o(cy_out);
			else
				i_fulladder[i]->cy_o(sig_cy_out[i]);

			i_fulladder[i]->sum_o(sum_out[i]);
		}
	}

};

#endif /* FULLADDER_RTL_H_ */
