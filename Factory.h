#ifndef FACTORY_H
#define FACTORY_H

class PatronFactory {
  public:
    virtual void createPatron(Patron**, string, string, int) = 0;
};

class AdultFactory : public PatronFactory {
  public:
    virtual void createPatron(Patron** patron, string fn, string ln, int age){
      AdultPatron* newAdult = new AdultPatron(fn, ln, age);
      *patron = newAdult;
    }
};

class ChildFactory : public PatronFactory {
  public:
    virtual void createPatron(Patron** patron, string fn, string ln, int age){
      ChildPatron* newChild = new ChildPatron(fn, ln, age);
      *patron = newChild;
    }
};

#endif
