#pragma once

namespace syntax {

template<typename T> class ast_type;

template<typename T>
class type_visitor : public ast_visitor</* TODO: Value* */ void*, ast_type<T>> {
private:
  typedef ast_visitor</* TODO: Value* */ void*, ast_type<T>> parent_type;
protected:
public:
  typedef typename parent_type::return_type return_type;
  typedef typename parent_type::unique_ast_type unique_ast_type;
private:
protected:
public:
  virtual ~type_visitor() = default;

  return_type visit(unique_ast_type ast) { return nullptr;/*return llvm::generate_type<T>(expr->value());*/ }
};

} // namespace syntax
