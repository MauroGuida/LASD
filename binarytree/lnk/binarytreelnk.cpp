// NodeLnk
  template <typename Data>
  Data& BinaryTreeLnk<Data>::NodeLnk::Element(){
    return value;
  }

  template <typename Data>
  const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const{
    return value;
  }

  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::IsLeaf() const noexcept{
    return !(HasLeftChild() && HasRightChild());
  }

  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::HasLeftChild() const noexcept{
    return (Left != nullptr);
  }

  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept{
    return (Right != nullptr);
  }

  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const{
    if(Left == nullptr)
      throw std::length_error("Empty Child!");

    return *Left;
  }

  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const{
    if(Right == nullptr)
      throw std::length_error("Empty Child!");

    return *Right;
  }

// BinaryTreeLnk
// Specific constructors
  // Copy
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const Data& copyValue){
    root = new NodeLnk(copyValue);
    size++;
  }

  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& copyTree){
    root = copySubtree(copyTree.root);
  }

  // Move
  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(Data&& moveValue) noexcept{
    root = new NodeLnk(std::move(moveValue));
    size++;
  }

  template <typename Data>
  BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& moveTree) noexcept{
    std::swap(moveTree.root, root);
    std::swap(moveTree.size, size);
  }

// Destructor
  template <typename Data>
  BinaryTreeLnk<Data>::~BinaryTreeLnk(){
    Clear();
  }

// Assignment
  // Copy
    template <typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& copyTree){
      Clear();

      root = copySubtree(copyTree.root);

      return *this;
    }

  // Move
    template <typename Data>
    BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& moveTree) noexcept{
      Clear();

      std::swap(moveTree.root, root);
      std::swap(moveTree.size, size);

      return *this;
    }

// Comparison operators
  // template <typename Data>
  // bool BinaryTreeLnk<Data>::operator==(const BinaryTree<Data>& comp) const noexcept{
  //   return BinaryTree<Data>::operator==(comp);
  // }
  //
  // template <typename Data>
  // bool BinaryTreeLnk<Data>::operator!=(const BinaryTree<Data>& comp) const noexcept{
  //   return !(*this == comp);
  // }

// Specific member functions (inherited from BinaryTree)
  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::Root() const{
    if(root == nullptr)
      throw std::length_error("Empty Tree!");

    return *root;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::NewRoot(const Data& copyValue){
    Clear();
    root = new struct NodeLnk(copyValue);
    size++;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::NewRoot(Data&& moveValue){
    Clear();
    root = new struct NodeLnk(std::move(moveValue));
    size++;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::AddLeftChild(struct NodeLnk& mainNode, const Data& newChildData){
    if(mainNode.HasLeftChild())
      RemoveLeftChild(mainNode);

    mainNode.Left = new struct NodeLnk(newChildData);
    size++;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::AddLeftChild(struct NodeLnk& mainNode, Data&& newChildData){
    if(mainNode.HasLeftChild())
      RemoveLeftChild(mainNode);

    mainNode.Left = new struct NodeLnk(std::move(newChildData));
    size++;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::AddRightChild(struct NodeLnk& mainNode, const Data& newChildData){
    if(mainNode.HasRightChild())
      RemoveRightChild(mainNode);

    mainNode.Right = new struct NodeLnk(newChildData);
    size++;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::AddRightChild(struct NodeLnk& mainNode, Data&& newChildData){
    if(mainNode.HasRightChild())
      RemoveRightChild(mainNode);

    mainNode.Right = new struct NodeLnk(std::move(newChildData));
    size++;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::RemoveLeftChild(struct NodeLnk& node){
    RemoveSubtree(node.Left);
    node.Left = nullptr;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::RemoveRightChild(struct NodeLnk& node){
    RemoveSubtree(node.Right);
    node.Right = nullptr;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::Clear(){
      RemoveSubtree(root);
      root = nullptr;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::RemoveSubtree(struct NodeLnk* node){
    if(node != nullptr){
      RemoveSubtree(node->Left);
      RemoveSubtree(node->Right);
      delete node;
      if(size > 0)
        size--;
    }
  }

  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::copySubtree(struct NodeLnk* copyTree){
    if(copyTree == nullptr)
      return nullptr;

    struct NodeLnk* tmp = new NodeLnk(copyTree->Element());
    tmp->Left = copySubtree(copyTree->Left);
    tmp->Right = copySubtree(copyTree->Right);

    size++;

    return tmp;
  }
