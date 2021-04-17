//
// Created by Veronica  Soden  on 4/17/21.
//
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "song.h"
#include "Node.h"

#ifndef PROJ3_BST_H
#define PROJ3_BST_H


class BST {
public:
    Node* root = nullptr;
    int size = 0;

    bool insert(song*);
    bool insertRecusrion(Node*, song*);
    bool search(song*);
    Node* searchRecursion(Node*, song*);
    void traverseInOrder(Node*, queue<song>);
    int height(Node*);
};


#endif //PROJ3_BST_H
