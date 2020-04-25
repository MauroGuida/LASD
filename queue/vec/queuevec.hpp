
#ifndef QUEUEVEC_HPP
#define QUEUEVEC_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../vector/vector.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueVec : public Queue<Data>, protected Vector<Data> { // Should extend Queue<Data> and Vector<Data>

private:
  ulong head = 0;
  ulong tail = 0;
  ulong lenght = 0;

protected:
  using Vector<Data>::size;
  using Vector<Data>::Elements;

public:

  // Default constructor
  QueueVec();

  // Copy constructor
  QueueVec(const QueueVec&);

  // Move constructor
  QueueVec(QueueVec&&);

  /* ************************************************************************ */

  // Destructor
  ~QueueVec();

  /* ************************************************************************ */

  // Copy assignment
  QueueVec& operator=(const QueueVec&);

  // Move assignment
  QueueVec& operator=(QueueVec&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueVec&) const noexcept;
  bool operator!=(const QueueVec&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)
  Data& Head() const override; // Override Queue member (might throw std::length_error)
  void Dequeue() override; // Override Queue member (might throw std::length_error)
  Data HeadNDequeue() override; // Override Queue member (might throw std::length_error)
  void Enqueue(const Data&) override; // Override Queue member
  void Enqueue(Data&&) override; // Override Queue member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  bool Empty() const noexcept override; // Override Container member
  ulong Size() const noexcept override; // Override Container member
  void Clear() override; // Override Container member

protected:

  void Resize(const ulong) override; // Override Vector member
  void Expand(); // Accessory function
  void Reduce(); // Accessory function

};

/* ************************************************************************** */

#include "queuevec.cpp"

}

#endif
