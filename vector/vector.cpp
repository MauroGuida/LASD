#include <stdexcept>


/* Costructos - Destructors */

  // Specific constructor
  template <typename Data>
  Vector<Data>::Vector(const ulong vectorSize){
    size = vectorSize;
    Elements = new Data[size];
  }

  // Copy constructor
  template <typename Data>
  Vector<Data>::Vector(const Vector& copyVector){
    size = copyVector.size;
    Elements = new Data[size];

    for(ulong i=0; i<size; i++)
      Elements[i] = copyVector[i];
  }

  // Move constructor
  template <typename Data>
  Vector<Data>::Vector(Vector&& moveVector) noexcept{
    std::swap(size, moveVector.size);
    std::swap(Elements, moveVector.Elements);
  }

  // Destructor
  template <typename Data>
  Vector<Data>::~Vector(){
    delete[] Elements;
  }


/* Assignment - Operators */

  // Copy assignment
  template <typename Data>
  Vector<Data>& Vector<Data>::operator=(const Vector& copyFrom){
    if(&copyFrom != this){ //self assignment is invalid
      size = copyFrom.size;

      if(size != 0){
        Data* newData = new Data[size];

        for(ulong i=0; i<size; i++)
          newData[i] = copyFrom.Elements[i];

        delete[] Elements;

        Elements = newData;
      }else{
        Elements = nullptr;
      }

    }

    return *this;
  }

  // Move assignment
  template <typename Data>
  Vector<Data>& Vector<Data>::operator=(Vector&& moveFrom){
    std::swap(size, moveFrom.size);
    std::swap(Elements, moveFrom.Elements);

    return *this;
  }

  // Equal operator
  template <typename Data>
  bool Vector<Data>::operator==(const Vector& compVector) const noexcept{
    bool flag = false;

    if(size == compVector.size){
      flag = true;
      for(ulong i=0; i<size; i++)
        if(Elements[i] != compVector.Elements[i]){
          return false;
        }
    }

    return flag;
  }

  // Not equal operator
  template <typename Data>
  bool Vector<Data>::operator!=(const Vector& compVector) const noexcept{
    return !(*this == compVector);
  }


/* Member functions */

  //Resize
  template <typename Data>
  void Vector<Data>::Resize(const ulong newSize){
    if(newSize == 0)
      Clear();
    else if(newSize != size){
      Data* newVector = new Data[newSize];

      ulong stopIndex = (size < newSize) ? size : newSize;

      for(ulong i=0; i<stopIndex; i++)
        std::swap(newVector[i], Elements[i]);

      std::swap(Elements, newVector);
      delete[] newVector;
      size = newSize;
    }
  }

  //Clear
  template <typename Data>
  void Vector<Data>::Clear(){
    size = 0;
    delete[] Elements;
    Elements = nullptr;
  }

  //Front
  template <typename Data>
  Data& Vector<Data>::Front() const{
    if(Elements == nullptr)
      throw std::length_error("Array is empty!");

    return Elements[0];
  }

  //Back
  template <typename Data>
  Data& Vector<Data>::Back() const{
    if(Elements == nullptr)
      throw std::length_error("Array is empty!");

    return Elements[size-1];
  }

  template <typename Data>
  Data& Vector<Data>::operator[](const ulong index) const{
    if(size == 0)
      throw std::length_error("Array is empty!");
      
    if(index >= size)
      throw std::length_error("Out of Range!");

    return Elements[index];
  }


/* Map and Fold */

  //Map
  template <typename Data>
  void Vector<Data>::MapPreOrder(MapFunctor function, void* par){
    for(ulong i = 0; i<size; i++)
      function(Elements[i], par);
  }

  template <typename Data>
  void Vector<Data>::MapPostOrder(MapFunctor function, void* par){
    for(ulong i=size-1; i>=0 && i < size; i--)
      function(Elements[i], par);
  }

  //Fold
  template <typename Data>
  void Vector<Data>::FoldPreOrder(FoldFunctor function, const void* cPar, void* par) const{
    for(ulong i = 0; i<size; i++)
      function(Elements[i], cPar, par);
  }

  template <typename Data>
  void Vector<Data>::FoldPostOrder(FoldFunctor function, const void* cPar, void* par) const{
    for(ulong i=size-1; i>=0 && i < size; i--)
      function(Elements[i], cPar, par);
  }
