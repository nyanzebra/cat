#pragma once

#include "ast_visitor.hpp"
#include "syntax/ast/ast_type.hpp"

namespace syntax {

class type_visitor_policy {
private:
protected:
public:
  typedef std::experimental::optional<void*> return_type;
  typedef ast_type ast_type;
  typedef std::unique_ptr<ast_type> unique_ast_type;
private:
protected:
public:
  return_type visit(unique_ast_type ast) { return nullptr;/*return llvm::generate_type<T>(expr->value());*/ }
};

} // namespace syntax
