
#ifndef STACKLST_HPP
#define STACKLST_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackLst : public Stack<Data>, protected List<Data> { // Should extend Stack<Data> and List<Data>

private:

protected:
  // using List<Data>::size;

public:

  // Default constructor
  StackLst() = default;

  // Copy constructor
  StackLst(const StackLst&);

  // Move constructor
  StackLst(StackLst&&);

  /* ************************************************************************ */

  // Destructor
  ~StackLst();

  /* ************************************************************************ */

  // Copy assignment
  StackLst& operator=(const StackLst&);

  // Move assignment
  StackLst& operator=(StackLst&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackLst&) const noexcept;
  bool operator!=(const StackLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)
  Data& Top() const override; // Override Stack member (might throw std::length_error)
  void Pop() override; // Override Stack member (might throw std::length_error)
  Data TopNPop() override; // Override Stack member (might throw std::length_error)
  void Push(const Data&) override; // Override Stack member
  void Push(Data&&) override; // Override Stack member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  void Clear() override; // Override Container member

};

/* ************************************************************************** */

#include "stacklst.cpp"

}

#endif
