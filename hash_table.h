#pragma once
#include <string>

using namespace std;

#define MAX_COLLISION 5

class HashTable
{
private:
    struct Node
    {
        string key;
        int value;
        Node *next;
    };

    Node **table;
    int size;  // Size of the table
    int count; // Number of elements in the table

public:
    HashTable() : size(5), count(0)
    {
        table = new Node *[size];
        for (int i = 0; i < size; i++)
        {
            table[i] = nullptr;
        }
    }

    void set(string key, int value)
    {
        int index = hash(key);
        Node *newNode = new Node;
        newNode->key = key;
        newNode->value = value;
        newNode->next = nullptr;

        if (table[index] == nullptr)
        {
            table[index] = newNode;
        }
        else
        {
            Node *temp = table[index];
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    int get(string key)
    {
        int index = hash(key);
        Node *temp = table[index];
        while (temp != nullptr)
        {
            if (temp->key == key)
            {
                return temp->value;
            }
            temp = temp->next;
        }
        return -1;
    }

    int hash(string key)
    {
        int hash = 0;
        for (int i = 0; i < key.length(); i++)
        {
            hash += key[i];
        }
        return hash % size;
    }

private:
    void rehashing(){

    }
};

