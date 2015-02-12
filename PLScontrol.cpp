#include <iostream>
using namespace std;
#include "PLScontrol.h"

PLScontrol::PLScontrol() 
{ 
  lib  = new Library;
  storage = lib->getStorage();
  view = new View(this);
}

PLScontrol::~PLScontrol() 
{ 
  delete lib;
  delete view;
}

void PLScontrol::launch() 
{ 
  view->mainMenu();
  view->printAll();
}

void PLScontrol::addPatron() 
{
  Patron* parentPatron;
  Patron* patron;
  string fn, ln, parentfn, parentln;
  int    rc, age, index;

  view->getPatronName(fn, ln);

  rc = lib->findPatron(fn, ln, &patron, &index);
  if (rc == C_OK){
    view->printError("\nAlready exists! Failed to add.");
    return;
  }

  age = view->getPatronAge();

  if(age < 18){ //younger than 18
    Patron* newPat;
    ChildFactory fact;
    fact.createPatron(&newPat, fn, ln, age);

    view->getPatronName(parentfn, parentln);
    rc = lib->findPatron(parentfn, parentln, &parentPatron, &index);
    if(rc == C_OK){ //parent was found
      parentPatron->addDep(newPat);
      rc = lib->addPatron(newPat);
      if(rc != C_OK){ //if failed to add
        view->printError("\nCould not add patron to library, press <ENTER> to continue...");
        return;
      }
    }
    else { //parent was not found
      view->printError("\nCould not find parent. Press <ENTER> to continue...");
      return;
    }
  } 
  else { //18 or older
    Patron* newPat;
    AdultFactory fact;
    fact.createPatron(&newPat, fn, ln, age);

    rc = lib->addPatron(newPat);
    if (rc != C_OK) {
      view->printError("\nCould not add patron to library, press <ENTER> to continue...");
    }
  }
}

void PLScontrol::remPatron() 
{
  Patron *patron;
  string fn, ln;
  int    index;
  int    rc;

  view->getPatronName(fn, ln);

  rc = lib->findPatron(fn, ln, &patron, &index);
  if (rc != C_OK) {
    view->printError("\nCould not find patron, press <ENTER> to continue...");
    return;
  }

  if (patron->depSize() > 0){
    view->printError("\nThis patron has dependents. Can't delete!\npress <ENTER> to continue...");
    return; //suck it
  }
  
  if (patron->hasBooksOut()) {
    view->printError("\nPatron has books checked out, could not remove.  Press <ENTER> to continue...");
    return;
  }
  lib->remPatron(patron);
}

void PLScontrol::checkIn(Patron* patron) 
{
  Book* book;
  int   id, rc;

  view->getBookId(&id);

  rc = patron->findBook(id, &book);
  if (rc != C_OK) {
    view->printError("\nBook is not checked out to this patron, press <ENTER> to continue...");
    return;
  }

  patron->remBook(id);
  storage->updPatrons(MOD, patron);

}

void PLScontrol::checkOut(Patron* patron) 
{
  Book* book;
  int   id, index, rc;

  if (patron->getBookListSize() >= MAX_CO_BOOKS - 1) {
    view->printError("\nPatron cannot check out any more books.  Press <ENTER> to continue...");
    return;
  }

  view->getBookId(&id);

  rc = lib->findBook(id, &book, &index);
  if (rc != C_OK) {
    view->printError("\nCould not find book, press <ENTER> to continue...");
    return;
  }

  if (book->getStatus() != CHECKED_IN) {
    view->printError("\nBook is not available, press <ENTER> to continue...");
    return;
  }

  patron->addBook(book);
  storage->updPatrons(MOD, patron);
}


Library* PLScontrol::getLib() { return lib; }

Storage* PLScontrol::getStorage() { return storage; }
