#pragma once
#include <cstddef>

class ScreenGrid {
private:
    static const size_t DEFAULT_MARGIN;
    size_t m_width;
    size_t m_height;
    char **m_grid;

public:
    ScreenGrid(size_t width, size_t height);

    static ScreenGrid &getInstance();

    void erase();
    void set(size_t x, size_t y, char c);
    void set(char c);
    void print(bool clear = true);
    void clearTerminal();

    size_t getWidth() const;
    size_t getHeight() const;

    ~ScreenGrid();
};