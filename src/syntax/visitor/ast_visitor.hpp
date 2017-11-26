#pragma once

#include "deps/std.hpp"

namespace syntax {

template<typename Return, typename Ast, typename = std::enable_if_t<std::is_member_function_pointer_v<decltype(&Ast::accept)>>>
class ast_visitor {
private:
  //llvm::code_generator _code_generator;
protected:
public:
  typedef std::experimental::optional<Return> return_type;
  typedef std::unique_ptr<Ast> unique_ast_type;
private:
protected:
public:
  virtual ~ast_visitor() = default;

  virtual return_type visit(unique_ast_type ast) { return nullptr; }
}; // class visitor

} // namespace syntax
