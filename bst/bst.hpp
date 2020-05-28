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

    struct BSTNode* Left();
    const struct BSTNode* Left() const;
    struct BSTNode* Right();
    const struct BSTNode* Right() const;

  public:

    using BinaryTreeLnk<Data>::NodeLnk::NodeLnk;
    friend class BST<Data>;

  };

  /* ************************************************************************ */

  // Default constructor
  BST() = default;

  // Copy constructor
  BST(const BST&);

  // Move constructor
  BST(BST&&) noexcept;

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

  const Data& Min() const;
  Data MinNRemove();
  void RemoveMin();

  const Data& Max() const;
  Data MaxNRemove();
  void RemoveMax();

  const Data& Predecessor(const Data&) const;
  Data PredecessorNRemove(const Data&);
  void RemovePredecessor(const Data&);

  const Data& Successor(const Data&) const;
  Data SuccessorNRemove(const Data&);
  void RemoveSuccessor(const Data&);

  /* ************************************************************************ */

  // Specific member functions (inherited from TestableContainer)
  bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  using BinaryTreeLnk<Data>::MapBreadth;
  using BinaryTreeLnk<Data>::FoldBreadth;

  using BinaryTreeLnk<Data>::MapInOrder;
  using BinaryTreeLnk<Data>::MapPreOrder;
  using BinaryTreeLnk<Data>::MapPostOrder;

  using BinaryTreeLnk<Data>::FoldInOrder;
  using BinaryTreeLnk<Data>::FoldPreOrder;
  using BinaryTreeLnk<Data>::FoldPostOrder;

protected:

  void Remove(struct BSTNode&);

  void SkipOnLeft(struct BSTNode*);
  void SkipOnRight(struct BSTNode*);

  /* ************************************************************************ */

  QueueLst<Data>* enqueueTreeInOrder() const;
    void InOrderEnqueueTree(QueueLst<Data>*, struct BSTNode*) const;

  struct BSTNode* Min(struct BSTNode*) const;
  struct BSTNode* Max(struct BSTNode*) const;

  struct BSTNode* Predecessor(struct BSTNode*, const Data&) const;
    struct BSTNode* Predecessor_IT(struct BSTNode*, const Data&, struct BSTNode*) const noexcept;
  struct BSTNode* Successor(struct BSTNode*, const Data&) const;
    struct BSTNode* Successor_IT(struct BSTNode*, const Data&, struct BSTNode*) const noexcept;

  struct BSTNode* InsertNode(struct BSTNode*, const Data&);
  struct BSTNode* InsertNode(struct BSTNode*, Data&&);

  struct BSTNode* Search(struct BSTNode*, const Data&) const noexcept;
  struct BSTNode* SearchParent(struct BSTNode*, const Data&) const noexcept;

};

}

/* ************************************************************************** */

#include "bst.cpp"

/* ************************************************************************** */

#endif
