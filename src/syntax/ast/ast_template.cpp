#include "ast_template.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_template::accept(code_generator_visitor* visitor) {
   
  return visitor->visit(this);
}

} // namespace syntax
