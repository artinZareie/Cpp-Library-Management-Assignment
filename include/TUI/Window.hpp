#pragma once
#include <cstddef>
#include <functional>
#include <string>

// TODO: After testing, make this class pure abstract.
class Window {
protected:
    std::size_t m_pos_x, m_pos_y, m_width, m_height;
    std::string m_title;
    char m_border;
    bool m_visible;
    bool m_active;

public:
    Window(std::size_t pos_x, std::size_t pos_y, std::size_t width, std::size_t height, std::string title = "", char border = '*');

    virtual void draw();
    virtual bool click(std::size_t x, std::size_t y, std::function<void(std::size_t, std::size_t)>);
    virtual void makeActive();
    virtual void makeInactive();
    virtual void setTitle(std::string title);
    virtual void setBorder(char border);
    virtual void makeVisible();
    virtual void makeInvisible();
    virtual void setPos(std::size_t x, std::size_t y);
    virtual void setDimensions(std::size_t width, std::size_t height);
    virtual ~Window() = 0;
};