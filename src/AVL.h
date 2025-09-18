//
// Created by ers76 on 9/17/2025.
//

#ifndef AVL_H
#define AVL_H

#include<iostream>
#include<vector>


class AVL {
public:
    bool insert(int);
    bool erase(int);
    std::vector<int> inorder();
};



#endif //AVL_H
