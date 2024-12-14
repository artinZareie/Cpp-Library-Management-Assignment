#include <Models/Book.hpp>

Book::Book(std::string name, std::string author, std::string isbn) : m_name(name), m_author(author), m_isbn(isbn), m_is_borrowed(false) {}

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