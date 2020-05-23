
// Default constructor
  template <typename Data>
  PriorityQueue<Data>::PriorityQueue() : Heap<Data>::Heap(){

  }

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
  PriorityQueue<Data>::PriorityQueue(PriorityQueue<Data>&& moveFrom) noexcept : Heap<Data>::Heap(std::move(moveFrom)){

  }

// Copy assignment
  template <typename Data>
  PriorityQueue<Data>& PriorityQueue<Data>::operator=(const PriorityQueue& copyFrom){
    Heap<Data>::operator=(copyFrom);
    return *this;
  }

// Move assignment
  template <typename Data>
  PriorityQueue<Data>& PriorityQueue<Data>::operator=(PriorityQueue&& moveFrom) noexcept{
    Heap<Data>::operator=(std::move(moveFrom));
    return *this;
  }

// Comparison operators
  template <typename Data>
  bool PriorityQueue<Data>::operator==(const PriorityQueue<Data>& eq) const noexcept{
    return Heap<Data>::operator==(eq);
  }

  template <typename Data>
  bool PriorityQueue<Data>::operator!=(const PriorityQueue<Data>& eq) const noexcept{
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

    size--;
    heightVector[H]--;

    if(heightVector[H] == 0){
      if(treeHeight > 0)
        treeHeight--;

      if(treeHeight > 2)
        BinaryTreeVec<Data>::Reduce();
    }

    Heap<Data>::Heapify(0, size);
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

    if(size == 0)
      treeVec[size] = new struct BinaryTreeVec<Data>::NodeVec(value, size, 0, 2*size+1, 2*size+2, this);
    else
      treeVec[size] = new struct BinaryTreeVec<Data>::NodeVec(value, size, treeVec[(size-1)/2]->getHeight() + 1, 2*size+1, 2*size+2, this);


    if(treeVec[size]->getHeight() > treeHeight)
      treeHeight = treeVec[size]->getHeight();


    heightVector[treeVec[size]->getHeight()]++;
    size++;


    Heap<Data>::BuildHeap();
  }

  template <typename Data>
  void PriorityQueue<Data>::Insert(Data&& value){
    if(size+1 >= treeVec.Size())
      BinaryTreeVec<Data>::Expand();

    if(size == 0)
      treeVec[size] = new struct BinaryTreeVec<Data>::NodeVec(std::move(value), size, 0, 2*size+1, 2*size+2, this);
    else
      treeVec[size] = new struct BinaryTreeVec<Data>::NodeVec(std::move(value), size, treeVec[(size-1)/2]->getHeight() + 1, 2*size+1, 2*size+2, this);


    if(treeVec[size]->getHeight() > treeHeight)
      treeHeight = treeVec[size]->getHeight();


    heightVector[treeVec[size]->getHeight()]++;
    size++;


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

      while(temp->HasParent() && temp->Parent().Element() > temp->Element()){
        std::swap(temp->Parent().Element(), temp->Element());
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

      while(temp->HasParent() && temp->Parent().Element() > temp->Element()){
        std::swap(temp->Parent().Element(), temp->Element());
        temp = &refNode.Parent();
      }
    }
  }
