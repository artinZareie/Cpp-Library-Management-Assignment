#pragma once
#include <Models/Book.hpp>
#include <Utils/LinkedList.hpp>
#include <memory>
#include <string>

class User {
public:
    enum class UserType {Member, Staff};
private:
    std::string m_username;
    std::size_t m_password;
    UserType m_type;
    LinkedList<std::shared_ptr<Book>> m_loaned_books;

public:
    User(std::string username, std::string password, UserType type = UserType::Member);
    User(const User&) = delete;
    User& operator=(const User&) = delete;
    std::string getUsername() const;
    bool checkPassword(std::string password) const;
    UserType getType() const;
    LinkedList<std::shared_ptr<Book>>& getLoanedBooks();
    void loanBook(std::shared_ptr<Book> book);
    void returnBook(std::shared_ptr<Book> book);
    bool isMember() const;
    bool isStaff() const;
    void changePassword(std::string password);

    bool operator==(const User& other) const;
    bool operator!=(const User& other) const;
    bool operator==(std::string username) const;
    bool operator!=(std::string username) const;

    friend std::ostream& operator<<(std::ostream& os, const User& user);

    ~User() = default;
};