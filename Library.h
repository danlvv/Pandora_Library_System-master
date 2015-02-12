#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <vector>
#include "types.h"
#include "PDeque.h"
#include "Storage.h"
#include "Book.h"
#include "Patron.h"

class Library
{
  public:
    Library();
    ~Library();
    int     addBook(Book*);
    int     addPatron(Patron*);
    int     remPatron(Patron*);
    int     findBook(int, Book**, int*);
    int     findPatron(string, string, Patron**, int*);
    Book*   getBook(int);
    Patron* getPatron(int);
    Storage* getStorage();
  private:
    Storage* storage;
};

#endif

