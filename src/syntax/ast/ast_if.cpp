#include "ast_if.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_if::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
