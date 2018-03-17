
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

TwoFiveTree::DataPair::~DataPair() {

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
    (*data).clear();
    (*pointers).clear();

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
    std::vector<DataPair*>* rightData = new std::vector<DataPair*>((*node->data).begin() + 3, (*node->data).begin() + (*node->data).size());

    // Create new Node for right two elements
    if (!node->isLeaf())
    {
        std::vector<TwoFiveNode*>* rightPointers = new std::vector<TwoFiveNode*>((*node->pointers).begin() + 3, (*node->pointers).begin() + (*node->pointers).size());
        newPostNode = new TwoFiveNode(rightData, rightPointers);
        for (auto i = ((*node->pointers).begin() + POINTER_MIDDLE);  i != (*node->pointers).begin() + (*node->pointers).size(); i++)
        {
            *i = nullptr;
        }
        (*node->pointers).erase((*node->pointers).begin() + POINTER_MIDDLE, (*node->pointers).begin() + (*node->pointers).size());
    }
    else
        newPostNode = new TwoFiveNode(rightData);

    // Erase moved data
    for (auto i = ((*node->data).begin() + DATA_MIDDLE);  i != (*node->data).begin() + (*node->data).size(); i++)
    {
        *i = nullptr;
    }
    (*node->data).erase((*node->data).begin() + DATA_MIDDLE, (*node->data).begin() + (*node->data).size());
    node->numData = (*node->data).size();

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
    if (word == "")
        return;

    if (root == nullptr)
    {
        root = new TwoFiveNode(word);
        return;
    }
    insertWord(root, nullptr, word);
}

void TwoFiveTree::insertWord(TwoFiveNode *node, TwoFiveNode *parent, std::string &word)
{
    if (word > (*node->data)[node->numData - 1]->word)
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

TwoFiveTree::Truple* TwoFiveTree::searchWord(TwoFiveNode *n, TwoFiveNode *p, std::string w)
{
    // start traversing from root
    // go through data starting with biggest value in back.
    // need to return pair of node and parent

    if (w > (*n->data)[n->numData - 1]->word && !n->isLeaf())
    {
        return searchWord((*n->pointers)[n->numData], n, w);
    }

    else
    {
        for (int i = 0; i < n->numData; i++)
        {
            if ((*n->data)[i]->word == w)
            {
                Truple* nodeTruple = new Truple(n,p,i);
                return nodeTruple;
            }

            else if (w < (*n->data)[i]->word)
                if (!n->isLeaf())
                    return searchWord((*n->pointers)[i], n, w);
        }
    }



    return nullptr;
}

void TwoFiveTree::deleteFromLeaf(Truple &tru)
{
    if (root == tru.node)
    {
        delete (*root->data)[tru.index];
        (*root->data)[tru.index] = nullptr;
        (*((tru.node)->data)).erase((*((tru.node)->data)).begin()+tru.index);
        (tru.node)->numData--;

        if (root->numData == 0)
        {
            delete root;
            root = nullptr;
        }
        return;

    }
    //case 1: leaf contains more than 1 value. Simply delete value
    if (tru.node->numData > 1)
    {
        (*((tru.node)->data)).erase((*((tru.node)->data)).begin()+tru.index);
        (tru.node)->numData--;
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
                    rotateRight(tru);
                }

                //case 3: leaf contains 1 but right neighbor has an extra. Call rotate left
                else if (i < tru.parent->pointers->size()-1 && (*tru.parent->pointers)[i+1]->numData > 1)
                {
                    rotateLeft(tru);
                }

                //case 4: leaf contains 1 and no neighbors have extras
                else
                {
                    mergeAndDelete(tru.node, tru.parent, (*tru.node->data)[tru.index]->word);
                }
            }
        }
    }

}

void TwoFiveTree::deleteFromNonLeaf(TwoFiveNode* node, TwoFiveNode* parent, std::string word)
{
    int ndx;
    for (ndx = 0; (*node->data)[ndx]->word != word; ndx++);

    TwoFiveTree::DataPair* maxDataPair = findMax((*node->pointers)[ndx]);

    delete (*node->data)[ndx];
    (*node->data)[ndx] = new DataPair(maxDataPair->word, maxDataPair->count);
    maxDataPair->count = 1;
    deleteWordFromTree((*node->pointers)[ndx], node, maxDataPair->word);
}

void TwoFiveTree::printTree(TwoFiveNode *n)
{

    if (!n->isLeaf())
    {
        for (int i = 0; i <= n->numData; i++)
            printTree((*n->pointers)[i]);
    }

    for (int i = 0; i < n->numData; i++)
    {
        std::cout << (*n->data)[i]->word << " | " << (*n->data).size() << std::endl;

    }

}

TwoFiveTree::TwoFiveNode* TwoFiveTree::merge(TwoFiveNode *node, TwoFiveNode *parent)
{
	if (node == nullptr)
		throw std::runtime_error("Tried to merge nullptr");

    if (parent == nullptr)
        return nullptr;

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

		// Append seperator from parent and delete value
		(*leftNode->data).push_back((*parent->data)[leftNdx]);
        (*parent->data)[leftNdx] = nullptr;
		(*parent->data).erase((*parent->data).begin() + leftNdx);
		parent->numData--;
		leftNode->numData++;

		// Append value from right neighbor and delete right node
        if (rightNode->numData > 0)
        {
            (*leftNode->data).push_back((*rightNode->data)[0]);
            leftNode->numData++;
        }


		delete rightNode;
        (*parent->pointers)[rightNdx] = nullptr;
        (*parent->pointers).erase((*parent->pointers).begin() + rightNdx);

    }
	else
	{
        (*leftNode->data).push_back((*parent->data)[leftNdx]);
        leftNode->numData++;
        (*parent->data)[leftNdx] = nullptr;
        (*parent->data).erase((*parent->data).begin() + leftNdx);
        parent->numData--;
		for (int i = 0; i < rightNode->numData; i++)
		{
			(*leftNode->data).push_back((*rightNode->data)[i]);
            (*rightNode->data)[i] = nullptr;
            leftNode->numData++;
		}

        for (int i = 0; i < (*rightNode->pointers).size(); i++)
        {
            (*leftNode->pointers).push_back((*rightNode->pointers)[i]);
            (*rightNode->pointers)[i] = nullptr;
        }

        (*rightNode->pointers).erase((*rightNode->pointers).begin(), (*rightNode->pointers).begin() + (*rightNode->pointers).size());
        (*parent->pointers)[rightNdx] = nullptr;
        (*parent->pointers).erase((*parent->pointers).begin() + rightNdx);

		delete rightNode;
	}
    return leftNode;
}

void TwoFiveTree::rotateLeft(TwoFiveTree::Truple tru)
{
    //left neighbor only has 1 value so we are borrowing from
    //the right neighbor and moving parent down

    int i;
    for (i = 0; (*tru.parent->pointers)[i]->data[tru.index] != tru.node->data[tru.index]; i++);

    (*tru.node->data).erase((*tru.node->data).begin());
    (*tru.node->data).push_back((*tru.parent->data)[i]);
    (*tru.parent->data)[i] = (*(*tru.parent->pointers)[i+1]->data).front();

    (*(*tru.parent->pointers)[i+1]->data)[0] = nullptr;


    (*(*tru.parent->pointers)[i+1]->data).erase((*(*tru.parent->pointers)[i+1]->data).begin());
    (*tru.parent->pointers)[i+1]->numData--;

}

void TwoFiveTree::rotateRight(TwoFiveTree::Truple tru)
{
    //right neighbor only has 1 value so we are borrowing from
    //the left neighbor and moving parent down

    int i;
    for (i = 0; (*tru.parent->pointers)[i]->data[tru.index] != tru.node->data[tru.index]; i++);

    (*tru.node->data).erase((*tru.node->data).begin());
    (*tru.node->data).push_back((*tru.parent->data)[i-1]);

    (*tru.parent->data)[i-1] = (*(*tru.parent->pointers)[i-1]->data)[(*tru.parent->pointers)[i-1]->numData - 1];

    (*(*tru.parent->pointers)[i-1]->data)[(*tru.parent->pointers)[i-1]->numData - 1] = nullptr;
    (*(*tru.parent->pointers)[i-1]->data).erase((*(*tru.parent->pointers)[i-1]->data).begin()+(*tru.parent->pointers)[i-1]->numData-1);
    (*tru.parent->pointers)[i-1]->numData--;
}

void TwoFiveTree::mergeAndDelete(TwoFiveTree::TwoFiveNode *node, TwoFiveTree::TwoFiveNode *parent, std::string word)
{
    TwoFiveNode* leftNode;

    for (int i = 0; i < node->numData; i ++)
    {
        if ((*node->data)[i]->word == word)
        {
            delete (*node->data)[i];
            (*node->data)[i] = nullptr;
            (*node->data).erase((*node->data).begin() + i);
            node->numData--;
            leftNode = merge(node, parent);
            break;
        }
    }
    if ((leftNode != nullptr) && (leftNode->isFull()))
        split(leftNode, parent);

}


void TwoFiveTree::deleteWordFromTree(std::string word)
{
    deleteWordFromTree(root, nullptr, word);
}

void TwoFiveTree::deleteWordFromTree(TwoFiveTree::TwoFiveNode* node, TwoFiveTree::TwoFiveNode *parent, std::string word)
{
    if (node == nullptr)
        return;

    if (word > (*node->data)[node->numData - 1]->word)
    {
        if (!node->isLeaf())
        {
            deleteWordFromTree((*node->pointers)[node->numData], node, word);
        }
    }
    else {
        for (int i = 0; i < node->numData; i++)
        {
            if (word < (*node->data)[i]->word)
            {
                if (!node->isLeaf())
                {
                    deleteWordFromTree((*node->pointers)[i], node, word);
                    break;
                }
            }
            else if ((*node->data)[i]->word == word)
            {
                if ((*node->data)[i]->count > 1)
                {
                    (*node->data)[i]->count--;
                    return;
                }
                else
                {
                    if (node->isLeaf())
                    {
                        Truple truple(node, parent, i);
                        deleteFromLeaf(truple);
                        break;
                    }
                    else
                    {
                        deleteFromNonLeaf(node, parent, word);
                        break;
                    }
                }
            }
        }
    }

    if (this->root == nullptr && parent == nullptr)
    {
        return;
    }

    if (node->numData == 0 && parent == nullptr)
    {
        this->root = (*node->pointers)[0];
        (*node->pointers)[0] = nullptr;
        delete node;
        return;
    }

    bool found = false;
    if (parent)
    {
        for (int i = 0; i < (*parent->pointers).size(); i++)
        {
            if ((*parent->pointers)[i] == node)
                found = true;
        }

        if (!found)
            return;
    }

    if (node->isFull())
        split(node, parent);

    TwoFiveNode* leftNode;

    if (node->numData == 0)
    {
        leftNode = merge(node, parent);
        if (leftNode != nullptr && leftNode->isFull())
            split(leftNode, parent);

        if (parent == this->root)
        {
            if (parent->numData == 0)
            {
                this->root = node;
            }
        }
    }

}

TwoFiveTree::DataPair *TwoFiveTree::findMax(TwoFiveTree::TwoFiveNode *node)
{
    if (!node->isLeaf())
    {
        return findMax((*node->pointers)[node->numData]);
    }
    else
    {
        return (*node->data)[node->numData - 1];
    }
}

void TwoFiveTree::rangeSearch(TwoFiveNode* node,std::string first, std::string last)
{
    if (node == nullptr)
        return;


    for (int i = 0; i < node->numData; i++)
    {
        if (((*node->data)[i]->word > first) && !node->isLeaf())
            rangeSearch((*node->pointers)[i], first, last);

        if ((*node->data)[i]->word >= first && (*node->data)[i]->word <= last)
            std::cout << (*node->data)[i]->word << "\n";
    }

    if ((*node->data)[node->numData - 1]->word < last && !node->isLeaf())
        rangeSearch((*node->pointers)[node->numData], first, last);

}

void TwoFiveTree::sort(TwoFiveNode* node)
{
    if (!node->isLeaf())
        sort((*node->pointers)[0]);

    for (int i = 0; i < node->numData; i++)
    {
            TwoFiveTree::sortedOutput.push_back((*node->data)[i]->word);

        if (!node->isLeaf())
            sort((*node->pointers)[i+1]);
    }
}

std::vector<std::string> TwoFiveTree::sort()
{
    sortedOutput.clear();

    if (this->root == nullptr)
        return sortedOutput;

    sort(this->getRoot());
    return this->sortedOutput;
}

bool TwoFiveTree::search(std::string word)
{
    if (this->getRoot() == nullptr)
        return false;

    if (searchWord(this->getRoot(), this->getRoot(), word) == nullptr)
        return false;
    else
        return true;
}

void TwoFiveTree::rangeSearch(std::string first, std::string last)
{
    rangeSearch(this->getRoot(), first, last);
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
