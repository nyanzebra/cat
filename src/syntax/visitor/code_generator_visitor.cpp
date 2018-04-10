#include "syntax/visitor/code_generator_visitor.hpp"
//#include "output/logger.hpp"

// #endif
// #endif
// #if LLVM_VERSION_GE(4, 0)
// #if LLVM_VERSION_LE(4, 0)
// #include "llvm-c/Transforms/PassManagerBuilder.h"
// #include "llvm/Analysis/TargetLibraryInfo.h"
// #include "llvm/Analysis/TargetTransformInfo.h"
// #include "llvm/ExecutionEngine/ExecutionEngine.h"
// #include "llvm/ExecutionEngine/Interpreter.h"
// #include "llvm/ExecutionEngine/MCJIT.h"
// #include "llvm/IR/AssemblyAnnotationWriter.h"
// #include "llvm/IR/AutoUpgrade.h"
// #include "llvm/IR/DebugInfo.h"
// #include "llvm/IR/DIBuilder.h"
// #include "llvm/IR/IRPrintingPasses.h"
// #include "llvm/Linker/Linker.h"
// #include "llvm/LTO/LTO.h"
// #include "llvm/Object/ModuleSummaryIndexObjectFile.h"
// #include "llvm/Support/CBindingWrapping.h"
// #include "llvm/Support/Host.h"
// #include "llvm/Transforms/IPO/AlwaysInliner.h"
// #include "llvm/Transforms/IPO/FunctionImport.h"
// #include "llvm/Transforms/IPO/PassManagerBuilder.h"
// #include "llvm/Transforms/Utils/FunctionImportUtils.h"
#include "llvm-c/BitReader.h"
#include "llvm-c/Core.h"
#include "llvm-c/ExecutionEngine.h"
#include "llvm-c/Object.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/DenseSet.h"
#include "llvm/ADT/Triple.h"
#include "llvm/Analysis/Lint.h"
#include "llvm/Analysis/Passes.h"
//#include "llvm/Bitcode/ReaderWriter.h"
#include "llvm/IR/InlineAsm.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/PassManager.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/DynamicLibrary.h"
#include "llvm/Support/FileSystem.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/Host.h"
#include "llvm/Support/Memory.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Support/Timer.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetOptions.h"
#include "llvm/Target/TargetSubtargetInfo.h"
#include "llvm/Transforms/Instrumentation.h"
#include "llvm/Transforms/IPO.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Vectorize.h"

namespace syntax {

static llvm::LLVMContext gCONTEXT;
static llvm::IRBuilder<> gBUILDER(gCONTEXT);

llvm::TargetMachine* target_machine() {
  std::string error;
  auto triple = llvm::sys::getProcessTriple();
  std::cout << "triple " << triple << std::endl;
  llvm::Triple trip(triple);
  const llvm::Target *target = llvm::TargetRegistry::lookupTarget(trip.getTriple(), error);
  std::cout << "target " << (target == nullptr) << " " << error << std::endl;
  if (target == nullptr) {
    //LLVMRustSetLastError(error.c_str());
    return nullptr;
  }

  llvm::TargetOptions options;
  // #if LLVM_VERSION_LE(3, 8)
  // options.PositionIndependentExecutable = true;
  // #endif

  options.FloatABIType = llvm::FloatABI::Default;
  // if (UseSoftFloat) {
  //   options.FloatABIType = llvm::FloatABI::Soft;
  // }
  options.DataSections = true;
  options.FunctionSections = true;

  // if (TrapUnreachable) {
  //   // Tell LLVM to translate `unreachable` into an explicit trap instruction.
  //   // This limits the extent of possible undefined behavior in some cases, as
  //   // it prevents control flow from "falling through" into whatever code
  //   // happens to be laid out next in memory.
  //   options.TrapUnreachable = true;
  // }

  return target->createTargetMachine(trip.getTriple(), "generic", "", options, llvm::Optional<llvm::Reloc::Model>());
}

void code_generator_visitor::initialize() {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmParser();
  llvm::InitializeNativeTargetAsmPrinter();

  // Any other initialize features

  //llvm::InitializeModule();
  _module = std::make_unique<llvm::Module>("cat", gCONTEXT);
  //_module->setDataLayout()
  _module->addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);

  if (llvm::Triple(llvm::sys::getProcessTriple()).isOSDarwin()) {
    _module->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2);
  }

  _dibuilder = std::make_unique<llvm::DIBuilder>(*_module);
}
void code_generator_visitor::create_compile_units(const std::list<std::string>& units) {
  bool is_optimized = false;
  std::string flags = "";
  auto runtime_version = 0u;
  for (const auto& unit : units) {
    auto filename = unit.substr(unit.find_last_of("/"));
    auto directory = unit.substr(0, unit.find_last_of("/"));
    llvm::DIFile* file = _dibuilder->createFile(filename, directory);
    _compile_unit = _dibuilder->createCompileUnit(llvm::dwarf::DW_LANG_C_plus_plus_14, file, "Cat 1.0.0", is_optimized, flags, runtime_version);
  }
}
void code_generator_visitor::finalize(const std::string& output) {
  llvm::legacy::PassManager pass_manager;
  std::error_code err;
  llvm::raw_fd_ostream out(output, err, llvm::sys::fs::F_None);
  std::cout << "add pass to target machine" << std::endl;
  auto machine = target_machine();

  machine->addPassesToEmitFile(pass_manager, out, llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile);
  //pass_manager.add(llvm::createPrintModulePass(out, ));
  std::cout << "running pass manager" << std::endl;
  pass_manager.run(*_module);
  out.flush();
  std::cout << "dump module" << std::endl;
  _dibuilder->finalize();
  _module->print(llvm::errs(), nullptr);
  _module->dump();
}

llvm::Value* code_generator_visitor::visit(ast_bool* ast, const scope& current_scope) {
  std::cout << "ast_bool" <<std::endl;

  return llvm::ConstantInt::getSigned(llvm::Type::getInt1Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_int8* ast, const scope& current_scope) {
  std::cout << "ast_int8" <<std::endl;

  return llvm::ConstantInt::getSigned(llvm::Type::getInt8Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_uint8* ast, const scope& current_scope) {
  std::cout << "ast_uint8" <<std::endl;

  return llvm::ConstantInt::get(llvm::Type::getInt8Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_int16* ast, const scope& current_scope) {
  std::cout << "ast_int16" <<std::endl;

  return llvm::ConstantInt::getSigned(llvm::Type::getInt16Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_uint16* ast, const scope& current_scope) {
  std::cout << "ast_uint16" <<std::endl;

  return llvm::ConstantInt::get(llvm::Type::getInt16Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_int32* ast, const scope& current_scope) {
  std::cout << "ast_int32" <<std::endl;

  return llvm::ConstantInt::getSigned(llvm::Type::getInt32Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_uin32* ast, const scope& current_scope) {
  std::cout << "ast_uint32" <<std::endl;

  return llvm::ConstantInt::get(llvm::Type::getInt32Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_int64* ast, const scope& current_scope) {
  std::cout << "ast_int64" <<std::endl;

  return llvm::ConstantInt::getSigned(llvm::Type::getInt64Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_uint64* ast, const scope& current_scope) {
  std::cout << "ast_uint64" <<std::endl;

  return llvm::ConstantInt::get(llvm::Type::getInt64Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_flt32* ast, const scope& current_scope) {
  std::cout << "ast_flt32" <<std::endl;

  return llvm::ConstantInt::get(llvm::Type::getFloatTy(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_flt64* ast, const scope& current_scope) {
  std::cout << "ast_flt64" <<std::endl;

  return llvm::ConstantInt::get(llvm::Type::getDoubleTy(gCONTEXT), ast->value());
}
void* code_generator_visitor::visit(ast_arm* ast, const scope& current_scope) {
  std::cout << "ast_arm" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_assembly* ast, const scope& current_scope) {
  std::cout << "ast_assembly" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_binary_operator* ast, const scope& current_scope) {
  std::cout << "ast_binary_operator" <<std::endl;

  return nullptr;
}
llvm::Value* code_generator_visitor::visit(ast_block* ast, const scope& current_scope) {
  std::cout << "ast_block" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_for* ast, const scope& current_scope) {
  std::cout << "ast_for" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_return* ast, const scope& current_scope) {
  std::cout << "ast_return" <<std::endl;

  return nullptr;
}
llvm::Value* code_generator_visitor::visit(ast_function_call* ast, const scope& current_scope) {
  std::cout << "ast_function_call" <<std::endl;

  llvm::Function* call = _module->getFunction(ast->callee());

  if (!call) {
    //_log.error("Function does not exist, therefore cannot call ", ast->callee());
    return nullptr;
  }

  if (call->arg_size() != ast->args().size()) {
    //_log.error("Function does not have appropriate amount of arguments ", ast->callee());
    return nullptr;
  }

  std::vector<llvm::Value*> args;
  for (auto& arg : ast->args()) {
    args.push_back(static_cast<llvm::Value*>(arg->accept(this, current_scope)));
    if (!args.back()) {
      return nullptr;
    }
  }

  return gBUILDER.CreateCall(call, args, "calltmp");
}
llvm::Function* code_generator_visitor::visit(ast_function_prototype* ast, const scope& current_scope) {
  std::cout << "ast_function_prototype" <<std::endl;

  std::vector<llvm::Type*> args(ast->args().size());
  for (const auto& arg : ast->args()) {
    args.push_back(static_cast<llvm::Type*>(arg->accept(this, current_scope)));
  }
  std::cout << "got function types" << std::endl;
  ast_type* resultant = ast->result().get();
  std::cout << "getting function type" << std::endl;
  llvm::FunctionType* function_type = llvm::FunctionType::get(/*TODO get actual type later*/llvm::Type::getVoidTy(gCONTEXT), args, false);

  if (!function_type) {
    // log error?
    std::cout << "no function type" << std::endl;
  }

  std::cout << "get function" << std::endl;
  llvm::Function* function = llvm::Function::Create(function_type, llvm::Function::ExternalLinkage, ast->name(), _module.get());

  if (!function) {
    //_log.error("Cannot create function ", ast->name());
    std::cout << "no function" << std::endl;
    return nullptr;
  }

  auto args_it = ast->args().begin();
  std::cout << "set names" << std::endl;
  for (auto& arg : function->args()) {
    arg.setName((*args_it)->name());
    ++args_it;
  }

  return function;
}
llvm::Function* code_generator_visitor::visit(ast_function* ast, const scope& current_scope) {
  std::cout << "ast_function" <<std::endl;

  if (!ast->prototype()) {
    // log error
  }
  llvm::Function* function = _module->getFunction(ast->prototype()->name());

  if (!function) {
    // TODO: is this an error?
    std::cout << "no function exists" << std::endl;
    function = visit(ast->prototype().get(), current_scope);
    if (!function) {
      std::cout << "still no function" << std::endl;
    }
  }
  std::cout << "create block" << std::endl;
  llvm::BasicBlock* block = llvm::BasicBlock::Create(gCONTEXT, "entry", function);
  gBUILDER.SetInsertPoint(block);

  scope next_scope(current_scope);
  for (auto& arg : function->args()) {
    // evaluate each expr and get resut for calling function
  }

  auto body = ast->body().get();
  if (!body) {
    // log error
    std::cout << "body is nullptr" << std::endl;
  }

  if (llvm::Value* result = static_cast<llvm::Value*>(body->accept(this, next_scope))) {
    gBUILDER.CreateRet(result);
    std::cout << "verifyFunction" << std::endl;
    llvm::verifyFunction(*function);

    return function;
  }

  function->eraseFromParent();
  return nullptr;
}
void* code_generator_visitor::visit(ast_if* ast, const scope& current_scope) {
  std::cout << "ast_if" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_match* ast, const scope& current_scope) {
  std::cout << "ast_match" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_meta_class* ast, const scope& current_scope) {
  std::cout << "ast_meta_class" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_meta_interface* ast, const scope& current_scope) {
  std::cout << "ast_meta_interface" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_pattern* ast, const scope& current_scope) {
  std::cout << "ast_pattern" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_program* ast, const scope& current_scope) {
  std::cout << "ast_program" <<std::endl;

  for (const auto& expr : ast->expressions()) {
    expr->accept(this, current_scope);
  }
  return nullptr;
}
void* code_generator_visitor::visit(ast_range* ast, const scope& current_scope) {
  std::cout << "ast_range" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_string* ast, const scope& current_scope) {
  std::cout << "ast_string" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_template* ast, const scope& current_scope) {
  std::cout << "ast_template" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_try* ast, const scope& current_scope) {
  std::cout << "ast_try" <<std::endl;

  return nullptr;
}
llvm::Type* code_generator_visitor::visit(ast_type* ast, const scope& current_scope) {
  std::cout << "ast_type" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_unary_operator* ast, const scope& current_scope) {
  std::cout << "ast_unary_operator" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_variable* ast, const scope& current_scope) {
  std::cout << "ast_variable" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_while* ast, const scope& current_scope) {
  std::cout << "ast_while" <<std::endl;

  return nullptr;
}

} // namespace syntax
