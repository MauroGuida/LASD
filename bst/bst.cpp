
namespace lasd {

/* ************************************************************************** */

template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::Left(){
  return static_cast<struct BSTNode*>(BinaryTreeLnk<Data>::NodeLnk::left);
}

template <typename Data>
const struct BST<Data>::BSTNode* BST<Data>::BSTNode::Left() const{
  return static_cast<struct BSTNode*>(BinaryTreeLnk<Data>::NodeLnk::left);
}

template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::Right(){
  return static_cast<struct BSTNode*>(BinaryTreeLnk<Data>::NodeLnk::right);
}

template <typename Data>
const struct BST<Data>::BSTNode* BST<Data>::BSTNode::Right() const{
  return static_cast<struct BSTNode*>(BinaryTreeLnk<Data>::NodeLnk::right);
}

template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::Find(struct BSTNode* node, const Data& SearchValue) const{
  struct BSTNode* tmp = nullptr;
  if(node != nullptr){
    if(node->value == SearchValue)
      tmp = node;
    else
      if(node->value < SearchValue)
        tmp = Find(node->Right(), SearchValue);
      else
        tmp = Find(node->Left(), SearchValue);
  }

  return tmp;
}

template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::FindParent(struct BSTNode* node, const Data& SearchValue) const{
  if(node != nullptr && node->value != SearchValue)
    while (node != nullptr && !node->IsLeaf()) {
      if(node->HasLeftChild())
        if(node->LeftChild()->value == SearchValue)
          return node;

      if(node->HasRightChild())
        if(node->RightChild()->value == SearchValue)
          return node;


      if(SearchValue > node->value)
        node = node->Right();
      else
        node = node->Left();
    }

  return nullptr;
}


template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::MinParent() const{
  struct BSTNode* tmp = this;
  while(tmp->Left() != nullptr)
      tmp = tmp->Left();

  return FindParent(this, tmp->value);
}

template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::MaxParent() const{
  struct BSTNode* tmp = this;
  while(tmp->Right() != nullptr)
      tmp = tmp->Right();

  return FindParent(this, tmp->value);
}


template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::PredecessorParent(const Data& value) const{

}

template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::SuccessorParent(const Data& value) const{

}


/* ************************************************************************** */

// Copy constructor
  template <typename Data>
  BST<Data>::BST(const Data& copyFrom) : BinaryTreeLnk<Data>::BinaryTreeLnk(copyFrom){

  }

// Move constructor
  template <typename Data>
  BST<Data>::BST(Data&& moveFrom) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(moveFrom)){

  }

// Copy assignment
  template <typename Data>
  BST<Data>& BST<Data>::operator=(const BST<Data>& copyFrom){
    return BinaryTreeLnk<Data>::operator=(copyFrom);
  }

// Move assignment
  template <typename Data>
  BST<Data>& BST<Data>::operator=(BST<Data>&& moveFrom) noexcept{
    return BinaryTreeLnk<Data>::operator=(std::move(moveFrom));
  }

// Comparison operators
  template <typename Data>
  bool BST<Data>::operator==(const BST<Data>& comp) const noexcept{
    if(comp.size == this.size){
      QueueLst<Data>& q1 = this.enqueueTreeInOrder();
      QueueLst<Data>& q2 = comp.enqueueTreeInOrder();

      return q1==q2;
    }

    return false;
  }

  template <typename Data>
  bool BST<Data>::operator!=(const BST<Data>& comp) const noexcept{
    return !(*this == comp);
  }

// Specific member functions (inherited from BinaryTree)
  template <typename Data>
  struct BST<Data>::BSTNode& BST<Data>::Root() const{
    if(size == 0)
      throw std::length_error("Empty BST!");

    return *static_cast<struct BSTNode*>(root);
  }

  template <typename Data>
  void BST<Data>::NewRoot(const Data& copyValue){
    BinaryTreeLnk<Data>::Clear();
    root = new struct BST<Data>::BSTNode(copyValue);
    size++;
  }

  template <typename Data>
  void BST<Data>::NewRoot(Data&& moveValue){
    BinaryTreeLnk<Data>::Clear();
    root = new struct BST<Data>::BSTNode(std::move(moveValue));
    size++;
  }

// Specific member functions
  template <typename Data>
  void BST<Data>::Insert(const Data& copyValue){
    root = InsertNode(static_cast<struct BSTNode*>(root), copyValue);
    size++;
  }

  template <typename Data>
  void BST<Data>::Insert(Data&& moveValue){
    root = InsertNode(static_cast<struct BSTNode*>(root), std::move(moveValue));
    size++;
  }


  template <typename Data>
  void BST<Data>::Remove(const Data& value){

  }


  template <typename Data>
  struct BST<Data>::BSTNode& BST<Data>::Min() const{
  }

  template <typename Data>
  Data BST<Data>::MinNRemove(){
  }

  template <typename Data>
  void BST<Data>::RemoveMin(){
  }


  template <typename Data>
  struct BST<Data>::BSTNode& BST<Data>::Max() const{
  }

  template <typename Data>
  Data BST<Data>::MaxNRemove(){
  }

  template <typename Data>
  void BST<Data>::RemoveMax(){
  }


  template <typename Data>
  struct BST<Data>::BSTNode& BST<Data>::Predecessor(const Data& value) const{
  }

  template <typename Data>
  Data BST<Data>::PredecessorNRemove(const Data& value){
  }

  template <typename Data>
  void BST<Data>::RemovePredecessor(const Data& value){
  }


  template <typename Data>
  struct BST<Data>::BSTNode& BST<Data>::Successor(const Data& value) const{
  }

  template <typename Data>
  Data BST<Data>::SuccessorNRemove(const Data& value){
  }

  template <typename Data>
  void BST<Data>::RemoveSuccessor(const Data& value){
  }

// Specific member functions (inherited from TestableContainer)
  template <typename Data>
  bool BST<Data>::Exists(const Data& value) const noexcept{
    if(size <= 0)
      return false;

    return Search(static_cast<struct BSTNode*>(root), value);
  }

/* ************************************************************************** */

  template <typename Data>
  QueueLst<Data>& BST<Data>::enqueueTreeInOrder(){
    QueueLst<Data> Q1;

    this.MapInOrder(&mapEnqueueTree, &Q1);

    return Q1;
  }

    template <typename Data>
    void BST<Data>::mapEnqueueTree(Data& elem, void* q){
      (*(QueueLst<Data>*)q).Enqueue(elem);
    }

  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::InsertNode(struct BSTNode* node, const Data& copyValue){
    if(node == nullptr)
      node = new struct BSTNode(copyValue);
    else{
      if(copyValue < node->Element())
        node->left = InsertNode(node->Left(), copyValue);
      else if(copyValue > node->Element())
        node->right = InsertNode(node->Right(), copyValue);
    }

    return node;
  }

  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::InsertNode(struct BSTNode* node, Data&& moveValue){
    if(node == nullptr)
      node = new struct BSTNode(std::move(moveValue));
    else{
      if(moveValue < node->Element())
        node->left = InsertNode(node->Left(), std::move(moveValue));
      else if(moveValue > node->Element())
        node->right = InsertNode(node->Right(), std::move(moveValue));
    }

    return node;
  }

  template <typename Data>
  bool BST<Data>::Search(struct BSTNode* node, const Data& value) const noexcept{
    bool ret = false;
    if(node != nullptr){
      if(value == node->Element())
        ret = true;
      else{
        if(value < node->Element())
          ret = Search(node->Left(), value);
        else if(value > node->Element())
          ret = Search(node->Right(), value);
      }
    }

    return ret;
  }

}
