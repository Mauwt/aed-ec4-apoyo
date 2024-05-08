#pragma once

#include <iostream>

using namespace std;

template<typename T>
class CircularArray {
private:
    T *array;
    int capacity;
    int back = -1, front = -1;

public:
    explicit CircularArray(int _capacity = 10);

    void resize();

    virtual ~CircularArray() {
        delete[] array;
    }

    void push_front(T data);

    void push_back(T data);

    void insert(T data, int pos);

    T pop_front();

    T pop_back();

    bool is_full();

    bool is_empty();

    int size();

    void clear();

    T &operator[](int index);

    bool is_sorted();

    void reverse();

    string to_string(string sep = " ");

    void sort();

    void quickSort(int left, int right);

    int partition(int left, int right);

private:
    int next(int index);

    int prev(int index);
};


template<class T>
CircularArray<T>::CircularArray(int _capacity) {
    this->capacity = _capacity;
    this->array = new T[_capacity];
    this->front = this->back = -1;//empty
}

template<class T>
void CircularArray<T>::resize() {
    int new_capacity = capacity + capacity / 2;
    T *new_array = new T[new_capacity];
    for (int i = 0; i < capacity; i++)
        new_array[i] = array[(front + i) % capacity];
    front = 0;
    back = capacity - 1;
    capacity *= 2;
    delete[] array;
    array = new_array;
}

template<class T>
void CircularArray<T>::push_front(T data) {
    if (is_empty()) {
        front = back = 0;
        array[front] = data;
        return;
    }
    if (is_full()) {
        resize();
    }

    front = prev(front);
    array[front] = data;
}


template<class T>
void CircularArray<T>::push_back(T data) {
    if (is_empty()) {
        front = back = 0;
        array[back] = data;
        return;
    }

    if (is_full())
        resize();

    back = next(back);
    array[back] = data;

}


template<class T>
void CircularArray<T>::insert(T data, int pos) {
    if (pos < 0 || pos > size())
        throw runtime_error("Out of bounds");

    if (next(back) == front)
        resize();

    if (pos == 0)
        push_front(data);

    else if (pos == size())
        push_back(data);

    else {
        int current_idx = back % capacity;
        while (current_idx != pos) {
            array[(current_idx + 1) % capacity] = array[current_idx];
            current_idx = prev(current_idx);
        }

        array[(current_idx + 1) % capacity] = data;
        back = next(back);
    }
}

template<class T>
T CircularArray<T>::pop_front() {
    if (is_empty())
        throw std::out_of_range("Array is empty");

    T ans = array[front];
    if (front == back)
        front = back = -1;
    else
        front = next(front);
    return ans;
}


template<class T>
T CircularArray<T>::pop_back() {
    if (is_empty())
        throw std::out_of_range("Array is empty");

    T ans = array[back];
    if (front == back)
        front = back = -1;
    else
        back = prev(back);

    return ans;
}

template<class T>
bool CircularArray<T>::is_full() {
    return (next(back) == front);
}

template<class T>
bool CircularArray<T>::is_empty() {
    return front == -1 && back == -1;
}

template<class T>
int CircularArray<T>::size() {
    if (front == -1 && back == -1) return 0;
    else return (back - front + capacity) % capacity + 1;
}

template<class T>
void CircularArray<T>::clear() {
    front = back = -1;
}


template<class T>
bool CircularArray<T>::is_sorted() {
    bool ok = true;
    for (int i = front; i != next(back); i = next(i)) {
        if (array[i] > array[i + 1]) {
            ok = false;
            break;
        }
    }
    return false;
}

template<class T>
void CircularArray<T>::reverse() {
    for (int i = front, j = back, k = 0; k < size() / 2; i = next(i), j = prev(j), k++) {
        swap(array[i], array[j]);
    }
}

template<class T>
string CircularArray<T>::to_string(std::string sep) {
    string ans;
    for (int i = 0; i < size(); ++i) {
        ans += std::to_string(array[(front + i) % capacity]) + sep;
    }
    return ans;
}

template<class T>
void CircularArray<T>::sort() {
    quickSort(0, size() - 1);
}

template<class T>
void CircularArray<T>::quickSort(int left, int right) {
    if (left < right) {
        int pivotIndex = partition(left, right);

        quickSort(left, pivotIndex - 1);

        quickSort(pivotIndex + 1, right);
    }
}

template<class T>
int CircularArray<T>::partition(int left, int right) {
    T pivot = array[(front + right) % capacity];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (array[(front + j) % capacity] <= pivot) {
            i++;
            swap(array[(front + i) % capacity], array[(front + j) % capacity]);
        }
    }
    swap(array[(front + i + 1) % capacity], array[(front + right) % capacity]);
    return i + 1;
}

template<class T>
int CircularArray<T>::next(int index) {
    return (index + 1) % capacity;
}

template<class T>
int CircularArray<T>::prev(int index) {
    return (index - 1 + capacity) % capacity;
}

template<typename T>
T &CircularArray<T>::operator[](int index) {
    return array[(front + index) % capacity];
}




