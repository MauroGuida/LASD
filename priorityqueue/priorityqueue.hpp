
#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP

/* ************************************************************************** */

#include "../heap/heap.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class PriorityQueue : virtual public Heap<Data> {

private:

  // ...

protected:

  using Heap<Data>::size;
  using Heap<Data>::treeVec;

  using Heap<Data>::heightVector;
  using Heap<Data>::treeHeight;

  using Heap<Data>::NodeVec;

public:

  // Default constructor
  PriorityQueue();

  // Specific constructor
  PriorityQueue(const LinearContainer<Data>&); // Construct a priority queue from a LinearContainer

  // Copy constructor
  PriorityQueue(const PriorityQueue<Data>&);

  // Move constructor
  PriorityQueue(PriorityQueue<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~PriorityQueue() = default;

  /* ************************************************************************ */

  // Copy assignment
  PriorityQueue& operator=(const PriorityQueue&);

  // Move assignment
  PriorityQueue& operator=(PriorityQueue&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const PriorityQueue<Data>&) const noexcept;
  bool operator!=(const PriorityQueue<Data>&) const noexcept;
  using BinaryTree<Data>::operator==;
  using BinaryTree<Data>::operator!=;

  /* ************************************************************************ */

  // Specific member functions

  using Heap<Data>::Root;

  const Data& Tip() const; // (might throw std::length_error)
  void RemoveTip(); // (might throw std::length_error)
  Data TipNRemove(); // (might throw std::length_error)
  void Insert(const Data&); // Copy of the value
  void Insert(Data&&); // Move of the value

  void ChangePriority(struct BinaryTreeVec<Data>::NodeVec&, const Data&); // Change priority of a Node (Copy of the value)
  void ChangePriority(struct BinaryTreeVec<Data>::NodeVec&, Data&&); // Change priority of a Node (Move of the value)

};

/* ************************************************************************** */

#include "priorityqueue.cpp"

}

#endif
