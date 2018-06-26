#include "ast_pattern.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_pattern::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
