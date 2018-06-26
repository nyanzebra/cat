#include "syntax/visitor/code_generator_visitor.hpp"

#include "deps/llvm.hpp"

namespace syntax {

static llvm::LLVMContext gCONTEXT;
static llvm::IRBuilder<> gBUILDER(gCONTEXT);
static llvm::TargetMachine* gTARGET_MACHINE = nullptr;

static llvm::TargetMachine* target_machine() {
  if (gTARGET_MACHINE) return gTARGET_MACHINE;
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

  gTARGET_MACHINE = target->createTargetMachine(trip.getTriple(), "generic", "", options, llvm::Optional<llvm::Reloc::Model>());
  return gTARGET_MACHINE;
}

void code_generator_visitor::initialize() {
  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmParser();
  llvm::InitializeNativeTargetAsmPrinter();

  _main_count = 0u;
  // Any other initialize features

  //llvm::InitializeModule();
  _module = std::make_unique<llvm::Module>("catc", gCONTEXT);

  auto machine = target_machine();
  _module->setDataLayout(machine->createDataLayout());
  _module->setTargetTriple(llvm::sys::getProcessTriple());
  _module->addModuleFlag(llvm::Module::Warning, "Debug Info Version", llvm::DEBUG_METADATA_VERSION);

  if (llvm::Triple(llvm::sys::getProcessTriple()).isOSDarwin()) {
    _module->addModuleFlag(llvm::Module::Warning, "Dwarf Version", 2);
  }

  _dibuilder = std::make_unique<llvm::DIBuilder>(*_module);

  // base types
  context::add_typedef("void", llvm::Type::getVoidTy(gCONTEXT));
  context::add_typedef("bool", llvm::Type::getInt1Ty(gCONTEXT));
  context::add_typedef("int8", llvm::Type::getInt8Ty(gCONTEXT));
  context::add_typedef("int16", llvm::Type::getInt16Ty(gCONTEXT));
  context::add_typedef("int32", llvm::Type::getInt32Ty(gCONTEXT));
  context::add_typedef("int64", llvm::Type::getInt64Ty(gCONTEXT));
  context::add_typedef("uint8", llvm::Type::getInt8Ty(gCONTEXT));
  context::add_typedef("uint16", llvm::Type::getInt16Ty(gCONTEXT));
  context::add_typedef("uint32", llvm::Type::getInt32Ty(gCONTEXT));
  context::add_typedef("uint64", llvm::Type::getInt64Ty(gCONTEXT));
  context::add_typedef("flt32", llvm::Type::getFloatTy(gCONTEXT));
  context::add_typedef("flt64", llvm::Type::getDoubleTy(gCONTEXT));
}
void code_generator_visitor::create_compile_units(const std::list<std::string>& units) {
  bool is_optimized = true;
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

  std::cout << "print module" << std::endl;
  _module->print(llvm::errs(), nullptr);
  std::cout << "dump module" << std::endl;
  _module->dump();

  llvm::legacy::PassManager pass_manager;
  std::error_code err;
  llvm::raw_fd_ostream out(output, err, llvm::sys::fs::F_None);
  if (err) {
    llvm::errs() << "Could not open file: " << err.message();
  }
  std::cout << "add pass to target machine" << std::endl;
  auto machine = target_machine();

  if (machine->addPassesToEmitFile(pass_manager, out, llvm::TargetMachine::CodeGenFileType::CGFT_ObjectFile)) {
    llvm::errs() << "target machine cannot emit file of this type";
  }
  //pass_manager.add(llvm::createPrintModulePass(out, ));
  _dibuilder->finalize();

  std::cout << "running pass manager" << std::endl;
  pass_manager.run(*_module);
  out.flush();
}

llvm::Value* code_generator_visitor::visit(ast_bool* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_bool" <<std::endl;

  return llvm::ConstantInt::getSigned(llvm::Type::getInt1Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_int8* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_int8" <<std::endl;

  return llvm::ConstantInt::getSigned(llvm::Type::getInt8Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_uint8* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_uint8" <<std::endl;

  return llvm::ConstantInt::get(llvm::Type::getInt8Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_int16* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_int16" <<std::endl;

  return llvm::ConstantInt::getSigned(llvm::Type::getInt16Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_uint16* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_uint16" <<std::endl;

  return llvm::ConstantInt::get(llvm::Type::getInt16Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_int32* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_int32" <<std::endl;

  return llvm::ConstantInt::getSigned(llvm::Type::getInt32Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_uint32* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_uint32" <<std::endl;

  return llvm::ConstantInt::get(llvm::Type::getInt32Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_int64* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_int64" <<std::endl;

  return llvm::ConstantInt::getSigned(llvm::Type::getInt64Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_uint64* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_uint64" <<std::endl;

  return llvm::ConstantInt::get(llvm::Type::getInt64Ty(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_flt32* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_flt32" <<std::endl;

  return llvm::ConstantFP::get(llvm::Type::getFloatTy(gCONTEXT), ast->value());
}
llvm::Value* code_generator_visitor::visit(ast_flt64* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_flt64 " << ast->value() <<std::endl;

  return llvm::ConstantFP::get(llvm::Type::getDoubleTy(gCONTEXT), ast->value());
}
void* code_generator_visitor::visit(ast_arm* ast) {

  _module->dump();
  std::cout << "ast_arm" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_assembly* ast) {

  _module->dump();
  std::cout << "ast_assembly" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_binary_operator* ast) {

  _module->dump();
  std::cout << "ast_binary_operator" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_block* ast) {
  if (!ast) {
    std::cout << "block is empty" << std::endl;
  }
  _module->dump();
  std::cout << "ast_block" <<std::endl;

  for (auto&& expr : ast->expressions()) {
    if (expr) {
      if (!expr->accept(this)) {
        return nullptr;
      }
    }
  }
  // TODO: clean this up, want something better than returning self
  return ast;
}
void* code_generator_visitor::visit(ast_for* ast) {

  _module->dump();
  std::cout << "ast_for" <<std::endl;

  return nullptr;
}
llvm::ReturnInst* code_generator_visitor::visit(ast_return* ast) {
  if (!ast) {}
  if (!(ast->expression())) {
    return gBUILDER.CreateRetVoid();
  }
  _module->dump();
  std::cout << "ast_return" <<std::endl;

  return gBUILDER.CreateRet((llvm::Value*)ast->expression()->accept(this));
}
llvm::Value* code_generator_visitor::visit(ast_function_call* ast) {

  _module->dump();
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
    args.push_back(static_cast<llvm::Value*>(arg->accept(this)));
    if (!args.back()) {
      return nullptr;
    }
  }

  return gBUILDER.CreateCall(call, args, "calltmp");
}
llvm::Function* code_generator_visitor::visit(ast_function_prototype* ast) {

  _module->dump();
  std::cout << "ast_function_prototype" <<std::endl;

  if (ast->name() == "main") {
    if (_main_count > 0) {
      std::cout << "Cannot have more than one main function!" << std::endl;
      return nullptr;
    }
    ast->name("cat_main");
    ++_main_count;
  }

  std::vector<llvm::Type*> args(ast->args().size());
  for (const auto& arg : ast->args()) {
    args.push_back(static_cast<llvm::Type*>(arg->accept(this)));
  }
  std::cout << "got function types" << std::endl;
  ast_type* resultant = ast->result().get();
  std::cout << "getting function type" << std::endl;
  llvm::FunctionType* function_type = llvm::FunctionType::get(context::get_typedef(resultant->name()), args, false);

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
llvm::Function* code_generator_visitor::visit(ast_function* ast) {

  _module->dump();
  std::cout << "ast_function" <<std::endl;

  if (!ast->prototype()) {
    // log error
  }
  llvm::Function* function = _module->getFunction(ast->prototype()->name());

  if (!function) {
    // TODO: is this an error?
    std::cout << "no function exists" << std::endl;
    function = visit(ast->prototype().get());
    if (!function) {
      std::cout << "still no function" << std::endl;
    }
  }
  std::cout << "create block" << std::endl;
  llvm::BasicBlock* block = llvm::BasicBlock::Create(gCONTEXT, "entry", function);
  gBUILDER.SetInsertPoint(block);

  for (auto& arg : function->args()) {
    // evaluate each expr and get result for calling function
  }

  auto body = ast->body().get();
  if (!body) {
    // log error
    std::cout << "body is nullptr" << std::endl;
  }

  if (body->accept(this)) {
    std::cout << "verifyFunction" << std::endl;
    llvm::verifyFunction(*function);

    return function;
  }

  function->eraseFromParent();
  return nullptr;
}
void* code_generator_visitor::visit(ast_if* ast) {

  _module->dump();
  std::cout << "ast_if" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_match* ast) {

  _module->dump();
  std::cout << "ast_match" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_meta_class* ast) {

  _module->dump();
  std::cout << "ast_meta_class" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_meta_interface* ast) {

  _module->dump();
  std::cout << "ast_meta_interface" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_pattern* ast) {

  _module->dump();
  std::cout << "ast_pattern" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_program* ast) {

  _module->dump();
  std::cout << "ast_program" <<std::endl;

  for (const auto& expr : ast->expressions()) {
    expr->accept(this);
  }
  return nullptr;
}
void* code_generator_visitor::visit(ast_range* ast) {

  _module->dump();
  std::cout << "ast_range" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_string* ast) {

  _module->dump();
  std::cout << "ast_string" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_template* ast) {

  _module->dump();
  std::cout << "ast_template" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_try* ast) {

  _module->dump();
  std::cout << "ast_try" <<std::endl;

  return nullptr;
}
llvm::Type* code_generator_visitor::visit(ast_type* ast) {

  _module->dump();
  std::cout << "ast_type" <<std::endl;

  return nullptr;
}
void* code_generator_visitor::visit(ast_unary_operator* ast) {

  _module->dump();
  std::cout << "ast_unary_operator" <<std::endl;

  return nullptr;
}
llvm::Value* code_generator_visitor::visit(ast_variable* ast) {
  if (!ast) return nullptr;
  _module->dump();
  std::cout << "ast_variable" << std::endl;

  llvm::Value* value = (llvm::Value*)ast->value()->accept(this);
  std::cout << ((value != nullptr) ? "got value" : "did not get value") << std::endl;
  auto name = ast->name().c_str();
  std::cout << "variable name: " << ast->name() << std::endl;

  // need to keep this in the scope object!
  llvm::Function* fn = gBUILDER.GetInsertBlock()->getParent();

  // TODO: use scope to keep track of teh correct types for variables
  auto alloc = llvm::IRBuilder<>(&fn->getEntryBlock(), fn->getEntryBlock().begin()).CreateAlloca(llvm::Type::getDoubleTy(gCONTEXT),nullptr, name); // need to get TYPE*
  gBUILDER.CreateStore(value, alloc);
  return gBUILDER.CreateLoad(alloc, name);
}
void* code_generator_visitor::visit(ast_while* ast) {

  _module->dump();
  std::cout << "ast_while" <<std::endl;

  return nullptr;
}

} // namespace syntax
