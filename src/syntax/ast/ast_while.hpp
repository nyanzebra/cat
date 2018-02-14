#pragma once

#include "ast_conditional.hpp"

namespace syntax {

class ast_while final : public ast_conditional {
private:
protected:
public:
private:
protected:
public:
  void print() override {}

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
