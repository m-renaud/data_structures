#ifndef MRR_LINKED_LIST_HXX__
#define MRR_LINKED_LIST_HXX__

template <typename T>
struct Node
{
  T datum_;
  Node<T> * next_;

  Node() : datum_(T()), next_(nullptr) { }

  Node(T const& val) : datum_(val), next_(nullptr) { }

  Node(Node<T> const& n) : datum_(n.datum_), next_(n.next_) { }

};

template <typename T>
std::ostream& operator << (std::ostream& os, Node<T> const& n)
{
  os << "(" << n.datum_ << "," << n.next_ << ")";

  return os;
}

template <typename T>
struct List
{
  Node<T> * head_;

  List() : head_(nullptr) { }

  void insert(T const&  val)
  {
    Node<T> * n = new Node<T>(val);

    Node<T> ** cur = &head_;

    while(*cur != nullptr)
      cur = &(*cur)->next_;

    *cur = n;
  }

  void insertOrdered(T const& val)
  {
    Node<T> * n = new Node<T>(val);

    Node<T> ** cur = &head_;

    while(*cur != nullptr && (*cur)->datum_ < val)
    {
      /* For learning.
      std::cout << "cur:  " << cur  << std::endl
		<< "*cur: " << *cur << std::endl
		<< "&(*cur)->next: " << &(*cur)->next_ << std::endl
		<< "(*cur)->next: " << (*cur)->next_ << std::endl;
      */
      cur = &(*cur)->next_;
    }

    n->next_ = *cur;
    *cur = n;
  }

  void remove(T const& val)
  {

    Node<T> ** cur = &head_;

    for(; *cur != nullptr && (*cur)->datum_ != val; cur = &(*cur)->next_)
      ;

    if(*cur != nullptr)
    {
      Node<T> * del = *cur;
      *cur = (*cur)->next_;
      delete del;
    }

  }

  bool member(T const& val)
  {
    for(
      Node<T> ** cur = &head_;
      *cur != nullptr;
      cur = &(*cur)->next_
    )
      if((*cur)->datum_ == val)
	return true;

    return false;
  }

  void dump()
  {
    for(
      Node<T> * cur = head_;
      cur != nullptr;
      cur = cur->next_
    )
      std::cout << cur << ": " << *cur << std::endl;
  }

};

#endif // #ifndef MRR_LINKED_LIST_HXX__
