#include "ast_arithmetic.hpp"
#include "syntax/ast_visitors.hpp"

namespace syntax {

template <typename T>
void* ast_arithmetic<T>::accept(code_generator_visitor* visitor) {

  return visitor->visit(this);
}

template class ast_arithmetic<bool>;
template class ast_arithmetic<signed char>;
template class ast_arithmetic<unsigned char>;
template class ast_arithmetic<signed short>;
template class ast_arithmetic<unsigned short>;
template class ast_arithmetic<signed long>;
template class ast_arithmetic<unsigned long>;
template class ast_arithmetic<signed long long>;
template class ast_arithmetic<unsigned long long>;
template class ast_arithmetic<float>;
template class ast_arithmetic<double>;

} // namespace syntax
