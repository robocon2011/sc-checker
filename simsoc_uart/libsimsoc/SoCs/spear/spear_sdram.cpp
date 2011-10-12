//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "spear_sdram.hpp"
#include "libsimsoc/display.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

  static bool sdram_valid_word_address(uint32_t a) {
    return (SDRAMCtrl::SDRAM_WORD_LOWER_BOUND <= a) &&
      (a <= SDRAMCtrl::SDRAM_WORD_UPPER_BOUND);
  }

/*
 * Constructor and destructor
 */

SDRAMCtrl::SDRAMCtrl(sc_module_name name):
  Module(name)
{
  rw_port(*this);              // bind the target port
  debug() <<"SDRAMCtrl constructor" <<endl;
}

SDRAMCtrl::~SDRAMCtrl()
{
  debug() <<"SDRAMCtrl destructed" << endl;
}

/*
 * The addresses for
 *
 */

uint32_t SDRAMCtrl::read_word(uint32_t addr) {
  if (!sdram_valid_word_address(addr)) {
    error() << "Invalid SDRAM controller read word" << endl;
    exit(1);
  }
  uint32_t index = addr >> 2; // words of 4 bytes
  if (index < SDRAM_REGISTERS_COUNT ) {
    debug() << "read SDRAM controller register : " << index << endl;
    return control[index];
  }
  else {
    // should not happen
    error() << "Try to read non existent SDRAM register " << endl;
    exit(1);
  }
}

void SDRAMCtrl::write_word(uint32_t addr, uint32_t d) {
  if (!sdram_valid_word_address(addr)) {
    error() << "Invalid write SDRAM register" << endl;
    exit(1);
  }
  uint32_t index = addr >> 2; // words of 4 bytes
  if (index < SDRAM_REGISTERS_COUNT ) {
    debug() << "write SDRAM controller register : " << index << endl;
    control[index] = d;
  }
  else {
    // should not happen
    error() << "Try to read non existent SDRAM register " << endl;
    exit(1);
  }
}

} // namespace simsoc
