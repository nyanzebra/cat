#include "ast_return.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_return::accept(code_generator_visitor* visitor) {
   
  return visitor->visit(this);
}

} // namespace syntax
