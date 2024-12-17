#include "Models/Library.hpp"
#include "TUI/ScreenGrid.hpp"
#include "TUI/Window.hpp"
#include "Utils/ArrayList.hpp"
#include "Utils/LinkedList.hpp"
#include <iostream>
#include <memory>

int main() {
    ScreenGrid &grid = ScreenGrid::getInstance();
    grid.set(' ');

    Window w(0, 0, 10, 4, "Hello");
    w.draw();

    grid.print();

    return 0;
}