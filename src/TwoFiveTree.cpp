//
// Created by Myles on 3/4/2018.
//

#include "TwoFiveTree.hpp"

#include <vector>
#include <string>
#include <iostream>
#include <exception>

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
    Truple nodeCheck = searchWord(n, p, word);

    if (nodeCheck.node != nullptr)
    {
        if (nodeCheck.node->isLeaf())
        {
            deleteFromLeaf(nodeCheck);
        }

        else if (!nodeCheck.node->isLeaf())
        {
            deleteFromNonLeaf(word, nodeCheck.node);
        }
    }

}

TwoFiveTree::Truple TwoFiveTree::searchWord(TwoFiveNode *n, TwoFiveNode *p, std::string w)
{
    // start traversing from root
    // go through data starting with biggest value in back.
    // need to return pair of node and parent

    if (w > (*n->data).back()->word)
    {
        return searchWord((*n->pointers)[n->numData], n, w);
    }

    else
    {
        for (int i = 0; i < n->numData; i++)
        {
            if ((*n->data)[i]->word == w)
            {
                Truple nodeTruple(n,p,i);
                return nodeTruple;
            }

            else if (w < (*n->data)[i]->word)
                if (!n->isLeaf())
                    return searchWord((*n->pointers)[i], n, w);
        }
    }

    return Truple();
}

void TwoFiveTree::deleteFromLeaf(Truple tru)
{
    //case 1: leaf contains more than 1 value. Simply delete value
    if (tru.node->numData > 1)
    {
        for (int i = tru.index; i < tru.node->numData; i++)
        {
            if (i < tru.node->numData-1)
                (*tru.node->data)[i]->word = (*tru.node->data)[i+1]->word;

            else if (i == tru.node->numData-1)
            {
                delete((*tru.node->data)[i]);
                tru.node->numData--;
            }

        }
    }

    else
    {
        for (int i = 0; i < tru.parent->pointers->size(); i++)
        {
            if ((*tru.parent->pointers)[i]->data[tru.index] == tru.node->data[tru.index])
            {
                //found which pointer in parent holds node

                //case 2: leaf contains 1 but left neighbor has an extra. Call rotate right
                if(i > 0 && (*tru.parent->pointers)[i-1]->numData > 1)
                {
                    //rotate right
                }

                //case 3: leaf contains 1 but right neighbor has an extra. Call rotate left
                else if (i < tru.parent->pointers->size()-1 && (*tru.parent->pointers)[i+1]->numData > 1)
                {
                    //rotate left
                }

                //case 4: leaf contains 1 and no neighbors have extras
                else
                {
                    if (i > 0 && i < tru.parent->pointers->size()-1)
                    {
                        //merge with a node to the right (append this node that will be deleted to it)
                        //possible code:
                        //delete(merge(tru.parent->pointers[i],tru.parent->pointers[i-1],tru.parent)[1])
                        //decrement numdata on returned node

                    }
                    else
                    {
                        //merge with a node to the left (append this node that will be deleted to it)
                        //possible code:
                        //delete(merge(tru.parent->pointers[i],tru.parent->pointers[i+1],tru.parent)[3])
                        //decrement numdata on returned node
                    }

                }
            }
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

        if ((*n->pointers)[i]->numData >= 2 && foundWord)
        {
            (*n->data)[i]->word = (*n->pointers)[i]->data->back()->word;
            (*n->pointers)[i]->data->erase((*n->pointers)[i]->data->begin()+i);
            (*n->pointers)[i]->numData--;
            foundWord = false;
        }

        else if ((*n->pointers)[i+1]->numData >= 2 && foundWord)
        {
            (*n->data)[i]->word = (*n->pointers)[i+1]->data->front()->word;
            (*n->pointers)[i]->data->erase((*n->pointers)[i]->data->begin()+i);
            (*n->pointers)[i]->numData--;
            foundWord = false;
        }

        else if (foundWord)
        {
            //merge((*n->pointers)[i+1],(*n->pointers)[i]);
            deleteWord(root, root, word);
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

//bool TwoFiveTree::TwoFiveNode::isNullNode(TwoFiveNode *n)
//{
//    bool flag = true;
//
//    for (int i = 0; i < n->numData; i++)
//       if((*n->data)[i]->word != "NULL")
//           flag = false;
//
//    return flag;
//}

TwoFiveTree::TwoFiveNode* TwoFiveTree::merge(TwoFiveNode *node, TwoFiveNode *parent)
{
	if (node == nullptr)
		throw std::runtime_error("Tried to merge nullptr");
    if (node->numData != 1 || node->numData != 1)
        throw std::runtime_error("Tried to merge nodes of size greater than one");

	TwoFiveNode* leftNode;
	TwoFiveNode* rightNode;

	int nodeNdx, leftNdx, rightNdx;
    for (nodeNdx = 0; (*parent->pointers)[nodeNdx] != node; nodeNdx++) {}

	if (nodeNdx == (*parent->pointers).size() - 1)
	{
		leftNode = (*parent->pointers)[nodeNdx - 1];
		rightNode = (*parent->pointers)[nodeNdx];
		leftNdx = nodeNdx - 1;
		rightNdx = nodeNdx;
	}
	else
	{
		leftNode = (*parent->pointers)[nodeNdx];
		rightNode = (*parent->pointers)[nodeNdx + 1];
		leftNdx = nodeNdx;
		rightNdx = nodeNdx + 1;
	}

	if (node->isLeaf())
	{
		// Leafs being merged must be of size 1
		if (node->numData != 1 || node->numData != 1)
			throw std::runtime_error("Tried to merge nodes of size greater than one");

		// Append seperator from parent and delete value
		(*leftNode->data).push_back((*parent->data)[leftNdx]);
		(*parent->data).erase((*parent->data).begin() + leftNdx);
		parent->numData--;
		leftNode->numData++;

		// Append value from right neighbor and delete right node
		(*leftNode->data).push_back((*rightNode->data)[0]);
		(*rightNode->pointers).erase((*rightNode->pointers).begin());
		leftNode->numData++;
		delete rightNode;
		(*parent->pointers).erase((*parent->pointers).begin() + leftNdx + 1);
	}
	else
	{
		for (int i = 0; i < rightNode->numData; i++)
		{
			(*leftNode->data).push_back((*rightNode->data)[i]);
			(*leftNode->pointers).push_back((*rightNode->pointers)[i]);
		}

		(*leftNode->pointers).push_back((*rightNode->pointers)[rightNode->numData]);

		(*rightNode->data).clear();
		(*rightNode->pointers).clear();

		delete rightNode;

		if (leftNode->isFull())
			split(leftNode, parent);
			
			// Continue work here

	}
}

void TwoFiveTree::rotateLeft(TwoFiveTree::Truple tru)
{
    //left neighbor only has 1 value so we are borrowing from
    //the right neighbor and moving parent down

    //take value of parent and place it where current node is
    //take first value of neighbor and place it where parent was
    //readjust vector of neighbor

    int i;
    for (i = 0; (*tru.parent->pointers)[i]->data[tru.index] != tru.node->data[tru.index]; i++);

    (*tru.node->data)[tru.index]->word = (*tru.parent->data)[i]->word;
    (*tru.parent->data)[i]->word = (*(*tru.parent->pointers)[i+1]->data)[0]->word;

    for (int j = 0; j < (*tru.parent->pointers)[i+1]->numData - 1; j++)
    {
        (*(*tru.parent->pointers)[i+1]->data)[j]->word = (*(*tru.parent->pointers)[i+1]->data)[j+1]->word;
    }

    delete((*tru.parent->pointers)[i+1]->data->back());
}

void TwoFiveTree::rotateRight(TwoFiveTree::Truple tru)
{
    //right neighbor only has 1 value so we are borrowing from
    //the left neighbor and moving parent down

    //take value of parent and place it where current node is
    //take last value of neighbor and place it where parent was
    //no need to readjust vector of neighbor since we took from back? just delete

    int i;
    for (i = 0; (*tru.parent->pointers)[i]->data[tru.index] != tru.node->data[tru.index]; i++);

    (*tru.node->data)[tru.index]->word = (*tru.parent->data)[i]->word;
    (*tru.parent->data)[i]->word = (*(*tru.parent->pointers)[i-1]->data).back()->word;

    delete((*tru.parent->pointers)[i-1]->data->back());
}

TwoFiveTree::Truple::Truple()
{
    node = nullptr;
    parent = nullptr;
    index = -1;
}

TwoFiveTree::Truple::Truple(TwoFiveNode *n, TwoFiveNode* p, int i)
{
    node = n;
    parent = p;
    index = i;
}