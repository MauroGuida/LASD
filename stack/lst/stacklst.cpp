
#include <stdexcept>

/* ************************************************************************** */

// Copy constructor
  template <typename Data>
  StackLst<Data>::StackLst(const StackLst& copyFrom) : List<Data>(copyFrom){
  }

// Move constructor
  template <typename Data>
  StackLst<Data>::StackLst(StackLst&& moveFrom) : List<Data>(std::move(moveFrom)){
  }

// Destructor
  template <typename Data>
  StackLst<Data>::~StackLst(){
    // list destructor will be called
  }

// Copy assignment
  template <typename Data>
  StackLst<Data>& StackLst<Data>::operator=(const StackLst& copyFrom){
    List<Data>::operator=(copyFrom);

    return *this;
  }

// Move assignment
  template <typename Data>
  StackLst<Data>& StackLst<Data>::operator=(StackLst&& moveFrom){
    List<Data>::operator=(std::move(moveFrom));

    return *this;
  }

// Comparison operators
  template <typename Data>
  bool StackLst<Data>::operator==(const StackLst& comp) const noexcept{
    return List<Data>::operator==(comp);
  }

  template <typename Data>
  bool StackLst<Data>::operator!=(const StackLst& comp) const noexcept{
    return !(*this == comp);
  }

// Specific member functions (inherited from Stack)
  template <typename Data>
  Data& StackLst<Data>::Top() const{
    return List<Data>::Front();
  }

  template <typename Data>
  void StackLst<Data>::Pop(){
    List<Data>::RemoveFromFront();
  }

  template <typename Data>
  Data StackLst<Data>::TopNPop(){
    return List<Data>::FrontNRemove();
  }

  template <typename Data>
  void StackLst<Data>::Push(const Data& element){
    List<Data>::InsertAtFront(element);
  }

  template <typename Data>
  void StackLst<Data>::Push(Data&& element){
    List<Data>::InsertAtFront(element);
  }

// Specific member functions (inherited from Container)
  template <typename Data>
  void StackLst<Data>::Clear(){
    List<Data>::Clear();
  }
