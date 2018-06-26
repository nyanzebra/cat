#include "ast_variable.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_variable::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
