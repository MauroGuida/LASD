#include <iostream> // NON NE CAPISCO IL MOTIVO MA SERVE

#ifndef HEAP_HPP
#define HEAP_HPP

/* ************************************************************************** */

#include "../container/container.hpp"
#include "../binarytree/vec/binarytreevec.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Heap : virtual public SearchableContainer<Data>, protected BinaryTreeVec<Data>{ // Should extend SearchableContainer<Data> and BinaryTreeVec<Data>

private:

  // ...

protected:

  // using SearchableContainer<Data>::???;

  using BinaryTreeVec<Data>::size;

  using BinaryTreeVec<Data>::treeVec;
  using BinaryTreeVec<Data>::NodeVec;

  void BuildTree(const LinearContainer<Data>&);

  void BuildHeap();

  void Heapify(ulong, ulong);

public:

  // Default constructor
  Heap();

  // Specific constructor
  Heap(const LinearContainer<Data>&); // Construct a heap from a LinearContainer

  // Copy constructor
  Heap(const Heap<Data>&);

  // Move constructor
  Heap(Heap<Data>&&) noexcept;

  /* ************************************************************************ */

  // Destructor
  ~Heap() = default;

  /* ************************************************************************ */

  // Copy assignment
  Heap& operator=(const Heap<Data>&);

  // Move assignment
  Heap& operator=(Heap<Data>&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  // bool operator==(const Heap<Data>&) const noexcept;
  // bool operator!=(Heap<Data>&&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions
  void Sort() noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from SearchableContainer)
  using typename SearchableContainer<Data>::MapFunctor;
  void MapPreOrder(MapFunctor, void*) override; // Override SearchableContainer member
  void MapPostOrder(MapFunctor, void*) override; // Override SearchableContainer member

  using typename SearchableContainer<Data>::FoldFunctor;
  void FoldPreOrder(FoldFunctor, const void*, void*) const override; // Override SearchableContainer member
  void FoldPostOrder(FoldFunctor, const void*, void*) const override; // Override SearchableContainer member

};

/* ************************************************************************** */

#include "heap.cpp"

}

#endif
