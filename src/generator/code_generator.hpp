#pragma once

#include "llvm/ADT/STLExtras.h"
#include "llvm/Analysis/BasicAliasAnalysis.h"
#include "llvm/Analysis/Passes.h"
#include "llvm/IR/DIBuilder.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/TargetSelect.h"
#include "llvm/Transforms/Scalar.h"

#include "deps/std.hpp"
#include "syntax/ast.hpp"
#include "output/logger.hpp"

namespace llvm {

static LLVMContext gCONTEXT;
static IRBuilder<> gBUILDER(gCONTEXT);

class code_generator {
private:
  std::unique_ptr<Module> _module;
  std::unique_ptr<DIBuilder> _dibuilder;
  output::logger _log(output::output_type::kSTANDARD_ERROR);

  std::unique_ptr<DICompileUnit> _compile_unit;
protected:
public:
  typedef Type llvm_type;
  typedef Value llvm_value;
  typedef Function llvm_function;
  typedef FunctionType llvm_function_type;
private:
protected:
public:
  void initialize() {
    InitializeNativeTarget();
    InitializeNativeTargetAsmParser();
    InitializeNativeTargetAsmPrinter();

    // Any other initialize features

    //InitializeModule();
    _module = std::make_unique<Module>("cat", gCONTEXT);
    //_module->setDataLayout()
    _module->addModuleFlag(Module::Warning, "Debug Info Version", DEBUG_METADATA_VERSION);

    if (Triple(sys::getProcessTriple()).isOSDarwin()) {
      _module->addModuleFlag(Module::Warning, "Dwarf Version", 2);
    }

    _dibuilder = std::make_unique<DIBuilder>(*_module);
  }
  void create_compile_units(const std::list<std::string>& units) {
    bool is_optimized = false;
    std::string flags = "";
    auto runtime_version = 0u;
    for (const auto& unit : units) {
      auto filename = unit.substr(unit.find_last_of("/"));
      auto directory = unit.substr(0, unit.find_last_of("/"));
      DIFile* file = _dibuilder->createFile(filename, directory);
      _compile_unit.reset(_dibuilder->createCompileUnit(dwarf::DW_LANG_C_plus_plus_14, file, "Cat 1.0.0", is_optimized, flags, runtime_version));
    }
  }
  void finalize() {
    _dibuilder->finalize();
    _module->print(errs(), nullptr);
  }

  static Value* generate(const std::unique_ptr<ast_bool>& ast, const scope& current_scope) {
    return ConstantInt::getSigned(Type::getInt1Ty(gCONTEXT), ast->value());
  }
  static Value* generate(const std::unique_ptr<ast_int8>& ast, const scope& current_scope) {
    return ConstantInt::getSigned(Type::getInt8Ty(gCONTEXT), ast->value());
  }
  static Value* generate(const std::unique_ptr<ast_uint8>& ast, const scope& current_scope) {
    return ConstantInt::get(Type::getInt8Ty(gCONTEXT), ast->value());
  }
  static Value* generate(const std::unique_ptr<ast_int16>& ast, const scope& current_scope) {
    return ConstantInt::getSigned(Type::getInt16Ty(gCONTEXT), ast->value());
  }
  static Value* generate(const std::unique_ptr<ast_uint16>& ast, const scope& current_scope) {
    return ConstantInt::get(Type::getInt16Ty(gCONTEXT), ast->value());
  }
  static Value* generate(const std::unique_ptr<ast_int32>& ast, const scope& current_scope) {
    return ConstantInt::getSigned(Type::getInt32Ty(gCONTEXT), ast->value());
  }
  static Value* generate(const std::unique_ptr<ast_uin32>& ast, const scope& current_scope) {
    return ConstantInt::get(Type::getInt32Ty(gCONTEXT), ast->value());
  }
  static Value* generate(const std::unique_ptr<ast_int64>& ast, const scope& current_scope) {
    return ConstantInt::getSigned(Type::getInt64Ty(gCONTEXT), ast->value());
  }
  static Value* generate(const std::unique_ptr<ast_uint64>& ast, const scope& current_scope) {
    return ConstantInt::get(Type::getInt64Ty(gCONTEXT), ast->value());
  }
  static Value* generate(const std::unique_ptr<ast_flt32>& ast, const scope& current_scope) {
    return ConstantInt::get(Type::getFloatTy(gCONTEXT), ast->value());
  }
  static Value* generate(const std::unique_ptr<ast_flt64>& ast, const scope& current_scope) {
    return ConstantInt::get(Type::getDoubleTy(gCONTEXT), ast->value());
  }
  static void generate(const std::unique_ptr<ast_arm>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_assembly>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_binary_operator>& ast, const scope& current_scope) const {

  }
  static Value* generate(const std::unique_ptr<ast_block>& ast, const scope& current_scope) const {
    return nullptr;
  }
  static void generate(const std::unique_ptr<ast_conditional>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_expression>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_for>& ast, const scope& current_scope) const {

  }
  static Value* generate(const std::unique_ptr<ast_function_call>& ast, const scope& current_scope) const {
    Function* call = _module->getFunction(ast->callee());

    if (!call) {
      _log.error("Function does not exist, therefore cannot call ", ast->callee());
      return nullptr;
    }

    if (call->arg_size() != ast->args().size()) {
      _log.error("Function does not have appropriate amount of arguments ", ast->callee());
      return nullptr;
    }

    std::vector<Value*> args;
    for (auto& arg : ast->args()) {
      args.push_back(visit(arg, current_scope));
      if (!args.back()) {
        return nullptr;
      }
    }

    return gBUILDER.CreateCall(call, args, "calltmp");
  }
  static Function* generate(const std::unique_ptr<ast_function_prototype>& ast, const scope& current_scope) const {
    std::vector<Type*> args(ast->args().size());
    for (const auto& arg : ast->args()) {
      args.push_back(visit(arg, current_scope));
    }

    auto resultant = std::move(ast->result());
    Type* return_type;
    FunctionType* function_type = FunctionType::get(return_type, args, false);

    if (!function_type) {
      // log error?
    }

    Function* function = Function::Create(function_type, Function::ExternalLinkage, ast->name(), _module.get());

    if (!function) {
      _log.error("Cannot create function ", ast->name());
      return nullptr;
    }

    auto args_it = ast->args().begin();

    for (auto& arg : function->args()) {
      arg.setName(args_it->name());
      ++args_it;
    }

    return function;
  }
  static Function* generate(const std::unique_ptr<ast_function>& ast, const scope& current_scope) const {
    Function* function = _module->getFunction(ast->prototype()->name());

    if (!function) {
      // TODO: is this an error?
    }

    BasicBlock* block = BasicBlock::Create(gCONTEXT, "entry", function);
    gBUILDER.SetInsertPoint(block);

    scope next_scope(current_scope);
    for (auto& arg : function->args()) {

    }

    if (Value* result = generate(ast->body(), next_scope)) {
      gBUILDER.CreateRet(result);

      verifyFunction(*function);

      return function;
    }

    function->eraseFromParent();
    return nullptr;
  }
  static void generate(const std::unique_ptr<ast_if>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_match>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_meta_class>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_meta_interface>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_node>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_pattern>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_program>& ast, const scope& current_scope) const {
    for (const auto& expr : ast->expressions()) {
      visit(expr, current_scope);
    }
  }
  static void generate(const std::unique_ptr<ast_range>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_string>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_template>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_try>& ast, const scope& current_scope) const {

  }
  static Type* generate(const std::unique_ptr<ast_type>& ast, const scope& current_scope) const {
    return nullptr;
  }
  static void generate(const std::unique_ptr<ast_unary_operator>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_variable>& ast, const scope& current_scope) const {

  }
  static void generate(const std::unique_ptr<ast_while>& ast, const scope& current_scope) const {

  }
}; // class generateor

} // namespace syntax
