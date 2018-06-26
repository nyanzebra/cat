#include "ast_match.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_match::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
