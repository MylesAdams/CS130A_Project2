//
// Created by Myles on 3/4/2018.
//

#include "TwoFiveTree.hpp"

#include <vector>
#include <string>

/* Begin DataPair for 2-5 Tree */
TwoFiveTree::DataPair::DataPair(std::string data)
{
    this->data = data;
    this->count = 1;
}

TwoFiveTree::DataPair::DataPair(std::string data, int count)
{
    this->data = data;
    this->count = count;
}
/* End DataPair for 2-5 Tree */

/*===============================================*/
/*===============================================*/

/* Begin TwoFiveNode for 2-5 Tree */
TwoFiveTree::TwoFiveNode::TwoFiveNode()
{
    this->data = new std::vector<DataPair*>(5);
    this->pointers = new std::vector<TwoFiveNode*>(5);
    numData = 0;
}

TwoFiveTree::TwoFiveNode::TwoFiveNode(DataPair *&dataPair)
{
    this->data = new std::vector<DataPair*>(5);
    this->pointers = new std::vector<TwoFiveNode*>(5);
    this->data->push_back(dataPair);
    numData = 1;
}

TwoFiveTree::TwoFiveNode::TwoFiveNode(std::vector<DataPair *> *&data)
{
    this->data = data;
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
            if (dataPair->data < data->[i]->data)
            {
                data->insert(data->begin() + i, dataPair);
                numData++;
                return i;
            }
        }
        data->insert(this->data->begin() + numData, dataPair);
        numData++;
        return numData;
    }
    return -1;
}

void TwoFiveTree::TwoFiveNode::insertPointer(TwoFiveNode *node, int index)
{
    this->pointers->insert(this->pointers->begin() + index, node);
}

void TwoFiveTree::TwoFiveNode::insertDataAndPointer(DataPair *&dataPair, TwoFiveNode *node)
{
    int index = insertDataPair(dataPair);
}

void TwoFiveTree::TwoFiveNode::split(TwoFiveNode *&parent)
{
    TwoFiveNode* newPostNode;
    DataPair* premotedData = this->data->[2];
    this->data->erase(this->data->begin() + 2);

}

TwoFiveTree::TwoFiveNode::~TwoFiveNode()
{
    for (int i = 0; i < this->pointers->size(); i++)
        delete this->pointers[i];
    for (int j = 0; j < this->data->size(); j++)
        delete this->data[j];
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
