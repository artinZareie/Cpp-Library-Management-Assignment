#include <TUI/ScreenGrid.hpp>
#include <TUI/Window.hpp>
#include <cstddef>

Window::Window(std::size_t pos_x, std::size_t pos_y, std::size_t width, std::size_t height, std::string title, char border)
    : m_pos_x(pos_x), m_pos_y(pos_y), m_width(width), m_height(height), m_title(title), m_border(border), m_visible(true), m_active(true) {}

void Window::draw() {
    for (int i = 0; i < m_height; ++i) {
        ScreenGrid::getInstance().set(m_pos_x, m_pos_y + i, m_border);
        ScreenGrid::getInstance().set(m_pos_x + m_width - 1, m_pos_y + i, m_border);
    }

    for (int i = 0; i < m_width; ++i) {
        ScreenGrid::getInstance().set(m_pos_x + i, m_pos_y, m_border);
        ScreenGrid::getInstance().set(m_pos_x + i, m_pos_y + m_height - 1, m_border);
    }

    ScreenGrid::getInstance().set(m_pos_x + m_width - 1, m_pos_y, 'x');
    ScreenGrid::getInstance().set(m_pos_x + m_width - 2, m_pos_y, '-');

    for (int i = 0; (std::size_t)i < m_title.size(); i++) {
        ScreenGrid::getInstance().set(m_pos_x + i + 1, m_pos_y + 1, m_title[i]);
    }
}

bool Window::click(std::size_t x, std::size_t y, std::function<void(std::size_t, std::size_t)> callback) {
    return false;
}

void Window::makeActive() {
    m_active = true;
}

void Window::makeInactive() {
    m_active = false;
}

void Window::setTitle(std::string title) {
    m_title = title;
}

void Window::setBorder(char border) {
    m_border = border;
}

void Window::makeVisible() {
    m_visible = true;
}

void Window::makeInvisible() {
    m_visible = false;
}

void Window::setPos(std::size_t x, std::size_t y) {
    m_pos_x = x;
    m_pos_y = y;
}

void Window::setDimensions(std::size_t width, std::size_t height) {
    m_width = width;
    m_height = height;
}

Window::~Window() {};