#ifndef MRR_THREADED_BINARY_TREE__
#define MRR_THREADED_BINARY_TREE__

//===========================================================================
// Author: Matt Renaud
// The following is an implementation of a threaded binary tree.
//---------------------------------------------------------------------------

#include <stdio.h>
#include <string.h>

//===========================================================================
// ThreadedBinaryTreeNode Class.
//---------------------------------------------------------------------------
template <typename T>
class ThreadedBinaryTreeNode
{
public:

  typedef T value_type;
  typedef ThreadedBinaryTreeNode<T> node_type;

  value_type datum_;
  node_type * left_;
  node_type * right_;
  bool isSet_;
  bool isThreadedLeft;
  bool isThreadedRight;

  ThreadedBinaryTreeNode()
    : isSet_(false), left_(nullptr), right_(nullptr), isThreadedLeft(false),
      isThreadedRight(false), datum_(T())
  { }

  ThreadedBinaryTreeNode(value_type const& d)
    : isSet_(true), left_(nullptr), right_(nullptr), isThreadedLeft(false),
      isThreadedRight(false), datum_(d)
  { }
};


//===========================================================================
// ThreadedBinaryTree Class.
//---------------------------------------------------------------------------
template <typename T>
class ThreadedBinaryTree
{

  typedef T value_type;
  typedef ThreadedBinaryTreeNode<T> node_type;

  node_type * root_;

public:
  ThreadedBinaryTree()
    : root_(new node_type())
  { }

  void empty(node_type * cur)
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
    root_ = new node_type();
  }

  node_type * inorderSuccessor(node_type * n)
  {
    if(n == nullptr)
      return nullptr;
    node_type * p = n->right_;
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

  node_type * findInsertPosition(node_type * node
				 , node_type * parent
				 , value_type const& val)
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

  node_type * threadedInsert(value_type val)
  {
    if(!root_->isSet_)
    {
      root_ = new node_type(val);
      return root_;
    }

    node_type * pos = findInsertPosition(root_, nullptr, val);

    if(pos == nullptr)
      return nullptr;
    else
    {
      node_type * n = new node_type(val);
      return threadedInsert(pos, n);
    }

  }

  node_type * threadedInsert(node_type * P, node_type * Q)
  {
    node_type * pRightOld = P->right_;
    P->right_ = Q;
    Q->isThreadedLeft = true;
    Q->left_ = P;
    Q->right_ = pRightOld;
    if(!Q->isThreadedRight)
    {
      node_type * succQ = inorderSuccessor(Q);
      if(succQ != nullptr)
      {
	succQ->isThreadedLeft = true;
	succQ->left_ = Q;
      }
    }
    return Q;
  }

  node_type * insert(node_type * node, node_type * parent, value_type const& val)
  {
    if(!root_->isSet_)
    {
      root_ = new node_type(val);
      return root_;
    }
    if(node == nullptr)
    {
      node_type * newnode = new node_type(val);
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

  node_type * insert(value_type val)
  {
    return insert(root_, nullptr, val);
  }

  bool isElement(node_type * node, value_type val)
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

  void threadedPrint(node_type * n, std::string s = "")
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

  void print(node_type * n, std::string s = "")
  {
    if(n == nullptr)
      return;
    print(n->left_, s + "l");
    std::cout << s << " - " << (n->datum_) << std::endl;
    print(n->right_, s + "r");
  } // print()

  value_type min()
  {
    node_type * cur = root_;

    while(cur->left_ != nullptr)
      cur = cur->left_;

    return cur->datum_;
  }

  value_type max()
  {
    node_type * cur = root_;

    while(cur->right_ != nullptr)
      cur = cur->right_;

    return cur->datum_;
  }

  unsigned depth(node_type * cur)
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


#endif // #ifndef MRR_THREADED_BINARY_TREE__
