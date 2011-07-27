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
  ThreadedBinaryTreeNode * tLeft_;
  ThreadedBinaryTreeNode * tRight_;
};


//===========================================================================
// ThreadedBinaryTree Class.
//===========================================================================
template <typename T>
class ThreadedBinaryTree
{
  ThreadedBinaryTree<T> * root_;

  public:
  BinaryTree()
    : root_(new ThreadedBinaryTreeNode<T>())
  { }

  ThreadedBinaryTreeNode<T> * insert(ThreadedBinaryTreeNode<T> * node,
				     ThreadedBinaryTreeNode<T> * parent, T val)
  {
    if(!root_->isSet_)
    {
      root_ = new ThreadedBinaryTreeNode<T>(val);
    }
    if(node == nullptr)
    {
      ThreadedBinaryTreeNode<T> * newnode = new ThreadedBinaryTreeNode<T>(val);
      if(val < parent->datum_)
	parent->left_ = newnode;
      else
	parent->right_ = newnode;
    }
    else if(val < node->datum_)
      insert(node->left_, node, val);
    else
      insert(node->right_, node, val);
  } // insert()

  ThreadedBinaryTreeNode<T> * insert(T val)
  {
    return insert(root_, nullptr, val);
  }

  bool isElement(ThreadedBinaryTreeNode<T> * node, T val)
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

  void print(std::string s = "")
  {
    print(root_, s);
  }

  void print(ThreadedBinaryTreeNode<T> * n, std::string s = "")
  {
    if(n == NULL)
      return;
    print(n->left_, s + "l");
    std::cout << s << " - " << (n->datum_) << std::endl;
    print(n->right_, s + "r");
  } // print()
};



#endif // __MRR_THREADED_BINARY_TREE__
