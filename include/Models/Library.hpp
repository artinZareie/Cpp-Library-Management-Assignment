#pragma once
#include "Models/User.hpp"
#include <Models/Book.hpp>
#include <Utils/ArrayList.hpp>
#include <map>
#include <memory>

class Library {
private:
    ArrayList<std::shared_ptr<Book>> m_books;
    ArrayList<std::shared_ptr<User>> m_users;
    std::map<std::shared_ptr<Book>, std::shared_ptr<User>> m_loaned_books;

public:
    Library();

    void addBook(std::shared_ptr<Book> book);
    void addUser(std::shared_ptr<User> user);
    void loanBook(std::shared_ptr<Book> book, std::shared_ptr<User> user);
    void returnBook(std::shared_ptr<Book> book, std::shared_ptr<User> user);

    std::shared_ptr<User> getUser(std::string username);
    std::shared_ptr<Book> getBook(std::string isbn);

    ArrayList<std::shared_ptr<Book>>& getBooks();
    ArrayList<std::shared_ptr<User>>& getUsers();

    bool isBookLoaned(std::shared_ptr<Book> book);
    std::string getBookLoanedBy(std::shared_ptr<Book> book);

    void removeBook(std::shared_ptr<Book> book);
    void removeUser(std::shared_ptr<User> user);

    ~Library();
};