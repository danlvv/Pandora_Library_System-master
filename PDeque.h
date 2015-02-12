#ifndef PDEQUE_H
#define PDEQUE_H
#include "types.h"

template <class T>
class PDeque {
  class Node {
    friend class PDeque;
    public:
      Node();
      Node(T _data);
      ~Node();
    private:
      T data;
      Node* next;
  };

  public:
    PDeque();
    PDeque(const PDeque&);
    ~PDeque();
    int size() const;
    int findInList(T, T*) const;
    int  remove(T);
    void push(T);
    void popFront();
    void popBack();
    T front() const;
    T back() const;
    T operator[] (int) const;
    void operator-- ();
    PDeque& operator-- (int);
    
  private:
    Node* head;
};

#endif
