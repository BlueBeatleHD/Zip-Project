//
//  RBTree.cpp
//  Project 3 - RedBlackTree
//

#include <stdio.h>
#include <algorithm>
#include "RBTree.h"
#include <iostream>
using namespace std;

RBNode::RBNode(int data, int zipcode) {
    this->data = data;
    this->zipcode = zipcode;
    color = 1;
    left = right = parent = nullptr;
}

RBTree::RBTree() {
    root = nullptr;
}

RBNode* RBTree::insertTree(RBNode* &root, RBNode* &temp) {
    if (root == nullptr)
        return temp;

    if (temp->data < root->data) {
        root->left = insertTree(root->left, temp);
        root->left->parent = root;
    } else if (temp->data > root->data) {
        root->right = insertTree(root->right, temp);
        root->right->parent = root;
    }

    return root;
}

void RBTree::fixInsertTree(RBNode* &temp) {
    RBNode* parent = nullptr;
    RBNode* grandparent = nullptr;
    while (temp != root && getColor(temp) == 1 && getColor(temp->parent) == 1) {
        parent = temp->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            RBNode* uncle = grandparent->right;
            if (getColor(uncle) == 1) {
                setColor(uncle, 0);
                setColor(parent, 0);
                setColor(grandparent, 1);
                temp = grandparent;
            } else {
                if (temp == parent->right) {
                    rotateLeft(parent);
                    temp = parent;
                    parent = temp->parent;
                }
                rotateRight(grandparent);
                swap(parent->color, grandparent->color);
                temp = parent;
            }
        } else {
            RBNode* uncle = grandparent->left;
            if (getColor(uncle) == 1) {
                setColor(uncle, 0);
                setColor(parent, 0);
                setColor(grandparent, 1);
                temp = grandparent;
            } else {
                if (temp == parent->left) {
                    rotateRight(parent);
                    temp = parent;
                    parent = temp->parent;
                }
                rotateLeft(grandparent);
                swap(parent->color, grandparent->color);
                temp = parent;
            }
        }
    }
    setColor(root, 0);
}


void RBTree::insertValue(int n, int zip) {
    RBNode* node = new RBNode(n, zip);
    root = insertTree(root, node);
    fixInsertTree(node);
}

void RBTree::rotateLeft(RBNode* &temp) {
    RBNode* right_child = temp->right;
    temp->right = right_child->left;

    if (temp->right != nullptr)
        temp->right->parent = temp;

    right_child->parent = temp->parent;

    if (temp->parent == nullptr)
        root = right_child;
    else if (temp == temp->parent->left)
        temp->parent->left = right_child;
    else
        temp->parent->right = right_child;

    right_child->left = temp;
    temp->parent = right_child;
}

void RBTree::rotateRight(RBNode* &temp) {
    RBNode* left_child = temp->left;
    temp->left = left_child->right;

    if (temp->left != nullptr)
        temp->left->parent = temp;

    left_child->parent = temp->parent;

    if (temp->parent == nullptr)
        root = left_child;
    else if (temp == temp->parent->left)
        temp->parent->left = left_child;
    else
        temp->parent->right = left_child;

    left_child->right = temp;
    temp->parent = left_child;
}

bool RBTree::getColor(RBNode* &node) {
    if (node == nullptr)
        return 0;
    return node->color;
}

void RBTree::setColor(RBNode* &node, bool color) {
    if (node == nullptr)
        return;
    node->color = color;
}

void RBTree::inorderBST(RBNode* &temp, int count) {
    if (temp == nullptr)
        return;
    
    inorderBST(temp->left, count);
    if (print_count_increasing < count) {
        print_count_increasing++;
		cout << setw(4) << print_count_increasing << ". The zipcode " << temp->zipcode << " has a population of " << temp->data << "." << endl;
		inorderBST(temp->right, count);
    }
}

void RBTree::printBottom(int count) {
    inorderBST(root, count);
}

void RBTree::reverseInorderBST(RBNode* &temp, int count) {
    if (temp == nullptr)
        return;
	reverseInorderBST(temp->right, count);
    if (print_count_decreasing < count) {
        
        print_count_decreasing++;
        cout << setw(4) <<print_count_decreasing <<". The zipcode " << temp->zipcode << " has a population of " << temp->data << "." << endl;
        reverseInorderBST(temp->left, count);
    }
}

void RBTree::printTop(int count) {
    reverseInorderBST(root, count);
}
