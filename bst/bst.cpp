
namespace lasd {

/* ************************************************************************** */

template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::Left(){
  return static_cast<struct BSTNode*>(BinaryTreeLnk<Data>::NodeLnk::Left);
}

template <typename Data>
const struct BST<Data>::BSTNode* BST<Data>::BSTNode::Left() const{
  return static_cast<struct BSTNode*>(BinaryTreeLnk<Data>::NodeLnk::Left);
}

template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::Right(){
  return static_cast<struct BSTNode*>(BinaryTreeLnk<Data>::NodeLnk::Right);
}

template <typename Data>
const struct BST<Data>::BSTNode* BST<Data>::BSTNode::Right() const{
  return static_cast<struct BSTNode*>(BinaryTreeLnk<Data>::NodeLnk::Right);
}

template <typename Data>
struct BST<Data>::BSTNode* BST<Data>::BSTNode::Find(struct BSTNode* node, const Data& SearchValue) const{
  struct BSTNode* tmp = nullptr;
  if(node != nullptr){
    if(node->value == SearchValue)
      tmp = node;
    else
      if(node->value < SearchValue)
        tmp = Find(node->Right, SearchValue);
      else
        tmp = Find(node->Left, SearchValue);
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
  BST& BST<Data>::operator=(const BST<Data>& copyFrom){
    return BinaryTreeLnk<Data>::operator=(copyFrom);
  }

// Move assignment
  template <typename Data>
  BST& BST<Data>::operator=(BST<Data>&& moveFrom) noexcept{
    return BinaryTreeLnk<Data>::operator=(std::move(moveFrom));
  }

// Comparison operators
  template <typename Data>
  bool BST<Data>::operator==(const BST<Data>& comp) const noexcept{

  }

  template <typename Data>
  bool BST<Data>::operator!=(const BST<Data>& comp) const noexcept{
    return !(*this == comp);
  }

}
