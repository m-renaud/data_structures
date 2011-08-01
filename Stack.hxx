#ifndef __MRR_STACK_HXX__
#define __MRR_STACK_HXX__

#include <iostream>

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
class Stack
{
  Node<T> * head_;

public:

  Stack() : head_(nullptr) { }

  Stack(Stack<T> const& s)
  {
    head_ = new Node<T>(s.head_->datum_);
    Node<T> * n = head_;
    Node<T> * cur = s.head_->next_;

    while(cur != nullptr)
    {
      n->next_ = new Node<T>(cur->datum_);
      cur = cur->next_;
      n = n->next_;
    }
  }

  bool empty()
  {
    return head_ == nullptr;
  }

  Node<T> * push(T val)
  {
    Node<T> * n = new Node<T>(val);
    n->next_ = head_;
    head_ = n;
    return head_;
  }

  T pop()
  {
    if(head_ == nullptr)
    {
      std::cout << "error: No elements on stack. Exiting now." << std::endl;
      exit(1);
    }
    T val = head_->datum_;
    Node<T> * oldHead = head_;
    head_ = head_->next_;
    delete oldHead;
    return val;
  }
};

#endif // __MRR_STACK_HXX__
