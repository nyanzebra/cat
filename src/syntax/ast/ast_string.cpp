#include "ast_string.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_string::accept(code_generator_visitor* visitor) {
   
  return visitor->visit(this);
}

} // namespace syntax
