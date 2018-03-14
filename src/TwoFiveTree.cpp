//
// Created by Myles on 3/4/2018.
//

#include "TwoFiveTree.hpp"

#include <vector>
#include <string>
#include <iostream>

/* Begin DataPair for 2-5 Tree */
TwoFiveTree::DataPair::DataPair(std::string word)
{
    this->word = word;
    this->count = 1;
}

TwoFiveTree::DataPair::DataPair(std::string word, int count)
{
    this->word = word;
    this->count = count;
}
/* End DataPair for 2-5 Tree */

/*===============================================*/
/*===============================================*/

/* Begin TwoFiveNode for 2-5 Tree */
TwoFiveTree::TwoFiveNode::TwoFiveNode(std::string word)
{
    DataPair* dataPair = new DataPair(word);
    this->data = new std::vector<DataPair*>();
    this->data->push_back(dataPair);
    this->pointers = new std::vector<TwoFiveNode*>();
    numData = 1;
}

TwoFiveTree::TwoFiveNode::TwoFiveNode()
{
    this->data = new std::vector<DataPair*>();
    this->pointers = new std::vector<TwoFiveNode*>();
    numData = 0;
}

TwoFiveTree::TwoFiveNode::TwoFiveNode(DataPair *&dataPair)
{
    this->data = new std::vector<DataPair*>();
    this->pointers = new std::vector<TwoFiveNode*>();
    this->data->push_back(dataPair);
    numData = 1;
}

TwoFiveTree::TwoFiveNode::TwoFiveNode(std::vector<DataPair *> *&data)
{
    this->data = data;
    this->pointers = new std::vector<TwoFiveNode*>();
    numData = data->size();
}

TwoFiveTree::TwoFiveNode::TwoFiveNode(std::vector<DataPair *> *&data, std::vector<TwoFiveNode *> *&pointers)
{
    this->data = data;
    this->pointers = pointers;
    numData = data->size();
}

bool TwoFiveTree::TwoFiveNode::isFull()
{
    return (numData >= 5);
}

int TwoFiveTree::TwoFiveNode::insertDataPair(DataPair *&dataPair)
{
    if (!this->isFull())
    {
        for (int i = 0; i < numData; i++)
        {
            if (dataPair->word < (*data)[i]->word)
            {
                data->insert(data->begin() + i, dataPair);
                numData++;
                return i+1;
            }
        }
        data->insert(this->data->begin() + numData, dataPair);
        numData++;
        return numData;
    }
    return -1;
}

void TwoFiveTree::TwoFiveNode::insertDataPair(DataPair *&dataPair, int index)
{
    data->insert(this->data->begin() + index, dataPair);
}

void TwoFiveTree::TwoFiveNode::insertPointer(TwoFiveNode *node, int index)
{
    this->pointers->insert(this->pointers->begin() + index, node);
}

void TwoFiveTree::TwoFiveNode::insertDataAndPointer(DataPair *&dataPair, TwoFiveNode *&newPostNode)
{
    int index = this->insertDataPair(dataPair);

    if (index != -1)
        this->insertPointer(newPostNode, index);
}

bool TwoFiveTree::TwoFiveNode::isLeaf()
{
    return (pointers->size() == 0);
}

TwoFiveTree::TwoFiveNode::~TwoFiveNode()
{
    for (int i = 0; i < pointers->size(); i++)
        delete (*pointers)[i];
    for (int j = 0; j < this->data->size(); j++)
        delete (*data)[j];
    delete this->data;
    delete this->pointers;
}
/* End TwoFiveNode for 2-5 Tree */

/*===============================================*/
/*===============================================*/

/* Begin TwoFiveTree */
TwoFiveTree::TwoFiveTree()
{
    this->root = nullptr;
    this->count = 0;
}

TwoFiveTree::~TwoFiveTree()
{
    delete root;
}

void TwoFiveTree::split(TwoFiveNode* node, TwoFiveNode* parent)
{
    TwoFiveNode* newPostNode;
    DataPair* promotedData = (*node->data)[2];

    // Create sub-vector for right two elements
    std::vector<DataPair*>* rightData = new std::vector<DataPair*>(node->data->begin() + 3, node->data->end());

    // Create new Node for right two elements
    if (!node->isLeaf())
    {
        std::vector<TwoFiveNode*>* rightPointers = new std::vector<TwoFiveNode*>(node->pointers->begin() + 3, node->pointers->end());
        newPostNode = new TwoFiveNode(rightData, rightPointers);
        node->pointers->erase(node->pointers->begin() + POINTER_MIDDLE, node->pointers->end());
    }
    else
        newPostNode = new TwoFiveNode(rightData);

    // Erase moved data
    node->data->erase(node->data->begin() + DATA_MIDDLE, node->data->end());
    node->numData = node->data->size();

    // Promote median
    if (parent != nullptr)
        parent->insertDataAndPointer(promotedData, newPostNode);
    else
    {
        TwoFiveNode* newParent = new TwoFiveNode(promotedData);
        (*newParent->pointers).push_back(node);
        (*newParent->pointers).push_back(newPostNode);
        root = newParent;
    }
}

void TwoFiveTree::insertWord(std::string word)
{
    if (root == nullptr)
    {
        root = new TwoFiveNode(word);
        return;
    }
    insertWord(root, nullptr, word);
}

void TwoFiveTree::insertWord(TwoFiveNode *node, TwoFiveNode *parent, std::string &word)
{
    if (word > (*node->data).back()->word)
    {
        if (!node->isLeaf())
            insertWord((*node->pointers)[node->numData], node, word);
        else
        {
            DataPair *dataPair = new DataPair(word);
            node->insertDataPair(dataPair, node->numData);
            node->numData++;
        }
    }
    else {
        for (int i = 0; i < node->numData; i++)
        {
            if (word < (*node->data)[i]->word)
            {
                if (!node->isLeaf())
                    insertWord((*node->pointers)[i], node, word);
                else
                {
                    DataPair *dataPair = new DataPair(word);
                    node->insertDataPair(dataPair, i);
                    node->numData++;
                }
                break;
            }
            else if ((*node->data)[i]->word == word)
            {
                (*node->data)[i]->count++;
                return;
            }
        }
    }
    if (node->isFull())
        split(node, parent);
}

void TwoFiveTree::deleteWord(TwoFiveNode *n, TwoFiveNode *p, std::string word)
{
    //search word (should return where it is located or the node?)
    TwoFiveNode* nodeCheck = searchWord(n, p, word);


    if (!nodeCheck->isNullNode(nodeCheck))
    {

        if (nodeCheck->isLeaf())
        {
            deleteFromLeaf(word, nodeCheck);
        }

        else if (!nodeCheck->isLeaf())
        {
            deleteFromNonLeaf(word, nodeCheck);
        }
    }


    //if return of searchWord is (leaf) call deleteLeaf function
    //if return of searchWord is not (!leaf) call deleteNotLeaf function
    //deal with merge resolutions

}

TwoFiveTree::TwoFiveNode* TwoFiveTree::searchWord(TwoFiveNode *n, TwoFiveNode *p, std::string w)
{
    // start traversing from root
    // go through data starting with biggest value in back.

    if (w > (*n->data).back()->word)
    {
        return searchWord((*n->pointers)[n->numData], n, w);
    }
    else
    {
        for (int i = 0; i < n->numData; i++)
        {
            if ((*n->data)[i]->word == w)
                return n;
            else if (w < (*n->data)[i]->word)
                if (!n->isLeaf())
                    return searchWord((*n->pointers)[i], n, w);
        }
    }

    TwoFiveNode* nullNode;
    for (int i = 0; i < n->numData; i++)
        (*nullNode->data)[i]->word = "NULL";
    return nullNode;
}

void TwoFiveTree::deleteFromLeaf(std::string word, TwoFiveNode *n)
{
    bool foundWord = false;

    for (int i = 0; i < n->numData; i++)
    {
        if ((*n->data)[i]->word == word)
            foundWord = true;

        if (foundWord && i < (n->numData - 1))
            (*n->data)[i]->word = (*n->data)[i+1]->word;
        else if (foundWord && i == (n->numData - 1))
        {
            (*n->data)[i]->word = "";
            n->numData--;
        }
    }

}

void TwoFiveTree::deleteFromNonLeaf(std::string word, TwoFiveNode *n)
{
    bool foundWord = false;
    for (int i = 0; i < n->numData; i++)
    {
        if ((*n->data)[i]->word == word)
            foundWord = true;

        if (n->numData <= ((*n->pointers).size() - 1) && foundWord)
        {
            (*n->data)[i]->word = (*n->pointers)[i]->data->back()->word;
            (*n->pointers)[i]->data->back()->word = "";
            (*n->pointers)[i]->numData--;
            foundWord = false;
            //(*n->data)[i]->word = (*n->data)[i+1]->word;
        }


    }

}

void TwoFiveTree::printTree(TwoFiveNode *n)
{

    if (!n->isLeaf())
    {
        for (int i = 0; i <= n->numData; i++)
            printTree((*n->pointers)[i]);
    }

    for (int i = 0; i < n->numData; i++)
        std::cout << (*n->data)[i]->word << std::endl;

}

bool TwoFiveTree::TwoFiveNode::isNullNode(TwoFiveNode *n){
    bool flag = true;

    for (int i = 0; i < n->numData; i++)
       if((*n->data)[i]->word != "NULL")
           flag = false;

    return flag;
}