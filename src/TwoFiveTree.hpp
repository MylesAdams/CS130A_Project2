//
// Created by Myles on 3/4/2018.
//

#ifndef CS130A_PROJECT2_TWOFIVETREE_HPP
#define CS130A_PROJECT2_TWOFIVETREE_HPP

#include <vector>
#include <string>

class TwoFiveTree {
    // Key Value pair for 2-5 Pair
    struct DataPair
    {
        std::string data;
        int count;

        DataPair(std::string data);
        DataPair(std::string data, int count);
    };

    // Node for 2-5 Tree
    struct TwoFiveNode
    {
        std::vector<DataPair*>* data;
        std::vector<TwoFiveNode*>* pointers;
        int numData;

        TwoFiveNode();
        explicit TwoFiveNode(DataPair*& dataPair);
        explicit TwoFiveNode(std::vector<DataPair*>*& data);
        bool isFull();
        int insertDataPair(DataPair*& dataPair);
        void insertPointer(TwoFiveNode* node, int index);
        void deleteDataPair(DataPair*& dataPair);
        void insertDataAndPointer(DataPair*& dataPair, TwoFiveNode* node);
        void split(TwoFiveNode*& parent);
        ~TwoFiveNode();

    };

private:
    TwoFiveNode* root;
    int count;



public:
    TwoFiveTree();
    ~TwoFiveTree();
    bool searchWord(std::string word);
    void insertWord(std::string key);
    void deleteWord(std::string key);
    std::vector<std::string> sort();
    void rangeSearch(std::string first, std::string last);

};


#endif //CS130A_PROJECT2_TWOFIVETREE_HPP
