
#ifndef BINARYTREEVEC_HPP
#define BINARYTREEVEC_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeVec : virtual public BinaryTree<Data> { // Should extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;
  ulong treeHeight = 0;

public:

  using BinaryTree<Data>::Node;

  struct NodeVec : public BinaryTree<Data>::Node { // Should extend Node

  private:

    // ...

  protected:

    ulong index;
    ulong height;

    ulong left;
    ulong right;

    bool valid = false;

    using BinaryTree<Data>::Node::value;
    using BinaryTree<Data>::Node::Node;

  public:

    friend class BinaryTreeVec<Data>;

    /* ********************************************************************** */

    // Specific member functions
    bool HasParent() const noexcept;
    bool HasLeftSibling() const noexcept;
    bool HasRightSibling() const noexcept;

    struct NodeVec& Parent() const; // (might throw std::out_of_range)
    struct NodeVec& LeftSibling() const; // (might throw std::out_of_range)
    struct NodeVec& RightSibling() const; // (might throw std::out_of_range)

    /* ********************************************************************** */

    // Specific member functions (inherited from Node)
    Data& Element() override; // Override Node member Mutable access to the element
    const Data& Element() const override; // Override Node member Immutable access to the element

    bool IsLeaf() const noexcept override; // Override Node member
    bool HasLeftChild() const noexcept override; // Override Node member
    bool HasRightChild() const noexcept override; // Override Node member

    struct NodeVec& LeftChild() const override; // Override Node member (might throw std::out_of_range)
    struct NodeVec& RightChild() const override; // Override Node member (might throw std::out_of_range)

  };

protected:

  Vector<struct NodeVec> *treeVec = nullptr;

  /* ************************************************************************ */

public:

  // Default constructor
  BinaryTreeVec() = default;

  // Specific constructors
  BinaryTreeVec(const Data&); // Construct a tree with a given root data (Copy of the value)
  BinaryTreeVec(Data&&) noexcept; // Construct a tree with a given root data (Move of the value)

  // Copy constructor
  BinaryTreeVec(const BinaryTreeVec<Data>&);

  // Move constructor
  BinaryTreeVec(BinaryTreeVec<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeVec();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeVec& operator=(const BinaryTreeVec<Data>&);

  // Move assignment
  BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // bool operator==(const BinaryTreeVec&) const noexcept;
  // bool operator!=(const BinaryTreeVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  struct NodeVec& Root() const override; // Override Node member (might throw std::length_error)
  void NewRoot(const Data&) override; // Override Node member (Copy of the value)
  void NewRoot(Data&&) override; // Override Node member (Move of the value)

  void AddLeftChild(struct NodeVec&, Data&); // Add a child to a given node (Copy of the value)
  void AddLeftChild(struct NodeVec&, Data&&); // Add a child to a given node (Move of the value)
  void AddRightChild(struct NodeVec&, Data&); // Add a child to a given node (Copy of the value)
  void AddRightChild(struct NodeVec&, Data&&); // Add a child to a given node (Move of the value)

  void RemoveLeftChild(struct NodeVec&); // Remove an entire subtree rooted in a child of a given node
  void RemoveRightChild(struct NodeVec&); // Remove an entire subtree rooted in a child of a given node

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  void Clear() override; // Override Container member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthSearchableContainer)
  using typename BinaryTree<Data>::MapFunctor;
  void MapBreadth(MapFunctor, void*) override; // Override BreadthSearchableContainer member

  using typename BinaryTree<Data>::FoldFunctor;
  void FoldBreadth(FoldFunctor, const void*, void*) const override; // Override BreadthSearchableContainer member

protected:

  // Accessory functions
  void Expand();
  void Reduce();

};

/* ************************************************************************** */

#include "binarytreevec.cpp"

}

#endif
