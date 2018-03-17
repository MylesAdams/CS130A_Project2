//
// Created by Myles Adams on 2/27/18.
//

#include <iostream>
#include "AVLTree.hpp"
#include "TwoFiveTree.hpp"
#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>
#include <regex>
#include <chrono>
#include <unordered_map>


const std::string SORT_OUTPUT_FILEPATH = "../sort.txt";

const std::string TEST_OUTPUT = "../test_output.txt";

const std::string DATA_PATH = "../hotels-small/";

const double NANO = 1000000000.0;

// 100 words for testing
const std::vector<std::string> wordsToTest = {"hello", "omg", "zip", "first", "for", "from", "get", "give", "go",
                                              "have",
                                              "he",
                                              "her", "here", "asd", "aa-", "soccer", "pie", "ability", "babypool",
                                              "breaker",
                                              "ppood", "what", "joke", "cause", "cats", "cattle", "dog",
                                              "abbababababba",
                                              "clijpc",
                                              "poq", "asd,,''", "pier", "but", "why", "so", "joke", "peach", "iijasd",
                                              "i", "iuy",
                                              ".,.,", "but", "can't", "dollar", "dome", "everyone-", "everynight",
                                              "everywhere",
                                              "bye", "goodnight", "pui", "guise", "guitar", "pony", "qwer", "pool",
                                              "night",
                                              "children", "sid", "oasdo", "ododod", "yuyuuyuy", "iuqweu", "hdhdhdh",
                                              "giant",
                                              "lkasdjh", "0123", ",z,z,z,", "please", "thank-you", "seven", "guidebook",
                                              "pieme", "guests'", "guite", "gulou", "akjshdjkhas", "wjnasjd", "higher",
                                              "high", "hub", "induce", "infact", "lol", "old", "young", "zen", "zone",
                                              "zoning", "zoo", "///asd", "iu", "worn", "world", "worries", "mild",
                                              "zzzz",
                                              "wost", "workman", "nine"};

std::vector<std::string> open(std::string path);

void testAll(AVLTree *&avl, TwoFiveTree *&tft);

void testAVLSearch(AVLTree *&avl, std::ofstream &output);

void testAVLInsert(AVLTree *&avl, std::ofstream &output);

void testAVLDelete(AVLTree *&avl, std::ofstream &output);

void testAVLSort(AVLTree *&avl, std::ofstream &output);

void testAVLRangeSearch(AVLTree *&avl, std::ofstream &output);

void testTFTSearch(TwoFiveTree *&tft, std::ofstream &output);

void testTFTInsert(TwoFiveTree *&tft, std::ofstream &output);

void testTFTDelete(TwoFiveTree *&tft, std::ofstream &output);

void testTFTSort(TwoFiveTree *&tft, std::ofstream &output);

void testTFTRangeSearch(TwoFiveTree *&tft, std::ofstream &output);

int main()
{

    AVLTree *avl = new AVLTree();
    TwoFiveTree *tft = new TwoFiveTree();

    // Vectors of all filenames
    std::vector<std::string> beijingFiles = open(DATA_PATH + "beijing");
    std::vector<std::string> chicagoFiles = open(DATA_PATH + "chicago");
    std::vector<std::string> dubaiFiles = open(DATA_PATH + "dubai");
    std::vector<std::string> lasvegasFiles = open(DATA_PATH + "las-vegas");
    std::vector<std::string> londonFiles = open(DATA_PATH + "london");
    std::vector<std::string> montrealFiles = open(DATA_PATH + "montreal");
    std::vector<std::string> newdelhiFiles = open(DATA_PATH + "new-delhi");
    std::vector<std::string> nycFiles = open(DATA_PATH + "new-york-city");
    std::vector<std::string> sfFiles = open(DATA_PATH + "san-francisco");
    std::vector<std::string> shanghaiFiles = open(DATA_PATH + "shanghai");

    // Vector of groupings of all files
    std::vector<std::vector<std::string> > allFiles;
    allFiles.push_back(beijingFiles);
    allFiles.push_back(chicagoFiles);
    allFiles.push_back(dubaiFiles);
    allFiles.push_back(lasvegasFiles);
    allFiles.push_back(londonFiles);
    allFiles.push_back(montrealFiles);
    allFiles.push_back(newdelhiFiles);
    allFiles.push_back(nycFiles);
    allFiles.push_back(sfFiles);
    allFiles.push_back(shanghaiFiles);

    // Vector of all folder names
    std::vector<std::string> folderNames;
    folderNames.push_back("beijing/");
    folderNames.push_back("chicago/");
    folderNames.push_back("dubai/");
    folderNames.push_back("las-vegas/");
    folderNames.push_back("london/");
    folderNames.push_back("montreal/");
    folderNames.push_back("new-delhi/");
    folderNames.push_back("new-york-city/");
    folderNames.push_back("san-francisco/");
    folderNames.push_back("shanghai/");

    // Array of all stop words
    std::string stopwords[127] = {"i", "me", "my", "myself", "we", "our", "ours", "ourselves", "you", "your", "yours",
                                  "yourself", "yourselves", "he", "him", "his", "himself", "she", "her", "hers",
                                  "herself", "it", "its", "itself", "they", "them", "their", "theirs", "themselves",
                                  "what", "which", "who", "whom", "this", "that", "these", "those", "am", "is", "are",
                                  "was", "were", "be", "been", "being", "have", "has", "had", "having", "do", "does",
                                  "did", "doing", "a", "an", "the", "and", "but", "if", "or", "because", "as", "until",
                                  "while", "of", "at", "by", "for", "with", "about", "against", "between", "into",
                                  "through", "during", "before", "after", "above", "below", "to", "from", "up", "down",
                                  "in", "out", "on", "off", "over", "under", "again", "further", "then", "once", "here",
                                  "there", "when", "where", "why", "how", "all", "any", "both", "each", "few", "more",
                                  "most", "other", "some", "such", "no", "nor", "not", "only", "own", "same", "so",
                                  "than", "too", "very", "s", "t", "can", "will", "just", "don", "should", "now"};

    // Put stop words into hash table
    std::unordered_map<std::string, int> stopwordsHash(500);
    for (int i = 0; i < 127; i++)
    {
        stopwordsHash.insert({stopwords[i], 0});
    }

    // Prepare regex
    std::string rgxWord;
    std::string word;
    std::regex rgx("[a-z]+[a-z_'-]*");

    // Go through all files and build BST from unique words
    for (int i = 0; i < allFiles.size(); i++)
    {
        for (int j = 2; j < allFiles[i].size(); j++)
        {
            std::ifstream file;
            file.open(DATA_PATH + folderNames[i] + allFiles[i][j]);
            while (file >> rgxWord)
            {
                std::transform(rgxWord.begin(), rgxWord.end(), rgxWord.begin(), ::tolower);
                for (std::sregex_iterator iter(rgxWord.begin(), rgxWord.end(), rgx), it_end; iter != it_end; iter++)
                {
                    word = iter->str();
                    if (stopwordsHash.find(word) == stopwordsHash.end())
                    {
                        avl->insertWord(word);
                        tft->insertWord(word);
                    }
                }
            }
        }
    }



    auto start = std::chrono::high_resolution_clock::now();
    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
    int choice;
    std::string startWord, endWord;
    double seconds;
    double secondsHash;
    std::ofstream sortFile;
    std::vector<std::string> avlSorted, hashSorted;

    // Format cout
    std::cout.precision(17);
    std::cout << std::boolalpha;

    /* Uncomment the line below to test program and write timings to ../test_output.txt */
    //testAll(bst, hashTable);

    // Command Line user interface
    while (true)
    {
        std::cout
                << "Enter a number to execute an action.\n1 (search), 2 (insert), 3 (delete), 4 (sort), 5 (range search).\n";
        std::cin >> choice;

        while (!std::cin || choice < 1 || choice > 5)
        {
            std::cin.clear();
            std::cin.ignore(512, '\n');
            std::cout << "Invalid entry.\n";
            std::cout
                    << "Enter a number to execute an action.\n1 (search), 2 (insert), 3 (delete), 4 (sort), 5 (range search).\n";
            std::cin >> choice;
        }

        switch (choice)
        {
            case 1:
                std::cout << "Enter word to search:\n";
                std::cin >> word;
                bool found;

                start = std::chrono::high_resolution_clock::now();
                found = avl->searchWord(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << found << std::endl;
                std::cout << std::fixed << "AVL: " << seconds << " s" << std::endl;

                start = std::chrono::high_resolution_clock::now();
                found = tft->search(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << std::fixed << "TFT: " << seconds << " s\n" << std::endl;
                break;

            case 2:
                std::cout << "Enter word to insert:\n";
                std::cin >> word;

                start = std::chrono::high_resolution_clock::now();
                avl->insertWord(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << std::fixed << "AVL: " << seconds << " s" << std::endl;

                start = std::chrono::high_resolution_clock::now();
                tft->insertWord(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << std::fixed << "TFT: " << seconds << " s\n" << std::endl;
                break;

            case 3:
                std::cout << "Enter word to delete:\n";
                std::cin >> word;

                start = std::chrono::high_resolution_clock::now();
                avl->deleteWord(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << "AVL: " << std::fixed << seconds << " s" << std::endl;

                start = std::chrono::high_resolution_clock::now();
                tft->deleteWordFromTree(word);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << std::fixed << "TFT: " << seconds << " s\n" << std::endl;
                break;

            case 4:
                std::cout << SORT_OUTPUT_FILEPATH << std::endl;

                start = std::chrono::high_resolution_clock::now();
                avlSorted = avl->sort();
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << "AVL: " << std::fixed << seconds << " s" << std::endl;

                start = std::chrono::high_resolution_clock::now();
                hashSorted = tft->sort();
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;
                std::cout << "TFT: " << std::fixed << seconds << " s\n" << std::endl;

                sortFile.open(SORT_OUTPUT_FILEPATH);
                for (auto word : avlSorted)
                    sortFile << word + "\n";
                sortFile << "\n";
                for (auto word : hashSorted)
                {
                    if (word != "" && word != " ")
                        sortFile << word + "\n";
                }
                sortFile.close();
                break;

            case 5:
                std::cout << "Enter the start word\n";
                std::cin >> startWord;
                std::cout << "Enter the end word\n";
                std::cin >> endWord;

                start = std::chrono::high_resolution_clock::now();
                avl->rangeSearch(startWord, endWord);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                seconds = ns / NANO;

                std::cout << std::endl;

                start = std::chrono::high_resolution_clock::now();
                tft->rangeSearch(startWord, endWord);
                end = std::chrono::high_resolution_clock::now();
                dur = end - start;
                ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();
                secondsHash = ns / NANO;
                std::cout << "\nAVL: " << std::fixed << seconds << " s" << std::endl;
                std::cout << "TFT: " << std::fixed << secondsHash << " s\n" << std::endl;
                break;

            default:
                break;
        }
    }
}

// Find files and return vector of strings
std::vector<std::string> open(std::string path = ".")
{
    DIR *dir;
    dirent *pdir;
    std::vector<std::string> files;

    dir = opendir(path.c_str());

    while ((pdir = readdir(dir)))
        files.push_back(pdir->d_name);

    return files;
}


// Test all functionality of BST and Hash Table
void testAll(AVLTree *&avl, TwoFiveTree *&tft)
{
    std::ofstream testOutput;
    testOutput.open(TEST_OUTPUT);

    testAVLSearch(avl, testOutput);
    testAVLInsert(avl, testOutput);
    testAVLDelete(avl, testOutput);
    testAVLSort(avl, testOutput);
    testAVLRangeSearch(avl, testOutput);

    testTFTSearch(tft, testOutput);
    testTFTInsert(tft, testOutput);
    testTFTDelete(tft, testOutput);
    testTFTSort(tft, testOutput);
    testTFTRangeSearch(tft, testOutput);

    testOutput.close();
}

// Test BST Search
void testAVLSearch(AVLTree *&avl, std::ofstream &output)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (std::string word : wordsToTest)
        avl->searchWord(word);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "BST Search (100 words): ";
    output << ns / NANO;
    output << "\n\n";
}

// Test BST Insert
void testAVLInsert(AVLTree *&avl, std::ofstream &output)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (std::string word : wordsToTest)
        avl->insertWord(word);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "BST Insert (100 words): ";
    output << ns / NANO;
    output << "\n\n";
}

// Test BST Delete
void testAVLDelete(AVLTree *&avl, std::ofstream &output)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (std::string word : wordsToTest)
        avl->deleteWord(word);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "BST Delete (100 words): ";
    output << ns / NANO;
    output << "\n\n";
}

// Test BST Sort
void testAVLSort(AVLTree *&avl, std::ofstream &output)
{
    auto start = std::chrono::high_resolution_clock::now();

    avl->sort();

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "BST Sort (all words): ";
    output << ns / NANO;
    output << "\n\n";
}

// Test BST Range Search
void testAVLRangeSearch(AVLTree *&avl, std::ofstream &output)
{
    auto start = std::chrono::high_resolution_clock::now();

    avl->rangeSearch("a-", "abad");

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "BST Range Search (10 words): ";
    output << ns / NANO;
    output << "\n\n";

    start = std::chrono::high_resolution_clock::now();

    avl->rangeSearch("a-", "accomodating");

    end = std::chrono::high_resolution_clock::now();
    dur = end - start;
    ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "BST Range Search (100 words): ";
    output << ns / NANO;
    output << "\n\n";

    start = std::chrono::high_resolution_clock::now();

    avl->rangeSearch("a-", "astetics");

    end = std::chrono::high_resolution_clock::now();
    dur = end - start;
    ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "BST Range Search (1000 words): ";
    output << ns / NANO;
    output << "\n\n";
}

// Test Hash Table Search
void testTFTSearch(TwoFiveTree *&tft, std::ofstream &output)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (std::string word : wordsToTest)
        tft->search(word);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "Hash Search (100 words): ";
    output << ns / NANO;
    output << "\n\n";
}

// Test Hash Table Insert
void testTFTInsert(TwoFiveTree *&tft, std::ofstream &output)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (std::string word : wordsToTest)
        tft->insertWord(word);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "Hash Insert (100 words): ";
    output << ns / NANO;
    output << "\n\n";
}

// Test Hash Table Delete
void testTFTDelete(TwoFiveTree *&tft, std::ofstream &output)
{
    auto start = std::chrono::high_resolution_clock::now();

    for (std::string word : wordsToTest)
        tft->deleteWordFromTree(word);

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "Hash Delete (100 words): ";
    output << ns / NANO;
    output << "\n\n";
}

// Test Hash Table Sort
void testTFTSort(TwoFiveTree *&tft, std::ofstream &output)
{
    auto start = std::chrono::high_resolution_clock::now();

    tft->sort();

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "Hash Sort (all words): ";
    output << ns / NANO;
    output << "\n\n";
}

// Test Hash Table Range Search
void testTFTRangeSearch(TwoFiveTree *&tft, std::ofstream &output)
{
    auto start = std::chrono::high_resolution_clock::now();

    tft->rangeSearch("a-", "abad");

    auto end = std::chrono::high_resolution_clock::now();
    auto dur = end - start;
    auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "Hash Range Search (10 words): ";
    output << ns / NANO;
    output << "\n\n";

    start = std::chrono::high_resolution_clock::now();

    tft->rangeSearch("a-", "accomodating");

    end = std::chrono::high_resolution_clock::now();
    dur = end - start;
    ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "Hash Range Search (100 words): ";
    output << ns / NANO;
    output << "\n\n";

    start = std::chrono::high_resolution_clock::now();

    tft->rangeSearch("a-", "astetics");

    end = std::chrono::high_resolution_clock::now();
    dur = end - start;
    ns = std::chrono::duration_cast<std::chrono::nanoseconds>(dur).count();

    output << "Hash Range Search (1000 words): ";
    output << ns / NANO;
    output << "\n\n";
}

//int main()
//{
//    std::cout << "CS130A Project 2" << std::endl;
//
//    AVLTree* tree = new AVLTree();
//
//    std::string a, b, c, d, e;
//    a = "a";
//    b = "b";
//    c = "c";
//    d = "d";
//    e = "e";
//
//    // LL Test
////    tree->insertWord(b);
////    tree->insertWord(a);
////    tree->insertWord(d);
////    tree->insertWord(c);
////    tree->insertWord(e);
////    tree->deleteWord(a);
//
//
//    // LR Test
////    tree->insertWord(b);
////    tree->insertWord(a);
////    tree->insertWord(d);
////    tree->insertWord(c);
////    tree->deleteWord(a);
//
//
//    // RR Test
////    tree->insertWord(d);
////    tree->insertWord(b);
////    tree->insertWord(e);a
////    tree->insertWord(a);
////    tree->insertWord(c);
////    tree->deleteWord(e);
//
//    // RL Test
////    tree->insertWord(c);
////    tree->insertWord(a);
////    tree->insertWord(d);
////    tree->insertWord(b);
////    tree->deleteWord(d);
//
////    tree->insertWord("18");
////    tree->insertWord("23");
////    tree->insertWord("27");
////    tree->insertWord("13");
////    tree->insertWord("16");
////    tree->insertWord("10");
////    tree->insertWord("33");
////    tree->insertWord("39");
////    tree->insertWord("28");
//
//
////    std::vector<AVLTree::AVLNode*> nodes;
////
////    AVLTree::AVLNode* node = new AVLTree::AVLNode("a");
////    nodes.push_back(node);
////
////    AVLTree::AVLNode* nodeptr = nodes[0];
////
////    nodes.erase(nodes.begin(), nodes.end());
////
////    TwoFiveTree::TwoFiveNode* node1 = new TwoFiveTree::TwoFiveNode("a");
////    TwoFiveTree::TwoFiveNode* node2 = new TwoFiveTree::TwoFiveNode("b");
////
////    std::vector<TwoFiveTree::TwoFiveNode*>* moreNodes = new std::vector<TwoFiveTree::TwoFiveNode*>({node1, node2});
////
////    std::cout << (*(*moreNodes)[0]->data)[0]->word << std::endl;
////    std::cout << (*(*moreNodes)[1]->data)[0]->word << std::endl;
////
////    std::cout << moreNodes->size() << std::endl;
////    std::cout << (*(*moreNodes)[1]->data).size() << std::endl;
//
//
//
////    std::cout << nodeptr->data << nodeptr->count << nodes.size() << std::endl;
//
//
////    std::vector<TwoFiveTree::TwoFiveNode*>* nodes2 = new std::vector<TwoFiveTree::TwoFiveNode*>(5);
////    std::cout << nodes2->size()<< std::endl;
////    std::cout << ((*nodes2)[0] == nullptr) << std::endl;
//
//
//
////    tree->root = new AVLTree::AVLNode("C");
////    tree->root->left = new AVLTree::AVLNode("B");
////    tree->root->left->left = new AVLTree::AVLNode("A");
//
////    AVLTree::rotateRight(tree->root);
//
//    TwoFiveTree* tft = new TwoFiveTree();
//
//    tft->insertWord("30");
////    std::cout << (*tft->getRoot()->data)[0]->word << std::endl;
//    tft->insertWord("10");
//    tft->insertWord("15");
//    tft->insertWord("40");
//    tft->insertWord("45");
//    tft->insertWord("20");
//    tft->insertWord("50");
//    tft->insertWord("55");
//    tft->insertWord("60");
//    tft->insertWord("24");
//    tft->insertWord("28");
//    tft->insertWord("12");
//    tft->insertWord("11");
//    tft->insertWord("14");
//    tft->insertWord("56");
//    tft->insertWord("57");
//    tft->insertWord("70");
//
//    //prints left, right, parent. So root is last
//    tft->printTree(tft->getRoot());
//
//
////    tft->deleteWord(tft->getRoot(), tft->getRoot(), "70");
////    std::cout << "\n\n Deleted 70.. Result: \n";
////    tft->printTree(tft->getRoot());
////
////    tft->deleteWord(tft->getRoot(), tft->getRoot(), "60");
////    std::cout << "\n\n Deleted 60.. Result: \n";
////    tft->printTree(tft->getRoot());
////
////    tft->deleteWord(tft->getRoot(), tft->getRoot(), "10");
////    std::cout << "\n\n Deleted 10.. Result: \n";
////    tft->printTree(tft->getRoot());
////
////    tft->deleteWord(tft->getRoot(), tft->getRoot(), "11");
////    std::cout << "\n\n Deleted 11.. Result: \n";
////    tft->printTree(tft->getRoot());
////
////    tft->deleteWord(tft->getRoot(), tft->getRoot(), "45");
////    std::cout << "\n\n Deleted 45.. Result: \n";
////    tft->printTree(tft->getRoot());
////
////    tft->deleteWord(tft->getRoot(), tft->getRoot(), "57");
////    std::cout << "\n\n Deleted 55.. Result: \n";
////    tft->printTree(tft->getRoot());
////
////    tft->deleteWord(tft->getRoot(), tft->getRoot(), "28");
////    std::cout << "\n\n Deleted 28.. Result: \n";
////    tft->printTree(tft->getRoot());
////
////    tft->deleteWord(tft->getRoot(), tft->getRoot(), "15");
////    std::cout << "\n\n Deleted 15.. Result: \n";
////    tft->printTree(tft->getRoot());
////
////    tft->deleteWord(tft->getRoot(), tft->getRoot(), "30");
////    std::cout << "\n\n Deleted 30.. Result: \n";
////    tft->printTree(tft->getRoot());
////
////    tft->deleteWord(tft->getRoot(), tft->getRoot(), "24");
////    std::cout << "\n\n Deleted 24.. Result: \n";
////    tft->printTree(tft->getRoot());
//
//    tft->deleteWordFromTree("70");
//    std::cout << "\n\n Deleted 70.. Result: \n";
//    tft->printTree(tft->getRoot());
//
//    tft->deleteWordFromTree("60");
//    std::cout << "\n\n Deleted 60.. Result: \n";
//    tft->printTree(tft->getRoot());
//
//    tft->deleteWordFromTree("10");
//    std::cout << "\n\n Deleted 10.. Result: \n";
//    tft->printTree(tft->getRoot());
//
//    tft->deleteWordFromTree("11");
//    std::cout << "\n\n Deleted 11.. Result: \n";
//    tft->printTree(tft->getRoot());
//
//    tft->deleteWordFromTree("45");
//    std::cout << "\n\n Deleted 45.. Result: \n";
//    tft->printTree(tft->getRoot());
//
//    tft->deleteWordFromTree("57");
//    std::cout << "\n\n Deleted 57.. Result: \n";
//    tft->printTree(tft->getRoot());
//
//    tft->deleteWordFromTree("28");
//    std::cout << "\n\n Deleted 28.. Result: \n";
//    tft->printTree(tft->getRoot());
//
//    tft->deleteWordFromTree("15");
//    std::cout << "\n\n Deleted 15.. Result: \n";
//    tft->printTree(tft->getRoot());
//
//
//    tft->insertWord("57");
//    tft->insertWord("58");
//    tft->insertWord("59");
//    tft->insertWord("60");
//    tft->insertWord("61");
//    tft->insertWord("62");
//    tft->insertWord("63");
//    tft->insertWord("64");
//    tft->insertWord("65");
//
//    tft->deleteWordFromTree("24");
//    std::cout << "\n\n Deleted 24.. Result: \n";
//    tft->printTree(tft->getRoot());
//
//    std::cout << std::endl;
//
//
//    tft->printTree(tft->getRoot());
//
//    tft->deleteWordFromTree("14");
//    std::cout << "\n\n Deleted 14.. Result: \n";
//    tft->printTree(tft->getRoot());
//
//
//
//
////
////    tft->deleteWordFromTree("30");
////    std::cout << "\n\n Deleted 30.. Result: \n";
////    tft->printTree(tft->getRoot());
////
//
//
//    std::cout << "\n\n" << std::endl;
//
//    tft->rangeSearch(tft->getRoot(), "20", "56");
//
//    std::cout << "\n\n" << std::endl;
//
//    std::vector<std::string> sortedVec = tft->sort(tft->getRoot());
//
//    for (int i = 0; i < sortedVec.size(); i++)
//        std::cout << sortedVec[i] << std::endl;
////    for (int i = 0; i < tft->getRoot()->numData; i++)
////    {
////        for (int j = 0; j < (*tft->getRoot()->pointers)[i]->data->size(); j++)
////        {
////            std::cout << (*(*tft->getRoot()->pointers)[i]->data)[j]->word << std::endl;
////        }
////        std::cout << "Root: " << (*tft->getRoot()->data)[i]->word << std::endl;
////    }
////
////    int index = tft->getRoot()->numData;
////    std::vector<TwoFiveTree::DataPair*> vec = (*(*tft->getRoot()->pointers)[index]->data);
////    int endSize = vec.size();
////    for (int i = 0; i < endSize; i++)
////    {
////        std::cout << (*(*tft->getRoot()->pointers)[tft->getRoot()->numData]->data)[i]->word << std::endl;
////    }
//
//
//    std::cout << "\n" << std::endl;
//
//    TwoFiveTree::DataPair* datapair = new TwoFiveTree::DataPair("Hello");
//    delete datapair;
//    std::cout << datapair->word << std::endl;
//
//    return  0;
//}