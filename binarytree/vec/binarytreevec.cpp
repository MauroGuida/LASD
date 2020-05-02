
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
    return (treeVec[2 * index+1].valid);
  }

  template <typename Data>
  bool BinaryTreeVec<Data>::NodeVec::HasRightChild() const noexcept{
    return (treeVec[2 * index+2].valid);
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

  }

  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(Data&&) noexcept{

  }

  // Copy constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>&){

  }

  // Move constructor
  template <typename Data>
  BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&&) noexcept{

  }

// Destructor
  template <typename Data>
  BinaryTreeVec<Data>::~BinaryTreeVec(){

  }

// Assignment
  // Copy assignment
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>&){

  }

  // Move assignment
  template <typename Data>
  BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec&&) noexcept{

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
    treeVec[0].valid = true;
    treeVec[0].value = newValue;

    size++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::NewRoot(Data&& newValue){
    Clear();
    treeVec[0].valid = true;
    treeVec[0].value = std::move(newValue);

    size++;
  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddLeftChild(struct NodeVec&, Data&){

  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddLeftChild(struct NodeVec&, Data&&){

  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddRightChild(struct NodeVec&, Data&){

  }

  template <typename Data>
  void BinaryTreeVec<Data>::AddRightChild(struct NodeVec&, Data&&){

  }

  template <typename Data>
  void BinaryTreeVec<Data>::RemoveLeftChild(struct NodeVec&){

  }

  template <typename Data>
  void BinaryTreeVec<Data>::RemoveRightChild(struct NodeVec&){

  }

// Specific member functions (inherited from Container)
  template <typename Data>
  void BinaryTreeVec<Data>::Clear(){

  }

// Specific member functions (inherited from BreadthSearchableContainer)
  template <typename Data>
  void BinaryTreeVec<Data>::MapBreadth(MapFunctor, void*){

  }

  template <typename Data>
  void BinaryTreeVec<Data>::FoldBreadth(FoldFunctor, const void*, void*) const{

  }

// Accessory functions
  template <typename Data>
  void BinaryTreeVec<Data>::Expand(){

  }

  template <typename Data>
  void BinaryTreeVec<Data>::Reduce(){

  }
