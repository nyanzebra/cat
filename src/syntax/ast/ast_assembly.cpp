#include "ast_assembly.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_assembly::accept(code_generator_visitor* visitor) {
  
  return visitor->visit(this);
}

} // namespace syntax
