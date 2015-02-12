# Pandora_Library_System
A Walk into the World of C++ and Software Engineering

By Frank Egan
Jay Gadi
Daniel Vanderveen

Instructions: make, then ./PLS

we created a file testinput which tests every feature of the program
you can do leak check like this:

valgrind --leak-check=full ./PLS < testinput


Pandora Library System(PLS) allows users to access patron menu, the administration menu, or to view a collection of books/patrons.

The Patron Menu:
Allows a specific patron to check in a book, chack out a book, and view the collection of books the patron has currently cchecked out.

The Administrator Menu:
Allows the administrator to add a patron and delete a patron. 
-When adding a patron, the adiministrator is prompted of their age, and if the age of the patron is less than 18, they are listed as a "dependent" or child of an already exiting "adult" patron. 
-When deleteing a patron, the patron, must have all dependants deleted as well, and have no books checked out.

View Entire Collection:
Allows user to view the entire collection of books that the library has to offer. It also shows a status for each book, specifying whether the book is available for checkout. 

View Patrons:
Allows user to view the list of patrons, their dependants, and all books they have checkout, as well as a total count of books they have ever checkout. Patrons can be printed in ascending order of most books checked out, descending order of most books checked out, and alphabetically. 

The application uses many software engineering principles to accomplish this.
Various Software Engineering Principles: 
-Uses an Entity object, Control object, View object relationship
-Uses a factory design pattern to create adult and child patrons. 
-Uses a storage class to access all list of books and patrons. This allows us to work on copies of the collections, instead of the physical collections.
-Patrons are stored in a priority deque, of highest number of books checked out.
-Use of operator overloading, i.e +=, =, prefix--, postfix--, and copy constructors. 
-Use of inheritance for Parent, dependent patron.
-Uses a server class to populate collection of books. Collection is updated at random, to emulate real life scenerio.
-Uses the STL vector to store collection of books. 
-Uses a templated map class, which was built by us, to store patron's collection of books and dependents.
 


File List:

Book.cpp     Library.h  Map.h       PDeque.h        Server.h     types.h
Book.h       main.cpp   Patron.cpp  PLScontrol.cpp  Server.o     View.cpp
Factory.h    Makefile   Patron.h    PLScontrol.h    Storage.cpp  View.h
Library.cpp  Map.cpp    PDeque.cpp  README          Storage.h    testinput
