#include "Utils/ArrayList.hpp"
#include "Utils/Functional.hpp"
#include "Utils/LinkedList.hpp"
#include <Models/Library.hpp>
#include <functional>
#include <memory>

Library &Library::getInstance() {
    static Library instance;
    return instance;
}

void Library::addBook(std::shared_ptr<Book> book) {
    m_books.push_back(book);
}

void Library::addUser(std::shared_ptr<User> user) {
    m_users.push_back(user);
}

void Library::reserveBook(std::shared_ptr<Book> book, std::shared_ptr<User> user) {
    if (m_reservations[book].cfind(user) != m_reservations[book].cend()) {
        return;
    }

    m_reservations[book].push_back(user);
}

void Library::loanBook(std::shared_ptr<Book> book, std::shared_ptr<User> user) {
    if (m_loaned_books.count(book) > 0) {
        reserveBook(book, user);
        return;
    }

    m_loaned_books[book] = user;
    user->loanBook(book);
}

void Library::returnBook(std::shared_ptr<Book> book, std::shared_ptr<User> user) {
    m_loaned_books.erase(book);
    user->returnBook(book);
}

void Library::removeFromReservation(std::shared_ptr<Book> book, std::shared_ptr<User> user) {
    auto it = m_reservations[book].find(user);

    if (it != m_reservations[book].end()) {
        m_reservations[book].erase(it);
    }
}

void Library::reverseToLoan(std::shared_ptr<Book> book) {
    if (m_loaned_books.count(book) > 0) {
        throw std::logic_error("Book is already loaning");
    }

    auto front = m_reservations[book].front();
    m_reservations[book].pop_front();

    m_loaned_books[book] = front;
    front->loanBook(book);
}

LinkedList<std::shared_ptr<User>>& Library::getReservations(std::shared_ptr<Book> book) { return m_reservations[book]; }

bool Library::registerMember(std::string username, std::string password) {
    std::shared_ptr<User> dummy_user = std::make_shared<User>(username, password, User::UserType::Member);

    if (m_users.cfind(dummy_user) != m_users.cend()) {
        return false;
    }

    m_users.push_back(dummy_user);
    return true;
}

bool Library::registerStaff(std::string username, std::string password) {
    std::shared_ptr<User> dummy_user = std::make_shared<User>(username, password, User::UserType::Staff);

    if (m_users.cfind(dummy_user) != m_users.cend()) {
        return false;
    }

    m_users.push_back(dummy_user);
    return true;
}

std::optional<std::shared_ptr<User>> Library::getUser(std::string username) {
    std::shared_ptr<User> dummy_user = std::make_shared<User>(username, "", User::UserType::Member);
    auto found = m_users.cfind(dummy_user, std::function(sharedEq<User>));

    if (found == m_users.cend()) {
        return std::nullopt;
    }

    return *found;
}

std::optional<std::shared_ptr<Book>> Library::getBook(std::string isbn) {
    std::shared_ptr<Book> dummy_book = std::make_shared<Book>(isbn, "", "");
    auto found = m_books.cfind(dummy_book, std::function(sharedEq<Book>));

    if (found == m_books.cend()) {
        return std::nullopt;
    }

    return *found;
}

ArrayList<std::shared_ptr<Book>>& Library::getBooks() { return m_books; }

ArrayList<std::shared_ptr<User>>& Library::getUsers() { return m_users; }

const std::unordered_map<std::shared_ptr<Book>, std::shared_ptr<User>> &Library::getLoanedBooks() { return m_loaned_books; }

bool Library::isBookLoaned(std::shared_ptr<Book> book) {
    return m_loaned_books.count(book) > 0;
}

std::string Library::getBookLoanedBy(std::shared_ptr<Book> book) {
    return m_loaned_books[book]->getUsername();
}

void Library::removeBook(std::shared_ptr<Book> book) {
    if (m_loaned_books.count(book) > 0) {
        m_loaned_books.erase(book);
    }

    if (m_reservations.count(book) > 0) {
        m_reservations.erase(book);
    }

    m_books.erase(book);
}

void Library::removeUser(std::shared_ptr<User> user) {
    m_users.erase(user);

    ArrayList<std::shared_ptr<Book>> to_return;
    for (auto &[book, loaned_by] : m_loaned_books) {
        if (loaned_by == user) {
            to_return.push_back(book);
        }
    }

    for (auto book : to_return) {
        m_loaned_books.erase(book);
    }

    for (auto &[book, users] : m_reservations) {
        auto it = users.find(user);
        if (it != users.end()) {
            users.erase(it);
        }
    }
}

Library::~Library() {}