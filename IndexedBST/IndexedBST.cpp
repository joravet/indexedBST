// Jackson Oravetz; Professor Ahmed, Kishwar; Code for an indexed binary search tree
//

#include <iostream>
#include "IndexedBST.h"
using namespace std;

void testSearch(IndexedBST* tree, double key);
void testAt(IndexedBST* tree, int index);

int main()
{
    // Test insert
    double numbers[] = { 9, 4, 11, 2, 6, 15, 1, 3, 5, 8 };
    IndexedBST* tree = new IndexedBST();
    for (double number : numbers) {     //for each loop for entire array
        tree->insert(new Node(number));
    }

    double key;
    cout << "Enter key to search for: ";
    cin >> key;
    testSearch(tree, key);

    int index;
    cout << "Enter index: ";
    cin >> index;
    testAt(tree, index);

    // Test remove
    double keyToRemove;
    cout << endl << "Enter key to remove: ";
    cin >> keyToRemove;
    bool keyRemoved = tree->remove(keyToRemove);
    cout << "Removed key " << keyToRemove << "?: " << keyRemoved << endl;
    testSearch(tree, key);
    testAt(tree, index);

    return 0;
}

//calls search function and prints results of search
void testSearch(IndexedBST* tree, double key) {
    Node* foundNode = tree->search(key);
    if (foundNode != nullptr) {
        cout << "Found node with key = " << foundNode->key << endl;
        cout << "Left size = " << foundNode->leftSize << endl;
        if (foundNode->parent != nullptr) {
            cout << "Parent node key = " << foundNode->parent->key << endl;
            cout << "Left size = " << foundNode->parent->leftSize << endl;
        }
        if (foundNode->left != nullptr) {
            cout << "Left child node key = " << foundNode->left->key << endl;
            cout << "Left size = " << foundNode->left->leftSize << endl;
        }
        if (foundNode->right != nullptr) {
            cout << "Right child node key = " << foundNode->right->key << endl;
            cout << "Left size = " << foundNode->right->leftSize << endl;
        }
    }
    else
        cout << "Key " << key << " not found." << endl;
}

//calls at function and prints results
void testAt(IndexedBST* tree, int index) {
    Node* foundNode = tree->at(index);
    if (foundNode != nullptr) {
        cout << "Found node with key = " << foundNode->key << endl;
        cout << "Left size = " << foundNode->leftSize << endl;
    }
    else
        cout << "Index " << index << " not found." << endl;
}

//search for requested key
Node* IndexedBST::search(double desiredKey) {
    Node* cur = root;
    while (cur != nullptr) {
        // Return the node if the key matches
        if (cur->key == desiredKey) {
            return cur;
        }

        // Navigate to the left if the search key is 
        // less than the node's key.
        else if (desiredKey < cur->key) {
            cur = cur->left;
        }

        // Navigate to the right if the search key is 
        // greater than the node's key.
        else {
            cur = cur->right;
        }
    }

    // The key was not found in the tree.
    return nullptr;
}

//return node at requested index
Node* IndexedBST::at(int index) {
    Node* cur = root;
    while (cur != nullptr) {
        if (index == cur->leftSize)
            return cur;     // Found
        else if (index < cur->leftSize)
            cur = cur->left;    // index is in left subtree
        else {
            // index is in right subtree
            index = index - cur->leftSize - 1;
            cur = cur->right;
        }
    }

    return nullptr;
}

void IndexedBST::insert(Node* node) //method to insert in tree
{
    if (root == nullptr)        //if the tree is empty, make new node the root
    {
        root = node;
        root->parent = nullptr; //roots parent is null
        node->leftSize = 0;     //set the first nodes left size to 0
    }
       
    else         //if not first node
    {
        Node* currentNode = root;   
        while (currentNode != nullptr)  //while pointer isnt null
        {
            if (node->key < currentNode->key)   //if new key is less than key of node we are at
            {
                currentNode->leftSize++;        //increment left size of node because an addition is being made to its left
                if (currentNode->left == nullptr)   //if current nodes left branch is null
                {
                    currentNode->left = node;   //place new node here
                    node->parent = currentNode; //make current node new nodes parent
                    currentNode = nullptr;      //break while loop
                }
                else      //move to left branch if it is not null
                    currentNode = currentNode->left;
            }
            else    //new node is larger than current node
            {
                if (currentNode->right == nullptr)  //if right branch is null
                {
                    currentNode->right = node;  //place new node here
                    node->parent = currentNode; //make nodes parent currentNode
                    currentNode = nullptr;      //break while loop
                }
                else      //move to right branch if not null
                    currentNode = currentNode->right;
            }
        }
    } 
}

bool IndexedBST::remove(double key)
{
    Node* parent = nullptr;
    Node* currentNode = root;
    while (currentNode != nullptr)
    {
        if (currentNode->key == key)    //Check if currentNode has an equal key
        {
            if (currentNode->left == nullptr && currentNode->right == nullptr)  //remove leaf
            {
                if (parent == nullptr)              //node is root
                    root = nullptr;
                else if (parent->left == currentNode)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
                return true;                        //node found and removed  
            }
            else if (currentNode->right == nullptr) //remove nod with only one left child
            {
                if (parent == nullptr)              //node is root
                    root = currentNode->left;
                else if (parent->left == currentNode)
                    parent->left = currentNode->left;
                else
                    parent->right = currentNode->left;
                return true;                        //node found and removed
            }
            else if (currentNode->left == nullptr)  //remove node with only right child
            {   
                if (parent == nullptr)              //node is root
                    root = currentNode->right;
                else if (parent->left == currentNode)
                    parent->left = currentNode->right;
                else
                    parent->right = currentNode->right;
                return true;                        //node found and removed
            }
            else  //remove node with two children
            {
                Node* successor = currentNode->right;   //find successor (leftmost child of right subtree
                while (successor->left != nullptr)
                {
                    successor = successor->left;
                }

                //copy successor's key to currentNode
                currentNode->key = successor->key;
                parent = currentNode;

                //reassign currentNode and key so that loop continues with new

                currentNode = currentNode->right;
                key = successor->key;
            }
            return true;    //node found and removed
        }
        else if (currentNode->key < key)    //search right
        {
            parent = currentNode;
            currentNode = currentNode->right;
        }
        else                                //search left
        {
            currentNode->leftSize--;
            parent = currentNode;
            currentNode = currentNode->left;
        }
    }

    if (searchRemove(key) == false)
        return false;   //node not found
}

//method to correct leftSize changes if remove method was called on a key that wasn't present
bool IndexedBST::searchRemove(double desiredKey)
{
    Node* cur = root;
    while (cur != nullptr) {
        // Return the node if the key matches
        if (cur->key == desiredKey) {
            return true;
        }

        // Navigate to the left if the search key is 
        // less than the node's key.
        else if (desiredKey < cur->key) {
            cur->leftSize++;                //add back removed left index if key is not found
            cur = cur->left;
        }

        // Navigate to the right if the search key is 
        // greater than the node's key.
        else {
            cur = cur->right;
        }
    }
    return false;
}



