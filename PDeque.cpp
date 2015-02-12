#include "PDeque.h"
#include "Patron.h"


//PDeque constructor, copy ctr, and destructor
template <class T>
PDeque<T>::PDeque() : head(0) { }

template <class T>
PDeque<T>::PDeque(const PDeque<T>& oldPD) : head(0) {
  int size = oldPD.size();
  for (int i=0; i<size; ++i){
    push(oldPD[i]);
  }
}


template <class T>
PDeque<T>::~PDeque(){
  Node* curNode = head;
  Node* tmpNode;
  while (curNode != NULL){
    tmpNode = curNode->next;
    delete curNode;
    curNode = tmpNode;
  }
}

//Node constructors and destructor
template <class T>
PDeque<T>::Node::Node() { }

template <class T>
PDeque<T>::Node::Node(T _data) : next(0) {
  data = _data;
}

template <class T>
PDeque<T>::Node::~Node() { }


//deque operation member funcs
template <class T>
int PDeque<T>::size() const {
  int count = 0;
  Node* curNode = head;
  while (curNode != NULL){
    ++count;
    curNode = curNode->next;
  }
  return count;
}


template <> //specialized to patron
int PDeque<Patron*>::findInList(Patron* patron, Patron** patronToUpdate) const {
  Node* curNode = head;
  while (curNode != NULL){
    if (curNode->data->getFname() == patron->getFname()
        && curNode->data->getLname() == patron->getLname()){
      *patronToUpdate = curNode->data;
      return C_OK;
    }
    curNode = curNode->next;
  }
  *patronToUpdate = 0;
  return C_NOK;
}


template <> //also specialized to patron
int PDeque<Patron*>::remove(Patron* patron){
  switch(size()){
    case 0: //list size 0 - fail
      break;
    case 1: //list size 1 - empty the list
      if (head->data->getFname() == patron->getFname()
          && head->data->getLname() == patron->getLname()){
        delete head;
        head = 0;
        return C_OK;
      }
      break;
    default: //list size > 1 - remove, and if last ele repoint tail pointer
      Node* curNode = head;
      Node* prevNode = 0;
      while(curNode != NULL){
        if (curNode->data->getFname() == patron->getFname()
            && curNode->data->getLname() == patron->getLname()){
          if (curNode == head){ //first element in list
            head = curNode->next;
          }
          else if (curNode->next == NULL){ //last element in list
            prevNode->next = 0;
          }
          else { //middle of list
            prevNode->next = curNode->next;
          }
          delete curNode;
          return C_OK;
        }
        prevNode = curNode;
        curNode = curNode->next;
      }
  } 
  return C_NOK;
}

template <>
void PDeque<Patron*>::push(Patron* pat){
  //Node* newNode = new Node(_data);

  Node* tempNode = new Node(pat);

  if(head == NULL){
    tempNode->data = pat;
    tempNode->next = NULL;
    head = tempNode;
    
    
  }
  else if(head->next == NULL){
    if(head->data->getTotalCO() == pat->getTotalCO()){
      tempNode->data = pat;
      tempNode->next = NULL;
      head->next =tempNode;

    }
    else if(head->data->getTotalCO() < pat->getTotalCO()){
      tempNode->data = pat;
      tempNode->next = head;
      head = tempNode;


    }
  
    else if(head->data->getTotalCO() > pat->getTotalCO()){
      tempNode->data = pat;
      tempNode->next = NULL;
      tempNode->next = head->next;
      head->next = tempNode;

      
    }
  }
  else{
    Node* currNode = head;
    if(head->data->getTotalCO() < pat->getTotalCO()){
      tempNode->data = pat;
      tempNode->next=NULL;
      tempNode->next=head;
      head=tempNode;
    }
    else{
      while(currNode->next != NULL){
        if(currNode->next->data->getTotalCO()< pat->getTotalCO()){
          break;
        }
        currNode= currNode->next;
      }
      tempNode->data = pat;
      tempNode->next=currNode->next;
      currNode->next = tempNode;
    }
    
  }
}

template <class T>
void PDeque<T>::popFront(){
  if (head == NULL) return;

  Node* tmpNode = head;
  head = head->next;
  delete(tmpNode);
}

template <class T>
void PDeque<T>::popBack(){
  if (head == NULL) return;
  
  Node* curNode = head;
  Node* prevNode = 0;
  while(curNode->next != NULL){
    prevNode = curNode;
    curNode = curNode->next;
  }

  if (prevNode != NULL)
    prevNode->next = 0;
  else
    head = 0;
  delete(curNode);
}

  
template <class T>
T PDeque<T>::front() const {
  return head->data;
}

template <class T>
T PDeque<T>::back() const {
  if (head == NULL) return NULL;
  
  Node* curNode = head;
  while (curNode->next != NULL)
    curNode = curNode->next;

  return curNode->data;
}

template <class T>
T PDeque<T>::operator[] (int index) const { 
  Node* curNode = head;
  for (int i = 0; i < index; ++i){
    if (curNode == NULL) return 0;
    curNode = curNode->next;
  }
  if (curNode == NULL) return 0;
  return curNode->data;
}




template <class T>
void PDeque<T>::operator-- () {
  popFront();
}



template <class T>
PDeque<T>& PDeque<T>::operator-- (int) {
  PDeque<T>& copy(*this);
  popBack();
  return copy;
}



template class PDeque<Patron*>;
