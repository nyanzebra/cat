#include "ast_block.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_block::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

} // namespace syntax
