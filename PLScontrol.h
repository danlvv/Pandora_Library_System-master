#ifndef PLS_CONTROL_H
#define PLS_CONTROL_H

#include "types.h"
#include "Library.h"
#include "View.h"
#include "Factory.h"

class View;

class PLScontrol
{
  public:
    PLScontrol();
    ~PLScontrol();
    void launch();
    void addPatron();
    void remPatron();
    void checkIn(Patron*);
    void checkOut(Patron*);
    Library* getLib();
    Storage* getStorage();
  private:
    Library* lib;
    View*    view;
    Storage* storage;
};

#endif

