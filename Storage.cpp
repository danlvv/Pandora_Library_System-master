#include "Storage.h"

void Storage::retBooks(vector<Book*>& bookArr){
  server->retrieve(bookArr);
}

void Storage::retPatrons(PDeque<Patron*>* patronDeq){
  PDeque<Patron*>* copyOfPatrons = new PDeque<Patron*>(*patrons);
  for(int i = 0; i < patrons->size(); ++i){
    patronDeq->push(copyOfPatrons->front());
    //copyOfPatrons->popFront();
    --(*copyOfPatrons);
  }
  delete copyOfPatrons;
}

void Storage::updPatrons(UpdateType action, Patron* patron){
  //hold permanent patron
  Patron* permanentPatron;
  switch(action){
    case ADD:
      patrons->push(patron);
      break;
    case DEL:
      permanentPatron = 0;
      patrons->findInList(patron, &permanentPatron);
      if (permanentPatron != NULL){
        for(int i = 0; i < patrons->size();++i){
          if ((*patrons)[i]->remDep(patron) == C_OK){
            (*patrons)[i]->increaseltCO(patron->getLifetimeCO());
          }
        }
        patrons->remove(patron);       
        delete permanentPatron;
      }
      break;
    case MOD:
      //find permanent patron in list
      patrons->findInList(patron, &permanentPatron);
      if (permanentPatron != NULL){
        *permanentPatron = *patron;
        //delete and re-add patron to fix priority
        patrons->remove(permanentPatron);
        patrons->push(permanentPatron);
      }
      break;
    default:
      break;
  }
}

Storage::Storage(){  
  server = new Server(); 
  patrons = new PDeque<Patron*>;
  AdultFactory adultFactory;


  //virtual void createPatron(Patron**, string="", string="", int=1);

  Patron* newPatron;

  adultFactory.createPatron(&newPatron, "Jack", "Shephard", 30);
  patrons->push(newPatron);

  adultFactory.createPatron(&newPatron, "Kate", "Austen", 27);
  patrons->push(newPatron);

  adultFactory.createPatron(&newPatron, "Hugo", "Reyes", 25);
  patrons->push(newPatron);

  adultFactory.createPatron(&newPatron, "James", "Ford", 35);
  patrons->push(newPatron);

  adultFactory.createPatron(&newPatron, "Sayid", "Jarrah", 33);
  patrons->push(newPatron);

  adultFactory.createPatron(&newPatron, "Sun-Hwa", "Kwon", 45);
  patrons->push(newPatron);

  adultFactory.createPatron(&newPatron, "Jin-Soo", "Kwon", 56);
  patrons->push(newPatron);

  adultFactory.createPatron(&newPatron, "John", "Locke", 60);
  patrons->push(newPatron);

  adultFactory.createPatron(&newPatron, "Juliet", "Burke", 43);
  patrons->push(newPatron);

  adultFactory.createPatron(&newPatron, "Benjamin", "Linus", 46);
  patrons->push(newPatron);

  adultFactory.createPatron(&newPatron, "a", "a", 20); // for testing
  patrons->push(newPatron);
}

Storage::~Storage(){
  delete server;
  for(int i=0; i<patrons->size(); ++i){
    delete (*patrons)[i];
  }
  delete patrons;
}
