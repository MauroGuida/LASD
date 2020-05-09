
// NodeVec
// Specific member functions
  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasParent() const noexcept{
    if(index == 0)
      return false;

    return ((refTree->treeVec)[(index-1)/2].valid);
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasLeftSibling() const noexcept{
    if(index == 0)
      return false;

    return ((refTree->treeVec)[index-1].valid && (refTree->treeVec)[index-1].height == (refTree->treeVec)[index].height);
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasRightSibling() const noexcept{
    if(index == 0)
      return false;

    return ((refTree->treeVec)[index+1].valid && (refTree->treeVec)[index+1].height == (refTree->treeVec)[index].height);
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::Parent() const{
    if(!HasParent())
      throw std::out_of_range("Parent does not Exists!");

    return (refTree->treeVec)[(index-1)/2];
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftSibling() const{
    if(!HasLeftSibling())
      throw std::out_of_range("Left Sibling does not Exists!");

    return (refTree->treeVec)[index-1];
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightSibling() const{
    if(!HasRightSibling())
      throw std::out_of_range("Right Sibling does not Exists!");

    return (refTree->treeVec)[index+1];
  }

// Specific member functions (inherited from Node)
  template <typename Data>
  Data& BinaryTreeVec<Data>::NodeVec::Element(){
    return value;
  }

  template <typename Data>
  const Data& BinaryTreeVec<Data>::NodeVec::Element() const{
    return value;
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::IsLeaf() const noexcept{
    return (!HasLeftChild() && !HasRightChild());
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
    if((2 * index+1) < (refTree->treeVec).Size())
      return ((refTree->treeVec)[2 * index+1].valid);

    return false;
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
    if((2 * index+2) < (refTree->treeVec).Size())
      return ((refTree->treeVec)[2 * index+2].valid);

    return false;
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const{
    if(!HasLeftChild())
      throw std::out_of_range("Left Child does not Exists!");

    return (refTree->treeVec)[2 * index+1];
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const{
    if(!HasRightChild())
      throw std::out_of_range("Right Child does not Exists!");

    return (refTree->treeVec)[2 * index+2];
  }

// BinaryTreeVec
// Specific constructors
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const Data& newValue){
    for(int i = 0; i < 100; i++)
      heightVector[i] = 0;

    treeVec.Resize(7);
    // heightVector.Resize(4);

    heightVector[0] = 1;

    treeVec[0].value = newValue;

    treeVec[0].index = 0;
    treeVec[0].height = 0;

    treeVec[0].left = 1;
    treeVec[0].right = 2;

    treeVec[0].valid = true;
    treeVec[0].refTree = this;

    size++;
  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(Data&& newValue) noexcept{
    for(int i = 0; i < 100; i++)
      heightVector[i] = 0;

    treeVec.Resize(7);
    // heightVector.Resize(4);

    heightVector[0] = 1;

    treeVec[0].value = std::move(newValue);

    treeVec[0].index = 0;
    treeVec[0].height = 0;

    treeVec[0].left = 1;
    treeVec[0].right = 2;

    treeVec[0].valid = true;
    treeVec[0].refTree = this;

    size++;
  }

  // Copy constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& copyTree){
    treeHeight = copyTree.treeHeight;
    size = copyTree.size;

    treeVec = copyTree.treeVec;
    heightVector = copyTree.heightVector;
  }

  // Move constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& moveTree) noexcept{
    std::swap(treeHeight, moveTree.treeHeight);
    std::swap(size, moveTree.size);

    std::swap(treeVec, moveTree.treeVec);
    std::swap(heightVector, moveTree.heightVector);
  }

// Destructor
  template <typename Data>
  BinaryTreeVec<Data>::~BinaryTreeVec(){
    Clear();
  }

// Assignment
  // Copy assignment
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& copyTree){
    Clear();

    treeHeight = copyTree.treeHeight;
    size = copyTree.size;

    treeVec = copyTree.treeVec;
    heightVector = copyTree.heightVector;

    return *this;
  }

  // Move assignment
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec&& moveTree) noexcept{
    Clear();

    std::swap(treeHeight, moveTree.treeHeight);
    std::swap(size, moveTree.size);

    std::swap(treeVec, moveTree.treeVec);
    std::swap(heightVector, moveTree.heightVector);

    return *this;
  }

// Specific member functions (inherited from BinaryTree)
  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const{
    if(size == 0)
      throw std::out_of_range("Root does not Exists!");

    return treeVec[0];
  }

  template <typename Data>
  void BinaryTreeVec<Data>::NewRoot(const Data& newValue){
    Clear();

    treeVec.Resize(7);
    // heightVector.Resize(4);

    heightVector[0] = 1;

    treeVec[0].value = newValue;

    treeVec[0].index = 0;
    treeVec[0].height = 0;

    treeVec[0].left = 1;
    treeVec[0].right = 2;

    treeVec[0].valid = true;
    treeVec[0].refTree = this;

    size++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::NewRoot(Data&& newValue){
    Clear();

    treeVec.Resize(7);
    // heightVector.Resize(4);

    heightVector[0] = 1;

    treeVec[0].value = std::move(newValue);

    treeVec[0].index = 0;
    treeVec[0].height = 0;

    treeVec[0].left = 1;
    treeVec[0].right = 2;

    treeVec[0].valid = true;
    treeVec[0].refTree = this;

    size++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddLeftChild(struct NodeVec& node, const Data& value){
    if(node.HasLeftChild())
      RemoveLeftChild(node);

    ulong newNodeIndex = node.left;
    ulong fatherIndex = node.index;

    // std::cout << "Indice del nuovo nodo: " << newNodeIndex <<
    // "  Indice del padre: " << fatherIndex << std::endl;
    //
    // std::cout << "Altezza nuovo nodo: " << treeVec[fatherIndex].height+1 <<
    // "  Altezza del padre: " << treeVec[fatherIndex].height << std::endl;

    if(newNodeIndex >= treeVec.Size())
      Expand();

    treeVec[newNodeIndex].value = value;

    treeVec[newNodeIndex].index = newNodeIndex;
    treeVec[newNodeIndex].height = treeVec[fatherIndex].height+1;

    treeVec[newNodeIndex].left = 2 * treeVec[fatherIndex].left+1;
    treeVec[newNodeIndex].right = 2 * treeVec[fatherIndex].left+2;

    treeVec[newNodeIndex].valid = true;
    treeVec[newNodeIndex].refTree = this;

    size++;

    if(treeHeight < treeVec[newNodeIndex].height)
      treeHeight++;

    heightVector[treeVec[newNodeIndex].height]++;

    // std::cout << "L'altezza " << treeVec[newNodeIndex].height << " adesso ha " <<
    // heightVector[treeVec[newNodeIndex].height] << " nodi" << std::endl;
   }

  template <typename Data>
  void BinaryTreeVec<Data>::AddLeftChild(struct NodeVec& node, Data&& value){
    if(node.HasLeftChild())
      RemoveLeftChild(node);

    ulong newNodeIndex = node.left;
    ulong fatherIndex = node.index;

    // std::cout << "Indice del nuovo nodo: " << newNodeIndex <<
    // "  Indice del padre: " << fatherIndex << std::endl;
    //
    // std::cout << "Altezza nuovo nodo: " << treeVec[fatherIndex].height+1 <<
    // "  Altezza del padre: " << treeVec[fatherIndex].height << std::endl;

    if(newNodeIndex >= treeVec.Size())
      Expand();

    treeVec[newNodeIndex].value = std::move(value);

    treeVec[newNodeIndex].index = newNodeIndex;
    treeVec[newNodeIndex].height = treeVec[fatherIndex].height+1;

    treeVec[newNodeIndex].left = 2 * treeVec[fatherIndex].left+1;
    treeVec[newNodeIndex].right = 2 * treeVec[fatherIndex].left+2;

    treeVec[newNodeIndex].valid = true;
    treeVec[newNodeIndex].refTree = this;

    size++;

    if(treeHeight < treeVec[newNodeIndex].height)
      treeHeight++;

    heightVector[treeVec[newNodeIndex].height]++;

    // std::cout << "L'altezza " << treeVec[newNodeIndex].height << " adesso ha " <<
    // heightVector[treeVec[newNodeIndex].height] << " nodi" << std::endl;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddRightChild(struct NodeVec& node, const Data& value){
    if(node.HasRightChild())
      RemoveRightChild(node);

    ulong newNodeIndex = node.right;
    ulong fatherIndex = node.index;

    // std::cout << "Indice del nuovo nodo: " << newNodeIndex <<
    // "  Indice del padre: " << fatherIndex << std::endl;
    //
    // std::cout << "Altezza nuovo nodo: " << treeVec[fatherIndex].height+1 <<
    // "  Altezza del padre: " << treeVec[fatherIndex].height << std::endl;

    if(newNodeIndex >= treeVec.Size())
      Expand();

    treeVec[newNodeIndex].value = value;

    treeVec[newNodeIndex].index = newNodeIndex;
    treeVec[newNodeIndex].height = treeVec[fatherIndex].height+1;

    treeVec[newNodeIndex].left = 2 * treeVec[fatherIndex].right+1;
    treeVec[newNodeIndex].right = 2 * treeVec[fatherIndex].right+2;

    treeVec[newNodeIndex].valid = true;
    treeVec[newNodeIndex].refTree = this;

    size++;

    if(treeHeight < treeVec[newNodeIndex].height)
      treeHeight++;

    heightVector[treeVec[newNodeIndex].height]++;

    // std::cout << "L'altezza " << treeVec[newNodeIndex].height << " adesso ha " <<
    // heightVector[treeVec[newNodeIndex].height] << " nodi" << std::endl;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddRightChild(struct NodeVec& node, Data&& value){
    if(node.HasRightChild())
      RemoveRightChild(node);

    ulong newNodeIndex = node.right;
    ulong fatherIndex = node.index;

    // std::cout << "Indice del nuovo nodo: " << newNodeIndex <<
    // "  Indice del padre: " << fatherIndex << std::endl;
    //
    // std::cout << "Altezza nuovo nodo: " << treeVec[fatherIndex].height+1 <<
    // "  Altezza del padre: " << treeVec[fatherIndex].height << std::endl;

    if(newNodeIndex >= treeVec.Size())
      Expand();

    treeVec[newNodeIndex].value = std::move(value);

    treeVec[newNodeIndex].index = newNodeIndex;
    treeVec[newNodeIndex].height = treeVec[fatherIndex].height+1;

    treeVec[newNodeIndex].left = 2 * treeVec[fatherIndex].right+1;
    treeVec[newNodeIndex].right = 2 * treeVec[fatherIndex].right+2;

    treeVec[newNodeIndex].valid = true;
    treeVec[newNodeIndex].refTree = this;

    size++;

    if(treeHeight < treeVec[newNodeIndex].height)
      treeHeight++;

    heightVector[treeVec[newNodeIndex].height]++;

    // std::cout << "L'altezza " << treeVec[newNodeIndex].height << " adesso ha " <<
    // heightVector[treeVec[newNodeIndex].height] << " nodi" << std::endl;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::RemoveLeftChild(struct NodeVec& node){
    if(!node.HasLeftChild())
      return;

    ulong nodeIndex = node.index;

    if(treeVec[nodeIndex].HasLeftChild())
      RemoveLeftChild(treeVec[nodeIndex].LeftChild());

    if(treeVec[nodeIndex].HasRightChild())
      RemoveRightChild(treeVec[nodeIndex].RightChild());

    treeVec[nodeIndex].LeftChild().valid = false;

    size--;
    heightVector[treeVec[nodeIndex].height+1]--;

    if(heightVector[treeHeight] == 0){
      if(treeVec.Size() > 7)
        Reduce();
      treeHeight--;
    }
  }

  template <typename Data>
  void BinaryTreeVec<Data>::RemoveRightChild(struct NodeVec& node){
    if(!node.HasRightChild())
      return;

    ulong nodeIndex = node.index;

    if(treeVec[nodeIndex].HasLeftChild())
      RemoveLeftChild(treeVec[nodeIndex].LeftChild());

    if(treeVec[nodeIndex].HasRightChild())
      RemoveRightChild(treeVec[nodeIndex].RightChild());

    treeVec[nodeIndex].RightChild().valid = false;

    size--;
    heightVector[treeVec[nodeIndex].height+1]--;

    if(heightVector[treeHeight] == 0){
      if(treeVec.Size() > 7)
        Reduce();
      treeHeight--;
    }
  }

// Specific member functions (inherited from Container)
  template <typename Data>
  void BinaryTreeVec<Data>::Clear(){
    treeVec.Clear();
    // heightVector.Clear();
    for(int i = 0; i < 100; i++)
      heightVector[i] = 0;

    size = 0;
    treeHeight = 0;
  }

// Specific member functions (inherited from BreadthSearchableContainer)
  template <typename Data>
  void BinaryTreeVec<Data>::MapBreadth(MapFunctor func, void* par){
    for(ulong i = 0; i < treeVec.Size(); i++)
      if(treeVec[i].valid)
        func(treeVec[i].value, par);
  }

  template <typename Data>
  void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor func, const void* cPar, void* par) const{
    for(ulong i = 0; i < treeVec.Size(); i++)
      if(treeVec[i].valid)
        func(treeVec[i].value, cPar, par);
  }

// Accessory functions
  template <typename Data>
  void BinaryTreeVec<Data>::Expand(){
    // heightVector.Resize(heightVector.Size() + 1);
    treeVec.Resize(treeVec.Size()*2+1);
  }

  template <typename Data>
  void BinaryTreeVec<Data>::Reduce(){
    // heightVector.Resize(heightVector.Size() - 1);
    treeVec.Resize((treeVec.Size()-1)/2);
  }
