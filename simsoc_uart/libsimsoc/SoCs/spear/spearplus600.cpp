//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "spearplus600.hpp"
#include "libsimsoc/display.hpp"

using namespace sc_core;
using namespace std;

namespace simsoc {

ParameterBool arm_v6("ARM processor", "-v6",
                     "Use the ARMv6 ISS based on simlight2");

SPEArPlus600::SPEArPlus600(sc_module_name name,
                           StopBox *sb):
  Module(name),
  bus("BUS"),
  dram("DRAM", DRAM_SIZE),
  sram("SRAM", SRAM_SIZE),
  arm_processor(NULL),
  uart0("UART0"),
  uart1("UART1"),
  fsmc("FSMC"),
  nand_flash("NAND_FLASH",  0),
  gmac("GMAC"),
  itc("VIC_CHAIN", 2),
  pll("PLL", "PLL not enabled", 1),
  ahb("AHB", "AHB not enabled", 1),
  spi1("SPI1", "SPI1 not enabled", 1),
  spi2("SPI2", "SPI2 not enabled",  1),
  spi3("SPI3", "SPI3 not enabled", 1),
  i2c("I2C", "I2C not enabled", 0),
  gpio0("GPIO0", "GPIO0 not enabled", 0),
  gpio1("GPIO1", "GPIO1 not enabled", 0),
  gpio2("GPIO2", "GPIO2 not enabled", 0),
  adc("ADC", "ADC not enabled", 1),
  //   res0("RES0", "RES0 not enabled", 0),
  //   res1("RES1", "RES1 not enabled", 0),
  //   res2("RES2", "RES2 not enabled", 0),
  //   res3("RES3", "RES3 not enabled", 0),
  //   res4("RES4", "RES4 not enabled", 0),
  timer0("TIMER0"),
  timer1("TIMER1"),
  timer2("TIMER2", "TIMER2 not enabled", 1),
  timer3("TIMER3", "TIMER3 not enabled", 1),
  serial_flash("SERIAL_BANK0", 0), // Bank 0 enabled
  smi("SMI_CTRL", &serial_flash, NULL, NULL, NULL), // init serial memory with bank0
  jpeg("JPEG","JPEG  not enabled", 1),
  irda("IRDA","IRDA  not enabled", 1),
  lcd("LCD", "LCD  not enabled", 1),
  dma("DMAC"),
  sdram_ctrl("SDRAM_CTRL"),
  rtc("RTC", "RTC not enabled", 0),
  usb("USB", "USB  not enabled", 0),
  usb_config_reg("USB_CONFIG_REGISTER","USB CONFIGURATION REGISTER not enabled",0),
  usb_plug_detect("USB_PLUG_DETECT","USB PLUG DETECT not enabled",0),
  usb_ehci1("USB_EHCI1", "USB EHCI1  not enabled", 0),
  usb_ohci1("USB_OHCI1", "USB OHCI1 not enabled",0),
  usb_ehci2("USB_EHCI2", "USB EHCI2 not enabled",0),
  usb_ohci2("USB_OHCI2", "USB OHCI2 not enabled",0),
  usb_arb("USB_ARB", "USB arbitration not enabled", 1),
  watchdog("WATCHDOG"),
  sys("PRIMEXSYS_CTRL"),
  soc_conf("SoC_Config"),
  cons("CONSOLE",sb),
  rom("ROM","ROM not enabled",0)
{
  debug() << "building spear plus\n" << endl;

  if (arm_v6.get())
    arm_processor = new ARMv6_Processor("PROCESSOR");
  else
    arm_processor = new ARM_Processor("PROCESSOR");

  // set initiators
  if (arm_v6.get()) {
    ARMv6_Processor *arm_v6 = static_cast<ARMv6_Processor*>(arm_processor);
    arm_v6->mmu.rw_socket(bus.target_sockets);
    itc.irq_port(arm_v6->irq_port);
    itc.fiq_port(arm_v6->fiq_port);

    // disable "unpredictable" fatal error on unaligned access 
    // Otherwise, the SPEAr does not boot with the Linux from ST.
    arm_v6->cp15.control |= ARMv6_SystemCoproc::CONTROL_U;
  } else {
    ARM_Processor *arm_v5 = static_cast<ARM_Processor*>(arm_processor);
    arm_v5->mmu.rw_socket(bus.target_sockets);
    itc.irq_port(arm_v5->irq_port);
    itc.fiq_port(arm_v5->fiq_port);
  }

  gmac.out_port(bus.target_sockets);
  cons.initiator_socket(arm_processor->debug_port);
  dma.initiator_socket(bus.target_sockets);

  // set IRQ ports
  uart0.it_signal(itc.in_ports[IRQ_UART0]);
  uart1.it_signal(itc.in_ports[IRQ_UART1]);
  gmac.it_port0(itc.in_ports[IRQ_ETHERNET0]);
  gmac.it_port1(itc.in_ports[IRQ_ETHERNET1]);
  timer0.channels[0].it_port(itc.in_ports[IRQ_ARM_SUBSYS_TIMER0]);
  timer0.channels[1].it_port(itc.in_ports[IRQ_ARM_SUBSYS_TIMER1]);
  timer1.channels[0].it_port(itc.in_ports[IRQ_APP_SUBSYS_TIMER1_0]);
  timer1.channels[1].it_port(itc.in_ports[IRQ_APP_SUBSYS_TIMER1_1]);
  dma.dmacintr(itc.in_ports[IRQ_BASIC_SUBSYS_DMA]);

  // stubs
  debug() << "binding components\n";

  // bus
  bus.bind_target(dram.rw_socket, DRAM_BASE, 0x40000000);
  bus.bind_target(sram.rw_socket, SRAM_BASE, 0x5800000);
  bus.bind_target(uart0.rw_port, UART0_BASE, 0x80000);
  bus.bind_target(uart1.rw_port, UART1_BASE, 0x80000);
  bus.bind_target(cons.target_socket, CONS_BASE, DebugConsole::SIZE);
  bus.bind_target(fsmc.rw_port, FSMC_BASE, 0x800000);
  bus.bind_target(gmac.in_port, GMAC_BASE, 0x800000);
  bus.bind_target(itc[0]->rw_port, VIC0_BASE, 0x100000);
  bus.bind_target(itc[1]->rw_port, VIC1_BASE, 0x100000);
  bus.bind_target(nand_flash.rw_port, NAND_FLASH_BASE, 0x800000);
  bus.bind_target(sys.rw_port, SYS_CTL_BASE, 0x80000);
  bus.bind_target(watchdog.rw_port, WATCHDOG_BASE, 0x80000);
  bus.bind_target(soc_conf.rw_port, SoC_CONF_BASE, 0x80000);
  bus.bind_target(smi.rw_port, SMI_CTRL_BASE, 0x200000);
  bus.bind_target(sdram_ctrl.rw_port, SDRAM_CTRL_BASE, 0x200000);
  bus.bind_target(serial_flash.rw_port, SERIAL_FLASH_BASE, 0x4000000);

  debug() << "binding stubs\n";
  bus.bind_target(pll.rw_port, PLL_BASE, 0x80000000);
  bus.bind_target(ahb.rw_port, AHB_BASE, 0x10000000);
  bus.bind_target(spi1.rw_port, SPI1_BASE, 0x80000);
  bus.bind_target(spi2.rw_port, SPI2_BASE, 0x80000);
  bus.bind_target(spi3.rw_port, SPI3_BASE, 0x80000);
  bus.bind_target(i2c.rw_port, I2C_BASE, 0x80000);
  bus.bind_target(gpio0.rw_port, GPIO0_BASE, 0x80000);
  bus.bind_target(gpio1.rw_port, GPIO1_BASE, 0x100000);
  bus.bind_target(gpio2.rw_port, GPIO2_BASE, 0x80000);
  bus.bind_target(adc.rw_port, ADC_BASE, 0x80000);
  //   bus.bind_target(res0.rw_port, RES0_BASE);
  //   bus.bind_target(res1.rw_port, RES1_BASE);
  //   bus.bind_target(res2.rw_port, RES2_BASE);
  bus.bind_target(timer0.rw_port, TIMER0_BASE, 0x80000);
  bus.bind_target(timer1.rw_port, TIMER1_BASE, 0x80000);
  bus.bind_target(timer2.rw_port, TIMER2_BASE, 0x80000);
  bus.bind_target(timer3.rw_port, TIMER3_BASE, 0x80000);
  //   bus.bind_target(res3.rw_port, RES3_BASE);
  bus.bind_target(usb.rw_port, USB_BASE, 0x100000);
  bus.bind_target(usb_config_reg.rw_port,USB_CONFIG_REG, 0x100000);
  bus.bind_target(usb_plug_detect.rw_port,USB_PLUG_DETECT, 0x100000);
  bus.bind_target(usb_ehci1.rw_port, USB_EHCI1_BASE, 0x100000);
  bus.bind_target(usb_ohci1.rw_port,USB_OHCI1_BASE, 0x100000);
  bus.bind_target(usb_ehci2.rw_port, USB_EHCI2_BASE, 0x100000);
  bus.bind_target(usb_ohci2.rw_port,USB_OHCI2_BASE, 0x100000);
  bus.bind_target(usb_arb.rw_port, USB_ARB_BASE, 0x10000);
  //   bus.bind_target(res4.rw_port, RES4_BASE);
  bus.bind_target(lcd.rw_port, LCD_BASE, 0x200000);
  bus.bind_target(jpeg.rw_port, JPEG_BASE, 0x800000);
  bus.bind_target(irda.rw_port, IRDA_BASE, 0x800000);
  bus.bind_target(dma.target_socket, DMA_BASE, 0x200000);
  bus.bind_target(rtc.rw_port, RTC_BASE, 0x80000);
  bus.bind_target(rom.rw_port, INTER_ROM_BASE, 0x1000000);

  debug() << "Finished configuring spear plus\n";
}

SPEArPlus600::~SPEArPlus600() {
  debug() <<"desctructor called\n";
}

} // namespace simsoc
