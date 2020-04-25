
#include <stdexcept>

/* ************************************************************************** */

// Default constructor
  template <typename Data>
  StackVec<Data>::StackVec(){
    Elements = new Data[2];
    size = 2;
  }

// Copy constructor
  template <typename Data>
  StackVec<Data>::StackVec(const StackVec& copyFrom) : Vector<Data>(copyFrom){
    index = copyFrom.index;
  }

// Move constructor
  template <typename Data>
  StackVec<Data>::StackVec(StackVec&& moveFrom) : Vector<Data>(std::move(moveFrom)){
    std::swap(index, moveFrom.index);
  }

// Destructor
  template <typename Data>
  StackVec<Data>::~StackVec(){
    // vector destructor will be called
  }

// Copy assignment
  template <typename Data>
  StackVec<Data>& StackVec<Data>::operator=(const StackVec& copyFrom){
    Vector<Data>::operator=(copyFrom);
    index = copyFrom.index;

    return *this;
  }

// Move assignment
  template <typename Data>
  StackVec<Data>& StackVec<Data>::operator=(StackVec&& moveFrom) noexcept{
    Vector<Data>::operator=(std::move(moveFrom));
    std::swap(index, moveFrom.index);

    return *this;
  }

// Comparison operators
  template <typename Data>
  bool StackVec<Data>::operator==(const StackVec& comp) const noexcept{
    if(index == comp.index){
      for (ulong i = 0; i < index-1; i++)
        if(Elements[i] != comp.Elements[i])
          return false;
    }else
      return false;

    return true;
  }

  template <typename Data>
  bool StackVec<Data>::operator!=(const StackVec& comp) const noexcept{
    return !(*this == comp);
  }

// Specific member functions (inherited from Stack)
  template <typename Data>
  Data& StackVec<Data>::Top() const{
    if(index == 0)
      throw std::length_error("Empty Stack!");

    return Elements[index-1];
  }

  template <typename Data>
  void StackVec<Data>::Pop(){
    if(index > 0){
      index--;

      if(index <= (size/4))
        Reduce();
    }else
      throw std::length_error("Empty Stack!");
  }

  template <typename Data>
  Data StackVec<Data>::TopNPop(){
    Data value = Top(); //throws length_error
    Pop();
    return value;
  }

  template <typename Data>
  void StackVec<Data>::Push(const Data& element){
    if(index == size)
      Expand();


    Elements[index] = element;
    index++;
  }

  template <typename Data>
  void StackVec<Data>::Push(Data&& element){
    if(index == size)
      Expand();


    std::swap(Elements[index], element);
    index++;
  }

  template <typename Data>
  bool StackVec<Data>::Empty() const noexcept{
    return (index==0);
  }

  template <typename Data>
  ulong StackVec<Data>::Size() const noexcept{
    return index;
  }

  template <typename Data>
  void StackVec<Data>::Clear(){
    Vector<Data>::Clear();
    Vector<Data>::Resize(2);
    index = 0;
  }

  template <typename Data>
  void StackVec<Data>::Expand(){
    Vector<Data>::Resize(size * 2);
  }

  template <typename Data>
  void StackVec<Data>::Reduce(){
    int newSize = size/2;
    if(newSize >= 2)
      Vector<Data>::Resize(newSize);
  }
