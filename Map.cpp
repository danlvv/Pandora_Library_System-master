#include "Map.h"


template <class T1, class T2>
Map<T1, T2>::Map(){
  for (int i=0; i<MAX_MAP_ITEMS; ++i){
    keys[i] = 0;
    values[i] = 0;
  }
  size_ = 0;
}

template <class T1, class T2>
Map<T1, T2>::Map(const Map& old){
  for(int i=0; i<MAX_MAP_ITEMS; ++i){
    keys[i] = old.keys[i];
    values[i] = old.values[i];
  }
  size_ = old.size_;
}

template <class T1, class T2>
Map<T1, T2>::~Map(){ 
}

template <class T1, class T2>
T2 Map<T1, T2>::operator[] (T1 key) const {
  for (int i=0; i<MAX_MAP_ITEMS; ++i)
    if (keys[i] == key)
      return values[i];
  return 0;
}

template <>
Patron* Map<int, Patron*>::operator[] (int index) const {
  int count = 0;
  for (int i=0; i<MAX_MAP_ITEMS; ++i){
    if (values[i] != 0){
      if (count == i)
        return values[i];
      else
        ++count;
    }
  }
}

template <class T1, class T2>
int Map<T1, T2>::find(T1 key, T2* outPointer) const {
  if (contains(key)){
    *outPointer = operator[](key);
    return C_OK;
  }
  else {
    return C_NOK;
  }
}

template <class T1, class T2>
int Map<T1, T2>::size() const {
  return size_;
}


template <class T1, class T2>
bool Map<T1, T2>::empty() const {
  return size_ == 0;
}

template <class T1, class T2>
bool Map<T1, T2>::contains(T1 key) const {
  for (int i=0; i<MAX_MAP_ITEMS; ++i){
    if (keys[i] == key){
      return C_TRUE;
    }
  }
  return C_FALSE;
}


template <class T1, class T2>
int Map<T1, T2>::add (T1 key, T2 value){
  if ((*this)[key] != 0)
    return C_NOK;
  else {
    for (int i=0; i<MAX_MAP_ITEMS; ++i){
      if (keys[i] == 0){
        keys[i] = key;
        values[i] = value;
        ++size_;
        return C_OK;
      }
    }
    return C_NOK;
  }
}

template <class T1, class T2>
int Map<T1, T2>::add (T2 value){
  if (size_ > MAX_MAP_ITEMS - 1)
    return C_NOK;
  else {
    for (int i=0; i<MAX_MAP_ITEMS; ++i){
      if (values[i] == 0){
        values[i] = value;
        ++size_;
        return C_OK;
      }
    }
  }
  return C_NOK;
}

template <class T1, class T2>
int Map<T1, T2>::remove (T1 key){
  for (int i=0; i<MAX_MAP_ITEMS; ++i){
    if (keys[i] == key){
      keys[i] = 0;
      values[i] = 0;
      --size_;
      return C_OK;
    }
  }
  return C_NOK;
}

template <class T1, class T2>
int Map<T1, T2>::remove (T2 value){
  for (int i=0; i<MAX_MAP_ITEMS; ++i){
    if (values[i] == value){
      keys[i] = 0;
      values[i] = 0;
      --size_;
      return C_OK;
    }
  }
  return C_NOK;
}

//needed to instantiate (use to define all uses of template)
template class Map<int, Book*>;
template class Map<int, Patron*>;
