#pragma once

template<typename T>
class Iterator {
public:
    virtual T& operator*() = 0;
    virtual void operator++(int) = 0;
    virtual bool operator==(Iterator<T> &other) const = 0;
    virtual bool operator!=(Iterator<T> &other) const = 0;
};