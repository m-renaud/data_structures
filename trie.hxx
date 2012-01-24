#ifndef MRR_TRIE_HXX_
#define MRR_TRIE_HXX_

#include <map>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
class trie;

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
class trie_node
{
  friend class trie<Key, T>;

  typedef Key key_type;

  typedef T value_type;
  typedef T& reference;
  typedef T const& const_reference;

  typedef trie_node<Key, T> node_type;
  typedef std::map<typename key_type::value_type, node_type> edge_type;

  edge_type edges_;
  bool final_state_;
  value_type value_;

public:
  trie_node();
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
class trie
{
public:
  typedef T value_type;
  typedef T& reference;
  typedef T const& const_reference;

  typedef trie_node<Key,T> node_type;
  typedef Key key_type;
  typedef typename node_type::edge_type edge_type;
  typedef value_type* iterator;

private:
  node_type root_;
  iterator end_;

public:
  trie();
  auto end() const -> iterator;
  auto insert(key_type const& key, value_type const& value) -> value_type&;
  auto find(key_type const& key) -> iterator;
  auto operator [] (key_type const& key) const -> value_type&;
};


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// trie_node<Key,T> member functions...
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
trie_node<Key,T>::trie_node()
  : edges_(), final_state_(false), value_(value_type())
{
}


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// trie<T,Index> member functions...
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
trie<Key,T>::trie()
  : root_(), end_(nullptr)
{
}


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
auto trie<Key,T>::end() const -> iterator
{
  return end_;
}


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
auto trie<Key,T>::insert(key_type const& key, value_type const& value) -> value_type&
{
  node_type * cur = &root_;
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



#endif // #ifndef MRR_TRIE_HXX_
