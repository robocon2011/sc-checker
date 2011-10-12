//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

/*
 * WARNING This model is not complete.
 * It implements the registers but has no semantics
 */

#include "spear_soc_conf.hpp"
#include "libsimsoc/display.hpp"

using namespace std;
using namespace sc_core;

namespace simsoc {

  static bool soc_ctrl_valid_word_address(uint32_t a) {
    return (SoC_Config::SOC_CTRL_WORD_LOWER_BOUND <= a) &&
      (a <= SoC_Config::SOC_CTRL_WORD_UPPER_BOUND);
  }

/*
 * Constructor and destructor
 */

SoC_Config::SoC_Config(sc_module_name name):
  Module(name)
{
  rw_port(*this);              // bind the target port
  debug() <<"SoC_Config constructor" <<endl;
}

SoC_Config::~SoC_Config()
{
  debug() <<"SoC_Config destructed" << endl;
}

/*
 * The addresses for
 *
 */
uint32_t SoC_Config::read_word(uint32_t addr) {
  if (!soc_ctrl_valid_word_address(addr)) {
    error() << "Invalid read word" << endl;
    exit(1);
  }
  // read register
  info() << "SoC_Config read register " << addr << endl;
  switch(addr) {
  case SOC_CTRL_SOC_CFG_OFFSET:
    return soc_config;

  case SOC_CTRL_DIAG_CFG_OFFSET      :
    return diag_config;

  case SOC_CTRL_PLL1_CTRL_OFFSET     :
    return pll1_control;

  case SOC_CTRL_PLL1_FRQ_OFFSET      :
    return pll1_freq;

  case SOC_CTRL_PLL1_MOD_OFFSET      :
    return pll1_mode;

  case SOC_CTRL_PLL2_CTRL_OFFSET     :
    return pll2_control;

  case SOC_CTRL_PLL2_FRQ_OFFSET      :
    return pll2_freq;

  case SOC_CTRL_PLL2_MOD_OFFSET      :
    return pll2_mode;

  case SOC_CTRL_PLL_CLK_OFFSET       :
    return pll_clock_conf;

  case SOC_CTRL_CORE_CLK_OFFSET      :
    return core_clock_conf;

  case SOC_CTRL_PER_CLK_OFFSET       :
    return periph_clock_conf;

  case SOC_CTRL_PER1_CLK_ENB_OFFSET  :
    return per1_clock_enable;

  case SOC_CTRL_PER2_CLK_ENB_OFFSET  :
    return per2_clock_enable;

  case SOC_CTRL_RAS_CLK_ENB_OFFSET   :
    return ras_clock_enable;

  case SOC_CTRL_PER1_SOF_RST_OFFSET  :
    return per1_soft_reset;

  case SOC_CTRL_PER2_SOF_RST_OFFSET  :
    return per2_soft_reset;

  case SOC_CTRL_RAS_SOF_RST_OFFSET   :
    return ras_soft_reset;

  case SOC_CTRL_PRSC1_CLK_OFFSET     :
    return prsc1_clock_conf;

  case SOC_CTRL_PRSC2_CLK_OFFSET     :
    return prsc2_clock_conf;

  case SOC_CTRL_PRSC3_CLK_OFFSET     :
    return prsc3_clock_conf;

  case SOC_CTRL_AMEM_CLK_OFFSET      :
    return amem_clock_conf;

  case SOC_CTRL_EXP_CLK_OFFSET       :
    return expand_clock_conf;

  case SOC_CTRL_LCD_CLK_OFFSET       :
    return lcd_clock_synt;

  case SOC_CTRL_IRDA_CLK_OFFSET      :
    return irda_clock_synt;

  case SOC_CTRL_UART_CLK_OFFSET      :
    return uart_clock_synt;

  case SOC_CTRL_GMAC_CLK_OFFSET      :
    return gmac_clock_synt;

  case SOC_CTRL_RAS1_CLK_OFFSET      :
    return ras1_clock_synt;

  case SOC_CTRL_RAS2_CLK_OFFSET      :
    return ras2_clock_synt;

  case SOC_CTRL_RAS31_CLK_OFFSET     :
    return ras3_clock_synt;

  case SOC_CTRL_RAS41_CLK_OFFSET     :
    return ras4_clock_synt;

  case SOC_ICM1_ARB_CONF_OFFSET      :
    return icm1_arb_conf;

  case SOC_ICM2_ARB_CONF_OFFSET      :
    return icm1_arb_conf;

  case SOC_ICM3_ARB_CONF_OFFSET      :
    return icm1_arb_conf;

  case SOC_ICM4_ARB_CONF_OFFSET      :
    return icm2_arb_conf;

  case SOC_ICM5_ARB_CONF_OFFSET      :
    return icm5_arb_conf;

  case SOC_ICM6_ARB_CONF_OFFSET      :
    return icm6_arb_conf;

  case SOC_ICM7_ARB_CONF_OFFSET      :
    return icm7_arb_conf;

  case SOC_ICM8_ARB_CONF_OFFSET      :
    return icm8_arb_conf;

  case SOC_ICM9_ARB_CONF_OFFSET      :
    return icm9_arb_conf;

  case SOC_DMA_CHN_CONF_OFFSET       :
    return dma_conf;

  case SOC_USB_PHY_OFFSET            :
    return usb_conf;

  case SOC_GMAC_CONF_OFFSET          :
    return gmac_conf;

  case SOC_EXPI_CONF_OFFSET :
    return expand_conf;

  case SOC_POWER_DOWN_CONF_OFFSET :
    return powerdown_conf;

  case SOC_1V8_CONF_OFFSET :
    return ddr_1v8_conf;

  case SOC_2V5_CONF_OFFSET :
    return ddr_2v5_conf;

  case SOC_3V3_CONF_OFFSET :
    return ddr_3v3_conf;

  case SOC_DDRPAD_CONF_OFFSET :
    return ddr_pad_conf;

  // should not happen
  default :
    error() << "Try to read non suported SYSCTRL register " << endl;
    exit(1);
  }

}

void SoC_Config::write_word(uint32_t addr, uint32_t d) {
  if (!soc_ctrl_valid_word_address(addr)) {
    error() << "Invalid write word address" << endl;
    exit(1);
  }

  switch (addr) {
  case SOC_CTRL_SOC_CFG_OFFSET :
    soc_config = d;
    debug() << "Write soc_config register " << endl;
    return;

  case SOC_CTRL_DIAG_CFG_OFFSET :
    diag_config = d;
    debug() << "Write soc_config register " << endl;
    return;

  case SOC_CTRL_PLL1_CTRL_OFFSET     :
     pll1_control = d;
     if (d & PLL_ENABLE_MASK) {
       pll1_control |= PLL_LOCK_STATUS;
       debug() << "LOCK PLL1 " << endl;
     }
     else
       debug() << "Write pll1_control register " << endl;
     return;

  case SOC_CTRL_PLL1_FRQ_OFFSET      :
     pll1_freq = d;
    debug() << "Write  pll1_freq register " << endl;
     return;

  case SOC_CTRL_PLL1_MOD_OFFSET      :
     pll1_mode = d;
    debug() << "Write  pll1_mode register " << endl;
     return;

  case SOC_CTRL_PLL2_CTRL_OFFSET     :
     pll2_control = d;
      if (d & PLL_ENABLE_MASK) {
       pll2_control |= PLL_LOCK_STATUS;
       debug() << "LOCK PLL2 " << endl;
     }
     else
       debug() << "Write  pll2_control register " << endl;
     return;

  case SOC_CTRL_PLL2_FRQ_OFFSET      :
     pll2_freq = d;
    debug() << "Write  pll2_freq register " << endl;
     return;

  case SOC_CTRL_PLL2_MOD_OFFSET      :
     pll2_mode = d;
    debug() << "Write  pll2_mode register " << endl;
     return;

  case SOC_CTRL_PLL_CLK_OFFSET       :
     pll_clock_conf = d;
    debug() << "Write  pll_clock_conf register " << endl;
     return;

  case SOC_CTRL_CORE_CLK_OFFSET      :
     core_clock_conf = d;
    debug() << "Write  core_clock_conf register " << endl;
     return;

  case SOC_CTRL_PER_CLK_OFFSET       :
     periph_clock_conf = d;
    debug() << "Write  periph_clock_conf register " << endl;
     return;

  case SOC_CTRL_PER1_CLK_ENB_OFFSET  :
     per1_clock_enable = d;
    debug() << "Write  per1_clock_enable register " << endl;
     return;

  case SOC_CTRL_PER2_CLK_ENB_OFFSET  :
     per2_clock_enable = d;
    debug() << "Write  per2_clock_enable register " << endl;
     return;

  case SOC_CTRL_RAS_CLK_ENB_OFFSET   :
     ras_clock_enable = d;
    debug() << "Write  ras_clock_enable register " << endl;
     return;

  case SOC_CTRL_PER1_SOF_RST_OFFSET  :
     per1_soft_reset = d;
    debug() << "Write  per1_soft_reset register " << endl;
     return;

  case SOC_CTRL_PER2_SOF_RST_OFFSET  :
     per2_soft_reset = d;
    debug() << "Write  per2_soft_reset register " << endl;
     return;

  case SOC_CTRL_RAS_SOF_RST_OFFSET   :
     ras_soft_reset = d;
    debug() << "Write  ras_soft_reset register " << endl;
     return;

  case SOC_CTRL_PRSC1_CLK_OFFSET     :
     prsc1_clock_conf = d;
    debug() << "Write  prsc1_clock_conf register " << endl;
     return;

  case SOC_CTRL_PRSC2_CLK_OFFSET     :
     prsc2_clock_conf = d;
    debug() << "Write  prsc2_clock_conf register " << endl;

  case SOC_CTRL_PRSC3_CLK_OFFSET     :
     prsc3_clock_conf = d;
    debug() << "Write  prsc3_clock_conf register " << endl;
     return;

  case SOC_CTRL_AMEM_CLK_OFFSET      :
     amem_clock_conf = d;
    debug() << "Write  amem_clock_conf register " << endl;
     return;

  case SOC_CTRL_EXP_CLK_OFFSET       :
     expand_clock_conf = d;
    debug() << "Write  expand_clock_conf register " << endl;
     return;

  case SOC_CTRL_LCD_CLK_OFFSET       :
     lcd_clock_synt = d;
    debug() << "Write  lcd_clock_synt register " << endl;
     return;

  case SOC_CTRL_IRDA_CLK_OFFSET      :
     irda_clock_synt = d;
    debug() << "Write  irda_clock_synt register " << endl;
     return;

  case SOC_CTRL_UART_CLK_OFFSET      :
     uart_clock_synt = d;
    debug() << "Write  uart_clock_synt register " << endl;
     return;

  case SOC_CTRL_GMAC_CLK_OFFSET      :
     gmac_clock_synt = d;
    debug() << "Write  gmac_clock_synt register " << endl;
     return;

  case SOC_CTRL_RAS1_CLK_OFFSET      :
     ras1_clock_synt = d;
    debug() << "Write  ras1_clock_synt register " << endl;
     return;

  case SOC_CTRL_RAS2_CLK_OFFSET      :
     ras2_clock_synt = d;
    debug() << "Write  ras2_clock_synt register " << endl;
     return;

  case SOC_CTRL_RAS31_CLK_OFFSET     :
     ras3_clock_synt = d;
    debug() << "Write  ras3_clock_synt register " << endl;
     return;

  case SOC_CTRL_RAS41_CLK_OFFSET     :
     ras4_clock_synt = d;
    debug() << "Write  ras4_clock_synt register " << endl;
     return;

  case SOC_ICM1_ARB_CONF_OFFSET      :
     icm1_arb_conf = d;
    debug() << "Write  icm1_arb_conf register " << endl;
     return;

  case SOC_ICM2_ARB_CONF_OFFSET      :
     icm1_arb_conf = d;
    debug() << "Write  icm1_arb_conf register " << endl;
     return;

  case SOC_ICM3_ARB_CONF_OFFSET      :
     icm1_arb_conf = d;
    debug() << "Write  icm1_arb_conf register " << endl;
     return;

  case SOC_ICM4_ARB_CONF_OFFSET      :
     icm2_arb_conf = d;
    debug() << "Write  icm2_arb_conf register " << endl;
     return;

  case SOC_ICM5_ARB_CONF_OFFSET      :
     icm5_arb_conf = d;
    debug() << "Write  icm5_arb_conf register " << endl;
     return;

  case SOC_ICM6_ARB_CONF_OFFSET      :
     icm6_arb_conf = d;
    debug() << "Write  icm6_arb_conf register " << endl;
     return;

  case SOC_ICM7_ARB_CONF_OFFSET      :
     icm7_arb_conf = d;
    debug() << "Write  icm7_arb_conf register " << endl;
     return;

  case SOC_ICM8_ARB_CONF_OFFSET      :
     icm8_arb_conf = d;
    debug() << "Write  icm8_arb_conf register " << endl;
     return;

  case SOC_ICM9_ARB_CONF_OFFSET      :
     icm9_arb_conf = d;
    debug() << "Write  icm9_arb_conf register " << endl;
     return;

  case SOC_DMA_CHN_CONF_OFFSET       :
     dma_conf = d;
     debug() << "Write  dma_conf register " << endl;
     return;

  case SOC_USB_PHY_OFFSET            :
     usb_conf = d;
     debug() << "Write  usb_conf register " << endl;
     return;

  case SOC_GMAC_CONF_OFFSET          :
    gmac_conf = d;
    debug() << "Write  gmac_conf register " << endl;
    return;

  case SOC_EXPI_CONF_OFFSET          :
    expand_conf = d;
    debug() << "Write exoand register " << endl;
    return;

  case SOC_POWER_DOWN_CONF_OFFSET :
    debug() << "Write power down register " << endl;
    powerdown_conf = d;
    return ;

  case SOC_1V8_CONF_OFFSET :
    debug() << "Write 1v8 register " << endl;
    ddr_1v8_conf = d;
    return ;

  case SOC_2V5_CONF_OFFSET :
    debug() << "Write 2v5 register " << endl;
    ddr_2v5_conf = d;
    return ;

  case SOC_3V3_CONF_OFFSET :
    debug() << "Write 3v3 register " << endl;
    ddr_3v3_conf = d;
    return ;

  case SOC_DDRPAD_CONF_OFFSET :
    debug() << "Write ddr pad register " << endl;
    ddr_pad_conf = d;
    return ;


  // should not happen
  default:
    error() << "Invalid write SYSCTRL  pll1_control register" << endl;
    exit(1);
  }

}

} // namespace simsoc
