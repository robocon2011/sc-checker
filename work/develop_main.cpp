
#include "driver.h"
#include "monitor.h"
#include "stimulator_config.h"
#include "scoreboard_config.h"
#include "fulladder_rtl.h"
#include "testcontroller.h"
#include "reference_model.h"

#include "global.h"

#ifndef PACKETS_
  #include "packets.h"
#endif
#ifndef SP_PORTS_
  #include "sp_ports.h"
#endif

int sc_main (int argc, char *argv[])
{
  scv_startup();

  /*scv_tr_text_init();
  scv_tr_db db("ESP_DB");
  scv_tr_db::set_default_db(&db); */

  int i;
  //sc_set_time_resolution(1, SC_NS);

  /* create tracefile */
  sc_trace_file* tracefile_fulladder;

  tracefile_fulladder = sc_create_vcd_trace_file("fulladder_trace");

  if (!tracefile_fulladder){
      cout << "Error creating tracefile." << endl;
  }

  stimulator_m i_stimulator("i_stimulator");
  testcontroller i_testcontroller("i_testcontroller");
  reference_model i_reference_model ("i_reference_model");
  scoreboard_m i_scoreboard ("i_scoreboard");

  fulladder_cascade i_fulladder("i_fulladder");

  monitor mon_p_i("mon_p_i");
  driver dri_p_i("dri_p_i");

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
  sc_signal <sc_logic> a_in[BITWIDTH], b_in[BITWIDTH];
  sc_signal <sc_logic> a_out[BITWIDTH];

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

  i_fulladder.cy_in(cy_in);

  for(i=0;i<BITWIDTH;i++){

    mon_p_i.port_in_a(a_out[i]);

    dri_p_i.port_out_a(a_in[i]);
    dri_p_i.port_out_b(b_in[i]);

    i_fulladder.a_in[i](a_in[i]);
    i_fulladder.b_in[i](b_in[i]);
    i_fulladder.sum_out[i](a_out[i]);

  }

  i_fulladder.cy_out(cy_out);
  mon_p_i.cy_in(cy_out);

  mon_p_i.port_out(signal_output);
  mon_p_i.cy_out(signal_carry_out);

  /* transaction recording */
  sc_trace(tracefile_fulladder, signal_A_dut, "driver_in_a");
  sc_trace(tracefile_fulladder, signal_B_dut, "driver_in_b");
  sc_trace(tracefile_fulladder, a_in, "DUT_in_a");
  sc_trace(tracefile_fulladder, b_in, "DUT_in_b");

  sc_trace(tracefile_fulladder, a_out, "DUT_output");
  sc_trace(tracefile_fulladder, signal_carry_in_dut, "driver_carry_in");


  cout << "START OF SIMULATION" << endl;

  sc_start();
  if (! sc_end_of_simulation_invoked()) sc_stop();

  sc_close_vcd_trace_file(tracefile_fulladder);

  cout << "END OF SIMULATION" << endl;


  return 0;
}