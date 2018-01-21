#pragma once

#include "deps/std.hpp"

namespace syntax {

template<typename Policy>
class ast_visitor {
private:
  typedef typename Policy::ast_type ast_type;
  //llvm::code_generator _code_generator;
protected:
public:
private:
protected:
public:
  typename Policy::return_type visit(typename Policy::unique_ast_type ast, typename std::enable_if_t<std::is_member_function_pointer<decltype(&ast_type::accept)>::value>* = 0) { return Policy::visit(std::move(ast)); }
}; // class visitor

} // namespace syntax
