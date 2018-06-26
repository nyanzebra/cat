#include "ast_meta_class.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

void* ast_meta_class::accept(code_generator_visitor* visitor) {
   
  return visitor->visit(this);
}

} // namespace syntax
