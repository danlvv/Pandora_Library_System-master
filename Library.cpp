#include "Library.h"

Library::Library()
{
  storage = new Storage();
}

Library::~Library()
{
  delete storage;
}

Book* Library::getBook(int index) 
{ 
  vector<Book*>* collection = new vector<Book*>;
  storage->retBooks(*collection);
  if (index < 0 || index >= collection->size())
    return 0;
  return (*collection)[index];
  delete collection;
}

Patron* Library::getPatron(int index) 
{ 
  PDeque<Patron*>* patrons = new PDeque<Patron*>;
  storage->retPatrons(patrons);
  if (index < 0 || index >= patrons->size())
    return 0;
  return (*patrons)[index];
  delete patrons;
}

Storage* Library::getStorage(){
  return storage;
}


int Library::addPatron(Patron* patron)
{
  PDeque<Patron*>* patrons = new PDeque<Patron*>;
  storage->retPatrons(patrons);
  if (patrons->size() >= MAX_COLL_SIZE - 1) {
    return C_NOK;
  }

  storage->updPatrons(ADD, patron);
  delete patrons;
  return C_OK;
}

int Library::remPatron(Patron* patron)
{
  storage->updPatrons(DEL, patron);

  return C_OK;
}

int Library::findPatron(string fn, string ln, Patron** patron, int* index)
{
  PDeque<Patron*>* patrons = new PDeque<Patron*>;
  storage->retPatrons(patrons);
  Patron* newPatron = new Patron(fn, ln);
  int rc = patrons->findInList(newPatron, patron);
  delete patrons;
  delete newPatron;
  return rc;
}


int Library::findBook(int id, Book** book, int* index)
{
  vector<Book*>* books = new vector<Book*>;
  storage->retBooks(*books);
  for (int i=0; i<books->size(); ++i) {
    if ((*books)[i] == 0)
      continue;
    if ((*books)[i]->getId() == id) {
      *book  = (*books)[i];
      *index = i;
      delete books;
      return C_OK;
    }
  }
  *book  =  0;
  *index = -1;
  delete books;
  return C_NOK;
}
