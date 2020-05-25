
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

  // using BST<Data>::???;

  // ...

public:

  struct RBNode { // Should extend BSTNode

    // ...

  };

  /* ************************************************************************ */

  // Default constructor
  // RB() specifiers;

  // Copy constructor
  // RB(argument) specifiers;

  // Move constructor
  // RB(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~RB() specifiers;

  /* ************************************************************************ */

  // Copy assignment
  // type operator=(argument) specifiers;

  // Move assignment
  // type operator=(argument) specifiers;

  /* ************************************************************************ */

  // Comparison operators
  // type operator==(argument) specifiers;
  // type operator!=(argument) specifiers;

  /* ************************************************************************ */

  // Specific member functions (inherited from BinaryTree)

  // type Root() specifiers; // Override BinaryTree member (might throw std::length_error)
  // type NewRoot(argument) specifiers; // Override BinaryTree member (Copy of the value)
  // type NewRoot(argument) specifiers; // Override BinaryTree member (Move of the value)

  /* ************************************************************************ */

  // Specific member functions

  // type Insert(argument) specifiers;
  // type Insert(argument) specifiers;
  // type Remove(argument) specifiers;

  // type MinNRemove() specifiers;
  // type RemoveMin() specifiers;

  // type MaxNRemove() specifiers;
  // type RemoveMax() specifiers;

  // type PredecessorNRemove(argument) specifiers;
  // type RemovePredecessor(argument) specifiers;

  // type SuccessorNRemove(argument) specifiers;
  // type RemoveSuccessor(argument) specifiers;

  /* ************************************************************************ */

};

}

/* ************************************************************************** */

#include "rb.cpp"

/* ************************************************************************** */

#endif
