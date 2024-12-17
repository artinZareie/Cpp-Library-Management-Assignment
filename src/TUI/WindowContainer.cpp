#include <TUI/WindowContainer.hpp>

WindowContainer::WindowContainer(std::size_t pos_x, std::size_t pos_y, std::size_t width, std::size_t height, std::string title, char border)
    : Window(pos_x, pos_y, width, height, title, border) {}

void WindowContainer::draw() {
    Window::draw();

    for (auto &window : m_windows) {
        window->draw();
    }
}

bool WindowContainer::click(std::size_t x, std::size_t y, std::function<void(std::size_t, std::size_t)> callback) {
    for (auto &window : m_windows) {
        if (window->click(x, y, callback)) {
            return true;
        }
    }

    if (x >= m_pos_x && x < m_pos_x + m_width && y >= m_pos_y && y < m_pos_y + m_height) {
        callback(x - m_pos_x, y - m_pos_y);
        return true;
    }

    return false;
}

WindowContainer::~WindowContainer() {}