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
template <typename T>
class ThreadedBinaryTreeNode
{
public:
  T datum_;
  ThreadedBinaryTreeNode * left_;
  ThreadedBinaryTreeNode * right_;
  bool isSet_;
};


//===========================================================================
// ThreadedBinaryTree Class.
template <typename T>
class ThreadedBinaryTree
{
  ThreadedBinaryTree<T> * root_;
};



#endif // __MRR_THREADED_BINARY_TREE__
