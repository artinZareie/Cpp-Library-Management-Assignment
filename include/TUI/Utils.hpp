#pragma once
#include <cstddef>

#ifdef _WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>

    std::size_t getTerminalWidth();
    std::size_t getTerminalHeight();
#else
    #include <unistd.h>

    std::size_t getTerminalWidth();
    std::size_t getTerminalHeight();
#endif