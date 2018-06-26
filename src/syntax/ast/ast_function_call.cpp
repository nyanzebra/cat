#include "ast_function_call.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_function_call::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
