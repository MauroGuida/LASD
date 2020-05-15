
// Specific constructor
  template <typename Data>
  PriorityQueue<Data>::PriorityQueue(const LinearContainer<Data>& LC) : Heap<Data>::Heap(LC){

  }

// Copy constructor
  template <typename Data>
  PriorityQueue<Data>::PriorityQueue(const PriorityQueue<Data>& copyFrom) : Heap<Data>::Heap(copyFrom){

  }

// Move constructor
  template <typename Data>
  PriorityQueue<Data>::PriorityQueue(PriorityQueue<Data>&& moveFrom) noexcept : Heap<Data>::Heap(moveFrom){

  }

// Copy assignment
  template <typename Data>
  PriorityQueue<Data>& PriorityQueue<Data>::operator=(const PriorityQueue& copyFrom){
    Heap<Data>::operetor=(copyFrom);
    return *this;
  }

// Move assignment
  template <typename Data>
  PriorityQueue<Data>& PriorityQueue<Data>::operator=(PriorityQueue&& moveFrom) noexcept{
    Heap<Data>::operetor=(moveFrom);
    return *this;
  }

// Comparison operators
  template <typename Data>
  bool PriorityQueue<Data>::operator==(const PriorityQueue& eq) const noexcept{
    return Heap<Data>::operator==(eq);
  }

  template <typename Data>
  bool PriorityQueue<Data>::operator!=(const PriorityQueue& eq) const noexcept{
    return Heap<Data>::operator!=(eq);
  }

// Specific member functions
  template <typename Data>
  const Data& PriorityQueue<Data>::Tip() const{
    if(size == 0)
      throw std::length_error("Empty PriorityQueue!");

    return treeVec[0]->Element();
  }

  template <typename Data>
  void PriorityQueue<Data>::RemoveTip(){
    if(size == 0)
      throw std::length_error("Empty PriorityQueue!");

    std::swap(treeVec[0]->Element(), treeVec[size-1]->Element());

    ulong H = treeVec[size-1]->getHeight();
    delete treeVec[size-1];
    treeVec[size-1] = nullptr;

    heightVector[H]--;
    if(heightVector[H] == 0){
      treeHeight--;

      if(treeHeight > 2)
        BinaryTreeVec<Data>::Reduce();
    }
  }

  template <typename Data>
  Data PriorityQueue<Data>::TipNRemove(){
    Data tmp= Tip();
    RemoveTip();

    return tmp;
  }

  template <typename Data>
  void PriorityQueue<Data>::Insert(const Data& value){
    if(size+1 >= treeVec.Size())
      BinaryTreeVec<Data>::Expand();

    size++;
    treeVec[size] = new struct BinaryTreeVec<Data>::NodeVec(value, size, treeVec[(size-1)/2]->getHeight() + 1, 2*size+1, 2*size+2, this);

    heightVector[treeVec[size]->getHeight()]++;

    if(treeVec[size]->getHeight() > treeHeight)
      treeHeight = treeVec[size]->getHeight();

    Heap<Data>::BuildHeap();
  }

  template <typename Data>
  void PriorityQueue<Data>::Insert(Data&& value){
    if(size+1 >= treeVec.Size())
      BinaryTreeVec<Data>::Expand();

    size++;
    treeVec[size] = new struct BinaryTreeVec<Data>::NodeVec(std::move(value), size, treeVec[(size-1)/2]->getHeight() + 1, 2*size+1, 2*size+2, this);

    heightVector[treeVec[size]->getHeight()]++;

    if(treeVec[size]->getHeight() > treeHeight)
      treeHeight = treeVec[size]->getHeight();

    Heap<Data>::BuildHeap();
  }

  template <typename Data>
  void PriorityQueue<Data>::ChangePriority(struct BinaryTreeVec<Data>::NodeVec& refNode, const Data& copyValue){
    if(refNode.Element() < copyValue){
      refNode.Element() = copyValue;

      Heap<Data>::Heapify(refNode.getIndex(), size);
    }else if(refNode.Element() > copyValue){
      refNode.Element() = copyValue;
      struct BinaryTreeVec<Data>::NodeVec* temp = &refNode;

      while(refNode.HasParent() && refNode.Parent().Element() > refNode.Element()){
        std::swap(refNode.Parent().Element(), refNode.Element());
        temp = &refNode.Parent();
      }
    }
  }

  template <typename Data>
  void PriorityQueue<Data>::ChangePriority(struct BinaryTreeVec<Data>::NodeVec& refNode, Data&& moveValue){
    if(refNode.Element() < moveValue){
      refNode.Element() = std::move(moveValue);

      Heap<Data>::Heapify(refNode.getIndex(), size);
    }else if(refNode.Element() > moveValue){
      refNode.Element() = std::move(moveValue);
      struct BinaryTreeVec<Data>::NodeVec* temp = &refNode;

      while(refNode.HasParent() && refNode.Parent().Element() > refNode.Element()){
        std::swap(refNode.Parent().Element(), refNode.Element());
        temp = &refNode.Parent();
      }
    }
  }
