
// NodeVec
// Specific member functions
  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasParent() const noexcept{
    if(index == 0)
      return false;

    return (treeVec[(index-1)/2].valid);
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasLeftSibling() const noexcept{
    if(index == 0)
      return false;

    return (treeVec[index-1].flag && treeVec[index-1].height == treeVec[index].height);
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasRightSibling() const noexcept{
    if(index == 0)
      return false;

    return (treeVec[index+1].flag && treeVec[index+1].height == treeVec[index].height);
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::Parent() const{
    if(!HasParent())
      throw std::out_of_range("Parent does not Exists!");

    return treeVec[(index-1)/2];
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftSibling() const{
    if(!HasLeftSibling())
      throw std::out_of_range("Left Sibling does not Exists!");

    return treeVec[index-1];
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightSibling() const{
    if(!HasRightSibling())
      throw std::out_of_range("Right Sibling does not Exists!");

    return treeVec[index+1];
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
    return !(HasLeftChild() && HasRightChild());
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasLeftChild() const noexcept{
    if((2 * index+1) <= size)
      return (treeVec[2 * index+1].valid);

    return false;
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
    if((2 * index+2) <= size)
      return (treeVec[2 * index+2].valid);

    return false;
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const{
    if(!HasLeftChild())
      throw std::out_of_range("Left Child does not Exists!");

    return (treeVec[2 * index+1]);
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const{
    if(!HasRightChild())
      throw std::out_of_range("Right Child does not Exists!");

    return (treeVec[2 * index+2]);
  }

// BinaryTreeVec
// Specific constructors
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const Data& newValue){
    treeVec = new Vector<struct NodeVec>(6);

    treeVec[0].value = newValue;

    treeVec[0].index = 0;
    treeVec[0].height = 0;

    treeVec[0].left = 1;
    treeVec[0].right = 2;

    treeVec[0].valid = true;

    size++;
  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(Data&& newValue) noexcept{
    treeVec = new Vector<struct NodeVec>(6);

    treeVec[0].value = std::move(newValue);

    treeVec[0].index = 0;
    treeVec[0].height = 0;

    treeVec[0].left = 1;
    treeVec[0].right = 2;

    treeVec[0].valid = true;

    size++;
  }

  // Copy constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& copyTree){
    treeHeight = copyTree.treeHeight;
    size = copyTree.size;

    treeVec = new Vector<struct NodeVec>(*copyTree->treeVec);
  }

  // Move constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& moveTree) noexcept{
    std::swap(treeHeight, moveTree.treeHeight);
    std::swap(size, moveTree.size);

    std::swap(treeVec, moveTree.treeVec);
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

    treeVec = new Vector<struct NodeVec>(*copyTree->treeVec);

    return *this;
  }

  // Move assignment
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec&& moveTree) noexcept{
    Clear();

    std::swap(treeHeight, moveTree.treeHeight);
    std::swap(size, moveTree.size);

    std::swap(treeVec, moveTree.treeVec);

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

    treeVec = new Vector<struct NodeVec>(6);

    treeVec[0].value = newValue;

    treeVec[0].index = 0;
    treeVec[0].height = 0;

    treeVec[0].left = 1;
    treeVec[0].right = 2;

    treeVec[0].valid = true;

    size++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::NewRoot(Data&& newValue){
    Clear();

    treeVec = new Vector<struct NodeVec>(6);

    treeVec[0].value = std::move(newValue);

    treeVec[0].index = 0;
    treeVec[0].height = 0;

    treeVec[0].left = 1;
    treeVec[0].right = 2;

    treeVec[0].valid = true;

    size++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddLeftChild(struct NodeVec& node, Data& value){
    if(node.HasLeftChild())
      RemoveLeftChild(node);

    if(treeVec->Size()-1 < node.left)
      Expand();

    treeVec[node.left].value = value;

    treeVec[node.left].index = node.left;
    treeVec[node.left].height = node.height+1;

    treeVec[node.left].left = 2 * node.left+1;
    treeVec[node.left].right = 2 * node.left+2;

    treeVec[node.left].valid = true;

    if(treeHeight < treeVec[node.left].height)
      treeHeight++;
   }

  template <typename Data>
  void BinaryTreeVec<Data>::AddLeftChild(struct NodeVec& node, Data&& value){
    if(node.HasLeftChild())
      RemoveLeftChild(node);

    if(treeVec->Size()-1 < node.left)
      Expand();

    treeVec[node.left].value = std::move(value);

    treeVec[node.left].index = node.left;
    treeVec[node.left].height = node.height+1;

    treeVec[node.left].left = 2 * node.left+1;
    treeVec[node.left].right = 2 * node.left+2;

    treeVec[node.left].valid = true;

    if(treeHeight < treeVec[node.left].height)
      treeHeight++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddRightChild(struct NodeVec& node, Data& value){
    if(node.HasRightChild())
      RemoveRightChild(node);

    if(treeVec->Size()-1 < node.right)
      Expand();

    treeVec[node.right].value = value;

    treeVec[node.right].index = node.right;
    treeVec[node.right].height = node.height+1;

    treeVec[node.right].left = 2 * node.left+1;
    treeVec[node.right].right = 2 * node.left+2;

    treeVec[node.right].valid = true;

    if(treeHeight < treeVec[node.right].height)
      treeHeight++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddRightChild(struct NodeVec& node, Data&& value){
    if(node.HasRightChild())
      RemoveRightChild(node);

    if(treeVec->Size()-1 < node.right)
      Expand();

    treeVec[node.right].value = std::move(value);

    treeVec[node.right].index = node.right;
    treeVec[node.right].height = node.height+1;

    treeVec[node.right].left = 2 * node.left+1;
    treeVec[node.right].right = 2 * node.left+2;

    treeVec[node.right].valid = true;

    if(treeHeight < treeVec[node.right].height)
      treeHeight++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::RemoveLeftChild(struct NodeVec& node){
    if(node.HasLeftChild()){
      node.valid = false;

      if(node.LeftChild().HasLeftChild())
        RemoveLeftChild(node.LeftChild());

      if(node.LeftChild().HasRightChild())
        RemoveRightChild(node.RightChild());
    }
  }

  template <typename Data>
  void BinaryTreeVec<Data>::RemoveRightChild(struct NodeVec& node){
    if(node.HasRightChild()){
      node.valid = false;

      if(node.RightChild().HasLeftChild())
        RemoveLeftChild(node.LeftChild());

      if(node.RightChild().HasRightChild())
        RemoveRightChild(node.RightChild());
    }
  }

// Specific member functions (inherited from Container)
  template <typename Data>
  void BinaryTreeVec<Data>::Clear(){
    delete treeVec;
    treeVec = nullptr;

    size = 0;
    treeHeight = 0;
  }

// Specific member functions (inherited from BreadthSearchableContainer)
  template <typename Data>
  void BinaryTreeVec<Data>::MapBreadth(MapFunctor func, void* par){
    treeVec.MapPreOrder(func, par);
  }

  template <typename Data>
  void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor func, const void* cPar, void* par) const{
    treeVec.FoldPreOrder(func, cPar, par);
  }

// Accessory functions
  template <typename Data>
  void BinaryTreeVec<Data>::Expand(){

  }

  template <typename Data>
  void BinaryTreeVec<Data>::Reduce(){

  }
