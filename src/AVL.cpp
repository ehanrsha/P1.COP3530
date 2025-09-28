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
        if (heightDifferenceChild >= 0) { //pos check
            currentNode = leftLeft(currentNode);
        }
        else {
            currentNode = leftRight(currentNode);
        }
    }
    //right right or right-left
    if (heightDifference <= -2) {
        int heightDifferenceChild = calculateHeight(currentNode->right->right) - calculateHeight(currentNode->right->left);
        if (heightDifferenceChild >= 0) {
            currentNode = rightRight(currentNode);
        }
        else {
            currentNode = rightLeft(currentNode);
        }
    }

    return currentNode;
}

Node* AVL::searchHelper(Node *currentNode, int id) {

    if (currentNode == nullptr) {
        cout << "unsuccessful" << endl;
        return currentNode;
    }
    else if (currentNode->UFID == id) {
        cout << currentNode->name << endl;
        return currentNode;
    }
    else if (id > currentNode->UFID) {
        return searchHelper(currentNode->right, id);
    }
    else {
        return searchHelper(currentNode->left, id);
    }
}

Node * AVL::inorderSuccessorFinder(Node *node, Node* &copied) {
    if (node == nullptr) {
        copied = nullptr;
        return nullptr;
    }

    //left node found in right subtree
    if (node->left == nullptr) { //inorder successor
        copied = node;
        Node* children = node->right;
        return children;
    }

    node->left = inorderSuccessorFinder(node->left, copied);

    node->height = calculateNewHeight(node);
    return node;

}

//preorder traversal - NLR
Node* AVL::searchHelper(Node *currentNode, string name, vector<int>& studentID) {

    if (currentNode == nullptr) {
        return currentNode;
    }

    if (currentNode->name == name) {
        studentID.push_back(currentNode->UFID);
    }
    searchHelper(currentNode->left, name, studentID);
    searchHelper(currentNode->right, name, studentID);

    return currentNode;
}

Node * AVL::preOrderTraversalHelper(Node *currentNode, vector<string> &studentNames) {
    if (currentNode == nullptr) {
        return currentNode;
    }
    studentNames.push_back(currentNode->name);
    preOrderTraversalHelper(currentNode->left, studentNames);
    preOrderTraversalHelper(currentNode->right, studentNames);

    return currentNode;
}

Node * AVL::inOrderTraversalHelper(Node *currentNode, vector<string> &studentNames) {
    if (currentNode == nullptr) {
        return currentNode;
    }
    inOrderTraversalHelper(currentNode->left, studentNames);
    studentNames.push_back(currentNode->name);
    inOrderTraversalHelper(currentNode->right, studentNames);

    return currentNode;
}

Node * AVL::postOrderTraversalHelper(Node *currentNode, vector<string> &studentNames) {
    if (currentNode == nullptr) {
        return currentNode;
    }
    postOrderTraversalHelper(currentNode->left, studentNames);
    postOrderTraversalHelper(currentNode->right, studentNames);
    studentNames.push_back(currentNode->name);

    return currentNode;
}

Node * AVL::removeHelper(Node *currentNode, int id, bool& found) {
    if (currentNode == nullptr) {
        return nullptr;
    }

    //delete process - inorder successor for two children (right subtrees left most child)
    if (id > currentNode->UFID) {
        currentNode->right = removeHelper(currentNode->right, id, found);
    }
    else if (id < currentNode->UFID) {
        currentNode->left = removeHelper(currentNode->left, id, found);
    }
    else {
        found = true;
        //leaf case
        if (currentNode->left == nullptr && currentNode->right == nullptr) {
            delete currentNode;
            return nullptr;
        }
        else if (currentNode->left == nullptr || currentNode->right == nullptr) {
            if (currentNode->left == nullptr) {
                Node* temp = currentNode->right;
                delete currentNode;
                return temp;
            }
            else {
                Node* temp = currentNode->left;
                delete currentNode;
                return temp;
            }
        }
        //inorder successor replacement - two children
        else {
            Node* toBeCopiedFrom = nullptr;
            currentNode->right = inorderSuccessorFinder(currentNode->right, toBeCopiedFrom);
            currentNode->UFID = toBeCopiedFrom->UFID;
            currentNode->name = toBeCopiedFrom->name;
            delete toBeCopiedFrom;
        }

    }

    currentNode->height = calculateNewHeight(currentNode);
    return currentNode;
}

//avoid null cases
int AVL::calculateHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

//citations: max gotten from https://cplusplus.com/reference/algorithm/max/
int AVL::calculateNewHeight(Node *node) {
    return 1 + max(calculateHeight(node->left), calculateHeight(node->right));
}

void AVL::endHelper(Node *currentNode) {
    if (!currentNode) {
        return;
    }
    endHelper(currentNode->left);
    endHelper(currentNode->right);
    delete currentNode;
}

void AVL::insert(std::string name, int UFID) {
    if (root == nullptr) {
        Node* newNode = new Node(name, UFID);
        root = newNode;
        return;
    }
    root = insertHelper(root, name, UFID); //equal to root, because of shifting
}

void AVL::remove(int UFID) {
    bool found = false;
    root = removeHelper(root, UFID, found);

    if (found) {
        cout << "successful" << endl;
    }
    else {
        cout << "unsuccessful" << endl;
    }
}


//traversals
void AVL::preOrder() {
    vector<string> studentNames;
    preOrderTraversalHelper(root, studentNames);

    for (int x = 0; x < studentNames.size(); x++) {
        if (x == studentNames.size() - 1) {
            cout << studentNames[x] << endl;
        }
        else {
            cout << studentNames[x] << ", ";
        }
    }
}

void AVL::inOrder() {
    vector<string> studentNames;
    inOrderTraversalHelper(root, studentNames);

    for (int x = 0; x < studentNames.size(); x++) {
        if (x == studentNames.size() - 1) {
            cout << studentNames[x] << endl;
        }
        else {
            cout << studentNames[x] << ", ";
        }
    }
}

void AVL::postOrder() {

    vector<string> studentNames;
    postOrderTraversalHelper(root, studentNames);

    for (int x = 0; x < studentNames.size(); x++) {
        if (x == studentNames.size() - 1) {
            cout << studentNames[x] << endl;
        }
        else {
            cout << studentNames[x] << ", ";
        }
    }
}



void AVL::printLevelCount() {
    if (root == nullptr) {
        std::cout << 0 << std::endl;
    }

    cout << calculateHeight(root) << endl;

}

Node * AVL::inOrderLister(Node *currentNode, vector<Node *> &listOfNodes) {
    if (currentNode == nullptr) {
        return currentNode;
    }
    inOrderLister(currentNode->left, listOfNodes);
    listOfNodes.push_back(currentNode);
    inOrderLister(currentNode->right, listOfNodes);

    return currentNode;
}

void AVL::removeInorder(int n) {
    vector<Node *> listOfNodes;
    root = inOrderLister(root, listOfNodes); //return a list of all the nodes using inorder traversal

    if ((n < 0) || (n >= listOfNodes.size())) {
        cout << "unsuccessful" << endl;
        return;
    }



    bool found = false;
    root = removeHelper(root, listOfNodes[n]->UFID, found);

    if (!found) {
        cout << "unsuccessful" << endl;
        return;
    }
    cout << "successful" << endl;

}


//search methods
void AVL::search(string name1) {
    vector<int> studentID;
    searchHelper(root, name1, studentID);
    if (studentID.size() > 0) {
        for (int i = 0; i < studentID.size(); i++) {
            cout << studentID[i] << endl;
        }
    }
    else {
        cout << "unsuccessful" << endl;
    }
}

void AVL::search(int id) {
    searchHelper(root, id);
}


//credits lecture slide 12 (4)
Node* AVL::rightRight(Node* node) {
    Node* grandChild = node->right->left;
    Node* parent = node->right;
    parent->left = node;
    node->right = grandChild;

    node->height  = 1 + max(calculateHeight(node->left),  calculateHeight(node->right));
    parent->height = 1 + max(calculateHeight(parent->left), calculateHeight(parent->right));

    return parent;
}

Node* AVL::leftLeft(Node *node) {
    Node* grandchild = node->left->right;
    Node* parent = node->left;
    parent->right = node;
    node->left = grandchild;

    node->height  = 1 + max(calculateHeight(node->left),  calculateHeight(node->right));
    parent->height = 1 + max(calculateHeight(parent->left), calculateHeight(parent->right));

    return parent;
}

Node* AVL::rightLeft(Node *node) {
    node->right = leftLeft(node->right);
    return rightRight(node);

}

Node* AVL::leftRight(Node *node) {
    node -> left = rightRight(node->left);
    return leftLeft(node);
}

AVL::~AVL() {
    endHelper(root);
    root = nullptr;
}


