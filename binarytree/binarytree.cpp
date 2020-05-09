
#include "../queue/queue.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

using namespace lasd;
/* ************************************************************************** */

// Node
// Specific constructors
  template <typename Data>
  BinaryTree<Data>::Node::Node(const Data& elem){
    value = elem;
  }

  template <typename Data>
  BinaryTree<Data>::Node::Node(Data&& elem){
    value = std::move(elem);
  }

  template <typename Data>
  bool BinaryTree<Data>::Node::operator==(const Node& comp) const noexcept{
    return (value == comp.value);
  }

  template <typename Data>
  bool BinaryTree<Data>::Node::operator!=(const Node& comp) const noexcept{
    return !(*this == comp);
  }

// BinaryTree
// Comparison operators
  template <typename Data>
  bool BinaryTree<Data>::operator==(const BinaryTree<Data>& comp) const noexcept{
    if(size == 0 && comp.size == 0)
      return true;
    else if(size == comp.size)
      return equals(Root(), comp.Root());
    else
      return false;
  }

    template <typename Data>
    bool BinaryTree<Data>::equals(const struct BinaryTree<Data>::Node& T1, const struct BinaryTree<Data>::Node& T2) const{
      if(T1 != T2)
        return false;

      bool flag = true;
      if(!(T1.HasLeftChild() ^ T2.HasLeftChild())){
        if(T1.HasLeftChild() && T2.HasLeftChild())
          flag = equals(T1.LeftChild(), T2.LeftChild());
        // else
        //   flag = true;
      }


      if(!(T1.HasRightChild() ^ T2.HasRightChild())){
        if(T1.HasRightChild() && T2.HasRightChild())
          return flag && equals(T1.RightChild(), T2.RightChild());
        // else
        //   return flag;
      }

      return flag;
    }

  template <typename Data>
  bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& comp) const noexcept{
    return !(*this == comp);
  }

// Specific member functions
  template <typename Data>
  void BinaryTree<Data>::MapInOrder(MapFunctor func, void* par){
    MapInOrder(func, par, Root());
  }

  template <typename Data>
  void BinaryTree<Data>::FoldInOrder(FoldFunctor func, const void* cPar, void* par) const{
    FoldInOrder(func, cPar, par, Root());
  }

// Specific member functions (inherited from SearchableContainer)
  template <typename Data>
  void BinaryTree<Data>::MapPreOrder(MapFunctor func, void* par){
    MapPreOrder(func, par, Root());
  }

  template <typename Data>
  void BinaryTree<Data>::MapPostOrder(MapFunctor func, void* par){
    MapPostOrder(func, par, Root());
  }

  template <typename Data>
  void BinaryTree<Data>::FoldPreOrder(FoldFunctor func, const void* cPar, void* par) const{
    FoldPreOrder(func, cPar, par, Root());
  }

  template <typename Data>
  void BinaryTree<Data>::FoldPostOrder(FoldFunctor func, const void* cPar, void* par) const{
    FoldPostOrder(func, cPar, par, Root());
  }

// Specific member functions (inherited from BreadthSearchableContainer)
  template <typename Data>
  void BinaryTree<Data>::MapBreadth(MapFunctor func, void* par){
    MapBreadth(func, par, Root());
  }

  template <typename Data>
  void BinaryTree<Data>::FoldBreadth(FoldFunctor func, const void* cPar, void* par) const{
    FoldBreadth(func, cPar, par, Root());
  }

// Accessory function
  template <typename Data>
  void BinaryTree<Data>::MapBreadth(MapFunctor func, void* par, struct Node& node){
    QueueVec<struct Node*> ql;

    if(&node != nullptr){
      ql.Enqueue(&node);

      while(!ql.Empty()){
        func(ql.Head()->Element(), par);

        if(ql.Head()->HasLeftChild())
          ql.Enqueue(&(ql.Head()->LeftChild()));

        if(ql.Head()->HasRightChild())
          ql.Enqueue(&(ql.Head()->RightChild()));

        ql.Dequeue();
      }
    }
  }

  template <typename Data>
  void BinaryTree<Data>::MapPreOrder(MapFunctor func, void* par, struct Node& node){
    if(&node == nullptr)
      return;

    func(node.Element(), par);

    if(node.HasLeftChild())
      MapPreOrder(func, par, node.LeftChild());

    if(node.HasRightChild())
    MapPreOrder(func, par, node.RightChild());
  }

  template <typename Data>
  void BinaryTree<Data>::MapInOrder(MapFunctor func, void* par, struct Node& node){
    if(&node == nullptr)
      return;

    if(node.HasLeftChild())
      MapInOrder(func, par, node.LeftChild());

    func(node.Element(), par);

    if(node.HasRightChild())
      MapInOrder(func, par, node.RightChild());
  }

  template <typename Data>
  void BinaryTree<Data>::MapPostOrder(MapFunctor func, void* par, struct Node& node){
    if(&node == nullptr)
      return;

    if(node.HasLeftChild())
      MapPostOrder(func, par, node.LeftChild());

    if(node.HasRightChild())
      MapPostOrder(func, par, node.RightChild());

    func(node.Element(), par);
  }

  template <typename Data>
  void BinaryTree<Data>::FoldBreadth(FoldFunctor func, const void* cPar, void* par, struct Node& node) const{
    QueueVec<struct Node*> ql;

    if(&node != nullptr){
      ql.Enqueue(&node);

      while(!ql.Empty()){
        func(ql.Head()->Element(), cPar, par);

        if(ql.Head()->HasLeftChild())
          ql.Enqueue(&(ql.Head()->LeftChild()));

        if(ql.Head()->HasRightChild())
          ql.Enqueue(&(ql.Head()->RightChild()));

        ql.Dequeue();
      }
    }
  }

  template <typename Data>
  void BinaryTree<Data>::FoldPreOrder(FoldFunctor func, const void* cPar, void* par, struct Node& node) const{
    if(&node == nullptr)
      return;

    func(node.Element(), cPar, par);

    if(node.HasLeftChild())
      FoldPreOrder(func, cPar, par, node.LeftChild());

    if(node.HasRightChild())
      FoldPreOrder(func, cPar, par, node.RightChild());
  }

  template <typename Data>
  void BinaryTree<Data>::FoldInOrder(FoldFunctor func, const void* cPar, void* par, struct Node& node) const{
    if(&node == nullptr)
      return;

    if(node.HasLeftChild())
      FoldInOrder(func, cPar, par, node.LeftChild());

    func(node.Element(), cPar, par);

    if(node.HasRightChild())
      FoldInOrder(func, cPar, par, node.RightChild());
  }

  template <typename Data>
  void BinaryTree<Data>::FoldPostOrder(FoldFunctor func, const void* cPar, void* par, struct Node& node) const{
    if(&node == nullptr)
      return;

    if(node.HasLeftChild())
      FoldPostOrder(func, cPar, par, node.LeftChild());

    if(node.HasRightChild())
      FoldPostOrder(func, cPar, par, node.RightChild());

    func(node.Element(), cPar, par);
  }
