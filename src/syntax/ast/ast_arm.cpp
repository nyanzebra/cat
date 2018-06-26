#include "ast_arm.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_arm::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
