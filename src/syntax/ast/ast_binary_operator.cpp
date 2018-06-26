#include "ast_binary_operator.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_binary_operator::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
