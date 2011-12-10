
#include "global.h"

#include <systemc.h>
#include <scv.h>


SC_MODULE (reference_model)
{
public:
        sc_in < sc_uint<BITWIDTH> > input_A_stimulator;
        sc_in < sc_uint<BITWIDTH> > input_B_stimulator;
        sc_in < bool > carry_in_stimulator;
        sc_in < double > timeout;
        sc_in < unsigned int > testsequence_id;
        sc_in < unsigned int > testcase_id;

        sc_inout < sc_uint <BITWIDTH> > output_scoreboard;
        sc_inout < bool > output_carry_scoreboard;
        sc_inout < double > timeout_scoreboard;
        sc_inout < unsigned int > testcase_id_scoreboard;
        sc_inout < unsigned int > testsequence_id_scoreboard;

        SC_CTOR(reference_model)
        {
                SC_METHOD(reference_method);
                sensitive << input_A_stimulator.value_changed() << input_B_stimulator.value_changed();
        }

        void reference_method ()
        {
                input_A = input_A_stimulator.read();
                input_B = input_B_stimulator.read();
                carry_in = carry_in_stimulator.read();

                output = input_A + input_B + (carry_in ? 1 : 0) ;
                carry_out = ( output < input_A ) || ( output < input_B) ;

                output_scoreboard.write(output);
                output_carry_scoreboard.write(carry_out);
                timeout_scoreboard.write(timeout);
                testsequence_id_scoreboard.write(testsequence_id.read());
                testcase_id_scoreboard.write(testcase_id.read());
        }

private:
        sc_uint <BITWIDTH> input_A;
        sc_uint <BITWIDTH> input_B;
        bool carry_in;

        sc_uint <BITWIDTH> output;
        bool carry_out;
};
