#ifndef TABLE_H
#define TABLE_H
#include <unordered_map>
#include <vector>

using std::unordered_map;
using std::vector;

template <typename TKey, typename TValue>
class Table
{
public:
  unordered_map<TKey, size_t> index_map;
  vector<TValue> values;

  Table() {}

  void add(const TKey &key, const TValue &value)
  {
    if (index_map.count(key))
    {
      values.at(index_map.at(key)) = value;
    }
    else
    {
      size_t index = values.size();
      index_map.insert({key, index});
      values.push_back(value);
    }
  }

  TValue find_by_index(size_t index) { return values.at(index); }
  TValue find_by_key(const TKey &key) { return values.at(index_map.at(key)); }
  bool has_key(const TKey &key) const { return index_map.count(key) == 1; }
  size_t get_index(const TKey &key) const { return index_map.at(key); }
};

#endif // TABLE_H