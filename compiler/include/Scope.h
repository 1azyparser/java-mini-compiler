#ifndef SCOPE_H
#define SCOPE_H
#include <optional>
#include <string>
#include <unordered_map>

using std::optional;
using std::string;
using std::unordered_map;

template <typename T>
class Scope
{
public:
  Scope<T> *parent;
  unordered_map<string, T> table;

  explicit Scope(Scope<T> *parent = nullptr) : parent{parent} {}

  optional<T> resolve(string key)
  {
    if (table.count(key))
    {
      return table[key];
    }
    else if (parent)
    {
      return parent->resolve(key);
    }
    else
    {
      return optional<T>();
    }
  }

  void put(string key, T value) { table[key] = value; }
};

#endif // SCOPE_H