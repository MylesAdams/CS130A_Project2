//
// Created by Myles Adams on 2/27/18.
//

#include <iostream>
#include "AVLTree.hpp"
#include "TwoFiveTree.hpp"

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

//    tree->insertWord("18");
//    tree->insertWord("23");
//    tree->insertWord("27");
//    tree->insertWord("13");
//    tree->insertWord("16");
//    tree->insertWord("10");
//    tree->insertWord("33");
//    tree->insertWord("39");
//    tree->insertWord("28");


//    std::vector<AVLTree::AVLNode*> nodes;
//
//    AVLTree::AVLNode* node = new AVLTree::AVLNode("a");
//    nodes.push_back(node);
//
//    AVLTree::AVLNode* nodeptr = nodes[0];
//
//    nodes.erase(nodes.begin(), nodes.end());
//
//    TwoFiveTree::TwoFiveNode* node1 = new TwoFiveTree::TwoFiveNode("a");
//    TwoFiveTree::TwoFiveNode* node2 = new TwoFiveTree::TwoFiveNode("b");
//
//    std::vector<TwoFiveTree::TwoFiveNode*>* moreNodes = new std::vector<TwoFiveTree::TwoFiveNode*>({node1, node2});
//
//    std::cout << (*(*moreNodes)[0]->data)[0]->word << std::endl;
//    std::cout << (*(*moreNodes)[1]->data)[0]->word << std::endl;
//
//    std::cout << moreNodes->size() << std::endl;
//    std::cout << (*(*moreNodes)[1]->data).size() << std::endl;



//    std::cout << nodeptr->data << nodeptr->count << nodes.size() << std::endl;


//    std::vector<TwoFiveTree::TwoFiveNode*>* nodes2 = new std::vector<TwoFiveTree::TwoFiveNode*>(5);
//    std::cout << nodes2->size()<< std::endl;
//    std::cout << ((*nodes2)[0] == nullptr) << std::endl;



//    tree->root = new AVLTree::AVLNode("C");
//    tree->root->left = new AVLTree::AVLNode("B");
//    tree->root->left->left = new AVLTree::AVLNode("A");

//    AVLTree::rotateRight(tree->root);

    TwoFiveTree* tft = new TwoFiveTree();

    tft->insertWord("30");
//    std::cout << (*tft->getRoot()->data)[0]->word << std::endl;
    tft->insertWord("10");
    tft->insertWord("15");
    tft->insertWord("40");
    tft->insertWord("45");
    tft->insertWord("20");
    tft->insertWord("50");
    tft->insertWord("55");
    tft->insertWord("60");
    tft->insertWord("24");
    tft->insertWord("28");
    tft->insertWord("12");
    tft->insertWord("11");
    tft->insertWord("14");
    tft->insertWord("56");
    tft->insertWord("57");
    tft->insertWord("70");

    //prints left, right, parent. So root is last
    tft->printTree(tft->getRoot());


    tft->deleteWord(tft->getRoot(), tft->getRoot(), "70");

    std::cout << "\n\n Deleted 70.. Result: \n";

    tft->printTree(tft->getRoot());

    tft->deleteWord(tft->getRoot(), tft->getRoot(), "60");


    std::cout << "\n\n Deleted 60.. Result: \n";

    tft->printTree(tft->getRoot());

    tft->deleteWord(tft->getRoot(), tft->getRoot(), "10");

    std::cout << "\n\n Deleted 10.. Result: \n";

    tft->printTree(tft->getRoot());

    tft->deleteWord(tft->getRoot(), tft->getRoot(), "11");

    std::cout << "\n\n Deleted 11.. Result: \n";

    tft->printTree(tft->getRoot());

    tft->deleteWord(tft->getRoot(), tft->getRoot(), "45");

    std::cout << "\n\n Deleted 45.. Result: \n";

    tft->printTree(tft->getRoot());

    tft->deleteWord(tft->getRoot(), tft->getRoot(), "55");

    std::cout << "\n\n Deleted 55.. Result: \n";

    tft->printTree(tft->getRoot());





//    for (int i = 0; i < tft->getRoot()->numData; i++)
//    {
//        for (int j = 0; j < (*tft->getRoot()->pointers)[i]->data->size(); j++)
//        {
//            std::cout << (*(*tft->getRoot()->pointers)[i]->data)[j]->word << std::endl;
//        }
//        std::cout << "Root: " << (*tft->getRoot()->data)[i]->word << std::endl;
//    }
//
//    int index = tft->getRoot()->numData;
//    std::vector<TwoFiveTree::DataPair*> vec = (*(*tft->getRoot()->pointers)[index]->data);
//    int endSize = vec.size();
//    for (int i = 0; i < endSize; i++)
//    {
//        std::cout << (*(*tft->getRoot()->pointers)[tft->getRoot()->numData]->data)[i]->word << std::endl;
//    }


    std::cout << "\n" << std::endl;

    TwoFiveTree::DataPair* datapair = new TwoFiveTree::DataPair("Hello");
    delete datapair;
    std::cout << datapair->word << std::endl;

    return  0;
}