#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <queue>

#include "song.h"
#include "Node.h"
#include "BST.h"

using namespace std;

bool BST::insert(song *Song) {
    //check duration is unique if not inc till is
    while(search(Song)) {
        Song->duration++;
    }

    Node* temp = root;
    size++;
    return insertRecusrion(temp, Song);
}

// Return true if insertion successful
bool BST::insertRecusrion(Node* temp, song* Song) {
    //three main insert cases
    //first case check if root has yet to be made, i.e., first insertion
    if(root == nullptr) {
        root = new Node(Song);
        return true;
    }
        //use song duration to sort
    else if(Song->duration > temp->Song->duration) {
        if (temp->right == nullptr) {
            temp->right = new Node(Song);
            return true;
        }
        else {
            //use recursion to insert new node
            insertRecusrion(temp->right, Song);
        }
    }
        //id number is less than node
    else if(Song->duration > temp->Song->duration) {
        if (temp->left == nullptr) {
            temp->left = new Node(Song);
            return true;
        }
        else {
            //use recursion to insert new node
            insertRecusrion(temp->left, Song);
        }
    }
    else {
        return false;
    }
    return true;
}

// method to find height of given node
int BST::height(Node* temp) {
    if (temp == nullptr) {
        return 0;
    }
    return 1 + max(height(temp->left), height(temp->right));
}

// Return comma-separated string of inorder traversal
void BST::traverseInOrder(Node* temp, queue<song> toQ){
    if(temp == nullptr) {
        return;
    }
    traverseInOrder(temp->left, toQ);
    toQ.push(*(temp->Song));
    traverseInOrder(temp->right, toQ);
}

bool BST::search(song* Song) {
    Node* temp = searchRecursion(root, Song);
    if(temp != nullptr) {
        return true;
    }
    else {
        return false;
    }
}

Node* BST::searchRecursion(Node* root, song* Song) {
    if(root == nullptr || root->Song->duration == Song->duration) {
        return root;
    }
    else if(Song->duration < root->Song->duration) {
        return searchRecursion(root->left, Song);
    }
    else {
        return searchRecursion(root->right, Song);
    }
}