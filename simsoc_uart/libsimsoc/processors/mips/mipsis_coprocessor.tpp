//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

// File included by "mipsis_coprocessor.hpp"

namespace simsoc {

template <typename word_t>
MIPS_bc2f<word_t>::MIPS_bc2f(uint8_t c,uint16_t f):
  cc(c),offset(f) {}

template <typename word_t>
void MIPS_bc2f<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("bc2f");
}

template <typename word_t>
std::ostream& MIPS_bc2f<word_t>::display(std::ostream& os) const {
  return os <<"bc2f\t" <<(int) cc<<" ," <<(int) offset;
}

/**********************************************************************************/

template <typename word_t>
MIPS_bc2fl<word_t>::MIPS_bc2fl(uint8_t c, uint16_t f):
  cc(c), offset(f) {}

template <typename word_t>
void MIPS_bc2fl<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("bc2fl");
}

template <typename word_t>
std::ostream& MIPS_bc2fl<word_t>::display(std::ostream& os) const {
  return os <<"bc2fl\t" <<(int) cc<<" ," <<(int) offset;
}

/**********************************************************************************/

template <typename word_t>
MIPS_bc2t<word_t>::MIPS_bc2t(uint8_t c, uint16_t f):
  cc(c),offset(f) {}


template <typename word_t>
void MIPS_bc2t<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("bc2t");
}

template <typename word_t>
std::ostream& MIPS_bc2t<word_t>::display(std::ostream& os) const {
  return os <<"bc2t\t" <<(int) cc<<" ," <<(int) offset;
}


template <typename word_t>
MIPS_Instruction<word_t>* mips_bc2t(uint32_t instr){
  uint8_t c;
  uint16_t f;
  MIPS_BC_FORMAT(instr,c,f);
  return new MIPS_bc2t<word_t>(c,f);
}

/**********************************************************************************/

template <typename word_t>
MIPS_bc2tl<word_t>::MIPS_bc2tl(uint8_t c, uint16_t f):
  cc(c),offset(f) {}

template <typename word_t>
void MIPS_bc2tl<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("bc2tl");
}

template <typename word_t>
std::ostream& MIPS_bc2tl<word_t>::display(std::ostream& os) const {
  return os <<"bc2tl\t" <<(int) cc<<" ," <<(int) offset;
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_bc2tl(uint32_t instr){
  uint8_t c;
  uint16_t f;
  MIPS_BC_FORMAT(instr,c,f);
  return new MIPS_bc2tl<word_t>(c,f);
}


/**********************************************************************************/

template <typename word_t>
MIPS_cfc2<word_t>::MIPS_cfc2(uint8_t t, uint32_t i):
  rt(t),immed(i) {}

template <typename word_t>
void MIPS_cfc2<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("cfc2");
}

template <typename word_t>
std::ostream& MIPS_cfc2<word_t>::display(std::ostream& os) const {
  return os <<"bne\t" <<(int) rt<< ", "<<(int) immed;
}

/***********************************************************************************/

template <typename word_t>
MIPS_ctc2<word_t>::MIPS_ctc2(uint8_t t,uint32_t i):
  rt(t),immed(i) {}

template <typename word_t>
void MIPS_ctc2<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("ctc2");
}

template <typename word_t>
std::ostream& MIPS_ctc2<word_t>::display(std::ostream& os) const{
  return os <<"ctc2\t"<<(int) rt<<", "<<(int) immed;
}

/***********************************************************************************/

template <typename word_t>
MIPS_mfc2<word_t>::MIPS_mfc2(uint8_t s, uint8_t t, uint32_t i):
  rs(s),rt(t),sel(i) {}

template <typename word_t>
void MIPS_mfc2<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("mfc2");
}

template <typename word_t>
std::ostream& MIPS_mfc2<word_t>::display(std::ostream& os) const{
  return os <<"mfc2\t"<<(int) rs<<", "<<(int) rt<<", "<<(int) sel;
}

/***********************************************************************************/

template <typename word_t>
MIPS_ldc2<word_t>::MIPS_ldc2(uint8_t s,uint8_t t, uint32_t o):
  base(s),rt(t),offset(o) {}

template <typename word_t>
void MIPS_ldc2<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("ldc2");
}

template <typename word_t>
std::ostream& MIPS_ldc2<word_t>::display(std::ostream& os) const{
  return os <<"ldc2\t"<<(int) rt<<" ,"<<(int) offset<<", "<<(int) base;
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_ldc2(uint32_t instr){
  uint8_t s,t;
  uint32_t o;
  MIPS_I_FORMAT(instr,s,t,o);
  return new MIPS_ldc2<word_t>(s,t,o);
}

/***********************************************************************************/

template <typename word_t>
MIPS_lwc2<word_t>::MIPS_lwc2(uint8_t s,uint8_t t,uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_lwc2<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("lwc2");
}
template <typename word_t>
std::ostream& MIPS_lwc2<word_t>::display(std::ostream& os) const{
  return os <<"lwc2\t"<<(int) rt<<" ,"<<(int) offset<<", "<<(int) base;
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_lwc2(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_lwc2<word_t>(s,t,i);
}
/************************************************************************************/
template <typename word_t>
MIPS_sdc2<word_t>::MIPS_sdc2(uint8_t s,uint8_t t,uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_sdc2<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("sdc2");
}

template <typename word_t>
std::ostream& MIPS_sdc2<word_t>::display(std::ostream& os) const {
  return os <<"sdc2\t" <<(int) rt<< ", "<<(int) offset<<", " <<(int) base;
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_sdc2(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_sdc2<word_t>(s,t,i);
}
/**********************************************************************************/

template <typename word_t>
MIPS_swc2<word_t>::MIPS_swc2(uint8_t s,uint8_t t,uint32_t i):
  base(s),rt(t),offset(i) {}

template <typename word_t>
void MIPS_swc2<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("swc2");
}

template <typename word_t>
std::ostream& MIPS_swc2<word_t>::display(std::ostream& os) const {
  return os <<"swc2\t" <<(int) rt<< ", "<<(int) offset<<", " <<(int) base;
}

template <typename word_t>
MIPS_Instruction<word_t>* mips_swc2(uint32_t instr){
  uint8_t s,t;
  uint32_t i;
  MIPS_I_FORMAT(instr,s,t,i);
  return new MIPS_swc2<word_t>(s,t,i);
}
/***********************************************************************************/
/*
  template <typename word_t>
MIPS_cop2::MIPS_cop2(typename MIPS_Instruction<word_t>::bus_width_t u):
  cofun(u) {}

std::ostream& MIPS_cop2::display(std::ostream& os) const{
  return os <<"cop2\t"<<(int) cofun;
}
*/

/***********************************************************************************/
template <typename word_t>
MIPS_mtc2<word_t>::MIPS_mtc2(uint8_t s,uint8_t t,uint32_t i):
  rs(s),rt(t),sel(i) {}

template <typename word_t>
void MIPS_mtc2<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("mtc2");
}

template <typename word_t>
std::ostream& MIPS_mtc2<word_t>::display(std::ostream& os) const{
  return os <<"mtc2\t"<<(int) rs<<", "<<(int) rt<<", "<<(int) sel;
}

/***********************************************************************************///MIPS64

template <typename word_t>
MIPS_dmfc2<word_t>::MIPS_dmfc2(uint8_t s,uint8_t t,uint32_t i):
  rs(s),rt(t),sel(i) {}

template <typename word_t>
void MIPS_dmfc2<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("dmfc2");
}

template <typename word_t>
std::ostream& MIPS_dmfc2<word_t>::display(std::ostream& os) const{
  return os <<"dmfc2\t"<<(int) rs<<", "<<(int) rt<<", "<<(int) sel;
}

/*****************************************************************************///MIPS64
template <typename word_t>
MIPS_dmtc2<word_t>::MIPS_dmtc2(uint8_t s,uint8_t t,uint32_t i):
  rs(s),rt(t),sel(i) {}

template <typename word_t>
void MIPS_dmtc2<word_t>::exec(MIPS_Processor<word_t> &proc)
{
  TODO("dmtc2");
}

template <typename word_t>
std::ostream& MIPS_dmtc2<word_t>::display(std::ostream& os) const{
  return os <<"dmtc2\t"<<(int) rs<<", "<<(int) rt<<", "<<(int) sel;
}

/***********************************************************************************/


//declare the function

#if 0 // This code seems useless, because theses functions are defined above
template <typename word_t>
MIPS_Instruction<word_t>* mips_bc2t(uint32_t instr);

template <typename word_t>
MIPS_Instruction<word_t>* mips_bc2tl(uint32_t instr);

template <typename word_t>
MIPS_Instruction<word_t>* mips_ldc2( uint32_t instr);

template <typename word_t>
MIPS_Instruction<word_t>* mips_lwc2( uint32_t instr);

template <typename word_t>
MIPS_Instruction<word_t>* mips_sdc2( uint32_t instr);

template <typename word_t>
MIPS_Instruction<word_t>* mips_swc2(uint32_t instr);

template <typename word_t>
MIPS_Instruction<word_t>* mips_dmfc2( uint32_t instr);
#endif //0

} // namespace simsoc
