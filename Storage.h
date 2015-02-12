#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "PDeque.h"
#include "Server.h"
#include "Book.h"
#include "Patron.h"
#include "types.h"
#include "Factory.h"

class Storage{
  public:
    Storage();
    ~Storage();
    void retBooks(vector<Book*>&);
    void retPatrons(PDeque<Patron*>*);
    void updPatrons(UpdateType, Patron*);

  private:
    //LinkedList<Book*>* books;
    PDeque<Patron*>* patrons;
    Server* server;
};
#endif
