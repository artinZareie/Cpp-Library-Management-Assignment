#pragma once
#include <cstddef>

template<typename T, typename Deriven>
class Iterator {
public:
    virtual T& operator*() = 0;
    virtual Deriven &operator++() = 0;
    virtual void operator++(int) = 0;
    virtual bool operator==(const Deriven &other) const = 0;
    virtual bool operator!=(const Deriven &other) const = 0;
};