#pragma once

namespace syntax {

class ast_sequence : public ast_node {
private:
  std::list<std::unique_ptr<ast_node>> _expression_sequence;
public:
  ~ast_sequence() = default;

  virtual void print() { //TODO: should be able to pretty print with indent
    for (auto it = _expression_sequence.begin(); it != _expression_sequence.end(); ++it) {
      (*it)->print();
    }
  }
  template<typename Visitor, typename = std::enable_if_t<std::is_member_function_pointer<decltype(&Visitor::visit)>::value>>
  typename Visitor::return_type accept(std::unique_ptr<Visitor> visitor) { return visitor->visit(std::make_unique<decltype(this)>(this)); }
};

} // namespace syntax
