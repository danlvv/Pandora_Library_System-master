#include "Book.h"

int Book::nextId = 1001;

Book::Book(string t, string a, int y) 
  : title(t), author(a), year(y)
{ 
  id     = nextId++;
  status = CHECKED_IN;
}

Book::Book(string t, string a, int y, BookStatusType bst)
  : title(t), author(a), year(y), status(bst)
{
  id     = nextId++;
}


void Book::setStatus(BookStatusType s)
{
  status = s;
}

int            Book::getId()     { return id; }
string         Book::getTitle()  { return title; }
string         Book::getAuthor() { return author; }
BookStatusType Book::getStatus() { return status; }

