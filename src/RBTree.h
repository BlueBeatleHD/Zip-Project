//
//  RBTree.h
//  Project 3 - RedBlackTree
//

#ifndef RBTree_h
#define RBTree_h
#include <string>
#include <iomanip>
using namespace std;

struct RBNode {
    int data;
    int zipcode;
    bool color; //0 = black, 1 = red
    RBNode *left, *right, *parent;
    explicit RBNode(int, int);
};

class RBTree {
private:
    RBNode* root;
    int print_count_increasing = 0;
    int print_count_decreasing = 0;
public:
    RBTree();
    RBNode* insertTree(RBNode* &, RBNode* &);
    void fixInsertTree(RBNode* &);
    void insertValue(int, int);
    void rotateLeft(RBNode* &);
    void rotateRight(RBNode* &);
    bool getColor(RBNode* &);
    void setColor(RBNode* &, bool);
    
    void inorderBST(RBNode* &, int);
    void printBottom(int);
    
    void reverseInorderBST(RBNode* &, int);
    void printTop(int);
};

#endif /* RBTree_h */
