#include <Models/User.hpp>
#include <functional>

User::User(std::string username, std::string password, UserType type) 
    : m_username(username), m_password(std::hash<std::string>{}(password)), m_type(type) {}

std::string User::getUsername() const {
    return m_username;
}

bool User::checkPassword(std::string password) const {
    return m_password == std::hash<std::string>{}(password);
}

User::UserType User::getType() const {
    return m_type;
}

LinkedList<std::shared_ptr<Book>>& User::getLoanedBooks() {
    return m_loaned_books;
}

void User::loanBook(std::shared_ptr<Book> book) {
    m_loaned_books.push_back(book);
}

void User::returnBook(std::shared_ptr<Book> book) {
    m_loaned_books.erase(book);
}

bool User::isMember() const {
    return m_type == UserType::Member;
}

bool User::isStaff() const {
    return m_type == UserType::Staff;
}

void User::changePassword(std::string password) {
    if (!isStaff())
        throw std::logic_error("You are not a staff member");
    
    m_password = std::hash<std::string>{}(password);
}

bool User::operator==(const User& other) const {
    return m_username == other.m_username;
}

bool User::operator!=(const User& other) const {
    return !(*this == other);
}

bool User::operator==(std::string username) const {
    return m_username == username;
}

bool User::operator!=(std::string username) const {
    return !(*this == username);
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << user.m_username << " (" << (user.m_type == User::UserType::Member ? "Member" : "Staff") << "): ";

    for (const auto& book : user.m_loaned_books) {
        os << book->getName() << ", ";
    }
    os << std::endl;
    
    return os;
}