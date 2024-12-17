#include <TUI/Utils.hpp>
#include <TUI/ScreenGrid.hpp>
#include <cstddef>
#include <iostream>

ScreenGrid::ScreenGrid(size_t width, size_t height) : m_width(width), m_height(height) {
    m_grid = new char*[m_height];

    for (size_t i = 0; i < m_height; ++i) {
        m_grid[i] = new char[m_width];
        for (size_t j = 0; j < m_width; ++j) {
            m_grid[i][j] = ' ';
        }
    }
}

const size_t ScreenGrid::DEFAULT_MARGIN = 3;

ScreenGrid &ScreenGrid::getInstance() {
    static ScreenGrid instance(getTerminalWidth() - DEFAULT_MARGIN * 2, getTerminalHeight() - DEFAULT_MARGIN * 2);
    return instance;
}

void ScreenGrid::set(size_t x, size_t y, char c) {
    m_grid[y][x] = c;
}

void ScreenGrid::set(char c) {
    for (size_t i = 0; i < m_height; ++i) {
        for (size_t j = 0; j < m_width; ++j) {
            m_grid[i][j] = c;
        }
    }
}

void ScreenGrid::print(bool clear) {
    if (clear) {
        clearTerminal();
    }

    for (int i = 0; i < DEFAULT_MARGIN; ++i) {
        std::cout << std::endl;
    }

    for (size_t i = 0; i < m_height; ++i) {
        for (int j = 0; j < DEFAULT_MARGIN; ++j) {
            std::cout << " ";
        }

        for (size_t j = 0; j < m_width; ++j) {
            std::cout << m_grid[i][j];
        }
        std::cout << std::endl;
    }
}

ScreenGrid::~ScreenGrid() {
    for (size_t i = 0; i < m_height; ++i) {
        delete[] m_grid[i];
    }
    delete[] m_grid;
}

void ScreenGrid::clearTerminal() {
    #ifdef WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

std::size_t ScreenGrid::getWidth() const { return m_width; }
std::size_t ScreenGrid::getHeight() const { return m_height; }