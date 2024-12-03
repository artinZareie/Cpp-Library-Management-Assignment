#pragma once

#include <cstddef>
template<typename T>
class List {
public:
    virtual void push_front(T data) = 0;
    virtual void push_back(T data) = 0;
    virtual T &front() = 0;
    virtual void pop_front() = 0;
    virtual T &back() = 0;
    virtual void pop_back() = 0;
    virtual void insert(std::size_t position, T data) = 0;
    virtual void erase(std::size_t position) = 0;
    virtual std::size_t size() const = 0;
    virtual std::size_t capacity() const {
        return size();
    }
    virtual T &operator[](std::size_t position) = 0;
    virtual void clear() = 0;
    virtual bool empty() const = 0;
};