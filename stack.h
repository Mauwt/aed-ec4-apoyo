#pragma once

#include "forward_list.h"

template <class T>
class Stack {
private:
    forward_list<T> list;
public:

    Stack() = default;

    void push(const T& data) {
        this->list.push_back(data);
    }

    T pop() {
        if (this->list.is_empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return this->list.pop_back();
    }

    T top() {
        if (this->list.is_empty()) {
            throw std::runtime_error("Stack is empty");
        }
        return this->list.back();
    }

    bool empty() {
        return this->list.is_empty();
    }

    int size() const {
        return this->list.size();
    }

    void clear() {
        this->list.clear();
    }
};