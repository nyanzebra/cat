#pragma once

#include "ast_expression.hpp"

namespace syntax {

  class ast_function : public ast_expression {
  private:
    std::unique_ptr<ast_expression> _prototype, _body;
  protected:
  public:
  private:
  protected:
  public:
    ast_function(std::unique_ptr<ast_expression> prototype, std::unique_ptr<ast_expression> body) : _prototype(std::move(prototype)), _body(std::move(body)) {

    }

    virtual void print() {
      _prototype->print();
      _body->print();
    }


    template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer_v<decltype(&Visitor::visit)>>>
    typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
  };

} // namespace syntax
