#include "ast_assembly.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_assembly::accept(code_generator_visitor* visitor, const scope& current_scope) {
  
  return visitor->visit(this, current_scope);
}

} // namespace syntax
