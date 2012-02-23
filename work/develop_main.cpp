/******************************************************************************/
/*                                                                            */
/* Filename:    develop_main.cpp                                              */
/*                                                                            */
/* Author:      Roman Sollböck, Philipp Maroschek                             */
/*                                                                            */
/* Tools:       Compiles with SystemC 2.2.v0                                  */
/*                                                                            */
/* Project:     SystemC Checker                                               */
/*                                                                            */
/* Topmodule:   ------                                                        */
/* Submodules:  ------                                                        */
/*                                                                            */
/******************************************************************************/

#define BITWIDTH 10


#include "database/database.h"
#include "driver/driver.h"
#include "dut/fulladder/fulladder_rtl.h"
#include "monitor/monitor.h"
#include "reference_model/reference_model.h"
#include "scoreboard/scoreboard_config.h"
#include "stimulator/stimulator_config.h"
#include "testcontroller/testcontroller.h"

#include "global.h"

int sc_main (int argc, char *argv[])
{
  int i;

  scv_startup();

  scv_tr_text_init();
  scv_tr_db db("ESP_DB");
  scv_tr_db::set_default_db(&db);

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

  sc_signal <sc_uint<BITWIDTH> > signal_input_a_reference;
  sc_signal <sc_uint<BITWIDTH> > signal_input_b_reference;
  sc_signal <bool> signal_input_carry_reference;
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

  handshake monitor_data_written;

  i_testcontroller.next_sample_to_reference(signal_next_sample_to_reference);
  i_testcontroller.reference_received(signal_reference_received);
  i_testcontroller.next_sample_to_dut(signal_next_sample_to_dut);
  i_testcontroller.testcase_finished(signal_testcase_finished);
  i_testcontroller.all_sequences_finished(signal_all_testsequences_finished);

  i_stimulator.port_inputs_reference(signal_A_reference);
  i_stimulator.port_inputs_reference(signal_B_reference);
  i_stimulator.carry_in_reference(signal_carry_in_reference);
  i_stimulator.timeout(signal_timeout);
  i_stimulator.testsequence_id(signal_testsequence_id);
  i_stimulator.testcase_id(signal_testcase_id);
  i_stimulator.port_inputs(signal_A_dut);
  i_stimulator.port_inputs(signal_B_dut);
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
  i_reference_model.input_a_scoreboard(signal_input_a_reference);
  i_reference_model.input_b_scoreboard(signal_input_b_reference);
  i_reference_model.input_carry_scoreboard(signal_input_carry_reference);
  i_reference_model.output_scoreboard(signal_output_reference);
  i_reference_model.output_carry_scoreboard(signal_carry_out_reference);
  i_reference_model.timeout_scoreboard(signal_timeout_scoreboard);
  i_reference_model.testcase_id_scoreboard(signal_testcase_id_scoreboard);
  i_reference_model.testsequence_id_scoreboard(signal_testsequence_id_scoreboard);

  i_scoreboard.input_a_reference(signal_input_a_reference);
  i_scoreboard.input_b_reference(signal_input_b_reference);
  i_scoreboard.input_carry_reference(signal_input_carry_reference);
  i_scoreboard.output_reference(signal_output_reference);
  i_scoreboard.output_carry_reference(signal_carry_out_reference);
  i_scoreboard.timeout_reference(signal_timeout_scoreboard);
  i_scoreboard.testcase_id_reference(signal_testcase_id_scoreboard);
  i_scoreboard.testsequence_id_reference(signal_testsequence_id_scoreboard);
  i_scoreboard.output_monitor(signal_output);
  i_scoreboard.output_carry_monitor(signal_carry_out);
  i_scoreboard.reference_received(signal_reference_received);
  i_scoreboard.testcase_finished(signal_testcase_finished);
  i_scoreboard.data_written(monitor_data_written);

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
  mon_p_i.data_written(monitor_data_written);

  /* transaction recording */
  sc_trace(tracefile_fulladder, signal_A_dut, "DUT_A_in");
  sc_trace(tracefile_fulladder, signal_B_dut, "DUT_B_in");
  sc_trace(tracefile_fulladder, signal_carry_in_dut, "DUT_CY_in");

  sc_trace(tracefile_fulladder, signal_output, "DUT_output");
  sc_trace(tracefile_fulladder, signal_carry_out, "DUT_CY_out");


  cout << "START OF SIMULATION" << endl;

  sc_start();
  if (! sc_end_of_simulation_invoked()) sc_stop();

  sc_close_vcd_trace_file(tracefile_fulladder);

  cout << "END OF SIMULATION" << endl;


  return 0;
}
