#include "AVL.h"
#include "Node.h"
#include "RBTree.h"
#include <chrono>
using namespace std;


int main() {
	vector<Node*> nodes;
	ifstream file;
	AVL AVLtree;
	cout << "Parsing through CSV..." << "\n";
	readData(file,nodes);
	cout <<"Found " << nodes.size() << " zipcodes!\n\n";
	std::chrono::time_point<std::chrono::system_clock> start_time, end_time;

	start_time = std::chrono::system_clock::now();
	for (int i = 0; i < nodes.size(); i++)
	{
	
		AVLtree.insert(nodes[i]->pop,nodes[i]->zip);
	}
	end_time = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end_time - start_time;
	cout << "Elapsed time to build the AVL Tree: " << elapsed_seconds.count() << "s\n\n";


	RBTree RedBlackTreePopulation;
	start_time = std::chrono::system_clock::now();
	for (int i = 0; i < nodes.size(); i++) {
		RedBlackTreePopulation.insertValue((*nodes[i]).pop, (*nodes[i]).zip);
	}
	end_time = std::chrono::system_clock::now();
	elapsed_seconds = end_time - start_time;
	std::cout << "Elapsed time to build the Red Black Tree: " << elapsed_seconds.count() << "s" << endl << endl;

	int input, c;
	cout << "Would you like to sort by increasing order or decreasing order?" << endl;
	cout << "1. Increasing order (starting with the lowest value)" << endl;
	cout << "2. Decreasing order (starting with the highest value)" << endl;
	cout << "Input: ";
	cin >> input;
	while (!(input == 1 || input == 2)) {
		cout << "Not a requested input. Please try again." << endl;
		cout << "Input: ";
		cin >> input;
	}
	cout << "\nHow many zipcodes would you like to display?" << endl;
	cout << "Input: ";
	cin >> c;
	cout << endl;
	start_time = std::chrono::system_clock::now();
	switch (input) {
	case 1:
		//Print zipcodes with lowest c values
		RedBlackTreePopulation.printBottom(c);
		break;
	case 2:
		//Print zipcodes with highest c values
		RedBlackTreePopulation.printTop(c);
		break;
	}
	end_time = std::chrono::system_clock::now();
	elapsed_seconds = end_time - start_time;
	std::cout << "Elapsed time to sort and display the desired number of zipcodes for the Red Black Tree is: " << elapsed_seconds.count() << "s\n" << endl;


	start_time = std::chrono::system_clock::now();
	switch (input)
	{
	case 1:
		AVLtree.printLeastX(c);
		break;

	case 2:
		AVLtree.printTopX(c);
		break;
	}
	end_time = std::chrono::system_clock::now();
	elapsed_seconds = end_time - start_time;
	std::cout << "Elapsed time to sort and display the desired number of zipcodes for the AVL tree is: " << elapsed_seconds.count() << "s" << endl;
}
