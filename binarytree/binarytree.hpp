
#ifndef BINARYTREE_HPP
#define BINARYTREE_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTree : virtual public BreadthSearchableContainer<Data> { // Should extend BreadthSearchableContainer<Data>

private:

  // ...

protected:

  using BreadthSearchableContainer<Data>::size;

public:

  struct Node {

    private:

      // ...

    protected:

      Data value;

      // Specific constructors
      Node(const Data&);
      Node(Data&&);

    public:

      friend class BinaryTree<Data>;

      /* ********************************************************************** */

      // Specific member functions
      virtual Data& Element() = 0; // Mutable access to the element
      virtual const Data& Element() const = 0; // Immutable access to the element

      virtual bool IsLeaf() const noexcept = 0;
      virtual bool HasLeftChild() const noexcept = 0;
      virtual bool HasRightChild() const noexcept = 0;

      virtual struct Node& LeftChild() const = 0; // (might throw std::out_of_range)
      virtual struct Node& RightChild() const = 0; // (might throw std::out_of_range)

      bool operator==(const Node&) const noexcept;
      bool operator!=(const Node&) const noexcept;

  };

public:

  /* ************************************************************************ */

  // Destructor
  virtual ~BinaryTree() = default;

  /* ************************************************************************ */

  // Copy assignment
  BinaryTree& operator=(const BinaryTree<Data>&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BinaryTree& operator=(BinaryTree<Data>&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  virtual bool operator==(const BinaryTree<Data>&) const noexcept; // Comparison of abstract binary tree is possible.
  virtual bool operator!=(const BinaryTree<Data>&) const noexcept; // Comparison of abstract binary tree is possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual struct Node& Root() const = 0; // (might throw std::length_error)
  virtual void NewRoot(const Data&) = 0; // Copy of the value
  virtual void NewRoot(Data&&) = 0; // Move of the value

  using typename SearchableContainer<Data>::MapFunctor;
  virtual void MapInOrder(MapFunctor, void*);

  using typename SearchableContainer<Data>::FoldFunctor;
  virtual void FoldInOrder(FoldFunctor, const void*, void*) const;

  /* ************************************************************************ */

  // Specific member functions (inherited from SearchableContainer)
  virtual void MapPreOrder(MapFunctor, void*) override; // Override SearchableContainer member
  virtual void MapPostOrder(MapFunctor, void*) override; // Override SearchableContainer member

  virtual void FoldPreOrder(FoldFunctor, const void*, void*) const override; // Override SearchableContainer member
  virtual void FoldPostOrder(FoldFunctor, const void*, void*) const override; // Override SearchableContainer member

  /* ************************************************************************ */

  // Specific member functions (inherited from BreadthSearchableContainer)
  virtual void MapBreadth(MapFunctor, void*) override; // Override BreadthSearchableContainer member

  virtual void FoldBreadth(FoldFunctor, const void*, void*) const override; // Override BreadthSearchableContainer member

protected:

  virtual void MapBreadth(MapFunctor, void*, struct Node&); // Accessory function executing from one node of the tree
  virtual void MapPreOrder(MapFunctor, void*, struct Node&); // Accessory function executing from one node of the tree
  virtual void MapInOrder(MapFunctor, void*, struct Node&); // Accessory function executing from one node of the tree
  virtual void MapPostOrder(MapFunctor, void*, struct Node&); // Accessory function executing from one node of the tree

  virtual void FoldBreadth(FoldFunctor, const void*, void*, struct Node&) const; // Accessory function executing from one node of the tree
  virtual void FoldPreOrder(FoldFunctor, const void*, void*, struct Node&) const; // Accessory function executing from one node of the tree
  virtual void FoldInOrder(FoldFunctor, const void*, void*, struct Node&) const; // Accessory function executing from one node of the tree
  virtual void FoldPostOrder(FoldFunctor, const void*, void*, struct Node&) const; // Accessory function executing from one node of the tree

  public: bool equals(const struct Node& T1, const struct Node& T2) const;
};

/* ************************************************************************** */

#include "binarytree.cpp"

}

#endif
