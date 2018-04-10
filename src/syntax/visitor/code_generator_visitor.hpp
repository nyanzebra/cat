#pragma once

#include "syntax/ast.hpp"
#include "syntax/scope.hpp"
//#include "output/logger.hpp"

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

namespace syntax {

class code_generator_visitor {
private:
  std::unique_ptr<llvm::Module> _module;
  std::unique_ptr<llvm::DIBuilder> _dibuilder;
  //output::logger _log(output::output_type::kSTANDARD_ERROR);

  llvm::DICompileUnit* _compile_unit;
protected:
public:
  typedef llvm::Type llvm_type;
  typedef llvm::Value llvm_value;
  typedef llvm::Function llvm_function;
  typedef llvm::FunctionType llvm_function_type;
private:
protected:
public:
  void initialize();
  void create_compile_units(const std::list<std::string>& units);
  void finalize(const std::string& output);

  llvm::Value* visit(ast_bool* ast, const scope& current_scope);
  llvm::Value* visit(ast_int8* ast, const scope& current_scope);
  llvm::Value* visit(ast_uint8* ast, const scope& current_scope);
  llvm::Value* visit(ast_int16* ast, const scope& current_scope);
  llvm::Value* visit(ast_uint16* ast, const scope& current_scope);
  llvm::Value* visit(ast_int32* ast, const scope& current_scope);
  llvm::Value* visit(ast_uin32* ast, const scope& current_scope);
  llvm::Value* visit(ast_int64* ast, const scope& current_scope);
  llvm::Value* visit(ast_uint64* ast, const scope& current_scope);
  llvm::Value* visit(ast_flt32* ast, const scope& current_scope);
  llvm::Value* visit(ast_flt64* ast, const scope& current_scope);
  void* visit(ast_arm* ast, const scope& current_scope);
  void* visit(ast_assembly* ast, const scope& current_scope);
  void* visit(ast_binary_operator* ast, const scope& current_scope);
  llvm::Value* visit(ast_block* ast, const scope& current_scope);
  void* visit(ast_for* ast, const scope& current_scope);
  llvm::Value* visit(ast_function_call* ast, const scope& current_scope);
  llvm::Function* visit(ast_function_prototype* ast, const scope& current_scope);
  llvm::Function* visit(ast_function* ast, const scope& current_scope);
  void* visit(ast_if* ast, const scope& current_scope);
  void* visit(ast_match* ast, const scope& current_scope);
  void* visit(ast_meta_class* ast, const scope& current_scope);
  void* visit(ast_meta_interface* ast, const scope& current_scope);
  void* visit(ast_pattern* ast, const scope& current_scope);
  void* visit(ast_program* ast, const scope& current_scope);
  void* visit(ast_range* ast, const scope& current_scope);
  void* visit(ast_string* ast, const scope& current_scope);
  void* visit(ast_template* ast, const scope& current_scope);
  void* visit(ast_try* ast, const scope& current_scope);
  llvm::Type* visit(ast_type* ast, const scope& current_scope);
  void* visit(ast_unary_operator* ast, const scope& current_scope);
  void* visit(ast_variable* ast, const scope& current_scope);
  void* visit(ast_while* ast, const scope& current_scope);
  void* visit(ast_return* ast, const scope& current_scope);
}; // class visitor

} // namespace syntax
