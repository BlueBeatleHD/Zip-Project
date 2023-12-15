#include "AVL.h"

Leaf* AVL::rightRotate(Leaf* currentHead)
{
	Leaf* leftChild = currentHead->left;
	Leaf* rightGrandChild = leftChild->right;

	leftChild->right = currentHead;
	currentHead->left = rightGrandChild;

	currentHead->height = updateHeightOfLeaf(currentHead);
	leftChild->height = updateHeightOfLeaf(leftChild);

	return leftChild;
}


Leaf* AVL::leftRotate(Leaf* currentHead)
{
	Leaf* rightChild = currentHead->right;
	Leaf* leftGrandChild = rightChild->left;

	rightChild->left = currentHead;
	currentHead->right = leftGrandChild;

	currentHead->height = updateHeightOfLeaf(currentHead);
	rightChild->height = updateHeightOfLeaf(rightChild);

	return rightChild;
}

int AVL::balanceFactor(Leaf* current)
{
	if (current == nullptr) return 0;
	int currentLeftHeight = current->left ? current->left->height : 0;
	int currentRightHeight = current->right ? current->right->height : 0;
	return currentLeftHeight - currentRightHeight;
}

int AVL::updateHeightOfLeaf(Leaf* current)
{
	int leftHeight = current->left ? current->left->height : 0;
	int rightHeight = current->right ? current -> right->height : 0;
	int height = 1 + std::max(leftHeight, rightHeight);
	return height;
}

void AVL::printTopX(int count)
{
	int startingRank = 1;
	printTopXHelper(head, count, startingRank);
}

void AVL::printLeastX(int count)
{
	int startingRank = 1;
	printLeastXHelper(head, count, startingRank);
}


void AVL::printLeastXHelper(Leaf* current, int count, int& rank)
{
	if (rank > count) return;
	if (current == nullptr) return;

	printLeastXHelper(current->left, count, rank);
	if (rank > count) return;
	cout << setw(4) << rank << ". The zipcode " << current->zipcode << " has a population of " << current->population << ".\n";
	rank++;
	printLeastXHelper(current->right, count, rank);
}
void AVL::printTopXHelper(Leaf* current, int count, int& rank)
{
	if (rank > count) return;
	if (current == nullptr) return;

	printTopXHelper(current->right,count,rank);
	if (rank > count) return;
	cout << setw(4) << rank <<  ". The zipcode " << current->zipcode << " has a population of " << current->population << ".\n";
	rank++;
	printTopXHelper(current->left, count, rank);
}

void AVL::displayTreeHelper(Leaf* current, int space = 0)
{
	if (!current) return;
	space += 3;

	displayTreeHelper(current->right, space);

	std::cout << "\n";
	for (int i = 0; i < space; i++)
	{
		std::cout << " ";
	}
	std::cout << current->population;

	displayTreeHelper(current->left, space);
}

void AVL::displayTree()
{
	displayTreeHelper(head, 0);
}

Leaf* AVL::insert(int population,int zipcode)
{
	Leaf* inserted = new Leaf(population,zipcode);
	head = insertHelper(inserted,head);
	return inserted;
}



Leaf* AVL::insertHelper(Leaf* toInsert, Leaf* currentLeaf)
{
	if (currentLeaf == nullptr)
	{
		return toInsert;
	}
	if (toInsert->population < currentLeaf->population)
	{
		currentLeaf->left = insertHelper(toInsert, currentLeaf->left);
	}
	else if (toInsert->population > currentLeaf->population)
	{
		currentLeaf->right = insertHelper(toInsert, currentLeaf->right);
	}
	else 
	{
		return currentLeaf;
	}

	currentLeaf->height = updateHeightOfLeaf(currentLeaf);

	int balance = balanceFactor(currentLeaf);

	//Left Case
	if (balance > 1 && toInsert->population < currentLeaf->left->population)
		return rightRotate(currentLeaf);

	//Right Case
	else if (balance < -1 && toInsert->population > currentLeaf->right->population)
		return leftRotate(currentLeaf);
	  
	//Left Right Case
	else if (balance > 1 && toInsert->population > currentLeaf->left->population)
	{
		currentLeaf->left = leftRotate(currentLeaf->left);
		return rightRotate(currentLeaf);
	}

	//Right Left Case
	else if (balance < -1 && toInsert->population < currentLeaf->right->population)
	{
		currentLeaf->right = rightRotate(currentLeaf->right);
		return leftRotate(currentLeaf);
	}

	return currentLeaf;
}

AVL::~AVL()
{
	delete head;
}