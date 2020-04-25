
#ifndef STACKVEC_HPP
#define STACKVEC_HPP

/* ************************************************************************** */

#include "../stack.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class StackVec : public Stack<Data>, protected Vector<Data> { // Should extend Stack<Data> and Vector<Data>

private:
  ulong index = 0;
  
protected:
  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  StackVec();

  // Copy constructor
  StackVec(const StackVec&);

  // Move constructor
  StackVec(StackVec&&);

  /* ************************************************************************ */

  // Destructor
  ~StackVec();

  /* ************************************************************************ */

  // Copy assignment
  StackVec& operator=(const StackVec&);

  // Move assignment
  StackVec& operator=(StackVec&&) noexcept;

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const StackVec&) const noexcept;
  bool operator!=(const StackVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Stack)
  Data& Top() const override; // Override Stack member (might throw std::length_error)
  void Pop() override; // Override Stack member (might throw std::length_error)
  Data TopNPop() override; // Override Stack member (might throw std::length_error)
  void Push(const Data&) override; // Override Stack member
  void Push(Data&&) override; // Override Stack member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  bool Empty() const noexcept override; // Override Container member
  ulong Size() const noexcept override; // Override Container member
  void Clear() override; // Override Container member

protected:

  void Expand(); // Accessory function
  void Reduce(); // Accessory function

};

/* ************************************************************************** */

#include "stackvec.cpp"

}

#endif
