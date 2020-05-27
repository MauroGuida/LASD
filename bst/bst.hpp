#include <iostream> //ANCORA UNA VOLTA SERVE, MA NON NE CAPISCO IL MOTIVO

#ifndef BST_HPP
#define BST_HPP

/* ************************************************************************** */

#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../queue/lst/queuelst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class BST : virtual protected BinaryTreeLnk<Data> {

private:

  // ...

protected:

  using BinaryTreeLnk<Data>::size;
  using BinaryTreeLnk<Data>::root;

public:

  struct BSTNode : public BinaryTreeLnk<Data>::NodeLnk { // Should extend NodeLnk

  private:

    // ...

  protected:

    using BinaryTreeLnk<Data>::NodeLnk::left;
    using BinaryTreeLnk<Data>::NodeLnk::right;

    struct BSTNode* Left();
    const struct BSTNode* Left() const;
    struct BSTNode* Right();
    const struct BSTNode* Right() const;

    struct BSTNode* Find(struct BSTNode* root, const Data&) const;
    struct BSTNode* FindParent(struct BSTNode* node, const Data&) const;

    struct BSTNode* MinParent() const;
    struct BSTNode* MaxParent() const;

    struct BSTNode* PredecessorParent(const Data&) const;
    struct BSTNode* SuccessorParent(const Data&) const;

  public:

    using BinaryTreeLnk<Data>::NodeLnk::NodeLnk;
    friend class BST<Data>;

  };

  /* ************************************************************************ */

  // Default constructor
  BST() = default;

  // Copy constructor
  BST(const Data&);

  // Move constructor
  BST(Data&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~BST() = default;

  /* ************************************************************************ */

  // Copy assignment
  BST& operator=(const BST<Data>&);

  // Move assignment
  BST& operator=(BST<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BST<Data>&) const noexcept;
  bool operator!=(const BST<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  struct BSTNode& Root() const override; // Override BinaryTree member (might throw std::length_error)
  void NewRoot(const Data&) override; // Override BinaryTree member (Copy of the value)
  void NewRoot(Data&&) override; // Override BinaryTree member (Move of the value)

  /* ************************************************************************ */

  // Specific member functions
  void Insert(const Data&);
  void Insert(Data&&);

  void Remove(const Data&);

  struct BSTNode& Min() const;
  Data MinNRemove();
  void RemoveMin();

  struct BSTNode& Max() const;
  Data MaxNRemove();
  void RemoveMax();

  struct BSTNode& Predecessor(const Data&) const;
  Data PredecessorNRemove(const Data&);
  void RemovePredecessor(const Data&);

  struct BSTNode& Successor(const Data&) const;
  Data SuccessorNRemove(const Data&);
  void RemoveSuccessor(const Data&);

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

protected:

  void Remove(const struct BSTNode&);
  // void RemoveMin();
  // void RemoveMax();
  void SkipOnLeft(const struct BSTNode*);
  void SkipOnRight(const struct BSTNode*);

  /* ************************************************************************ */

  QueueLst<Data>& enqueueTreeInOrder();
    void mapEnqueueTree(Data&, void*);

  struct BSTNode* InsertNode(struct BSTNode*, const Data&);
  struct BSTNode* InsertNode(struct BSTNode*, Data&&);

  bool Search(struct BSTNode*, const Data&) const noexcept;
};

}

/* ************************************************************************** */

#include "bst.cpp"

/* ************************************************************************** */

#endif
