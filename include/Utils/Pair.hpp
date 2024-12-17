#pragma once

#include <algorithm>
template<typename T1, typename T2>
class Pair {
private:
    T1 m_first;
    T2 m_second;

public:
    Pair(T1 first, T2 second) : m_first(first), m_second(second) {}
    Pair(const Pair &other) : m_first(other.m_first), m_second(other.m_second) {}
    Pair(Pair &&other) : m_first(std::move(other.m_first)), m_second(std::move(other.m_second)) {}

    T1 &first() { return m_first; }
    T2 &second() { return m_second; }

    const T1 &first() const { return m_first; }
    const T2 &second() const { return m_second; }

    Pair &operator=(const Pair &other) {
        m_first = other.m_first;
        m_second = other.m_second;
        return *this;
    }

    Pair &operator=(Pair &&other) {
        m_first = std::move(other.m_first);
        m_second = std::move(other.m_second);
        return *this;
    }

    Pair<T2, T1> swap() {
        return Pair<T2, T1>(m_second, m_first);
    }
};