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

    //helper methods
    Node* insertHelper(Node* currentNode, string name, int id); //want to keep private so cannot access on main.
    Node* searchHelper(Node* currentNode, int id);
    Node* searchHelper(Node* currentNode, string name, vector<int>& studentID);
    Node* preOrderTraversalHelper(Node* curerntNode, vector<string>& studentNames);
    Node* inOrderTraversalHelper(Node* curerntNode, vector<string>& studentNames);
    Node* postOrderTraversalHelper(Node* curerntNode, vector<string>& studentNames);
    Node* removeHelper(Node* currentNode, int id, bool& found);
    Node* inorderSuccessorFinder(Node* node, Node* &copied);
    Node* inOrderLister(Node* currentNode, vector<Node*>& listOfNodes);
    static int calculateHeight(Node* node);
    static int calculateNewHeight(Node* node);
    void endHelper(Node* currentNode);




public:
    //Node* returnRoot();
    void insert(string name, int UFID);
    void remove(int UFID);
    void search(string name1);
    void search(int id);
    void preOrder();
    void inOrder();
    void postOrder();
    void printLevelCount();
    void removeInorder(int n);



    //rotations:
    Node* rightRight(Node* node);
    Node* leftLeft(Node* node);
    Node* rightLeft(Node* node);
    Node* leftRight(Node* node);

    //destructor
    ~AVL(); //use a post order traversal
};



#endif //AVL_H
