#ifndef PPC_FPSC_REGISTER_HPP
#define PPC_FPSC_REGISTER_HPP

#include <libsimsoc/display.hpp>
#include <inttypes.h>
#include <cassert>

namespace simsoc {
  class PPC_Processor;

  typedef enum FPCondition{
    No_Cond=0,//reset value
    FL=8,//less than or negative
    FG=4,//greater than or positive
    FE=2,//equal or zero
    FU=1//unordered or NaN
  }fpcc_t;

  typedef enum RoundControl{
    Round_Nearest=0,
    Round_Zero=1,
    Round_Pinfinity=2,
    Round_Minfinity=3
  }fp_rnd_t;

  typedef enum ResultValueClass{
    NON=0,
    QNAN=0x11,
    MINF=0x9,
    MNORM=0x8,
    MDORM=0x18,
    MZERO=0x12,
    RVC_PZERO=0x2, // "PZERO" conflicts with a macro in Apple /usr/include//sys/param.h
    PDORM=0x14,
    PNORM=0x4,
    PINF=0x5
  }result_class_t;

  typedef enum FPSCR_Index{
    OX = 3,
    UX = 4,
    ZX = 5,
    XX = 6,
    VXSNAN = 7,
    VXISI = 8,
    VXIDI = 9,
    VXZDZ = 10,
    VXIMZ = 11,
    VXVC = 12,
    VXSOFT = 21,
    VXSQRT = 22,
    VXCVI = 23
  }fpscr_excp_t;

  struct PPC_FPExcpId: Printable {
    fpscr_excp_t id;
    PPC_FPExcpId(fpscr_excp_t n):id(n){}
    virtual std::ostream &display(std::ostream &os) const;
  };

  extern const char * FPSCR_BIT_NAMES[32];

  typedef class PPC_FPSCRegister{
  public:
    friend class PPC_FloatPoint_Unit;

    PPC_FPSCRegister(PPC_Processor* _proc):reg(),proc(_proc){
      assert(proc);
    };

    void set_bit(uint8_t index,bool value){
      if(index!=FEX || index != VX){
        set(index,value);
        update_vx();
        update_fex();
      }
    }

    void set_excp(fpscr_excp_t index);
    void set_fi(bool value);
    inline void set_fr(bool value){ set(FR,value);};
    inline void set_fprf(result_class_t value){
      uint8_t data = static_cast<uint8_t>(value) & 0x1f;
      reg &= ~(0x1f<<FPRF_SHIFT);
      reg |= data << FPRF_SHIFT;
    };
    inline void set_fpcc(fpcc_t value){
      uint8_t data = static_cast<uint8_t>(value) & 0xf;
      reg &= ~(0xf<<FPCC_SHIFT);
      reg |= data << FPCC_SHIFT;
    };
    inline void set_rn(fp_rnd_t value){
      uint8_t data = static_cast<uint8_t>(value) & 0x3;
      reg &= ~(0x3);
      reg |= data;
    };
    inline uint8_t get_rn(){return reg & 0x3;};
    const uint32_t get_value() const{return reg;};
    void dump_value();

    uint8_t move_field_to_cr(uint8_t field);
    uint8_t get_field(uint8_t field);
    void set_field(uint8_t field,const uint8_t value);


    inline bool get_ve(){return reg & VE_MASK;};
    inline bool get_oe(){return reg & OE_MASK;};
    inline bool get_ue(){return reg & UE_MASK;};
    inline bool get_ze(){return reg & ZE_MASK;};
    inline bool get_fex(){return reg & FEX_MASK;};
  private:

    static const uint8_t FX = 0;
    static const uint8_t FEX = 1;
    static const uint8_t FEX_MASK = 30;
    static const uint8_t VX = 2;
    static const uint32_t INVALID_EXCEPTION_MASK = 0x01f80700;
    static const uint8_t EXCEPTIONBITS_SHIFT = 25;
    static const uint8_t FR = 13;
    static const uint8_t FI = 14;
    static const uint8_t FPRF = 15;
    static const uint8_t FPRF_SHIFT = 12;
    static const uint8_t C = 15;
    static const uint8_t FPCC = 16;
    static const uint8_t FPCC_SHIFT = 12;
    static const uint8_t VE = 24;
    static const uint8_t VE_MASK = 7;
    static const uint8_t OE = 25;
    static const uint8_t OE_MASK = 6;
    static const uint8_t UE = 26;
    static const uint8_t UE_MASK = 5;
    static const uint8_t ZE = 27;
    static const uint8_t ZE_MASK = 4;
    static const uint8_t XE = 28;
    static const uint8_t ENABLEBITS_SHIFT = 3;
    static const uint8_t NI = 29;
    static const uint8_t RN = 30;

    static const uint8_t field_exceptions[8];

    inline void set(uint8_t index,bool value){
      if(value)
        reg |= 1<<(31-index);
      else
        reg &= ~(1<<(31-index));
    };
    inline bool get(uint8_t index){return reg & 1<<(31-index);};

    void update_fex();
    void update_vx();
    uint32_t reg;

  private:
    PPC_Processor* proc;
  } PPC_FPSCR;

} // namespace simsoc

#endif // PPC_FPSC_REGISTER_HPP
