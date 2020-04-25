
#ifndef VECTOR_HPP
#define VECTOR_HPP

/* ************************************************************************** */

#include <iostream>
#include "../container/container.hpp"

/* ************************************************************************** */

namespace lasd {

/* ************************************************************************** */

  template <typename Data>
  class Vector : public LinearContainer<Data>, public SearchableContainer<Data> { // Should extend LinearContainer<Data> and SearchableContainer<Data>

  private:

  protected:

    using LinearContainer<Data>::size;

    Data* Elements = nullptr;

  public:

    // Default constructor
    Vector() = default;

    // Specific constructor
    Vector(const ulong); // A vector with an initial given dimension.

    // Copy constructor
    Vector(const Vector&);

    // Move constructor
    Vector(Vector&&) noexcept;

    /* ************************************************************************ */

    // Destructor
    ~Vector();

    /* ************************************************************************ */

    // Copy assignment
    Vector& operator=(const Vector&);

    // Move assignment
    Vector& operator=(Vector&&);

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const Vector&) const noexcept;
    bool operator!=(const Vector&) const noexcept;

    /* ************************************************************************ */

    // Specific member functions
    virtual void Resize(const ulong); // Resize the vector

    /* ************************************************************************ */

    // Specific member functions (inherited from Container)
    void Clear() override; // Override Container member

    /* ************************************************************************ */

    // Specific member functions (inherited from LinearContainer)
    Data& Front() const override; // Override LinearContainer member
    Data& Back() const override; // Override LinearContainer member

    Data& operator[](const ulong) const override; // Override LinearContainer member

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

  #include "vector.cpp"

}

#endif
