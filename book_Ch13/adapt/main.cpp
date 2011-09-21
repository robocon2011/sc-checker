//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//See adapt.h for more information
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

#include <iostream>
using std::cout;
using std::endl;

#include <systemc>
using namespace sc_core;
using std::cout;
using std::endl;
#include "adapt.h"

unsigned errors = 0;
const char* simulation_name = "adapt";

int sc_main(int argc, char* argv[]) 
{
  cout << "INFO: Elaboratiototing "<< simulation_name << endl;
  //sc_set_time_resolution(1,SC_PS);
  //sc_set_default_time_unit(1,SC_NS);
  adapt adapt_i("adapt_i");
  
  cout << "INFO: Simulating "<< simulation_name << endl;
  sc_start();
  if (not sc_end_of_simulation_invoked()) sc_stop(); //< invoke end_of_simulation
  
  cout << "INFO: Post-processing "<< simulation_name << endl;
  cout << "INFO: Simulation " << simulation_name
       << " " << (errors?"FAILED":"PASSED")
       << " with " << errors << " errors"
       << endl;
  return errors?1:0;
} // end sc_main
