
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
  ulong max = index;

  if(l < heapSize && treeVec[l] != nullptr && treeVec[l]->Element() > treeVec[index]->Element())
    max = l;

  if(r < heapSize && treeVec[r] != nullptr && treeVec[r]->Element() > treeVec[max]->Element())
    max = r;

  if(max != index && treeVec[max] != nullptr){
    std::swap(treeVec[index]->Element(), treeVec[max]->Element());
    Heapify(max, heapSize);
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
  Heap<Data>::Heap(Heap<Data>&& moveFrom) noexcept : BinaryTreeVec<Data>::BinaryTreeVec(moveFrom){

  }

// Copy assignment
  template <typename Data>
  Heap<Data>& Heap<Data>::operator=(const Heap<Data>& copyFrom){
    return BinaryTreeVec<Data>::operetor=(copyFrom);
  }

// Move assignment
  template <typename Data>
  Heap<Data>& Heap<Data>::operator=(Heap<Data>&& moveFrom) noexcept{
    return BinaryTreeVec<Data>::operetor=(moveFrom);
  }

// Specific member functions
  template <typename Data>
  void Heap<Data>::Sort() noexcept{
    ulong heapSize = size-1;
    BuildHeap();
    for(ulong i = heapSize; i>=0 && i < size; i--){
      std::swap(treeVec[i]->Element(), treeVec[0]->Element());
      heapSize--;
      Heapify(0, heapSize);
    }
  }

// Specific member functions (inherited from SearchableContainer)
  template <typename Data>
  void Heap<Data>::MapPreOrder(MapFunctor funct, void* par){
    for(ulong i = 0; i < size; i++)
      funct(treeVec[i]->Element(), par);
  }

  template <typename Data>
  void Heap<Data>::MapPostOrder(MapFunctor funct, void* par){
    for(ulong i = size; i>=0 && i < size; i++)
      funct(treeVec[i]->Element(), par);
  }

  template <typename Data>
  void Heap<Data>::FoldPreOrder(FoldFunctor funct, const void* cPar, void* par) const{
    for(ulong i = 0; i < size; i++)
      funct(treeVec[i]->Element(), cPar, par);
  }

  template <typename Data>
  void Heap<Data>::FoldPostOrder(FoldFunctor funct, const void* cPar, void* par) const{
    for(ulong i = size; i>=0 && i < size; i++)
      funct(treeVec[i]->Element(), cPar, par);
  }
