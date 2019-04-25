// Name
// Section #
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "person.cpp"
#include "book.cpp"
using namespace std;

void printMenu();
void readBooks(vector<Book *> & myBooks);
void printBooks(vector<Book *> &myBooks);
int readPersons(vector<Person *> &myCardholders);
void readRentals(vector<Book *> &myBooks, vector<Person *> myCardholders);
void returnBook(vector<Book *> myBooks, vector<Person *> myCardholders);
int openCard(vector<Person *> &myCardholders, int nextID);
void closeCard(vector<Person *> myCardholders);
int bookCheckout(vector<Book *> myBooks, vector<Person *> myCardholders);
void outstandingRentalsForPerson(vector<Book *> &myBooks, vector<Person *> $myCardholders);
void outstandingRentals(vector<Book *> &myBooks, vector<Person *> myCardholders);
void closeCard(vector<Person *> myCardholders);
void updatePersonsFile(vector<Person *> myCardholders);
void updateRentalsFile(vector<Book *> myBooks);
void deletePointers(vector<Person *> myCardholders, vector<Book *> myBooks);

int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;

    // use to track what number to make new account with --> lastID++
    int lastID; 

    readBooks(books);
    lastID = readPersons(cardholders);
    readRentals(books, cardholders);

    int choice;
    do
    {
        // If you use cin anywhere, don't forget that you have to handle the <ENTER> key that 
        // the user pressed when entering a menu option. This is still in the input stream.
        printMenu();
        cin >> choice;
        switch(choice)
        {
            case 1:
                // Book checkout
                bookCheckout(books, cardholders);
                break;

            case 2:
                // Book return
                returnBook(books, cardholders);
                break;

            case 3:
                // View all available books
                printBooks(books);
                break;

            case 4:
                // View all outstanding rentals
                outstandingRentals(books, cardholders);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                outstandingRentalsForPerson(books, cardholders);
                break;

            case 6:
                // Open new library card
                // needs fixing
                lastID = openCard(cardholders, lastID);
                break;

            case 7:
                // Close library card
                closeCard(cardholders);
                break;

            case 8:
                // Must update records in files here before exiting the program
                // needs fixing
                updatePersonsFile(cardholders);
                updateRentalsFile(books);
                //deletePointers(cardholders, books);
                break;

            default:
                cout << "Invalid entry" << endl;
                break;
        }
        cout << endl;
   } while(choice != 8); // exits the system
      return 0;
}

void printMenu() {
    cout << "----------Library Book Rental System----------" << endl;
    cout << "1.  Book checkout" << endl;
    cout << "2.  Book return" << endl;
    cout << "3.  View all available books" << endl;
    cout << "4.  View all outstanding rentals" << endl;
    cout << "5.  View outstanding rentals for a cardholder" << endl;
    cout << "6.  Open new library card" << endl;
    cout << "7.  Close library card" << endl;
    cout << "8.  Exit system" << endl;
    cout << "Please enter a choice: ";
}

void readBooks(vector<Book *> & myBooks) {
    fstream inFile;
    inFile.open("books.txt");

    int bookID;
    string title, author, category;
    string temp;

    while(!inFile.eof()) {
        inFile >> bookID;
        // gets the rest of the ID line
        getline(inFile, temp);
        getline(inFile, title);
        getline(inFile, author);
        getline(inFile, category);
        // gets the line separating book entries
        getline(inFile, temp);

        Book * aBook;
        aBook = new Book(bookID, title, author, category);
        // by default sets the person pointer to null, meaning not rented out
        aBook->setPersonPtr(nullptr);
        myBooks.push_back(aBook);
    }
    inFile.close();
}

void printBooks(vector<Book *> &myBooks)
{
    int count = 0;
    // Read only AVAILABLE books 
    for (int i = 0; i < myBooks.size(); i++)
    {
        // if a person has the book, the ptr is assigned to the person
        if (myBooks.at(i)->getPersonPtr() != nullptr) {
            cout << "Book ID: " << myBooks.at(i)->getId() << endl;
            cout << "Title: " << myBooks.at(i)->getTitle() << endl;
            cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
            cout << "Category: " << myBooks.at(i)->getCategory() << endl << endl;
            count++;
        }
    }
    if (count == 0)
    {
        cout << "No available books" << endl;
    }
}

int readPersons(vector<Person *> &myCardholders)
{
    fstream inFile;
    inFile.open("persons.txt");

    int cardID;
    bool active;
    string firstName, lastName;

    while (!inFile.eof())
    {
        inFile >> cardID;
        //cout << "Card ID: " << cardID << endl;
        inFile >> active;
        //cout << "Active: " << active << endl;
        inFile >> firstName >> lastName;
        //cout << "First name: " << firstName << endl;
        //cout << "Last name: " << lastName << endl;
        

        Person * aPerson;
        aPerson = new Person(cardID, active, firstName, lastName);
        myCardholders.push_back(aPerson);
    }
    inFile.close();

    return (cardID + 1);

    // return last cardholder ID to create new cardholder
}

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    fstream inFile;
    inFile.open("rentals.txt");

    int bookID, cardID;

    while (!inFile.eof())
    {
        // reading book ID and card ID from file
        inFile >> bookID >> cardID;

        // going through books vector
        for (int i = 0; i < myBooks.size(); i++)
        {
            // finds book ID in books vector
            if (bookID == myBooks.at(i)->getId())
            {
                // for that book ID, goes through the cardholder vector
                for (int j = 0; j < myCardholders.size(); j++)
                {
                    // for that book ID, finds the card ID that matches
                    if (cardID == myCardholders.at(j)->getId())
                    {
                        // calls the function to connect the bookID to cardID
                        Person * temp = myCardholders.at(j);
                        myBooks.at(i)->setPersonPtr(temp);

                        if (myBooks.at(i)->getPersonPtr()->isActive() == false) 
                        {
                            myBooks.at(i)->getPersonPtr()->setActive(true);
                            cout << myBooks.at(i)->getPersonPtr()->isActive() << "\t";
                        }
                    }
                }
            }
        }
    }
}

void outstandingRentals(vector<Book *> &myBooks, vector<Person *> myCardholders)
{
    fstream inFile;
    inFile.open("rentals.txt");

    int bookID, cardID;

    while (!inFile.eof())
    {
        // reading book ID and card ID from file
        inFile >> bookID >> cardID;

        // going through books vector
        for (int i = 0; i < myBooks.size(); i++)
        {
            // finds book ID in books vector
            if (bookID == myBooks.at(i)->getId())
            {
                // for that book ID, goes through the cardholder vector
                for (int j = 0; j < myCardholders.size(); j++)
                {
                    // for that book ID, finds the card ID that matches
                    if (cardID == myCardholders.at(j)->getId())
                    {
                        // calls the function to connect the bookID to cardID
                        Person *temp = myCardholders.at(j);
                        myBooks.at(i)->setPersonPtr(temp);

                        cout << "Book ID: " << myBooks.at(i)->getId() << endl;
                        cout << "Title: " << myBooks.at(i)->getTitle() << endl;
                        cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
                        cout << "Cardholder: " << myBooks.at(i)->getPersonPtr()->getFirstName() << " " << myBooks.at(i)->getPersonPtr()->getLastName() << endl;
                        cout << "Card ID: " << myBooks.at(i)->getPersonPtr()->getId() << endl << endl;
                    }
                }
            }
        }
    }
}

void returnBook(vector<Book *> myBooks, vector<Person *> myCardholders) {
    int cardID, tempBookID;
    
    cout << "Please enter your card ID: ";
    cin >> cardID;
    cout << "Please enter the book ID to return: ";
    cin >> tempBookID;
    bool found = false;

    // going through books vector
    for (int i = 0; i < myBooks.size(); i++)
    {
        // finds book ID in books vector
        if (tempBookID == myBooks.at(i)->getId())
        {
            found = true;
            Person * personPtr;
            personPtr = myBooks.at(i)->getPersonPtr();
            if (((* personPtr).getId()) == cardID) 
            {
                // no one has the book checked out
                myBooks.at(i)->setPersonPtr(NULL);

                cout << "Book with title \"" << myBooks.at(i)->getTitle() << "\" has sucessfully been returned." << endl;
            }
        }
    }

    if (found == false)
    {
        cout << "You do not have this book rented out." << endl;
    }
}

int openCard(vector<Person *> & myCardholders, int nextID) {
    // have to check if person exists in system
    // have to check if account is active or inactive

    string fName, lName, fullName;
    bool found = false;

    cin.ignore();
    // Don't want to use getline in case user inputs first and last name at the same time - breaks system
    cout << "Please enter your first name: ";
    cin >> fName;
    cout << "Please enter your last name: ";
    cin >> lName;
    fullName = fName + " " + lName;

    for (int i = 0; i < myCardholders.size(); i++)
    {
        if (myCardholders.at(i)->fullName() == fullName)
        {
            // already exists an account
            cout << "An account for " << myCardholders.at(i)->getFirstName() << " " << myCardholders.at(i)->getLastName() << " already exists." << endl;
            cout << "The account is now active." << endl;
            if (myCardholders.at(i)->isActive() == false)
            {
                myCardholders.at(i)->setActive(true);
            }
            found = true;
            break;
        }
    }

    if (found == false)
    {
        // creates a new account
        Person *newPerson;
        newPerson = new Person(nextID, true, fName, lName);
        myCardholders.push_back(newPerson);

        cout << "An account has been created for..." << endl;
        cout << "Card ID: " << myCardholders.at(i)->getId() << endl;
        cout << "Cardholder: " << myCardholders.at(i)->fullName() << endl;
    }

    return nextID++;
}

int bookCheckout(vector<Book *> myBooks, vector<Person *> myCardholders)
{
    int cardID, bookID;
    bool found = false;

    cout << "Please enter card ID: ";
    cin >> cardID;
    for (int i = 0; i < myCardholders.size(); i++)
    {
        if (cardID == myCardholders.at(i)->getId())
        {
            found = true;
            // have to check status of account - active or inactive
            if (myCardholders.at(i)->isActive() == false)
            {
                cout << "ERROR! Your account is not currently active." << endl;
                return 0;
            }
            cout << "Cardholder: " << myCardholders.at(i)->getFirstName();
            cout << " " << myCardholders.at(i)->getLastName() << endl;
            break;
        }
    }

    if (found == false)
    {
        // Card ID was not found
        cout << "Card ID not found" << endl;
        return 0;
    }

    // resets found variable
    found = false;
    cout << "Please enter the book ID: ";
    cin >> bookID;

    for (int i = 0; i < myBooks.size(); i++)
    {
        // finds the book in the book vector
        if (bookID == myBooks.at(i)->getId())
        {
            found = true;
            for (int j = 0; j < myCardholders.size(); j++)
            {
                if (cardID == myCardholders.at(j)->getId())
                {
                    cout << "Title: " << myBooks.at(i)->getTitle() << endl;
                    Person * personPtr;
                    personPtr = myBooks.at(i)->getPersonPtr();
                    // if the book is not checked out
                    if (personPtr == NULL)
                    {
                        // set the book to the owner
                        Person * temp = myCardholders.at(j);
                        myBooks.at(i)->setPersonPtr(temp);
                        cout << "Card ID: " << myBooks.at(i)->getPersonPtr()->getId() << endl;
                        cout << "Book ID: " << myBooks.at(i)->getId() << endl;
                        return 0;
                    }
                    else
                    {
                        cout << "Book already checked out" << endl;
                        return 0;
                    }
                }
            }
        }
    }

    if (found == false)
    {
        // book ID was not found
        cout << "Book ID not found" << endl;
        return 0;
    }

    return 0;
}

void outstandingRentalsForPerson(vector<Book *> &myBooks, vector<Person *> myCardholders)
{
    int cardID;

    cout << "Please enter your card ID: ";
    cin >> cardID;

    cout << endl;

    // goes through the book vector to look for the card ID
    for (int i = 0; i < myBooks.size(); i++)
    {
        // the card ID exists
        if (myBooks.at(i)->getPersonPtr() != NULL)
        {
            // checks if the person is active
            if (cardID == myBooks.at(i)->getPersonPtr()->getId() && myBooks.at(i)->getPersonPtr()->isActive() == true)
            {
                
                // if the card ID matches the ID the person pointer points to
                // aka the person the book is rented out to
                    
                // prints the information of the book
                cout << "Book ID: " << myBooks.at(i)->getId() << endl;
                cout << "Title: " << myBooks.at(i)->getTitle() << endl;
                cout << "Author: " << myBooks.at(i)->getAuthor() <<endl << endl;
                    
            }
        }
    }
}

void closeCard(vector<Person *> myCardholders)
{
    int cardID;
    char choice;
    bool found = false;

    cout << "Please enter the card ID: ";
    cin >> cardID;
    cin.ignore();

    for (int i = 0; i < myCardholders.size(); i++)
    {
        // finds the card ID
        if (cardID == myCardholders.at(i)->getId())
        {
            found = true;
            cout << "Cardholder: " << myCardholders.at(i)->getFirstName() << " " << myCardholders.at(i)->getLastName() << endl;
            cout << "Are you sure you want to deactivitate the card (y/n) ?";
            cin >> choice;
            if (toupper(choice) == 'Y')
            {
                if (myCardholders.at(i)->isActive() == false)
                {
                    // already inactive
                    cout << "Cardholder: " << myCardholders.at(i)->getFirstName() << " " << myCardholders.at(i)->getLastName() << endl;
                    cout << "Card ID is already inactive" << endl;
                }
                else
                {
                    // set active status to inactive
                    myCardholders.at(i)->setActive(false);
                    cout << "Card ID Deactivated" << endl;
                }
            }
            else
            {
                cout << "Card cancellation aborted." << endl;
            }
        }
    }

    if (found == false)
    {
        cout << "Card ID not found" << endl;
    }
}

void updatePersonsFile(vector<Person *> myCardholders)
{
    fstream oFile;
    oFile.open("persons.txt");

    // updates entire card holders
    for (int i = 0; i < myCardholders.size(); i++)
    {
        oFile << myCardholders.at(i)->getId() << " " << myCardholders.at(i)->isActive() << " " << myCardholders.at(i)->getFirstName() << " " << myCardholders.at(i)->getLastName() << endl;
    }
    
    oFile.close();
}

void updateRentalsFile(vector<Book *> myBooks)
{
    fstream oFile;
    oFile.open("rentals.txt");

    for (int i = 0; i < myBooks.size(); i++)
    {
        // if the person has books checked out
        if (myBooks.at(i)->getPersonPtr() != NULL)
        {
            if (myBooks.at(i)->getPersonPtr()->isActive() == true) 
            {
                oFile << myBooks.at(i)->getId() << " " << myBooks.at(i)->getPersonPtr()->getId() << endl;
            }
        }
    }

    oFile.close();
}

void deletePointers(vector<Person *> myCardholders, vector <Book *> myBooks)
{
    // need to delete as many pointer as you dynamically allocated

    // you have many personPtrs
    // you have many Book pointers allocated for each Book existing
    // need to delete as many pointers as you created
    for (int i = 0; i < myBooks.size(); i++)
    {
        delete myBooks.at(i)->getPersonPtr();
        delete myBooks.at(i);
    }

    // you have many Person pointers allocated for each card holder existing
    for (int i = 0; i < myCardholders.size(); i++)
    {
        delete myCardholders.at(i);
    }
}