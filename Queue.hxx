#ifndef __MRR_QUEUE_HXX__
#define __MRR_QUEUE_HXX__

template <typename T>
struct Node
{
  T datum_;
  Node<T> * next_;

  Node() : datum_(0), next_(nullptr) { }
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
    Node<T> n = head_;
    Node<T> * cur = q.head_->next_;
    while(cur != nullptr)
    {
      n->next_ = new Node<T>(cur->datum_);
      cur = cur->next_;
      n = n->next_;
    }
    last_ = n;
  }




};

#endif // __MRR_QUEUE_HXX__
