#pragma once
#include <cstddef>
#include <string>

class Window {
protected:
    std::size_t m_pos_x, m_pos_y, m_width, m_height;
    std::string m_title;
    char m_border;
    bool visible;


public:
};