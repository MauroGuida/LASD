
// NodeVec
// Constructor
  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::NodeVec(Data&& elem, ulong i, ulong h, ulong l, ulong r, BinaryTreeVec<Data>* ref){
    value = std::move(elem);

    index = i;
    height = h;

    left = l;
    right = r;

    refTree = ref;
  }

  template <typename Data>
  BinaryTreeVec<Data>::NodeVec::NodeVec(const Data& elem, ulong i, ulong h, ulong l, ulong r, BinaryTreeVec<Data>* ref){
    value = elem;

    index = i;
    height = h;

    left = l;
    right = r;

    refTree = ref;
  }

// Getters
  template <typename Data>
  const ulong BinaryTreeVec<Data>::NodeVec::getIndex() const{
    return index;
  }

  template <typename Data>
  const ulong BinaryTreeVec<Data>::NodeVec::getHeight() const{
    return height;
  }

  template <typename Data>
  const ulong BinaryTreeVec<Data>::NodeVec::getLeft() const{
    return left;
  }

  template <typename Data>
  const ulong BinaryTreeVec<Data>::NodeVec::getRight() const{
    return right;
  }

// Specific member functions
  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasParent() const noexcept{
    if(index == 0)
      return false;

    return ((refTree->treeVec)[(index-1)/2] != nullptr);
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasLeftSibling() const noexcept{
    if(index == 0)
      return false;

    return ((refTree->treeVec)[index-1] != nullptr && (refTree->treeVec)[index-1]->height == (refTree->treeVec)[index]->height);
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasRightSibling() const noexcept{
    if(index == 0)
      return false;

    return ((refTree->treeVec)[index+1] != nullptr && (refTree->treeVec)[index+1]->height == (refTree->treeVec)[index]->height);
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::Parent() const{
    if(!HasParent())
      throw std::out_of_range("Parent does not Exists!");

    return *(refTree->treeVec)[(index-1)/2];
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftSibling() const{
    if(!HasLeftSibling())
      throw std::out_of_range("Left Sibling does not Exists!");

    return *(refTree->treeVec)[index-1];
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightSibling() const{
    if(!HasRightSibling())
      throw std::out_of_range("Right Sibling does not Exists!");

    return *(refTree->treeVec)[index+1];
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
    if(left < refTree->treeVec.Size())
      return refTree->treeVec[left] != nullptr;

    return false;
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
    if(right < refTree->treeVec.Size())
      return refTree->treeVec[right] != nullptr;

    return false;
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::LeftChild() const{
    if(!HasLeftChild())
      throw std::out_of_range("Left Child does not Exists!");

    return *(refTree->treeVec)[left];
  }

  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::NodeVec::RightChild() const{
    if(!HasRightChild())
      throw std::out_of_range("Right Child does not Exists!");

    return *(refTree->treeVec)[right];
  }

// BinaryTreeVec
// Default constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(){
    for(int i = 0; i < 100; i++)
      heightVector[i] = 0;

    treeVec.Resize(7);
    for(int i = 0; i < 7; i++)
      treeVec[i] = nullptr;
  }

// Specific constructors
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const Data& newValue){
    for(int i = 0; i < 100; i++)
      heightVector[i] = 0;

    treeVec.Resize(7);
    for(ulong i = 0; i < treeVec.Size(); i++)
      treeVec[i] = nullptr;


    treeVec[0] = new struct NodeVec(newValue, 0, 0, 1, 2, this);

    heightVector[0] = 1;

    // treeVec[0]->index = 0;
    // treeVec[0]->height = 0;
    //
    // treeVec[0]->left = 1;
    // treeVec[0]->right = 2;
    //
    // treeVec[0]->refTree = this;

    size++;
  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(Data&& newValue) noexcept{
    for(int i = 0; i < 100; i++)
      heightVector[i] = 0;

    treeVec.Resize(7);
    for(ulong i = 0; i < treeVec.Size(); i++)
      treeVec[i] = nullptr;


    treeVec[0] = new struct NodeVec(std::move(newValue), 0, 0, 1, 2, this);

    heightVector[0] = 1;

    // treeVec[0]->index = 0;
    // treeVec[0]->height = 0;
    //
    // treeVec[0]->left = 1;
    // treeVec[0]->right = 2;
    //
    // treeVec[0]->refTree = this;

    size++;
  }

  // Copy constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& copyTree){
    treeHeight = copyTree.treeHeight;
    size = copyTree.size;

    treeVec.Resize(copyTree.treeVec.Size());
    // for(ulong i = 0; i < treeVec.Size(); i++)
    //   treeVec[i] = nullptr;

    for(ulong i = 0; i < copyTree.treeVec.Size(); i++)
      if(copyTree.treeVec[i] != nullptr){
        treeVec[i] = new struct NodeVec(copyTree.treeVec[i]->value, copyTree.treeVec[i]->index,
            copyTree.treeVec[i]->height, copyTree.treeVec[i]->left, copyTree.treeVec[i]->right, this);

        // treeVec[i]->index = copyTree.treeVec[i]->index;
        // treeVec[i]->height = copyTree.treeVec[i]->height;
        //
        // treeVec[i]->left = copyTree.treeVec[i]->left;
        // treeVec[i]->right = copyTree.treeVec[i]->right;
        //
        // treeVec[i]->refTree = this;
      }else{
        treeVec[i] = nullptr;
      }

    for(int i = 0; i < 100; i++)
      heightVector[i] = copyTree.heightVector[i];
  }

  // Move constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& moveTree) noexcept{
    Clear();

    std::swap(treeHeight, moveTree.treeHeight);
    std::swap(size, moveTree.size);

    std::swap(treeVec, moveTree.treeVec);
    std::swap(heightVector, moveTree.heightVector);

    for(ulong i = 0; i<treeVec.Size(); i++)
      if(treeVec[i] != nullptr)
        treeVec[i]->refTree = this;
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

    treeVec.Resize(copyTree.treeVec.Size());
    // for(ulong i = 0; i < treeVec.Size(); i++)
    //   treeVec[i] = nullptr;

    for(ulong i = 0; i < copyTree.treeVec.Size(); i++)
      if(copyTree.treeVec[i] != nullptr){
        treeVec[i] = new struct NodeVec(copyTree.treeVec[i]->value, copyTree.treeVec[i]->index,
            copyTree.treeVec[i]->height, copyTree.treeVec[i]->left, copyTree.treeVec[i]->right, this);

        // treeVec[i]->index = copyTree.treeVec[i]->index;
        // treeVec[i]->height = copyTree.treeVec[i]->height;
        //
        // treeVec[i]->left = copyTree.treeVec[i]->left;
        // treeVec[i]->right = copyTree.treeVec[i]->right;
        //
        // treeVec[i]->refTree = this;
      }else{
        treeVec[i] = nullptr;
      }

    for(int i = 0; i < 100; i++)
      heightVector[i] = copyTree.heightVector[i];

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

    for(ulong i = 0; i<treeVec.Size(); i++)
      if(treeVec[i] != nullptr)
        treeVec[i]->refTree = this;

    return *this;
  }

// Specific member functions (inherited from BinaryTree)
  template <typename Data>
  struct BinaryTreeVec<Data>::NodeVec& BinaryTreeVec<Data>::Root() const{
    if(size == 0)
      throw std::out_of_range("Root does not Exists!");

    return *treeVec[0];
  }

  template <typename Data>
  void BinaryTreeVec<Data>::NewRoot(const Data& newValue){
    Clear();

    treeVec[0] = new struct NodeVec(newValue, 0, 0, 1, 2, this);

    heightVector[0] = 1;

    // treeVec[0]->index = 0;
    // treeVec[0]->height = 0;
    //
    // treeVec[0]->left = 1;
    // treeVec[0]->right = 2;
    //
    // treeVec[0]->refTree = this;

    size++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::NewRoot(Data&& newValue){
    Clear();

    treeVec[0] = new struct NodeVec(std::move(newValue), 0, 0, 1, 2, this);

    heightVector[0] = 1;

    // treeVec[0]->index = 0;
    // treeVec[0]->height = 0;
    //
    // treeVec[0]->left = 1;
    // treeVec[0]->right = 2;

    // treeVec[0]->refTree = this;

    size++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddLeftChild(struct NodeVec& node, const Data& value){
    if(node.HasLeftChild())
      RemoveLeftChild(node);

    if(node.height+1 > treeHeight)
      Expand();

    treeVec[node.left] = new struct NodeVec(value, node.left, node.height+1, 2 * node.left + 1,
        2 * node.left + 2, this);

    // treeVec[node.left]->index = node.left;
    // treeVec[node.left]->height = node.height+1;
    //
    // treeVec[node.left]->left = 2 * node.left + 1;
    // treeVec[node.left]->right = 2 * node.left + 2;
    //
    // treeVec[node.left]->refTree = this;

    size++;

    if(treeHeight < treeVec[node.left]->height)
      treeHeight++;

    heightVector[treeVec[node.left]->height]++;
   }

  template <typename Data>
  void BinaryTreeVec<Data>::AddLeftChild(struct NodeVec& node, Data&& value){
    if(node.HasLeftChild())
      RemoveLeftChild(node);

    if(node.height+1 > treeHeight)
      Expand();

    treeVec[node.left] = new struct NodeVec(std::move(value), node.left, node.height+1,
        node.left * 2 + 1, node.left * 2 + 2, this);

    // treeVec[node.left]->index = node.left;
    // treeVec[node.left]->height = node.height+1;
    //
    // treeVec[node.left]->left = node.left * 2 + 1;
    // treeVec[node.left]->right = node.left * 2 + 2;
    //
    // treeVec[node.left]->refTree = this;

    size++;

    if(treeHeight < treeVec[node.left]->height)
      treeHeight++;

    heightVector[treeVec[node.left]->height]++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddRightChild(struct NodeVec& node, const Data& value){
    if(node.HasRightChild())
      RemoveRightChild(node);

    if(node.height+1 > treeHeight)
      Expand();

    treeVec[node.right] = new struct NodeVec(value, node.right, node.height+1, node.right * 2 + 1,
        node.right * 2 + 2, this);

    // treeVec[node.right]->index = node.right;
    // treeVec[node.right]->height = node.height+1;
    //
    // treeVec[node.right]->left = node.right * 2 + 1;
    // treeVec[node.right]->right = node.right * 2 + 2;
    //
    // treeVec[node.right]->refTree = this;

    size++;

    if(treeHeight < treeVec[node.right]->height)
      treeHeight++;

    heightVector[treeVec[node.right]->height]++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddRightChild(struct NodeVec& node, Data&& value){
    if(node.HasRightChild())
      RemoveRightChild(node);

    if(node.height+1 > treeHeight)
      Expand();

    treeVec[node.right] = new struct NodeVec(std::move(value), node.right, node.height+1, node.right * 2 + 1,
        node.right * 2 + 2, this);

    // treeVec[node.right]->index = node.right;
    // treeVec[node.right]->height = node.height+1;
    //
    // treeVec[node.right]->left = node.right * 2 + 1;
    // treeVec[node.right]->right = node.right * 2 + 2;
    //
    // treeVec[node.right]->refTree = this;

    size++;

    if(treeHeight < treeVec[node.right]->height)
      treeHeight++;

    heightVector[treeVec[node.right]->height]++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::removeSubtree(struct NodeVec& node){
    ulong nodeIndex = node.index;

    ulong LIndex = node.left;
    ulong RIndex = node.right;


    if(treeVec.Size() > nodeIndex && treeVec[nodeIndex]->HasLeftChild())
      removeSubtree(*treeVec[LIndex]);

    if(treeVec.Size() > nodeIndex && treeVec[nodeIndex]->HasRightChild())
      removeSubtree(*treeVec[RIndex]);


    int h = node.height;
    delete treeVec[nodeIndex];
    treeVec[nodeIndex] = nullptr;

    size--;
    heightVector[h]--;


    if(heightVector[treeHeight] == 0){
      if(treeHeight > 2)
        Reduce();

      if(treeHeight > 0)
        treeHeight--;
    }
  }

  template <typename Data>
  void BinaryTreeVec<Data>::RemoveLeftChild(struct NodeVec& node){
    if(node.HasLeftChild())
      removeSubtree(node.LeftChild());
  }

  template <typename Data>
  void BinaryTreeVec<Data>::RemoveRightChild(struct NodeVec& node){
    if(node.HasRightChild())
      removeSubtree(node.RightChild());
  }

// Specific member functions (inherited from Container)
  template <typename Data>
  void BinaryTreeVec<Data>::Clear(){
    for(ulong i = 0; i < treeVec.Size(); i++)
      if(treeVec[i] != nullptr){
        delete treeVec[i];
        treeVec[i] = nullptr;
      }

    treeVec.Clear();

    for(int i = 0; i < 100; i++)
      heightVector[i] = 0;

    size = 0;
    treeHeight = 0;

    treeVec.Resize(7);
    for(int i = 0; i < 7; i++)
      treeVec[i] = nullptr;
  }

// Specific member functions (inherited from BreadthSearchableContainer)
  template <typename Data>
  void BinaryTreeVec<Data>::MapBreadth(MapFunctor func, void* par){
    for(ulong i = 0; i < treeVec.Size(); i++)
      if(treeVec[i] != nullptr)
        func(treeVec[i]->value, par);
  }

  template <typename Data>
  void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor func, const void* cPar, void* par) const{
    for(ulong i = 0; i < treeVec.Size(); i++)
      if(treeVec[i] != nullptr)
        func(treeVec[i]->value, cPar, par);
  }

// Accessory functions
  template <typename Data>
  void BinaryTreeVec<Data>::Expand(){
    ulong oldSize = treeVec.Size();
    treeVec.Resize(oldSize*2+1);

    for(ulong i = oldSize; i < treeVec.Size(); i++)
      treeVec[i] = nullptr;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::Reduce(){
    treeVec.Resize((treeVec.Size()-1)/2);
  }
