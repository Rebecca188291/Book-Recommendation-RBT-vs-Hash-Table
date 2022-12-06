// RBT.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>

#include "Book.h"
#include "tree.h"
using namespace std;

int main()
{
    tree RBTree;
    /*Book book;
    book.author = "yo";
    book.genre = "classic";
    book.name = "hotwheels";
    book.wordCount = 420;

    Book book2;
    book2.author = "yo";
    book2.genre = "classic";
    book2.name = "mario";
    book2.wordCount = 100;

    Book book3;
    book3.author = "yo";
    book3.genre = "classic";
    book3.name = "penguin";
    book3.wordCount = 960;

    Book book4;
    book4.author = "yo";
    book4.genre = "classic";
    book4.name = "spongebob";
    book4.wordCount = 1960;

    RBTree.insert(book);
    cout << book.name << " red? " << RBTree.root->red << endl;

    RBTree.insert(book2);
    cout << book2.name << " red?" << RBTree.root->left->red << endl;

    RBTree.insert(book3);
    cout << book3.name << " red?" << RBTree.root->right->red << endl;
    
    RBTree.insert(book4);
    cout << book4.name << " red?" << RBTree.root->right->right->red << endl;*/



    string desired_genre = "HQ";

    int desired_wordCount = 50000;

    // Make a vector of book objects
    vector<Book> library;

    // input from CSV
    ifstream inFile("C:\\Users\\Rebecca\\source\\repos\\RBT\\RBT\\classics.csv.csv");
    string line;
    string token;
    getline(inFile, line);
    istringstream stream(line);

    while (getline(inFile, line))
    {
        istringstream stream(line);

        getline(stream, token, '_');
        if (token.compare(desired_genre) != 0)
        {
            continue;
        }

        Book book("", "", "", 0);

        book.genre = token;

        for (int i = 0; i < 2; i++)
        {
            getline(stream, token, '_');
        }
        book.title = token;

        for (int i = 0; i < 7; i++)
        {
            getline(stream, token, '_');
        }
        book.author = token;

        for (int i = 0; i < 25; i++)
        {
            getline(stream, token, '_');
        }
        book.wordCount = stoi(token);

        library.push_back(book);
    }


    //for (Book book : library)
    //{
    //    RBTree.insert(book);
    //    cout << book.wordCount << endl;
    //}

    RBTree.insert(library[0]);
    RBTree.insert(library[1]);
    RBTree.insert(library[2]);
    RBTree.insert(library[3]);


    RBTree.printInorder();
    RBTree.remove(library[0].wordCount);
    RBTree.printInorder();
    //cout << "root: " << RBTree.root->bookNode.wordCount << endl;




}

