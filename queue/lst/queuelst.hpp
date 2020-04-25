
#ifndef QUEUELST_HPP
#define QUEUELST_HPP

/* ************************************************************************** */

#include "../queue.hpp"
#include "../../list/list.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

template <typename Data>
class QueueLst : public Queue<Data>, protected List<Data> { // Should extend Queue<Data> and List<Data>

private:

protected:
  // using List<Data>::size;

public:

  // Default constructor
  QueueLst() = default;

  // Copy constructor
  QueueLst(const QueueLst&);

  // Move constructor
  QueueLst(QueueLst&&);

  /* ************************************************************************ */

  // Destructor
  ~QueueLst();

  /* ************************************************************************ */

  // Copy assignment
  QueueLst& operator=(const QueueLst&);

  // Move assignment
  QueueLst& operator=(QueueLst&&);

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const QueueLst&) const noexcept;
  bool operator!=(const QueueLst&) const noexcept;

  /* ************************************************************************ */

  // Specific member functions (inherited from Queue)
  Data& Head() const override; // Override Queue member (might throw std::length_error)
  void Dequeue() override; // Override Queue member (might throw std::length_error)
  Data HeadNDequeue() override; // Override Queue member (might throw std::length_error)
  void Enqueue(const Data&) override; // Override Queue member
  void Enqueue(Data&&) override; // Override Queue member

  /* ************************************************************************ */

  // Specific member functions (inherited from Container)
  void Clear() override; // Override Container member

};

/* ************************************************************************** */

#include "queuelst.cpp"

}

#endif
