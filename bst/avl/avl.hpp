
#ifndef AVL_HPP
#define AVL_HPP

/* ************************************************************************** */

#include "../bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class AVL : virtual public BST<Data> {

private:

  // ...

protected:

  using BST<Data>::size;
  using BST<Data>::root;

public:

  struct AVLNode : public BST<Data>::BSTNode {

  protected:

    struct AVLNode* Left();
    const struct AVLNode* Left() const;
    struct AVLNode* Right();
    const struct AVLNode* Right() const;

    long heightST = 0;

  public:

    using BST<Data>::BSTNode::BSTNode;
    friend class AVL<Data>;

  };

  /* ************************************************************************ */

  // Default constructor
  AVL() = default;

  // Copy constructor
  AVL(const AVL<Data>&);

  // Move constructor
  AVL(AVL<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~AVL() = default;

  /* ************************************************************************ */

  // Copy assignment
  AVL<Data>& operator=(const AVL<Data>&);

  // Move assignment
  AVL<Data>& operator=(AVL<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators // inherited from BST
  // bool operator==(const AVL<Data>&) const noexcept;
  // bool operator!=(const AVL<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  struct AVLNode& Root() const override; // Override BinaryTree member (might throw std::length_error)
  void NewRoot(const Data&) override; // Override BinaryTree member (Copy of the value)
  void NewRoot(Data&&) override; // Override BinaryTree member (Move of the value)

  /* ************************************************************************ */

  // Specific member functions
  void Insert(const Data&) override;
  void Insert(Data&&) override;

  void Remove(const Data&) override;

  Data MinNRemove() override;
  void RemoveMin() override;

  Data MaxNRemove() override;
  void RemoveMax() override;

  Data PredecessorNRemove(const Data&) override;
  void RemovePredecessor(const Data&) override;

  Data SuccessorNRemove(const Data&) override;
  void RemoveSuccessor(const Data&) override;

  /* ************************************************************************ */

private:

  struct AVLNode* DetachMin(struct AVLNode*, struct AVLNode*);

  struct AVLNode* Remove(struct AVLNode*, const Data&);

  struct AVLNode* InsertNode(struct AVLNode*, const Data&);
  struct AVLNode* InsertNode(struct AVLNode*, Data&&);

  struct AVLNode* BalanceL(struct AVLNode*);
  struct AVLNode* BalanceR(struct AVLNode*);

  struct AVLNode* RotationSL(struct AVLNode*);
  struct AVLNode* RotationSR(struct AVLNode*);

  struct AVLNode* RotationDL(struct AVLNode*);
  struct AVLNode* RotationDR(struct AVLNode*);

  bool isSL(struct AVLNode*) const noexcept;
  bool isSR(struct AVLNode*) const noexcept;

  long getHeightST(struct AVLNode*) const noexcept;
  long max(long, long);

  struct AVLNode* copySubtree(struct AVLNode*);

};

}

/* ************************************************************************** */

#include "avl.cpp"

/* ************************************************************************** */

#endif
