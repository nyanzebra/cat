#include "ast_program.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_program::accept(code_generator_visitor* visitor) {
  
  return visitor->visit(this); 
}

} // namespace syntax
