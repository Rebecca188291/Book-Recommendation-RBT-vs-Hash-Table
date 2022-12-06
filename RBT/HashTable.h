#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <cstdlib>
#include <iterator>
#include <unordered_map>
#include "Book.h"
using namespace std;

class HashTable
{
private:
    Book ourbook; // stores our ideal book
    // int buckets = 1000;
    unordered_map<int, vector<Book>> table;

public:
    HashTable();
    void getDesiredBook(Book book);
    void insert(Book book);
    void getTop5();
    void traverse(vector<Book>& endvec, int goalkey);
};
