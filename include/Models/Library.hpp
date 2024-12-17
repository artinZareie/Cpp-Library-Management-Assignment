#pragma once
#include "Models/User.hpp"
#include "Utils/LinkedList.hpp"
#include <Models/Book.hpp>
#include <Utils/ArrayList.hpp>
#include <memory>
#include <unordered_map>

class Library {
private:
    ArrayList<std::shared_ptr<Book>> m_books;
    ArrayList<std::shared_ptr<User>> m_users;
    std::unordered_map<std::shared_ptr<Book>, std::shared_ptr<User>> m_loaned_books;
    std::unordered_map<std::shared_ptr<Book>, LinkedList<std::shared_ptr<User>>> m_reservations;

public:
    Library() = default;

    Library &getInstance();

    void addBook(std::shared_ptr<Book> book);
    void addUser(std::shared_ptr<User> user);
    void reserveBook(std::shared_ptr<Book> book, std::shared_ptr<User> user);
    void loanBook(std::shared_ptr<Book> book, std::shared_ptr<User> user);
    void returnBook(std::shared_ptr<Book> book, std::shared_ptr<User> user);
    void removeFromReservation(std::shared_ptr<Book> book, std::shared_ptr<User> user);
    void reverseToLoan(std::shared_ptr<Book> book);
    LinkedList<std::shared_ptr<User>>& getReservations(std::shared_ptr<Book> book);

    bool registerMember(std::string username, std::string password);
    bool registerStaff(std::string username, std::string password);

    std::optional<std::shared_ptr<User>> getUser(std::string username);
    std::optional<std::shared_ptr<Book>> getBook(std::string isbn);

    ArrayList<std::shared_ptr<Book>>& getBooks();
    ArrayList<std::shared_ptr<User>>& getUsers();
    const std::unordered_map<std::shared_ptr<Book>, std::shared_ptr<User>> &getLoanedBooks();

    bool isBookLoaned(std::shared_ptr<Book> book);
    std::string getBookLoanedBy(std::shared_ptr<Book> book);

    void removeBook(std::shared_ptr<Book> book);
    void removeUser(std::shared_ptr<User> user);

    ~Library();
};