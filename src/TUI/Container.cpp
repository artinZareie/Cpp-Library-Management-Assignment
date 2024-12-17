#include <TUI/Container.hpp>
#include <memory>
#include <optional>

void Container::add(std::shared_ptr<Window> window) { m_windows.push_back(window); }
void Container::remove(std::shared_ptr<Window> window) { m_windows.erase(window); }

std::optional<std::shared_ptr<Window>> Container::click(std::size_t x, std::size_t y) {
    for (auto it = m_windows.begin(); it != m_windows.end(); ++it) {
        if ((*it)->click(x, y)) {
            return *it;
        }
    }

    return std::nullopt;
}