#include "ast_return.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_return::accept(code_generator_visitor* visitor, const scope& current_scope) {
   
  return visitor->visit(this, current_scope);
}

} // namespace syntax
