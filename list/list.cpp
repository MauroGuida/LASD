
#include <stdexcept>

/* ************************************************************************** */

// STRUCT NODE
  // Specific constructors
    template <typename Data>
    List<Data>::Node::Node(Data newValue){
      value = newValue;
    }

  // Copy constructor
    template <typename Data>
    List<Data>::Node::Node(const Node& copyFrom){
      value = copyFrom.value;
    }

  // Move constructor
    template <typename Data>
    List<Data>::Node::Node(Node&& moveFrom) noexcept{
      std::swap(value, moveFrom.value);
      std::swap(next, moveFrom.next);
    }

  // Comparison operators
    template <typename Data>
    bool List<Data>::Node::operator==(const Node& comp) const noexcept{
      if(value == comp.value && next == comp.next)
        return true;

      return false;
    }

    template <typename Data>
    bool List<Data>::Node::operator!=(const Node& comp) const noexcept{
      return !(*this == comp);
    }

// CLASS LIST
  // Copy constructor
    template <typename Data>
    List<Data>::List(const List& copyFrom){ //DEEP COPY
      if(copyFrom.head != nullptr){
        struct Node* tmp = copyFrom.head;
        while(tmp != nullptr){
          List<Data>::InsertAtBack(tmp->value);
          tmp = tmp->next;
        }
      }
    }

  // Move constructor
    template <typename Data>
    List<Data>::List(List&& moveFrom){
      std::swap(size, moveFrom.size);
      std::swap(head, moveFrom.head);
      std::swap(tail, moveFrom.tail);
    }

  // Destructor
    template <typename Data>
    List<Data>::~List(){
      Clear();
    }

  // Copy assignment
    template <typename Data>
    List<Data>& List<Data>::operator=(const List& copyFrom){
      if(*this != copyFrom){
        Clear();

        if(copyFrom.head != nullptr){ //Copied from copy constructor method
          struct Node* tmp = copyFrom.head;
          while(tmp != nullptr){
            List<Data>::InsertAtBack(tmp->value);
            tmp = tmp->next;
          }
        }
      }

      return *this;
    }

  // Move assignment
    template <typename Data>
    List<Data>& List<Data>::operator=(List&& moveFrom){
      if(*this != moveFrom){
        Clear();

        std::swap(size, moveFrom.size);
        std::swap(head, moveFrom.head);
        std::swap(tail, moveFrom.tail);
      }

      return *this;
    }

  // Comparison operators
    template <typename Data>
    bool List<Data>::operator==(const List& comp) const noexcept{
      if(this->size != comp.size)
        return false;

      struct Node* ptrL1 = this->head;
      struct Node* ptrL2 = comp.head;

      while(ptrL1 != nullptr && ptrL2 != nullptr){
        if(ptrL1->value != ptrL2->value)
          return false;

        ptrL1 = ptrL1->next;
        ptrL2 = ptrL2->next;
      }

      return true;
    }

    template <typename Data>
    bool List<Data>::operator!=(const List& comp) const noexcept{
      return !(*this == comp);
    }

  // Specific member functions
    template <typename Data>
    void List<Data>::RemoveFromFront(){
      if(head == nullptr)
        throw std::length_error("Empty list!");

      size--;
      struct Node* tmp = head;
      head = head->next;
      delete tmp;

      if(size == 0)
        tail = nullptr;
    }

    template <typename Data>
    Data List<Data>::FrontNRemove(){
      if(head == nullptr)
        throw std::length_error("Empty list!");

      Data returnValue = head->value;

      List<Data>::RemoveFromFront();

      return returnValue;
    }

    template <typename Data>
    void List<Data>::InsertAtFront(const Data& elem){
      struct Node* tmp = head;
      struct Node* newNode = new Node(elem);
      newNode->next = tmp;

      head = newNode;
      size++;

      if(size == 1)
        tail = head;
    }

    template <typename Data>
    void List<Data>::InsertAtFront(Data&& elem){
      struct Node* tmp = head;
      struct Node* newNode = new Node(elem);
      newNode->next = tmp;

      head = newNode;
      size++;

      if(size == 1)
        tail = head;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(const Data& elem){
      if(head==nullptr){
        head = new Node(elem);
        tail = head;
      }else{
        tail->next = new Node(elem);
        tail = tail->next;
      }
      size++;
    }

    template <typename Data>
    void List<Data>::InsertAtBack(Data&& elem){
      if(head==nullptr){
        head = new Node(elem);
        tail = head;
      }else{
        tail->next = new Node(elem);
        tail = tail->next;
      }
      size++;
    }

    template <typename Data>
    void List<Data>::Clear(){
      while(head != nullptr)
        RemoveFromFront();
    }

    template <typename Data>
    Data& List<Data>::Front() const{
      if(head == nullptr)
        throw std::length_error("Empty list!");

      return head->value;
    }

    template <typename Data>
    Data& List<Data>::Back() const{
      if(tail == nullptr)
        throw std::length_error("Empty list!");

      return tail->value;
    }

    template <typename Data>
    Data& List<Data>::operator[](const ulong index) const{
      if(head == nullptr)
        throw std::length_error("Empty list!");
      else if(index >= size)
        throw std::length_error("Invalid Index!");

      if(index == size-1)
        return tail->value;

      struct Node* tmp = head;
      for(ulong i = 0; i<index; i++)
        tmp = tmp->next;

      return tmp->value;
    }

    template <typename Data>
    void List<Data>::MapPreOrder(MapFunctor function, void* par){
      MapPreOrder(function, par, head);
    }

    template <typename Data>
    void List<Data>::MapPostOrder(MapFunctor function, void* par){
      MapPostOrder(function, par, head);
    }

    template <typename Data>
    void List<Data>::FoldPreOrder(FoldFunctor function, const void* constPar, void* par) const{
      FoldPreOrder(function, constPar, par, head);
    }

    template <typename Data>
    void List<Data>::FoldPostOrder(FoldFunctor function, const void* constPar, void* par) const{
      FoldPostOrder(function, constPar, par, head);
    }

    //OVERLOAD Accessory Function

    template <typename Data>
    void List<Data>::MapPreOrder(MapFunctor function, void* par, struct Node* node){
      if(node == nullptr)
        return;

      function(node->value, par);
      MapPreOrder(function, par, node->next);
    }

    template <typename Data>
    void List<Data>::MapPostOrder(MapFunctor function, void* par, struct Node* node){
      if(node == nullptr)
        return;

      MapPostOrder(function, par, node->next);
      function(node->value, par);
    }

    template <typename Data>
    void List<Data>::FoldPreOrder(FoldFunctor function, const void* constPar, void* par, struct Node* node) const{
      if(node == nullptr)
        return;

      function(node->value, constPar, par);
      FoldPreOrder(function, constPar, par, node->next);
    }

    template <typename Data>
    void List<Data>::FoldPostOrder(FoldFunctor function, const void* constPar, void* par, struct Node* node) const{
      if(node == nullptr)
        return;

      FoldPostOrder(function, constPar, par, node->next);
      function(node->value, constPar, par);
    }
