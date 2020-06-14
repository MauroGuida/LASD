
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

/* ************************************************************************** */

// Copy constructor
  template <typename Data>
  BST<Data>::BST(const BST& copyFrom) : BinaryTreeLnk<Data>::BinaryTreeLnk(copyFrom){

  }

// Move constructor
  template <typename Data>
  BST<Data>::BST(BST&& moveFrom) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(moveFrom)){

  }

// Copy assignment
  template <typename Data>
  BST<Data>& BST<Data>::operator=(const BST<Data>& copyFrom){
    BinaryTreeLnk<Data>::Clear();
    BinaryTreeLnk<Data>::operator=(copyFrom);
    return *this;
  }

// Move assignment
  template <typename Data>
  BST<Data>& BST<Data>::operator=(BST<Data>&& moveFrom) noexcept{
    BinaryTreeLnk<Data>::operator=(std::move(moveFrom));
    return *this;
  }

// Comparison operators
  template <typename Data>
  bool BST<Data>::operator==(const BST<Data>& comp) const noexcept{
    bool res = false;
    if(comp.size == size){
      QueueVec<Data>* q1 = enqueueTreeInOrder();
      QueueVec<Data>* q2 = comp.enqueueTreeInOrder();

      res = *q1==*q2;
      delete q1;
      delete q2;
    }

    return res;
  }

  template <typename Data>
  bool BST<Data>::operator!=(const BST<Data>& comp) const noexcept{
    return !(*this == comp);
  }

// Specific member functions (inherited from BinaryTree)
  template <typename Data>
  struct BST<Data>::BSTNode& BST<Data>::Root() const{
    if(root == nullptr)
      throw std::length_error("Root does not Exists!");

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
  }

  template <typename Data>
  void BST<Data>::Insert(Data&& moveValue){
    root = InsertNode(static_cast<struct BSTNode*>(root), std::move(moveValue));
  }


  template <typename Data>
  void BST<Data>::Remove(const Data& value){
    struct BSTNode* del = Search(static_cast<struct BSTNode*>(root), value);

    if(del != nullptr)
      Remove(del);
  }


  template <typename Data>
  const Data& BST<Data>::Min() const{
    return Min(&Root())->Element();
  }

  template <typename Data>
  Data BST<Data>::MinNRemove(){
    BSTNode* min = Min(&Root());
    Data ret = min->Element();
    Remove(min);

    return ret;
  }

  template <typename Data>
  void BST<Data>::RemoveMin(){
    Remove(Min(&Root()));
  }


  template <typename Data>
  const Data& BST<Data>::Max() const{
    return Max(&Root())->Element();
  }

  template <typename Data>
  Data BST<Data>::MaxNRemove(){
    BSTNode* max = Max(&Root());
    Data ret = max->Element();
    Remove(max);

    return ret;
  }

  template <typename Data>
  void BST<Data>::RemoveMax(){
    Remove(Max(&Root()));
  }


  template <typename Data>
  const Data& BST<Data>::Predecessor(const Data& value) const{
    return Predecessor(&Root(), value)->Element();
  }

  template <typename Data>
  Data BST<Data>::PredecessorNRemove(const Data& value){
    struct BSTNode* pred = Predecessor(&Root(), value);
    Data retValue = pred->Element();
    Remove(pred);

    return retValue;
  }

  template <typename Data>
  void BST<Data>::RemovePredecessor(const Data& value){
    Remove(Predecessor(&Root(), value));
  }


  template <typename Data>
  const Data& BST<Data>::Successor(const Data& value) const{
    return Successor(&Root(), value)->Element();
  }

  template <typename Data>
  Data BST<Data>::SuccessorNRemove(const Data& value){
    struct BSTNode* succ = Successor(&Root(), value);
    Data retValue = succ->Element();
    Remove(succ);

    return retValue;
  }

  template <typename Data>
  void BST<Data>::RemoveSuccessor(const Data& value){
    Remove(Successor(&Root(), value));
  }

// Specific member functions (inherited from TestableContainer)
  template <typename Data>
  bool BST<Data>::Exists(const Data& value) const noexcept{
    return Search(&Root(), value) != nullptr;
  }


/* ************************************************************************ */


  template <typename Data>
  void BST<Data>::Remove(struct BSTNode* del){
    if(del->HasLeftChild() && del->HasRightChild()){
      struct BSTNode* tmp = Min(del->Right());
      Data savedValue = tmp->Element();

      Remove(tmp);
      del->Element() = savedValue;
    }else{
      struct BSTNode* parent = SearchParent(&Root(), del->Element());

      if(del->IsLeaf()){
        if(parent == nullptr)
          BinaryTreeLnk<Data>::Clear();
        else if(parent->HasLeftChild() && parent->left->Element() == del->Element())
          BinaryTreeLnk<Data>::RemoveLeftChild(*parent);
        else if(parent->HasRightChild() && parent->right->Element() == del->Element())
          BinaryTreeLnk<Data>::RemoveRightChild(*parent);
      }else if(del->HasLeftChild() ^ del->HasRightChild()){
        if(parent == nullptr){
          if(del->HasLeftChild()){
            root = del->Left();
            delete del;
          }else{
            root = del->Right();
            delete del;
          }
        }else if(parent->HasLeftChild() && parent->left->Element() == del->Element()){
          if(del->HasLeftChild())
            parent->left = SkipOnLeft(parent->Left());
          else
            parent->left = SkipOnRight(parent->Left());
        }else if(parent->HasRightChild() && parent->right->Element() == del->Element()){
          if(del->HasLeftChild())
            parent->right = SkipOnLeft(parent->Right());
          else
            parent->right = SkipOnRight(parent->Right());
        }
        size--;
      }
    }
  }


  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::SkipOnLeft(struct BSTNode* node){
    struct BSTNode* Left = static_cast<struct BSTNode*>(node->left);

    delete node;
    // size--;

    return Left;
  }

  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::SkipOnRight(struct BSTNode* node){
    struct BSTNode* Right = static_cast<struct BSTNode*>(node->right);

    delete node;
    // size--;

    return Right;
  }


  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::Search(struct BSTNode* node, const Data& value) const noexcept{
    struct BSTNode* ret = node;
    if(ret != nullptr && value != node->Element()){
      if(value < node->Element())
        ret = Search(node->Left(), value);
      else if(value > node->Element())
        ret = Search(node->Right(), value);
    }

    return ret;
  }

  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::SearchParent(struct BSTNode* node, const Data& value) const noexcept{
    if(node != nullptr && node->Element() != value)
      while (node != nullptr && !node->IsLeaf()) {
        if(node->HasLeftChild())
          if(node->Left()->Element() == value)
            return node;

        if(node->HasRightChild())
          if(node->Right()->Element() == value)
            return node;


        if(value > node->Element())
          node = node->Right();
        else
          node = node->Left();
      }

    return nullptr;
  }


  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::Min(struct BSTNode* node) const{
    while(node->Left() != nullptr)
        node = node->Left();

    return node;
  }

  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::Max(struct BSTNode* node) const{
    while(node->Right() != nullptr)
        node = node->Right();

    return node;
  }


  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::Predecessor(struct BSTNode* node, const Data& value) const{
    struct BSTNode* ret = Predecessor_IT(node, value, nullptr);
    if(ret == nullptr)
      throw std::length_error("Predecessor does not Exists!");

    return ret;
  }

  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::Successor(struct BSTNode* node, const Data& value) const{
    struct BSTNode* ret = Successor_IT(node, value, nullptr);
    if(ret == nullptr)
      throw std::length_error("Successor does not Exists!");

    return ret;
  }

/* ************************************************************************** */

  template <typename Data>
  QueueVec<Data>* BST<Data>::enqueueTreeInOrder() const{
    QueueVec<Data>* Q1 = new QueueVec<Data>();

    InOrderEnqueueTree(Q1, static_cast<struct BSTNode*>(root));

    return Q1;
  }

    template <typename Data>
    void BST<Data>::InOrderEnqueueTree(QueueVec<Data>* Q, struct BSTNode* node) const{
      if(node == nullptr)
        return;

      if(node->HasLeftChild())
        InOrderEnqueueTree(Q, node->Left());

      Q->Enqueue(node->Element());

      if(node->HasRightChild())
        InOrderEnqueueTree(Q, node->Right());
    }


  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::Predecessor_IT(struct BSTNode* node, const Data& value, struct BSTNode* candidate) const noexcept{
    struct BSTNode* ret = candidate;
    if(node != nullptr)
      if(node->Element() == value){
        if(node->Left() != nullptr)
          ret = Max(node->Left());
      }else{
        if(value > node->Element())
          ret = Predecessor_IT(node->Right(), value, node);
        else if(value < node->Element())
          ret = Predecessor_IT(node->Left(), value, candidate);
      }

    return ret;
  }

  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::Successor_IT(struct BSTNode* node, const Data& value, struct BSTNode* candidate) const noexcept{
    struct BSTNode* ret = candidate;
    if(node != nullptr)
      if(node->Element() == value){
        if(node->Right() != nullptr)
          ret = Min(node->Right());
      }else{
        if(value > node->Element())
          ret = Successor_IT(node->Right(), value, ret);
        else if(value < node->Element())
          ret = Successor_IT(node->Left(), value, node);
      }

    return ret;
  }


  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::InsertNode(struct BSTNode* node, const Data& copyValue){
    if(node == nullptr){
      node = new struct BSTNode(copyValue);
      size++;
    }else{
      if(copyValue < node->Element())
        node->left = InsertNode(node->Left(), copyValue);
      else if(copyValue > node->Element())
        node->right = InsertNode(node->Right(), copyValue);
    }

    return node;
  }

  template <typename Data>
  struct BST<Data>::BSTNode* BST<Data>::InsertNode(struct BSTNode* node, Data&& moveValue){
    if(node == nullptr){
      node = new struct BSTNode(std::move(moveValue));
      size++;
    }else{
      if(moveValue < node->Element())
        node->left = InsertNode(node->Left(), std::move(moveValue));
      else if(moveValue > node->Element())
        node->right = InsertNode(node->Right(), std::move(moveValue));
    }

    return node;
  }

}
