/*
 * dummy.cpp
 *
 *  Created on: 04.01.2012
 *      Author: Phil
 */

#include "dummy.h"

void dummy::dummy_method(){
  static int count = 0;
  static bool sof = true, delay = true;
  static bitset<DATABITS> b_set;
  static string a = "";

  /* delay it for a small amount of time */
  if(delay == true){
      next_trigger(5, SC_PS);
      delay = false;
  }
  else{
    delay = true;

    if((rx_in.read() == '0') && (sof == true)){
        cout<<"SOF detected" << endl;
        count = 0;
        b_set = 0;
        sof = false;
        next_trigger(rxclk.posedge_event());

        testcase_finished.write(false);
        reference_received.write(false);
    }
    else{
      /* catch transmitted data */
      if(count < DATABITS){
        if(rx_in.read() == '1'){
            b_set.set(count);
            a+="1";
        }
        else{
            b_set.reset(count);
            a+="0";
        }
        count++;
        cout << "catched bit " << count <<  endl;
        next_trigger(rxclk.posedge_event());
      }

      /*end of frame detected */
      else if(count == (DATABITS)){
        if(rx_in.read() == '0') cout << "ERROR: overrun on databits" << endl;
        else{
          sof = true;
          cout << "received data: " << b_set.to_ulong() << " bin: " << b_set << endl;
          cout << "--------dummy finished!----------" << endl;
          count++;

          reference_received.write(true);
          testcase_finished.write(true);
          next_trigger();
        }
      }
    }
  }
}



