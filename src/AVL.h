//
// Created by ers76 on 9/17/2025.
//

#ifndef AVL_H
#define AVL_H

#include<iostream>
#include<vector>

using namespace std;

struct Node {

    int UFID;
    string name;
    int height;
    Node* left;
    Node* right;

    Node(string name, int UFID) {
        this->name = name;
        this->UFID = UFID;
        left = nullptr;
        right = nullptr;
        height = 1;
    }
};


class AVL {
private:
    Node* root = nullptr;
    Node* insertHelper(Node* currentNode, string name, int id); //want to keep private so cannot access on main.
    static int calculateHeight(Node* node);


public:
    //Node* returnRoot();
    void insert(std::string name, int UFID);
    //bool erase(int);
    //std::vector<std::pair<std::string, int>> inorder();
    //std::vector<std::pair<std::string, int>> preorder();
    //void remove(int ID);


    //rotations:
    void rightRight(Node* node);
    void leftLeft(Node* node);
    void rightLeft(Node* node);
    void leftRight(Node* node);

    //destructor
    ~AVL(); //use a post order traversal
};



#endif //AVL_H
