
#ifndef STACK_HPP
#define STACK_HPP

/* ************************************************************************** */

#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class Stack : virtual public Container { // Should extend Container

private:

protected:

public:

  // Destructor
  virtual ~Stack() = default;

  /* ************************************************************************ */

  // Copy assignment
  Stack& operator=(const Stack&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  Stack& operator=(Stack&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const Stack&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const Stack&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  virtual Data& Top() const = 0; // (might throw std::length_error)
  virtual void Pop() = 0; // (might throw std::length_error)
  virtual Data TopNPop() = 0; // (might throw std::length_error)
  virtual void Push(const Data&) = 0; // Copy of the value
  virtual void Push(Data&&) = 0; // Move of the value

};

/* ************************************************************************** */

}

#endif
