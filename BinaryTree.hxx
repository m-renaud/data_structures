#ifndef MRR_BINARY_TREE__
#define MRR_BINARY_TREE__

//===========================================================================
// Author: Matt Renaud
// The following is an implementation of a simple binary tree.
//---------------------------------------------------------------------------

#include <iostream>
#include <functional>
#include <string>

//===========================================================================
// BinaryTreeNode Class.
//---------------------------------------------------------------------------
template <class T>
class BinaryTreeNode
{
public:
  typedef T value_type;

  value_type datum_;
  BinaryTreeNode<value_type> * left_;
  BinaryTreeNode<value_type> * right_;
  bool isSet_;

  BinaryTreeNode()
    : isSet_(false), left_(nullptr), right_(nullptr)
  { }

  BinaryTreeNode(value_type d)
    : isSet_(true), left_(nullptr), right_(nullptr), datum_(d)
  { }
};


//===========================================================================
// BinaryTree Class.
//---------------------------------------------------------------------------
template <class T, class Comp = std::less<T> >
class BinaryTree
{
  typedef T value_type;
  typedef Comp compare_type;
  typedef BinaryTreeNode<value_type> Node;
  Node * root_;

public:
  BinaryTree() : root_(new Node()) { }

  bool empty();

  void clear();
  void clear(Node * cur);

  Node * insert(Node * node, Node * parent, value_type const& val);
  Node * insert(value_type const& val);

  bool isElement(Node * node, value_type const& val);

  void print(std::string s);
  void print(Node * n, std::string s);

  value_type min();
  value_type max();

  unsigned depth();
  unsigned depth(Node * cur);
};


//===========================================================================
template <class T, class C>
bool BinaryTree<T, C>::empty()
{
  return root_ == nullptr;
}


//===========================================================================
template <class T, class C>
void BinaryTree<T, C>::clear()
{
  clear(root_);
  root_ = new Node();
}


//===========================================================================
template <class T, class C>
void BinaryTree<T, C>::clear(Node * cur)
{
  if(cur == nullptr)
    return;
  clear(cur->left_);
  clear(cur->right_);
  delete cur;

}


//===========================================================================
template <class T, class C>
BinaryTreeNode<T> * BinaryTree<T, C>::insert(value_type const&val)
{
  return insert(root_, nullptr, val);
}


//===========================================================================
template <class T, class C>
BinaryTreeNode<T> * BinaryTree<T, C>::insert(Node * node,
					     Node * parent,
					     value_type const& val)
{
  compare_type comp;

  if(!root_->isSet_)
  {
    root_ = new Node(val);
    return root_;
  }
  if(node == nullptr)
  {
    Node * newnode = new Node(val);
    if(comp(val,parent->datum_))
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
  else if(comp(val, node->datum_))
    insert(node->left_, node, val);
  else
    insert(node->right_, node, val);
}


//===========================================================================
template <class T, class C>
bool BinaryTree<T, C>::isElement(Node * node, value_type const& val)
{
  if(node == nullptr)
    return false;
  if(node->datum_ == val)
    return true;
  else if(comp(val, node->datum_))
    return isElement(node->left_, val);
  else
    return isElement(node->right_, val);
}

//===========================================================================
template <class T, class C>
void BinaryTree<T, C>::print(std::string s)
{
  print(root_, s);
}


//===========================================================================
template <class T, class C>
void BinaryTree<T, C>::print(Node * n, std::string s = "")
{
  if(n == NULL)
    return;
  print(n->left_, s + "l");
  std::cout << s << " - " << (n->datum_) << std::endl;
  print(n->right_, s + "r");
}


//===========================================================================
template <class T, class C>
T BinaryTree<T, C>::min()
{
  Node * cur = root_;

  while(cur->left_ != nullptr)
    cur = cur->left_;

  return cur->datum_;
}

//===========================================================================
template <class T, class C>
T BinaryTree<T, C>::max()
{
  Node * cur = root_;

  while(cur->right_ != nullptr)
    cur = cur->right_;

  return cur->datum_;
}


//===========================================================================
template <class T, class C>
unsigned BinaryTree<T, C>::depth(Node * cur)
{
  if(cur == nullptr)
    return 0;

  return 1 + std::max(depth(cur->left_), depth(cur->right_));
}


//===========================================================================
template <class T, class C>
unsigned BinaryTree<T, C>::depth()
{
  return depth(root_);
}

#endif // #ifndef MRR_BINARY_TREE__
