#pragma once
#include "TUI/Window.hpp"
#include <Utils/LinkedList.hpp>
#include <memory>
#include <optional>

class Container {
private:
    using WLinkedList = LinkedList<std::shared_ptr<Window>>;
    WLinkedList m_windows;

public:
    virtual void add(std::shared_ptr<Window> window);
    virtual void remove(std::shared_ptr<Window> window);
    virtual std::optional<std::shared_ptr<Window>> click(std::size_t x, std::size_t y);
};