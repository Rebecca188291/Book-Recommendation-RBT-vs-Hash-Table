#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>

#include "Book.h"
#include "tree.h"
//#include "HashTable.h"
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

    Book desired_book(desired_genre, "[desired]", "[desired]", desired_wordCount);

    int data_structure;
    cout << "Enter number of which data structure to use: " << endl;
    cout << "1. Red Black Tree" << endl;
    cout << "2. Hash Table" << endl;
    cin >> data_structure;

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

    if (data_structure == 1)
    {
        for (Book book : library)
        {
            RBTree.insert(book);
            cout << book.wordCount << endl;
        }
        RBTree.printTop5(desired_wordCount);
    }

    if (data_structure == 2)
    {
        //HashTable h;
        //h.getDesiredBook(desired_book);
        //for (int i = 0; i < library.size(); i++)
        //{
        //    h.insert(library.at(i));
        //}
        //h.getTop5();
        cout << "hash table stuff" << endl;
    }

   /* RBTree.insert(library[0]);
    RBTree.insert(library[1]);
    RBTree.insert(library[2]);
    RBTree.insert(library[3]);*/


    //RBTree.printInorder();
    //RBTree.remove(library[0].wordCount);
    //RBTree.printTop5(58000);
    //RBTree.printInorder();
    //cout << "root: " << RBTree.root->bookNode.wordCount << endl;




}

