#include "ast_function.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_function::accept(code_generator_visitor* visitor, const scope& current_scope) {

  return visitor->visit(this, current_scope);
}

} // namespace syntax
