#pragma once
#include <iostream>
#include "Book.h"
#include <vector>
using namespace std;

class tree
{
    //private:
    public:

    struct TreeNode
    {
        Book bookNode;
        bool red;

        TreeNode* right;
        TreeNode* left;
        TreeNode* parent;

        TreeNode(Book& currBook) : bookNode(currBook), right(nullptr), left(nullptr), parent(nullptr), red(true) {}
    };
    TreeNode* root = nullptr;

    TreeNode* insertHelper(TreeNode* currNode, Book newBook);
    TreeNode* findUncle(TreeNode* currNode);
    //TreeNode* rotation(TreeNode* currNode);
    void flipColors(TreeNode* currNode, TreeNode* exception);
    TreeNode* rotateRightChild(TreeNode* parent, TreeNode* child);
    TreeNode* rotateLeftChild(TreeNode* parent, TreeNode* child);
    void printInorder();
    void printInorderHelper(TreeNode* currNode, vector<int>& titles);
    bool remove(int wordCount);
    TreeNode* traversal(TreeNode* root, int wordcount);



    //public:

    void insert(Book curr);
    void printTop5(int targetWordCount);

};

