#pragma once

#include <iostream>
#include "list.h"

template <typename T>
class CircularList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node() : next(nullptr), prev(nullptr) {}

        Node(T value) : data(value), next(nullptr), prev(nullptr) {}

        void killSelf() {
            delete this;
        }
    };

private:
    Node* head; // sentinel
    int nodes;

public:
    CircularList() : List<T>(), head(nullptr), nodes(0) {}

    ~CircularList() {
        clear();
    }

    T front() {
        if (is_empty())
            throw std::runtime_error("Lista vacía");
        return head->next->data;
    }

    T back() {
        if (is_empty())
            throw std::runtime_error("Lista vacía");
        return head->prev->data;
    }

    void push_front(T data) {
        Node* newNode = new Node(data);
        if (is_empty()) {
            newNode->next = newNode;
            newNode->prev = newNode;
            head = newNode;
        } else {
            newNode->next = head->next;
            newNode->prev = head;
            head->next->prev = newNode;
            head->next = newNode;
        }
        nodes++;
    }

    void push_back(T data) {
        push_front(data);
        head = head->next;
    }

    T pop_front() {
        if (is_empty())
            throw std::runtime_error("Lista vacía");
        Node* temp = head->next;
        T data = temp->data;
        head->next = temp->next;
        temp->next->prev = head;
        delete temp;
        nodes--;
        return data;
    }

    T pop_back() {
        if (is_empty())
            throw std::runtime_error("Lista vacía");
        head = head->prev;
        T data = pop_front();
        return data;
    }

    bool insert(T data, int pos) {
        if (pos < 0 || pos > nodes)
            throw std::out_of_range("Índice fuera de rango");
        if (pos == 0) {
            push_front(data);
        } else if (pos == nodes) {
            push_back(data);
        } else {
            Node* current = head->next;
            for (int i = 0; i < pos - 1; i++)
                current = current->next;
            Node* newNode = new Node(data);
            newNode->next = current->next;
            newNode->prev = current;
            current->next->prev = newNode;
            current->next = newNode;
            nodes++;
        }
        return true;
    }

    bool remove(int pos) {
        if (pos < 0 || pos >= nodes)
            return false;
        if (pos == 0) {
            pop_front();
        } else if (pos == nodes - 1) {
            pop_back();
        } else {
            Node* current = head->next;
            for (int i = 0; i < pos; i++)
                current = current->next;
            current->prev->next = current->next;
            current->next->prev = current->prev;
            delete current;
            nodes--;
        }
        return true;
    }

    T& operator[](int pos) {
        if (pos < 0 || pos >= nodes)
            throw std::out_of_range("Índice fuera de rango");
        Node* current = head->next;
        for (int i = 0; i < pos; i++)
            current = current->next;
        return current->data;
    }

    bool is_empty() {
        return nodes == 0;
    }

    int size() {
        return nodes;
    }

    void clear() {
        while (!is_empty())
            pop_front();
    }

    void sort() {
        if (!is_empty())
            quicksort(head->next, head->prev);
    }

    void quicksort(Node* left, Node* right) {
        if (left != right && right != left->prev) {
            Node* pivot = partition(left, right);
            quicksort(left, pivot->prev);
            quicksort(pivot->next, right);
        }
    }

    Node* partition(Node* left, Node* right) {
        T pivot = right->data;
        Node* i = left->prev;
        for (Node* j = left; j != right; j = j->next) {
            if (j->data <= pivot) {
                i = (i == nullptr) ? left : i->next;
                std::swap(i->data, j->data);
            }
        }
        i = (i == nullptr) ? left : i->next;
        std::swap(i->data, right->data);
        return i;
    }

    bool is_sorted() {
        if (is_empty() || size() == 1)
            return true;

        Node* current = head->next;
        while (current->next != head) {
            if (current->data > current->next->data)
                return false;
            current = current->next;
        }

        if (current->data > head->prev->data)
            return false;

        return true;
    }

    void reverse() {
        if (is_empty() || size() == 1)
            return;
        Node* current = head->next;
        do {
            Node* temp = current->next;
            current->next = current->prev;
            current->prev = temp;
            current = temp;
        } while (current != head->next);
        head->prev = head->next;
        head->next = current->prev;
    }

    std::string name() {
        return "CircularList";
    }
};


