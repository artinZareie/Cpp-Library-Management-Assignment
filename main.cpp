#include <Utils/ArrayList.hpp>
#include <Utils/LinkedList.hpp>
#include <iostream>

int main() {
    ArrayList<int> a;

    for (int i = 0; i < 10; i++) {
        a.push_back(i);
    }

    for (auto x : a) {
        std::cout << x << std::endl;
    }
    std::cout << "--------------\n";

    a.clear();
    std::cout << a.capacity() << " " << a.size() << std::endl;

    for (int i = 0; i < 10; i++) {
        a.push_front(i);
    }

    for (auto x : a) {
        std::cout << x << std::endl;
    }
    std::cout << "--------------\n";

    a.clear();

    for (int i = 0; i < 10; i++) {
        a.insert(0, 2 * i);
    }

    for (auto x : a) {
        std::cout << x << std::endl;
    }
    std::cout << "--------------\n";

    a.erase(0);
    for (auto x : a) {
        std::cout << x << std::endl;
    }
    std::cout << "--------------\n";

    a.pop_back();
    for (auto x : a) {
        std::cout << x << std::endl;
    }
    std::cout << "--------------\n";

    a.pop_front();
    for (auto x : a) {
        std::cout << x << std::endl;
    }
    std::cout << "--------------\n";
    
    return 0;
}