#include "tree.h"

void tree::insert(Book curr)
{
    root = insertHelper(root, curr);
    //check if root is black
    if (root->red == true) 
    {
        root->red = false;
    }
}

tree::TreeNode* tree::insertHelper(tree::TreeNode* currNode, Book newBook)
{
    if (currNode == nullptr)
    {
        return new TreeNode(newBook);
    }
    else if (newBook.wordCount < currNode->bookNode.wordCount)
    {
        currNode->left = insertHelper(currNode->left, newBook);
        currNode->left->parent = currNode;
        if (currNode->red && currNode->parent->red)
        {
            //check uncle
            //if uncle is red, flip the colors of everything. recolor root
            TreeNode* uncle = findUncle(currNode);
            if (currNode == nullptr || currNode->red == false)
            {
                //rotate currNode and children
                //rember to set currNode to new parent!!!!! change the parents!!!
                currNode = rotateLeftChild(currNode, currNode->left);
            }
            else
            {
                //flipColors(root, currNode->left);
            }
        }

    }
    else
    {
        currNode->right = insertHelper(currNode->right, newBook);
        currNode->right->parent = currNode;

        if (currNode->red && currNode->parent->red)
        {
            TreeNode* uncle = findUncle(currNode);
            if (currNode == nullptr || currNode->red == false)
            {
                //rotate currNode and children
                //rember to set currNode to new parent!!!!! change the parents!!!
                currNode = rotateRightChild(currNode, currNode->right);
            }
            else
            {
                //flipColors(root, currNode->right);
            }
        }

        /*rules to check:
          1. is the root black (checked in main insert)
          2. if the parent is black, done
          3. if the prent is red, look at the uncle:
              a. if uncle is red, flip the colors of everything, recolor the root
              b. if the uncle is black or null, rotate
        */
    }
    return currNode;
}

tree::TreeNode* tree::findUncle(tree::TreeNode* currNode)
{
    //Uncle is just grandparents other child
    if (currNode->parent == nullptr)
    {
        return nullptr;
    }
    else if (currNode->parent->parent == nullptr)
    {
        return nullptr;
    }
    else
    {
        TreeNode* grandparent = currNode->parent->parent;
        if (grandparent->left == currNode->parent)
        {
            return grandparent->right;
        }
        else
        {
            return grandparent->left;
        }
    }
}

void tree::flipColors(TreeNode* currNode, TreeNode* exception)
{
    TreeNode* curr = currNode;
    //if curr is null or it is a leaf, we do not flip of newly added book
    if (curr == nullptr || (curr == exception))
    {
        return;
    }

    cout << curr->bookNode.title << endl;
    bool red = curr->red;
    string color = "";
    if (red)
    {
        color = "red";
    }
    else
    {
        color = "black";
    }
    cout << curr->bookNode.title << " color is " << color << endl;

    curr->red = !(curr->red);
    flipColors(curr->left, exception);
    flipColors(curr->right, exception);
    
    cout << curr->bookNode.title << " color is " << color << endl;
    return;

}

tree::TreeNode* tree::rotateRightChild(TreeNode* parent, TreeNode* child)
{
    TreeNode* greatGrandpa = parent->parent->parent;
    TreeNode* grandpa = parent->parent;
    if (grandpa->bookNode.wordCount < greatGrandpa->bookNode.wordCount)
    {
        grandpa->right = nullptr;
        parent->left = grandpa;
        grandpa->parent = parent;
        parent->parent = greatGrandpa;
    }
    return parent;
}

tree::TreeNode* tree::rotateLeftChild(TreeNode* parent, TreeNode* child)
{
    TreeNode* greatGrandpa = parent->parent->parent;
    TreeNode* grandpa = parent->parent;
    if (grandpa->bookNode.wordCount < greatGrandpa->bookNode.wordCount)
    {
        grandpa->left = nullptr;
        parent->right = grandpa;
        grandpa->parent = parent;
        parent->parent = greatGrandpa;
    }
    return parent;
}

void tree::printInorder()
{
    vector<int> titles;
    if (root == nullptr)
    {
        cout << "";
        return;
    }
    printInorderHelper(root, titles);
    for (int i = 0; i < titles.size(); i++)
    {
        if (i == titles.size() - 1)
        {
            cout << titles[i] << endl;
        }
        else
        {
            cout << titles[i] << ", ";
        }
    }
}

void tree::printInorderHelper(TreeNode* currNode, vector<int>& titles)
{
    if (currNode == nullptr)
    {
        cout << "";
    }
    else
    {
        printInorderHelper(currNode->left, titles);
        titles.push_back(currNode->bookNode.wordCount);
        printInorderHelper(currNode->right, titles);
    }
}

bool tree::remove(int wordcount)
{
    // Case for when the node to remove is the root of tree
        // (traversal() does not work for root nodes)
    if (root->bookNode.wordCount == wordcount)
    {
        // If there are no child nodes from the node to remove
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr;
            //cout << "successful" << endl;
            return true;
        }
        // If there is only one, left child node from the node to remove
        else if (root->left != nullptr && root->right == nullptr)
        {
            TreeNode* temp = root;
            root = root->left;
            root->parent = nullptr;
            delete temp;
            //cout << "successful" << endl;
            return true;
        }
        // If there is only one, right child node from the node to remove
        else if (root->right != nullptr && root->left == nullptr)
        {
            TreeNode* temp = root;
            root = root->right;
            root->parent = nullptr;
            delete temp;
           // cout << "successful" << endl;
            return true;
        }
        // If there are two nodes from the node to remove
        else
        {
            // This is the parent of the node that will replace the removed node
            TreeNode* successorParent = root->right;

            // Case of no left node from node directly to the right of Node to be removed
            if (successorParent->left == nullptr)
            {
                successorParent->left = root->left;
                root->left->parent = successorParent;
                delete root;
                root = successorParent;
                root->parent = nullptr;
                //cout << "successful" << endl;
                return true;
            }

            // Case of there are node(s) to the left of the node directly right of Node to be removed
            while (successorParent->left->left != nullptr)
            {
                successorParent = successorParent->left;
            }
            if (successorParent->left->right != nullptr)
            {
                TreeNode* temp = new TreeNode(successorParent->left->right->bookNode);
                temp->left = successorParent->left->right->left;
                temp->right = successorParent->left->right->right;
                delete successorParent->left->right;
                successorParent->left->right = root->right;
                root->right->parent = successorParent->left;
                successorParent->left->left = root->left;
                delete root;
                root = successorParent->left;
                successorParent->left = temp;
                root->parent = nullptr;

            }
            else
            {
                successorParent->left->right = root->right;
                successorParent->left->left = root->left;
                delete root;
                root = successorParent->left;
                successorParent->left = nullptr;

            }
            //cout << "successful" << endl;
            return true;
        }
    }
    TreeNode* parent = traversal(root, wordcount);

    if (parent == nullptr)
    {
        return false;
    }

    TreeNode* removeNode = nullptr;

    // If node to remove is to the left of the identified parent
    if (parent->left != nullptr && parent->left->bookNode.wordCount == wordcount)
    {
        removeNode = parent->left;
        // If there are not child nodes from the node to remove
        if (removeNode->left == nullptr && removeNode->right == nullptr)
        {
            parent->left = nullptr;
            delete removeNode;
            return true;
        }
        // If there is only one, left child node from the node to remove
        else if (removeNode->left != nullptr && removeNode->right == nullptr)
        {
            parent->left = removeNode->left;
            removeNode->left->parent = parent;
            delete removeNode;
            return true;
        }
        // If there is only one, right child node from the node to remove
        else if (removeNode->right != nullptr && removeNode->left == nullptr)
        {
            parent->left = removeNode->right;
            parent->left->parent = parent;
            delete removeNode;
            return true;
        }
        // If there are two nodes from the node to remove
        else
        {
            // This is the parent of the node that will replace the removed node
            TreeNode* successorParent = removeNode->right;

            // Case of no left node from node directly to the right of Node to be removed
            if (successorParent->left == nullptr)
            {
                successorParent->left = removeNode->left;
                removeNode->left->parent = successorParent;
                parent->left = successorParent;
                successorParent->parent = parent;
                delete removeNode;
                return true;
            }

            // Case of there are node(s) to the left of the node directly right of Node to be removed

            while (successorParent->left->left != nullptr)
            {
                successorParent = successorParent->left;
            }

            parent->left = successorParent->left;
            successorParent->left->parent = parent;
            successorParent->left->left = removeNode->left;
            removeNode->left->parent = successorParent->left;
            if (successorParent->left->right != nullptr)
            {
                Book book;
                book.wordCount = successorParent->left->right->bookNode.wordCount;
                book.title = successorParent->left->right->bookNode.title;
                book.author = successorParent->left->right->bookNode.author;
                book.genre = successorParent->left->right->bookNode.genre;
                TreeNode* temp = new TreeNode(book);

                temp->left = successorParent->left->right->left;
                temp->right = successorParent->left->right->right;
                delete successorParent->left->right;
                successorParent->left->right = removeNode->right;
                successorParent->left = temp;
            }
            else
            {
                successorParent->left->right = removeNode->right;
                successorParent->left = nullptr;
            }
            delete removeNode;
            return true;
        }

    }
    // If node to remove is to the right of the identified parent
    else
    {
        removeNode = parent->right;
        if (removeNode->left == nullptr && removeNode->right == nullptr)
        {
            parent->right = nullptr;
            delete removeNode;
            return true;
        }
        else if (removeNode->left != nullptr && removeNode->right == nullptr)
        {
            parent->right = removeNode->left;
            delete removeNode;
            return true;
        }
        else if (removeNode->right != nullptr && removeNode->left == nullptr)
        {
            parent->right = removeNode->right;
            delete removeNode;
            return true;
        }

        // If there are two nodes from the node to remove
        else
        {
            // This is the parent of the node that will replace the removed node
            TreeNode* successorParent = removeNode->right;

            // Case of no left node from node directly to the right of Node to be removed
            if (successorParent->left == nullptr)
            {
                successorParent->left = removeNode->left;
                parent->right = successorParent;
                delete removeNode;
                return true;
            }

            // Case of there are node(s) to the left of the node directly right of Node to be removed
            while (successorParent->left->left != nullptr)
            {
                successorParent = successorParent->left;
            }

            // Here accounting for any height decrementing that may come from moving the node
            parent->right = successorParent->left;

            successorParent->left->left = removeNode->left;
            if (successorParent->left->right != nullptr)
            {
                Book book;
                book.wordCount = successorParent->left->right->bookNode.wordCount;
                book.title = successorParent->left->right->bookNode.title;
                book.author = successorParent->left->right->bookNode.author;
                book.genre = successorParent->left->right->bookNode.genre;
                TreeNode* temp = new TreeNode(book);

                temp->left = successorParent->left->right->left;
                temp->right = successorParent->left->right->right;
                delete successorParent->left->right;
                successorParent->left->right = removeNode->right;
                successorParent->left = temp;
            }
            else
            {
                successorParent->left->right = removeNode->right;
                successorParent->left = nullptr;
            }
            delete removeNode;
            return true;
        }
    }
}

tree::TreeNode* tree::traversal(TreeNode* root, int wordcount)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    if (root->bookNode.wordCount == wordcount)
    {
        return nullptr;
    }
    if (root->bookNode.wordCount > wordcount)
    {
        if (root->left == nullptr)
        {
            return nullptr;
        }
        if (root->left->bookNode.wordCount == wordcount)
        {
            return root;
        }
        return traversal(root->left, wordcount);
    }
    else
    {
        if (root->right == nullptr)
        {
            return nullptr;
        }
        if (root->right->bookNode.wordCount == wordcount)
        {
            return root;
        }
        return traversal(root->right, wordcount);
    }
}

tree::TreeNode* tree::tracker(TreeNode* root, int wordcount, vector<Book>& library)
{
    if (root == nullptr)
    {
        return nullptr;
    }
    library.push_back(root->bookNode);
    if (root->bookNode.wordCount == wordcount)
    {
        return nullptr;
    }
    if (root->bookNode.wordCount > wordcount)
    {
        if (root->left == nullptr)
        {
            return nullptr;
        }
        //if (root->left->bookNode.wordCount == wordcount)
        //{
        //    return root;
        //}
        return tracker(root->left, wordcount, library);
    }
    else
    {
        if (root->right == nullptr)
        {
            return nullptr;
        }
        //if (root->right->bookNode.wordCount == wordcount)
        //{
        //    return root;
        //}
        return tracker(root->right, wordcount, library);
    }
}

vector<Book> tree::findTop5(int targetWordCount)
{
    vector<Book> library;
    vector<Book> nodePath;
    //temp doesn't do anything, tracker just returns tree node bc it's recursive, we only care about nodePath
    TreeNode* temp = tracker(root, targetWordCount, nodePath);
    while (library.size() < 5)
    {
        int minDiff = abs(nodePath[0].wordCount - targetWordCount);
        Book minBook = nodePath[0];
        for (int i = 1; i < nodePath.size(); i++)
        {
            int currDiff = abs(nodePath[i].wordCount - targetWordCount);
            if (currDiff < minDiff)
            {
                minDiff = currDiff;
                minBook = nodePath[i];
            }
        }
        library.push_back(minBook);
        bool removed = remove(minBook.wordCount);
        nodePath.clear();
        TreeNode* temp = tracker(root, targetWordCount, nodePath);
    }
    return library;
}

void tree::printTop5(int targetWordCount)
{
    vector<Book> library;
    library = findTop5(targetWordCount);
    cout << "Your top 5 recommended books are: " << endl;
    cout << endl;
    for (int i = 0; i < library.size(); i++)
    {
        cout << i + 1 << ". " << library[i].title << endl;
        cout << "Author: " << library[i].author << endl;
        cout << "Word count: " << library[i].wordCount << endl;
        cout << endl;
    }
}