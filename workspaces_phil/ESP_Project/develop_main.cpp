
#include "driver.h"
#include "monitor.h"

#ifndef PACKETS_
  #include "packets.h"
#endif
#ifndef SP_PORTS_
  #include "sp_ports.h"
#endif

//#include "driver.h"
//#include "monitor.h"

int sc_main (int argc, char *argv[])
{
       /*scv_startup();

	//database i_database("i_database");
        scv_tr_text_init();
	scv_tr_db db("myDB");
	scv_tr_db::set_default_db(&db); */

        int i;

        monitor mon_p_i("mon_p_i");
        driver dri_p_i("dri_p_i");

        sc_signal<int> c, d;
        sc_signal<sc_logic> a[INSTANCES_FULLADDER];
        sc_signal<sc_logic> b[INSTANCES_FULLADDER];

        c = 2;
        d = 3;

        dri_p_i.port_in(c);
        dri_p_i.port_in(d);
        for(i=0;i<INSTANCES_FULLADDER;i++){
          dri_p_i.port_out_a(a[i]);
          mon_p_i.port_in_a(a[i]);
          dri_p_i.port_out_b(b[i]);
          mon_p_i.port_in_b(b[i]);
          }
        mon_p_i.port_out(c);
        mon_p_i.port_out(d);

	cout << "START OF SIMULATION" << endl;

	sc_start();
	if (! sc_end_of_simulation_invoked()) sc_stop();

	cout << "END OF SIMULATION" << endl;
	return 0;
}
