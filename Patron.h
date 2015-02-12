#ifndef PATRON_H
#define PATRON_H

#include <string>
#include "Book.h"
#include "Map.h"
#include "types.h"

class Patron
{
  public:
    Patron(string="", string="", int=1);
    Patron(const Patron&);
    ~Patron();
    void   addDep(Patron*);
    int    remDep(Patron*);
    void   addBook(Book*);
    void   remBook(int);
    int    depSize();
    int    findBook(int, Book**);
    int    hasBooksOut();
    Patron* getDep(int);
    string getFname() const;
    string getLname() const;
    int    getAge() const;
    Book*  getBook(int) const;
    int    getBookListSize() const;
    int    getLifetimeCO() const;
    void   increaseltCO(int);
    int    getTotalCO() const;
    const  Patron& operator=(const Patron&);
    bool   operator< (const Patron&) const;
  private:
    string fname;
    string lname;
    int age;
    Map<int, Book*>* books;
    Map<int, Patron*>* deps;
    int    lifetimeCO;
};


class AdultPatron : public Patron{
  public:
    AdultPatron(string fn = "", string ln = "", int age = 1)
      : Patron(fn,ln,age){ }
};

class ChildPatron : public Patron{
  public:
    ChildPatron(string fn = "", string ln = "", int age = 1)
      : Patron(fn,ln,age){ }
};
#endif
