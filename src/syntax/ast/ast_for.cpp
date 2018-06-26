#include "ast_for.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_for::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
