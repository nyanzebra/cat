#include "ast_function.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_function::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
