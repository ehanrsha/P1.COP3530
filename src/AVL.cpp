//
// Created by ers76 on 9/17/2025.
//

#include "AVL.h"
#include <iostream>
using namespace std;

//referenced from the lecture slides
Node* AVL::insertHelper(Node* currentNode, string name, int id) {

    if (id == currentNode->UFID) {
        cout << "Unsuccessful" << endl;
        return currentNode;
    }

    //addition state
    if (id > currentNode->UFID) {
        //if null add the node to the right
        if (currentNode->right == nullptr) {
            Node* newNode = new Node(name, id);
            currentNode->right = newNode;
            cout << "Successful" << endl;
            //recalculate the node height
        }
        //keep going down the tree
        else {
            currentNode->right = insertHelper(currentNode->right, name, id);
        }
    }
    else if (id < currentNode->UFID) {
        //if null add the node to the left
        if (currentNode->left == nullptr) {
            Node* newNode = new Node(name, id);
            currentNode->left = newNode;
            cout << "Successful" << endl;
        }
        //keep going down the list
        else {
            currentNode -> left = insertHelper(currentNode->left, name, id);
        }
    }


    //update height of the nodes by going through the list below - max gotten from https://cplusplus.com/reference/algorithm/max/
    currentNode->height = 1 + max(calculateHeight(currentNode->right), calculateHeight(currentNode->left));

    //balance the tree - credits Slide 74 Lecture Slides 4
    int heightDifference = calculateHeight(currentNode->left) - calculateHeight(currentNode->right);

    //left left or left-right
    if (heightDifference >= 2) {
        int heightDifferenceChild = calculateHeight(currentNode->left->left) - calculateHeight(currentNode->left->right);
        if (heightDifferenceChild >= 1) {
            leftLeft(currentNode);
        }
        else {
            leftRight(currentNode);
        }
    }
    //right right or right-left
    if (heightDifference <= -2) {
        int heightDifferenceChild = calculateHeight(currentNode->right->right) - calculateHeight(currentNode->right->left);
        if (heightDifferenceChild >= 1) {
            rightRight(currentNode);
        }
        else {
            rightLeft(currentNode);
        }
    }

    return currentNode;
}

int AVL::calculateHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

void AVL::insert(std::string name, int UFID) {
    if (root == nullptr) {
        Node* newNode = new Node(name, UFID);
        root = newNode;
        return;
    }
    root = insertHelper(root, name, UFID); //equal to root, because of shifting
}
/*
bool AVL::erase(int) {
    return true;
}

std::vector<std::pair<std::string, int>> AVL::inorder(){
    return data;
}

std::vector<std::pair<std::string, int>> AVL::preorder(){
    return data;
}

void AVL::remove(int ID) {
    for (size_t i = 0; i < data.size(); ++i) {
        if (data[i].second == ID) {
            data.erase(data.begin() + i);
        }
    }
}

*/
//credits lecture slide 12 (4)
void AVL::rightRight(Node* node) {
    Node* grandChild = node->right->left;
    Node* parent = node->right;
    parent->left = node;
    node->right = grandChild;

    node->height  = 1 + max(calculateHeight(node->left),  calculateHeight(node->right));
    parent->height = 1 + max(calculateHeight(parent->left), calculateHeight(parent->right));
}

void AVL::leftLeft(Node *node) {
    Node* grandchild = node->left->right;
    Node* parent = node->left;
    parent->left = node;
    node->left = grandchild;

    node->height  = 1 + max(calculateHeight(node->left),  calculateHeight(node->right));
    parent->height = 1 + max(calculateHeight(parent->left), calculateHeight(parent->right));
}

void AVL::rightLeft(Node *node) {
    leftLeft(node->right);


}

void AVL::leftRight(Node *node) {
}

AVL::~AVL() {
}


