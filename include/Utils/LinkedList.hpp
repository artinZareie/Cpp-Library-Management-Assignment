#pragma once
#include <Utils/Iterator.hpp>
#include <cstddef>
#include <memory>
#include <stdexcept>

/*
* Class LinkedList
* Implementation of standard one-direction linked list.
*/
template<typename T>
class LinkedList {
private:
    struct Node {
        std::unique_ptr<T> data;
        std::shared_ptr<Node> next; 

        Node(T data) : data(std::make_unique<T>(data)), next(nullptr) {}

        std::shared_ptr<Node> operator++() {
            return next;
        }
    };

    std::shared_ptr<Node> m_head;
    std::shared_ptr<Node> m_tail;
    std::size_t m_capacity;
public:
    struct iterator : Iterator<T> {
        std::shared_ptr<Node> node;

        iterator(std::shared_ptr<Node> node) : node(node) {}

        T &operator*() {
            return *node->data;
        }

        void operator++(int) {
            node = node->next;
        }

        bool operator==(const iterator &other) const {
            return node == other.node;
        }

        bool operator!=(const iterator &other) const {
            return node != other.node;
        }
    };
public:
    LinkedList(): m_head(nullptr), m_tail(nullptr), m_capacity(0) {}

    void push_back(T data) {
        if (!m_head) {
            m_head = std::make_shared<Node>(data);
            m_tail = m_head;
        } else {
            m_tail->next = std::make_shared<Node>(data);
            m_tail = m_tail->next;
        }

        ++m_capacity;
    }

    void push_front(T data) {
        if (!m_head) {
            m_head = std::make_shared<Node>(data);
            m_tail = m_head;
        } else {
            auto new_node = std::make_shared<Node>(data);
            new_node->next = m_head;
            m_head = new_node;
        }

        ++m_capacity;
    }

    T &operator[](std::size_t index) {
        if (index >= m_capacity) {
            throw std::out_of_range("Index out of range");
        }

        std::shared_ptr<Node> node = m_head;
        for (std::size_t i = 0; i < index; ++i) {
            node = node->next;
        }

        return *node->data;
    }

    std::size_t size() const {
        return m_capacity;
    }

    void clear() {
        while (m_head) {
            m_head = m_head->next;
        }
        m_tail = nullptr;
        m_capacity = 0;
    }

    bool empty() const {
        return m_capacity == 0;
    }

    void pop_front() {
        if (!m_head) {
            throw std::out_of_range("Index out of range");
        }

        m_head = m_head->next;
        --m_capacity;
    }

    void erase(std::size_t index) {
        if (index >= m_capacity) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            m_head = m_head->next;
        } else {
            std::shared_ptr<Node> node = m_head;
            for (std::size_t i = 0; i < index - 1; ++i) {
                node = node->next;
            }

            node->next = node->next->next;
        }

        --m_capacity;
    }

    T &front() {
        return *m_head->data;
    }

    T &back() {
        return *m_tail->data;
    }

    iterator begin() {
        return iterator(m_head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    ~LinkedList() {
        while (!m_head) {
            m_head = m_head->next;
        }

        m_tail = nullptr;
        m_capacity = 0;
    }
};