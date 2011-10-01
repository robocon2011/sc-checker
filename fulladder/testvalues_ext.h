#ifndef TESTVALUES_EXT_H
#define TESTVALUES_EXT_H

#include "testvalues.h"

SCV_EXTENSIONS(testvalues)
{
public:
	scv_extensions<sc_uint<8>> value_A;
	scv_extensions<sc_uint<8>> value_B;
	SCV_EXTENSIONS_CTOR(testvalues)
	{
		SCV_FIELD(value_A);
		SCV_FIELD(value_B);
	}

	bool has_valid_extensions() {return true;}



};


//ostream& operator << (ostream& os, const scv_smart_ptr<testvalues>& p)
//{
//	os << "value_A=" << p->value_A << ", value_B=" << p->value_B << endl;
//	return os;
//}

#endif