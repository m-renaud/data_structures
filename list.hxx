#ifndef __MRR_LIST_HXX__
#define __MRR_LIST_HXX__

#include <cstddef>

namespace mrr {
//===========================================================================
// List
// Forward class declarations.
//---------------------------------------------------------------------------

template <typename T> class list;


//===========================================================================
// list_node
//
// Represents a node in a linked list.
//---------------------------------------------------------------------------

template <typename T>
class list_node
{
  friend class list<T>;

  T datum_;
  list_node<T> * next_;
  list_node<T> * prev_;

  list_node();
  list_node(T const& val);
  list_node(list_node<T> const& n);
};


//===========================================================================
// list
//
// Represents a doubly-linked list container
//---------------------------------------------------------------------------

template <typename T>
class list
{

public:
  typedef T& reference;
  typedef T const& const_reference;

  typedef std::size_t size_type;

  typedef T value_type;
  typedef T* pointer;
  typedef T const* const_pointer;

  list();
  ~list();

  bool empty()       { return head_ == nullptr; }
  unsigned size()    { return size_;            }
  value_type front() { return head_->datum_;    }
  value_type back()  { return last_->datum_;    }

  void push_front(value_type val);
  value_type pop_front();
  void push_back(value_type val);
  value_type pop_back();
  void clear();
  void remove(value_type val);

private:
  list_node<T> * head_;
  list_node<T> * last_;
  unsigned size_;


};


//===========================================================================
// list_node<T> member functions.
//---------------------------------------------------------------------------

template <typename T>
list_node<T>::list_node()
  : datum_(T()), next_(nullptr), prev_(nullptr)
{
}

template <typename T>
list_node<T>::list_node(T const& val)
  : datum_(val), next_(nullptr), prev_(nullptr)
{
}

template <typename T>
list_node<T>::list_node(list_node<T> const& n)
  : datum_(n.datum_), next_(n.next_), prev_(n.prev_)
{
}

//===========================================================================
// list<T> member functions.
//---------------------------------------------------------------------------

template <typename T>
list<T>::list()
  : head_(nullptr), last_(nullptr), size_(0)
{
}

template <typename T>
inline list<T>::~list()
{
  clear();
}

template <typename T>
void list<T>::push_front(value_type val)
{
  list_node<T> * n = new list_node<T>(val);
  ++size_;

  if(head_ == nullptr)
  {
    head_ = n;
    last_ = n;
    return;
  }

  n->next_ = head_;
  head_->prev_ = n;
  head_ = n;
  return;
}

template <typename T>
T list<T>::pop_front()
{
  value_type val = head_->datum_;
  list_node<T> * old = head_;
  head_ = head_->next_;
  if(head_ != nullptr)
    head_->prev_ = nullptr;
  delete old;
  return val;
}

template <typename T>
void list<T>::push_back(T val)
{
  list_node<T> * n = new list_node<T>(val);
  ++size_;

  if(head_ == nullptr)
  {
    head_ = n;
    last_ = n;
    return;
  }

  n->prev_ = last_;
  last_->next_ = n;
  last_ = n;
  return;
}

template <typename T>
T list<T>::pop_back()
{
  value_type val = last_->datum_;
  list_node<T> * old = last_;
  last_ = last_->prev_;
  if(last_ != nullptr)
    last_->next_ = nullptr;
  delete old;
  return val;
}

template <typename T>
void list<T>::clear()
{
  list_node<T> *cur = head_;
  while(cur != nullptr)
  {
    list_node<T> *old = cur;
    cur = cur->next_;
    delete old;
  }

  head_ = nullptr;
  last_ = nullptr;
}

template <typename T>
void list<T>::remove(value_type val)
{
  list_node<T> ** cur = &head_;
  while(*cur != nullptr)
  {
    if((*cur)->datum_ == val)
    {
      list_node<T> * old = *cur;
      *cur = (*cur)->next_;
      delete old;
    }

    cur = &(*cur)->next_;
  }
}

} // namespace mrr
#endif
