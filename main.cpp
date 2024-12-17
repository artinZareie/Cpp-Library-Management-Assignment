#include "Utils/LinkedList.hpp"
#include <iostream>

int main() {
    LinkedList<int> list;

    for (int i = 0; i < 10; i++) {
        list.push_back(i);
    }

    for (const auto &item : list) {
        std::cout << item << " ";
    }
    std::cout << std::endl;
    
    return 0;
}