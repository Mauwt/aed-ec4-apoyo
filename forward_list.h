#pragma once
#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class ForwardList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;

        Node(): next(nullptr) {}

        explicit Node(T value): data(value), next(nullptr) {}

        void killSelf(){}
    };

private:
    Node* head = nullptr;
    int nodes;
    bool isSorted = false;

    Node* partition(Node* beg, Node* end, Node** newHead, Node** newEnd){
        Node* pivot = end;
        Node* prev = nullptr;
        Node* cur = beg;
        Node* tail = pivot;

        while (cur != pivot){
            if (cur->data < pivot->data){
                if ((*newHead) == nullptr)
                    (*newHead) = cur;

                prev = cur;
                cur = cur->next;
            } else {
                if (prev)
                    prev->next = cur->next;

                Node* temp = cur->next;
                cur->next = nullptr;
                tail->next = cur;
                tail = cur;
                cur = temp;
            }
        }

        if ((*newHead) == nullptr)
            (*newHead) = pivot;

        (*newEnd) = tail;

        return pivot;
    }

    Node* quickSortRecur(Node* beg, Node* end){
        if (!beg || beg == end)
            return beg;

        Node* newHead = nullptr;
        Node* newEnd = nullptr;

        Node* pivot = partition(beg, end, &newHead, &newEnd);

        if (newHead != pivot){
            Node* temp = newHead;
            while (temp->next != pivot)
                temp = temp->next;

            temp->next = nullptr;

            newHead = quickSortRecur(newHead, temp);

            temp = getTail(newHead);
            temp->next = pivot;
        }

        pivot->next = quickSortRecur(pivot->next, newEnd);

        return newHead;
    }

    Node* getTail(Node* beg){
        Node* temp = beg;
        while (temp != nullptr && temp->next != nullptr)
            temp = temp->next;

        return temp;
    }

public:
    ForwardList() : List<T>(), nodes(0) {}

    ~ForwardList(){
        clear();
    }

    T front(){
        if (head == nullptr) {
            throw std::out_of_range("empty list");
        }
        return head->data;
    }

    T back(){
        if (head == nullptr) {
            throw std::out_of_range("empty list");
        }

        Node *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        return temp->data;
    }

    void push_front(T data){
        auto *new_node = new Node;

        new_node->data = data;
        new_node->next = head;

        head = new_node;
        nodes++;
    }

    void push_back(T data){
        auto *new_node = new Node;
        new_node->data = data;
        new_node->next = nullptr;

        if (head == nullptr) {
            head = new_node;
            return;
        }

        Node *temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        temp->next = new_node;
        nodes++;
    }

    T pop_front(){
        if (head == nullptr) {
            throw std::out_of_range("Empty list");
        }


        if (head->next == nullptr) {
            T res = head->data;
            delete head;
            head = nullptr;
            return res;
        }

        T res = head->data;
        Node *temp = head;
        head = head->next;
        delete temp;
        nodes--;
        return res;
    }

    T pop_back(){
        if (head == nullptr)
            throw std::out_of_range("empty list");

        if (head->next == nullptr) {
            T res = head->data;
            delete head;
            head = nullptr;
            return res;
        }

        Node *temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }

        T res = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        nodes--;
        return res;
    }

    bool insert(T data, int pos){

        if (pos < 0 || pos > nodes)
            return false;

        if (pos == 0) {
            push_front(data);
            return true;
        }

        if (pos == nodes) {
            push_back(data);
            return true;
        }

        Node *new_node = new Node;
        new_node->data = data;

        Node *temp = head;
        for (int i = 0; i < pos - 1; i++) {
            temp = temp->next;
        }

        new_node->next = temp->next;
        temp->next = new_node;

        nodes++;
        return true;
    }

    bool remove(int pos){
        if (pos < 0 || pos > nodes) return false;

        if (pos == 0) {
            pop_front();
            return true;
        }

        if (pos == nodes - 1) {
            pop_back();
            return true;
        }

        Node* aux = head;

        for (int i = 0; i< pos-1; i++){
            aux = aux->next;
        }

        Node* temp = aux->next;

        aux->next = aux->next->next;

        temp->next = nullptr;
        delete temp;
        nodes--;
        return true;
    }

    T& operator[](int pos){
        if(this->is_empty())
            throw ("empty list");

        if( pos <0 || pos > this->nodes)
            throw ("position out of range");

        Node * aux = head;
        for(int i = 0; i < pos; i++){
            aux = aux->next;
        }

        return aux->data;
    }

    bool is_empty(){
        return head == nullptr;
    }

    int size(){
        return nodes;
    }

    void clear(){
        if (head == nullptr)
            return;

        while (head != nullptr) {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
    }

    void sort(){
        head = quickSortRecur(head, getTail(head));
        isSorted = true;
    };

    bool is_sorted(){
        return isSorted;
    }

    void reverse(){
        if (head == nullptr) {
            throw ("empty list");
        }

        if (head->next == nullptr)
            return;

        Node *temp1 = head;
        Node *temp2 = head->next;
        head->next = nullptr;
        while (temp2 != nullptr) {
            head = temp2;
            temp2 = temp2->next;
            head->next = temp1;
            temp1 = head;
        }
    }

    std::string name(){
        return "ForwardList";
    }

};