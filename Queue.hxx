#ifndef MRR_QUEUE_HXX__
#define MRR_QUEUE_HXX__

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
class Queue
{
  Node<T> * head_;
  Node<T> * last_;

public:
  Queue() : head_(nullptr), last_(nullptr) { }

  Queue(Queue<T> const& q)
  {
    head_ = new Node<T>(q.head_->datum_);
    Node<T> * n = head_;
    Node<T> * cur = q.head_->next_;
    while(cur != nullptr)
    {
      n->next_ = new Node<T>(cur->datum_);
      cur = cur->next_;
      n = n->next_;
    }
    last_ = n;
  }

  bool empty()
  {
    return head_ == nullptr;
  }

  Node<T> * enqueue(T val)
  {
    Node<T> * n = new Node<T>(val);

    if(head_ == nullptr)
    {
      head_ = n;
      last_ = n;
    }

    last_->next_ = n;
    last_ = n;
  }

  T dequeue()
  {
    if(head_ == nullptr)
    {
      std::cout << "error: No elements in the queue. Exiting now." << std::endl;
      exit(1);
    }
    T val = head_->datum_;
    Node<T> * oldHead = head_;
    head_ = head_->next_;
    delete oldHead;
    return val;
  }

};

#endif // #ifndef MRR_QUEUE_HXX__
