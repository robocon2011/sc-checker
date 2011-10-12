//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef SPEAR_SDRAM_CTRL_HPP
#define SPEAR_SDRAM_CTRL_HPP
/*
 * TLM Model for Serial Memory Controller
 *
 */

#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

/*
 * The controller manages system Serial Memory Interface
 */

class SDRAMCtrl: public Module,
                 public RW_Target {

public:
  static const uint32_t  SDRAM_WORD_LOWER_BOUND  = 0x00;
  static const uint32_t  SDRAM_WORD_UPPER_BOUND  = 0x18C;
  static const uint32_t  SDRAM_REGISTERS_COUNT   = 100;

  RW_TargetPort rw_port;
  uint32_t control[SDRAM_REGISTERS_COUNT]; // 100 control registers


  SDRAMCtrl(sc_core::sc_module_name name);
  ~SDRAMCtrl();

  // TLM read writes
  uint32_t read_word(uint32_t addr);
  void write_word(uint32_t addr, uint32_t data);

 void trans_read_data(PayLoad &pl)
  {
      switch (pl.get_data_length()) {
      case 4: {
        uint32_t addr = pl.get_address();
          uint32_t data = read_word(addr);
          *(uint32_t*)(pl.get_data_ptr()) = data;
      } break;
      default:
        error() <<": read data method is not implemented for data_length = "
        <<pl.get_data_length() <<std::endl;
        exit(1);
      }
   };

  void trans_write_data(PayLoad &pl)
  {
      switch (pl.get_data_length()) {
      case 4: {
        uint32_t addr = pl.get_address();
          uint32_t data = *(uint32_t*)(pl.get_data_ptr());
          write_word(addr,data);
        } break;
      default:
       error() <<": write data method is not implemented for data_length = "
        <<pl.get_data_length() <<std::endl;
        exit(1);
      }
  };

protected:
  // void Reset();
};

} // namespace simsoc

#endif //SDRAM
