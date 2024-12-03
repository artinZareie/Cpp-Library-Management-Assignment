#include "include/Utils/LinkedList.hpp"
#include <iostream>
#include <Utils/LinkedList.hpp>

int main() {
    LinkedList<int> a;

    for (int i = 1; i < 11; i++) {
        a.push_back(i);
    }

    for (auto x : a) {
        std::cout << x << std::endl;
    }
    
    return 0;
}