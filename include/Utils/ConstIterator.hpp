#pragma once
#include <cstddef>

template <typename T, class Deriven, class Iterator>
class ConstIterator {
public:
    virtual const T operator*() const = 0;
    virtual const Deriven &operator++() = 0;
    virtual void operator++(int) = 0;
    virtual bool operator==(const Iterator &other) const = 0;
    virtual bool operator!=(const Iterator &other) const = 0;
    virtual bool operator==(const Deriven &other) const = 0;
    virtual bool operator!=(const Deriven &other) const = 0;
};