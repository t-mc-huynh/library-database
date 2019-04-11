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

    int main()
{
    vector<Book *> books;
    vector<Person *> cardholders;

    readBooks(books);

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
                readPersons(cardholders);
                break;

            case 2:
                // Book return
                break;

            case 3:
                // View all available books
                printBooks(books);
                break;

            case 4:
                // View all outstanding rentals
                readRentals(books, cardholders);
                break;

            case 5:
                // View outstanding rentals for a cardholder
                break;

            case 6:
                // Open new library card
                // have to check if person exists in system
                // active or inactive
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
        cout << "Category: " << category << endl;
        getline(inFile, temp);
        Book * aBook;
        aBook = new Book(bookID, title, author, category);
        myBooks.push_back(aBook);
    }
    inFile.close();
}

void printBooks(vector<Book *> &myBooks)
{
    // Read only AVAILABLE books 
    for (int i = 0; i < myBooks.size(); i++)
    {
        // if a person has the book, the ptr is assigned to the person
        if (myBooks.at(i)->getPersonPtr() != nullptr) {
            cout << "Book ID: " << myBooks.at(i)->getId() << endl;
            cout << "Title: " << myBooks.at(i)->getTitle() << endl;
            cout << "Author: " << myBooks.at(i)->getAuthor() << endl;
            cout << "Category: " << myBooks.at(i)->getCategory() << endl << endl;
        }
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

    return 0;

    // return last cardholder ID to create new cardholder
}
/*

void readRentals(vector<Book *> & myBooks, vector<Person *> myCardholders) {
    // have to read rentals file
    // match bookID with cardID
    // set personPtr
    return ;
}


void openCard(vector<Person *> & myCardholders, int nextID) {
    // have to check if person has an account
    // have to check if account is active or inactive
    return;
}

Book * searchBook(vector<Book *> myBooks, int id) {
    return nullptr;
}
*/