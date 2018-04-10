#include "ast_if.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_if::accept(code_generator_visitor* visitor, const scope& current_scope) {

  return visitor->visit(this, current_scope);
}

} // namespace syntax
