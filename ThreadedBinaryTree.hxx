#ifndef __MRR_THREADED_BINARY_TREE__
#define __MRR_THREADED_BINARY_TREE__

//===========================================================================
// Author: Matt Renaud
// The following is an implementation of a threaded binary tree.
//===========================================================================

#include <stdio.h>
#include <string.h>

//===========================================================================
// ThreadedBinaryTreeNode Class.
//===========================================================================
template <typename T>
class ThreadedBinaryTreeNode
{
public:
  T datum_;
  ThreadedBinaryTreeNode * left_;
  ThreadedBinaryTreeNode * right_;
  bool isSet_;
  bool isThreadedLeft;
  bool isThreadedRight;

  ThreadedBinaryTreeNode()
    : isSet_(false), left_(nullptr), right_(nullptr), isThreadedLeft(false),
      isThreadedRight(false), datum_(T())
  { }

  ThreadedBinaryTreeNode(T d)
    : isSet_(true), left_(nullptr), right_(nullptr), isThreadedLeft(false),
      isThreadedRight(false), datum_(d)
  { }
};


//===========================================================================
// ThreadedBinaryTree Class.
//===========================================================================
template <typename T>
class ThreadedBinaryTree
{
  typedef ThreadedBinaryTreeNode<T> Node;
  Node * root_;

public:
  ThreadedBinaryTree()
    : root_(new Node())
  { }

  void empty(Node * cur)
  {
    if(cur == nullptr)
      return;
    empty(cur->left_);
    empty(cur->right_);
    delete cur;
  }

  void empty()
  {
    empty(root_);
    root_ = new Node();
  }

  Node * inorderSuccessor(Node * n)
  {
    if(n == nullptr)
      return nullptr;
    Node * p = n->right_;
    if(p == nullptr)
    {
      return nullptr;
    }
    else if(!n->isThreadedLeft)
    {
      while(!p->isThreadedLeft && p->left_ != nullptr)
	p = p->left_;
    }

    return p;
  }

  Node * findInsertPosition(Node * node, Node * parent, T val)
  {
    if(node == nullptr)
      return parent;
    else if(val < node->datum_)
      return findInsertPosition(node->left_, node, val);
    else if(val > node->datum_)
      return findInsertPosition(node->right_, node, val);
    else
      return nullptr;
  }

  Node * threadedInsert(T val)
  {
    if(!root_->isSet_)
    {
      root_ = new Node(val);
      return root_;
    }

    Node * pos = findInsertPosition(root_, nullptr, val);

    if(pos == nullptr)
      return nullptr;
    else
    {
      Node * n = new Node(val);
      return threadedInsert(pos, n);
    }

  }

  Node * threadedInsert(Node * P, Node * Q)
  {
    Node * pRightOld = P->right_;
    P->right_ = Q;
    Q->isThreadedLeft = true;
    Q->left_ = P;
    Q->right_ = pRightOld;
    if(!Q->isThreadedRight)
    {
      Node * succQ = inorderSuccessor(Q);
      if(succQ != nullptr)
      {
	succQ->isThreadedLeft = true;
	succQ->left_ = Q;
      }
    }
    return Q;
  }

  Node * insert(Node * node, Node * parent, T val)
  {
    if(!root_->isSet_)
    {
      root_ = new Node(val);
      return root_;
    }
    if(node == nullptr)
    {
      Node * newnode = new Node(val);
      if(val < parent->datum_)
      {
	parent->left_ = newnode;
	return newnode;
      }
      else
      {
	parent->right_ = newnode;
	return newnode;
      }
    }
    else if(val < node->datum_)
      insert(node->left_, node, val);
    else
      insert(node->right_, node, val);

  } // insert()

  Node * insert(T val)
  {
    return insert(root_, nullptr, val);
  }

  bool isElement(Node * node, T val)
  {
    if(node == nullptr)
      return false;
    if(node->datum_ == val)
      return true;
    else if(val < node->datum_)
      return isElement(node->left_, val);
    else
      return isElement(node->right_, val);
  } // isElement()

  void threadedPrint(std::string s = "")
  {
    threadedPrint(root_, s);
  }

  void threadedPrint(Node * n, std::string s = "")
  {
    if(n == nullptr)
      return;

    while(n->left_ != nullptr)
      n = n->left_;

    while(n != nullptr)
    {
      std::cout << n->datum_ << " ";
      n = n->right_;
    }
  }

  void print(std::string s = "")
  {
    print(root_, s);
  }

  void print(Node * n, std::string s = "")
  {
    if(n == nullptr)
      return;
    print(n->left_, s + "l");
    std::cout << s << " - " << (n->datum_) << std::endl;
    print(n->right_, s + "r");
  } // print()

  T min()
  {
    Node * cur = root_;

    while(cur->left_ != nullptr)
      cur = cur->left_;

    return cur->datum_;
  }

  T max()
  {
    Node * cur = root_;

    while(cur->right_ != nullptr)
      cur = cur->right_;

    return cur->datum_;
  }

  unsigned depth(Node * cur)
  {

    if(cur == nullptr)
      return 0;

    return 1 + std::max(depth(cur->left_), depth(cur->right_));
  }

  unsigned depth()
  {
    return depth(root_);
  }


};


#endif // __MRR_THREADED_BINARY_TREE__
