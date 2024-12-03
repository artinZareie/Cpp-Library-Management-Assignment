#pragma once
#include <cstddef>

template<typename T, typename Derived>
class Iterator {
public:
    virtual T& operator*() = 0;
    virtual Derived &operator++() = 0;
    virtual void operator++(int) = 0;
    virtual bool operator==(const Derived &other) const = 0;
    virtual bool operator!=(const Derived &other) const = 0;
};