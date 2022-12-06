#include <iomanip>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>

//#include "Book.h"
#include "tree.h"
#include "HashTable.h"
using namespace std;

int main()
{
    string desired_genre = "PR";

    int desired_wordCount = 50000;

    Book desired_book(desired_genre, "[desired]", "[desired]", desired_wordCount);

    int data_structure;
    cout << "Enter number of which data structure to use: " << endl;
    cout << "1. Red Black Tree" << endl;
    cout << "2. Hash Table" << endl;
    cin >> data_structure;


    // get start time
    clock_t time_req;
    time_req = clock();

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
        tree RBTree;
        for (Book book : library)
        {
            RBTree.insert(book);
            //cout << book.wordCount << endl;
        }
        RBTree.printTop5(desired_wordCount);
    }

    if (data_structure == 2)
    {
        HashTable h;
        h.getDesiredBook(desired_book);
        for (int i = 0; i < library.size(); i++)
        {
            h.insert(library.at(i));
        }
        h.getTop5();
        //cout << "hash table stuff" << endl;
    }

    if (data_structure == 3)
    {
        tree RBTree;
        HashTable h;
        h.getDesiredBook(desired_book);
        for (Book book : library)
        {
            RBTree.insert(book);
            h.insert(book);
            //cout << book.wordCount << endl;
        }
        cout << "RBT: " << endl;
        RBTree.printTop5(desired_wordCount);
        cout << endl << endl;
        cout << "HashTable: " << endl;
        h.getTop5();
    }

    time_req = clock() - time_req;
    cout << endl;
    cout << "This output took " << (float)time_req / CLOCKS_PER_SEC << " seconds." << endl;

}

