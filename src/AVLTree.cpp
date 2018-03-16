//
// Created by Myles Adams on 2/27/18.
//

#include "AVLTree.hpp"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>


AVLTree::AVLTree()
{
    this->root = nullptr;
    this->count = 0;
}

AVLTree::~AVLTree()
{
    delete root;
}

void AVLTree::rotateLeft(AVLNode*& root)
{
    AVLNode* newRoot = root->right;
    root->right = newRoot->left;
    newRoot->left = root;
    root = newRoot;
    setHeight(root->left);
    setHeight(root);
}

void AVLTree::rotateRight(AVLNode*& root)
{
    AVLNode* newRoot = root->left;
    root->left = newRoot->right;
    newRoot->right = root;
    root = newRoot;
    setHeight(root->right);
    setHeight(root);
}

bool AVLTree::searchWord(std::string word)
{
    AVLNode* cur;

    if (root == nullptr)
        return false;
    else
    {
        cur = root;
        int comp;
        while(cur != nullptr)
        {
            if ((comp = word.compare(cur->data)) == 0)
                return true;
            else if (comp < 0)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return false;
    }
}

AVLTree::AVLNode* AVLTree::searchNode(std::string word)
{
    AVLNode* cur;

    if (root == nullptr)
        return nullptr;
    else
    {
        cur = root;
        int comp;
        while(cur != nullptr)
        {
            if ((comp = word.compare(cur->data)) == 0)
                return cur;
            else if (comp < 0)
                cur = cur->left;
            else
                cur = cur->right;
        }
        return nullptr;
    }
}

void AVLTree::insertWord(std::string word)
{
    insertWord(root, word);
}

void AVLTree::insertWord(AVLNode*& root, std::string& word)
{
    if (root == nullptr)
    {
        root = new AVLNode(word);
        count++;
        return;
    }
    if (word < root->data)
        insertWord(root->left, word);
    else if (word > root->data)
        insertWord(root->right, word);
    else
    {
        root->count++;
        return;
    }
    setHeight(root);
    balanceTree(root);
}

void AVLTree::deleteWord(std::string &word)
{
    AVLNode* tempParent = new AVLNode();
    deleteWord(root, tempParent, word);
    delete tempParent;
}

void AVLTree::deleteWord(AVLNode *&node, AVLNode*& parent, std::string &word)
{
    if (node == nullptr)
        return;
    if (word < node->data)
        deleteWord(node->left, node, word);
    else if (word > node->data)
        deleteWord(node->right, node, word);
    else
    {
        if (node->count > 1)
        {
            node->count--;
            return;
        }
        else if (node->left == nullptr && node->right == nullptr)
        {
            if (node != root)
            {
                if (parent->left == node)
                    parent->left = nullptr;
                else
                    parent->right = nullptr;
            }
            else
                root = nullptr;
            delete node;
            count--;
        }
        else if (node->left != nullptr && node->right != nullptr)
        {
            AVLNode* rSubMin = findMinimum(node->right);

            std::string newData = rSubMin->data;
            
            int newCount = rSubMin->count;
            deleteWord(node, parent, newData);

            node->data = newData;
            node->count = newCount;
        }
        else
        {
            AVLNode* child = (node->left)? node->left: node->right;
            if (node != root)
            {
                if (node == parent->left)
                    parent->left = child;
                else
                    parent->right = child;
            }
            else
                root = child;

            node->left = nullptr;
            node->right = nullptr;
            delete node;
            count--;
        }
    }
    if (parent->data != "")
    {
        setHeight(parent);
        balanceTree(parent);
    }
}

AVLTree::AVLNode* AVLTree::findMinimum(AVLNode* node)
{
    while (node->left != nullptr)
        node = node->left;

    return node;
}

void AVLTree::balanceTree(AVLNode*& root)
{
    int balance = getBalance(root);

    if (balance < -1)
    {
        if (getBalance(root->right) <= 0)
        {
            //RR
            rotateLeft(root);
        }
        else
        {
            //RL
            rotateRight(root->right);
            rotateLeft(root);
        }
    }
    else if (balance > 1)
    {
        if (getBalance(root->left) >= 0)
        {
            //LL
            rotateRight(root);
        }
        else
        {
            //LR
            rotateLeft(root->left);
            rotateRight(root);
        }
    }
}

void AVLTree::setHeight(AVLNode *&root)
{
    root->height = 1 + std::max(AVLNode::getHeight(root->left),
                                AVLNode::getHeight(root->right));
}

int AVLTree::getBalance(AVLNode *root)
{
    return AVLNode::getHeight(root->left) - AVLNode::getHeight(root->right);
}

std::vector<std::string> AVLTree::sort()
{
    std::vector<std::string> sortedWords;
    inOrder(this->root, sortedWords);
    return sortedWords;
}

void AVLTree::inOrder(AVLNode* root, std::vector<std::string>& vec)
{
    if (root == nullptr)
        return;
    else
    {
        inOrder(root->left, vec);
        vec.push_back(root->data);
        inOrder(root->right, vec);
    }
}

void AVLTree::rangeSearch(std::string first, std::string last)
{
    inOrderRange(root, first, last);
}

void AVLTree::inOrderRange(AVLNode* root, std::string first, std::string last)
{
    if (root == nullptr)
        return;

    inOrderRange(root->left, first, last);
    if (root->data >= first && root->data <= last)
        std::cout << root->data << std::endl;
    inOrderRange(root->right, first, last);
}
