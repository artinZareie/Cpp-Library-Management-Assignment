#pragma once
#include <Utils/Iterator.hpp>
#include <Utils/List.hpp>
#include <cstddef>
#include <memory>
#include <stdexcept>

/*
* Class LinkedList
* Implementation of standard one-direction linked list.
*/
template<typename T>
class LinkedList final : public List<T> {
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
    struct iterator : public Iterator<T, iterator> {
        std::shared_ptr<Node> node;

        iterator(std::shared_ptr<Node> node) : node(node) {}

        T &operator*() override {
            return *node->data;
        }

        iterator &operator++() override {
            node = node->next;
            return *this;
        }

        void operator++(int) override {
            node = node->next;
        }

        bool operator==(const iterator &other) const override {
            return node == other.node;
        }

        bool operator!=(const iterator &other) const override {
            return node != other.node;
        }
    };
public:
    LinkedList(): m_head(nullptr), m_tail(nullptr), m_capacity(0) {}
    LinkedList(const LinkedList<T> &other): m_head(other.m_head), m_tail(other.m_tail), m_capacity(other.m_capacity) {}
    LinkedList(LinkedList<T> &&other): m_head(other.m_head), m_tail(other.m_tail), m_capacity(other.m_capacity) {
        other.m_head = nullptr;
        other.m_tail = nullptr;
        other.m_capacity = 0;
    }

    void operator=(const LinkedList<T> &other) {
        m_head = other.m_head;
        m_tail = other.m_tail;
        m_capacity = other.m_capacity;
    }

    void push_back(T data) override {
        if (!m_head) {
            m_head = std::make_shared<Node>(data);
            m_tail = m_head;
        } else {
            m_tail->next = std::make_shared<Node>(data);
            m_tail = m_tail->next;
        }

        ++m_capacity;
    }

    void push_front(T data) override {
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

    std::size_t size() const override {
        return m_capacity;
    }

    void clear() override {
        while (m_head) {
            m_head = m_head->next;
        }
        m_tail = nullptr;
        m_capacity = 0;
    }

    bool empty() const override {
        return m_capacity == 0;
    }

    void pop_front() override {
        if (!m_head) {
            throw std::out_of_range("Index out of range");
        }

        m_head = m_head->next;
        --m_capacity;
    }

    void pop_back() override {
        if (!m_head) {
            throw std::out_of_range("Index out of range");
        }

        std::shared_ptr<Node> node = m_head;
        for (std::size_t i = 0; i < m_capacity - 2; ++i) {
            node = node->next;
        }

        node->next = nullptr;
        m_tail = node;
        --m_capacity;
    }

    void insert(std::size_t index, T data) override {
        if (index > m_capacity) {
            throw std::out_of_range("Index out of range");
        }

        if (index == 0) {
            push_front(data);
        }

        if (index == m_capacity) {
            push_back(data);
        }

        std::shared_ptr<Node> node = m_head;
        for (std::size_t i = 0; i < index - 1; ++i) {
            node = node->next;
        }

        auto new_node = std::make_shared<Node>(data);
        new_node->next = node->next;
        node->next = new_node;
        ++m_capacity;
    }

    void erase(std::size_t index) override {
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

    T &front() override {
        return *m_head->data;
    }

    T &back() override {
        return *m_tail->data;
    }

    iterator begin() {
        return iterator(m_head);
    }

    iterator end() {
        return iterator(nullptr);
    }

    ~LinkedList() {
        m_head = nullptr;
        m_tail = nullptr;
        m_capacity = 0;
    }
};