#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_template final : public ast_expression {
private:
protected:
public:
private:
protected:
public:
  std::ostream& print(std::ostream& stream, size_t tabs = 0) override { return stream; }

  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
