
#ifndef RB_HPP
#define RB_HPP

/* ************************************************************************** */

#include "../bst.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class RB : virtual public BST<Data> {

private:

  // ...

protected:

  using BST<Data>::size;
  using BST<Data>::root;
  enum Color {black, red, dblack};

public:

  struct RBNode : public BST<Data>::BSTNode { // Should extend BSTNode

  protected:

    Color color = red;

    struct RBNode* Left();
    const struct RBNode* Left() const;
    struct RBNode* Right();
    const struct RBNode* Right() const;

  public:

    using BST<Data>::BSTNode::BSTNode;
    friend class RB<Data>;

  };

  /* ************************************************************************ */

  // Default constructor
  RB() = default;

  // Copy constructor
  RB(const RB&);

  // Move constructor
  RB(RB&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~RB() = default;

  /* ************************************************************************ */

  // Copy assignment
  RB& operator=(const RB<Data>&);

  // Move assignment
  RB& operator=(RB<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // bool operator==(const RB<Data>&) const noexcept;
  // bool operator!=(const RB<Data>&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)
  struct RBNode& Root() const override; // Override BinaryTree member (might throw std::length_error)
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

  // DA RIMUOVERE!
  // void stampaInOrder(struct RBNode* node){
  //   if(node == nullptr)
  //     return;
  //
  //   stampaInOrder(node->Left());
  //   std::cout << "Value: " << node->Element() << " Color: " << node->color << std::endl;
  //   stampaInOrder(node->Right());
  // }
  //
  // void printRB(){
  //       printRB("", static_cast<struct RBNode*>(root),false);
  //   }
  //
  // void printRB(const std::string& prefix,struct RBNode* root, bool isLeft){
  //   if(root != nullptr){
  //     std::cout << prefix;
  //     std::cout << (isLeft ? "├──" : "└──" );
  //     std::cout << root->Element() << (root->color == Color::black ? "(B)" : "(R)") << std::endl;
  //
  //     printRB( prefix + (isLeft ? "│   " : "    "), root->Left(), true);
  //     printRB( prefix + (isLeft ? "│   " : "    "), root->Right(), false);
  //   }
  // }

private:

  // Insert
  struct RBNode* InsertNode(struct RBNode*, const Data&);
  struct RBNode* InsertNode(struct RBNode*, Data&&);

  int ViolationTypeL(struct RBNode*, struct RBNode*);
  int ViolationTypeR(struct RBNode*, struct RBNode*);

  struct RBNode* BalanceL(struct RBNode*);
    struct RBNode* BalanceL_1(struct RBNode*);
    struct RBNode* BalanceL_2(struct RBNode*);
    struct RBNode* BalanceL_3(struct RBNode*);
  struct RBNode* BalanceR(struct RBNode*);
    struct RBNode* BalanceR_1(struct RBNode*);
    struct RBNode* BalanceR_2(struct RBNode*);
    struct RBNode* BalanceR_3(struct RBNode*);

  struct RBNode* RotationL(struct RBNode*);
  struct RBNode* RotationR(struct RBNode*);

  // Remove
  struct RBNode* Remove(struct RBNode*, const Data&);

  int removeViolationTypeL(struct RBNode*, struct RBNode*);
  int removeViolationTypeR(struct RBNode*, struct RBNode*);

  struct RBNode* removeBalanceL(struct RBNode*);
    struct RBNode* removeBalanceL_1(struct RBNode*);
    struct RBNode* removeBalanceL_2(struct RBNode*);
    struct RBNode* removeBalanceL_3(struct RBNode*);
    struct RBNode* removeBalanceL_4(struct RBNode*);
    struct RBNode* removeBalanceL_5(struct RBNode*);
  struct RBNode* removeBalanceR(struct RBNode*);
    struct RBNode* removeBalanceR_1(struct RBNode*);
    struct RBNode* removeBalanceR_2(struct RBNode*);
    struct RBNode* removeBalanceR_3(struct RBNode*);
    struct RBNode* removeBalanceR_4(struct RBNode*);
    struct RBNode* removeBalanceR_5(struct RBNode*);

  struct RBNode* removeRoot(struct RBNode*);

  struct RBNode* DetachMin(struct RBNode*, struct RBNode*);

  void propagateBlack(struct RBNode*);

  // Accessory
  struct RBNode* copySubtree(struct RBNode*);

};

}

/* ************************************************************************** */

#include "rb.cpp"

/* ************************************************************************** */

#endif
