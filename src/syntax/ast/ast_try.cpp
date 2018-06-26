#include "ast_try.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_try::accept(code_generator_visitor* visitor) {
   
  return visitor->visit(this);
}

} // namespace syntax
