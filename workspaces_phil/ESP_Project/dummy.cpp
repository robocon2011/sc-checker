/*
 * dummy.cpp
 *
 *  Created on: 04.01.2012
 *      Author: Phil
 */

#include "dummy.h"

void dummy::dummy_method(){
static bool check_it = false;

  if(check_it == false){
    testcase_finished.write(false);
    reference_received.write(false);
    check_it = true;

    next_trigger(50, SC_PS);
  }
  else{
    testcase_finished.write(true);
    reference_received.write(true);
    check_it = false;
    cout << "Dummy catched values, temporarily instead of scoreboard: \n"
         << "rx_data_out: "  << rx_data_out.read() << "\n"
         << "rx_empty_out: " << rx_empty_out.read() << "\n"
         << "tx_data_out: "  << tx_data_out.read()  << "\n"
         << endl;
  }
}
