
#include "driver.h"
#include "monitor.h"
#include "stimulator_config.h"
#include "scoreboard_config.h"
#include "fulladder_rtl.h"
#include "global.h"

#ifndef PACKETS_
  #include "packets.h"
#endif
#ifndef SP_PORTS_
  #include "sp_ports.h"
#endif

SC_MODULE (asdf)
{
  fa_rtl_lv_single_port input;

  SC_CTOR(asdf){
    SC_METHOD(asdf_method);
    sensitive << input;
  }
  void asdf_method(){

      cout << "Triggered ..." << endl;

  }
};

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


int sc_main (int argc, char *argv[])
{
  scv_startup();

  /*scv_tr_text_init();
  scv_tr_db db("ESP_DB");
  scv_tr_db::set_default_db(&db); */

  //int i;
  sc_set_time_resolution(1, SC_NS);

  stimulator_m i_stimulator("i_stimulator");
  testcontroller i_testcontroller("i_testcontroller");
  reference_model i_reference_model ("i_reference_model");
  scoreboard_m i_scoreboard ("i_scoreboard");

  fulladder_cascade i_fulladder("i_fulladder");

  monitor mon_p_i("mon_p_i");
  driver dri_p_i("dri_p_i");


  //asdf i_test("i_test");

  sc_signal <sc_uint<BITWIDTH> > signal_A_reference;
  sc_signal <sc_uint<BITWIDTH> > signal_B_reference;
  sc_signal <bool> signal_carry_in_reference;
  sc_signal < double > signal_timeout;
  sc_signal < unsigned int > signal_testcase_id;
  sc_signal < unsigned int > signal_testsequence_id;

  sc_signal <sc_uint<BITWIDTH> > signal_A_dut;
  sc_signal <sc_uint<BITWIDTH> > signal_B_dut;
  sc_signal <bool> signal_carry_in_dut;

  sc_signal <sc_uint<BITWIDTH> > signal_output_reference;
  sc_signal <bool> signal_carry_out_reference;
  sc_signal < double > signal_timeout_scoreboard;
  sc_signal < unsigned int > signal_testcase_id_scoreboard;
  sc_signal < unsigned int > signal_testsequence_id_scoreboard;

  sc_signal <sc_uint<BITWIDTH> > signal_output;
  sc_signal <bool> signal_carry_out;

  sc_signal <bool> signal_next_sample_to_reference;
  sc_signal <bool> signal_next_sample_to_dut;
  sc_signal <bool> signal_reference_received;
  sc_signal <bool> signal_testcase_finished;
  sc_signal <bool> signal_all_testsequences_finished;

  sc_signal <sc_logic> cy_in, cy_out;
  sc_signal <sc_lv <BITWIDTH> > a_in, b_in;
  sc_signal <sc_lv <BITWIDTH> > a_out;

  i_testcontroller.next_sample_to_reference(signal_next_sample_to_reference);
  i_testcontroller.reference_received(signal_reference_received);
  i_testcontroller.next_sample_to_dut(signal_next_sample_to_dut);
  i_testcontroller.testcase_finished(signal_testcase_finished);
  i_testcontroller.all_sequences_finished(signal_all_testsequences_finished);

  i_stimulator.input_A_reference(signal_A_reference);
  i_stimulator.input_B_reference(signal_B_reference);
  i_stimulator.carry_in_reference(signal_carry_in_reference);
  i_stimulator.timeout(signal_timeout);
  i_stimulator.testsequence_id(signal_testsequence_id);
  i_stimulator.testcase_id(signal_testcase_id);
  i_stimulator.input_A(signal_A_dut);
  i_stimulator.input_B(signal_B_dut);
  i_stimulator.carry_in(signal_carry_in_dut);
  i_stimulator.next_sample_to_reference(signal_next_sample_to_reference);
  i_stimulator.next_sample_to_dut(signal_next_sample_to_dut);
  i_stimulator.testsequences_finished(signal_all_testsequences_finished);

  i_reference_model.input_A_stimulator(signal_A_reference);
  i_reference_model.input_B_stimulator(signal_B_reference);
  i_reference_model.carry_in_stimulator (signal_carry_in_reference);
  i_reference_model.timeout(signal_timeout);
  i_reference_model.testcase_id(signal_testcase_id);
  i_reference_model.testsequence_id(signal_testsequence_id);
  i_reference_model.output_scoreboard(signal_output_reference);
  i_reference_model.output_carry_scoreboard(signal_carry_out_reference);
  i_reference_model.timeout_scoreboard(signal_timeout_scoreboard);
  i_reference_model.testcase_id_scoreboard(signal_testcase_id_scoreboard);
  i_reference_model.testsequence_id_scoreboard(signal_testsequence_id_scoreboard);

  i_scoreboard.output_reference(signal_output_reference);
  i_scoreboard.output_carry_reference(signal_carry_out_reference);
  i_scoreboard.timeout_reference(signal_timeout_scoreboard);
  i_scoreboard.testcase_id_reference(signal_testcase_id_scoreboard);
  i_scoreboard.testsequence_id_reference(signal_testsequence_id_scoreboard);
  i_scoreboard.output_monitor(signal_output);
  i_scoreboard.output_carry_monitor(signal_carry_out);
  i_scoreboard.reference_received(signal_reference_received);
  i_scoreboard.testcase_finished(signal_testcase_finished);

  dri_p_i.port_in(signal_A_dut);
  dri_p_i.port_in(signal_B_dut);
  dri_p_i.cy_in(signal_carry_in_dut);
  dri_p_i.cy_out(cy_in);
  dri_p_i.port_out_a(a_in);
  dri_p_i.port_out_b(b_in);

  i_fulladder.port_a(a_in);
  i_fulladder.port_b(b_in);
  i_fulladder.cy_out(cy_out);
  i_fulladder.port_out(a_out);
  i_fulladder.cy_in(cy_in);

  //i_test.input(a_out);

  mon_p_i.port_in_a(a_out);
  mon_p_i.port_out(signal_output);
  mon_p_i.cy_in(cy_out);
  mon_p_i.cy_out(signal_carry_out);

  cout << "START OF SIMULATION" << endl;

  sc_start();
  if (! sc_end_of_simulation_invoked()) sc_stop();

  cout << "END OF SIMULATION" << endl;
  return 0;
}
