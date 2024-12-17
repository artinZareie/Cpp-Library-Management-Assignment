#pragma once
#include <cstddef>
#include <string>

// TODO: After testing, make this class pure abstract.
class Window {
protected:
    std::size_t m_pos_x, m_pos_y, m_width, m_height;
    std::string m_title;
    char m_border;
    bool visible;
    bool active;

public:
    Window(std::size_t pos_x, std::size_t pos_y, std::size_t width, std::size_t height, std::string title = "", char border = '*');

    virtual void draw();
    virtual bool click(std::size_t x, std::size_t y);
    virtual ~Window();
};