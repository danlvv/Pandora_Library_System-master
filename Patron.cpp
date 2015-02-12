#include "Patron.h"

Patron::Patron(string fn, string ln, int ag) 
  : fname(fn), lname(ln), lifetimeCO(0), age(ag) 
{
  books = new Map<int, Book*>;
  deps = new Map<int, Patron*>;
}

Patron::Patron(const Patron& old){
  fname = old.fname;
  lname = old.lname;
  lifetimeCO = old.lifetimeCO;
  books = new Map<int, Book*>(*old.books);
  deps = new Map<int, Patron*>(*old.deps);
}



Patron::~Patron()
{
  delete books;
  delete deps;
}

void Patron::addDep(Patron* p){
  deps->add(p);
}

Patron* Patron::getDep(int i){
  return (*deps)[i];
}

int Patron::depSize(){
  return deps->size();
}

void Patron::addBook(Book* book)
{
  books->add(book->getId(), book);
  book->setStatus(CHECKED_OUT);
  ++lifetimeCO;
}

void Patron::remBook(int id)
{
  (*books)[id]->setStatus(CHECKED_IN);
  books->remove(id);
}

int Patron::findBook(int id, Book** book)
{
  return books->find(id, book);
}

int Patron::hasBooksOut()
{
  for(int i=0; i<books->size(); ++i) {
    if ((*books)[i] != 0)
      return C_TRUE;
  }
  return C_FALSE;
}

int Patron::getBookListSize() const  { return books->size(); }
int Patron::getLifetimeCO() const    { return lifetimeCO; }
string Patron::getFname() const      { return fname; }
string Patron::getLname() const      { return lname; }
int    Patron::getAge()   const      { return age;   }

int Patron::getTotalCO() const {
  int count = lifetimeCO;
  if (deps->size() == 0) return count;
  int size = deps->size();
  for(int i=0; i<size; ++i)
    count += (*deps)[i]->getTotalCO();
  return count;
}
int Patron::remDep(Patron* p){
  return deps->remove(p);
}
Book* Patron::getBook(int id) const
{
  return (*books)[id];
}

void Patron::increaseltCO(int amount){
  lifetimeCO += amount;
}

bool Patron::operator<(const Patron& b) const {
  string afn = getFname();
  string aln = getLname();
  string bfn = b.getFname();
  string bln = b.getLname();

  for (int i=0; i<afn.length(); ++i)
    afn[i] = tolower(afn[i]);
  for (int i=0; i<aln.length(); ++i)
    aln[i] = tolower(aln[i]);
  for (int i=0; i<bfn.length(); ++i)
    bfn[i] = tolower(bfn[i]);
  for (int i=0; i<bln.length(); ++i)
    bln[i] = tolower(bln[i]);

  if (afn > bfn)
    return false;
  else if (afn < bfn)
    return true;
  else {
    if (aln > bln)
      return false;
    else
      return true;
  }
}

const Patron& Patron::operator=(const Patron& old){
  
  Map<int, Book*>* booksptr = books;
  Map<int, Patron*>* depsptr = deps;
  
  fname = old.fname;
  lname = old.lname;
  lifetimeCO = old.lifetimeCO;
  if (old.books != NULL)
    books = new Map<int, Book*>(*old.books);
  else
    books = new Map<int, Book*>;

  if (old.deps != NULL)
    deps = new Map<int, Patron*>(*old.deps);
  else
    deps = new Map<int, Patron*>;

  delete booksptr;
  delete depsptr;
  return old;
}
