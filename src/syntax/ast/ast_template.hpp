#pragma once

#include "ast_expression.hpp"

namespace syntax {

class ast_template : public ast_expression {
private:
protected:
public:
private:
protected:
public:
template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer_v<decltype(&Visitor::visit)>>>
typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
