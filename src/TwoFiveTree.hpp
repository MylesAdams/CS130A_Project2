//
// Created by Myles on 3/4/2018.
//

#ifndef CS130A_PROJECT2_TWOFIVETREE_HPP
#define CS130A_PROJECT2_TWOFIVETREE_HPP

#include <vector>
#include <string>

const int DATA_MIDDLE = 2;
const int POINTER_MIDDLE = 3;

class TwoFiveTree {
public:
    // Key Value pair for 2-5 Pair
    struct DataPair
    {
        std::string word;
        int count;

        DataPair(std::string word);
        DataPair(std::string word, int count);
    };

    // Node for 2-5 Tree
    struct TwoFiveNode
    {
        std::vector<DataPair*>* data;
        std::vector<TwoFiveNode*>* pointers;
        int numData;

        TwoFiveNode();
        explicit TwoFiveNode(std::string word);
        explicit TwoFiveNode(DataPair*& dataPair);
        // Only for leaf nodes
        explicit TwoFiveNode(std::vector<DataPair*>*& data);
        // For non leaf nodes
        TwoFiveNode(std::vector<DataPair*>*& data, std::vector<TwoFiveNode*>*& pointers);
        bool isFull();
        bool isNullNode(TwoFiveNode *n);
        int insertDataPair(DataPair*& dataPair);
        void insertDataPair(DataPair*& dataPair, int index);
        void insertPointer(TwoFiveNode* node, int index);
        void deleteDataPair(DataPair*& dataPair);
        void insertDataAndPointer(DataPair*& dataPair, TwoFiveNode*& node);
        bool isLeaf();
        ~TwoFiveNode();

    };

private:
    TwoFiveNode* root;
    int count;
    void insertWord(TwoFiveNode* node, TwoFiveNode* parent, std::string& word);
    void split(TwoFiveNode* node, TwoFiveNode* parent);



public:
    TwoFiveTree();
    ~TwoFiveTree();
    TwoFiveNode* searchWord(TwoFiveNode *n, TwoFiveNode *p, std::string word);
    void insertWord(std::string word);
    void deleteWord(TwoFiveNode *nodeCheck, TwoFiveNode *p, std::string word);
    std::vector<std::string> sort();
    void rangeSearch(std::string first, std::string last);
    void merge(TwoFiveNode *n1, TwoFiveNode *n2);
    void printTree(TwoFiveNode *n);
    void deleteFromLeaf(std::string word, TwoFiveNode *n);
    void deleteFromNonLeaf(std::string word, TwoFiveNode *n);
    TwoFiveNode* getRoot() {return this->root;}

};


#endif //CS130A_PROJECT2_TWOFIVETREE_HPP
