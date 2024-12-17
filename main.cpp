#include "Models/Library.hpp"
#include "TUI/ScreenGrid.hpp"
#include "TUI/Window.hpp"
#include "TUI/WindowContainer.hpp"
#include "Utils/ArrayList.hpp"
#include "Utils/LinkedList.hpp"
#include <iostream>
#include <memory>

int main() {
    ScreenGrid &grid = ScreenGrid::getInstance();
    grid.set(' ');

    std::shared_ptr<WindowContainer> container = std::make_shared<WindowContainer>(0, 0, grid.getWidth(), grid.getHeight());
    container->add(std::make_shared<Window>(0, 0, 10, 10, "Hello"));
    container->add(std::make_shared<Window>(10, 0, 10, 10, "World"));

    container->draw();

    return 0;
}