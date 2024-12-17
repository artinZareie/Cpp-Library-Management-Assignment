#pragma once
#include <string>

class Book {
private:
    std::string m_name;
    std::string m_author;
    std::string m_isbn;
    bool m_is_borrowed;

public:
    Book(std::string isbn, std::string name, std::string author);

    std::string getName() const;
    std::string getAuthor() const;
    std::string getISBN() const;
    bool isLoaning() const;
    void loan();
    void returnBook();

    bool operator==(const Book& other) const;
    bool operator!=(const Book& other) const;
    bool operator==(std::string isbn) const;
    bool operator!=(std::string isbn) const;
};