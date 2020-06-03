
namespace lasd {

/* ************************************************************************** */

  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::RBNode::Left(){
    return static_cast<struct RBNode*>(BinaryTreeLnk<Data>::NodeLnk::left);
  }

  template <typename Data>
  const struct RB<Data>::RBNode* RB<Data>::RBNode::Left() const{
    return static_cast<struct RBNode*>(BinaryTreeLnk<Data>::NodeLnk::left);
  }

  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::RBNode::Right(){
    return static_cast<struct RBNode*>(BinaryTreeLnk<Data>::NodeLnk::right);
  }

  template <typename Data>

  const struct RB<Data>::RBNode* RB<Data>::RBNode::Right() const{
    return static_cast<struct RBNode*>(BinaryTreeLnk<Data>::NodeLnk::right);
  }


/* ************************************************************************** */

  // Copy constructor
  template <typename Data>
  RB<Data>::RB(const RB& copyFrom) : BinaryTreeLnk<Data>::BinaryTreeLnk(copyFrom){
    root = copySubtree(static_cast<struct RBNode*>(copyFrom.root));
  }

  // Move constructor
  template <typename Data>
  RB<Data>::RB(RB&& moveFrom) noexcept : BinaryTreeLnk<Data>::BinaryTreeLnk(moveFrom){

  }

  // Copy assignment
  template <typename Data>
  RB<Data>& RB<Data>::operator=(const RB<Data>& copyFrom){
    BinaryTreeLnk<Data>::Clear();

    root = copySubtree(static_cast<struct RBNode*>(copyFrom.root));

    return *this;
  }

  // Move assignment
  template <typename Data>
  RB<Data>& RB<Data>::operator=(RB<Data>&& moveFrom) noexcept{
    return BinaryTreeLnk<Data>::operator=(std::move(moveFrom));
  }


  template <typename Data>
  struct RB<Data>::RBNode& RB<Data>::Root() const{
    if(!root)
      throw std::length_error("Root does not Exists!");

    return *static_cast<struct RBNode*>(root);
  }

  template <typename Data>
  void RB<Data>::NewRoot(const Data& copyValue){
    BinaryTreeLnk<Data>::Clear();
    root = new struct RB<Data>::RBNode(copyValue);
    Root().color = black;

    size++;
  }

  template <typename Data>
  void RB<Data>::NewRoot(Data&& moveValue){
    BinaryTreeLnk<Data>::Clear();
    root = new struct RB<Data>::RBNode(std::move(moveValue));
    Root().color = black;

    size++;
  }


  template <typename Data>
  void RB<Data>::Insert(const Data& value){
    root = InsertNode(static_cast<struct RBNode*>(root), value);
    Root().color = black;
  }

  template <typename Data>
  void RB<Data>::Insert(Data&& value){
    root = InsertNode(static_cast<struct RBNode*>(root), std::move(value));
    Root().color = black;
  }


  template <typename Data>
  void RB<Data>::Remove(const Data& value){
    root = Remove(static_cast<struct RBNode*>(root), value);
    if(root)
      Root().color = black;
  }


  template <typename Data>
  Data RB<Data>::MinNRemove(){
    Data min = BST<Data>::Min(&Root())->Element();
    root = Remove(&Root(), min);

    return min;
  }

  template <typename Data>
  void RB<Data>::RemoveMin(){
    root = Remove(&Root(), BST<Data>::Min(&Root())->Element());
  }


  template <typename Data>
  Data RB<Data>::MaxNRemove(){
    Data max = BST<Data>::Max(&Root())->Element();
    root = Remove(&Root(), max);

    return max;
  }

  template <typename Data>
  void RB<Data>::RemoveMax(){
    root = Remove(&Root(), BST<Data>::Max(&Root())->Element());
  }


  template <typename Data>
  Data RB<Data>::PredecessorNRemove(const Data& value){
    Data pred = BST<Data>::Predecessor(&Root(), value)->Element();
    root = Remove(&Root(), pred);

    return pred;
  }

  template <typename Data>
  void RB<Data>::RemovePredecessor(const Data& value){
    root = Remove(&Root(), BST<Data>::Predecessor(&Root(), value)->Element());
  }


  template <typename Data>
  Data RB<Data>::SuccessorNRemove(const Data& value){
    Data succ = BST<Data>::Successor(&Root(), value)->Element();
    root = Remove(&Root(), succ);

    return succ;
  }

  template <typename Data>
  void RB<Data>::RemoveSuccessor(const Data& value){
    root = Remove(&Root(), BST<Data>::Successor(&Root(), value)->Element());
  }


/* ************************************************************************** */

  // Insert
  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::InsertNode(struct RB<Data>::RBNode* node, const Data& copyValue){
    if(node){
      if(copyValue < node->Element()){
        node->left = InsertNode(node->Left(), copyValue);
        node = BalanceL(node);
      }else if(copyValue > node->Element()){
        node->right = InsertNode(node->Right(), copyValue);
        node = BalanceR(node);
      }
    }else{
      node = new struct RBNode(copyValue);
      size++;
    }

    return node;
  }

  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::InsertNode(struct RB<Data>::RBNode* node, Data&& moveValue){
    if(node){
      if(moveValue < node->Element()){
        node->left = InsertNode(node->Left(), std::move(moveValue));
        node = BalanceL(node);
      }else if(moveValue > node->Element()){
        node->right = InsertNode(node->Right(), std::move(moveValue));
        node = BalanceR(node);
      }
    }else{
      node = new struct RBNode(std::move(moveValue));
      size++;
    }

    return node;
  }


  template <typename Data>
  int RB<Data>::ViolationTypeL(struct RB<Data>::RBNode* nodeL, struct RB<Data>::RBNode* nodeR){
    int violation = 0;
    if((nodeL && nodeL->color == red) && (nodeR && nodeR->color == red)){
      if((nodeL->HasLeftChild() && nodeL->Left()->color == red) || (nodeL->HasRightChild() && nodeL->Right()->color == red))
        violation = 1;
    }else
      if(nodeL && nodeL->color == red){
        if(nodeL->HasRightChild() && nodeL->Right()->color == red)
          violation = 2;
        else if(nodeL->HasLeftChild() && nodeL->Left()->color == red)
          violation = 3;
      }

    return violation;
  }

  template <typename Data>
  int RB<Data>::ViolationTypeR(struct RB<Data>::RBNode* nodeL, struct RB<Data>::RBNode* nodeR){
    int violation = 0;
    if((nodeL && nodeL->color == red) && (nodeR && nodeR->color == red)){
      if((nodeR->HasRightChild() && nodeR->Right()->color == red) || (nodeR->HasLeftChild() && nodeR->Left()->color == red))
        violation = 1;
    }else
      if(nodeR && nodeR->color == red){
        if(nodeR->HasLeftChild() && nodeR->Left()->color == red)
          violation = 2;
        else if(nodeR->HasRightChild() && nodeR->Right()->color == red)
          violation = 3;
      }

    return violation;
  }


  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::BalanceL(struct RB<Data>::RBNode* node){
    int violation;
    if(node->HasRightChild() || node->HasLeftChild())
      violation = ViolationTypeL(node->Left(), node->Right());
      switch(violation){
        case 1:{
          node = BalanceL_1(node);
          break;
        }case 2:{
          node = BalanceL_2(node);
          break;
        }case 3:{
          node = BalanceL_3(node);
          break;
        }
      }

    return node;
  }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::BalanceL_1(struct RB<Data>::RBNode* node){
      node->Left()->color = black;
      node->color = red;
      node->Right()->color = black;

      return node;
    }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::BalanceL_2(struct RB<Data>::RBNode* node){
      node->left = RotationR(node->Left());
      return BalanceL_3(node);
    }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::BalanceL_3(struct RB<Data>::RBNode* node){
      node = RotationL(node);
      node->color = black;
      node->Right()->color = red;

      return node;
    }

  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::BalanceR(struct RB<Data>::RBNode* node){
    int violation;
    if(node->HasRightChild() || node->HasLeftChild())
      violation = ViolationTypeR(node->Left(), node->Right());
      switch(violation){
        case 1:{
          node = BalanceR_1(node);
          break;
        }case 2:{
          node = BalanceR_2(node);
          break;
        }case 3:{
          node = BalanceR_3(node);
          break;
        }
      }

    return node;
  }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::BalanceR_1(struct RB<Data>::RBNode* node){
      node->Right()->color = black;
      node->color = red;
      node->Left()->color = black;

      return node;
    }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::BalanceR_2(struct RB<Data>::RBNode* node){
      node->right = RotationL(node->Right());
      return BalanceR_3(node);
    }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::BalanceR_3(struct RB<Data>::RBNode* node){
      node = RotationR(node);
      node->color = black;
      node->Left()->color = red;

      return node;
    }


  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::RotationR(struct RB<Data>::RBNode* node){
    struct RBNode* rightChild = node->Right();
    node->right = rightChild->Left();
    rightChild->left = node;

    return rightChild;
  }

  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::RotationL(struct RB<Data>::RBNode* node){
    struct RBNode* leftChild = node->Left();
    node->left = leftChild->Right();
    leftChild->right = node;

    return leftChild;
  }


  // Remove
  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::Remove(struct RB<Data>::RBNode* node, const Data& value){
    if(node){
      if(node->Element() < value){
        node->right = Remove(node->Right(), value);
        node = removeBalanceR(node);
      }else if(node->Element() > value){
        node->left = Remove(node->Left(), value);
        node = removeBalanceL(node);
      }else{
        node = removeRoot(node);
        size --;
      }
    }

    return node;
  }


  template <typename Data>
  int RB<Data>::removeViolationTypeL(struct RB<Data>::RBNode* nodeL, struct RB<Data>::RBNode* nodeR){
    int violation = 0;
    if(nodeL && nodeL->color == dblack){
      if(nodeR && nodeR->color == red)
        violation = 1;
      else if(nodeR && (nodeR->HasRightChild() && nodeR->Right()->color == black) && (nodeR->HasLeftChild() && nodeR->Left()->color == black))
        violation = 2;
      else if(nodeR && nodeR->HasRightChild() && nodeR->Right()->color == black)
        violation = 3;
      else
        violation = 4;
    }

    return violation;
  }

  template <typename Data>
  int RB<Data>::removeViolationTypeR(struct RB<Data>::RBNode* nodeL, struct RB<Data>::RBNode* nodeR){
    int violation = 0;
    if(nodeR && nodeR->color == dblack){
      if(nodeL && nodeL->color == red)
        violation = 1;
      else if(nodeL && (nodeL->HasRightChild() && nodeL->Right()->color == black) && (nodeL->HasLeftChild() && nodeL->Left()->color == black))
        violation = 2;
      else if(nodeL && nodeL->HasRightChild() && nodeL->Right()->color == black)
        violation = 3;
      else
        violation = 4;
    }

    return violation;
  }


  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::removeBalanceL(struct RB<Data>::RBNode* node){
    if(node->HasLeftChild() || node->HasRightChild()){
      int violation = removeViolationTypeL(node->Left(), node->Right());
      switch(violation){
        case 1:{
          node = removeBalanceL_1(node);
          node->left = removeBalanceL(node->Left());
          break;
        }case 2:{
          node = removeBalanceL_2(node);
          break;
        }case 3:{
          node = removeBalanceL_3(node);
          break;
        }case 4:{
          node = removeBalanceL_4(node);
        }
      }
    }

    return node;
  }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::removeBalanceL_1(struct RB<Data>::RBNode* node){
      node = RotationR(node);
      node->color = black;
      node->Left()->color = red;

      return node;
    }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::removeBalanceL_2(struct RB<Data>::RBNode* node){
      node->Right()->color = red;
      node->Left()->color = black;
      propagateBlack(node);

      return node;
    }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::removeBalanceL_3(struct RB<Data>::RBNode* node){
      node->right = RotationL(node->Right());
      node->Right()->color = black;
      node->Right()->Right()->color = red;
      node = removeBalanceL_4(node);

      return node;
    }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::removeBalanceL_4(struct RB<Data>::RBNode* node){
      node = RotationL(node);
      node->Right()->color = node->color;
      node->color = node->Left()->color;
      node->Left()->color = black;
      node->Left()->Left()->color = black;

      return node;
    }


    template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::removeBalanceR(struct RB<Data>::RBNode* node){
    if(node->HasLeftChild() || node->HasRightChild()){
      int violation = removeViolationTypeR(node->Left(), node->Right());
      switch(violation){
        case 1:{
          node = removeBalanceR_1(node);
          node->right = removeBalanceR(node->Right());
          break;
        }case 2:{
          node = removeBalanceR_2(node);
          break;
        }case 3:{
          node = removeBalanceR_3(node);
          break;
        }case 4:{
          node = removeBalanceR_4(node);
        }
      }
    }

    return node;
  }

  template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::removeBalanceR_1(struct RB<Data>::RBNode* node){
      node = RotationL(node);
      node->color = black;
      node->Right()->color = red;

      return node;
    }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::removeBalanceR_2(struct RB<Data>::RBNode* node){
      node->Left()->color = red;
      node->Right()->color = black;
      propagateBlack(node);

      return node;
    }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::removeBalanceR_3(struct RB<Data>::RBNode* node){
      node->left = RotationR(node->Left());
      node->Left()->color = black;
      node->Left()->Left()->color = red;
      node = removeBalanceR_4(node);

      return node;
    }

    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::removeBalanceR_4(struct RB<Data>::RBNode* node){
      node = RotationR(node);
      node->Left()->color = node->color;
      node->color = node->Right()->color;
      node->Right()->color = black;
      node->Right()->Right()->color = black;

      return node;
    }


    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::removeRoot(struct RB<Data>::RBNode* node){
      struct RBNode* tmp;

      if(!node->Left() || !node->Right()){
        tmp = node;

        if(!node->Left())
          node = node->Right();
        else if(!node->Right())
          node = node->Left();

        if(tmp->color == black)
          propagateBlack(node);
      }else{
        tmp = DetachMin(node->Right(), node);
        node->Element() = tmp->Element();
        node = removeBalanceR(node);

        delete tmp;
      }

      return node;
    }


    template <typename Data>
    struct RB<Data>::RBNode* RB<Data>::DetachMin(struct RB<Data>::RBNode* node, struct RB<Data>::RBNode* parent){
      struct RBNode* tmp;

      if(node){
        if(node->Left()){
          tmp = DetachMin(node->Left(), node);
          if(node == parent->Left())
            parent->left = removeBalanceL(node);
          else
            parent->right = removeBalanceR(node);

          node = tmp;
        }else{
          tmp = node;
          if(node == parent->Left())
            parent->left = node->Right();
          else
            parent->right = node->Right();

          if(node->color == black)
            propagateBlack(node->Right());
        }
      }

      return tmp;
    }


    template <typename Data>
    void RB<Data>::propagateBlack(struct RB<Data>::RBNode* node){
      if(!node)
        return;

      if(node->color == red)
        node->color = black;
      else
        node->color = dblack;
    }


  // Accessory
  template <typename Data>
  struct RB<Data>::RBNode* RB<Data>::copySubtree(struct RB<Data>::RBNode* copyTree){
    if(!copyTree)
      return nullptr;

    struct RBNode* tmp = new struct RBNode(copyTree->Element());
    tmp->color = copyTree->color;

    tmp->left = copySubtree(copyTree->Left());
    tmp->right = copySubtree(copyTree->Right());

    size++;

    return tmp;
  }

}
