#include "book.h"

Book::Book(int id, string bookName, string auth, string cat) {
    bookID = id;
    title = bookName;
    author = auth;
    category = cat;
}

string Book::getTitle() {
    return title;
}

string Book::getAuthor() {
    return author;
}

string Book::getCategory() {
    return category;
}

int Book::getId() {
    return bookID;
}

void Book::setPersonPtr(Person * ptr) {
    // needs to point to a Person object
    // There's no access to the j counter here
    // personPtr = ptr->at(j);

    personPtr = ptr;
    // cout << ptr->getId() << endl;

    // setting to the person who rents the book
    // if no one rented, set to nullptr
    
    // if end up with another ptr, go through:
    // which vector
    // which element
    // what do i have
}

Person * Book::getPersonPtr() {
    return personPtr;
}