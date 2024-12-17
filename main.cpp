#include "Models/Library.hpp"
#include "Utils/ArrayList.hpp"
#include "Utils/LinkedList.hpp"
#include <iostream>
#include <memory>

int main() {
    // ArrayList<std::shared_ptr<int>> arr;

    // for (int i = 0; i < 10; i++) {
    //     arr.push_back(std::make_shared<int>(i));
    // }

    // for (int i = 0; i < arr.size(); i++) {
    //     std::cout << (*arr[i]) << " ";
    // }
    Library library;

    library.addUser(std::make_shared<User>("user1", "password1"));
    library.addUser(std::make_shared<User>("user2", "password2"));
    library.addUser(std::make_shared<User>("user3", "password3"));

    library.addBook(std::make_shared<Book>("isbn1", "title1", "author1"));
    library.addBook(std::make_shared<Book>("isbn2", "title2", "author2"));
    library.addBook(std::make_shared<Book>("isbn3", "title3", "author3"));

    auto user1 = library.getUser("user1");
    auto book1 = library.getBook("isbn1");
    auto book2 = library.getBook("isbn2");

    if (user1) {
        if (book1) {
            library.loanBook(book1.value(), user1.value());
            std::cout << book1.value()->getName() << " loaned to " << user1.value()->getUsername() << std::endl;
        }

        if (book2) {
            library.loanBook(book2.value(), user1.value());
            std::cout << book2.value()->getName() << " loaned to " << user1.value()->getUsername() << std::endl;
        }
    }

    if (book1 && user1) {
        library.returnBook(book1.value(), user1.value());
    } else {
        std::cout << "Book or user not found" << std::endl;
    }

    for (auto &[book, loaned_by] : library.getLoanedBooks()) {
        std::cout << book->getName() << " loaned by " << loaned_by->getUsername() << std::endl;
    }

    return 0;
}