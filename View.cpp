#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <algorithm>
#include <vector>
#include <cstdlib>
using namespace std;

#include "View.h"

View::View(PLScontrol* c) : control(c) { }

void View::mainMenu()
{
  string choice = "-1";

  while (choice != "0") {
    system("clear");
    cout<< "\n\n\n\n\n                   WELCOME TO THE PANDORA LIBRARY SYSTEM \n\n\n\n";
    cout<< "        Here are your options:\n\n";
    cout<< "          1. Patron Menu\n\n";
    cout<< "          2. Administrator Menu\n\n";
    cout<< "          3. View Entire Collection\n\n";
    cout<< "          4. View Patrons\n";
    cout<< "          0. Exit\n\n";
    cout<< "        Enter one of the choices above:  ";
    getline(cin, choice);

    while (choice != "1" && choice != "2"
        && choice != "3" &&  choice != "4" && choice != "0") {
      cout<< "        Enter one of the choices above:  ";
      getline(cin, choice);
    }

    switch(choice[0]) {
      case '1':
        patronMenu();
        break;
      case '2':
        adminMenu();
        break;
      case '3':
        viewCollection();
        break;
      case '4':
        viewPatronMenu();
        break;
      default:
        return;
    }
  }
}

void View::patronMenu()
{
  Patron* patron;
  Book*   book;
  string  choice = "-1";
  string  fn, ln;
  int     index, rc;

  getPatronName(fn, ln);
  rc = control->getLib()->findPatron(fn, ln, &patron, &index);
  if (rc != C_OK) {
    printError("\nCould not find patron, press <ENTER> to continue...");
    return;
  }

  while (choice != "0") {
    system("clear");
    cout<< "\n\n\n\n\n                   PATRON MENU \n\n";
    cout<< "        Here are your options:\n\n";
    cout<< "          1. Check in a book\n";
    cout<< "          2. Check out a book\n";
    cout<< "          3. List books checked out\n";
    cout<< "          0. Exit\n\n";
    cout<< "        Enter one of the choices above:  ";
    getline(cin, choice);

    while (choice != "1" && choice != "2"
        && choice != "3" && choice != "0") {
      cout<< "        Enter one of the choices above:  ";
      getline(cin, choice);
    }

    switch(choice[0]) {
      case '1':
        control->checkIn(patron);
        break;
      case '2':
        control->checkOut(patron);
        break;
      case '3':
        printCheckedOut(patron);
        break;
      default:
        return;
    }
  }
}

void View::adminMenu()
{
  string choice = "-1";

  while (choice != "0") {
    system("clear");
    cout<< "\n\n\n\n\n                   ADMINISTRATOR MENU \n\n";
    cout<< "        Here are your options:\n\n";
    cout<< "          1. Add a Patron \n";
    cout<< "          2. Delete a Patron\n";
    cout<< "          0. Exit\n\n";
    cout<< "        Enter one of the choices above:  ";
    getline(cin, choice);

    while (choice != "1" && choice != "2"
           && choice != "0") {
      cout<< "        Enter one of the choices above:  ";
      getline(cin, choice);
    }

    switch(choice[0]) {
      case '1':
        control->addPatron();
        break;
      case '2':
        control->remPatron();
        break;
      default:
        return;
    }
  }
}

void View::viewCollection()
{
  system("clear");
  printCollection();
  cout<< "\nPress <ENTER> to continue...";
  cin.get();
}

void View::viewPatronMenu()
{
  string choice = "-1";

  while (choice != "0"){
    system("clear");
    cout<< "\n\n\n\n\n            PRINT PATRONS\n\n";
    cout<< "        1. Ascending\n\n";
    cout<< "        2. Descending\n\n";
    cout<< "        3. Alphabetically\n";
    cout<< "        0. Exit\n\n";
    cout<< "      Enter one of the choices above: ";
    getline(cin, choice);
    
    if (choice.length() < 1) continue;

    switch (choice[0]) {
      case '1':
        system("clear");
        printPatrons("forwards");
        goto pressenter;
        break;
      case '2':
        system("clear");
        printPatrons("backwards");
        goto pressenter;
        break;
      case '3':
        system("clear");
        printPatronsAlpha();
        goto pressenter;
        break;
      case '0':
        return;
      default:
        break;
    }
  }
pressenter:
  cout << "Press <ENTER> to continue...";
  cin.get();
}

void View::getPatronName(string& fn, string& ln)
{
  string str;

  cout<< endl<<"        Enter patron name ([first] [last]:  ";
  getline(cin, str);
  stringstream ss(str);
  ss >> fn >> ln;
}

int View::getPatronAge(){
  int age;
  string line;
  cout<< endl<<"    Enter patron age: ";
  getline(cin, line);
  stringstream ss(line);
  
  if (!(ss >> age) || age > 120 || age < 1){
    printError("\nInvalid age: must be an integer between 1 and 120");
    return 1;
  }

  if(age < 18){
    cout<< endl<<"    Please enter parents name: ";
  }
  return age;
}

void View::getBookId(int* id)
{
  string str;

  cout<< endl<<"        Enter book identifier:  ";
  getline(cin, str);
  stringstream ss(str);
  ss >> *id;
}

void View::printAll()
{
  system("clear");
  printCollection();
  printPatrons("forwards");
}

void View::printCollection()
{
  cout << endl << setw(40)<< "COLLECTION" <<endl;;
  cout << setw(40)<< "----------"<<endl<<endl;
 
  vector<Book*>* books = new vector<Book*>;
  control->getStorage()->retBooks(*books);

  for (int i=0; i<books->size(); ++i) {
    if ((*books)[i] == NULL)
      continue;
    printBookInfo((*books)[i]);
  }
  delete books;
}

void View::printBookInfo(Book* book)
{
  cout<<" "<<setw(4)<<book->getId()<<setw(40)<<book->getTitle()<<setw(20)<<book->getAuthor();

  switch(book->getStatus()) {
    case CHECKED_IN:
      cout<< "  "<<setw(12)<< "Checked in";
      break;
    case CHECKED_OUT:
      cout<< "  "<<setw(12)<< "Checked out";
      break;
    case UNDER_REPAIR:
      cout<< "  "<<setw(12)<< "Under repair";
      break;
    case LOST:
      cout<< "  "<<setw(12)<< "Lost";
      break;
  }
  cout << endl;
}


void View::printPatrons(string direction)
{
  if (direction != "forwards" && direction != "backwards"){
    cout << "error in printPatrons: direction not 'forwards' or 'backwards'"
      << endl;
    return;
  }

  string str;

  cout<< endl<<endl<<setw(40)<<"PATRONS"<<endl;
  cout << setw(40)<< "-------"<<endl<<endl;

  PDeque<Patron*>* patrons = new PDeque<Patron*>;
  control->getStorage()->retPatrons(patrons);
 
  Patron* curPatron;

  int thesize = patrons->size();
  for (int i=0; i<thesize; ++i){
    if (direction == "forwards"){
      curPatron = patrons->front();
      --(*patrons);
    }
    else {
      curPatron = patrons->back();
      (*patrons)--;
    }


    str = curPatron->getFname() + " " + curPatron->getLname();
    str += ", lifetime #books: ";
    cout << setw(40) << str;
    cout << curPatron->getTotalCO();

    //print the dependents

    cout << "      Deps: ";
    int numDeps = curPatron->depSize();
    for (int i=0; i<numDeps; ++i){
      if (i > 0) cout << endl << setw(56);
      cout << curPatron->getDep(i)->getFname() << " "
           << curPatron->getDep(i)->getLname();
    }
    cout << endl;
    
    //print all books for patron
    int numBooks = curPatron->getBookListSize();
    int counted = 0;
    for (int i=0; i<MAX_MAP_ITEMS; ++i){
      if (counted == numBooks) break;
      Book* curBook = curPatron->getBook(i);
      if (curBook == NULL) continue;
      printBookInfo(curBook);
      ++counted;
    }
  }

  cout << endl;
  delete patrons;
}

void View::printPatronsAlpha(){
  PDeque<Patron*>* patrons = new PDeque<Patron*>;
  control->getStorage()->retPatrons(patrons);
  
  vector<Patron>* alphapats = new vector<Patron>;

  int thesize = patrons->size();
  for (int i=0; i<thesize; ++i){
    alphapats->push_back(*(patrons->front()));
    --(*patrons);
  }

  sort(alphapats->begin(), alphapats->end());

  cout<< endl<<endl<<setw(40)<<"PATRONS"<<endl;
  cout << setw(40)<< "-------"<<endl<<endl;
  
  for (int i=0; i<thesize; ++i){
    
    string str = (*alphapats)[i].getFname() + " " 
               + (*alphapats)[i].getLname()
               + ", lifetime #books: ";
    cout << setw(40) << str;
    cout << (*alphapats)[i].getTotalCO();


    cout << "     Deps: ";
    int numDeps = (*alphapats)[i].depSize();
    for (int j=0; j<numDeps; ++j){
      if (j>0) cout << endl << setw(56);
      cout << (*alphapats)[i].getDep(j)->getFname() << " "
           << (*alphapats)[i].getDep(j)->getLname();
    }
    cout << endl;

    int numBooks = (*alphapats)[i].getBookListSize();
    int counted = 0;
    for (int j=0; j<MAX_MAP_ITEMS; ++j){
      if (counted == numBooks) break;
      Book* curBook = (*alphapats)[i].getBook(i);
      if (curBook == NULL) continue;
      printBookInfo(curBook);
      ++counted;
    }
  }
  cout << endl;
  delete patrons;
  delete alphapats;
}

void View::printCheckedOut(Patron* patron)
{
  system("clear");
  cout << endl<<endl<<endl <<setw(40)<< "BOOKS CHECKED OUT FOR:  "
    << patron->getFname() << " " << patron->getLname() <<endl;
  cout << setw(38)<< "----------------------"<<endl<<endl;

  //print all books for patron
  int numBooks = patron->getBookListSize();
  int counted = 0;
  for (int i=0; i<MAX_MAP_ITEMS; ++i){
    if (counted == numBooks) break;
    Book* curBook = patron->getBook(i);
    if (curBook == NULL) continue;
    printBookInfo(curBook);
    ++counted;
  }


  cout<< "\nPress <ENTER> to continue...";
  cin.get();
}

void View::printError(const string& err)
{
  cout << err << endl;
  cin.get();
}

