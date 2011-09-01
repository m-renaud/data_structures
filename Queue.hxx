#ifndef MRR_QUEUE_HXX__
#define MRR_QUEUE_HXX__

//===========================================================================
// Author: Matt Renaud
// The following is an implementation of a simple queue.
//---------------------------------------------------------------------------

#include <iostream>

//===========================================================================
// QueueNode Class.
//---------------------------------------------------------------------------
template <class T>
struct QueueNode
{
  typedef T value_type;
  typedef QueueNode<value_type> Node;

  value_type datum_;
  Node * next_;

  QueueNode() : datum_(value_type()), next_(nullptr) { }
  QueueNode(value_type const& val) : datum_(val), next_(nullptr) { }
  QueueNode(Node const& n) : datum_(n.datum_), next_(n.next_) { }

};


//===========================================================================
// Queue Class.
//---------------------------------------------------------------------------
template <class T>
class Queue
{
  typedef T value_type;
  typedef QueueNode<value_type> Node;

  Node * head_;
  Node * last_;

public:
  Queue() : head_(nullptr), last_(nullptr) { }
  Queue(Queue<value_type> const& q);

  bool empty();
  Node * enqueue(value_type const& val);
  value_type dequeue();
};


//===========================================================================
template <class T>
Queue<T>::Queue(Queue<value_type> const& q)
{
  head_ = new Node(q.head_->datum_);
  Node * n = head_;
  Node * cur = q.head_->next_;

  while(cur != nullptr)
  {
    n->next_ = new Node(cur->datum_);
    cur = cur->next_;
    n = n->next_;
  }

  last_ = n;
}


//===========================================================================
template <class T>
bool Queue<T>::empty()
{
  return head_ == nullptr;
}


//===========================================================================
template <class T>
auto Queue<T>::enqueue(value_type const& val) -> Node *
{
  Node * n = new Node(val);

  if(head_ == nullptr)
  {
    head_ = n;
    last_ = n;
  }

  last_->next_ = n;
  last_ = n;
}


//===========================================================================
template <class T>
auto Queue<T>::dequeue() -> value_type
{
  if(head_ == nullptr)
  {
    std::cout << "error: No elements in the queue. Exiting now." << std::endl;
    exit(1);
  }
  value_type val = head_->datum_;
  Node * oldHead = head_;
  head_ = head_->next_;
  delete oldHead;
  return val;
}

#endif // #ifndef MRR_QUEUE_HXX__
