//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#ifndef PPC_LLVM_GENERATOR_HPP
#define PPC_LLVM_GENERATOR_HPP

#include "ppcis_visitor.hpp"
#include <llvm/LLVMContext.h>
#include <llvm/Support/IRBuilder.h>
#include <libsimsoc/profiling.hpp>
#include <fstream>

namespace llvm {
  class PassManager;
  class FunctionPassManager;
  class ExecutionEngine;
}

namespace simsoc {

  class PPC_BasicBlock;
  class PPC_OptimizedBasicBlock;

  class PPC_LLVM_Generator: PPC_InstructionVisitor {
    friend class PPC_LLVM_Deleter;
    PPC_LLVM_Generator();
    ~PPC_LLVM_Generator();
    static PPC_LLVM_Generator *singleton;
  public:
    static PPC_LLVM_Generator &get();

    PPC_OptimizedBasicBlock *compile(PPC_BasicBlock*);

    // ppcis.hpp
    void visit(PPC_Instruction &instruction);

    // ppcis_alu.hpp
    void visit(PPC_add &instruction);
    void visit(PPC_add_ &instruction);
    void visit(PPC_addc &instruction);
    void visit(PPC_addc_ &instruction);
    void visit(PPC_addco &instruction);
    void visit(PPC_addco_ &instruction);
    void visit(PPC_adde &instruction);
    void visit(PPC_adde_ &instruction);
    void visit(PPC_addeo &instruction);
    void visit(PPC_addeo_ &instruction);
    void visit(PPC_addme &instruction);
    void visit(PPC_addme_ &instruction);
    void visit(PPC_addmeo &instruction);
    void visit(PPC_addmeo_ &instruction);
    void visit(PPC_addze &instruction);
    void visit(PPC_addze_ &instruction);
    void visit(PPC_addzeo &instruction);
    void visit(PPC_addzeo_ &instruction);
    void visit(PPC_addic &instruction);
    void visit(PPC_addic_ &instruction);
    void visit(PPC_addo &instruction);
    void visit(PPC_addo_ &instruction);
    void visit(PPC_and &instruction);
    void visit(PPC_and_ &instruction);
    void visit(PPC_andc &instruction);
    void visit(PPC_andc_ &instruction);
    void visit(PPC_andi_ &instruction);
    void visit(PPC_andis_ &instruction);
    void visit(PPC_cmp &instruction);
    void visit(PPC_cmpl &instruction);
    void visit(PPC_cmpli &instruction);
    void visit(PPC_cntlzw &instruction);
    void visit(PPC_cntlzw_ &instruction);
    void visit(PPC_crand &instruction);
    void visit(PPC_crandc &instruction);
    void visit(PPC_creqv &instruction);
    void visit(PPC_crnand &instruction);
    void visit(PPC_crnor &instruction);
    void visit(PPC_cror &instruction);
    void visit(PPC_crorc &instruction);
    void visit(PPC_crxor &instruction);
    void visit(PPC_divw &instruction);
    void visit(PPC_divw_ &instruction);
    void visit(PPC_divwo &instruction);
    void visit(PPC_divwo_ &instruction);
    void visit(PPC_divwu &instruction);
    void visit(PPC_divwu_ &instruction);
    void visit(PPC_divwuo &instruction);
    void visit(PPC_divwuo_ &instruction);
    void visit(PPC_eqv &instruction);
    void visit(PPC_eqv_  &instruction);
    void visit(PPC_extsb  &instruction);
    void visit(PPC_extsb_ &instruction);
    void visit(PPC_extsh &instruction);
    void visit(PPC_extsh_ &instruction);
    void visit(PPC_or &instruction);
    void visit(PPC_or_ &instruction);
    void visit(PPC_orc &instruction);
    void visit(PPC_orc_ &instruction);
    void visit(PPC_neg &instruction);
    void visit(PPC_neg_ &instruction);
    void visit(PPC_nego  &instruction);
    void visit(PPC_nego_  &instruction);
    void visit(PPC_cmpi &instruction);
    void visit(PPC_addis &instruction);
    void visit(PPC_ori &instruction);
    void visit(PPC_oris &instruction);
    void visit(PPC_addi &instruction);
    void visit(PPC_rlwimi &instruction);
    void visit(PPC_rlwimi_ &instruction);
    void visit(PPC_rlwinm &instruction);
    void visit(PPC_rlwinm_ &instruction);
    void visit(PPC_rlwnm &instruction);
    void visit(PPC_rlwnm_ &instruction);
    void visit(PPC_sc &instruction);
    void visit(PPC_subf &instruction);
    void visit(PPC_subf_ &instruction);
    void visit(PPC_subfo &instruction);
    void visit(PPC_subfo_ &instruction);
    void visit(PPC_subfc &instruction);
    void visit(PPC_subfc_ &instruction);
    void visit(PPC_subfco &instruction);
    void visit(PPC_subfco_ &instruction);
    void visit(PPC_subfe &instruction);
    void visit(PPC_subfe_  &instruction);
    void visit(PPC_subfeo  &instruction);
    void visit(PPC_subfeo_ &instruction);
    void visit(PPC_subfme &instruction);
    void visit(PPC_subfme_ &instruction);
    void visit(PPC_subfmeo &instruction);
    void visit(PPC_subfmeo_ &instruction);
    void visit(PPC_subfze &instruction);
    void visit(PPC_subfze_ &instruction);
    void visit(PPC_subfzeo &instruction);
    void visit(PPC_subfzeo_ &instruction);
    void visit(PPC_subfic &instruction);
    void visit(PPC_slw &instruction);
    void visit(PPC_slw_ &instruction);
    void visit(PPC_srw &instruction);
    void visit(PPC_srw_ &instruction);
    void visit(PPC_sraw &instruction);
    void visit(PPC_sraw_ &instruction);
    void visit(PPC_srawi &instruction);
    void visit(PPC_srawi_ &instruction);
    void visit(PPC_xor &instruction);
    void visit(PPC_xor_ &instruction);
    void visit(PPC_xori &instruction);
    void visit(PPC_xoris &instruction);
    void visit(PPC_mulli &instruction);
    void visit(PPC_mullw &instruction);
    void visit(PPC_mullw_ &instruction);
    void visit(PPC_mullwo &instruction);
    void visit(PPC_mullwo_ &instruction);
    void visit(PPC_mulhw &instruction);
    void visit(PPC_mulhw_ &instruction);
    void visit(PPC_mulhwu &instruction);
    void visit(PPC_mulhwu_ &instruction);
    void visit(PPC_nand &instruction);
    void visit(PPC_nand_ &instruction);
    void visit(PPC_nor &instruction);
    void visit(PPC_nor_ &instruction);

    // ...

    // ppcis_fpu.hpp
    void visit(PPC_FP_Instruction &instruction);

    // ppcis_loadstore.hpp
    void visit(PPC_dcbz &instruction);
    void visit(PPC_lbz &instruction);
    void visit(PPC_lbzu &instruction);
    void visit(PPC_lbzux &instruction);
    void visit(PPC_lbzx &instruction);
    void visit(PPC_lfd &instruction);
    void visit(PPC_lfdu &instruction);
    void visit(PPC_lfdux &instruction);
    void visit(PPC_lfdx &instruction);
    void visit(PPC_lfs &instruction);
    void visit(PPC_lfsu &instruction);
    void visit(PPC_lfsux &instruction);
    void visit(PPC_lfsx &instruction);
    void visit(PPC_lwz &instruction);
    void visit(PPC_lwzu &instruction);
    void visit(PPC_lwzux &instruction);
    void visit(PPC_lwzx &instruction);
    void visit(PPC_lha &instruction);
    void visit(PPC_lhau &instruction);
    void visit(PPC_lhaux &instruction);
    void visit(PPC_lhax &instruction);
    void visit(PPC_lhbrx &instruction);
    void visit(PPC_lhz &instruction);
    void visit(PPC_lhzu &instruction);
    void visit(PPC_lhzux &instruction);
    void visit(PPC_lhzx &instruction);
    void visit(PPC_lmw &instruction);
    void visit(PPC_lswi &instruction);
    void visit(PPC_lswx &instruction);
    void visit(PPC_lwa &instruction);
    void visit(PPC_lwarx &instruction);
    void visit(PPC_lwax &instruction);
    void visit(PPC_lwbrx &instruction);
    void visit(PPC_lwaux &instruction);
    void visit(PPC_stb &instruction);
    void visit(PPC_stbu &instruction);
    void visit(PPC_stbux &instruction);
    void visit(PPC_stbx &instruction);
    void visit(PPC_sth &instruction);
    void visit(PPC_sthbrx &instruction);
    void visit(PPC_sthu &instruction);
    void visit(PPC_sthux &instruction);
    void visit(PPC_sthx &instruction);
    void visit(PPC_stmw &instruction);
    void visit(PPC_stswi &instruction);
    void visit(PPC_stswx &instruction);
    void visit(PPC_stwu &instruction);
    void visit(PPC_stw &instruction);
    void visit(PPC_stwbrx &instruction);
    void visit(PPC_stwcx_ &instruction);
    void visit(PPC_stwux &instruction);
    void visit(PPC_stwx &instruction);
    void visit(PPC_stfd &instruction);
    void visit(PPC_stfdu &instruction);
    void visit(PPC_stfdux &instruction);
    void visit(PPC_stfdx &instruction);
    void visit(PPC_stfiwx &instruction);
    void visit(PPC_stfs &instruction);
    void visit(PPC_stfsu &instruction);
    void visit(PPC_stfsux &instruction);
    void visit(PPC_stfsx &instruction);


    // ppcis_misc.hpp
    void visit(PPC_b &instruction);
    void visit(PPC_bl &instruction);
    void visit(PPC_ba &instruction);
    void visit(PPC_bla &instruction);
    void visit(PPC_bc &instruction);
    void visit(PPC_bca &instruction);
    void visit(PPC_bcl &instruction);
    void visit(PPC_bcla &instruction);
    void visit(PPC_bcctr &instruction);
    void visit(PPC_bcctrl &instruction);
    void visit(PPC_bclr &instruction);
    void visit(PPC_bclrl &instruction);
    void visit(PPC_tw &instruction);
    void visit(PPC_twi &instruction);
    void visit(PPC_mtspr &instruction);
    void visit(PPC_mfspr &instruction);
    void visit(PPC_mtcrf &instruction);
    void visit(PPC_mfcr &instruction);
    void visit(PPC_mfmsr &instruction);
    void visit(PPC_mfsr &instruction);
    void visit(PPC_mftb &instruction);
    void visit(PPC_mfsrin &instruction);
    void visit(PPC_mcrf &instruction);
    void visit(PPC_mcrfs &instruction);
    void visit(PPC_mffs &instruction);
    void visit(PPC_mffs_ &instruction);
    void visit(PPC_mtmsr &instruction);
    void visit(PPC_mtsr &instruction);
    void visit(PPC_mtsrin &instruction);
    void visit(PPC_mtfsb0 &instruction);
    void visit(PPC_mtfsb0_ &instruction);
    void visit(PPC_mtfsb1 &instruction);
    void visit(PPC_mtfsb1_ &instruction);
    void visit(PPC_mtfsf &instruction);
    void visit(PPC_mtfsf_ &instruction);
    void visit(PPC_mtfsfi &instruction);
    void visit(PPC_mtfsfi_ &instruction);
    void visit(PPC_rfi &instruction);



  private:
    llvm::LLVMContext &context;
    llvm::IRBuilder<> IRB;
    bool failed;

    llvm::Module *module;
    llvm::Value *proc;
    llvm::Value *status;

    llvm::Function *increment_pc;
    llvm::Function *proc_hook;
    llvm::Function *decrement_pc_if_not_OK;

    const llvm::IntegerType *const i8;
    const llvm::IntegerType *const i16;
    const llvm::IntegerType *const i32;
    const llvm::IntegerType *const iptr;
    const llvm::FunctionType *dyncode_type;

    llvm::PassManager *pm;
    llvm::FunctionPassManager *fpm;
    llvm::ExecutionEngine *ee;

    // profiling data
    std::ofstream profstream;
    bool profiling;
    bool prof_total;
    size_t prof_icount;
    size_t prof_bbcount;
    TimeVal prof_time;
  };

} // namespace simsoc

#endif // PPC_LLVM_GENERATOR_HPP
