
#include <stdexcept>

/* ************************************************************************** */

// Copy constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(const QueueLst& copyFrom) : List<Data>(copyFrom){
  }

// Move constructor
  template <typename Data>
  QueueLst<Data>::QueueLst(QueueLst&& moveFrom) : List<Data>(std::move(moveFrom)){
  }

// Destructor
  template <typename Data>
  QueueLst<Data>::~QueueLst(){
    // list destructor will be called
  }

// Copy assignment
  template <typename Data>
  QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst& copyFrom){
    List<Data>::operator=(copyFrom);

    return *this;
  }

// Move assignment
  template <typename Data>
  QueueLst<Data>& QueueLst<Data>::operator=(QueueLst&& moveFrom){
    List<Data>::operator=(std::move(moveFrom));

    return *this;
  }

// Comparison operators
  template <typename Data>
  bool QueueLst<Data>::operator==(const QueueLst& comp) const noexcept{
    return List<Data>::operator==(comp);
  }

  template <typename Data>
  bool QueueLst<Data>::operator!=(const QueueLst& comp) const noexcept{
    return !(*this == comp);
  }

// Specific member functions (inherited from Queue)
  template <typename Data>
  Data& QueueLst<Data>::Head() const{
    return List<Data>::Front();
  }

  template <typename Data>
  void QueueLst<Data>::Dequeue(){
    List<Data>::RemoveFromFront();
  }

  template <typename Data>
  Data QueueLst<Data>::HeadNDequeue(){
    return List<Data>::FrontNRemove();
  }

  template <typename Data>
  void QueueLst<Data>::Enqueue(const Data& insert){
    List<Data>::InsertAtBack(insert);
  }

  template <typename Data>
  void QueueLst<Data>::Enqueue(Data&& insert){
    List<Data>::InsertAtBack(insert);
  }

  template <typename Data>
  void QueueLst<Data>::Clear(){
    List<Data>::Clear();
  }
