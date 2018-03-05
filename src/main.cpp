//
// Created by Myles Adams on 2/27/18.
//

#include <iostream>
#include "AVLTree.hpp"

int main()
{
    std::cout << "CS130A Project 2" << std::endl;

    AVLTree* tree = new AVLTree();

    std::string a, b, c, d, e;
    a = "a";
    b = "b";
    c = "c";
    d = "d";
    e = "e";

    // LL Test
//    tree->insertWord(b);
//    tree->insertWord(a);
//    tree->insertWord(d);
//    tree->insertWord(c);
//    tree->insertWord(e);
//    tree->deleteWord(a);


    // LR Test
//    tree->insertWord(b);
//    tree->insertWord(a);
//    tree->insertWord(d);
//    tree->insertWord(c);
//    tree->deleteWord(a);


    // RR Test
//    tree->insertWord(d);
//    tree->insertWord(b);
//    tree->insertWord(e);
//    tree->insertWord(a);
//    tree->insertWord(c);
//    tree->deleteWord(e);

    // RL Test
//    tree->insertWord(c);
//    tree->insertWord(a);
//    tree->insertWord(d);
//    tree->insertWord(b);
//    tree->deleteWord(d);

    tree->insertWord("18");
    tree->insertWord("23");
    tree->insertWord("27");
    tree->insertWord("13");
    tree->insertWord("16");
    tree->insertWord("10");
    tree->insertWord("33");
    tree->insertWord("39");
    tree->insertWord("28");








//    tree->root = new AVLTree::AVLNode("C");
//    tree->root->left = new AVLTree::AVLNode("B");
//    tree->root->left->left = new AVLTree::AVLNode("A");

//    AVLTree::rotateRight(tree->root);

    std::cout << "TEST" << std::endl;

    return  0;
}