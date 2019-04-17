// Name
// Section #
#include <iostream>
#include <fstream>
#include <string>
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
void openCard(vector<Person *> &myCardholders, int nextID);
int bookCheckout(vector<Book *> myBooks, vector<Person *> myCardholders);
void outstandingRentals(vector<Book *> &myBooks, vector<Person *> myCardholders);

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
                // have to check status of account - active or inactive
                bookCheckout(books, cardholders);
                break;

            case 2:
                // Book return
                returnBook(books, cardholders);
                break;

            case 3:
                // View all available books
                printBooks(books);
                //readBooks(books);
                break;

            case 4:
                // View all outstanding rentals
                readRentals(books, cardholders);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                outstandingRentals(books, cardholders);
                break;

            case 6:
                // Open new library card
                // have to check if person exists in system
                // active or inactive
                openCard(cardholders, lastID++);
                break;

            case 7:
                // Close library card
                // set active status to inactive
                break;
                
            case 8:
                // Must update records in files here before exiting the program
                // write into files
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

/* You are not obligated to use these function declarations - they're just given as examples */
void readBooks(vector<Book *> & myBooks) {
    fstream inFile;
    inFile.open("books.txt");

    int bookID;
    string title, author, category;
    string temp;

    while(!inFile.eof()) {
        inFile >> bookID;
        getline(inFile, temp);
        getline(inFile, title);
        getline(inFile, author);
        getline(inFile, category);
        getline(inFile, temp);
        Book * aBook;
        aBook = new Book(bookID, title, author, category);
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
        cout << "Card ID: " << cardID << endl;
        inFile >> active;
        cout << "Active: " << active << endl;
        inFile >> firstName >> lastName;
        cout << "First name: " << firstName << endl;
        cout << "Last name: " << lastName << endl;
        

        Person * aPerson;
        aPerson = new Person(cardID, active, firstName, lastName);
        myCardholders.push_back(aPerson);

        cout << endl;
    }
    inFile.close();

    return cardID;

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
        // cout << "Entry: " << bookID << " " << cardID << endl;

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

    // going through books vector
    for (int i = 0; i < myBooks.size(); i++)
    {
        // finds book ID in books vector
        if (tempBookID == myBooks.at(i)->getId())
        {
            Person * personPtr;
            personPtr = myBooks.at(i)->getPersonPtr();
            if (((* personPtr).getId()) == cardID) 
            {
                myBooks.at(i)->setPersonPtr(NULL);
                //cout << myBooks.at(i)->getPersonPtr() << endl;
            }
            //cout << (* personPtr).getId() << endl;
        }
    }
}

void openCard(vector<Person *> & myCardholders, int nextID) {
    // have to check if person has an account
    // have to check if account is active or inactive
    string fName, lName, fullName;

    cout << "Please enter your first name: ";
    getline(cin, fName);
    cout << "Please enter your last name: ";
    getline(cin, lName);
    fullName = fName + " " + lName;

    for (int i = 0; i < myCardholders.size(); i++)
    {
        if ((myCardholders.at(i)->getFirstName() + " " + myCardholders.at(i)->getLastName() == fullName))
        {
            myCardholders.at(i)->setActive(true);
        }
        else
        {
            Person * newPerson;
            newPerson = new Person(nextID, true, fName, lName);
            myCardholders.push_back(newPerson);
        }
    }
    return;
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
            cout << "Cardholder: " << myCardholders.at(i)->getFirstName();
            cout << " " << myCardholders.at(i)->getLastName() << endl;
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
                        // cout << "Card ID: " << myBooks.at(i)->getPersonPtr()->getId() << endl;
                        // cout << "Book ID: " << myBooks.at(i)->getId() << endl;
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

void outstandingRentals(vector<Book *> &myBooks, vector<Person *> myCardholders)
{
    int cardID;

    cout << "Please enter your card ID: ";
    cin >> cardID;

    // goes through the book vector to look for the card ID
    for (int i = 0; myBooks.size(); i++)
    {
        // the card ID exists
        if (cardID == myBooks.at(i)->getId())
        {
            // checks if the person is active
            if (myBooks.at(i)->getPersonPtr()->isActive() == true)
            {
                // if the card ID matches the ID the person pointer points to
                // aka the person the book is rented out to
                if (cardID == myBooks.at(i)->getPersonPtr()->getId())
                {
                    // prints the information of the book
                    cout << "Book ID: " << myBooks.at(i)->getId() << endl;
                    cout << "Title: " << myBooks.at(i)->getTitle() << endl;
                    cout << "Author: " << myBooks.at(i)->getAuthor() << endl << endl;
                }
            }
        }
    }
}

    /*
Book * searchBook(vector<Book *> myBooks, int id) {
    return nullptr;
}
*/