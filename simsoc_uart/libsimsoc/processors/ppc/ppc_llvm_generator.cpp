//
// SimSoC Initial software, Copyright © INRIA 2007, 2008, 2009, 2010
// LGPL license version 3
//

#include "ppc_llvm_generator.hpp"
#include "ppcis_alu.hpp"
#include "ppcis_fpu.hpp"
#include "ppcis_loadstore.hpp"
#include "ppcis_misc.hpp"
#include "ppcis_dyntrans.hpp"
#include <libsimsoc/processors/llvm_gen_parameters.hpp>
#include <libsimsoc/display.hpp>
#include <llvm/Bitcode/ReaderWriter.h>
#include <llvm/Support/MemoryBuffer.h>
#include <llvm/PassManager.h>
#include <llvm/Module.h>
#include <llvm/Target/TargetData.h>
#include <llvm/Transforms/IPO.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/Support/ManagedStatic.h>
#include <llvm/Target/TargetSelect.h>
#include <llvm/Target/TargetOptions.h>
#include <iostream>
#include "simsoc-config.h"

using namespace std;
using namespace llvm;

namespace simsoc {

  struct PPC_LLVM_Deleter {
    PPC_LLVM_Generator *gen;
    PPC_LLVM_Deleter(): gen(NULL) {}
    ~PPC_LLVM_Deleter() {delete gen;}
  };
  PPC_LLVM_Deleter ppc_deleter;

  static const char *bitcode_file() {
    return ABS_TOP_BUILDDIR "/libsimsoc/ppc_llvm_lib.bc";
  }

  PPC_LLVM_Generator *PPC_LLVM_Generator::singleton = NULL;

  PPC_LLVM_Generator &PPC_LLVM_Generator::get() {
    if (!singleton) {
      singleton = new PPC_LLVM_Generator();
      ppc_deleter.gen = singleton;
    }
    return *singleton;
  }

  PPC_LLVM_Generator::PPC_LLVM_Generator():
    context(getGlobalContext()),
    IRB(context),
    failed(false),
    module(NULL), proc(NULL), status(NULL),
    i8(IntegerType::get(context,8)),
    i16(IntegerType::get(context,16)),
    i32(IntegerType::get(context,32)),
    iptr(IntegerType::get(context,8*sizeof(intptr_t))),
    dyncode_type(NULL),
    pm(NULL), fpm(NULL), ee(NULL),
    profiling(false),
    prof_total(DT3_prof_total.get()), prof_icount(0), prof_bbcount(0), prof_time()
  {
    TimeVal start; start.set(); 
    const char *prof_file_name = DT3_prof_files.front();
    DT3_prof_files.pop_front();
    // if profiling is ON, then we open the profiling stream
    if (strcmp(prof_file_name,"")!=0) {
      profstream.open(prof_file_name);
      if(!profstream){
	error() <<"Failed to open \"" <<prof_file_name <<"\" for writing.\n";
	exit(1);
      }
      profiling = true;
    }
    // Load bitcode file
    string err_str;
    MemoryBuffer *mb = MemoryBuffer::getFile(bitcode_file(),&err_str);
    if (!mb) {
      error() <<"Cannot open \"" <<bitcode_file() <<"\": " <<err_str <<endl;
      exit(1);
    }
    module = llvm::ParseBitcodeFile(mb,context,&err_str);
    if (!module) {
      error() <<"Failed to load module from bitcode file: " <<err_str <<endl;
      exit(1);
    }
    delete mb;
    debug() <<"bitcode file loaded.\n";
    // mark all ppc_* functions as "AlwaysInline"
    const string prefix("ppc_");
    for (llvm::Module::iterator f = module->begin(), ef = module->end(); f!=ef; ++f) {
      if (f->hasName() && !f->getNameStr().compare(0,4,prefix)) {
        // debug() <<"Add \"AlwaysInline\" attribute to function "
        //         <<f->getNameStr() <<".\n";
        f->addFnAttr(Attribute::AlwaysInline);
      }
    }
    // Extract some common functions
    increment_pc = module->getFunction("ppc_increment_pc"); assert(increment_pc);
    proc_hook = module->getFunction("ppc_proc_hook"); assert(proc_hook);
    decrement_pc_if_not_OK = module->getFunction("ppc_decrement_pc_if_not_OK");
    assert(decrement_pc_if_not_OK);
    // compute function type for dynamic code: void XXX(PPC_Processor*)
    // NB: it is the same type than ppc_increment_pc
    dyncode_type = increment_pc->getFunctionType();
    // Initialize pass managers
    pm = new PassManager();
    pm->add(createAlwaysInlinerPass());
    fpm = new FunctionPassManager(module);
    fpm->add(new TargetData(module));
    fpm->add(createGVNPass());
    fpm->add(createInstructionCombiningPass());
    fpm->add(createCFGSimplificationPass());
    fpm->add(createDeadStoreEliminationPass());
    // Initialize the JIT compiler
#ifdef SIMSOC_HAVE_LLVM_DWARFEXCEPTIONHANDLING
    llvm::DwarfExceptionHandling = true;
#else
    llvm::JITExceptionHandling = true;
#endif
    InitializeNativeTarget();
    atexit(llvm_shutdown);  // Call llvm_shutdown() on exit.
    EngineBuilder builder(module);
    builder.setErrorStr(&err_str);
    builder.setEngineKind(EngineKind::JIT);
    builder.setOptLevel(CodeGenOpt::Default); // None/Less/Default/Aggressive
    ee = builder.create();
    if (!ee) {
      error() <<"failed to create execution engine: " <<err_str <<"\n";
      exit(1);
    }
    ee->DisableLazyCompilation(true);
    TimeVal end; end.set();
    info() <<"The llvm load time is " <<end-start <<'\n';
    debug() <<"execution engine created; LLVM generator is ready.\n";
  }

  PPC_LLVM_Generator::~PPC_LLVM_Generator() {
    if (profiling)
      profstream.close();
    if (prof_total) {
      cout <<"[PPC LLVM generator] " <<prof_icount <<" instructions in "
           <<prof_bbcount <<" blocks compiled in " <<prof_time <<endl; 
    }
  }

  PPC_OptimizedBasicBlock *PPC_LLVM_Generator::compile(PPC_BasicBlock *bb) {
    TimeVal start;
    if (profiling||prof_total)
      start.set();

    // create function
    Function *fct = Function::Create(dyncode_type, Function::ExternalLinkage,
                                     "dynamic_code", module);
    Function::arg_iterator arg0 = fct->arg_begin();
    arg0->setName("proc");
    proc = arg0;
    assert(++arg0==fct->arg_end());
    debug() <<"create llvm function " <<fct->getNameStr() <<".\n";
    // create and fill the main block
    BasicBlock *lbb = BasicBlock::Create(context, "entry", fct);
    IRB.SetInsertPoint(lbb);
    for (vector<PPC_Instruction*>::iterator i = bb->is.begin(), ei = bb->is.end();
         i!=ei; ++i) {
      (*i)->accept(*this);
      IRB.CreateCall(increment_pc,proc);
      IRB.CreateCall(proc_hook,proc);
    }
    if (status)
      IRB.CreateCall2(decrement_pc_if_not_OK,status,proc);
    else
      assert(failed);
    IRB.CreateRetVoid();
    // optimize
    // fct->dump(); // display the initial llvm code // DO NOT COMMIT
    pm->run(*module);
    // fct->dump(); // display the function after inlining
    fpm->run(*fct);
    // fct->dump(); // display the function after optimization
    // Check if everything OK
    if (failed) {
      failed = false;
      error() <<"LLVM generation not implemented for some instructions"
              <<" indicated above.\n";
      exit(1);
    } else {
      debug() <<"succesful generation\n";
    }
    PPC_OptimizedBasicBlock::ExecFunction nf =
      reinterpret_cast<PPC_OptimizedBasicBlock::ExecFunction>
      (ee->getPointerToFunction(fct));

    if (profiling) {
      TimeVal end; end.set();
      profstream <<bb->is.size() <<";" <<end-start <<'\n';
    }
    if (prof_total) {
      TimeVal end; end.set();
      prof_icount += bb->is.size(); ++prof_bbcount;
      prof_time = prof_time + (end-start);
    }
    return new PPC_OptimizedBasicBlock(bb,fct,nf);
  }

  void PPC_LLVM_Generator::visit(PPC_Instruction &instruction) {
    warning() <<"LLVM generation not implemented for instruction: "
              <<instruction <<std::endl;
    failed = true;
  }

  void PPC_LLVM_Generator::visit(PPC_FP_Instruction &instruction) {
    Function *fct = module->getFunction("ppc_generic"); assert(fct);
    Value *instr_int =
      ConstantInt::get(iptr,reinterpret_cast<intptr_t>(&instruction));
    Value *instr = IRB.CreateIntToPtr(instr_int,
                                      fct->getFunctionType()->getParamType(1),
                                      "instr");
    status = IRB.CreateCall2(fct,proc,instr,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_add &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_add"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_add_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_add_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addc &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_addc"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addc_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_addc_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addco &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_addco"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addco_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_addco_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_adde &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_adde"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_adde_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_adde_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addeo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_addeo"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addeo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_addeo_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addme &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_addme"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addme_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_addme_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addmeo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_addmeo"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addmeo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_addmeo_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addze &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_addze"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addze_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_addze_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addzeo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_addzeo"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addzeo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_addzeo_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addic &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_addic"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addic_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_addic_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_addo"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_addo_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_and &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_and"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_and_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_and_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_andc &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_andc"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_andc_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_andc_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_andi_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_andi_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_andis_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_andis_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_cmp &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_cmp"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_cmpl &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_cmpl"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_cmpli &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_cmpli"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_cntlzw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_cntlzw"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_cntlzw_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_cntlzw_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_crand &instruction) {
    Value *bt = ConstantInt::get(i8,instruction.bt);
    Value *ba = ConstantInt::get(i8,instruction.ba);
    Value *bb = ConstantInt::get(i8,instruction.bb);
    Function *fct = module->getFunction("ppc_crand"); assert(fct);
    status = IRB.CreateCall4(fct,proc,bt,ba,bb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_crandc &instruction) {
    Value *bt = ConstantInt::get(i8,instruction.bt);
    Value *ba = ConstantInt::get(i8,instruction.ba);
    Value *bb = ConstantInt::get(i8,instruction.bb);
    Function *fct = module->getFunction("ppc_crandc"); assert(fct);
    status = IRB.CreateCall4(fct,proc,bt,ba,bb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_creqv &instruction) {
    Value *bt = ConstantInt::get(i8,instruction.bt);
    Value *ba = ConstantInt::get(i8,instruction.ba);
    Value *bb = ConstantInt::get(i8,instruction.bb);
    Function *fct = module->getFunction("ppc_creqv"); assert(fct);
    status = IRB.CreateCall4(fct,proc,bt,ba,bb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_crnand &instruction) {
    Value *bt = ConstantInt::get(i8,instruction.bt);
    Value *ba = ConstantInt::get(i8,instruction.ba);
    Value *bb = ConstantInt::get(i8,instruction.bb);
    Function *fct = module->getFunction("ppc_crnand"); assert(fct);
    status = IRB.CreateCall4(fct,proc,bt,ba,bb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_crnor &instruction) {
    Value *bt = ConstantInt::get(i8,instruction.bt);
    Value *ba = ConstantInt::get(i8,instruction.ba);
    Value *bb = ConstantInt::get(i8,instruction.bb);
    Function *fct = module->getFunction("ppc_crnor"); assert(fct);
    status = IRB.CreateCall4(fct,proc,bt,ba,bb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_cror &instruction) {
    Value *bt = ConstantInt::get(i8,instruction.bt);
    Value *ba = ConstantInt::get(i8,instruction.ba);
    Value *bb = ConstantInt::get(i8,instruction.bb);
    Function *fct = module->getFunction("ppc_cror"); assert(fct);
    status = IRB.CreateCall4(fct,proc,bt,ba,bb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_crorc &instruction) {
    Value *bt = ConstantInt::get(i8,instruction.bt);
    Value *ba = ConstantInt::get(i8,instruction.ba);
    Value *bb = ConstantInt::get(i8,instruction.bb);
    Function *fct = module->getFunction("ppc_crorc"); assert(fct);
    status = IRB.CreateCall4(fct,proc,bt,ba,bb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_crxor &instruction) {
    Value *bt = ConstantInt::get(i8,instruction.bt);
    Value *ba = ConstantInt::get(i8,instruction.ba);
    Value *bb = ConstantInt::get(i8,instruction.bb);
    Function *fct = module->getFunction("ppc_crxor"); assert(fct);
    status = IRB.CreateCall4(fct,proc,bt,ba,bb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_divw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_divw"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_divw_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_divw_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_divwo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_divwo"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_divwo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_divwo_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_divwu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_divwu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_divwu_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_divwu_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_divwuo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_divwuo"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_divwuo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_divwuo_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_dcbz &instruction) {
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_dcbz_ra0"); assert(fct);
      status = IRB.CreateCall2(fct,proc,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_dcbz_raS"); assert(fct);
      status = IRB.CreateCall3(fct,proc,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_eqv &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_eqv"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_eqv_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_eqv_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_extsb &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_extsb"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_extsb_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_extsb_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_extsh &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_extsh"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_extsh_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_extsh_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_stwu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_stwu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_stw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stw_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stw_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stwbrx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stwbrx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stwbrx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stwcx_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stwcx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stwcx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stwux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_stwux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_stwx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stwx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stwx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stfd &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stfd_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stfd_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stfdu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_stfdu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_stfdux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_stfdux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_stfdx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stfdx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stfdx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stfiwx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stfiwx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stfiwx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stfs &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stfs_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stfs_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stfsu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_stfsu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_stfsux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_stfsux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_stfsx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stfsx_ra0"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    } else {
      Function *fct = module->getFunction("ppc_stfsx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_mfspr &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *spr = ConstantInt::get(i16,instruction.spr);
    Function *fct = module->getFunction("ppc_mfspr"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,spr,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtcrf &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *spr = ConstantInt::get(i16,instruction.spr);
    Function *fct = module->getFunction("ppc_mtcrf"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,spr,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mfcr &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Function *fct = module->getFunction("ppc_mfcr"); assert(fct);
    status = IRB.CreateCall2(fct,proc,rt,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mfmsr &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Function *fct = module->getFunction("ppc_mfmsr"); assert(fct);
    status = IRB.CreateCall2(fct,proc,rt,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mfsr &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_mfsr"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mftb &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *spr = ConstantInt::get(i16,instruction.spr);
    Function *fct = module->getFunction("ppc_mftb"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,spr,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mfsrin &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mfsrin"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mcrf &instruction) {
    Value *bt = ConstantInt::get(i8,instruction.bt);
    Value *ba = ConstantInt::get(i8,instruction.ba);
    Function *fct = module->getFunction("ppc_mcrf"); assert(fct);
    status = IRB.CreateCall3(fct,proc,bt,ba,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mcrfs &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_mcrfs"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mffs &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Function *fct = module->getFunction("ppc_mffs"); assert(fct);
    status = IRB.CreateCall2(fct,proc,rt,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mffs_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Function *fct = module->getFunction("ppc_mffs_"); assert(fct);
    status = IRB.CreateCall2(fct,proc,rt,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtmsr &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Function *fct = module->getFunction("ppc_mtmsr"); assert(fct);
    status = IRB.CreateCall2(fct,proc,rt,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtsr &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_mtsr"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtsrin &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mtsrin"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtfsb0 &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Function *fct = module->getFunction("ppc_mtfsb0"); assert(fct);
    status = IRB.CreateCall2(fct,proc,rt,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtfsb0_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Function *fct = module->getFunction("ppc_mtfsb0_"); assert(fct);
    status = IRB.CreateCall2(fct,proc,rt,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtfsb1 &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Function *fct = module->getFunction("ppc_mtfsb1"); assert(fct);
    status = IRB.CreateCall2(fct,proc,rt,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtfsb1_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Function *fct = module->getFunction("ppc_mtfsb1_"); assert(fct);
    status = IRB.CreateCall2(fct,proc,rt,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtfsf &instruction) {
    Value *flm = ConstantInt::get(i8,instruction.flm);
    Value *frb = ConstantInt::get(i8,instruction.frb);
    Function *fct = module->getFunction("ppc_mtfsf"); assert(fct);
    status = IRB.CreateCall3(fct,proc,flm,frb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtfsf_ &instruction) {
    Value *flm = ConstantInt::get(i8,instruction.flm);
    Value *frb = ConstantInt::get(i8,instruction.frb);
    Function *fct = module->getFunction("ppc_mtfsf_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,flm,frb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtfsfi &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mtfsfi"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mtfsfi_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mtfsfi_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_rfi &instruction) {
    Function *fct = module->getFunction("ppc_rfi"); assert(fct);
    status = IRB.CreateCall(fct,proc,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_or &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_or"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_or_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_or_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_orc &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_orc"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_orc_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_orc_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_bl &instruction) {
    Value *li = ConstantInt::get(i32,instruction.li);
    Function *fct = module->getFunction("ppc_bl"); assert(fct);
    status = IRB.CreateCall2(fct,proc,li,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_ba &instruction) {
    Value *li = ConstantInt::get(i32,instruction.li);
    Function *fct = module->getFunction("ppc_ba"); assert(fct);
    status = IRB.CreateCall2(fct,proc,li,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_bla &instruction) {
    Value *li = ConstantInt::get(i32,instruction.li);
    Function *fct = module->getFunction("ppc_bla"); assert(fct);
    status = IRB.CreateCall2(fct,proc,li,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lfd &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lfd_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lfd_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lfdu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_lfdu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lfdux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_lfdux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lfdx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lfdx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lfdx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lfs &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lfs_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lfs_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lfsu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_lfsu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lfsux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_lfsux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lfsx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lfsx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lfsx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lwz &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lwz_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lwz_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lwzu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_lwzu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lwzux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_lwzux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lwzx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lwzx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lwzx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_neg &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_neg"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_neg_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_neg_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_nego &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_nego"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_nego_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_nego_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_cmpi &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_cmpi"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_bc &instruction) {
    bool bo_0 = instruction.bo & 16;
    bool bo_2 = instruction.bo & 4;
    Value *bd = ConstantInt::get(i32,instruction.bd);
    if ((bo_0 == 1)&&(bo_2 == 1)) {
      Function *fct = module->getFunction("ppc_bc_bo01_bo21"); assert(fct);
      status = IRB.CreateCall2(fct,proc,bd,"status");
    } else if ((bo_0 == 0) && (bo_2 == 1)) {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Value *bi = ConstantInt::get(i8,instruction.bi);
      Function *fct = module->getFunction("ppc_bc_bo00_bo21"); assert(fct);
      status = IRB.CreateCall4(fct,proc,bo,bi,bd,"status");
    } else if ((bo_0 == 1) && (bo_2 == 0)) {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Function *fct = module->getFunction("ppc_bc_bo01_bo20"); assert(fct);
      status = IRB.CreateCall3(fct,proc,bo,bd,"status");
    } else {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Value *bi = ConstantInt::get(i8,instruction.bi);
      Function *fct = module->getFunction("ppc_bc_bo00_bo20"); assert(fct);
      status = IRB.CreateCall4(fct,proc,bo,bi,bd,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_bca &instruction) {
    bool bo_0 = instruction.bo & 16;
    bool bo_2 = instruction.bo & 4;
    Value *bd = ConstantInt::get(i32,instruction.bd);
    if ((bo_0 == 1) && (bo_2 == 1)) {
      Function *fct = module->getFunction("ppc_bca_bo01_bo21"); assert(fct);
      status = IRB.CreateCall2(fct,proc,bd,"status");
    } else if ((bo_0 == 0) && (bo_2 == 1)) {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Value *bi = ConstantInt::get(i8,instruction.bi);
      Function *fct = module->getFunction("ppc_bca_bo00_bo21"); assert(fct);
      status = IRB.CreateCall4(fct,proc,bo,bi,bd,"status");
    } else if  ((bo_0 == 1) && (bo_2 == 0)) {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Function *fct = module->getFunction("ppc_bca_bo01_bo20"); assert(fct);
      status = IRB.CreateCall3(fct,proc,bo,bd,"status");
    } else {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Value *bi = ConstantInt::get(i8,instruction.bi);
      Function *fct = module->getFunction("ppc_bca_bo00_bo20"); assert(fct);
      status = IRB.CreateCall4(fct,proc,bo,bi,bd,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_bcl &instruction) {
    bool bo_0 = instruction.bo & 16;
    bool bo_2 = instruction.bo & 4;
    Value *bd = ConstantInt::get(i32,instruction.bd);
    if ((bo_0 == 1) && (bo_2 == 1)) {
      Function *fct = module->getFunction("ppc_bcl_bo01_bo21"); assert(fct);
      status = IRB.CreateCall2(fct,proc,bd,"status");
    } else if ((bo_0 == 0) && (bo_2 == 1)) {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Value *bi = ConstantInt::get(i8,instruction.bi);
      Function *fct = module->getFunction("ppc_bcl_bo00_bo21"); assert(fct);
      status = IRB.CreateCall4(fct,proc,bo,bi,bd,"status");
    } else if ((bo_0 == 1) && (bo_2 == 0)) {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Function *fct = module->getFunction("ppc_bcl_bo01_bo20"); assert(fct);
      status = IRB.CreateCall3(fct,proc,bo,bd,"status");
    } else {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Value *bi = ConstantInt::get(i8,instruction.bi);
      Function *fct = module->getFunction("ppc_bcl_bo00_bo20"); assert(fct);
      status = IRB.CreateCall4(fct,proc,bo,bi,bd,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_bcla &instruction) {
    bool bo_0 = instruction.bo & 16;
    bool bo_2 = instruction.bo & 4;
    Value *bd = ConstantInt::get(i32,instruction.bd);
    if ((bo_0 == 1) && (bo_2 == 1)) {
      Function *fct = module->getFunction("ppc_bcla_bo01_bo21"); assert(fct);
      status = IRB.CreateCall2(fct,proc,bd,"status");
    } else if ((bo_0 == 0) && (bo_2 == 1)) {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Value *bi = ConstantInt::get(i8,instruction.bi);
      Function *fct = module->getFunction("ppc_bcla_bo00_bo21"); assert(fct);
      status = IRB.CreateCall4(fct,proc,bo,bi,bd,"status");
    } else if ((bo_0 == 1) && (bo_2 == 0)) {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Function *fct = module->getFunction("ppc_bcla_bo01_bo20"); assert(fct);
      status = IRB.CreateCall3(fct,proc,bo,bd,"status");
    } else {
      Value *bo = ConstantInt::get(i8,instruction.bo);
      Value *bi = ConstantInt::get(i8,instruction.bi);
      Function *fct = module->getFunction("ppc_bcla_bo00_bo20"); assert(fct);
      status = IRB.CreateCall4(fct,proc,bo,bi,bd,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_bcctr &instruction) {
    bool bo_0 = instruction.bt & 16;
    if (bo_0 == 1) {
      Function *fct = module->getFunction("ppc_bcctr_bo01"); assert(fct);
      status = IRB.CreateCall(fct,proc,"status");
    } else {
      Value *bt = ConstantInt::get(i8,instruction.bt);
      Value *ba = ConstantInt::get(i8,instruction.ba);
      Function *fct = module->getFunction("ppc_bcctr_bo00"); assert(fct);
      status = IRB.CreateCall3(fct,proc,bt,ba,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_bcctrl &instruction) {
    bool bo_0 = instruction.bt & 16;
    if (bo_0 == 1) {
      Function *fct = module->getFunction("ppc_bcctrl_bo01"); assert(fct);
      status = IRB.CreateCall(fct,proc,"status");
    } else {
      Value *bt = ConstantInt::get(i8,instruction.bt);
      Value *ba = ConstantInt::get(i8,instruction.ba);
      Function *fct = module->getFunction("ppc_bcctrl_bo00"); assert(fct);
      status = IRB.CreateCall3(fct,proc,bt,ba,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_addis &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_addis_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_addis_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_ori &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_ori"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_oris &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_oris"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_addi &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_addi_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_addi_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stb &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stb_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stb_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stbu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_stbu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_stbux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_stbux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_stbx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stbx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stbx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_sth &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_sth_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_sth_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_sthbrx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_sthbrx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_sthbrx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_sthu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_sthu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_sthux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_sthux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_sthx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_sthx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_sthx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stmw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stmw_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stmw_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stswi &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stswi_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stswi_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_stswx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_stswx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_stswx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_mtspr &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *spr = ConstantInt::get(i16,instruction.spr);
    Function *fct = module->getFunction("ppc_mtspr"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,spr,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_bclr &instruction) {
    bool bo_0 = instruction.bt & 16;
    bool bo_2 = instruction.bt & 4;
    if ((bo_0 == 1) && (bo_2 == 1)) {
      Function *fct = module->getFunction("ppc_bclr_bo01_bo21"); assert(fct);
      status = IRB.CreateCall(fct,proc,"status");
    } else if ((bo_0 == 0) && (bo_2 == 1)) {
      Value *bt = ConstantInt::get(i8,instruction.bt);
      Value *ba = ConstantInt::get(i8,instruction.ba);
      Function *fct = module->getFunction("ppc_bclr_bo00_bo21"); assert(fct);
      status = IRB.CreateCall3(fct,proc,bt,ba,"status");
    } else if ((bo_0 == 1) && (bo_2 == 0)) {
      Value *bt = ConstantInt::get(i8,instruction.bt);
      Function *fct = module->getFunction("ppc_bclr_bo01_bo20"); assert(fct);
      status = IRB.CreateCall2(fct,proc,bt,"status");
    } else {
      Value *bt = ConstantInt::get(i8,instruction.bt);
      Value *ba = ConstantInt::get(i8,instruction.ba);
      Function *fct = module->getFunction("ppc_bclr_bo00_bo20"); assert(fct);
      status = IRB.CreateCall3(fct,proc,bt,ba,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_bclrl &instruction) {
    bool bo_0 = instruction.bt & 16;
    bool bo_2 = instruction.bt & 4;
    if ((bo_0 == 1) && (bo_2 == 1)) {
      Function *fct = module->getFunction("ppc_bclrl_bo01_bo21"); assert(fct);
      status = IRB.CreateCall(fct,proc,"status");
    } else if ((bo_0 == 0) && (bo_2 == 1)) {
      Value *bt = ConstantInt::get(i8,instruction.bt);
      Value *ba = ConstantInt::get(i8,instruction.ba);
      Function *fct = module->getFunction("ppc_bclrl_bo00_bo21"); assert(fct);
      status = IRB.CreateCall3(fct,proc,bt,ba,"status");
    } else if ((bo_0 == 1) && (bo_2 == 0)) {
      Value *bt = ConstantInt::get(i8,instruction.bt);
      Function *fct = module->getFunction("ppc_bclrl_bo01_bo20"); assert(fct);
      status = IRB.CreateCall2(fct,proc,bt,"status");
    } else {
      Value *bt = ConstantInt::get(i8,instruction.bt);
      Value *ba = ConstantInt::get(i8,instruction.ba);
      Function *fct = module->getFunction("ppc_bclrl_bo00_bo20"); assert(fct);
      status = IRB.CreateCall3(fct,proc,bt,ba,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_b &instruction) {
    Value *li = ConstantInt::get(i32,instruction.li);
    Function *fct = module->getFunction("ppc_b"); assert(fct);
    status = IRB.CreateCall2(fct,proc,li,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lbz &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lbz_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lbz_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lbzu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_lbzu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lbzux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_lbzux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lbzx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lbzx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lbzx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_rlwimi &instruction) {
   Value *values[6];
    values[0] = proc;
    values[1] = /* rs */ ConstantInt::get(i8,instruction.rs);
    values[2] = /* ra */ ConstantInt::get(i8,instruction.ra);
    values[3] = /* rb */ ConstantInt::get(i8,instruction.rb);
    values[4] = /* mb */ ConstantInt::get(i8,instruction.mb);
    values[5] = /* me */ ConstantInt::get(i8,instruction.me);
    Function *fct = module->getFunction("ppc_rlwimi"); assert(fct);
    status = IRB.CreateCall<Value**>(fct,values,values+6,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_rlwimi_ &instruction) {
    Value *values[6];
    values[0] = proc;
    values[1] = /* rs */ ConstantInt::get(i8,instruction.rs);
    values[2] = /* ra */ ConstantInt::get(i8,instruction.ra);
    values[3] = /* rb */ ConstantInt::get(i8,instruction.rb);
    values[4] = /* mb */ ConstantInt::get(i8,instruction.mb);
    values[5] = /* me */ ConstantInt::get(i8,instruction.me);
    Function *fct = module->getFunction("ppc_rlwimi_"); assert(fct);
    status = IRB.CreateCall<Value**>(fct,values,values+6,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_rlwinm &instruction) {
    Value *values[6];
    values[0] = proc;
    values[1] = /* rs */ ConstantInt::get(i8,instruction.rs);
    values[2] = /* ra */ ConstantInt::get(i8,instruction.ra);
    values[3] = /* rb */ ConstantInt::get(i8,instruction.rb);
    values[4] = /* mb */ ConstantInt::get(i8,instruction.mb);
    values[5] = /* me */ ConstantInt::get(i8,instruction.me);
    Function *fct = module->getFunction("ppc_rlwinm"); assert(fct);
    status = IRB.CreateCall<Value**>(fct,values,values+6,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_rlwinm_ &instruction) {
    Value *values[6];
    values[0] = proc;
    values[1] = /* rs */ ConstantInt::get(i8,instruction.rs);
    values[2] = /* ra */ ConstantInt::get(i8,instruction.ra);
    values[3] = /* rb */ ConstantInt::get(i8,instruction.rb);
    values[4] = /* mb */ ConstantInt::get(i8,instruction.mb);
    values[5] = /* me */ ConstantInt::get(i8,instruction.me);
    Function *fct = module->getFunction("ppc_rlwinm_"); assert(fct);
    status = IRB.CreateCall<Value**>(fct,values,values+6,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_rlwnm &instruction) {
    Value *values[6];
    values[0] = proc;
    values[1] = /* rs */ ConstantInt::get(i8,instruction.rs);
    values[2] = /* ra */ ConstantInt::get(i8,instruction.ra);
    values[3] = /* rb */ ConstantInt::get(i8,instruction.rb);
    values[4] = /* mb */ ConstantInt::get(i8,instruction.mb);
    values[5] = /* me */ ConstantInt::get(i8,instruction.me);
    Function *fct = module->getFunction("ppc_rlwnm"); assert(fct);
    status = IRB.CreateCall<Value**>(fct,values,values+6,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_rlwnm_ &instruction) {
    Value *values[6];
    values[0] = proc;
    values[1] = /* rs */ ConstantInt::get(i8,instruction.rs);
    values[2] = /* ra */ ConstantInt::get(i8,instruction.ra);
    values[3] = /* rb */ ConstantInt::get(i8,instruction.rb);
    values[4] = /* mb */ ConstantInt::get(i8,instruction.mb);
    values[5] = /* me */ ConstantInt::get(i8,instruction.me);
    Function *fct = module->getFunction("ppc_rlwnm_"); assert(fct);
    status = IRB.CreateCall<Value**>(fct,values,values+6,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_sc &instruction) {
    Function *fct = module->getFunction("ppc_sc"); assert(fct);
    status = IRB.CreateCall(fct,proc,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subf &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subf"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subf_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subf_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subfo"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subfo_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfc &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subfc"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfc_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subfc_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfco &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subfco"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfco_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subfco_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfe &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subfe"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfe_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subfe_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfeo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subfeo"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfeo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_subfeo_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfme &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_subfme"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfme_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_subfme_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfmeo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_subfmeo"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfmeo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_subfmeo_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfze &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_subfze"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfze_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_subfze_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfzeo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_subfzeo"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfzeo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Function *fct = module->getFunction("ppc_subfzeo_"); assert(fct);
    status = IRB.CreateCall3(fct,proc,rt,ra,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_subfic &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_subfic"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_slw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_slw"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_slw_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_slw_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_tw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_tw"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_twi &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_twi"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_srw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_srw"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_srw_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_srw_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_sraw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_sraw"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_sraw_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_sraw_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_srawi &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_srawi"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_srawi_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_srawi_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_xor &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_xor"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_xor_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_xor_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_xori &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_xori"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_xoris &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_xoris"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lha &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lha_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lha_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lhau &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_lhau"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lhaux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_lhaux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lhax &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lhax_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lhax_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lhbrx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lhbrx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lhbrx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lhz &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *d = ConstantInt::get(i32,instruction.d);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lhz_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,d,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lhz_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lhzu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_lhzu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lhzux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_lhzux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lhzx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lhzx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lhzx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lmw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_lmw"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_lswi &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lswi_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lswi_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lswx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lswx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lswx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lwa &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ds = ConstantInt::get(i32,instruction.ds);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lwa_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,ds,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lwa_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,ds,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lwarx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lwarx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lwarx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lwax &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lwax_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lwax_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lwbrx &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    if (instruction.ra==0) {
      Function *fct = module->getFunction("ppc_lwbrx_ra0"); assert(fct);
      status = IRB.CreateCall3(fct,proc,rt,rb,"status");
    } else {
      Value *ra = ConstantInt::get(i8,instruction.ra);
      Function *fct = module->getFunction("ppc_lwbrx_raS"); assert(fct);
      status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
    }
  }

  void PPC_LLVM_Generator::visit(PPC_lwaux &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_lwaux"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mulli &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *d = ConstantInt::get(i32,instruction.d);
    Function *fct = module->getFunction("ppc_mulli"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,d,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mullw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mullw"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mullw_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mullw_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mullwo &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mullwo"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mullwo_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mullwo_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mulhw &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mulhw"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mulhw_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mulhw_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mulhwu &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mulhwu"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_mulhwu_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_mulhwu_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_nand &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_nand"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_nand_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_nand_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_nor &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_nor"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

  void PPC_LLVM_Generator::visit(PPC_nor_ &instruction) {
    Value *rt = ConstantInt::get(i8,instruction.rt);
    Value *ra = ConstantInt::get(i8,instruction.ra);
    Value *rb = ConstantInt::get(i8,instruction.rb);
    Function *fct = module->getFunction("ppc_nor_"); assert(fct);
    status = IRB.CreateCall4(fct,proc,rt,ra,rb,"status");
  }

} // namespace simsoc
