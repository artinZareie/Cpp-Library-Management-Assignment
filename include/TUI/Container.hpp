#pragma once
#include "TUI/Window.hpp"
#include <Utils/LinkedList.hpp>
#include <memory>

class Container {
protected:
    using WLinkedList = LinkedList<std::shared_ptr<Window>>;
    WLinkedList m_windows;

public:
    virtual void add(std::shared_ptr<Window> window);
    virtual void remove(std::shared_ptr<Window> window);
    virtual bool click(std::size_t x, std::size_t y, std::function<void(std::size_t, std::size_t)>) = 0;
};