#include <Models/Book.hpp>

Book::Book(std::string isbn, std::string title, std::string author) 
    : m_name(title), m_author(author), m_isbn(isbn), m_is_borrowed(false) {}

std::string Book::getName() const {
    return m_name;
}

std::string Book::getAuthor() const {
    return m_author;
}

std::string Book::getISBN() const {
    return m_isbn;
}

bool Book::isLoaning() const {
    return m_is_borrowed;
}

void Book::loan() {
    m_is_borrowed = true;
}

void Book::returnBook() {
    m_is_borrowed = false;
}

bool Book::operator==(const Book& other) const {
    return m_isbn == other.m_isbn;
}

bool Book::operator!=(const Book& other) const {
    return !(*this == other);
}

bool Book::operator==(std::string isbn) const {
    return m_isbn == isbn;
}

bool Book::operator!=(std::string isbn) const {
    return !(*this == isbn);
}