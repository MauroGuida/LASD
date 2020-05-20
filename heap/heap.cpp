
template <typename Data>
void Heap<Data>::BuildTree(const LinearContainer<Data>& LC){
  while(LC.Size() > treeVec.Size())
    BinaryTreeVec<Data>::Expand();

  if(LC.Size() > 0){
    treeVec[0] = new struct BinaryTreeVec<Data>::NodeVec(LC[0], 0, 0, 1, 2, this);

    size++;
    heightVector[0]++;
  }

  for(ulong i=1; i < LC.Size(); i++){
    treeVec[i] = new struct BinaryTreeVec<Data>::NodeVec(LC[i], i, treeVec[(i-1)/2]->getHeight() + 1,
      2*i+1, 2*i+2, this);

      size++;
      heightVector[treeVec[i]->getHeight()]++;

      if(treeVec[i]->getHeight() > treeHeight)
        treeHeight = treeVec[i]->getHeight();
  }
}

template <typename Data>
void Heap<Data>::BuildHeap(){
  for(ulong i = (size/2)-1; i>=0 && i < size; i--)
    Heapify(i, size);
}

template <typename Data>
void Heap<Data>::Heapify(ulong index, ulong heapSize){
  ulong l = 2 * index + 1;
  ulong r = 2 * index + 2;
  ulong min = index;

  if(l < heapSize && treeVec[l] != nullptr && treeVec[l]->Element() < treeVec[index]->Element())
    min = l;

  if(r < heapSize && treeVec[r] != nullptr && treeVec[r]->Element() < treeVec[min]->Element())
    min = r;

  if(min != index && treeVec[min] != nullptr){
    std::swap(treeVec[index]->Element(), treeVec[min]->Element());
    Heapify(min, heapSize);
  }
}

// Default constructor
  template <typename Data>
  Heap<Data>::Heap() : BinaryTreeVec<Data>::BinaryTreeVec(){
    BinaryTreeVec<Data>::Clear();
  }

// Specific constructor
  template <typename Data>
  Heap<Data>::Heap(const LinearContainer<Data>& LC) : Heap<Data>(){
    BuildTree(LC);
    BuildHeap();
  }

// Copy constructor
  template <typename Data>
  Heap<Data>::Heap(const Heap<Data>& copyFrom) : BinaryTreeVec<Data>::BinaryTreeVec(copyFrom){

  }

// Move constructor
  template <typename Data>
  Heap<Data>::Heap(Heap<Data>&& moveFrom) noexcept : BinaryTreeVec<Data>::BinaryTreeVec(std::move(moveFrom)){

  }

// Comparison operators
  template <typename Data>
  bool Heap<Data>::operator==(const Heap<Data>& eq) const noexcept{
    return BinaryTreeVec<Data>::operator==(eq);
  }

  template <typename Data>
  bool Heap<Data>::operator!=(Heap<Data>&& eq) const noexcept{
    return BinaryTreeVec<Data>::operator!=(eq);
  }

// Copy assignment
  template <typename Data>
  Heap<Data>& Heap<Data>::operator=(const Heap<Data>& copyFrom){
    BinaryTreeVec<Data>::operetor=(copyFrom);
    return *this;
  }

// Move assignment
  template <typename Data>
  Heap<Data>& Heap<Data>::operator=(Heap<Data>&& moveFrom) noexcept{
    BinaryTreeVec<Data>::operetor=(moveFrom);
    return *this;
  }

// Specific member functions
  template <typename Data>
  void Heap<Data>::Sort() noexcept{
    ulong heapSize = size;
    BuildHeap();
    for(ulong i = size - 1; i>=0 && i < size; i--){
      std::swap(treeVec[i]->Element(), treeVec[0]->Element());
      heapSize--;
      Heapify(0, heapSize);
    }

    ulong i = 0;
    ulong j = size - 1;
    Data temp;
    while(i < j){
  		temp = treeVec[i]->Element();
  		treeVec[i]->Element() = treeVec[j]->Element();
  		treeVec[j]->Element() = temp;
  		i++;
  		j--;
  	}
  }

// Specific member functions (inherited from SearchableContainer)
  template <typename Data>
  void Heap<Data>::MapPreOrder(MapFunctor funct, void* par){
    for(ulong i = 0; i < size; i++)
      if(treeVec[i] != nullptr)
        funct(treeVec[i]->Element(), par);

    BuildHeap();
  }

  template <typename Data>
  void Heap<Data>::MapPostOrder(MapFunctor funct, void* par){
    for(ulong i = size-1; i>=0 && i < size; i--)
      if(treeVec[i] != nullptr)
        funct(treeVec[i]->Element(), par);

    BuildHeap();
  }

  template <typename Data>
  void Heap<Data>::FoldPreOrder(FoldFunctor funct, const void* cPar, void* par) const{
    for(ulong i = 0; i < size; i++)
      if(treeVec[i] != nullptr)
        funct(treeVec[i]->Element(), cPar, par);
  }

  template <typename Data>
  void Heap<Data>::FoldPostOrder(FoldFunctor funct, const void* cPar, void* par) const{
    for(ulong i = size-1; i>=0 && i < size; i--)
      if(treeVec[i] != nullptr)
        funct(treeVec[i]->Element(), cPar, par);
  }
