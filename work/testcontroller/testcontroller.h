#ifndef TESTCONTROLLER_H
#define TESTCONTROLLER_H

#include <systemc.h>
#include <scv.h>

SC_MODULE (testcontroller)
{
public:
        sc_inout < bool > next_sample_to_reference;
        sc_in < bool > reference_received;
        sc_inout <bool > next_sample_to_dut;
        sc_in < bool > testcase_finished;
        sc_in < bool > all_sequences_finished;

        SC_CTOR(testcontroller)
        {
                SC_THREAD(testcontroller_thread);
        }

        void testcontroller_thread ()
        {
                while ( !all_sequences_finished.read() )
                {
                        next_sample_to_reference.write(true);

                        wait(reference_received.posedge_event());

                        next_sample_to_reference.write(false);
                        next_sample_to_dut.write(true);

                        wait(testcase_finished.posedge_event());
                        next_sample_to_dut.write(false);
                }
        }
};

#endif
