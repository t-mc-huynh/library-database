#include "book.h"

Book::Book(int id, string bookName, string auth, string cat) {
    id = bookID;
    bookName = title;
    auth = author;
    cat = category;
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
    personPtr = ptr;
}

Person * Book::getPersonPtr() {
    return personPtr;
}