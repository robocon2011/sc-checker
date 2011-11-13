/******************************************************************************/
/*                                                                            */
/* Filename:   database.cpp                                                   */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/


#include "database.h"

SC_HAS_PROCESS(database);

database::database(sc_module_name nm)
  : sc_module(nm){
  SC_THREAD(database_thread);
  }

void database::database_thread(){
  const char* name;

  const_cast<char*>(name = "DB_" + ((char) ID));

  scv_tr_db db(name);
}

