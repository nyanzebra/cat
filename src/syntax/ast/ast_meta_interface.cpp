#include "ast_expression.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_meta_interface::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
