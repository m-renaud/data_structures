#ifndef __MRR_BINARY_TREE__
#define __MRR_BINARY_TREE__

#include <iostream>
#include <string>

//==================================================
// BinaryTreeNode Class.
template <typename T>
class BinaryTreeNode
{
public:
  T datum_;
  BinaryTreeNode * left_;
  BinaryTreeNode * right_;
  bool isSet_;

  BinaryTreeNode()
    : isSet_(false), left_(nullptr), right_(nullptr)
  { }

  BinaryTreeNode(T d)
    : isSet_(true), left_(nullptr), right_(nullptr), datum_(d)
  { }

};


//==================================================
// BinaryTree Class.
template <typename T>
class BinaryTree
{
  BinaryTreeNode<T> * root_;

public:

  BinaryTree()
    : root_(new BinaryTreeNode<T>())
  { }

  BinaryTreeNode<T> * insert(BinaryTreeNode<T> * node, BinaryTreeNode<T> * parent, T val)
  {
    if(!root_->isSet_)
    {
      root_ = new BinaryTreeNode<T>(val);
    }
    if(node == nullptr)
    {
      BinaryTreeNode<T> * newnode = new BinaryTreeNode<T>(val);
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

  BinaryTreeNode<T> * insert(T val)
  {
    return insert(root_, nullptr, val);
  }

  bool isElement(BinaryTreeNode<T> * node, T val)
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

  void print(BinaryTreeNode<T> * n, std::string s = "")
  {
    if(n == NULL)
      return;
    print(n->left_, s + "l");
    std::cout << s << " - " << (n->datum_) << std::endl;
    print(n->right_, s + "r");
  } // print()
};

//==================================================
// Main...
/*
int main()
{
  BinaryTree<int> tree;
  tree.insert(4);
  tree.insert(8);
  tree.insert(2);
  tree.insert(12);
  tree.insert(10);
  tree.insert(1);

  std::string c = "Tree 1 - ";
  tree.print(c);
  return 0;
}
*/

#endif //__MRR_BINARY_TREE__
