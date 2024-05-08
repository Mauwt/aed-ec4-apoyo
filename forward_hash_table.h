#pragma once
#include <string>
#include <utility>
#include "forward_list.h"

using namespace std;

#define MAX_COLLISION 5

class HashTable
{
private:
    ForwardList<pair<string, int>>* table;
    int size;  // Size of the table
    int count; // Number of elements in the table
    std::hash<string> hash_fn;

public:
    HashTable() : size(5), count(0)
    {
        table = new ForwardList<pair<string, int>>[size];
    }


    bool isEmpty() const;
    int hashFunction(string key);
    void removeItem(string key){
        size_t hash_code = hashFunction(key);
        int index = hash_code % size;

        for (int i = 0; i<table[index].size(); i++){
            if(table[index][i].first == key){
                table[index].remove(i);
                break;
            }
        }
    };

    void set(string key, int value)
    {
        size_t hash_code = hash_fn(key);
        int index = hash_code % size;

        if(table[index].size() > MAX_COLLISION){
            rehashing();
         }

         table[index].push_back(make_pair(key, value));
    }

    int get(string key){
        size_t hash_code = hash_fn(key);
        int index = hash_code % size;

        for (int i = 0; i<table[index].size(); i++){
            if(table[index][i].first == key){
                return table[index][i].second;
            }
        }
        return -1;
    }

private:
    void rehashing(){
        auto new_table = new ForwardList<pair<string,int>> [size*2];

        for (int pos = 0; pos < size; pos++){
            for (int i = 0; i<table[pos].size(); i++){
                size_t hash_code = hash_fn(table[pos][i].first);
                int index = hash_code % (size*2);
                new_table[index].push_back(make_pair(table[pos][i].first, table[pos][i].second));
            }
        }
        delete[] table;
        table = new_table;
        size *= 2;
    }
};

