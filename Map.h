#ifndef MLP_H
#define MLP_H

#include "types.h"



class Book;
class Patron;

template <class T1, class T2>
class Map {
  public:
    Map();
    Map(const Map&);
    ~Map();
    T2 operator[] (T1) const;
    int find(T1, T2*) const;
    int size() const;
    bool empty() const;
    bool contains(T1) const;
    int add(T1, T2);
    int add(T2);
    int remove(T1);
    int remove(T2);

  private:
    T1 keys[MAX_MAP_ITEMS];
    T2 values[MAX_MAP_ITEMS];
    int size_;
};

#endif
