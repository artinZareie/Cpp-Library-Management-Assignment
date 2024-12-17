#include "Models/Library.hpp"
#include "TUI/ScreenGrid.hpp"
#include "Utils/ArrayList.hpp"
#include "Utils/LinkedList.hpp"
#include <iostream>
#include <memory>

int main() {
    ScreenGrid &grid = ScreenGrid::getInstance();
    grid.set('X');
    grid.print();

    return 0;
}