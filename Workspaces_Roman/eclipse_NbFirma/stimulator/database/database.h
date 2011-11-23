/******************************************************************************/
/*                                                                            */
/* Filename:   database.h                                                     */
/*                                                                            */
/* Author:     Philipp Maroschek                                              */
/*                                                                            */
/* Tools:      Compiles with SystemC 2.2.v0                                   */
/*                                                                            */
/******************************************************************************/

#ifndef DATABASE_H
#define DATABASE_

#include "config.h"

#include <iostream>
#include <string>

using namespace std;

SC_MODULE(database)
{
  // declaration of variables
  int ID;

  database(sc_module_name nm);

  // process declarations
  void database_thread();

};

#endif


