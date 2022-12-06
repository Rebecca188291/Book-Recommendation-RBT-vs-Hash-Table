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

HashTable::HashTable()
{

}

// need to read in our ideal book in some way
void HashTable::getDesiredBook(Book book)
{
    // my need to read in the data points one by one?
    ourbook = book;
}

void HashTable::insert(Book book)
{
    int key = book.wordCount;
    // highest is about 4mil, there are 3 at about a mil, most are like a few hundred thousand
    // so if we take the value, divide by 1000 and just store it like that
    int hashval = key / 1000;
    if (hashval >= 1000)
    {
        // ensures that we dont go over 1000 buckets
        table[999].push_back(book);
    }
    else
    {
        // puts book into the vector stored at table[hashval]
        table[hashval].push_back(book);
    }
}

void HashTable::getTop5()
{
    // make sure.wordCount is going in as an int, else cast it to one
    int goalkey = ourbook.wordCount / 1000;
    vector<Book> endvec;

    //if table[goal] exists
    if (table.find(goalkey) != table.end())
    {
        // there is a vector at goalkey
        vector<Book> bookvec = table.at(goalkey);
        for (int i = 0; i < bookvec.size(); i++)
        {
            endvec.push_back(bookvec.at(i));

        }
        if (endvec.size() < 5)
        {
            traverse(endvec, goalkey);
        }
    }
    else
    { // vector not at goalkey
        traverse(endvec, goalkey);
    }

    // narrow down endvec
    // stores the difference and the index
    map<int, int> narrowingmap;
    vector<Book> printvec;

    for (int i = 0; i < endvec.size(); i++)
    {
        int difference = abs(endvec.at(i).wordCount - ourbook.wordCount);
        if (narrowingmap.find(difference) == narrowingmap.end())
        {
            narrowingmap.emplace(difference, i);
        }
        // this just shifts all by 1 to ensure that if there are repeats they both make it into the map
        else
        {
            narrowingmap.emplace(difference + 1, i);
        }
    }

    map<int, int>::iterator it;
    for (it = narrowingmap.begin(); it != narrowingmap.end(); it++)
    {
        if (printvec.size() == 5)
        {
            break;
            it = narrowingmap.end();
        }
        else
        {
            printvec.push_back(endvec.at(it->second));
        }
    }

    cout << endl;
    cout << "Your top 5 recommended books are: " << endl;
    cout << endl;
    for (int i = 0; i < printvec.size(); i++)
    {
        // print out what you need to
        cout << i + 1 << ". " << printvec.at(i).title << endl;
        cout << "Author: " << printvec.at(i).author << endl;
        cout << "Word Count: " << printvec.at(i).wordCount << endl;
        cout << endl;
    }
}

// adds 5 above and below to vector
void HashTable::traverse(vector<Book>& endvec, int goalkey)
{
    int lowercount = 0;
    int highercount = 0;
    int i = 1;
    int j = 1;

    // get the 5 books lower than the current
    while (lowercount < 5)
    {
        //if there is a vec at current table spot
        if (table.find(goalkey - i) != table.end())
        {
            vector<Book> bookvec = table.at(goalkey - i);
            for (int x = 0; x < bookvec.size(); x++)
            {
                endvec.push_back(bookvec.at(x));
                lowercount++;
            }
        }
        i++;
        if (goalkey - i < 0) { break; }
    }

    // get the 5 books higher than the current
    while (highercount < 5)
    {
        if (table.find(goalkey + j) != table.end())
        {
            vector<Book> bookvec = table.at(goalkey + j);
            for (int x = 0; x < bookvec.size(); x++)
            {
                endvec.push_back(bookvec.at(x));
                highercount++;
            }
        }
        j++;
        if (goalkey + j > 999) { break; }
    }
}