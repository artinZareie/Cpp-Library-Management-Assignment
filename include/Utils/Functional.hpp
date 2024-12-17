#pragma once
#include <memory>

template<typename T>
bool sharedEq(const std::shared_ptr<T> &lhs, const std::shared_ptr<T> &rhs) {
    if (lhs == rhs) {
        return true;
    }

    if (!lhs || !rhs) {
        return false;
    }

    const T &dlhs = *lhs;
    const T &drhs = *rhs;

    return dlhs == drhs;
}

template<typename T>
bool sharedNeq(const std::shared_ptr<T> &lhs, const std::shared_ptr<T> &rhs) {
    return !sharedEq(lhs, rhs);
}

template<typename T, typename U>
bool sharedEq(const T &lhs, const std::shared_ptr<U> &rhs) {
    if (!rhs) {
        return false;
    }

    const U &drhs = *rhs;

    return lhs == drhs;
}

template<typename T, typename U>
bool sharedNeq(const T &lhs, const std::shared_ptr<U> &rhs) {
    return !sharedEq(lhs, rhs);
}

template<typename T, typename U>
bool sharedEq(const std::shared_ptr<T> &lhs, const U &rhs) {
    if (!lhs) {
        return false;
    }

    const T &dlhs = *lhs;

    return dlhs == rhs;
}

template<typename T, typename U>
bool sharedNeq(const std::shared_ptr<T> &lhs, const U &rhs) {
    return !sharedEq(lhs, rhs);
}