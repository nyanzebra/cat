#pragma once

#include "deps/std.hpp"

template<typename Key, typename Value>
class cache {
private:
  typedef std::list<Value> item_list;
  typedef std::unordered_map<Key, typename item_list::iterator> item_map;

  item_list _item_list;
  item_map _item_map;
protected:
public:
  size_t size() const { return _item_list.size(); }

  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  bool has(const T& key) { return _item_map.find(key) != _item_map.end(); }
  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  bool has(T&& key) { return _item_map.find(std::move(key)) != _item_map.end(); }

  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  Value& at(const T& key) { return this->operator[](key); }
  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  const Value& at(const T& key) const { return this->operator[](key); }
  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  Value& at(T&& key) { return this->operator[](std::move(key)); }
  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  const Value& at(T&& key) const { return this->operator[](std::move(key)); }

  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  Value& operator[](const T& key) { return *(_item_map.find(key)->second); }
  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  const Value& operator[](const T& key) const { return *(_item_map.find(key)->second); }
  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  Value& operator[](T&& key) { return *(_item_map.find(std::move(key))->second); }
  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  const Value& operator[](T&& key) const { return *(_item_map.find(std::move(key))->second); }

  template<typename T = Key, typename U = Value, typename = std::enable_if_t<std::is_constructible<Key, T>::value && std::is_constructible<Value, U>::value>>
  void insert(const T& key, const U& value) {
    _item_list.push_front(value);
    auto it = _item_list.begin();
    _item_map[key] = it;
  }
  template<typename T = Key, typename U = Value, typename = std::enable_if_t<std::is_constructible<Key, T>::value && std::is_constructible<Value, U>::value>>
  void insert(T&& key, U&& value) {
    _item_list.push_front(std::move(value));
    auto it = _item_list.begin();
    _item_map[std::move(key)] = it;
  }

  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  void erase(const T& key) {
    _item_list.erase(_item_map[key]);
    _item_map.erase(key);
  }
  template<typename T = Key, typename = std::enable_if_t<std::is_constructible<Key, T>::value>>
  void erase(T&& key) {
    _item_list.erase(_item_map[std::move(key)]);
    _item_map.erase(std::move(key));
  }
};
