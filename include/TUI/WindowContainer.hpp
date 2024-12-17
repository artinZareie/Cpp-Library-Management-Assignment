#pragma once
#include <TUI/Window.hpp>
#include <TUI/Container.hpp>
#include <memory>
#include <optional>

class WindowContainer : public Window, public Container {
private:

public:
    WindowContainer(std::size_t pos_x, std::size_t pos_y, std::size_t width, std::size_t height, std::string title = "", char border = '*');

    void draw() override;
    bool click(std::size_t x, std::size_t y, std::function<void(std::size_t, std::size_t)> callback) override;

    ~WindowContainer() override;
};