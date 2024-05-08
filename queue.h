#pragma once

#include "circular_array.h"

template<typename T>
class QueueArray : public CircularArray<T> {

public:
    QueueArray(int _capacity = 10) : CircularArray<T>(_capacity) {}

    void enqueue(T data) {
        if (this->is_full())
            this->resize();

        this->push_back(data);
    }

    T dequeue() {
        if (this->is_empty())
            throw std::out_of_range("Queue is empty");

        T data = this->pop_front();
        return data;
    }

    void display() {
        cout << this->to_string() << endl;
    }

    T front() {
        return this->array[this->front];
    }

    T back() {
        return this->array[this->back];
    }

    int size() {
        return this->size();
    }
};