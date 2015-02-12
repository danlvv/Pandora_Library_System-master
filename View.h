#ifndef VIEW_H
#define VIEW_H

#include <string>
#include "Book.h"
#include "PLScontrol.h"
#include <vector>

class PLScontrol;

class View
{
  public:
    View(PLScontrol*);
    void mainMenu();
    void getBookId(int*);
    int  getPatronAge();
    void getPatronName(string&,string&);
    void printAll();
    void printError(const string&);
  private:
    PLScontrol* control;
    void adminMenu();
    void patronMenu();
    void viewCollection();
    void viewPatronMenu();
    void printCollection();
    void printPatrons(std::string);
    void printPatronsAlpha();
    void printBookInfo(Book*);
    void printCheckedOut(Patron*);
};

#endif
