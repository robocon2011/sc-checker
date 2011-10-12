//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef SPEAR_SOC_CTRL_HPP
#define SPEAR_SOC_CTRL_HPP
/*
 * TLM Model for SPEAR PLUS SoC controller
 * This model is incomplete with many TODO's
 */

#include "libsimsoc/interfaces/tlm.hpp"
#include "libsimsoc/module.hpp"

namespace simsoc {

/*
 * The controller sets global SoC configuration
 */

class SoC_Config: public Module,
                  public RW_Target {

public:
  static const uint32_t  SOC_CTRL_WORD_LOWER_BOUND  = 0x00;
  static const uint32_t  SOC_CTRL_WORD_UPPER_BOUND  = 0xF0;

  static const uint32_t  SOC_CTRL_SOC_CFG_OFFSET        = 0x00;
  static const uint32_t  SOC_CTRL_DIAG_CFG_OFFSET       = 0x04;
  static const uint32_t  SOC_CTRL_PLL1_CTRL_OFFSET      = 0x08;
  static const uint32_t  SOC_CTRL_PLL1_FRQ_OFFSET       = 0x0C;
  static const uint32_t  SOC_CTRL_PLL1_MOD_OFFSET       = 0x10;
  static const uint32_t  SOC_CTRL_PLL2_CTRL_OFFSET      = 0x14;
  static const uint32_t  SOC_CTRL_PLL2_FRQ_OFFSET       = 0x18;
  static const uint32_t  SOC_CTRL_PLL2_MOD_OFFSET       = 0x1C;
  static const uint32_t  SOC_CTRL_PLL_CLK_OFFSET        = 0x20;
  static const uint32_t  SOC_CTRL_CORE_CLK_OFFSET       = 0x24;
  static const uint32_t  SOC_CTRL_PER_CLK_OFFSET        = 0x28;
  static const uint32_t  SOC_CTRL_PER1_CLK_ENB_OFFSET   = 0x2C;
  static const uint32_t  SOC_CTRL_PER2_CLK_ENB_OFFSET   = 0x30;
  static const uint32_t  SOC_CTRL_RAS_CLK_ENB_OFFSET    = 0x34;
  static const uint32_t  SOC_CTRL_PER1_SOF_RST_OFFSET   = 0x38;
  static const uint32_t  SOC_CTRL_PER2_SOF_RST_OFFSET   = 0x3C;
  static const uint32_t  SOC_CTRL_RAS_SOF_RST_OFFSET    = 0x40;
  static const uint32_t  SOC_CTRL_PRSC1_CLK_OFFSET      = 0x44;
  static const uint32_t  SOC_CTRL_PRSC2_CLK_OFFSET      = 0x48;
  static const uint32_t  SOC_CTRL_PRSC3_CLK_OFFSET      = 0x4C;
  static const uint32_t  SOC_CTRL_AMEM_CLK_OFFSET       = 0x50;
  static const uint32_t  SOC_CTRL_EXP_CLK_OFFSET        = 0x54; // no 0x58
  static const uint32_t  SOC_CTRL_LCD_CLK_OFFSET        = 0x5C;
  static const uint32_t  SOC_CTRL_IRDA_CLK_OFFSET       = 0x60;
  static const uint32_t  SOC_CTRL_UART_CLK_OFFSET       = 0x64;
  static const uint32_t  SOC_CTRL_GMAC_CLK_OFFSET       = 0x68;
  static const uint32_t  SOC_CTRL_RAS1_CLK_OFFSET       = 0x6C;
  static const uint32_t  SOC_CTRL_RAS2_CLK_OFFSET       = 0x70;
  static const uint32_t  SOC_CTRL_RAS31_CLK_OFFSET      = 0x74;
  static const uint32_t  SOC_CTRL_RAS41_CLK_OFFSET      = 0x78;
  static const uint32_t  SOC_ICM1_ARB_CONF_OFFSET       = 0x7C;
  static const uint32_t  SOC_ICM2_ARB_CONF_OFFSET       = 0x80;
  static const uint32_t  SOC_ICM3_ARB_CONF_OFFSET       = 0x84;
  static const uint32_t  SOC_ICM4_ARB_CONF_OFFSET       = 0x88;
  static const uint32_t  SOC_ICM5_ARB_CONF_OFFSET       = 0x8C;
  static const uint32_t  SOC_ICM6_ARB_CONF_OFFSET       = 0x90;
  static const uint32_t  SOC_ICM7_ARB_CONF_OFFSET       = 0x94;
  static const uint32_t  SOC_ICM8_ARB_CONF_OFFSET       = 0x98;
  static const uint32_t  SOC_ICM9_ARB_CONF_OFFSET       = 0x9C;
  static const uint32_t  SOC_DMA_CHN_CONF_OFFSET        = 0xA0;
  static const uint32_t  SOC_USB_PHY_OFFSET             = 0xA4;
  static const uint32_t  SOC_GMAC_CONF_OFFSET           = 0xA8;
  static const uint32_t  SOC_EXPI_CONF_OFFSET           = 0xAC;
  // PRC locks not yet implemented
  static const uint32_t  SOC_POWER_DOWN_CONF_OFFSET     = 0xE0;
  static const uint32_t  SOC_1V8_CONF_OFFSET            = 0xE4;
  static const uint32_t  SOC_2V5_CONF_OFFSET            = 0xE8;
  static const uint32_t  SOC_3V3_CONF_OFFSET            = 0xEC;
  static const uint32_t  SOC_DDRPAD_CONF_OFFSET         = 0xF0;


  static const uint32_t  PLL_UNLOCK_STATUS      = 0x0;
  static const uint32_t  PLL_LOCK_STATUS        = 0x1;
  static const uint32_t  PLL_ENABLE_MASK = 0x4;
  static const uint32_t  PLL_RESET_MASK  = 0x2;
  RW_TargetPort rw_port;
  uint32_t soc_config; // read only
  uint32_t diag_config; //
  uint32_t pll1_control; //
  uint32_t pll1_freq; //
  uint32_t pll1_mode; //
  uint32_t pll2_control; //
  uint32_t pll2_freq; //
  uint32_t pll2_mode; //
  uint32_t pll_clock_conf; //
  uint32_t core_clock_conf; //
  uint32_t periph_clock_conf; //
  uint32_t per1_clock_enable; //
  uint32_t per2_clock_enable; //
  uint32_t ras_clock_enable; //
  uint32_t per1_soft_reset;
  uint32_t per2_soft_reset; //
  uint32_t ras_soft_reset; //
  uint32_t prsc1_clock_conf; //
  uint32_t prsc2_clock_conf; //
  uint32_t prsc3_clock_conf; //
  uint32_t amem_clock_conf; //
  uint32_t expand_clock_conf;
  uint32_t lcd_clock_synt; //
  uint32_t irda_clock_synt; //
  uint32_t uart_clock_synt; //
  uint32_t gmac_clock_synt; //
  uint32_t ras1_clock_synt; //
  uint32_t ras2_clock_synt; //
  uint32_t ras3_clock_synt; //
  uint32_t ras4_clock_synt; //
  uint32_t icm1_arb_conf; //
  uint32_t icm2_arb_conf; //
  uint32_t icm3_arb_conf; //
  uint32_t icm4_arb_conf; //
  uint32_t icm5_arb_conf; //
  uint32_t icm6_arb_conf; //
  uint32_t icm7_arb_conf; //
  uint32_t icm8_arb_conf; //
  uint32_t icm9_arb_conf; //
  uint32_t dma_conf; //
  uint32_t usb_conf; //
  uint32_t gmac_conf; //
  uint32_t expand_conf; //
  uint32_t powerdown_conf; //
  uint32_t ddr_1v8_conf; //
  uint32_t ddr_2v5_conf; //
  uint32_t ddr_3v3_conf; //
  uint32_t ddr_pad_conf; //


  SoC_Config(sc_core::sc_module_name name);
  ~SoC_Config();

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

#endif //SOC_CTRL
