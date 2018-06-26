#include "ast_unary_operator.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_unary_operator::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
