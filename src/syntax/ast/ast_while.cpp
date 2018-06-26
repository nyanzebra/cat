#include "ast_while.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_while::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
