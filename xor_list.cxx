#include <iostream>

using namespace std;

//
// Start by creating a class that will represent an XOR-encoded
// pointer pair...
//
template <typename T>
union XORPtr
{
  XORPtr()
    : ptr_(0)
  {
  }

  XORPtr(T* p)
    : ptr_(p)
  {
  }

  XORPtr(XORPtr<T> const& p)
    : ptr_(p.ptr_)
  {
  }

  XORPtr<T>& operator = (XORPtr<T> const& p)
  {
    ptr_ = p.ptr_;
    return *this;
  }

  XORPtr<T>& operator ^= (XORPtr<T> const& b)
  {
    for (unsigned i=0; i<sizeof(XORPtr); ++i)
      byte_[i] ^= b.byte_[i];
    return *this;
  }

  XORPtr<T> operator ^ (XORPtr<T> const& b) const
  {
    XORPtr retval(*this);
    retval ^= b;
    return retval;
  }

  T* ptr_;
  char byte_[1];
};

//
// A convenience function to output a pointer...//

template <typename T>
ostream& operator <<(ostream& os, XORPtr<T> const& xp)
{
  os << xp.ptr_;
  return os;
}


// List node using at XOR pointer.
template <typename T>
struct Node
{
  T datum_;           // Whatever is being stored in the list!
  XORPtr<Node> ptr_;  // The prevptr ^ nextptr value.

  Node() : datum_(0), ptr_(nullptr) { }

  Node(T const& val) : datum_(val), ptr_(nullptr) { }

  Node(Node<T> const& n) : datum_(n.datum_), ptr_(n.ptr_) { }

};



// List class using the XOR node.
template <typename T>
struct xor_list
{
  node<T> * head_;
  node<T> * tail_;

  xor_list() : head_(nullptr), tail_(nullptr) { }

  void insert(T const& val)
  {
    Node<T> * n = new Node<T>(val);

    Node<T> ** cur = &head_;

    while(*cur != nullptr)
      cur = &(*cur)->next_;

    *cur = n;

  } // insert()

  void remove(T const& val)
  {
    for(Node<T> ** cur = &head_;
	*cur != nullptr && (*cur)->datum_ != val;
	cur = &(*cur)->next_)
      ;

    if(*cur != nullptr)
    {
      Node<T> * del = *cur;
      *cur = (*cur)->next;
      delete del;
    }

  } // remove()


};


int main()
{
  XORPtr<int> a((int*)0xA), b((int*)0xB), c((int*)0xC);

  cout
    << a << ", " << b << ", " << c << endl
    << "a ^ b: " << (a ^ b) << endl
    << "b ^ c: " << (b ^ c) << endl
    << "a ^ c: " << (a ^ c) << endl
    << "(a ^ b) ^ a: " << ((a ^ b) ^ a) << endl
    << "(a ^ b) ^ b: " << ((a ^ b) ^ b) << endl
  ;

  XORPtr<int> ab = a ^ b;
  cout << (ab ^ a) << endl;


  list<int> l;
  l.head_ = l.tail_ = new node<int>;

  //
  // "Easier..."
  //
  // no nodes...
  //   head_ = 0
  //   tail_ = 0
  //
  // one nodes...
  //   head_ = &NODE_1
  //   tail_ = &NODE_1
  //
  //   NODE_1.ptr_ = 0 ^ 0
  //     i.e., prev is NULL and next is NULL
  //     NOTE: 0 ^ 0 == 0
  //
  // two nodes...
  //   head_ = &NODE_1
  //   tail_ = &NODE_2
  //
  //   NODE_1.ptr_ = 0 ^ &NODE_2
  //     i.e., prev is NULL and next is &NODE_2
  //   NODE_2.ptr_ = &NODE_1 ^ 0
  //     i.e., prev is &NODE_1 and next is null
  //
  // three nodes...
  //   head_ = &NODE_1
  //   tail_ = &NODE_3
  //
  //   NODE_1.ptr_ = 0 ^ &NODE_2
  //     i.e., prev is NULL and next is &NODE_2
  //   NODE_2.ptr_ = &NODE_1 ^ &NODE_3
  //     i.e., prev is &NODE_1 and next is &NODE_3
  //   NODE_3.ptr_ = &NODE_2 ^ 0
  //     i.e., prev is &NODE_2 and next is NULL
  //
  // For 3-node => 4-node, to add a node NODE_NEW
  //   Let's add BEFORE NODE_2... i.e., NODE_1, NODE_NEW, NODE_2, NODE_3
  //
  //   NODE_NEW.ptr_ = &NODE_1 ^ &NODE_2
  //   Need to fix NODE_1 and NODE_2...
  //    NODE_1.ptr_ = NODE1.ptr_ ^ &NODE_2 ^ &NODE_NEW
  //      i.e.,
  //        remove NODE_2 from "next" of NODE_1
  //        add NODE_NEW as "next" of NODE_1
  //    NODE_2.ptr_ = NODE2.ptr_ ^ &NODE_1 ^ &NODE_NEW
  //      i.e.,
  //        remove NODE_1 from "prev" of NODE_2
  //        add NODE_NEW as "prev" of NODE_2
  //
  // Recall ^ is associative and commutative.
  //
  // To traverse:
  //
  //    1) Start from the begin() or end().
  //      i.e.,
  //        - your iterator will have these members:
  //          - node* curpos = head_ (or tail_)
  //          - ndoe* prevpos = 0
  //
  //    2) To go to the "next" node (either way):
  //      - node* newpos = curpos->ptr_ ^ prevpos
  //      - prevpos = curpos
  //      - curpos = newpos
  //
  //    3) You are done when curpos == 0. :-)
  //
}

