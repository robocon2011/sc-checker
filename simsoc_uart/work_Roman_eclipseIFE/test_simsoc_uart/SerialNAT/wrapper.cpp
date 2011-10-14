//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "libsimsoc/components/memory.hpp"
#include "libsimsoc/components/bus.hpp"
#include "libsimsoc/components/uart_16550.hpp"
#include "wrapper_send.hpp"
#include "wrapper_receive.hpp"
#include "libsimsoc/components/dce_null_modem.hpp"
#include "libsimsoc/context.hpp"

const uint32_t START = 0x100000;
const uint32_t DEST = 0x200000;

using namespace std;
using namespace sc_core;
using namespace simsoc;

class SubSystemSend: public Module {
public:
  static const uint32_t MEM_BASE  = 0x00000000;
  static const uint32_t MEM_SIZE  =  0x4000000;
  static const uint32_t UART_BASE = 0x11000000;

  Bus bus;
  Memory mem;
  Uart16550 uart;
  WrapperSend proc;

  SubSystemSend(sc_module_name name,
                uint32_t start, uint32_t size):
    Module(name),
    // module instantiation
    bus("BUS"),
    mem("MEMORY", MEM_SIZE),
    uart("UART"),
    proc("SENDER",start,size)
  {
    proc.rw_port(bus.target_sockets);
    uart.it_signal(proc.it_signal);
    bus.bind_target(mem.rw_socket, MEM_BASE, MEM_SIZE);
    bus.bind_target(uart.rw_port, UART_BASE, Uart16550::LENGTH);

    // init memory (write the alphabet size/26 times)
    uint8_t* host_mem = (uint8_t*) mem.get_host_address();
    char c = 'a';
    for (size_t i = 0; i<size; ++i) {
      host_mem[start+i] = c;
      if (c=='z')
        c = 'a';
      else
        ++c;
    }
  }
};

class SubSystemReceive: public Module {
public:
  static const uint32_t MEM_BASE  = 0x00000000;
  static const uint32_t MEM_SIZE  =  0x4000000;
  static const uint32_t UART_BASE = 0x11000000;

  Bus bus;
  Memory mem;
  Uart16550 uart;
  WrapperReceive proc;

  SubSystemReceive(sc_module_name name,
                   uint32_t dest):
    Module(name),
    // module instantiation
    bus("BUS"),
    mem("MEMORY", MEM_SIZE),
    uart("UART"),
    proc("RECEIVER",dest)
  {
    proc.rw_port(bus.target_sockets);
    uart.it_signal(proc.it_signal);
    bus.bind_target(mem.rw_socket, MEM_BASE, MEM_SIZE);
    bus.bind_target(uart.rw_port, UART_BASE, Uart16550::LENGTH);
  }
};

class Top: public Module {
  public:
  const uint32_t N;
  SubSystemSend soc0;
  SubSystemReceive soc1;
  NullModem serial_line;
  Top(sc_module_name name,
      uint32_t n):
    Module(name),
    N(n),
    soc0("SOC0",START,N*26),
    soc1("SOC1",DEST),
    serial_line("SERIAL_LINE")
  {
    serial_line.dte_0 = &soc0.uart;
    soc0.uart.dce = &serial_line.dce_0;
    serial_line.dte_1 = &soc1.uart;
    soc1.uart.dce = &serial_line.dce_1;
  }

  ~Top() {
    // check the memory
    uint8_t* sender_mem = (uint8_t*) soc0.mem.get_host_address();
    uint8_t* receiver_mem = (uint8_t*) soc1.mem.get_host_address();
    for (size_t i = 0; i<N*26; ++i) {
      if (sender_mem[START+i]!=receiver_mem[DEST+i]) {
        error() <<"Transmission Error! (character number " <<dec <<i <<")\n";
        exit(1);
      }
    }
    cout <<"Transmission OK." <<endl;
  }
};

int sc_main(int argc, char *argv[])
{
  ParameterInt size("TOP","-n","control the length of the test",10000);
  simsoc_init(argc,argv);
  Top top("TOP",size.get());
  sc_start();
  return 0;
}
