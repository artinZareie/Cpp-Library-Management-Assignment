#include <TUI/Container.hpp>
#include <memory>

void Container::add(std::shared_ptr<Window> window) { m_windows.push_back(window); }
void Container::remove(std::shared_ptr<Window> window) { m_windows.erase(window); }

bool Container::click(std::size_t x, std::size_t y, std::function<void(std::size_t, std::size_t)> callback) {
    for (auto &window : m_windows) {
        window->click(x, y, callback);
        return true;
    }

    return false;
}