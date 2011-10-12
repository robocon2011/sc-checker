//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef SPEARPLUS600_HPP
#define SPEARPLUS600_HPP

#include "libsimsoc/components/bus.hpp"
#include "libsimsoc/processors/arm/arm_processor.hpp"
#include "libsimsoc/processors/arm_v6/arm_v6_processor.hpp"
#include "libsimsoc/components/memory.hpp"
#include "libsimsoc/components/primecell_uart.hpp"
#include "libsimsoc/components/nand_flash.hpp"
#include "libsimsoc/components/serial_flash.hpp"
#include "libsimsoc/components/rw_stub.hpp"
#include "libsimsoc/components/gmac_univ.hpp"
#include "libsimsoc/components/primecell_vic_pl190.hpp"
#include "libsimsoc/components/primecell_dmac_pl080.hpp"
#include "libsimsoc/components/primexsys_ctrl.hpp"
#include "libsimsoc/components/watchdog.hpp"
#include "libsimsoc/components/st_smi.hpp"
#include "libsimsoc/SoCs/spear/spear_soc_conf.hpp"
#include "libsimsoc/SoCs/spear/spear_sdram.hpp"
#include "libsimsoc/SoCs/spear/spear_gpts.hpp"

// for debug only:
#include "libsimsoc/components/debug_console.hpp"

namespace simsoc {

class SPEArPlus600: public Module {
public:
  // Memory map
  static const uint32_t DRAM_BASE  = 0x00000000;
  static const uint32_t DRAM_SIZE  = 0x4000000;
  // PLL and AHB after RAM
  static const uint32_t PLL_BASE   = 0x40000000;
  static const uint32_t AHB_BASE   = 0xC0000000;

  // start ICM1
  static const uint32_t UART0_BASE      = 0xD0000000;
  static const uint32_t UART1_BASE      = 0xD0080000;
  static const uint32_t SPI1_BASE       = 0xD0100000;
  static const uint32_t SPI2_BASE       = 0xD0180000;
  static const uint32_t I2C_BASE        = 0xD0200000;
  static const uint32_t RES0_BASE       = 0xD0280000;
  static const uint32_t JPEG_BASE       = 0xD0800000;
  static const uint32_t IRDA_BASE       = 0xD1000000;
  static const uint32_t FSMC_BASE       = 0xD1800000;
  static const uint32_t NAND_FLASH_BASE = 0xD2000000;
  static const uint32_t SRAM_BASE       = 0xD2800000;
  static const uint32_t SRAM_SIZE       = 0x4000;

  // start ICM2
  static const uint32_t TIMER1_BASE   = 0xD8000000;
  static const uint32_t TIMER2_BASE   = 0xD8080000;
  static const uint32_t GPIO0_BASE    = 0xD8100000;
  static const uint32_t SPI3_BASE     = 0xD8180000;
  static const uint32_t ADC_BASE      = 0xD8200000;

  //start ICM4 mapped before icm3
  static const uint32_t RES1_BASE      = 0xE0000000;
  static const uint32_t GMAC_BASE      = 0xE0800000;
  static const uint32_t USB_BASE       = 0xE1000000;
  static const uint32_t USB_CONFIG_REG = 0xE1100000;
  static const uint32_t USB_PLUG_DETECT = 0xE1200000;
  static const uint32_t USB_EHCI1_BASE = 0xE1800000;
  static const uint32_t USB_OHCI1_BASE = 0xE1900000;
  static const uint32_t RES2_BASE      = 0xE1A00000;
  static const uint32_t USB_EHCI2_BASE  = 0xE2000000;
  static const uint32_t USB_OHCI2_BASE = 0xE2100000;
  static const uint32_t RES3_BASE      = 0xE2200000;
  static const uint32_t USB_ARB_BASE   = 0xE2800000;
  static const uint32_t RES4_BASE      = 0xE2900000;

  // start Multi Layer at 0xf0000
  static const uint32_t TIMER0_BASE  = 0xF0000000;
  static const uint32_t GPIO1_BASE   = 0xF0100000;
  static const uint32_t VIC0_BASE    = 0xF1100000; // after VIC1
  static const uint32_t VIC1_BASE    = 0xF1000000;

  //start ICM3 is after icm4
  static const uint32_t SERIAL_FLASH_BASE = 0xF8000000;
  static const uint32_t SMI_CTRL_BASE     = 0xFC000000;
  static const uint32_t LCD_BASE          = 0xFC200000;
  static const uint32_t DMA_BASE          = 0xFC400000;
  static const uint32_t SDRAM_CTRL_BASE   = 0xFC600000;
  static const uint32_t TIMER3_BASE       = 0xFC800000;
  static const uint32_t WATCHDOG_BASE     = 0xFC880000;
  static const uint32_t RTC_BASE          = 0xFC900000;
  static const uint32_t GPIO2_BASE        = 0xFC980000;
  static const uint32_t SYS_CTL_BASE      = 0xFCA00000;
  static const uint32_t SoC_CONF_BASE     = 0xFCA80000;
  static const uint32_t RES5_BASE         = 0xFCB00000;
  static const uint32_t INTER_ROM_BASE	  = 0xFF000000;

  // the console is used for debug only (not part of the real SoC):
  static const uint32_t CONS_BASE = RES5_BASE; // inside reserved memory map

  // IRQ's
  // 0: software interrupt
  // 1-6: processor intercommunication
  // 7-15: customizable logic
  static const uint32_t IRQ_ARM_SUBSYS_TIMER0 = 16;
  static const uint32_t IRQ_ARM_SUBSYS_TIMER1 = 17;
  static const uint32_t IRQ_ARM_SUBSYS_GPIO = 18;
  static const uint32_t IRQ19_SYSTEM_ERROR = 19;
  static const uint32_t IRQ_JPEG = 20;
  static const uint32_t IRQ_WAKEUP = 21;
  static const uint32_t IRQ_IRDA = 22;
  // 23: reserved
  static const uint32_t IRQ_UART0 = 24;
  static const uint32_t IRQ_UART1 = 25;
  static const uint32_t IRQ_SPI0 = 26;
  static const uint32_t IRQ_SPI1 = 27;
  static const uint32_t IRQ_I2C = 28;
  // 29-31: customizable logic
  static const uint32_t IRQ_APP_SUBSYS_TIMER0_0 = 32;
  static const uint32_t IRQ_APP_SUBSYS_TIMER0_1 = 33;
  static const uint32_t IRQ_APP_SUBSYS_TIMER1_0 = 34;
  static const uint32_t IRQ_APP_SUBSYS_TIMER1_1 = 35;
  static const uint32_t IRQ_APP_SUBSYS_GPIO = 36;
  static const uint32_t IRQ_APP_SUBSYS_SPI = 37;
  static const uint32_t IRQ_APP_SUBSYS_ADC = 38;
  // 39: reserved
  // 40: AHB_EXP Master
  static const uint32_t IRQ_DDRC = 41;
  static const uint32_t IRQ_BASIC_SUBSYS_DMA = 42;
  // 43: reserved
  static const uint32_t IRQ_BASIC_SUBSYS_SPI = 44;
  static const uint32_t IRQ_BASIC_SUBSYS_LCDC = 45;
  // 46: EXP_AHB_1
  // 47: reserved
  static const uint32_t IRQ_BASIC_SUBSYS_TIMER0 = 48;
  static const uint32_t IRQ_BASIC_SUBSYS_TIMER1 = 49;
  static const uint32_t IRQ_BASIC_SUBSYS_RTC = 50;
  static const uint32_t IRQ_BASIC_SUBSYS_GPIO = 51;
  static const uint32_t IRQ_BASIC_SUBSYS_WATCHDOG = 52;
  // 53: reserved
  // 54: AHB_EXP Slave
  static const uint32_t IRQ_ETHERNET0 = 55;
  static const uint32_t IRQ_ETHERNET1 = 56;
  static const uint32_t IRQ_USB2_DEVICE = 57;
  static const uint32_t IRQ_USB2_HOST1_OHCI = 58;
  static const uint32_t IRQ_USB2_HOST1_EHCI = 59;
  static const uint32_t IRQ_USB2_HOST2_OHCI = 60;
  static const uint32_t IRQ_USB2_HOST2_EHCI = 61;
  // 62-63: reserved

  Bus bus;
  Memory dram;
  Memory sram;
  Processor *arm_processor;
  //  ARM_Processor& proc;
  PrimeCellUart uart0;
  PrimeCellUart uart1;
  RW_Stub fsmc; // flexible memory controller
  NAND_Flash nand_flash;
  GMAC_Univ gmac;
  PrimeCell_PL190_VIC_chain itc;
  RW_Stub pll; // programmable logic layer
  RW_Stub ahb;
  RW_Stub spi1, spi2, spi3;
  RW_Stub i2c;
  RW_Stub gpio0, gpio1, gpio2;
  RW_Stub adc;
  // RW_Stub res0, res1, res2, res3, res4;
  GPTimers timer0;
  GPTimers timer1;
  RW_Stub timer2, timer3;
  SerialFlash serial_flash;
  SMICtrl smi; // serial memory interface
  RW_Stub jpeg;
  RW_Stub irda;
  RW_Stub lcd;
  PrimeCell_DMAC_PL080 dma;
  SDRAMCtrl sdram_ctrl;
  RW_Stub rtc; // real time clock
  RW_Stub usb, usb_config_reg,usb_plug_detect,usb_ehci1,usb_ohci1,usb_ehci2,usb_ohci2,usb_arb;
  WatchDog watchdog;
  PrimeXsysCtrl sys;
  SoC_Config soc_conf;

  // for debug only:
  DebugConsole cons;
  RW_Stub rom;
  SPEArPlus600(sc_core::sc_module_name name,
               StopBox *sb);

  virtual ~SPEArPlus600();
};

} // namespace simsoc

#endif //SPEARPLUS600_HPP
