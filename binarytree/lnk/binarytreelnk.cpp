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
    return (left != nullptr);
  }

  template <typename Data>
  bool BinaryTreeLnk<Data>::NodeLnk::HasRightChild() const noexcept{
    return (right != nullptr);
  }

  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const{
    if(left == nullptr)
      throw std::length_error("Empty Child!");

    return *left;
  }

  template <typename Data>
  struct BinaryTreeLnk<Data>::NodeLnk& BinaryTreeLnk<Data>::NodeLnk::RightChild() const{
    if(right == nullptr)
      throw std::length_error("Empty Child!");

    return *right;
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

    mainNode.left = new struct NodeLnk(newChildData);
    size++;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::AddLeftChild(struct NodeLnk& mainNode, Data&& newChildData){
    if(mainNode.HasLeftChild())
      RemoveLeftChild(mainNode);

    mainNode.left = new struct NodeLnk(std::move(newChildData));
    size++;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::AddRightChild(struct NodeLnk& mainNode, const Data& newChildData){
    if(mainNode.HasRightChild())
      RemoveRightChild(mainNode);

    mainNode.right = new struct NodeLnk(newChildData);
    size++;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::AddRightChild(struct NodeLnk& mainNode, Data&& newChildData){
    if(mainNode.HasRightChild())
      RemoveRightChild(mainNode);

    mainNode.right = new struct NodeLnk(std::move(newChildData));
    size++;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::RemoveLeftChild(struct NodeLnk& node){
    RemoveSubtree(node.left);
    node.left = nullptr;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::RemoveRightChild(struct NodeLnk& node){
    RemoveSubtree(node.right);
    node.right = nullptr;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::Clear(){
      RemoveSubtree(root);
      root = nullptr;
  }

  template <typename Data>
  void BinaryTreeLnk<Data>::RemoveSubtree(struct NodeLnk* node){
    if(node != nullptr){
      RemoveSubtree(node->left);
      RemoveSubtree(node->right);
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
    tmp->left = copySubtree(copyTree->left);
    tmp->right = copySubtree(copyTree->right);

    size++;

    return tmp;
  }
