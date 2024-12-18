#pragma once
#include <string>

class Book {
private:
    std::string m_name;
    std::string m_author;
    std::string m_isbn;
    bool m_is_borrowed;

public:
    Book(std::string name, std::string author, std::string isbn);

    std::string getName() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    bool isBorrowed() const;
    void borrow();
    void returnBook();
};