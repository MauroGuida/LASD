
#include <stdexcept>

/* ************************************************************************** */

// Default constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(){
    Elements = new Data[2];
    size = 2;
  }

// Copy constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(const QueueVec& copyFrom) : Vector<Data>(copyFrom){
    head = copyFrom.head;
    tail = copyFrom.tail;
    lenght = copyFrom.lenght;
  }

// Move constructor
  template <typename Data>
  QueueVec<Data>::QueueVec(QueueVec&& moveFrom) : Vector<Data>(std::move(moveFrom)){
    std::swap(head, moveFrom.head);
    std::swap(tail, moveFrom.tail);
    std::swap(lenght, moveFrom.lenght);
  }

// Destructor
  template <typename Data>
  QueueVec<Data>::~QueueVec(){
    // vector destructor will be called
  }

// Copy assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec& copyFrom){
    Vector<Data>::operator=(copyFrom);
    head = copyFrom.head;
    tail = copyFrom.tail;
    lenght = copyFrom.lenght;

    return *this;
  }

// Move assignment
  template <typename Data>
  QueueVec<Data>& QueueVec<Data>::operator=(QueueVec&& moveFrom){
    Vector<Data>::operator=(std::move(moveFrom));
    std::swap(head, moveFrom.head);
    std::swap(tail, moveFrom.tail);
    std::swap(lenght, moveFrom.lenght);

    return *this;
  }

// Comparison operators
  template <typename Data>
  bool QueueVec<Data>::operator==(const QueueVec& comp) const noexcept{
    if(lenght == comp.lenght){
      ulong indexL = head;
      ulong indexR = comp.head;

      for(ulong i = 0; i < lenght; i++){
        if(Elements[indexL] != comp.Elements[indexR])
          return false;

        indexL = (indexL + 1) % size;
        indexR = (indexR + 1) % comp.size;
      }
    }else
      return false;

    return true;
  }

  template <typename Data>
  bool QueueVec<Data>::operator!=(const QueueVec& comp) const noexcept{
    return !(*this == comp);
  }

  // Specific member functions (inherited from Queue)
  template <typename Data>
  Data& QueueVec<Data>::Head() const{
    if(lenght == 0)
      throw std::length_error("Empty Queue!");

    return Elements[head];
  }

  template <typename Data>
  void QueueVec<Data>::Dequeue(){
    if(lenght == 0)
      throw std::length_error("Empty Queue!");

    head = (head + 1) % size;
    lenght--;

    if(lenght <= (size/4))
      Reduce();
  }

  template <typename Data>
  Data QueueVec<Data>::HeadNDequeue(){
    Data value = Head(); //throws length_error
    Dequeue();
    return value;
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(const Data& element){
    if(lenght == size - 1)
      Expand();

    lenght++;

    Elements[tail] = element;
    tail = (tail+1) % size;
  }

  template <typename Data>
  void QueueVec<Data>::Enqueue(Data&& element){
    if(lenght == size - 1)
      Expand();

    lenght++;

    std::swap(Elements[tail], element);
    tail = (tail+1) % size;
  }

  // Specific member functions (inherited from Container)
  template <typename Data>
  bool QueueVec<Data>::Empty() const noexcept{
    return (lenght==0);
  }

  template <typename Data>
  ulong QueueVec<Data>::Size() const noexcept{
    return lenght;
  }

  template <typename Data>
  void QueueVec<Data>::Clear(){
    Vector<Data>::Clear();

    delete[] Elements; //Inutile?
    Elements = new Data[2];
    size = 2;

    head = 0;
    tail = 0;
    lenght = 0;
  }

  template <typename Data>
  void QueueVec<Data>::Resize(const ulong newSize){
    if(newSize >= 2){
      Data *newVec = new Data[newSize];

      ulong i, next;
      for(i = 0, next = head; i < lenght; i++, next = (next+1) % size)
        std::swap(newVec[i], Elements[next]);

      head = 0;
      tail = lenght;
      size = newSize;

      std::swap(newVec, Elements);
      delete[] newVec;
    }
  }

  template <typename Data>
  void QueueVec<Data>::Expand(){
    Resize(size * 2);
  }

  template <typename Data>
  void QueueVec<Data>::Reduce(){
    Resize(size / 2);
  }
