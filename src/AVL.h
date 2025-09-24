//
// Created by ers76 on 9/17/2025.
//

#ifndef AVL_H
#define AVL_H

#include<iostream>
#include<vector>


class AVL {
public:
    std::vector<std::pair<std::string, int>> data; //store all the UF student names, and ID's here.
    bool insert(std::string name, int UFID);
    bool erase(int);
    std::vector<std::pair<std::string, int>> inorder();
    std::vector<std::pair<std::string, int>> preorder();
    void remove(int ID);
};



#endif //AVL_H
