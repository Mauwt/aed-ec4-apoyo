#include <iostream>
#include "list.h"

// TODO: Implement all methods
template <typename T>
class DoubleList : public List<T> {
private:
    struct Node {
        T data;
        Node* next;
        Node* prev;

        Node(){
            next = nullptr;
            prev = nullptr;
        }

        Node(T value){
            data = value;
            next = nullptr;
            prev = nullptr;
        }

        void killSelf(){
            if (next != nullptr)
                next->killSelf();
            delete this;
        }
    };

private:
    Node* head;
    Node* tail;
    int nodes;

public:
    DoubleList() : List<T>() {}

    ~DoubleList(){
        clear();
    }

    T front(){
        if (head == nullptr)
            throw ("Lista vacia");
        return head->data;
    }

    T back(){
        if (tail == nullptr)
            throw ("Lista vacia");
        return tail->data;
    }

    void push_front(T data){
        Node* newNode = new Node(data);
        if (is_empty()){
            head = newNode;
            tail = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        nodes++;
    }

    void push_back(T data){
        Node* newNode = new Node(data);
        if (is_empty()){
            head = newNode;
            tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    T pop_front(){
        if (is_empty())
            throw ("Lista vacia");
        T data = head->data;
        Node* temp = head;
        head = head->next;
        if (head != nullptr)
            head->prev = nullptr;
        delete temp;
        nodes--;
        return data;
    }

    T pop_back(){
        if (is_empty())
            throw ("Lista vacia");
        T data = tail->data;
        Node* temp = tail;
        tail = tail->prev;
        if (tail != nullptr)
            tail->next = nullptr;
        delete temp;
        nodes--;
        return data;
    }

    T insert(T data, int pos){
        if (pos < 0 || pos > nodes)
            throw ("Posicion invalida");
        if (pos == 0){
            push_front(data);
            return data;
        }
        if (pos == nodes){
            push_back(data);
            return data;
        }
        Node* newNode = new Node(data);
        Node* temp = head;
        for (int i = 0; i < pos - 1; i++)
            temp = temp->next;
        newNode->next = temp->next;
        newNode->prev = temp;
        temp->next->prev = newNode;
        temp->next = newNode;
        nodes++;
        return data;
    }

    bool remove(int pos){
        if (pos < 0 || pos >= nodes)
            return false;
        if (pos == 0){
            pop_front();
            return true;
        }
        if (pos == nodes - 1){
            pop_back();
            return true;
        }
        Node* temp = head;
        for (int i = 0; i < pos - 1; i++)
            temp = temp->next;
        Node* toDelete = temp->next;
        temp->next = toDelete->next;
        toDelete->next->prev = temp;
        delete toDelete;
        nodes--;
        return true;
    }

    T& operator[](int pos){
        if (is_empty())
            throw ("Lista vacia");
        if (pos < 0 || pos >= nodes)
            throw ("Posicion invalida");
        Node* temp = head;
        for (int i = 0; i < pos; i++)
            temp = temp->next;
        return temp->data;
    }

    bool is_empty(){
        if (head == nullptr)
            return true;
        return false;
    }

    int size(){
        return nodes;
    }

    void clear(){
        if (head == nullptr)
            return;
        head->killSelf();
        head = nullptr;
        tail = nullptr;
        nodes = 0;
    }

    void sort(){
        if (is_empty())
            return;
        Node* temp = head;
        while (temp->next != nullptr){
            Node* temp2 = temp->next;
            while (temp2 != nullptr){
                if (temp->data > temp2->data){
                    T aux = temp->data;
                    temp->data = temp2->data;
                    temp2->data = aux;
                }
                temp2 = temp2->next;
            }
            temp = temp->next;
        }
    }

    bool is_sorted(){
        if (is_empty())
            return true;
        Node* temp = head;
        while (temp->next != nullptr){
            if (temp->data > temp->next->data)
                return false;
            temp = temp->next;
        }
        return true;
    }

    void reverse(){
        if (is_empty())
            return;
        Node* temp = head;
        head = tail;
        tail = temp;
        while (temp != nullptr){
            Node* aux = temp->next;
            temp->next = temp->prev;
            temp->prev = aux;
            temp = aux;
        }
    }

    std::string name(){
        return "ForwardList";
    }

};