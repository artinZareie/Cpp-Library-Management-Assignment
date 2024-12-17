#pragma once
#include "Utils/ConstIterator.hpp"
#include <Utils/List.hpp>
#include <Utils/Iterator.hpp>
#include <cstdlib>
#include <functional>
#include <new>
#include <stdexcept>

template <typename T>
class ArrayList final : public List<T> {
private:
    T *m_data;
    std::size_t m_capacity, m_size;

private:
    bool is_full() const {
        return m_size == m_capacity;
    }

    void expand() {
        std::size_t alignment = alignof(T);
        T *new_data = reinterpret_cast<T *>(::operator new(sizeof(T) * m_capacity * 2, std::align_val_t(alignment)));
        for (std::size_t i = 0; i < m_size; ++i) {
            new (new_data + i) T(std::move(m_data[i]));
            m_data[i].~T();
        }

        ::operator delete(m_data, std::align_val_t(alignment));
        m_data = new_data;
        m_capacity *= 2;
    }

    void check_storage() {
        if (m_data == nullptr) {
            std::size_t alignment = alignof(T);
            m_data = reinterpret_cast<T *>(::operator new(sizeof(T) * 2, std::align_val_t(alignment)));
            m_capacity = 2;
            m_size = 0;
        }
    }

public:
    class iterator : public Iterator<T, iterator> {
    private:
        T *m_data;
        std::size_t m_index;

    public:
        iterator(T *data = nullptr, std::size_t index = 0) : m_data(data), m_index(index) {}
        T &operator*() override {
            return m_data[m_index];
        }

        iterator(const iterator &other) : m_data(other.m_data), m_index(other.m_index) {}

        iterator &operator++() override {
            ++m_index;
            return *this;
        }
        bool operator==(const iterator &other) const override {
            if (m_data == nullptr || other.m_data == nullptr) {
                return false;
            }

            return m_data == other.m_data && m_index == other.m_index;
        }

        bool operator!=(const iterator &other) const override {
            return m_index != other.m_index;
        } 

        void operator++(int) override {
            ++m_index;
        }

        iterator &operator=(const iterator &other) {
            m_data = other.m_data;
            m_index = other.m_index;
            return *this;
        }

        iterator &operator=(iterator &&other) = delete;

        friend class ArrayList;
    };

    struct const_iterator : public ConstIterator<T, const_iterator, iterator> {
    private:
        const T *m_data;
        std::size_t m_index;

    public:
        const_iterator(const T *data = nullptr, std::size_t index = 0) : m_data(data), m_index(index) {}
        const T operator*() const override {
            return m_data[m_index];
        }

        const_iterator(const const_iterator &other) : m_data(other.m_data), m_index(other.m_index) {}

        const_iterator &operator++() override {
            ++m_index;
            return *this;
        }
        bool operator==(const const_iterator &other) const override {
            return m_data == other.m_data && m_index == other.m_index;
        }

        bool operator!=(const const_iterator &other) const override {
            return m_index != other.m_index;
        }

        bool operator==(const iterator &other) const override {
            return m_data == other.m_data && m_index == other.m_index;
        }

        bool operator!=(const iterator &other) const override {
            return m_index != other.m_index;
        }

        void operator++(int) override {
            ++m_index;
        }

        const_iterator(const iterator &other) : m_data(other.m_data), m_index(other.m_index) {}

        const_iterator &operator=(const iterator &other) {
            m_data = other.m_data;
            m_index = other.m_index;
            return *this;
        }

        const_iterator &operator=(const const_iterator &other) {
            m_data = other.m_data;
            m_index = other.m_index;
            return *this;
        }
    };

public:
    explicit ArrayList(std::size_t size = 0, const T &data = T())
        : m_data(nullptr), m_capacity(0), m_size(0) {
        if (size > 0) {
            std::size_t alignment = alignof(T);
            m_capacity = (size + 1) * 2;
            m_data = reinterpret_cast<T *>(::operator new(sizeof(T) * m_capacity, std::align_val_t(alignment)));
            try {
                for (std::size_t i = 0; i < size; ++i) {
                    new (m_data + i) T(data);
                }
                m_size = size;
            } catch (...) {
                for (std::size_t i = 0; i < m_size; ++i) {
                    m_data[i].~T();
                }
                ::operator delete(m_data, std::align_val_t(alignment));
                m_data = nullptr;
                m_capacity = 0;
                throw;
            }
        }
    }

    ArrayList(const ArrayList &other) : m_data(new T[other.m_capacity]),
        m_capacity(other.m_capacity), m_size(other.m_size) {
        for (std::size_t i = 0; i < other.m_size; ++i) {
            new (m_data + i) T(other.m_data[i]);
        }
    }

    ArrayList(ArrayList &&other) : m_data(other.m_data), m_capacity(other.m_capacity), m_size(other.m_size) {
        other.m_data = nullptr;
        other.m_capacity = 0;
        other.m_size = 0;
    }

    void push_back(T data) override {
        check_storage();
        if (is_full()) {
            expand();
        }

        new (m_data + m_size++) T(data);
    }

    void push_front(T data) override {
        check_storage();
        if (is_full()) {
            expand();
        }

        for (std::size_t i = m_size; i > 0; --i) {
            m_data[i] = m_data[i - 1];
        }
        m_data[0] = data;
        ++m_size;
    }

    T &front() override {
        if (m_size == 0) {
            throw std::out_of_range("Index out of range");
        }

        return m_data[0];
    }

    T &back() override {
        if (m_size == 0) {
            throw std::out_of_range("Index out of range");
        }

        return m_data[m_size - 1];
    }

    void pop_front() override {
        if (m_size == 0) {
            throw std::out_of_range("Index out of range");
        }

        for (std::size_t i = 0; i < m_size - 1; ++i) {
            m_data[i] = m_data[i + 1];
        }
        --m_size;
    }

    void pop_back() override {
        if (m_size == 0) {
            throw std::out_of_range("Index out of range");
        }

        --m_size;
    }

    std::size_t size() const override {
        return m_size;
    }

    std::size_t capacity() const override {
        return m_capacity;
    }

    void clear() override {
        for (std::size_t i = 0; i < m_size; ++i) {
            m_data[i].~T();
        }

        m_size = 0;
    }

    T &operator[](std::size_t index) override {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }

        return m_data[index];
    }

    void erase(std::size_t index) override {
        if (index >= m_size) {
            throw std::out_of_range("Index out of range");
        }

        for (std::size_t i = index; i < m_size - 1; ++i) {
            m_data[i] = m_data[i + 1];
        }
        --m_size;
    }

    void insert(std::size_t index, T data) override {
        if (index > m_size) {
            throw std::out_of_range("Index out of range");
        }

        if (is_full()) {
            expand();
        }

        for (std::size_t i = m_size; i > index; --i) {
            m_data[i] = m_data[i - 1];
        }
        m_data[index] = data;
        ++m_size;
    }

    bool empty() const override {
        return m_size == 0;
    }

    void reserve(std::size_t new_capacity) {
        if (new_capacity <= m_capacity) {
            return;
        }

        std::size_t alignment = alignof(T);
        T *new_data = reinterpret_cast<T *>(::operator new(sizeof(T) * new_capacity, std::align_val_t(alignment)));
        for (std::size_t i = 0; i < m_size; ++i) {
            new (new_data + i) T(std::move(m_data[i]));
            m_data[i].~T();
        }

        ::operator delete(m_data, std::align_val_t(alignment));
        m_data = new_data;
        m_capacity = new_capacity;
    }

    iterator begin() {
        return iterator(m_data, 0);
    }

    iterator end() {
        return iterator(m_data, m_size);
    }

    void erase(iterator it) {
        std::size_t index = it.m_index - begin().m_index;
        erase(index);
    }

    iterator find(T data) {
        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_data[i] == data) {
                return iterator(m_data, i);
            }
        }

        return end();
    }

    // find with custom comparison function as template parameter.
    iterator find(T data, const std::function<bool(const T &, const T &)> &comp) {
        for (std::size_t i = 0; i < m_size; ++i) {
            if (comp(m_data[i], data)) {
                return iterator(m_data, i);
            }
        }

        return end();
    }

    void erase(T data) {
        iterator it = find(data);
        erase(it);
    }

    const_iterator cbegin() const {
        return const_iterator(m_data, 0);
    }

    const_iterator cend() const {
        return const_iterator(m_data, m_size);
    }

    const_iterator begin() const {
        return cbegin();
    }

    const_iterator end() const {
        return cend();
    }

    const_iterator cfind(T data) const {
        for (std::size_t i = 0; i < m_size; ++i) {
            if (m_data[i] == data) {
                return const_iterator(m_data, i);
            }
        }

        return cend();
    }

    const_iterator cfind(T data, const std::function<bool(const T &, const T &)> &comp) const {
        for (std::size_t i = 0; i < m_size; ++i) {
            if (comp(m_data[i], data)) {
                return const_iterator(m_data, i);
            }
        }

        return cend();
    }

    ~ArrayList() {
        for (std::size_t i = 0; i < m_size; ++i) {
            m_data[i].~T();
        }

        ::operator delete(m_data, std::align_val_t(alignof(T)));
    }
};