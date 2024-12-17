#include <TUI/Utils.hpp>

#ifdef _WIN32
    #include <Windows.h>
    std::size_t getTerminalWidth() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return static_cast<std::size_t>(csbi.dwSize.X);
    }

    std::size_t getTerminalHeight() {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return static_cast<std::size_t>(csbi.dwSize.Y);
    }

#else
    #include <unistd.h>
    #include <sys/ioctl.h>

    std::size_t getTerminalWidth() {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_col;
    }

    std::size_t getTerminalHeight() {
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        return w.ws_row;
    }
#endif