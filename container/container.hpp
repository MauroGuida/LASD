#ifndef ulong
#define ulong unsigned long
#endif

#ifndef CONTAINER_HPP
#define CONTAINER_HPP

// #include <functional>

namespace lasd {

/* ************************************************************************** */

  class Container {

  private:

  protected:

    ulong size = 0;

  public:

    // Destructor

    virtual ~Container() = default;

    /* ************************************************************************ */

    // Copy assignment
    Container& operator=(const Container&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    Container& operator=(Container&&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const Container&) const noexcept = delete; // Comparison of abstract types might not be possible.
    bool operator!=(const Container&) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions
    virtual inline bool Empty() const noexcept{ return (size == 0); }
    virtual inline ulong Size() const noexcept{ return size; }
    virtual void Clear() = 0;

  };

  /* ************************************************************************** */

  template <typename Data>
  class LinearContainer : virtual public Container {

  private:

  protected:

  public:

    // Destructor
    virtual ~LinearContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    LinearContainer& operator=(const LinearContainer&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    LinearContainer& operator=(LinearContainer&&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const LinearContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
    bool operator!=(const LinearContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions
    virtual Data& Front() const = 0; //Il dato può essere modificato ma il contenitore del dato no.
    virtual Data& Back() const = 0; //Il dato può essere modificato ma il contenitore del dato no.

    virtual Data& operator[](const ulong) const = 0;

  };

  /* ************************************************************************** */

  template <typename Data>
  class TestableContainer : virtual public Container {

  private:

  protected:

  public:

    // Destructor
    virtual ~TestableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    TestableContainer& operator=(const TestableContainer&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    TestableContainer& operator=(TestableContainer&&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const TestableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
    bool operator!=(const TestableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions
    virtual bool Exists(const Data&) const noexcept = 0;

  };

  /* ************************************************************************** */

  template <typename Data>
  class SearchableContainer : virtual public TestableContainer<Data> {

  private:

  protected:

  public:

    // Destructor
    virtual ~SearchableContainer() = default;

    /* ************************************************************************ */

    // Copy assignment
    SearchableContainer& operator=(const SearchableContainer&) = delete; // Copy assignment of abstract types should not be possible.

    // Move assignment
    SearchableContainer& operator=(SearchableContainer&&) = delete; // Move assignment of abstract types should not be possible.

    /* ************************************************************************ */

    // Comparison operators
    bool operator==(const SearchableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
    bool operator!=(const SearchableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

    /* ************************************************************************ */

    // Specific member functions
    typedef void (*MapFunctor)(Data&, void*);
    // typedef std::function<void(Data&, void*)> MapFunctor;
    virtual void MapPreOrder(MapFunctor, void*) = 0;
    virtual void MapPostOrder(MapFunctor, void*) = 0;

    typedef void (*FoldFunctor)(const Data&, const void*, void*);
    // typedef std::function<void(const Data&, const void*, void*) noexcept> FoldFunctor;
    virtual void FoldPreOrder(FoldFunctor, const void*, void*) const = 0;
    virtual void FoldPostOrder(FoldFunctor, const void*, void*) const = 0;

    virtual bool Exists(const Data&) const noexcept override; // Override TestableContainer member

  };

/* ************************************************************************** */

template <typename Data>
class BreadthSearchableContainer : virtual public SearchableContainer<Data> { // Should extend SearchableContainer<Data>

private:

protected:

public:

  // Destructor
  virtual ~BreadthSearchableContainer() = default;

  /* ************************************************************************ */

  // Copy assignment
  BreadthSearchableContainer& operator=(const BreadthSearchableContainer&) = delete; // Copy assignment of abstract types should not be possible.

  // Move assignment
  BreadthSearchableContainer& operator=(BreadthSearchableContainer&&) = delete; // Move assignment of abstract types should not be possible.

  /* ************************************************************************ */

  // Comparison operators
  bool operator==(const BreadthSearchableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.
  bool operator!=(const BreadthSearchableContainer&) const noexcept = delete; // Comparison of abstract types might not be possible.

  /* ************************************************************************ */

  // Specific member functions
  using typename SearchableContainer<Data>::MapFunctor;
  virtual void MapBreadth(MapFunctor, void*) = 0;

  using typename SearchableContainer<Data>::FoldFunctor;
  virtual void FoldBreadth(FoldFunctor, const void*, void*) const =  0;

};

/* ************************************************************************** */

  #include "container.cpp"

}

#endif
