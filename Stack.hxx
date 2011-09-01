#ifndef MRR_STACK_HXX__
#define MRR_STACK_HXX__

//===========================================================================
// Author: Matt Renaud
// The following is an implementation of a simple stack.
//---------------------------------------------------------------------------

#include <iostream>

//===========================================================================
// StackNode Class.
//---------------------------------------------------------------------------
template <class T>
class StackNode
{
public:
  typedef T value_type;
  typedef StackNode<value_type> Node;

  value_type datum_;
  Node * next_;

  StackNode() : datum_(value_type()), next_(nullptr) { }
  StackNode(value_type const& val) : datum_(val), next_(nullptr) { }
  StackNode(Node const& n) : datum_(n.datum_), next_(n.next_) { }
};

template <class T>
class Stack
{

  typedef T value_type;
  typedef StackNode<T> Node;

  Node * head_;

public:

  Stack() : head_(nullptr) { }
  Stack(Stack<T> const& s);

  bool empty();
  Node * push(T val);
  value_type pop();
};


//===========================================================================
template <class T>
Stack<T>::Stack(Stack<T> const& s)
{
  head_ = new Node(s.head_->datum_);
  Node * n = head_;
  Node * cur = s.head_->next_;

  while(cur != nullptr)
  {
    n->next_ = new Node(cur->datum_);
    cur = cur->next_;
    n = n->next_;
  }
}


//===========================================================================
template <class T>
bool Stack<T>::empty()
{
  return head_ == nullptr;
}


//===========================================================================
template <class T>
auto Stack<T>::push(value_type val) -> Node *
{
  Node * n = new Node(val);
  n->next_ = head_;
  head_ = n;
  return head_;
}


//===========================================================================
template <class T>
auto Stack<T>::pop() -> value_type
{
  if(head_ == nullptr)
  {
    std::cout << "error: No elements on stack. Exiting now." << std::endl;
    exit(1);
  }
  value_type val = head_->datum_;
  Node * oldHead = head_;
  head_ = head_->next_;
  delete oldHead;
  return val;
}


#endif // #ifndef MRR_STACK_HXX__
