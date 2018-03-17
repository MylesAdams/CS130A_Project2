
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
        ~DataPair();
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
        int insertDataPair(DataPair*& dataPair);
        void insertDataPair(DataPair*& dataPair, int index);
        void insertPointer(TwoFiveNode* node, int index);
        void insertDataAndPointer(DataPair*& dataPair, TwoFiveNode*& node);
        bool isLeaf();
        ~TwoFiveNode();

    };

    struct Truple
    {
        TwoFiveNode* node;
        TwoFiveNode* parent;
        int index;

        Truple ();
        Truple (TwoFiveNode* node, TwoFiveNode* parent, int index);
    };


private:
    TwoFiveNode* root;
    void insertWord(TwoFiveNode* node, TwoFiveNode* parent, std::string& word);
    std::vector<std::string> sortedOutput;



public:
    TwoFiveTree();
    ~TwoFiveTree();
    bool search(std::string word);
    Truple* searchWord(TwoFiveNode *n, TwoFiveNode *p, std::string word);
    void insertWord(std::string word);
    std::vector<std::string> sort();
    void sort(TwoFiveNode *node);
    void rangeSearch(std::string first, std::string last);
    void rangeSearch(TwoFiveNode *node, std::string first, std::string last);
    TwoFiveNode* merge(TwoFiveNode *node, TwoFiveNode *parent);
    void mergeAndDelete(TwoFiveNode* node, TwoFiveNode* parent, std::string word);
    void printTree(TwoFiveNode *n);
    void deleteFromLeaf(Truple &node);
    void deleteFromNonLeaf(TwoFiveNode* node, TwoFiveNode* parent, std::string word);
	void split(TwoFiveNode* node, TwoFiveNode* parent);
    TwoFiveNode* getRoot() {return this->root;}
    void rotateLeft(Truple tru);
    void rotateRight(Truple tru);
    DataPair* findMax(TwoFiveNode* node);
    void deleteWordFromTree(std::string word);
    void deleteWordFromTree(TwoFiveNode* node, TwoFiveNode* parent, std::string word);

};


#endif //CS130A_PROJECT2_TWOFIVETREE_HPP
