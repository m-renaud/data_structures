#ifndef MRR_TRIE_HXX_
#define MRR_TRIE_HXX_

#include <map>
#include <iterator>
#include <utility>

//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace mrr {

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
class trie
{
private:
  class trie_node;
  class trie_iterator_base;
  class trie_iterator;

  using node_type = trie_node;
  using edge_type = typename node_type::edge_type;
  using edge_list_type = typename node_type::edge_list_type;
  using edge_list_iterator = typename edge_list_type::iterator;
  
public:
  using key_type = Key;
  using mapped_type = T;
  using value_type = std::pair<Key, T>;
  using iterator = trie_iterator;

private:
  node_type root_;
  iterator end_;

public:
  trie()
    : root_(), end_()
  {
  }
  
  iterator end() const { return end_; }
  auto insert(value_type const& x) -> std::pair<iterator, bool>;
  auto find(key_type const& key) -> iterator;

}; // class trie<Key,T>


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// mrr::trie<Key,T> member functions and inner classes
//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=


//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
auto trie<Key,T>::insert(value_type const& x) -> std::pair<iterator, bool>
{
  using std::begin;
  using std::end;
  
  node_type* cur = &root_;
  edge_list_iterator edge;

  auto key_end = end(x.first);

  // Go through each element in the key, creating a path in the tree
  for(auto i = begin(x.first); i != key_end; ++i)
  {
    edge = cur->edges_.find(*i);

    // If the current in the key doesn't exist, create it, if it does, follow 
    if(edge == end(cur->edges_))
    {
      auto newly_created = &(cur->edges_[*i]);
      newly_created->parent_ = cur;
      cur = newly_created;
    }
    else
    {
      cur = &(edge->second);
    }
  }


  // If the key already exists, ignore the insert attempt
  if(cur->final_state_ == true)
  {
    return std::make_pair(iterator(cur), false);
  }
  else
  {
  
    // Set the key and value value at the current node and set the state to final
    cur->value_.first = x.first;
    cur->value_.second = x.second;
    cur->final_state_ = true;

    // Return the value just inserted
    return std::make_pair(trie_iterator(cur), true);
  }

} // std::pair<iterator, bool> insert()



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
auto trie<Key,T>::find(key_type const& key) -> iterator
{
  using std::begin;
  using std::end;
  
  // Start at the root
  node_type* cur = &root_;

  // Loop through the key
  for(auto i = begin(key); i != end(key);++i)
  {
    // Follow the correct edge
    auto edge = cur->edges_.find(*i);

    // If the edge is not found, return end
    if(edge == end(cur->edges_))
      return end_;
    // If it is, move the pointer and continue
    else
      cur = &(edge->second);
  }

  // If the node we end up at is final, return a pointer to the value
  if(cur->final_state_ == true)
    return iterator(cur);
  // If not, return end
  else
    return end_;

} // iterator trie<Key,T>::find()



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
class trie<Key,T>::trie_node
{
  friend class trie<Key,T>;
  using edge_type = typename key_type::value_type;
  using edge_list_type = std::map<edge_type, node_type>;

  edge_list_type edges_;
  bool final_state_;

public:
  trie_node()
    : edges_(), final_state_(false), parent_(nullptr), value_(value_type())
  {
  }

  trie_node* parent_;
  value_type value_;

}; // class trie<Key,T>::trie_node



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
class trie<Key,T>::trie_iterator_base
  : std::iterator<std::forward_iterator_tag, value_type> 
{

  friend class trie<Key,T>;
  
public:
  bool operator ==(trie_iterator_base const& iter) const
  {
    return node_ == iter.node_;
  }

  bool operator !=(trie_iterator_base const& iter) const
  {
    return ! (*this == iter);
  }

protected:
  trie_iterator_base(trie_iterator_base const& iter)
    : node_(iter.node_)
  {
  }

  trie_iterator_base(node_type* node)
    : node_(node)
  {
  }

  node_type* node_;

private:
  trie_iterator_base()
    : node_(nullptr)
  {
  }
  
}; // class trie<Key,T>::trie_iterator_base



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
template <typename Key, typename T>
class trie<Key,T>::trie_iterator
  : public trie<Key,T>::trie_iterator_base
{

  friend class trie<Key,T>;
  
public:
  trie_iterator()
    : trie_iterator_base()
  {
  }
  
  trie_iterator& operator =(trie_iterator const& iter)
  {
    this->node_ = iter.node_;
    return *this;
  }

  value_type& operator*()  { return this->node_->value_; }
  value_type* operator->() { return &this->node_->value_; }

private:
  explicit trie_iterator(node_type* node)
    : trie_iterator_base(node)
  {
  }

}; // class trie<Key,T>::trie_iterator



template <typename Key, typename T>
inline auto end(trie<Key,T>& a) -> decltype(a.end())
{
  return a.end();
}



//m=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

} // namespace mrr

//=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#endif // #ifndef MRR_TRIE_HXX_
