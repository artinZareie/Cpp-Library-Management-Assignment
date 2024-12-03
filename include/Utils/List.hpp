#pragma once

template<typename T>
class List {
public:
    virtual void push_back(T data) = 0;
    virtual T &front() = 0;
    virtual void pop_front() = 0;
    virtual T &back() = 0;
    virtual void pop_back() = 0;
    virtual void insert(int position, T data) = 0;
    virtual void erase(int position) = 0;
    virtual int size() = 0;
    virtual void clear() = 0;

private:
    virtual ~List() = default;
};