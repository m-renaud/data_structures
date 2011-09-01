#ifndef MRR_LIST_HXX__
#define MRR_LIST_HXX__

//===========================================================================

namespace mrr {

//---------------------------------------------------------------------------

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

    typedef T value_type;
    typedef list_node<T> node_type;

    value_type datum_;
    node_type * next_;
    node_type * prev_;

    list_node();
    list_node(value_type const& val);
    list_node(node_type const& n);
  };


  //===========================================================================
  // list
  //
  // Represents a doubly-linked list container
  //---------------------------------------------------------------------------

  template <class T>
  class list
  {

  public:
    typedef T& reference;
    typedef T const& const_reference;

    typedef std::size_t size_type;

    typedef T value_type;
    typedef T* pointer;
    typedef T const* const_pointer;

    typedef list_node<T> node_type;

    list();
    ~list();

    bool empty()       { return head_ == nullptr; }
    unsigned size()    { return size_;            }
    value_type front() { return head_->datum_;    }
    value_type back()  { return last_->datum_;    }

    void push_front(value_type const& val);
    value_type pop_front();
    void push_back(value_type const& val);
    value_type pop_back();
    void clear();
    void remove(value_type const& val);

  private:
    node_type * head_;
    node_type * last_;
    size_type size_;

  };


  //===========================================================================
  // list_node<T> member functions.
  //---------------------------------------------------------------------------

  template <class T>
  list_node<T>::list_node()
  : datum_(value_type()), next_(nullptr), prev_(nullptr)
  {
  }

  template <class T>
  list_node<T>::list_node(value_type const& val)
  : datum_(val), next_(nullptr), prev_(nullptr)
  {
  }

  template <class T>
  list_node<T>::list_node(node_type const& n)
  : datum_(n.datum_), next_(n.next_), prev_(n.prev_)
  {
  }

  //===========================================================================
  // list<T> member functions.
  //---------------------------------------------------------------------------

  template <class T>
  list<T>::list()
  : head_(nullptr), last_(nullptr), size_(0)
  {
  }

  template <class T>
  inline list<T>::~list()
  {
    clear();
  }

  template <class T>
  void list<T>::push_front(value_type const& val)
  {
    node_type * n = new node_type(val);
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

  template <class T>
  auto list<T>::pop_front() -> value_type
  {
    value_type val = head_->datum_;
    node_type * old = head_;
    head_ = head_->next_;
    if(head_ != nullptr)
      head_->prev_ = nullptr;
    delete old;
    return val;
  }

  template <class T>
  void list<T>::push_back(value_type const& val)
  {
    node_type * n = new node_type(val);
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

  template <class T>
  auto list<T>::pop_back() -> value_type
  {
    value_type val = last_->datum_;
    node_type * old = last_;
    last_ = last_->prev_;
    if(last_ != nullptr)
      last_->next_ = nullptr;
    delete old;
    --size_;
    return val;
  }

  template <class T>
  void list<T>::clear()
  {
    node_type * cur = head_;
    while(cur != nullptr)
    {
      node_type * old = cur;
      cur = cur->next_;
      delete old;
    }

    head_ = nullptr;
    last_ = nullptr;
  }

  template <class T>
  void list<T>::remove(value_type const& val)
  {
    node_type ** cur = &head_;
    while(*cur != nullptr)
    {
      if((*cur)->datum_ == val)
      {
	node_type * old = *cur;
	*cur = (*cur)->next_;
	delete old;
      }

      cur = &(*cur)->next_;
    }
  }

//===========================================================================

} // namespace mrr

//---------------------------------------------------------------------------

#endif // #ifndef MRR_LIST_HXX__
