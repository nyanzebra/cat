#include "ast_range.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_range::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
