#pragma once

#include "syntax/ast.hpp"
#include "syntax/scope.hpp"
//#include "output/logger.hpp"

#include "deps/llvm.hpp"

namespace syntax {

class code_generator_visitor {
private:
  std::unique_ptr<llvm::Module> _module;
  std::unique_ptr<llvm::DIBuilder> _dibuilder;
  //output::logger _log(output::output_type::kSTANDARD_ERROR);
  size_t _main_count;
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

  llvm::Value* visit(ast_bool* ast);
  llvm::Value* visit(ast_int8* ast);
  llvm::Value* visit(ast_uint8* ast);
  llvm::Value* visit(ast_int16* ast);
  llvm::Value* visit(ast_uint16* ast);
  llvm::Value* visit(ast_int32* ast);
  llvm::Value* visit(ast_uint32* ast);
  llvm::Value* visit(ast_int64* ast);
  llvm::Value* visit(ast_uint64* ast);
  llvm::Value* visit(ast_flt32* ast);
  llvm::Value* visit(ast_flt64* ast);
  void* visit(ast_arm* ast);
  void* visit(ast_assembly* ast);
  void* visit(ast_binary_operator* ast);
  void* visit(ast_block* ast);
  void* visit(ast_for* ast);
  llvm::Value* visit(ast_function_call* ast);
  llvm::Function* visit(ast_function_prototype* ast);
  llvm::Function* visit(ast_function* ast);
  void* visit(ast_if* ast);
  void* visit(ast_match* ast);
  void* visit(ast_meta_class* ast);
  void* visit(ast_meta_interface* ast);
  void* visit(ast_pattern* ast);
  void* visit(ast_program* ast);
  void* visit(ast_range* ast);
  void* visit(ast_string* ast);
  void* visit(ast_template* ast);
  void* visit(ast_try* ast);
  llvm::Type* visit(ast_type* ast);
  void* visit(ast_unary_operator* ast);
  llvm::Value* visit(ast_variable* ast);
  void* visit(ast_while* ast);
  llvm::ReturnInst* visit(ast_return* ast);
}; // class visitor

} // namespace syntax
