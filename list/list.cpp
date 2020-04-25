
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

  // Specific member functions

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
      struct Node* tmp = head;
      while(tmp != nullptr){
          function(tmp->value, par);
          tmp=tmp->next;
      }
    }

    //Ricorsivo
    template <typename Data>
    void List<Data>::MapPostOrder(MapFunctor function, void* par){
      // for(ulong i=size-1; i>=0 && i < size; i--)
      //   function((*this)[i], par);
      RecursiveMapPostOrder(head, function, par);
    }

      template <typename Data>
      void List<Data>::RecursiveMapPostOrder(struct Node* nodo, MapFunctor function, void* par){
        if (nodo != nullptr){
          RecursiveMapPostOrder(nodo->next, function, par);
          function(nodo->value, par);
        }
      }

    template <typename Data>
    void List<Data>::FoldPreOrder(FoldFunctor function, const void* constPar, void* par) const{
      struct Node* tmp = head;
      while(tmp != nullptr){
          function(tmp->value, constPar, par);
          tmp=tmp->next;
      }
    }

    //Ricorsivo
    template <typename Data>
    void List<Data>::FoldPostOrder(FoldFunctor function, const void* constPar, void* par) const{
      // for(ulong i=size-1; i>=0 && i < size; i--)
      //   function((*this)[i], constPar, par);
      RecursiveFoldPostOrder(head, function, constPar, par);
    }

      template <typename Data>
      void List<Data>::RecursiveFoldPostOrder(struct Node* nodo, FoldFunctor function, const void* constPar, void* par) const{
        if (nodo != nullptr){
          RecursiveFoldPostOrder(nodo->next, function, constPar, par);
          function(nodo->value, constPar, par);
        }
      }

    //OVERLOAD Accessory Function

      template <typename Data>
      void List<Data>::MapPreOrder(MapFunctor function, void* par, struct Node* node){
        while(node != nullptr){
          function(node->value, par);
          node = node->next;
        }
      }

      //Ricorsivo
      template <typename Data>
      void List<Data>::MapPostOrder(MapFunctor function, void* par, struct Node* node){
        RecursiveMapPostOrder(head, function, par, node);
      }

        template <typename Data>
        void List<Data>::RecursiveMapPostOrder(struct Node * scrollNode, MapFunctor function, void* par, struct Node* node){
          if(scrollNode == node){
            function(scrollNode->value, par);
          }else if(scrollNode != node){
            RecursiveMapPostOrder(scrollNode->next, function, par, node);
            function(scrollNode->value, par);
          }
        }

      template <typename Data>
      void List<Data>::FoldPreOrder(FoldFunctor functor, const void* constPar, void* par, struct Node* node) const{
        while(node != nullptr){
          function(node->value, constPar, par);
          node = node->next;
        }
      }

      //Ricorsivo
      template <typename Data>
      void List<Data>::FoldPostOrder(FoldFunctor function, const void* constPar, void* par, struct Node* node) const{
        RecursiveFoldPostOrder(head, function, constPar, par, node);
      }

        template <typename Data>
        void List<Data>::RecursiveFoldPostOrder(struct Node * scrollNode, FoldFunctor function, const void* constPar, void* par, struct Node* node){
          if(scrollNode == node){
            function(scrollNode->value, constPar, par);
          }else if(scrollNode != node){
            RecursiveMapPostOrder(scrollNode->next, function, par, node);
            function(scrollNode->value, constPar, par);
          }
        }
