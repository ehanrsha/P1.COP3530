//
// Created by ers76 on 9/17/2025.
//

#include "AVL.h"
#include <iostream>
using namespace std;

bool AVL::insert(std::string name, int UFID) {
    data.emplace_back(name, UFID);
    return false;
}

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
