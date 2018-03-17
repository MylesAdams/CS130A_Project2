
#ifndef CS130A_PROJECT2_AVLTREE_HPP
#define CS130A_PROJECT2_AVLTREE_HPP

#include <string>
#include <vector>


class AVLTree
{

public:
    struct AVLNode
    {
        std::string data;
        int count;
        int height;
        AVLNode* left;
        AVLNode* right;

        AVLNode()
        {
            this->data = "";
            this->count = 1;
            this->height = 1;
            this->left = nullptr;
            this->right = nullptr;
        }

        ~AVLNode()
        {
            delete right;
            delete left;
        }

        AVLNode(std::string data)
        {
            this->data = data;
            this->count = 1;
            this->height = 1;
            this->left = nullptr;
            this->right = nullptr;
        }

        static int getHeight(AVLNode* node)
        {
            if (node == nullptr)
                return 0;
            else
                return node->height;
        }
    };

    AVLNode* root;
    int count;
    AVLTree();
    ~AVLTree();
    static void rotateLeft(AVLNode*& root);
    static void rotateRight(AVLNode*& root);
    void insertWord(std::string word);
    bool searchWord(std::string word);
    void deleteWord(std::string word);
    AVLNode* searchNode(std::string word);
    std::vector<std::string> sort();
    void rangeSearch(std::string first, std::string last);

private:
    void balanceTree(AVLNode*& root);
    static void setHeight(AVLNode*& root);
    static int getBalance(AVLNode* root);
    void inOrder(AVLNode* root, std::vector<std::string>& vec);
    void inOrderRange(AVLNode* root, std::string first, std::string last);
    void deleteWord(AVLNode*& node, AVLNode*& parent, std::string& word);
    void insertWord(AVLNode*& root, std::string& word);
    AVLNode* findMinimum(AVLNode* node);




};


#endif //CS130A_PROJECT2_AVLTREE_HPP
