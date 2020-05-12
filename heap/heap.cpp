
template <typename Data>
void Heap<Data>::BuildTree(const LinearContainer<Data>& LC){
  if(LC.Size() > 0){
    treeVec[0] = new struct BinaryTreeVec<Data>::NodeVec(LC[0], 0, 0, 1, 2, this);

    // treeVec[0]->index = 0;
    // treeVec[0]->height = 0;
    //
    // treeVec[0]->left = 1;
    // treeVec[0]->right = 2;
    //
    // treeVec[0]->refTree = this;
  }

  for(ulong i=1; i < LC.Size(); i++){
    treeVec[i] = new struct BinaryTreeVec<Data>::NodeVec(LC[i], i, treeVec[i]->Parent().height + 1,
      2*i+1, 2*i+2, this);

    // treeVec[i]->index = i;
    // treeVec[i]->height = treeVec[i]->Parent().height + 1;
    //
    // treeVec[i]->left = 2 * i + 1;
    // treeVec[i]->right = 2 * i + 2;
    //
    // treeVec[i]->refTree = this;
  }
}

template <typename Data>
void Heap<Data>::BuildHeap(){
  for(ulong i = size/2; i>0; i++)
    Heapify(i, size);
}

template <typename Data>
void Heap<Data>::Heapify(ulong index, ulong heapSize){
  ulong l = 2 * index + 1;
  ulong r = 2 * index + 2;
  ulong max = index;

  if(l <= heapSize && treeVec[l]->Element() > treeVec[index]->Element())
    max = l;

  if(r <= heapSize && treeVec[r]->Element() > treeVec[max]->Element())
    max = r;

  if(max != index){
    std::swap(treeVec[index]->Element(), treeVec[max]->Element());
    Heapify(max, heapSize);
  }
}

// Default constructor
  template <typename Data>
  Heap<Data>::Heap() : BinaryTreeVec<Data>::BinaryTreeVec(){

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
    for(ulong i = heapSize; i>0; i--){
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
