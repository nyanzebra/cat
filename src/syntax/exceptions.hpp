#pragma once



namespace syntax {

class syntax_exception : public std::exception {
private:
  std::string _what;
protected:
public:
private:
protected:
public:
  template<typename T, typename = std::enable_if_t<std::is_constructible_v<std::string, T>>>
  syntax_exception(T&& what) : _what(std::move(what)) {}
  ~syntax_exception() = default;

  virtual const char* what() const noexcept { return _what.c_str(); }
};

}
