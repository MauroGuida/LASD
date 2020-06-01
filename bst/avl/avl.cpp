
namespace lasd {

template <typename Data>
struct AVL<Data>::AVLNode* AVL<Data>::AVLNode::Left(){
  return static_cast<struct AVLNode*>(BST<Data>::BSTNode::left);
}

template <typename Data>
const struct AVL<Data>::AVLNode* AVL<Data>::AVLNode::Left() const{
  return static_cast<struct AVLNode*>(BST<Data>::BSTNode::left);
}

template <typename Data>
struct AVL<Data>::AVLNode* AVL<Data>::AVLNode::Right(){
  return static_cast<struct AVLNode*>(BST<Data>::BSTNode::right);
}

template <typename Data>
const struct AVL<Data>::AVLNode* AVL<Data>::AVLNode::Right() const{
  return static_cast<struct AVLNode*>(BST<Data>::BSTNode::right);
}

/* ************************************************************************** */

// Copy constructor
template <typename Data>
  AVL<Data>::AVL(const AVL<Data>& copyFrom){
    root = copySubtree(static_cast<struct AVLNode*>(copyFrom.root));
  }

// Move constructor
  template <typename Data>
  AVL<Data>::AVL(AVL<Data>&& moveFrom) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(std::move(moveFrom)){

  }

// Copy assignment
  template <typename Data>
  AVL<Data>& AVL<Data>::operator=(const AVL<Data>& copyFrom){
    BinaryTreeLnk<Data>::Clear();

    root = copySubtree(static_cast<struct AVLNode*>(copyFrom.root));

    return *this;
  }

// Move assignment
  template <typename Data>
  AVL<Data>& AVL<Data>::operator=(AVL<Data>&& moveFrom) noexcept{
    return BinaryTreeLnk<Data>::operator=(std::move(moveFrom));
  }


// Specific member functions (inherited from BinaryTree)
  template <typename Data>
  struct AVL<Data>::AVLNode& AVL<Data>::Root() const{
    if(root == nullptr)
      throw std::length_error("Root does not Exists!");

    return *static_cast<struct AVLNode*>(root);
  }

  template <typename Data>
  void AVL<Data>::NewRoot(const Data& copyValue){
    BinaryTreeLnk<Data>::Clear();
    root = new struct AVL<Data>::AVLNode(copyValue);
    size++;
  }

  template <typename Data>
  void AVL<Data>::NewRoot(Data&& moveValue){
    BinaryTreeLnk<Data>::Clear();
    root = new struct AVL<Data>::AVLNode(std::move(moveValue));
    size++;
  }


// Specific member functions
  template <typename Data>
  void AVL<Data>::Insert(const Data& value){
    root = InsertNode(static_cast<struct AVLNode*>(root), value);
  }

  template <typename Data>
  void AVL<Data>::Insert(Data&& value){
    root = InsertNode(static_cast<struct AVLNode*>(root), std::move(value));
  }

  template <typename Data>
  void AVL<Data>::Remove(const Data& value){
    root = Remove(&Root(), value);
  }

  template <typename Data>
  Data AVL<Data>::MinNRemove(){
    Data min = BST<Data>::Min(&Root())->Element();
    root = Remove(&Root(), min);

    return min;
  }

  template <typename Data>
  void AVL<Data>::RemoveMin(){
    root = Remove(&Root(), BST<Data>::Min(&Root())->Element());
  }

  template <typename Data>
  Data AVL<Data>::MaxNRemove(){
    Data max = BST<Data>::Max(&Root())->Element();
    root = Remove(&Root(), max);

    return max;
  }

  template <typename Data>
  void AVL<Data>::RemoveMax(){
    root = Remove(&Root(), BST<Data>::Max(&Root())->Element());
  }

  template <typename Data>
  Data AVL<Data>::PredecessorNRemove(const Data& value){
    Data pred = BST<Data>::Predecessor(&Root(), value)->Element();
    root = Remove(&Root(), pred);

    return pred;
  }

  template <typename Data>
  void AVL<Data>::RemovePredecessor(const Data& value){
    root = Remove(&Root(), BST<Data>::Predecessor(&Root(), value)->Element());
  }

  template <typename Data>
  Data AVL<Data>::SuccessorNRemove(const Data& value){
    Data succ = BST<Data>::Successor(&Root(), value)->Element();
    root = Remove(&Root(), succ);

    return succ;
  }

  template <typename Data>
  void AVL<Data>::RemoveSuccessor(const Data& value){
    root = Remove(&Root(), BST<Data>::Successor(&Root(), value)->Element());
  }


/* ************************************************************************** */

  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::DetachMin(struct AVL<Data>::AVLNode* node, struct AVL<Data>::AVLNode* parent){
    struct AVLNode* ret = nullptr;
    struct AVLNode* newNode = nullptr;

    if(node != nullptr){
      if(node->Left() != nullptr){
        ret = DetachMin(node->Left(), node);
        node = BalanceR(node);
      }else{
        ret = node;
        newNode = node->Right();
      }
    }

    if(node == parent->Left())
      parent->left = newNode;
    else
      parent->right = newNode;

    return ret;
  }

  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::Remove(struct AVL<Data>::AVLNode* node, const Data& value){
    if(node != nullptr){
      if(node->Element() > value){
        node->left = Remove(node->Left(), value);
        node = BalanceR(node);
      }else if(node->Element() < value){
        node->right = Remove(node->Right(), value);
        node = BalanceL(node);
      }else if(node->Left() == nullptr || node->Right() == nullptr){
        struct AVLNode* tmp = nullptr;

        if(node->HasLeftChild()){
          tmp = node->Left();
          node->left = nullptr;
        }else if(node->HasRightChild()){
          tmp = node->Right();
          node->right = nullptr;
        }

        BST<Data>::Remove(*node);
        return tmp;
      }else{
        struct AVLNode* tmp = DetachMin(node->Right(), node);
        std::swap(node->Element(), tmp->Element());
        node = BalanceL(node);
        delete tmp;

        // Data tmp = BST<Data>::Min(static_cast<struct BST<Data>::BSTNode*>(node->right))->Element();
        //
        // struct AVLNode* oldNode = node;
        // node = Remove(node, tmp);
        //
        // std::swap(oldNode->Element(), tmp);
      }
    }

    return node;
  }

  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::InsertNode(struct AVL<Data>::AVLNode* node, const Data& value){
    if(node != nullptr){
      if(node->Element() < value){
        node->right = InsertNode(node->Right(), value);
        node = BalanceR(node);
      }else if(node->Element() > value){
        node->left = InsertNode(node->Left(), value);
        node = BalanceL(node);
      }
    }else{
      node = new struct AVLNode(value);
      size++;
    }

    return node;
  }

  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::InsertNode(struct AVL<Data>::AVLNode* node, Data&& value){
    if(node != nullptr){
      if(node->Element() < value){
        node->right = InsertNode(node->Right(), std::move(value));
        node = BalanceR(node);
      }else if(node->Element() > value){
        node->left = InsertNode(node->Left(), std::move(value));
        node = BalanceL(node);
      }
    }else{
      node = new struct AVLNode(std::move(value));
      size++;
    }

    return node;
  }


  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::BalanceL(struct AVL<Data>::AVLNode* node){
    if((getHeightST(node->Left()) - getHeightST(node->Right())) > 1){
      if(isSL(node->Left()))
        node = RotationSL(node);
      else
        node = RotationDL(node);
    }else
      node->heightST = 1 + max(getHeightST(node->Left()), getHeightST(node->Right()));

    return node;
  }

  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::BalanceR(struct AVL<Data>::AVLNode* node){
    if((getHeightST(node->Right()) - getHeightST(node->Left())) > 1){
      if(isSR(node->Right())){
        node = RotationSR(node);
      }else{
        node = RotationDR(node);
      }
    }else
      node->heightST = 1 + max(getHeightST(node->Left()), getHeightST(node->Right()));

    return node;
  }


  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::RotationSL(struct AVL<Data>::AVLNode* node){
    if(node != nullptr){
      struct AVLNode* leftChild = node->Left();
      if(leftChild != nullptr){
        struct AVLNode* rightNephew = leftChild->Right();
        leftChild->right = node;
        node->left = rightNephew;

        node->heightST = 1 + max(getHeightST(node->Left()), getHeightST(node->Right()));
        leftChild->heightST = 1 + max(getHeightST(leftChild->Left()), getHeightST(leftChild->Right()));

        node = leftChild;
      }
    }

    return node;
  }

  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::RotationSR(struct AVL<Data>::AVLNode* node){
    if(node != nullptr){
      struct AVLNode* rightChild = node->Right();
      if(rightChild != nullptr){
        struct AVLNode* leftNephew = rightChild->Left();
        rightChild->left = node;
        node->right = leftNephew;

        node->heightST = 1 + max(getHeightST(node->Right()), getHeightST(node->Left()));
        rightChild->heightST = 1 + max(getHeightST(rightChild->Right()), getHeightST(rightChild->Left()));

        node = rightChild;
      }
    }

    return node;
  }

  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::RotationDL(struct AVL<Data>::AVLNode* node){
    node->left = RotationSR(node->Left());
    return RotationSL(node);
  }

  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::RotationDR(struct AVL<Data>::AVLNode* node){
    node->right = RotationSL(node->Right());
    return RotationSR(node);
  }


  template <typename Data>
  bool AVL<Data>::isSL(struct AVL<Data>::AVLNode* node) const noexcept{
    return getHeightST(node->Left()) > getHeightST(node->Right());
  }

  template <typename Data>
  bool AVL<Data>::isSR(struct AVL<Data>::AVLNode* node) const noexcept{
    return getHeightST(node->Right()) > getHeightST(node->Left());
  }


  template <typename Data>
  long AVL<Data>::getHeightST(struct AVL<Data>::AVLNode* node) const noexcept{
    if(node == nullptr)
      return -1;
    else
      return node->heightST;
  }

  template <typename Data>
  long AVL<Data>::max(long a, long b){
    if(a > b)
      return a;

    return b;
  }

  template <typename Data>
  struct AVL<Data>::AVLNode* AVL<Data>::copySubtree(struct AVL<Data>::AVLNode* copyTree){
    if(copyTree == nullptr)
      return nullptr;

    struct AVLNode* tmp = new struct AVLNode(copyTree->Element());
    tmp->heightST = copyTree->heightST;

    tmp->left = copySubtree(copyTree->Left());
    tmp->right = copySubtree(copyTree->Right());

    size++;

    return tmp;
  }

}
