#pragma once

#include "ast_expression.hpp"

namespace syntax {

// need for match
class ast_arm final : public ast_expression {
private:
protected:
public:
private:
protected:
public:
  void print(size_t indent) override {}

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
