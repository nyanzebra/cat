#include "ast_type.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_type::accept(code_generator_visitor* visitor) {
   
  return visitor->visit(this);
}

} // namespace syntax
