#pragma once
#include<algorithm> 
#include <iostream>
#include<string>
#include "Node.h"
struct Leaf
{
	Leaf* left;
	Leaf* right;
	int height;

	int population;
	int zipcode;
	Leaf(int pop,int zip) : population(pop), zipcode(zip)
	{
		left = nullptr;
		right = nullptr;
		height = 1;
	}
	~Leaf()
	{
		delete left;
		delete right;
	}
};


class AVL
{
	Leaf* head;
	Leaf* rightRotate(Leaf* currentHead);
	Leaf* leftRotate(Leaf* currentHead);
	int balanceFactor(Leaf* currentLeaf);
	void displayTreeHelper(Leaf* current, int space);
	Leaf* insertHelper(Leaf* toInsert,Leaf* currentLeaf);
	int updateHeightOfLeaf(Leaf* current);
	void printLeastXHelper(Leaf* current, int count, int& rank);
	void printTopXHelper(Leaf* current, int count, int& rank);
public:
	AVL()
	{
		head = nullptr;
	}
	~AVL();
	void displayTree();
	Leaf* insert(int population,int zipcode);
	void printTopX(int count);
	void printLeastX(int count);
};



