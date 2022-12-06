#pragma once
#include <iostream>
using namespace std;
class Book
{
public:
	string genre;
	string title;
	string author;
	//double difficulty;
	int wordCount;

	Book()
	{
		genre = "";
		title = "";
		author = "";
		wordCount = 0;
	}
	Book(string genre_, string title_, string author_, int wordCount_) 
	: genre(genre_), title(title_), author(author_), wordCount(wordCount_) {}
};

