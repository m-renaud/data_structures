#ifndef MRR_TRIE_HXX_
#define MRR_TRIE_HXX_

#include <map>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
class trie;

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
class trie_node
{
  friend class trie<Key, T>;

  using key_type = Key;

  using value_type = T;
  using reference = T&;
  using const_reference = T const&;

  using node_type = trie_node<Key, T>;
  using edge_type = std::map<typename key_type::value_type, node_type>;

  edge_type edges_;
  bool final_state_;
  value_type value_;

public:
  trie_node()
    : edges_(), final_state_(false), value_(value_type())
  {
  }
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
class trie
{
public:
  using value_type = T;
  using reference = T&;
  using const_reference = T const&;

  using node_type = trie_node<Key,T>;
  using key_type = Key;
  using edge_type = typename node_type::edge_type;
  using iterator = value_type*;

private:
  node_type root_;
  iterator end_;

public:
  trie()
    : root_(), end_(nullptr)
  {
  }
  
  iterator end() const { return end_; }
  
  auto insert(key_type const& key, value_type const& value) -> iterator;
  auto find(key_type const& key) -> iterator;
  auto operator [] (key_type const& key) const -> value_type&;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// trie<T,Index> member functions...
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
auto trie<Key,T>::insert(key_type const& key, value_type const& value)
  -> iterator
{
  node_type* cur = &root_;
  typename edge_type::iterator edge;

  for(auto i = std::begin(key); i != std::end(key); ++i)
  {
    edge = cur->edges_.find(*i);
    if(edge == std::end(cur->edges_))
      cur = &(cur->edges_[*i]);
    else
      cur =&(edge->second);
  }

  cur->value_ = value;
  cur->final_state_ = true;

  return &cur->value_;
}


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
auto trie<Key,T>::operator [] (key_type const& key) const -> value_type&
{
  node_type const* cur = &root_;
  typename edge_type::iterator edge;

  for(auto i = std::begin(key); i != std::end(key);++i)
  {
    edge = cur->edges_.find(*i);
    if(edge == std::end(cur->edges_))
      return end_;
    else
      cur = *edge;
  }
  if(cur->final_state_ == true)
    return cur->value_;
  else
    return end_;
}


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
auto trie<Key,T>::find(key_type const& key) -> iterator
{
  node_type * cur = &root_;
  //  typename edge_type::iterator edge;

  for(auto i = std::begin(key); i != std::end(key);++i)
  {
    auto edge = cur->edges_.find(*i);

    if(edge == std::end(cur->edges_))
      return end_;
    else
      cur = &(edge->second);
  }
  if(cur->final_state_ == true)
    return &cur->value_;
  else
    return end_;
}


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
auto end(trie<Key,T> const& t) -> typename trie<Key,T>::value_type&
{
  return t.end();
}


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#endif // #ifndef MRR_TRIE_HXX_
