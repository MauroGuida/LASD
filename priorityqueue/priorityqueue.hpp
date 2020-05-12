
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

  // using Heap<Data>::???;

  // ...

public:

  // Default constructor
  // PriorityQueue() specifiers;

  // Specific constructor
  // PriorityQueue(argument) specifiers; // Construct a priority queue from a LinearContainer

  // Copy constructor
  // PriorityQueue(argument) specifiers;

  // Move constructor
  // PriorityQueue(argument) specifiers;

  /* ************************************************************************ */

  // Destructor
  // ~PriorityQueue() specifiers;

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

  // Specific member functions

  // using Heap<Data>::???;

  // using Heap<Data>::Root;

  // type Tip() specifier; // (might throw std::length_error)
  // type RemoveTip() specifier; // (might throw std::length_error)
  // type TipNRemove() specifier; // (might throw std::length_error)
  // type Insert(argument) specifier; // Copy of the value
  // type Insert(argument) specifier; // Move of the value

  // type ChangePriority(arguments) specifier; // Change priority of a Node (Copy of the value)
  // type ChangePriority(arguments) specifier; // Change priority of a Node (Move of the value)

};

/* ************************************************************************** */

#include "priorityqueue.cpp"

}

#endif
