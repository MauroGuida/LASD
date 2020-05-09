
#ifndef BINARYTREELNK_HPP
#define BINARYTREELNK_HPP

/* ************************************************************************** */

#include "../binarytree.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BinaryTreeLnk : virtual public BinaryTree<Data> { // Should extend BinaryTree<Data>

private:

  // ...

protected:

  using BinaryTree<Data>::size;

public:

  using BinaryTree<Data>::Node;

  struct NodeLnk : public BinaryTree<Data>::Node { // Should extend Node

    private:

      // ...

    protected:

      struct NodeLnk* Left = nullptr;
      struct NodeLnk* Right = nullptr;

      using BinaryTree<Data>::Node::value;
      using BinaryTree<Data>::Node::Node;

    public:

      friend class BinaryTreeLnk<Data>;

      /* ********************************************************************** */

      // Specific member functions (inherited from Node)
      Data& Element() override; // Override Node member Mutable access to the element
      const Data& Element() const override; // Override Node member Immutable access to the element

      bool IsLeaf() const noexcept override; // Override Node member
      bool HasLeftChild() const noexcept override; // Override Node member
      bool HasRightChild() const noexcept override; // Override Node member

      struct NodeLnk& LeftChild() const override; // Override Node member (might throw std::out_of_range)
      struct NodeLnk& RightChild() const override; // Override Node member (might throw std::out_of_range)
      
  };

protected:

  struct NodeLnk* root = nullptr;

  /* ************************************************************************ */

public:

  // Default constructor
  BinaryTreeLnk() = default;

  // Specific constructors
  BinaryTreeLnk(const Data&); // Construct a tree with a given root data (Copy of the value)
  BinaryTreeLnk(Data&&) noexcept; // Construct a tree with a given root data (Move of the value)

  // Copy constructor
  BinaryTreeLnk(const BinaryTreeLnk<Data>&);

  // Move constructor
  BinaryTreeLnk(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BinaryTreeLnk();

  /* ************************************************************************ */

  // Copy assignment
  BinaryTreeLnk& operator=(const BinaryTreeLnk<Data>&);

  // Move assignment
  BinaryTreeLnk& operator=(BinaryTreeLnk<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // bool operator!=(const BinaryTree<Data>&) const noexcept override;
  // bool operator==(const BinaryTree<Data>&) const noexcept override;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  struct NodeLnk& Root() const override; // Override Node member (might throw std::length_error)
  void NewRoot(const Data&) override; // Override Node member (Copy of the value)
  void NewRoot(Data&&) override; // Override Node member (Move of the value)

  void AddLeftChild(struct NodeLnk&, const Data&); // Add a child to a given node (Copy of the value)
  void AddLeftChild(struct NodeLnk&, Data&&); // Add a child to a given node (Move of the value)
  void AddRightChild(struct NodeLnk&, const Data&); // Add a child to a given node (Copy of the value)
  void AddRightChild(struct NodeLnk&, Data&&); // Add a child to a given node (Move of the value)

  void RemoveLeftChild(struct NodeLnk&); // Remove an entire subtree rooted in a child of a given node
  void RemoveRightChild(struct NodeLnk&); // Remove an entire subtree rooted in a child of a given node

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  void Clear() override; // Override Container member

protected:

  void RemoveSubtree(struct NodeLnk*);
  struct NodeLnk* copySubtree(struct NodeLnk*);

};

/* ************************************************************************** */

#include "binarytreelnk.cpp"

}

#endif
